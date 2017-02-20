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

use Test::More tests => 9;
use Lucy::Test::TestUtils qw( create_temp_folder );

my $manager       = Lucy::Index::IndexManager->new;
my $other_manager = Lucy::Index::IndexManager->new;

$manager->use_portable_locks('host1');
$other_manager->use_portable_locks('host2');
test_write_lock( $manager, $other_manager );

$manager->use_native_locks;
$other_manager->use_native_locks;
test_write_lock( $manager, $other_manager );

$manager->use_native_locks;
$other_manager->use_portable_locks('host2');
test_lock_type_mismatch( $manager, $other_manager );
test_lock_type_mismatch( $other_manager, $manager );

sub test_write_lock {
    my ( $manager, $other_manager ) = @_;

    my $folder = create_temp_folder();
    my $schema = Lucy::Test::TestSchema->new;

    my $indexer = Lucy::Index::Indexer->new(
        index   => $folder,
        schema  => $schema,
        manager => $manager,
    );

    $indexer->add_doc( { content => 'foo' } );
    undef $indexer;

    $indexer = Lucy::Index::Indexer->new(
        index   => $folder,
        schema  => $schema,
        manager => $manager,
    );
    $indexer->add_doc( { content => 'foo' } );
    pass("Indexer ignores garbage from interrupted session");

    $other_manager->set_write_lock_timeout(0);
    eval {
        my $inv = Lucy::Index::Indexer->new(
            manager => $other_manager,
            index   => $folder,
            schema  => $schema,
        );
    };
    like( $@, qr/write.lock/, "failed to get lock with competing host" );
    isa_ok( $@, "Lucy::Store::LockErr", "Indexer throws a LockErr" );
    $other_manager->set_write_lock_timeout(1000);

    $indexer->commit;

    if ( $manager->get_lock_type ne 'native' ) {
        my $host = $other_manager->get_host;
        my $pid = 12345678;
        do {
            # Fake a write lock.
            my $outstream = $folder->open_out('locks/write.lock')
                or die Clownfish->error;
            while ( kill( 0, $pid ) ) {
                $pid++;
            }
            $outstream->print(
                qq|
                {
                    "host": "$host",
                    "pid": "$pid",
                    "name": "write"
                }|
            );
            $outstream->close;

            eval {
                my $inv = Lucy::Index::Indexer->new(
                    manager => $other_manager,
                    schema  => $schema,
                    index   => $folder,
                );
            };

            # Mitigate (though not eliminate) race condition false failure.
        } while ( kill( 0, $pid ) );

        ok( !$@, "clobbered lock from same host with inactive pid" );
    }
}

sub test_lock_type_mismatch {
    my ( $manager, $other_manager ) = @_;

    my $folder = create_temp_folder();
    my $schema = Lucy::Test::TestSchema->new;

    my $indexer = Lucy::Index::Indexer->new(
        index   => $folder,
        schema  => $schema,
        manager => $manager,
    );
    $indexer->add_doc( { content => 'foo' } );
    $indexer->commit;

    eval {
        $indexer = Lucy::Index::Indexer->new(
            manager => $other_manager,
            index   => $folder,
            schema  => $schema,
        );
    };
    like( $@, qr/index expects/i, "failed to get lock with wrong type" );
}

