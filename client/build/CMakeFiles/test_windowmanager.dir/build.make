# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_SOURCE_DIR = /Users/isika/code/tcp-chat/client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/isika/code/tcp-chat/client/build

# Include any dependencies generated for this target.
include CMakeFiles/test_windowmanager.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test_windowmanager.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test_windowmanager.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_windowmanager.dir/flags.make

CMakeFiles/test_windowmanager.dir/codegen:
.PHONY : CMakeFiles/test_windowmanager.dir/codegen

CMakeFiles/test_windowmanager.dir/tests/test_windowmanager.cpp.o: CMakeFiles/test_windowmanager.dir/flags.make
CMakeFiles/test_windowmanager.dir/tests/test_windowmanager.cpp.o: /Users/isika/code/tcp-chat/client/tests/test_windowmanager.cpp
CMakeFiles/test_windowmanager.dir/tests/test_windowmanager.cpp.o: CMakeFiles/test_windowmanager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/isika/code/tcp-chat/client/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_windowmanager.dir/tests/test_windowmanager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_windowmanager.dir/tests/test_windowmanager.cpp.o -MF CMakeFiles/test_windowmanager.dir/tests/test_windowmanager.cpp.o.d -o CMakeFiles/test_windowmanager.dir/tests/test_windowmanager.cpp.o -c /Users/isika/code/tcp-chat/client/tests/test_windowmanager.cpp

CMakeFiles/test_windowmanager.dir/tests/test_windowmanager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_windowmanager.dir/tests/test_windowmanager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/isika/code/tcp-chat/client/tests/test_windowmanager.cpp > CMakeFiles/test_windowmanager.dir/tests/test_windowmanager.cpp.i

CMakeFiles/test_windowmanager.dir/tests/test_windowmanager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_windowmanager.dir/tests/test_windowmanager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/isika/code/tcp-chat/client/tests/test_windowmanager.cpp -o CMakeFiles/test_windowmanager.dir/tests/test_windowmanager.cpp.s

CMakeFiles/test_windowmanager.dir/src/main.cpp.o: CMakeFiles/test_windowmanager.dir/flags.make
CMakeFiles/test_windowmanager.dir/src/main.cpp.o: /Users/isika/code/tcp-chat/client/src/main.cpp
CMakeFiles/test_windowmanager.dir/src/main.cpp.o: CMakeFiles/test_windowmanager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/isika/code/tcp-chat/client/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test_windowmanager.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_windowmanager.dir/src/main.cpp.o -MF CMakeFiles/test_windowmanager.dir/src/main.cpp.o.d -o CMakeFiles/test_windowmanager.dir/src/main.cpp.o -c /Users/isika/code/tcp-chat/client/src/main.cpp

CMakeFiles/test_windowmanager.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_windowmanager.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/isika/code/tcp-chat/client/src/main.cpp > CMakeFiles/test_windowmanager.dir/src/main.cpp.i

CMakeFiles/test_windowmanager.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_windowmanager.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/isika/code/tcp-chat/client/src/main.cpp -o CMakeFiles/test_windowmanager.dir/src/main.cpp.s

CMakeFiles/test_windowmanager.dir/src/chatWindow.cpp.o: CMakeFiles/test_windowmanager.dir/flags.make
CMakeFiles/test_windowmanager.dir/src/chatWindow.cpp.o: /Users/isika/code/tcp-chat/client/src/chatWindow.cpp
CMakeFiles/test_windowmanager.dir/src/chatWindow.cpp.o: CMakeFiles/test_windowmanager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/isika/code/tcp-chat/client/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/test_windowmanager.dir/src/chatWindow.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_windowmanager.dir/src/chatWindow.cpp.o -MF CMakeFiles/test_windowmanager.dir/src/chatWindow.cpp.o.d -o CMakeFiles/test_windowmanager.dir/src/chatWindow.cpp.o -c /Users/isika/code/tcp-chat/client/src/chatWindow.cpp

CMakeFiles/test_windowmanager.dir/src/chatWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_windowmanager.dir/src/chatWindow.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/isika/code/tcp-chat/client/src/chatWindow.cpp > CMakeFiles/test_windowmanager.dir/src/chatWindow.cpp.i

CMakeFiles/test_windowmanager.dir/src/chatWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_windowmanager.dir/src/chatWindow.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/isika/code/tcp-chat/client/src/chatWindow.cpp -o CMakeFiles/test_windowmanager.dir/src/chatWindow.cpp.s

CMakeFiles/test_windowmanager.dir/src/networkManager.cpp.o: CMakeFiles/test_windowmanager.dir/flags.make
CMakeFiles/test_windowmanager.dir/src/networkManager.cpp.o: /Users/isika/code/tcp-chat/client/src/networkManager.cpp
CMakeFiles/test_windowmanager.dir/src/networkManager.cpp.o: CMakeFiles/test_windowmanager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/isika/code/tcp-chat/client/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/test_windowmanager.dir/src/networkManager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_windowmanager.dir/src/networkManager.cpp.o -MF CMakeFiles/test_windowmanager.dir/src/networkManager.cpp.o.d -o CMakeFiles/test_windowmanager.dir/src/networkManager.cpp.o -c /Users/isika/code/tcp-chat/client/src/networkManager.cpp

CMakeFiles/test_windowmanager.dir/src/networkManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_windowmanager.dir/src/networkManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/isika/code/tcp-chat/client/src/networkManager.cpp > CMakeFiles/test_windowmanager.dir/src/networkManager.cpp.i

CMakeFiles/test_windowmanager.dir/src/networkManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_windowmanager.dir/src/networkManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/isika/code/tcp-chat/client/src/networkManager.cpp -o CMakeFiles/test_windowmanager.dir/src/networkManager.cpp.s

CMakeFiles/test_windowmanager.dir/src/windowManager.cpp.o: CMakeFiles/test_windowmanager.dir/flags.make
CMakeFiles/test_windowmanager.dir/src/windowManager.cpp.o: /Users/isika/code/tcp-chat/client/src/windowManager.cpp
CMakeFiles/test_windowmanager.dir/src/windowManager.cpp.o: CMakeFiles/test_windowmanager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/isika/code/tcp-chat/client/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/test_windowmanager.dir/src/windowManager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_windowmanager.dir/src/windowManager.cpp.o -MF CMakeFiles/test_windowmanager.dir/src/windowManager.cpp.o.d -o CMakeFiles/test_windowmanager.dir/src/windowManager.cpp.o -c /Users/isika/code/tcp-chat/client/src/windowManager.cpp

CMakeFiles/test_windowmanager.dir/src/windowManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_windowmanager.dir/src/windowManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/isika/code/tcp-chat/client/src/windowManager.cpp > CMakeFiles/test_windowmanager.dir/src/windowManager.cpp.i

CMakeFiles/test_windowmanager.dir/src/windowManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_windowmanager.dir/src/windowManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/isika/code/tcp-chat/client/src/windowManager.cpp -o CMakeFiles/test_windowmanager.dir/src/windowManager.cpp.s

CMakeFiles/test_windowmanager.dir/src/serverAddressWindow.cpp.o: CMakeFiles/test_windowmanager.dir/flags.make
CMakeFiles/test_windowmanager.dir/src/serverAddressWindow.cpp.o: /Users/isika/code/tcp-chat/client/src/serverAddressWindow.cpp
CMakeFiles/test_windowmanager.dir/src/serverAddressWindow.cpp.o: CMakeFiles/test_windowmanager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/isika/code/tcp-chat/client/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/test_windowmanager.dir/src/serverAddressWindow.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_windowmanager.dir/src/serverAddressWindow.cpp.o -MF CMakeFiles/test_windowmanager.dir/src/serverAddressWindow.cpp.o.d -o CMakeFiles/test_windowmanager.dir/src/serverAddressWindow.cpp.o -c /Users/isika/code/tcp-chat/client/src/serverAddressWindow.cpp

CMakeFiles/test_windowmanager.dir/src/serverAddressWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_windowmanager.dir/src/serverAddressWindow.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/isika/code/tcp-chat/client/src/serverAddressWindow.cpp > CMakeFiles/test_windowmanager.dir/src/serverAddressWindow.cpp.i

CMakeFiles/test_windowmanager.dir/src/serverAddressWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_windowmanager.dir/src/serverAddressWindow.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/isika/code/tcp-chat/client/src/serverAddressWindow.cpp -o CMakeFiles/test_windowmanager.dir/src/serverAddressWindow.cpp.s

CMakeFiles/test_windowmanager.dir/src/usernameWindow.cpp.o: CMakeFiles/test_windowmanager.dir/flags.make
CMakeFiles/test_windowmanager.dir/src/usernameWindow.cpp.o: /Users/isika/code/tcp-chat/client/src/usernameWindow.cpp
CMakeFiles/test_windowmanager.dir/src/usernameWindow.cpp.o: CMakeFiles/test_windowmanager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/isika/code/tcp-chat/client/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/test_windowmanager.dir/src/usernameWindow.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_windowmanager.dir/src/usernameWindow.cpp.o -MF CMakeFiles/test_windowmanager.dir/src/usernameWindow.cpp.o.d -o CMakeFiles/test_windowmanager.dir/src/usernameWindow.cpp.o -c /Users/isika/code/tcp-chat/client/src/usernameWindow.cpp

CMakeFiles/test_windowmanager.dir/src/usernameWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_windowmanager.dir/src/usernameWindow.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/isika/code/tcp-chat/client/src/usernameWindow.cpp > CMakeFiles/test_windowmanager.dir/src/usernameWindow.cpp.i

CMakeFiles/test_windowmanager.dir/src/usernameWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_windowmanager.dir/src/usernameWindow.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/isika/code/tcp-chat/client/src/usernameWindow.cpp -o CMakeFiles/test_windowmanager.dir/src/usernameWindow.cpp.s

CMakeFiles/test_windowmanager.dir/src/logger.cpp.o: CMakeFiles/test_windowmanager.dir/flags.make
CMakeFiles/test_windowmanager.dir/src/logger.cpp.o: /Users/isika/code/tcp-chat/client/src/logger.cpp
CMakeFiles/test_windowmanager.dir/src/logger.cpp.o: CMakeFiles/test_windowmanager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/isika/code/tcp-chat/client/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/test_windowmanager.dir/src/logger.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_windowmanager.dir/src/logger.cpp.o -MF CMakeFiles/test_windowmanager.dir/src/logger.cpp.o.d -o CMakeFiles/test_windowmanager.dir/src/logger.cpp.o -c /Users/isika/code/tcp-chat/client/src/logger.cpp

CMakeFiles/test_windowmanager.dir/src/logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_windowmanager.dir/src/logger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/isika/code/tcp-chat/client/src/logger.cpp > CMakeFiles/test_windowmanager.dir/src/logger.cpp.i

CMakeFiles/test_windowmanager.dir/src/logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_windowmanager.dir/src/logger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/isika/code/tcp-chat/client/src/logger.cpp -o CMakeFiles/test_windowmanager.dir/src/logger.cpp.s

# Object files for target test_windowmanager
test_windowmanager_OBJECTS = \
"CMakeFiles/test_windowmanager.dir/tests/test_windowmanager.cpp.o" \
"CMakeFiles/test_windowmanager.dir/src/main.cpp.o" \
"CMakeFiles/test_windowmanager.dir/src/chatWindow.cpp.o" \
"CMakeFiles/test_windowmanager.dir/src/networkManager.cpp.o" \
"CMakeFiles/test_windowmanager.dir/src/windowManager.cpp.o" \
"CMakeFiles/test_windowmanager.dir/src/serverAddressWindow.cpp.o" \
"CMakeFiles/test_windowmanager.dir/src/usernameWindow.cpp.o" \
"CMakeFiles/test_windowmanager.dir/src/logger.cpp.o"

# External object files for target test_windowmanager
test_windowmanager_EXTERNAL_OBJECTS =

bin/test_windowmanager: CMakeFiles/test_windowmanager.dir/tests/test_windowmanager.cpp.o
bin/test_windowmanager: CMakeFiles/test_windowmanager.dir/src/main.cpp.o
bin/test_windowmanager: CMakeFiles/test_windowmanager.dir/src/chatWindow.cpp.o
bin/test_windowmanager: CMakeFiles/test_windowmanager.dir/src/networkManager.cpp.o
bin/test_windowmanager: CMakeFiles/test_windowmanager.dir/src/windowManager.cpp.o
bin/test_windowmanager: CMakeFiles/test_windowmanager.dir/src/serverAddressWindow.cpp.o
bin/test_windowmanager: CMakeFiles/test_windowmanager.dir/src/usernameWindow.cpp.o
bin/test_windowmanager: CMakeFiles/test_windowmanager.dir/src/logger.cpp.o
bin/test_windowmanager: CMakeFiles/test_windowmanager.dir/build.make
bin/test_windowmanager: /usr/local/lib/QtWidgets.framework/Versions/A/QtWidgets
bin/test_windowmanager: /usr/local/lib/QtNetwork.framework/Versions/A/QtNetwork
bin/test_windowmanager: /usr/local/lib/QtTest.framework/Versions/A/QtTest
bin/test_windowmanager: /usr/local/lib/QtGui.framework/Versions/A/QtGui
bin/test_windowmanager: /usr/local/lib/QtCore.framework/Versions/A/QtCore
bin/test_windowmanager: CMakeFiles/test_windowmanager.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/isika/code/tcp-chat/client/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable bin/test_windowmanager"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_windowmanager.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_windowmanager.dir/build: bin/test_windowmanager
.PHONY : CMakeFiles/test_windowmanager.dir/build

CMakeFiles/test_windowmanager.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_windowmanager.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_windowmanager.dir/clean

CMakeFiles/test_windowmanager.dir/depend:
	cd /Users/isika/code/tcp-chat/client/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/isika/code/tcp-chat/client /Users/isika/code/tcp-chat/client /Users/isika/code/tcp-chat/client/build /Users/isika/code/tcp-chat/client/build /Users/isika/code/tcp-chat/client/build/CMakeFiles/test_windowmanager.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/test_windowmanager.dir/depend

