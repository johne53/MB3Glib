#! e:/program files/perl/bin/perl.exe
#  version info can be found in 'configure.ac'

require "../local-paths.lib";

$glib_version = "2.45.7";
$major = 2;
$minor = 45;
$micro = 7;
$binary_age = 4507;
$interface_age = 0;
$gettext_package = "glib20";
$current_minus_age = 0;
$glib_win32_static = "";
$gdbus_prefix = "gdbus-2.0";
$exec_prefix = "lib";
$intl_libs = "-lintl";

sub process_file
{
        my $outfilename = shift;
	my $infilename = $outfilename . ".in";
	
	open (INPUT, "< $infilename") || exit 1;
	open (OUTPUT, "> $outfilename") || exit 1;
	
	while (<INPUT>) {
	    s/\@GLIB_VERSION@/$glib_version/g;
	    s/\@GLIB_MAJOR_VERSION\@/$major/g;
	    s/\@GLIB_MINOR_VERSION\@/$minor/g;
	    s/\@GLIB_MICRO_VERSION\@/$micro/g;
	    s/\@GLIB_INTERFACE_AGE\@/$interface_age/g;
	    s/\@GLIB_BINARY_AGE\@/$binary_age/g;
	    s/\@GETTEXT_PACKAGE\@/$gettext_package/g;
	    s/\@LT_CURRENT_MINUS_AGE@/$current_minus_age/g;
	    s/\@GLIB_WIN32_STATIC_COMPILATION_DEFINE@/$glib_win32_static/g;
	    s/\@PERL_PATH@/$perl_path/g;
	    s/\@datarootdir@/$data_root_dir/g;
	    s/\@GlibBuildRootFolder@/$glib_build_root_folder/g;
	    s/\@GenericIncludeFolder@/$generic_include_folder/g;
	    s/\@GenericLibraryFolder@/$generic_library_folder/g;
	    s/\@GenericWin32LibraryFolder@/$generic_win32_library_folder/g;
	    s/\@GenericWin32BinaryFolder@/$generic_win32_binary_folder/g;
	    s/\@Debug32TestSuiteFolder@/$debug32_testsuite_folder/g;
	    s/\@Release32TestSuiteFolder@/$release32_testsuite_folder/g;
	    s/\@Debug32TargetFolder@/$debug32_target_folder/g;
	    s/\@Release32TargetFolder@/$release32_target_folder/g;
	    s/\@TargetSxSFolder@/$target_sxs_folder/g;
	    s/\@prefix@/$gdbus_prefix/g;
	    s/\@exec_prefix@/$exec_prefix/g;
	    s/\@includedir@/$generic_include_folder/g;
	    s/\@libdir@/$generic_library_folder/g;
	    s/\@VERSION@/$glib_version/g;
	    s/\@INTLLIBS@/$intl_libs/g;
	    print OUTPUT;
	}
}

process_file ("config.h.win32");
process_file ("glib/glibconfig.h.win32");
process_file ("gobject/glib-mkenums");
process_file ("gio/gdbus-2.0/codegen/config.py");
process_file ("gio-windows-2.0.pc");
process_file ("gio-2.0.pc");
process_file ("glib-2.0.pc");
process_file ("gthread-2.0.pc");
process_file ("gmodule-2.0.pc");
process_file ("gobject-2.0.pc");

my $command=join(' ',@ARGV);
if ($command eq -buildall) {
	process_file ("gio/gio.rc");
	process_file ("glib/makefile.msc");
	process_file ("glib/glib.rc");
	process_file ("gmodule/makefile.msc");
	process_file ("gmodule/gmodule.rc");
	process_file ("gobject/makefile.msc");
	process_file ("gobject/gobject.rc");
	process_file ("gthread/makefile.msc");
	process_file ("gthread/gthread.rc");
	process_file ("msvc/glib.vsprops");
	process_file ("tests/makefile.msc");
}