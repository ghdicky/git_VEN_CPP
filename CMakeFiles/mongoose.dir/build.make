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
include CMakeFiles/mongoose.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mongoose.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mongoose.dir/flags.make

CMakeFiles/mongoose.dir/mongoose/Server.cpp.o: CMakeFiles/mongoose.dir/flags.make
CMakeFiles/mongoose.dir/mongoose/Server.cpp.o: mongoose/Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hao/Downloads/VEN_CPP_source/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mongoose.dir/mongoose/Server.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mongoose.dir/mongoose/Server.cpp.o -c /home/hao/Downloads/VEN_CPP_source/mongoose/Server.cpp

CMakeFiles/mongoose.dir/mongoose/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mongoose.dir/mongoose/Server.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hao/Downloads/VEN_CPP_source/mongoose/Server.cpp > CMakeFiles/mongoose.dir/mongoose/Server.cpp.i

CMakeFiles/mongoose.dir/mongoose/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mongoose.dir/mongoose/Server.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hao/Downloads/VEN_CPP_source/mongoose/Server.cpp -o CMakeFiles/mongoose.dir/mongoose/Server.cpp.s

CMakeFiles/mongoose.dir/mongoose/Server.cpp.o.requires:

.PHONY : CMakeFiles/mongoose.dir/mongoose/Server.cpp.o.requires

CMakeFiles/mongoose.dir/mongoose/Server.cpp.o.provides: CMakeFiles/mongoose.dir/mongoose/Server.cpp.o.requires
	$(MAKE) -f CMakeFiles/mongoose.dir/build.make CMakeFiles/mongoose.dir/mongoose/Server.cpp.o.provides.build
.PHONY : CMakeFiles/mongoose.dir/mongoose/Server.cpp.o.provides

CMakeFiles/mongoose.dir/mongoose/Server.cpp.o.provides.build: CMakeFiles/mongoose.dir/mongoose/Server.cpp.o


CMakeFiles/mongoose.dir/mongoose/WebController.cpp.o: CMakeFiles/mongoose.dir/flags.make
CMakeFiles/mongoose.dir/mongoose/WebController.cpp.o: mongoose/WebController.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hao/Downloads/VEN_CPP_source/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mongoose.dir/mongoose/WebController.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mongoose.dir/mongoose/WebController.cpp.o -c /home/hao/Downloads/VEN_CPP_source/mongoose/WebController.cpp

CMakeFiles/mongoose.dir/mongoose/WebController.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mongoose.dir/mongoose/WebController.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hao/Downloads/VEN_CPP_source/mongoose/WebController.cpp > CMakeFiles/mongoose.dir/mongoose/WebController.cpp.i

CMakeFiles/mongoose.dir/mongoose/WebController.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mongoose.dir/mongoose/WebController.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hao/Downloads/VEN_CPP_source/mongoose/WebController.cpp -o CMakeFiles/mongoose.dir/mongoose/WebController.cpp.s

CMakeFiles/mongoose.dir/mongoose/WebController.cpp.o.requires:

.PHONY : CMakeFiles/mongoose.dir/mongoose/WebController.cpp.o.requires

CMakeFiles/mongoose.dir/mongoose/WebController.cpp.o.provides: CMakeFiles/mongoose.dir/mongoose/WebController.cpp.o.requires
	$(MAKE) -f CMakeFiles/mongoose.dir/build.make CMakeFiles/mongoose.dir/mongoose/WebController.cpp.o.provides.build
.PHONY : CMakeFiles/mongoose.dir/mongoose/WebController.cpp.o.provides

CMakeFiles/mongoose.dir/mongoose/WebController.cpp.o.provides.build: CMakeFiles/mongoose.dir/mongoose/WebController.cpp.o


# Object files for target mongoose
mongoose_OBJECTS = \
"CMakeFiles/mongoose.dir/mongoose/Server.cpp.o" \
"CMakeFiles/mongoose.dir/mongoose/WebController.cpp.o"

# External object files for target mongoose
mongoose_EXTERNAL_OBJECTS =

libmongoose.a: CMakeFiles/mongoose.dir/mongoose/Server.cpp.o
libmongoose.a: CMakeFiles/mongoose.dir/mongoose/WebController.cpp.o
libmongoose.a: CMakeFiles/mongoose.dir/build.make
libmongoose.a: CMakeFiles/mongoose.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hao/Downloads/VEN_CPP_source/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libmongoose.a"
	$(CMAKE_COMMAND) -P CMakeFiles/mongoose.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mongoose.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mongoose.dir/build: libmongoose.a

.PHONY : CMakeFiles/mongoose.dir/build

CMakeFiles/mongoose.dir/requires: CMakeFiles/mongoose.dir/mongoose/Server.cpp.o.requires
CMakeFiles/mongoose.dir/requires: CMakeFiles/mongoose.dir/mongoose/WebController.cpp.o.requires

.PHONY : CMakeFiles/mongoose.dir/requires

CMakeFiles/mongoose.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mongoose.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mongoose.dir/clean

CMakeFiles/mongoose.dir/depend:
	cd /home/hao/Downloads/VEN_CPP_source && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hao/Downloads/VEN_CPP_source /home/hao/Downloads/VEN_CPP_source /home/hao/Downloads/VEN_CPP_source /home/hao/Downloads/VEN_CPP_source /home/hao/Downloads/VEN_CPP_source/CMakeFiles/mongoose.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mongoose.dir/depend
