# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gsi/QA_TOOL/QA_tool_Hades/aamcc_to_mcini

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gsi/QA_TOOL/QA_tool_Hades/aamcc_to_mcini/build

# Include any dependencies generated for this target.
include CMakeFiles/JAMReader.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/JAMReader.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/JAMReader.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/JAMReader.dir/flags.make

CMakeFiles/JAMReader.dir/src/jam/JAMRunInfo.cxx.o: CMakeFiles/JAMReader.dir/flags.make
CMakeFiles/JAMReader.dir/src/jam/JAMRunInfo.cxx.o: ../src/jam/JAMRunInfo.cxx
CMakeFiles/JAMReader.dir/src/jam/JAMRunInfo.cxx.o: CMakeFiles/JAMReader.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gsi/QA_TOOL/QA_tool_Hades/aamcc_to_mcini/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/JAMReader.dir/src/jam/JAMRunInfo.cxx.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/JAMReader.dir/src/jam/JAMRunInfo.cxx.o -MF CMakeFiles/JAMReader.dir/src/jam/JAMRunInfo.cxx.o.d -o CMakeFiles/JAMReader.dir/src/jam/JAMRunInfo.cxx.o -c /home/gsi/QA_TOOL/QA_tool_Hades/aamcc_to_mcini/src/jam/JAMRunInfo.cxx

CMakeFiles/JAMReader.dir/src/jam/JAMRunInfo.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/JAMReader.dir/src/jam/JAMRunInfo.cxx.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gsi/QA_TOOL/QA_tool_Hades/aamcc_to_mcini/src/jam/JAMRunInfo.cxx > CMakeFiles/JAMReader.dir/src/jam/JAMRunInfo.cxx.i

CMakeFiles/JAMReader.dir/src/jam/JAMRunInfo.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/JAMReader.dir/src/jam/JAMRunInfo.cxx.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gsi/QA_TOOL/QA_tool_Hades/aamcc_to_mcini/src/jam/JAMRunInfo.cxx -o CMakeFiles/JAMReader.dir/src/jam/JAMRunInfo.cxx.s

CMakeFiles/JAMReader.dir/src/jam/JAMReader.cxx.o: CMakeFiles/JAMReader.dir/flags.make
CMakeFiles/JAMReader.dir/src/jam/JAMReader.cxx.o: ../src/jam/JAMReader.cxx
CMakeFiles/JAMReader.dir/src/jam/JAMReader.cxx.o: CMakeFiles/JAMReader.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gsi/QA_TOOL/QA_tool_Hades/aamcc_to_mcini/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/JAMReader.dir/src/jam/JAMReader.cxx.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/JAMReader.dir/src/jam/JAMReader.cxx.o -MF CMakeFiles/JAMReader.dir/src/jam/JAMReader.cxx.o.d -o CMakeFiles/JAMReader.dir/src/jam/JAMReader.cxx.o -c /home/gsi/QA_TOOL/QA_tool_Hades/aamcc_to_mcini/src/jam/JAMReader.cxx

CMakeFiles/JAMReader.dir/src/jam/JAMReader.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/JAMReader.dir/src/jam/JAMReader.cxx.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gsi/QA_TOOL/QA_tool_Hades/aamcc_to_mcini/src/jam/JAMReader.cxx > CMakeFiles/JAMReader.dir/src/jam/JAMReader.cxx.i

CMakeFiles/JAMReader.dir/src/jam/JAMReader.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/JAMReader.dir/src/jam/JAMReader.cxx.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gsi/QA_TOOL/QA_tool_Hades/aamcc_to_mcini/src/jam/JAMReader.cxx -o CMakeFiles/JAMReader.dir/src/jam/JAMReader.cxx.s

# Object files for target JAMReader
JAMReader_OBJECTS = \
"CMakeFiles/JAMReader.dir/src/jam/JAMRunInfo.cxx.o" \
"CMakeFiles/JAMReader.dir/src/jam/JAMReader.cxx.o"

# External object files for target JAMReader
JAMReader_EXTERNAL_OBJECTS =

JAMReader: CMakeFiles/JAMReader.dir/src/jam/JAMRunInfo.cxx.o
JAMReader: CMakeFiles/JAMReader.dir/src/jam/JAMReader.cxx.o
JAMReader: CMakeFiles/JAMReader.dir/build.make
JAMReader: libMcIniData.so
JAMReader: /home/gsi/ROOT/root_6_20/root/lib/libCore.so
JAMReader: /home/gsi/ROOT/root_6_20/root/lib/libImt.so
JAMReader: /home/gsi/ROOT/root_6_20/root/lib/libRIO.so
JAMReader: /home/gsi/ROOT/root_6_20/root/lib/libNet.so
JAMReader: /home/gsi/ROOT/root_6_20/root/lib/libHist.so
JAMReader: /home/gsi/ROOT/root_6_20/root/lib/libGraf.so
JAMReader: /home/gsi/ROOT/root_6_20/root/lib/libGraf3d.so
JAMReader: /home/gsi/ROOT/root_6_20/root/lib/libGpad.so
JAMReader: /home/gsi/ROOT/root_6_20/root/lib/libROOTDataFrame.so
JAMReader: /home/gsi/ROOT/root_6_20/root/lib/libTree.so
JAMReader: /home/gsi/ROOT/root_6_20/root/lib/libTreePlayer.so
JAMReader: /home/gsi/ROOT/root_6_20/root/lib/libRint.so
JAMReader: /home/gsi/ROOT/root_6_20/root/lib/libPostscript.so
JAMReader: /home/gsi/ROOT/root_6_20/root/lib/libMatrix.so
JAMReader: /home/gsi/ROOT/root_6_20/root/lib/libPhysics.so
JAMReader: /home/gsi/ROOT/root_6_20/root/lib/libMathCore.so
JAMReader: /home/gsi/ROOT/root_6_20/root/lib/libThread.so
JAMReader: /home/gsi/ROOT/root_6_20/root/lib/libMultiProc.so
JAMReader: CMakeFiles/JAMReader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gsi/QA_TOOL/QA_tool_Hades/aamcc_to_mcini/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable JAMReader"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/JAMReader.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/JAMReader.dir/build: JAMReader
.PHONY : CMakeFiles/JAMReader.dir/build

CMakeFiles/JAMReader.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/JAMReader.dir/cmake_clean.cmake
.PHONY : CMakeFiles/JAMReader.dir/clean

CMakeFiles/JAMReader.dir/depend:
	cd /home/gsi/QA_TOOL/QA_tool_Hades/aamcc_to_mcini/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gsi/QA_TOOL/QA_tool_Hades/aamcc_to_mcini /home/gsi/QA_TOOL/QA_tool_Hades/aamcc_to_mcini /home/gsi/QA_TOOL/QA_tool_Hades/aamcc_to_mcini/build /home/gsi/QA_TOOL/QA_tool_Hades/aamcc_to_mcini/build /home/gsi/QA_TOOL/QA_tool_Hades/aamcc_to_mcini/build/CMakeFiles/JAMReader.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/JAMReader.dir/depend

