# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hao/Downloads/VEN_CPP_source

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hao/Downloads/VEN_CPP_source

# Include any dependencies generated for this target.
include CMakeFiles/dbwrapper.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/dbwrapper.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dbwrapper.dir/flags.make

CMakeFiles/dbwrapper.dir/mysqlwrapper/mysqlwrapper.cpp.o: CMakeFiles/dbwrapper.dir/flags.make
CMakeFiles/dbwrapper.dir/mysqlwrapper/mysqlwrapper.cpp.o: mysqlwrapper/mysqlwrapper.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hao/Downloads/VEN_CPP_source/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/dbwrapper.dir/mysqlwrapper/mysqlwrapper.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/dbwrapper.dir/mysqlwrapper/mysqlwrapper.cpp.o -c /home/hao/Downloads/VEN_CPP_source/mysqlwrapper/mysqlwrapper.cpp

CMakeFiles/dbwrapper.dir/mysqlwrapper/mysqlwrapper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dbwrapper.dir/mysqlwrapper/mysqlwrapper.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hao/Downloads/VEN_CPP_source/mysqlwrapper/mysqlwrapper.cpp > CMakeFiles/dbwrapper.dir/mysqlwrapper/mysqlwrapper.cpp.i

CMakeFiles/dbwrapper.dir/mysqlwrapper/mysqlwrapper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dbwrapper.dir/mysqlwrapper/mysqlwrapper.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hao/Downloads/VEN_CPP_source/mysqlwrapper/mysqlwrapper.cpp -o CMakeFiles/dbwrapper.dir/mysqlwrapper/mysqlwrapper.cpp.s

CMakeFiles/dbwrapper.dir/mysqlwrapper/mysqlwrapper.cpp.o.requires:

.PHONY : CMakeFiles/dbwrapper.dir/mysqlwrapper/mysqlwrapper.cpp.o.requires

CMakeFiles/dbwrapper.dir/mysqlwrapper/mysqlwrapper.cpp.o.provides: CMakeFiles/dbwrapper.dir/mysqlwrapper/mysqlwrapper.cpp.o.requires
	$(MAKE) -f CMakeFiles/dbwrapper.dir/build.make CMakeFiles/dbwrapper.dir/mysqlwrapper/mysqlwrapper.cpp.o.provides.build
.PHONY : CMakeFiles/dbwrapper.dir/mysqlwrapper/mysqlwrapper.cpp.o.provides

CMakeFiles/dbwrapper.dir/mysqlwrapper/mysqlwrapper.cpp.o.provides.build: CMakeFiles/dbwrapper.dir/mysqlwrapper/mysqlwrapper.cpp.o


# Object files for target dbwrapper
dbwrapper_OBJECTS = \
"CMakeFiles/dbwrapper.dir/mysqlwrapper/mysqlwrapper.cpp.o"

# External object files for target dbwrapper
dbwrapper_EXTERNAL_OBJECTS =

libdbwrapper.so: CMakeFiles/dbwrapper.dir/mysqlwrapper/mysqlwrapper.cpp.o
libdbwrapper.so: CMakeFiles/dbwrapper.dir/build.make
libdbwrapper.so: libmysqlmgr.so
libdbwrapper.so: libmysqlclient/libmysqlclient.a
libdbwrapper.so: CMakeFiles/dbwrapper.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hao/Downloads/VEN_CPP_source/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libdbwrapper.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dbwrapper.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dbwrapper.dir/build: libdbwrapper.so

.PHONY : CMakeFiles/dbwrapper.dir/build

# Object files for target dbwrapper
dbwrapper_OBJECTS = \
"CMakeFiles/dbwrapper.dir/mysqlwrapper/mysqlwrapper.cpp.o"

# External object files for target dbwrapper
dbwrapper_EXTERNAL_OBJECTS =

CMakeFiles/CMakeRelink.dir/libdbwrapper.so: CMakeFiles/dbwrapper.dir/mysqlwrapper/mysqlwrapper.cpp.o
CMakeFiles/CMakeRelink.dir/libdbwrapper.so: CMakeFiles/dbwrapper.dir/build.make
CMakeFiles/CMakeRelink.dir/libdbwrapper.so: libmysqlmgr.so
CMakeFiles/CMakeRelink.dir/libdbwrapper.so: libmysqlclient/libmysqlclient.a
CMakeFiles/CMakeRelink.dir/libdbwrapper.so: CMakeFiles/dbwrapper.dir/relink.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hao/Downloads/VEN_CPP_source/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library CMakeFiles/CMakeRelink.dir/libdbwrapper.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dbwrapper.dir/relink.txt --verbose=$(VERBOSE)

# Rule to relink during preinstall.
CMakeFiles/dbwrapper.dir/preinstall: CMakeFiles/CMakeRelink.dir/libdbwrapper.so

.PHONY : CMakeFiles/dbwrapper.dir/preinstall

CMakeFiles/dbwrapper.dir/requires: CMakeFiles/dbwrapper.dir/mysqlwrapper/mysqlwrapper.cpp.o.requires

.PHONY : CMakeFiles/dbwrapper.dir/requires

CMakeFiles/dbwrapper.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dbwrapper.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dbwrapper.dir/clean

CMakeFiles/dbwrapper.dir/depend:
	cd /home/hao/Downloads/VEN_CPP_source && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hao/Downloads/VEN_CPP_source /home/hao/Downloads/VEN_CPP_source /home/hao/Downloads/VEN_CPP_source /home/hao/Downloads/VEN_CPP_source /home/hao/Downloads/VEN_CPP_source/CMakeFiles/dbwrapper.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dbwrapper.dir/depend
