# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/hyreos/Documentos/projects/emugb

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hyreos/Documentos/projects/emugb

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/hyreos/Documentos/projects/emugb/CMakeFiles /home/hyreos/Documentos/projects/emugb/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/hyreos/Documentos/projects/emugb/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named moegb

# Build rule for target.
moegb: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 moegb
.PHONY : moegb

# fast build rule for target.
moegb/fast:
	$(MAKE) -f CMakeFiles/moegb.dir/build.make CMakeFiles/moegb.dir/build
.PHONY : moegb/fast

Bootstrap.o: Bootstrap.cpp.o

.PHONY : Bootstrap.o

# target to build an object file
Bootstrap.cpp.o:
	$(MAKE) -f CMakeFiles/moegb.dir/build.make CMakeFiles/moegb.dir/Bootstrap.cpp.o
.PHONY : Bootstrap.cpp.o

Bootstrap.i: Bootstrap.cpp.i

.PHONY : Bootstrap.i

# target to preprocess a source file
Bootstrap.cpp.i:
	$(MAKE) -f CMakeFiles/moegb.dir/build.make CMakeFiles/moegb.dir/Bootstrap.cpp.i
.PHONY : Bootstrap.cpp.i

Bootstrap.s: Bootstrap.cpp.s

.PHONY : Bootstrap.s

# target to generate assembly for a file
Bootstrap.cpp.s:
	$(MAKE) -f CMakeFiles/moegb.dir/build.make CMakeFiles/moegb.dir/Bootstrap.cpp.s
.PHONY : Bootstrap.cpp.s

Cartrigbe.o: Cartrigbe.cpp.o

.PHONY : Cartrigbe.o

# target to build an object file
Cartrigbe.cpp.o:
	$(MAKE) -f CMakeFiles/moegb.dir/build.make CMakeFiles/moegb.dir/Cartrigbe.cpp.o
.PHONY : Cartrigbe.cpp.o

Cartrigbe.i: Cartrigbe.cpp.i

.PHONY : Cartrigbe.i

# target to preprocess a source file
Cartrigbe.cpp.i:
	$(MAKE) -f CMakeFiles/moegb.dir/build.make CMakeFiles/moegb.dir/Cartrigbe.cpp.i
.PHONY : Cartrigbe.cpp.i

Cartrigbe.s: Cartrigbe.cpp.s

.PHONY : Cartrigbe.s

# target to generate assembly for a file
Cartrigbe.cpp.s:
	$(MAKE) -f CMakeFiles/moegb.dir/build.make CMakeFiles/moegb.dir/Cartrigbe.cpp.s
.PHONY : Cartrigbe.cpp.s

Cpu.o: Cpu.cpp.o

.PHONY : Cpu.o

# target to build an object file
Cpu.cpp.o:
	$(MAKE) -f CMakeFiles/moegb.dir/build.make CMakeFiles/moegb.dir/Cpu.cpp.o
.PHONY : Cpu.cpp.o

Cpu.i: Cpu.cpp.i

.PHONY : Cpu.i

# target to preprocess a source file
Cpu.cpp.i:
	$(MAKE) -f CMakeFiles/moegb.dir/build.make CMakeFiles/moegb.dir/Cpu.cpp.i
.PHONY : Cpu.cpp.i

Cpu.s: Cpu.cpp.s

.PHONY : Cpu.s

# target to generate assembly for a file
Cpu.cpp.s:
	$(MAKE) -f CMakeFiles/moegb.dir/build.make CMakeFiles/moegb.dir/Cpu.cpp.s
.PHONY : Cpu.cpp.s

System.o: System.cpp.o

.PHONY : System.o

# target to build an object file
System.cpp.o:
	$(MAKE) -f CMakeFiles/moegb.dir/build.make CMakeFiles/moegb.dir/System.cpp.o
.PHONY : System.cpp.o

System.i: System.cpp.i

.PHONY : System.i

# target to preprocess a source file
System.cpp.i:
	$(MAKE) -f CMakeFiles/moegb.dir/build.make CMakeFiles/moegb.dir/System.cpp.i
.PHONY : System.cpp.i

System.s: System.cpp.s

.PHONY : System.s

# target to generate assembly for a file
System.cpp.s:
	$(MAKE) -f CMakeFiles/moegb.dir/build.make CMakeFiles/moegb.dir/System.cpp.s
.PHONY : System.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/moegb.dir/build.make CMakeFiles/moegb.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/moegb.dir/build.make CMakeFiles/moegb.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/moegb.dir/build.make CMakeFiles/moegb.dir/main.cpp.s
.PHONY : main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... moegb"
	@echo "... edit_cache"
	@echo "... Bootstrap.o"
	@echo "... Bootstrap.i"
	@echo "... Bootstrap.s"
	@echo "... Cartrigbe.o"
	@echo "... Cartrigbe.i"
	@echo "... Cartrigbe.s"
	@echo "... Cpu.o"
	@echo "... Cpu.i"
	@echo "... Cpu.s"
	@echo "... System.o"
	@echo "... System.i"
	@echo "... System.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
