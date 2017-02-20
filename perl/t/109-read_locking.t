# Licensed to the Apache Software Foundation (ASF) under one or more
# contributor license agreements.  See the NOTICE file distributed with
# this work for additional information regarding copyright ownership.
# The ASF licenses this file to You under the Apache License, Version 2.0
# (the "License"); you may not use this file except in compliance with
# the License.  You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

use strict;
use warnings;
use lib 'buildlib';

use Test::More tests => 30;

package NonMergingIndexManager;
use base qw( Lucy::Index::IndexManager );
sub recycle { [] }

package main;
use Scalar::Util qw( blessed );

use Lucy::Test::TestUtils qw( create_temp_folder );
use Lucy::Util::IndexFileNames qw( latest_snapshot );

my $manager          = Lucy::Index::IndexManager->new;
my $no_merge_manager = NonMergingIndexManager->new;
my $other_manager    = Lucy::Index::IndexManager->new;

$manager->use_portable_locks('host1');
$no_merge_manager->use_portable_locks('host1');
$other_manager->use_portable_locks('host2');
test_with_managers( $manager, $no_merge_manager, $other_manager );

$manager->use_native_locks;
$no_merge_manager->use_native_locks;
$other_manager->use_native_locks;
test_with_managers( $manager, $no_merge_manager, $other_manager );

sub test_with_managers {
    my ( $manager, $no_merge_manager, $other_manager ) = @_;

    my $folder  = create_temp_folder();
    my $schema  = Lucy::Test::TestSchema->new;
    my $indexer = Lucy::Index::Indexer->new(
        index   => $folder,
        schema  => $schema,
        manager => $manager,
    );
    $indexer->add_doc( { content => $_ } ) for qw( a b c );
    $indexer->commit;

    $indexer = Lucy::Index::Indexer->new(
        index   => $folder,
        schema  => $schema,
        manager => $manager,
        create  => 1,
    );
    $indexer->delete_by_term( field => 'content', term => $_ ) for qw( a b c );
    $indexer->add_doc( { content => 'x' } );

    # Request exclusive snapshot lock.
    my $snapshot_lock = $manager->make_snapshot_lock('snapshot_1.json');
    ok( $snapshot_lock, "Make snapshot lock" );
    ok( $snapshot_lock->request_exclusive, "Request snapshot lock" );

    $indexer->commit;

    my $num_ds_files = grep {m/documents\.dat$/} @{ $folder->list_r };
    cmp_ok( $num_ds_files, '>', 1,
        "Indexer doesn't process deletions when it can't get snapshot lock" );

    my $num_snap_files = grep {m/snapshot.*\.json/} @{ $folder->list_r };
    is( $num_snap_files, 2, "didn't zap the old snap file" );

    my $reader;
    SKIP: {
        skip( "IndexReader opening failure leaks", 1 )
            if $ENV{LUCY_VALGRIND};
        my $snapshot = Lucy::Index::Snapshot->new;
        $snapshot->read_file(
            folder => $folder,
            path   => 'snapshot_1.json',
        );
        eval {
            $reader = Lucy::Index::IndexReader->open(
                index    => $folder,
                snapshot => $snapshot,
                manager  => $other_manager,
            );
        };
        ok( blessed($@) && $@->isa("Lucy::Store::LockErr"),
            "IndexReader dies if it can't get snapshot lock"
        );
    }

    $snapshot_lock->release;

    # Close the CompoundFileReader for seg_1, so seg_1/cf.dat will be closed.
    # Otherwise, renaming seg_1 will fail on Windows.
    $folder->find_folder('seg_1')->close;

    Test_race_condition_1: {
        my $num_prev_passes = Lucy::Index::IndexReader::debug1_num_passes();
        my $latest_snapshot_file = latest_snapshot($folder);

        # Artificially set up situation where the index was updated and files
        # PolyReader was expecting to see were zapped after a snapshot file was
        # picked.
        $folder->rename( from => $latest_snapshot_file, to => 'temp' )
            or die Clownfish->error;
        $folder->rename(
            from => 'seg_1',
            to   => 'seg_1.hidden',
        ) or die Clownfish->error;
        Lucy::Index::IndexReader::set_race_condition_debug1(
            Clownfish::String->new($latest_snapshot_file) );

        $reader = Lucy::Index::IndexReader->open(
            index   => $folder,
            manager => $other_manager,
        );
        is( $reader->doc_count, 1,
            "reader overcomes race condition of index update after read lock" );
        is( Lucy::Index::IndexReader::debug1_num_passes(),
            $num_prev_passes + 2, "reader retried before succeeding" );

        # Clean up our artificial mess.
        $folder->rename(
            from => 'seg_1.hidden',
            to   => 'seg_1',
        );
        Lucy::Index::IndexReader::set_race_condition_debug1(undef);

        $reader->close;
    }

    # Start over with one segment.
    $folder  = create_temp_folder();
    $indexer = Lucy::Index::Indexer->new(
        index   => $folder,
        schema  => $schema,
        manager => $manager,
    );
    $indexer->add_doc( { content => $_ } ) for qw( a b c x );
    $indexer->commit;

    {
        # Add a second segment and delete one doc from existing segment.
        $indexer = Lucy::Index::Indexer->new(
            schema  => $schema,
            index   => $folder,
            manager => $no_merge_manager,
        );
        $indexer->add_doc( { content => 'foo' } );
        $indexer->add_doc( { content => 'bar' } );
        $indexer->delete_by_term( field => 'content', term => 'x' );
        $indexer->commit;

        # Delete a doc from the second seg and increase del gen on first seg.
        $indexer = Lucy::Index::Indexer->new(
            schema  => $schema,
            index   => $folder,
            manager => $no_merge_manager,
        );
        $indexer->delete_by_term( field => 'content', term => 'a' );
        $indexer->delete_by_term( field => 'content', term => 'foo' );
        $indexer->commit;
    }

    # Establish read lock.
    $reader = Lucy::Index::IndexReader->open(
        index   => $folder,
        manager => $other_manager,
    );

    $indexer = Lucy::Index::Indexer->new(
        index   => $folder,
        schema  => $schema,
        manager => $manager,
    );
    $indexer->delete_by_term( field => 'content', term => 'a' );
    $indexer->optimize;
    $indexer->commit;

    my $files = $folder->list_r;
    $num_snap_files = scalar grep {m/snapshot_\w+\.json$/} @$files;
    is( $num_snap_files, 2, "lock preserved last snapshot file" );
    my $num_del_files = scalar grep {m/deletions-seg_1\.bv$/} @$files;
    is( $num_del_files, 2, "outdated but locked del files survive" );
    ok( $folder->exists('seg_3/deletions-seg_1.bv'),
        "first correct old del file" );
    ok( $folder->exists('seg_3/deletions-seg_2.bv'),
        "second correct old del file" );
    $num_ds_files = scalar grep {m/documents\.dat$/} @$files;
    cmp_ok( $num_ds_files, '>', 1, "segment data files preserved" );

    undef $reader;
    $indexer = Lucy::Index::Indexer->new(
        index   => $folder,
        schema  => $schema,
        manager => $manager,
    );
    $indexer->optimize;
    $indexer->commit;

    $files = $folder->list_r;
    $num_del_files = scalar grep {m/deletions/} @$files;
    is( $num_del_files, 0, "lock freed, del files optimized away" );
    $num_snap_files = scalar grep {m/snapshot_\w+\.json$/} @$files;
    is( $num_snap_files, 1, "lock freed, now only one snapshot file" );
    $num_ds_files = scalar grep {m/documents\.dat$/} @$files;
    is( $num_ds_files, 1, "lock freed, now only one ds file" );
}

