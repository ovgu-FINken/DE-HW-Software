# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.6

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\JetBrains\CLion 2016.3\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\JetBrains\CLion 2016.3\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Workspace\5-Embedded_programming\DE-HW-Software\f411re_blinking

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Workspace\5-Embedded_programming\DE-HW-Software\f411re_blinking\build

# Include any dependencies generated for this target.
include CMakeFiles/CMSIS.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CMSIS.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CMSIS.dir/flags.make

CMakeFiles/CMSIS.dir/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c.obj: CMakeFiles/CMSIS.dir/flags.make
CMakeFiles/CMSIS.dir/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c.obj: ../Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Workspace\5-Embedded_programming\DE-HW-Software\f411re_blinking\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/CMSIS.dir/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c.obj"
	C:\PROGRA~2\GNUTOO~1\50A5A~1.420\bin\AR4A58~1.EXE  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\CMSIS.dir\Drivers\CMSIS\Device\ST\STM32F4xx\Source\Templates\system_stm32f4xx.c.obj   -c D:\Workspace\5-Embedded_programming\DE-HW-Software\f411re_blinking\Drivers\CMSIS\Device\ST\STM32F4xx\Source\Templates\system_stm32f4xx.c

CMakeFiles/CMSIS.dir/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CMSIS.dir/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c.i"
	C:\PROGRA~2\GNUTOO~1\50A5A~1.420\bin\AR4A58~1.EXE  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Workspace\5-Embedded_programming\DE-HW-Software\f411re_blinking\Drivers\CMSIS\Device\ST\STM32F4xx\Source\Templates\system_stm32f4xx.c > CMakeFiles\CMSIS.dir\Drivers\CMSIS\Device\ST\STM32F4xx\Source\Templates\system_stm32f4xx.c.i

CMakeFiles/CMSIS.dir/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CMSIS.dir/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c.s"
	C:\PROGRA~2\GNUTOO~1\50A5A~1.420\bin\AR4A58~1.EXE  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Workspace\5-Embedded_programming\DE-HW-Software\f411re_blinking\Drivers\CMSIS\Device\ST\STM32F4xx\Source\Templates\system_stm32f4xx.c -o CMakeFiles\CMSIS.dir\Drivers\CMSIS\Device\ST\STM32F4xx\Source\Templates\system_stm32f4xx.c.s

CMakeFiles/CMSIS.dir/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c.obj.requires:

.PHONY : CMakeFiles/CMSIS.dir/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c.obj.requires

CMakeFiles/CMSIS.dir/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c.obj.provides: CMakeFiles/CMSIS.dir/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c.obj.requires
	$(MAKE) -f CMakeFiles\CMSIS.dir\build.make CMakeFiles/CMSIS.dir/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c.obj.provides.build
.PHONY : CMakeFiles/CMSIS.dir/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c.obj.provides

CMakeFiles/CMSIS.dir/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c.obj.provides.build: CMakeFiles/CMSIS.dir/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c.obj


# Object files for target CMSIS
CMSIS_OBJECTS = \
"CMakeFiles/CMSIS.dir/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c.obj"

# External object files for target CMSIS
CMSIS_EXTERNAL_OBJECTS =

libCMSIS.a: CMakeFiles/CMSIS.dir/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c.obj
libCMSIS.a: CMakeFiles/CMSIS.dir/build.make
libCMSIS.a: CMakeFiles/CMSIS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Workspace\5-Embedded_programming\DE-HW-Software\f411re_blinking\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libCMSIS.a"
	$(CMAKE_COMMAND) -P CMakeFiles\CMSIS.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\CMSIS.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CMSIS.dir/build: libCMSIS.a

.PHONY : CMakeFiles/CMSIS.dir/build

CMakeFiles/CMSIS.dir/requires: CMakeFiles/CMSIS.dir/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c.obj.requires

.PHONY : CMakeFiles/CMSIS.dir/requires

CMakeFiles/CMSIS.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\CMSIS.dir\cmake_clean.cmake
.PHONY : CMakeFiles/CMSIS.dir/clean

CMakeFiles/CMSIS.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Workspace\5-Embedded_programming\DE-HW-Software\f411re_blinking D:\Workspace\5-Embedded_programming\DE-HW-Software\f411re_blinking D:\Workspace\5-Embedded_programming\DE-HW-Software\f411re_blinking\build D:\Workspace\5-Embedded_programming\DE-HW-Software\f411re_blinking\build D:\Workspace\5-Embedded_programming\DE-HW-Software\f411re_blinking\build\CMakeFiles\CMSIS.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CMSIS.dir/depend

