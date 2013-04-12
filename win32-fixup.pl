#! e:/program files/perl/bin/perl.exe
#  version info can be found in 'configure.ac'

$glib_version = "2.36.0";
$major = 2;
$minor = 36;
$micro = 0;
$binary_age = 236;
$interface_age = 0;
$gettext_package = "glib20";
$current_minus_age = 0;
$glib_win32_static = "";
$data_root_dir = "F:/+GTK-SOURCES/gnu-win32/src/glib/gio/prefix";
$generic_include_folder = "F:\\+GTK-SOURCES\\gnu-windows\\include";
$generic_library_folder = "F:\\+GTK-SOURCES\\gnu-windows\\lib";
$generic_win32_library_folder = "F:\\+GTK-SOURCES\\gnu-windows\\lib\\win32";
$debug32_testsuite_folder = "..\\..\\..\\..\\..\\..\\gnu-win32\\TestApps\\Debug\\Mixbus\\bin";
$release32_testsuite_folder = "..\\..\\..\\..\\..\\..\\gnu-win32\\TestApps\\Release\\Mixbus\\bin";
$debug32_target_folder = "C:\\Program Files\\Mixbus\\bin";
$release32_target_folder = "E:\\Mixbus\\bin";
$target_sxs_folder = "F:\\+GTK-SOURCES\\gnu-windows\\include\\ardourext\\sys";
$gdbus_prefix = "gdbus-2.0";

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
	    s/\@datarootdir@/$data_root_dir/g;
	    s/\@GenericIncludeFolder@/$generic_include_folder/g;
	    s/\@GenericLibraryFolder@/$generic_library_folder/g;
	    s/\@GenericWin32LibraryFolder@/$generic_win32_library_folder/g;
	    s/\@Debug32TestSuiteFolder@/$debug32_testsuite_folder/g;
	    s/\@Release32TestSuiteFolder@/$release32_testsuite_folder/g;
	    s/\@Debug32TargetFolder@/$debug32_target_folder/g;
	    s/\@Release32TargetFolder@/$release32_target_folder/g;
	    s/\@TargetSxSFolder@/$target_sxs_folder/g;
	    s/\@prefix@/$gdbus_prefix/g;
	    print OUTPUT;
	}
}

process_file ("config.h.win32");
process_file ("glib/glibconfig.h.win32");
process_file ("gio/gdbus-2.0/codegen/config.py");

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