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
CMAKE_COMMAND = C:\Users\Ilya\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\202.7660.37\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\Ilya\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\202.7660.37\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\ProgsProjects\OpenMP_tasks\task3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\ProgsProjects\OpenMP_tasks\task3\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/task3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/task3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/task3.dir/flags.make

CMakeFiles/task3.dir/main.c.obj: CMakeFiles/task3.dir/flags.make
CMakeFiles/task3.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\ProgsProjects\OpenMP_tasks\task3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/task3.dir/main.c.obj"
	E:\Games\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\task3.dir\main.c.obj   -c C:\ProgsProjects\OpenMP_tasks\task3\main.c

CMakeFiles/task3.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/task3.dir/main.c.i"
	E:\Games\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\ProgsProjects\OpenMP_tasks\task3\main.c > CMakeFiles\task3.dir\main.c.i

CMakeFiles/task3.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/task3.dir/main.c.s"
	E:\Games\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\ProgsProjects\OpenMP_tasks\task3\main.c -o CMakeFiles\task3.dir\main.c.s

# Object files for target task3
task3_OBJECTS = \
"CMakeFiles/task3.dir/main.c.obj"

# External object files for target task3
task3_EXTERNAL_OBJECTS =

task3.exe: CMakeFiles/task3.dir/main.c.obj
task3.exe: CMakeFiles/task3.dir/build.make
task3.exe: CMakeFiles/task3.dir/linklibs.rsp
task3.exe: CMakeFiles/task3.dir/objects1.rsp
task3.exe: CMakeFiles/task3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\ProgsProjects\OpenMP_tasks\task3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable task3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\task3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/task3.dir/build: task3.exe

.PHONY : CMakeFiles/task3.dir/build

CMakeFiles/task3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\task3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/task3.dir/clean

CMakeFiles/task3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\ProgsProjects\OpenMP_tasks\task3 C:\ProgsProjects\OpenMP_tasks\task3 C:\ProgsProjects\OpenMP_tasks\task3\cmake-build-debug C:\ProgsProjects\OpenMP_tasks\task3\cmake-build-debug C:\ProgsProjects\OpenMP_tasks\task3\cmake-build-debug\CMakeFiles\task3.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/task3.dir/depend

