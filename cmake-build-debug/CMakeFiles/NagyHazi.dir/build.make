# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Programok\CLion 2020.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Programok\CLion 2020.2.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\beren\Desktop\NagyHazi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\beren\Desktop\NagyHazi\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/NagyHazi.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/NagyHazi.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/NagyHazi.dir/flags.make

CMakeFiles/NagyHazi.dir/main.c.obj: CMakeFiles/NagyHazi.dir/flags.make
CMakeFiles/NagyHazi.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\beren\Desktop\NagyHazi\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/NagyHazi.dir/main.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\NagyHazi.dir\main.c.obj   -c C:\Users\beren\Desktop\NagyHazi\main.c

CMakeFiles/NagyHazi.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/NagyHazi.dir/main.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\beren\Desktop\NagyHazi\main.c > CMakeFiles\NagyHazi.dir\main.c.i

CMakeFiles/NagyHazi.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/NagyHazi.dir/main.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\beren\Desktop\NagyHazi\main.c -o CMakeFiles\NagyHazi.dir\main.c.s

# Object files for target NagyHazi
NagyHazi_OBJECTS = \
"CMakeFiles/NagyHazi.dir/main.c.obj"

# External object files for target NagyHazi
NagyHazi_EXTERNAL_OBJECTS =

NagyHazi.exe: CMakeFiles/NagyHazi.dir/main.c.obj
NagyHazi.exe: CMakeFiles/NagyHazi.dir/build.make
NagyHazi.exe: CMakeFiles/NagyHazi.dir/linklibs.rsp
NagyHazi.exe: CMakeFiles/NagyHazi.dir/objects1.rsp
NagyHazi.exe: CMakeFiles/NagyHazi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\beren\Desktop\NagyHazi\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable NagyHazi.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\NagyHazi.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/NagyHazi.dir/build: NagyHazi.exe

.PHONY : CMakeFiles/NagyHazi.dir/build

CMakeFiles/NagyHazi.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\NagyHazi.dir\cmake_clean.cmake
.PHONY : CMakeFiles/NagyHazi.dir/clean

CMakeFiles/NagyHazi.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\beren\Desktop\NagyHazi C:\Users\beren\Desktop\NagyHazi C:\Users\beren\Desktop\NagyHazi\cmake-build-debug C:\Users\beren\Desktop\NagyHazi\cmake-build-debug C:\Users\beren\Desktop\NagyHazi\cmake-build-debug\CMakeFiles\NagyHazi.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NagyHazi.dir/depend

