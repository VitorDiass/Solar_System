# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /home/vitor/Documentos/Instalações/clion-2016.3.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/vitor/Documentos/Instalações/clion-2016.3.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/motor.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/motor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/motor.dir/flags.make

CMakeFiles/motor.dir/main.cpp.o: CMakeFiles/motor.dir/flags.make
CMakeFiles/motor.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/motor.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/motor.dir/main.cpp.o -c "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/main.cpp"

CMakeFiles/motor.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/motor.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/main.cpp" > CMakeFiles/motor.dir/main.cpp.i

CMakeFiles/motor.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/motor.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/main.cpp" -o CMakeFiles/motor.dir/main.cpp.s

CMakeFiles/motor.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/motor.dir/main.cpp.o.requires

CMakeFiles/motor.dir/main.cpp.o.provides: CMakeFiles/motor.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/motor.dir/build.make CMakeFiles/motor.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/motor.dir/main.cpp.o.provides

CMakeFiles/motor.dir/main.cpp.o.provides.build: CMakeFiles/motor.dir/main.cpp.o


CMakeFiles/motor.dir/engine.cpp.o: CMakeFiles/motor.dir/flags.make
CMakeFiles/motor.dir/engine.cpp.o: ../engine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/motor.dir/engine.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/motor.dir/engine.cpp.o -c "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/engine.cpp"

CMakeFiles/motor.dir/engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/motor.dir/engine.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/engine.cpp" > CMakeFiles/motor.dir/engine.cpp.i

CMakeFiles/motor.dir/engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/motor.dir/engine.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/engine.cpp" -o CMakeFiles/motor.dir/engine.cpp.s

CMakeFiles/motor.dir/engine.cpp.o.requires:

.PHONY : CMakeFiles/motor.dir/engine.cpp.o.requires

CMakeFiles/motor.dir/engine.cpp.o.provides: CMakeFiles/motor.dir/engine.cpp.o.requires
	$(MAKE) -f CMakeFiles/motor.dir/build.make CMakeFiles/motor.dir/engine.cpp.o.provides.build
.PHONY : CMakeFiles/motor.dir/engine.cpp.o.provides

CMakeFiles/motor.dir/engine.cpp.o.provides.build: CMakeFiles/motor.dir/engine.cpp.o


CMakeFiles/motor.dir/tinystr.cpp.o: CMakeFiles/motor.dir/flags.make
CMakeFiles/motor.dir/tinystr.cpp.o: ../tinystr.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/motor.dir/tinystr.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/motor.dir/tinystr.cpp.o -c "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/tinystr.cpp"

CMakeFiles/motor.dir/tinystr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/motor.dir/tinystr.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/tinystr.cpp" > CMakeFiles/motor.dir/tinystr.cpp.i

CMakeFiles/motor.dir/tinystr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/motor.dir/tinystr.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/tinystr.cpp" -o CMakeFiles/motor.dir/tinystr.cpp.s

CMakeFiles/motor.dir/tinystr.cpp.o.requires:

.PHONY : CMakeFiles/motor.dir/tinystr.cpp.o.requires

CMakeFiles/motor.dir/tinystr.cpp.o.provides: CMakeFiles/motor.dir/tinystr.cpp.o.requires
	$(MAKE) -f CMakeFiles/motor.dir/build.make CMakeFiles/motor.dir/tinystr.cpp.o.provides.build
.PHONY : CMakeFiles/motor.dir/tinystr.cpp.o.provides

CMakeFiles/motor.dir/tinystr.cpp.o.provides.build: CMakeFiles/motor.dir/tinystr.cpp.o


CMakeFiles/motor.dir/tinyxml.cpp.o: CMakeFiles/motor.dir/flags.make
CMakeFiles/motor.dir/tinyxml.cpp.o: ../tinyxml.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/motor.dir/tinyxml.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/motor.dir/tinyxml.cpp.o -c "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/tinyxml.cpp"

CMakeFiles/motor.dir/tinyxml.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/motor.dir/tinyxml.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/tinyxml.cpp" > CMakeFiles/motor.dir/tinyxml.cpp.i

CMakeFiles/motor.dir/tinyxml.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/motor.dir/tinyxml.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/tinyxml.cpp" -o CMakeFiles/motor.dir/tinyxml.cpp.s

CMakeFiles/motor.dir/tinyxml.cpp.o.requires:

.PHONY : CMakeFiles/motor.dir/tinyxml.cpp.o.requires

CMakeFiles/motor.dir/tinyxml.cpp.o.provides: CMakeFiles/motor.dir/tinyxml.cpp.o.requires
	$(MAKE) -f CMakeFiles/motor.dir/build.make CMakeFiles/motor.dir/tinyxml.cpp.o.provides.build
.PHONY : CMakeFiles/motor.dir/tinyxml.cpp.o.provides

CMakeFiles/motor.dir/tinyxml.cpp.o.provides.build: CMakeFiles/motor.dir/tinyxml.cpp.o


CMakeFiles/motor.dir/tinyxmlerror.cpp.o: CMakeFiles/motor.dir/flags.make
CMakeFiles/motor.dir/tinyxmlerror.cpp.o: ../tinyxmlerror.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/motor.dir/tinyxmlerror.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/motor.dir/tinyxmlerror.cpp.o -c "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/tinyxmlerror.cpp"

CMakeFiles/motor.dir/tinyxmlerror.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/motor.dir/tinyxmlerror.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/tinyxmlerror.cpp" > CMakeFiles/motor.dir/tinyxmlerror.cpp.i

CMakeFiles/motor.dir/tinyxmlerror.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/motor.dir/tinyxmlerror.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/tinyxmlerror.cpp" -o CMakeFiles/motor.dir/tinyxmlerror.cpp.s

CMakeFiles/motor.dir/tinyxmlerror.cpp.o.requires:

.PHONY : CMakeFiles/motor.dir/tinyxmlerror.cpp.o.requires

CMakeFiles/motor.dir/tinyxmlerror.cpp.o.provides: CMakeFiles/motor.dir/tinyxmlerror.cpp.o.requires
	$(MAKE) -f CMakeFiles/motor.dir/build.make CMakeFiles/motor.dir/tinyxmlerror.cpp.o.provides.build
.PHONY : CMakeFiles/motor.dir/tinyxmlerror.cpp.o.provides

CMakeFiles/motor.dir/tinyxmlerror.cpp.o.provides.build: CMakeFiles/motor.dir/tinyxmlerror.cpp.o


CMakeFiles/motor.dir/tinyxmlparser.cpp.o: CMakeFiles/motor.dir/flags.make
CMakeFiles/motor.dir/tinyxmlparser.cpp.o: ../tinyxmlparser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/motor.dir/tinyxmlparser.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/motor.dir/tinyxmlparser.cpp.o -c "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/tinyxmlparser.cpp"

CMakeFiles/motor.dir/tinyxmlparser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/motor.dir/tinyxmlparser.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/tinyxmlparser.cpp" > CMakeFiles/motor.dir/tinyxmlparser.cpp.i

CMakeFiles/motor.dir/tinyxmlparser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/motor.dir/tinyxmlparser.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/tinyxmlparser.cpp" -o CMakeFiles/motor.dir/tinyxmlparser.cpp.s

CMakeFiles/motor.dir/tinyxmlparser.cpp.o.requires:

.PHONY : CMakeFiles/motor.dir/tinyxmlparser.cpp.o.requires

CMakeFiles/motor.dir/tinyxmlparser.cpp.o.provides: CMakeFiles/motor.dir/tinyxmlparser.cpp.o.requires
	$(MAKE) -f CMakeFiles/motor.dir/build.make CMakeFiles/motor.dir/tinyxmlparser.cpp.o.provides.build
.PHONY : CMakeFiles/motor.dir/tinyxmlparser.cpp.o.provides

CMakeFiles/motor.dir/tinyxmlparser.cpp.o.provides.build: CMakeFiles/motor.dir/tinyxmlparser.cpp.o


# Object files for target motor
motor_OBJECTS = \
"CMakeFiles/motor.dir/main.cpp.o" \
"CMakeFiles/motor.dir/engine.cpp.o" \
"CMakeFiles/motor.dir/tinystr.cpp.o" \
"CMakeFiles/motor.dir/tinyxml.cpp.o" \
"CMakeFiles/motor.dir/tinyxmlerror.cpp.o" \
"CMakeFiles/motor.dir/tinyxmlparser.cpp.o"

# External object files for target motor
motor_EXTERNAL_OBJECTS =

motor: CMakeFiles/motor.dir/main.cpp.o
motor: CMakeFiles/motor.dir/engine.cpp.o
motor: CMakeFiles/motor.dir/tinystr.cpp.o
motor: CMakeFiles/motor.dir/tinyxml.cpp.o
motor: CMakeFiles/motor.dir/tinyxmlerror.cpp.o
motor: CMakeFiles/motor.dir/tinyxmlparser.cpp.o
motor: CMakeFiles/motor.dir/build.make
motor: /usr/lib/x86_64-linux-gnu/libGLEW.so
motor: /usr/lib/x86_64-linux-gnu/libIL.so
motor: /usr/lib/x86_64-linux-gnu/libGLU.so
motor: /usr/lib/x86_64-linux-gnu/libGL.so
motor: /usr/lib/x86_64-linux-gnu/libglut.so
motor: /usr/lib/x86_64-linux-gnu/libXmu.so
motor: /usr/lib/x86_64-linux-gnu/libXi.so
motor: CMakeFiles/motor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable motor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/motor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/motor.dir/build: motor

.PHONY : CMakeFiles/motor.dir/build

CMakeFiles/motor.dir/requires: CMakeFiles/motor.dir/main.cpp.o.requires
CMakeFiles/motor.dir/requires: CMakeFiles/motor.dir/engine.cpp.o.requires
CMakeFiles/motor.dir/requires: CMakeFiles/motor.dir/tinystr.cpp.o.requires
CMakeFiles/motor.dir/requires: CMakeFiles/motor.dir/tinyxml.cpp.o.requires
CMakeFiles/motor.dir/requires: CMakeFiles/motor.dir/tinyxmlerror.cpp.o.requires
CMakeFiles/motor.dir/requires: CMakeFiles/motor.dir/tinyxmlparser.cpp.o.requires

.PHONY : CMakeFiles/motor.dir/requires

CMakeFiles/motor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/motor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/motor.dir/clean

CMakeFiles/motor.dir/depend:
	cd "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo" "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo" "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/cmake-build-debug" "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/cmake-build-debug" "/home/vitor/Documentos/Univ/3ºAno/2ºSemestre/Computação Gráfica/Trabalho Prático/4P/Fase4_Grupo7/Codigo/cmake-build-debug/CMakeFiles/motor.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/motor.dir/depend

