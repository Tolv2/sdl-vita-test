# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/four/lp/sdl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/four/lp/sdl/build

# Utility rule file for SDL_Test.vpk-vpk.

# Include any custom commands dependencies for this target.
include CMakeFiles/SDL_Test.vpk-vpk.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SDL_Test.vpk-vpk.dir/progress.make

CMakeFiles/SDL_Test.vpk-vpk: SDL_Test.vpk.out
	/usr/bin/cmake -E copy /home/four/lp/sdl/build/SDL_Test.vpk.out SDL_Test.vpk

SDL_Test.vpk.out: SDL_Test.vpk_param.sfo
SDL_Test.vpk.out: eboot.bin
SDL_Test.vpk.out: /home/four/lp/sdl/assets/png
SDL_Test.vpk.out: /home/four/lp/sdl/assets/ttf
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/four/lp/sdl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building vpk SDL_Test.vpk"
	/usr/local/vitasdk/bin/vita-pack-vpk -a /home/four/lp/sdl/assets/png=assets/png -a /home/four/lp/sdl/assets/ttf=assets/ttf -s /home/four/lp/sdl/build/SDL_Test.vpk_param.sfo -b /home/four/lp/sdl/build/eboot.bin /home/four/lp/sdl/build/SDL_Test.vpk.out

SDL_Test.vpk_param.sfo: eboot.bin
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/four/lp/sdl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating param.sfo for SDL_Test.vpk"
	/usr/local/vitasdk/bin/vita-mksfoex -s APP_VER=00.00 -s TITLE_ID=BRUH00003 "Bruh moment #3" /home/four/lp/sdl/build/SDL_Test.vpk_param.sfo

SDL_Test.vpk-vpk: CMakeFiles/SDL_Test.vpk-vpk
SDL_Test.vpk-vpk: SDL_Test.vpk.out
SDL_Test.vpk-vpk: SDL_Test.vpk_param.sfo
SDL_Test.vpk-vpk: CMakeFiles/SDL_Test.vpk-vpk.dir/build.make
.PHONY : SDL_Test.vpk-vpk

# Rule to build all files generated by this target.
CMakeFiles/SDL_Test.vpk-vpk.dir/build: SDL_Test.vpk-vpk
.PHONY : CMakeFiles/SDL_Test.vpk-vpk.dir/build

CMakeFiles/SDL_Test.vpk-vpk.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SDL_Test.vpk-vpk.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SDL_Test.vpk-vpk.dir/clean

CMakeFiles/SDL_Test.vpk-vpk.dir/depend:
	cd /home/four/lp/sdl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/four/lp/sdl /home/four/lp/sdl /home/four/lp/sdl/build /home/four/lp/sdl/build /home/four/lp/sdl/build/CMakeFiles/SDL_Test.vpk-vpk.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/SDL_Test.vpk-vpk.dir/depend

