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
include CMakeFiles/mysqlmgr.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mysqlmgr.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mysqlmgr.dir/flags.make

CMakeFiles/mysqlmgr.dir/mysqlmgr/MyDB.cpp.o: CMakeFiles/mysqlmgr.dir/flags.make
CMakeFiles/mysqlmgr.dir/mysqlmgr/MyDB.cpp.o: mysqlmgr/MyDB.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hao/Downloads/VEN_CPP_source/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mysqlmgr.dir/mysqlmgr/MyDB.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mysqlmgr.dir/mysqlmgr/MyDB.cpp.o -c /home/hao/Downloads/VEN_CPP_source/mysqlmgr/MyDB.cpp

CMakeFiles/mysqlmgr.dir/mysqlmgr/MyDB.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mysqlmgr.dir/mysqlmgr/MyDB.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hao/Downloads/VEN_CPP_source/mysqlmgr/MyDB.cpp > CMakeFiles/mysqlmgr.dir/mysqlmgr/MyDB.cpp.i

CMakeFiles/mysqlmgr.dir/mysqlmgr/MyDB.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mysqlmgr.dir/mysqlmgr/MyDB.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hao/Downloads/VEN_CPP_source/mysqlmgr/MyDB.cpp -o CMakeFiles/mysqlmgr.dir/mysqlmgr/MyDB.cpp.s

CMakeFiles/mysqlmgr.dir/mysqlmgr/MyDB.cpp.o.requires:

.PHONY : CMakeFiles/mysqlmgr.dir/mysqlmgr/MyDB.cpp.o.requires

CMakeFiles/mysqlmgr.dir/mysqlmgr/MyDB.cpp.o.provides: CMakeFiles/mysqlmgr.dir/mysqlmgr/MyDB.cpp.o.requires
	$(MAKE) -f CMakeFiles/mysqlmgr.dir/build.make CMakeFiles/mysqlmgr.dir/mysqlmgr/MyDB.cpp.o.provides.build
.PHONY : CMakeFiles/mysqlmgr.dir/mysqlmgr/MyDB.cpp.o.provides

CMakeFiles/mysqlmgr.dir/mysqlmgr/MyDB.cpp.o.provides.build: CMakeFiles/mysqlmgr.dir/mysqlmgr/MyDB.cpp.o


# Object files for target mysqlmgr
mysqlmgr_OBJECTS = \
"CMakeFiles/mysqlmgr.dir/mysqlmgr/MyDB.cpp.o"

# External object files for target mysqlmgr
mysqlmgr_EXTERNAL_OBJECTS =

libmysqlmgr.so: CMakeFiles/mysqlmgr.dir/mysqlmgr/MyDB.cpp.o
libmysqlmgr.so: CMakeFiles/mysqlmgr.dir/build.make
libmysqlmgr.so: libmysqlclient/libmysqlclient.a
libmysqlmgr.so: CMakeFiles/mysqlmgr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hao/Downloads/VEN_CPP_source/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libmysqlmgr.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mysqlmgr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mysqlmgr.dir/build: libmysqlmgr.so

.PHONY : CMakeFiles/mysqlmgr.dir/build

# Object files for target mysqlmgr
mysqlmgr_OBJECTS = \
"CMakeFiles/mysqlmgr.dir/mysqlmgr/MyDB.cpp.o"

# External object files for target mysqlmgr
mysqlmgr_EXTERNAL_OBJECTS =

CMakeFiles/CMakeRelink.dir/libmysqlmgr.so: CMakeFiles/mysqlmgr.dir/mysqlmgr/MyDB.cpp.o
CMakeFiles/CMakeRelink.dir/libmysqlmgr.so: CMakeFiles/mysqlmgr.dir/build.make
CMakeFiles/CMakeRelink.dir/libmysqlmgr.so: libmysqlclient/libmysqlclient.a
CMakeFiles/CMakeRelink.dir/libmysqlmgr.so: CMakeFiles/mysqlmgr.dir/relink.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hao/Downloads/VEN_CPP_source/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library CMakeFiles/CMakeRelink.dir/libmysqlmgr.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mysqlmgr.dir/relink.txt --verbose=$(VERBOSE)

# Rule to relink during preinstall.
CMakeFiles/mysqlmgr.dir/preinstall: CMakeFiles/CMakeRelink.dir/libmysqlmgr.so

.PHONY : CMakeFiles/mysqlmgr.dir/preinstall

CMakeFiles/mysqlmgr.dir/requires: CMakeFiles/mysqlmgr.dir/mysqlmgr/MyDB.cpp.o.requires

.PHONY : CMakeFiles/mysqlmgr.dir/requires

CMakeFiles/mysqlmgr.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mysqlmgr.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mysqlmgr.dir/clean

CMakeFiles/mysqlmgr.dir/depend:
	cd /home/hao/Downloads/VEN_CPP_source && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hao/Downloads/VEN_CPP_source /home/hao/Downloads/VEN_CPP_source /home/hao/Downloads/VEN_CPP_source /home/hao/Downloads/VEN_CPP_source /home/hao/Downloads/VEN_CPP_source/CMakeFiles/mysqlmgr.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mysqlmgr.dir/depend
