/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package main

import "flag"
import "fmt"
import "io"
import "io/ioutil"
import "log"
import "os"
import "os/exec"
import "path"
import "runtime"

import "git-wip-us.apache.org/repos/asf/lucy-clownfish.git/compiler/go/cfc"

var packageName string = "git-wip-us.apache.org/repos/asf/lucy.git/go/lucy"
var cfPackageName string = "git-wip-us.apache.org/repos/asf/lucy-clownfish.git/runtime/go/clownfish"
var charmonizerC string = "../common/charmonizer.c"
var charmonizerEXE string = "charmonizer"
var charmonyH string = "charmony.h"
var buildDir string
var hostSrcDir string
var buildGO string
var configGO string
var cfbindGO string
var installedLibPath string

func init() {
	_, buildGO, _, _ = runtime.Caller(1)
	buildDir = path.Dir(buildGO)
	hostSrcDir = path.Join(buildDir, "../c/src")
	configGO = path.Join(buildDir, "lucy", "config.go")
	cfbindGO = path.Join(buildDir, "lucy", "cfbind.go")
	var err error
	installedLibPath, err = cfc.InstalledLibPath(packageName)
	if err != nil {
		log.Fatal(err)
	}
}

func main() {
	os.Chdir(buildDir)
	flag.Parse()
	action := "build"
	args := flag.Args()
	if len(args) > 0 {
		action = args[0]
	}
	switch action {
	case "build":
		build()
	case "clean":
		clean()
	case "test":
		test()
	case "install":
		install()
	default:
		log.Fatalf("Unrecognized action specified: %s", action)
	}
}

func current(orig, dest string) bool {

	destInfo, err := os.Stat(dest)
	if err != nil {
		if os.IsNotExist(err) {
			// If dest doesn't exist, we're not current.
			return false
		} else {
			log.Fatalf("Unexpected stat err: %s", err)
		}
	}

	// If source is newer than dest, we're not current.
	origInfo, err := os.Stat(orig)
	if err != nil {
		log.Fatalf("Unexpected: %s", err)
	}
	return origInfo.ModTime().Before(destInfo.ModTime())
}

func runCommand(name string, args ...string) {
	command := exec.Command(name, args...)
	command.Stdout = os.Stdout
	command.Stderr = os.Stderr
	err := command.Run()
	if err != nil {
		log.Fatal(err)
	}
}

func configure() {
	if !current(charmonizerC, charmonizerEXE) {
		runCommand("cc", "-o", charmonizerEXE, charmonizerC)
	}
	if !current(charmonizerEXE, charmonyH) {
		runCommand("./charmonizer", "--cc=cc", "--enable-c", "--enable-go",
			"--enable-makefile", "--host=go", "--", "-std=gnu99", "-O2")
	}
}

func runCFC() {
	hierarchy := cfc.NewHierarchy("autogen")
	hierarchy.AddSourceDir("../core")
	hierarchy.Build()
	autogenHeader := "Auto-generated by build.go.\n"
	coreBinding := cfc.NewBindCore(hierarchy, autogenHeader, "")
	modified := coreBinding.WriteAllModified(false)
	if modified {
		cfc.RegisterParcelPackage("Clownfish", cfPackageName)
		goBinding := cfc.NewBindGo(hierarchy)
		goBinding.SetHeader(autogenHeader)
		goBinding.SetSuppressInit(true)
		parcel := cfc.FetchParcel("Lucy")
		specClasses(parcel)
		packageDir := path.Join(buildDir, "lucy")
		goBinding.WriteBindings(parcel, packageDir)
		hierarchy.WriteLog()
	}
}

func specClasses(parcel *cfc.Parcel) {
	tokenBinding := cfc.NewGoClass(parcel, "Lucy::Analysis::Token")
	tokenBinding.SpecMethod("", "SetText(string)")
	tokenBinding.SpecMethod("", "GetText() string")
	tokenBinding.Register()

	analyzerBinding := cfc.NewGoClass(parcel, "Lucy::Analysis::Analyzer")
	analyzerBinding.SpecMethod("Split", "Split(string) []string")
	analyzerBinding.Register()

	indexerBinding := cfc.NewGoClass(parcel, "Lucy::Index::Indexer")
	indexerBinding.SpecMethod("", "Close() error")
	indexerBinding.SpecMethod("Add_Doc", "AddDoc(doc interface{}) error")
	indexerBinding.SpecMethod("Commit", "Commit() error")
	indexerBinding.SetSuppressStruct(true)
	indexerBinding.Register()

	schemaBinding := cfc.NewGoClass(parcel, "Lucy::Plan::Schema")
	schemaBinding.SpecMethod("All_Fields", "AllFields() []string")
	schemaBinding.Register()

	searcherBinding := cfc.NewGoClass(parcel, "Lucy::Search::Searcher")
	searcherBinding.SpecMethod("Hits",
		"Hits(query interface{}, offset uint32, numWanted uint32, sortSpec SortSpec) (Hits, error)")
	searcherBinding.SpecMethod("Close", "Close() error")
	searcherBinding.SpecMethod("", "ReadDoc(int32, interface{}) error")
	searcherBinding.Register()

	hitsBinding := cfc.NewGoClass(parcel, "Lucy::Search::Hits")
	hitsBinding.SpecMethod("Next", "Next(hit interface{}) bool")
	hitsBinding.SpecMethod("", "Error() error")
	hitsBinding.SetSuppressStruct(true)
	hitsBinding.Register()

	andQueryBinding := cfc.NewGoClass(parcel, "Lucy::Search::ANDQuery")
	andQueryBinding.SetSuppressCtor(true)
	andQueryBinding.Register()

	orQueryBinding := cfc.NewGoClass(parcel, "Lucy::Search::ORQuery")
	orQueryBinding.SetSuppressCtor(true)
	orQueryBinding.Register()

	andMatcherBinding := cfc.NewGoClass(parcel, "Lucy::Search::ANDMatcher")
	andMatcherBinding.SetSuppressCtor(true)
	andMatcherBinding.Register()

	orMatcherBinding := cfc.NewGoClass(parcel, "Lucy::Search::ORMatcher")
	orMatcherBinding.SetSuppressCtor(true)
	orMatcherBinding.Register()

	orScorerBinding := cfc.NewGoClass(parcel, "Lucy::Search::ORScorer")
	orScorerBinding.SetSuppressCtor(true)
	orScorerBinding.Register()

	seriesMatcherBinding := cfc.NewGoClass(parcel, "Lucy::Search::SeriesMatcher")
	seriesMatcherBinding.SetSuppressCtor(true)
	seriesMatcherBinding.Register()

	bitVecBinding := cfc.NewGoClass(parcel, "Lucy::Object::BitVector")
	bitVecBinding.SpecMethod("To_Array", "ToArray() []bool")
	bitVecBinding.Register()

	mockMatcherBinding := cfc.NewGoClass(parcel, "LucyX::Search::MockMatcher")
	mockMatcherBinding.SetSuppressCtor(true)
	mockMatcherBinding.Register()

	topDocsBinding := cfc.NewGoClass(parcel, "Lucy::Search::TopDocs")
	topDocsBinding.SetSuppressCtor(true)
	topDocsBinding.SpecMethod("Set_Match_Docs", "SetMatchDocs([]MatchDoc)")
	topDocsBinding.SpecMethod("Get_Match_Docs", "GetMatchDocs() []MatchDoc")
	topDocsBinding.Register()

	sortSpecBinding := cfc.NewGoClass(parcel, "Lucy::Search::SortSpec")
	sortSpecBinding.SetSuppressCtor(true)
	sortSpecBinding.SpecMethod("Get_Rules", "GetRules() []SortRule")
	sortSpecBinding.Register()

	sortCollBinding := cfc.NewGoClass(parcel, "Lucy::Search::Collector::SortCollector")
	sortCollBinding.SpecMethod("Pop_Match_Docs", "PopMatchDocs() []MatchDoc")
	sortCollBinding.Register()

	inStreamBinding := cfc.NewGoClass(parcel, "Lucy::Store::InStream")
	inStreamBinding.SpecMethod("Reopen", "Reopen(string, int64, int64) (InStream, error)")
	inStreamBinding.SpecMethod("Close", "Close() error")
	inStreamBinding.SpecMethod("Seek", "Seek(int64) error")
	inStreamBinding.SpecMethod("", "ReadBytes([]byte, int) error")
	inStreamBinding.SpecMethod("", "ReadString() (string, error)")
	inStreamBinding.SpecMethod("Read_I8", "ReadI8() (int8, error)")
	inStreamBinding.SpecMethod("Read_I32", "ReadI32() (int32, error)")
	inStreamBinding.SpecMethod("Read_I64", "ReadI64() (int64, error)")
	inStreamBinding.SpecMethod("Read_U8", "ReadU8() (uint8, error)")
	inStreamBinding.SpecMethod("Read_U32", "ReadU32() (uint32, error)")
	inStreamBinding.SpecMethod("Read_U64", "ReadU64() (uint64, error)")
	inStreamBinding.SpecMethod("Read_C32", "ReadC32() (uint32, error)")
	inStreamBinding.SpecMethod("Read_C64", "ReadC64() (uint64, error)")
	inStreamBinding.SpecMethod("Read_F32", "ReadF32() (float32, error)")
	inStreamBinding.SpecMethod("Read_F64", "ReadF64() (float64, error)")
	inStreamBinding.Register()

	outStreamBinding := cfc.NewGoClass(parcel, "Lucy::Store::OutStream")
	outStreamBinding.SpecMethod("Close", "Close() error")
	outStreamBinding.SpecMethod("Grow", "Grow(int64) error")
	outStreamBinding.SpecMethod("Align", "Align(int64) error")
	outStreamBinding.SpecMethod("", "WriteBytes([]byte, int) error")
	outStreamBinding.SpecMethod("", "WriteString(string) error")
	outStreamBinding.SpecMethod("Write_I8", "WriteI8(int8) error")
	outStreamBinding.SpecMethod("Write_I32", "WriteI32(int32) error")
	outStreamBinding.SpecMethod("Write_I64", "WriteI64(int64) error")
	outStreamBinding.SpecMethod("Write_U8", "WriteU8(uint8) error")
	outStreamBinding.SpecMethod("Write_U32", "WriteU32(uint32) error")
	outStreamBinding.SpecMethod("Write_U64", "WriteU64(uint64) error")
	outStreamBinding.SpecMethod("Write_C32", "WriteC32(uint32) error")
	outStreamBinding.SpecMethod("Write_C64", "WriteC64(uint64) error")
	outStreamBinding.SpecMethod("Write_F32", "WriteF32(float32) error")
	outStreamBinding.SpecMethod("Write_F64", "WriteF64(float64) error")
	outStreamBinding.SpecMethod("Absorb", "Absorb(InStream) error")
	outStreamBinding.Register()

	folderBinding := cfc.NewGoClass(parcel, "Lucy::Store::Folder")
	folderBinding.SpecMethod("Initialize", "Initialize() error")
	folderBinding.SpecMethod("Open_Out", "OpenOut(string) (OutStream, error)")
	folderBinding.SpecMethod("Open_In", "OpenIn(string) (InStream, error)")
	folderBinding.SpecMethod("Open_FileHandle", "OpenFileHandle(string, uint32) (FileHandle, error)")
	folderBinding.SpecMethod("Open_Dir", "OpenDir(string) (DirHandle, error)")
	folderBinding.SpecMethod("MkDir", "MkDir(string) error")
	folderBinding.SpecMethod("List", "List(string) ([]string, error)")
	folderBinding.SpecMethod("List_R", "ListR(string) ([]string, error)")
	folderBinding.SpecMethod("Rename", "Rename(string, string) error")
	folderBinding.SpecMethod("Hard_Link", "HardLink(string, string) error")
	folderBinding.SpecMethod("Slurp_File", "SlurpFile(string) ([]byte, error)")
	folderBinding.SpecMethod("Consolidate", "Consolidate(string) error")
	folderBinding.SpecMethod("Local_Open_In", "LocalOpenIn(string) (InStream, error)")
	folderBinding.SpecMethod("Local_Open_FileHandle", "LocalOpenFileHandle(string, uint32) (FileHandle, error)")
	folderBinding.SpecMethod("Local_Open_Dir", "LocalOpenDir() (DirHandle, error)")
	folderBinding.SpecMethod("Local_MkDir", "LocalMkDir(string) error")
	folderBinding.Register()

	fhBinding := cfc.NewGoClass(parcel, "Lucy::Store::FileHandle")
	fhBinding.SpecMethod("", "Write([]byte, int) error")
	fhBinding.SpecMethod("", "Read([]byte, int64, int) error")
	fhBinding.SpecMethod("Window", "Window(FileWindow, int64, int64) error")
	fhBinding.SpecMethod("Release_Window", "ReleaseWindow(FileWindow) error")
	fhBinding.SpecMethod("Grow", "Grow(int64) error")
	fhBinding.SpecMethod("Close", "Close() error")
	fhBinding.Register()

	dhBinding := cfc.NewGoClass(parcel, "Lucy::Store::DirHandle")
	dhBinding.SpecMethod("Close", "Close() error")
	dhBinding.Register()

	lockBinding := cfc.NewGoClass(parcel, "Lucy::Store::Lock")
	lockBinding.SpecMethod("Request", "Request() error")
	lockBinding.SpecMethod("Obtain", "Obtain() error")
	lockBinding.SpecMethod("Release", "Release() error")
	lockBinding.SpecMethod("Clear_Stale", "ClearStale() error")
	lockBinding.Register()

	cfWriterBinding := cfc.NewGoClass(parcel, "Lucy::Store::CompoundFileWriter")
	cfWriterBinding.SpecMethod("Consolidate", "Consolidate() error")
	cfWriterBinding.Register()
}

func build() {
	configure()
	runCFC()
	runCommand("make", "-j", "static")
	writeConfigGO()
	runCommand("go", "build", packageName)
}

func test() {
	build()
	runCommand("go", "test", packageName)
}

func copyFile(source, dest string) {
	sourceFH, err := os.Open(source)
	if err != nil {
		log.Fatal(err)
	}
	defer sourceFH.Close()
	destFH, err := os.Create(dest)
	if err != nil {
		log.Fatal(err)
	}
	defer destFH.Close()
	_, err = io.Copy(destFH, sourceFH)
	if err != nil {
		log.Fatalf("io.Copy from %s to %s failed: %s", source, dest, err)
	}
}

func installStaticLib() {
	tempLibPath := path.Join(buildDir, "liblucy.a")
	destDir := path.Dir(installedLibPath)
	if _, err := os.Stat(destDir); os.IsNotExist(err) {
		err = os.MkdirAll(destDir, 0755)
		if err != nil {
			log.Fatalf("Can't create dir '%s': %s", destDir, err)
		}
	}
	os.Remove(installedLibPath)
	copyFile(tempLibPath, installedLibPath)
}

func install() {
	build()
	runCommand("go", "install", packageName)
	installStaticLib()
}

func writeConfigGO() {
	if current(buildGO, configGO) {
		return
	}
	installedLibDir := path.Dir(installedLibPath)
	cfLibPath, err := cfc.InstalledLibPath(cfPackageName)
	if err != nil {
		log.Fatal(err)
	}
	cfLibDir := path.Dir(cfLibPath)
	content := fmt.Sprintf(
		"// Auto-generated by build.go, specifying absolute path to static lib.\n"+
			"package lucy\n"+
			"// #cgo CFLAGS: -I%s/../core\n"+
			"// #cgo CFLAGS: -I%s\n"+
			"// #cgo CFLAGS: -I%s/autogen/include\n"+
			"// #cgo LDFLAGS: -L%s\n"+
			"// #cgo LDFLAGS: -L%s\n"+
			"// #cgo LDFLAGS: -L%s\n"+
			"// #cgo LDFLAGS: -llucy\n"+
			"// #cgo LDFLAGS: -lclownfish\n"+
			"import \"C\"\n",
		buildDir, buildDir, buildDir, buildDir, installedLibDir, cfLibDir)
	ioutil.WriteFile(configGO, []byte(content), 0666)
}

func clean() {
	fmt.Println("Cleaning")
	if _, err := os.Stat("Makefile"); !os.IsNotExist(err) {
		runCommand("make", "clean")
	}
	files := []string{charmonizerEXE, "charmony.h", "Makefile", configGO, cfbindGO}
	for _, file := range files {
		err := os.Remove(file)
		if err == nil {
			fmt.Println("Removing", file)
		} else if !os.IsNotExist(err) {
			log.Fatal(err)
		}
	}
}
