# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lpc/server/cserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lpc/server/cserver

# Include any dependencies generated for this target.
include CMakeFiles/http.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/http.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/http.dir/flags.make

CMakeFiles/http.dir/src/http_event_init.o: CMakeFiles/http.dir/flags.make
CMakeFiles/http.dir/src/http_event_init.o: src/http_event_init.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lpc/server/cserver/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/http.dir/src/http_event_init.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/http.dir/src/http_event_init.o   -c /home/lpc/server/cserver/src/http_event_init.c

CMakeFiles/http.dir/src/http_event_init.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/http.dir/src/http_event_init.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/lpc/server/cserver/src/http_event_init.c > CMakeFiles/http.dir/src/http_event_init.i

CMakeFiles/http.dir/src/http_event_init.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/http.dir/src/http_event_init.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/lpc/server/cserver/src/http_event_init.c -o CMakeFiles/http.dir/src/http_event_init.s

CMakeFiles/http.dir/src/http_event_init.o.requires:
.PHONY : CMakeFiles/http.dir/src/http_event_init.o.requires

CMakeFiles/http.dir/src/http_event_init.o.provides: CMakeFiles/http.dir/src/http_event_init.o.requires
	$(MAKE) -f CMakeFiles/http.dir/build.make CMakeFiles/http.dir/src/http_event_init.o.provides.build
.PHONY : CMakeFiles/http.dir/src/http_event_init.o.provides

CMakeFiles/http.dir/src/http_event_init.o.provides.build: CMakeFiles/http.dir/src/http_event_init.o

CMakeFiles/http.dir/src/http_get_line.o: CMakeFiles/http.dir/flags.make
CMakeFiles/http.dir/src/http_get_line.o: src/http_get_line.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lpc/server/cserver/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/http.dir/src/http_get_line.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/http.dir/src/http_get_line.o   -c /home/lpc/server/cserver/src/http_get_line.c

CMakeFiles/http.dir/src/http_get_line.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/http.dir/src/http_get_line.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/lpc/server/cserver/src/http_get_line.c > CMakeFiles/http.dir/src/http_get_line.i

CMakeFiles/http.dir/src/http_get_line.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/http.dir/src/http_get_line.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/lpc/server/cserver/src/http_get_line.c -o CMakeFiles/http.dir/src/http_get_line.s

CMakeFiles/http.dir/src/http_get_line.o.requires:
.PHONY : CMakeFiles/http.dir/src/http_get_line.o.requires

CMakeFiles/http.dir/src/http_get_line.o.provides: CMakeFiles/http.dir/src/http_get_line.o.requires
	$(MAKE) -f CMakeFiles/http.dir/build.make CMakeFiles/http.dir/src/http_get_line.o.provides.build
.PHONY : CMakeFiles/http.dir/src/http_get_line.o.provides

CMakeFiles/http.dir/src/http_get_line.o.provides.build: CMakeFiles/http.dir/src/http_get_line.o

CMakeFiles/http.dir/src/http_recv_msg.o: CMakeFiles/http.dir/flags.make
CMakeFiles/http.dir/src/http_recv_msg.o: src/http_recv_msg.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lpc/server/cserver/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/http.dir/src/http_recv_msg.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/http.dir/src/http_recv_msg.o   -c /home/lpc/server/cserver/src/http_recv_msg.c

CMakeFiles/http.dir/src/http_recv_msg.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/http.dir/src/http_recv_msg.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/lpc/server/cserver/src/http_recv_msg.c > CMakeFiles/http.dir/src/http_recv_msg.i

CMakeFiles/http.dir/src/http_recv_msg.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/http.dir/src/http_recv_msg.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/lpc/server/cserver/src/http_recv_msg.c -o CMakeFiles/http.dir/src/http_recv_msg.s

CMakeFiles/http.dir/src/http_recv_msg.o.requires:
.PHONY : CMakeFiles/http.dir/src/http_recv_msg.o.requires

CMakeFiles/http.dir/src/http_recv_msg.o.provides: CMakeFiles/http.dir/src/http_recv_msg.o.requires
	$(MAKE) -f CMakeFiles/http.dir/build.make CMakeFiles/http.dir/src/http_recv_msg.o.provides.build
.PHONY : CMakeFiles/http.dir/src/http_recv_msg.o.provides

CMakeFiles/http.dir/src/http_recv_msg.o.provides.build: CMakeFiles/http.dir/src/http_recv_msg.o

CMakeFiles/http.dir/src/http_event_accept.o: CMakeFiles/http.dir/flags.make
CMakeFiles/http.dir/src/http_event_accept.o: src/http_event_accept.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lpc/server/cserver/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/http.dir/src/http_event_accept.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/http.dir/src/http_event_accept.o   -c /home/lpc/server/cserver/src/http_event_accept.c

CMakeFiles/http.dir/src/http_event_accept.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/http.dir/src/http_event_accept.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/lpc/server/cserver/src/http_event_accept.c > CMakeFiles/http.dir/src/http_event_accept.i

CMakeFiles/http.dir/src/http_event_accept.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/http.dir/src/http_event_accept.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/lpc/server/cserver/src/http_event_accept.c -o CMakeFiles/http.dir/src/http_event_accept.s

CMakeFiles/http.dir/src/http_event_accept.o.requires:
.PHONY : CMakeFiles/http.dir/src/http_event_accept.o.requires

CMakeFiles/http.dir/src/http_event_accept.o.provides: CMakeFiles/http.dir/src/http_event_accept.o.requires
	$(MAKE) -f CMakeFiles/http.dir/build.make CMakeFiles/http.dir/src/http_event_accept.o.provides.build
.PHONY : CMakeFiles/http.dir/src/http_event_accept.o.provides

CMakeFiles/http.dir/src/http_event_accept.o.provides.build: CMakeFiles/http.dir/src/http_event_accept.o

CMakeFiles/http.dir/src/http_send_file.o: CMakeFiles/http.dir/flags.make
CMakeFiles/http.dir/src/http_send_file.o: src/http_send_file.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lpc/server/cserver/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/http.dir/src/http_send_file.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/http.dir/src/http_send_file.o   -c /home/lpc/server/cserver/src/http_send_file.c

CMakeFiles/http.dir/src/http_send_file.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/http.dir/src/http_send_file.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/lpc/server/cserver/src/http_send_file.c > CMakeFiles/http.dir/src/http_send_file.i

CMakeFiles/http.dir/src/http_send_file.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/http.dir/src/http_send_file.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/lpc/server/cserver/src/http_send_file.c -o CMakeFiles/http.dir/src/http_send_file.s

CMakeFiles/http.dir/src/http_send_file.o.requires:
.PHONY : CMakeFiles/http.dir/src/http_send_file.o.requires

CMakeFiles/http.dir/src/http_send_file.o.provides: CMakeFiles/http.dir/src/http_send_file.o.requires
	$(MAKE) -f CMakeFiles/http.dir/build.make CMakeFiles/http.dir/src/http_send_file.o.provides.build
.PHONY : CMakeFiles/http.dir/src/http_send_file.o.provides

CMakeFiles/http.dir/src/http_send_file.o.provides.build: CMakeFiles/http.dir/src/http_send_file.o

CMakeFiles/http.dir/src/http_get_type.o: CMakeFiles/http.dir/flags.make
CMakeFiles/http.dir/src/http_get_type.o: src/http_get_type.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lpc/server/cserver/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/http.dir/src/http_get_type.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/http.dir/src/http_get_type.o   -c /home/lpc/server/cserver/src/http_get_type.c

CMakeFiles/http.dir/src/http_get_type.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/http.dir/src/http_get_type.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/lpc/server/cserver/src/http_get_type.c > CMakeFiles/http.dir/src/http_get_type.i

CMakeFiles/http.dir/src/http_get_type.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/http.dir/src/http_get_type.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/lpc/server/cserver/src/http_get_type.c -o CMakeFiles/http.dir/src/http_get_type.s

CMakeFiles/http.dir/src/http_get_type.o.requires:
.PHONY : CMakeFiles/http.dir/src/http_get_type.o.requires

CMakeFiles/http.dir/src/http_get_type.o.provides: CMakeFiles/http.dir/src/http_get_type.o.requires
	$(MAKE) -f CMakeFiles/http.dir/build.make CMakeFiles/http.dir/src/http_get_type.o.provides.build
.PHONY : CMakeFiles/http.dir/src/http_get_type.o.provides

CMakeFiles/http.dir/src/http_get_type.o.provides.build: CMakeFiles/http.dir/src/http_get_type.o

CMakeFiles/http.dir/src/http_send_msg.o: CMakeFiles/http.dir/flags.make
CMakeFiles/http.dir/src/http_send_msg.o: src/http_send_msg.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lpc/server/cserver/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/http.dir/src/http_send_msg.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/http.dir/src/http_send_msg.o   -c /home/lpc/server/cserver/src/http_send_msg.c

CMakeFiles/http.dir/src/http_send_msg.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/http.dir/src/http_send_msg.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/lpc/server/cserver/src/http_send_msg.c > CMakeFiles/http.dir/src/http_send_msg.i

CMakeFiles/http.dir/src/http_send_msg.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/http.dir/src/http_send_msg.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/lpc/server/cserver/src/http_send_msg.c -o CMakeFiles/http.dir/src/http_send_msg.s

CMakeFiles/http.dir/src/http_send_msg.o.requires:
.PHONY : CMakeFiles/http.dir/src/http_send_msg.o.requires

CMakeFiles/http.dir/src/http_send_msg.o.provides: CMakeFiles/http.dir/src/http_send_msg.o.requires
	$(MAKE) -f CMakeFiles/http.dir/build.make CMakeFiles/http.dir/src/http_send_msg.o.provides.build
.PHONY : CMakeFiles/http.dir/src/http_send_msg.o.provides

CMakeFiles/http.dir/src/http_send_msg.o.provides.build: CMakeFiles/http.dir/src/http_send_msg.o

CMakeFiles/http.dir/src/http_create_msg.o: CMakeFiles/http.dir/flags.make
CMakeFiles/http.dir/src/http_create_msg.o: src/http_create_msg.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lpc/server/cserver/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/http.dir/src/http_create_msg.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/http.dir/src/http_create_msg.o   -c /home/lpc/server/cserver/src/http_create_msg.c

CMakeFiles/http.dir/src/http_create_msg.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/http.dir/src/http_create_msg.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/lpc/server/cserver/src/http_create_msg.c > CMakeFiles/http.dir/src/http_create_msg.i

CMakeFiles/http.dir/src/http_create_msg.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/http.dir/src/http_create_msg.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/lpc/server/cserver/src/http_create_msg.c -o CMakeFiles/http.dir/src/http_create_msg.s

CMakeFiles/http.dir/src/http_create_msg.o.requires:
.PHONY : CMakeFiles/http.dir/src/http_create_msg.o.requires

CMakeFiles/http.dir/src/http_create_msg.o.provides: CMakeFiles/http.dir/src/http_create_msg.o.requires
	$(MAKE) -f CMakeFiles/http.dir/build.make CMakeFiles/http.dir/src/http_create_msg.o.provides.build
.PHONY : CMakeFiles/http.dir/src/http_create_msg.o.provides

CMakeFiles/http.dir/src/http_create_msg.o.provides.build: CMakeFiles/http.dir/src/http_create_msg.o

CMakeFiles/http.dir/src/http_response.o: CMakeFiles/http.dir/flags.make
CMakeFiles/http.dir/src/http_response.o: src/http_response.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lpc/server/cserver/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/http.dir/src/http_response.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/http.dir/src/http_response.o   -c /home/lpc/server/cserver/src/http_response.c

CMakeFiles/http.dir/src/http_response.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/http.dir/src/http_response.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/lpc/server/cserver/src/http_response.c > CMakeFiles/http.dir/src/http_response.i

CMakeFiles/http.dir/src/http_response.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/http.dir/src/http_response.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/lpc/server/cserver/src/http_response.c -o CMakeFiles/http.dir/src/http_response.s

CMakeFiles/http.dir/src/http_response.o.requires:
.PHONY : CMakeFiles/http.dir/src/http_response.o.requires

CMakeFiles/http.dir/src/http_response.o.provides: CMakeFiles/http.dir/src/http_response.o.requires
	$(MAKE) -f CMakeFiles/http.dir/build.make CMakeFiles/http.dir/src/http_response.o.provides.build
.PHONY : CMakeFiles/http.dir/src/http_response.o.provides

CMakeFiles/http.dir/src/http_response.o.provides.build: CMakeFiles/http.dir/src/http_response.o

# Object files for target http
http_OBJECTS = \
"CMakeFiles/http.dir/src/http_event_init.o" \
"CMakeFiles/http.dir/src/http_get_line.o" \
"CMakeFiles/http.dir/src/http_recv_msg.o" \
"CMakeFiles/http.dir/src/http_event_accept.o" \
"CMakeFiles/http.dir/src/http_send_file.o" \
"CMakeFiles/http.dir/src/http_get_type.o" \
"CMakeFiles/http.dir/src/http_send_msg.o" \
"CMakeFiles/http.dir/src/http_create_msg.o" \
"CMakeFiles/http.dir/src/http_response.o"

# External object files for target http
http_EXTERNAL_OBJECTS =

lib/libhttp.so.1.2: CMakeFiles/http.dir/src/http_event_init.o
lib/libhttp.so.1.2: CMakeFiles/http.dir/src/http_get_line.o
lib/libhttp.so.1.2: CMakeFiles/http.dir/src/http_recv_msg.o
lib/libhttp.so.1.2: CMakeFiles/http.dir/src/http_event_accept.o
lib/libhttp.so.1.2: CMakeFiles/http.dir/src/http_send_file.o
lib/libhttp.so.1.2: CMakeFiles/http.dir/src/http_get_type.o
lib/libhttp.so.1.2: CMakeFiles/http.dir/src/http_send_msg.o
lib/libhttp.so.1.2: CMakeFiles/http.dir/src/http_create_msg.o
lib/libhttp.so.1.2: CMakeFiles/http.dir/src/http_response.o
lib/libhttp.so.1.2: CMakeFiles/http.dir/build.make
lib/libhttp.so.1.2: lib/libevent.so.1.2
lib/libhttp.so.1.2: CMakeFiles/http.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library lib/libhttp.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/http.dir/link.txt --verbose=$(VERBOSE)
	$(CMAKE_COMMAND) -E cmake_symlink_library lib/libhttp.so.1.2 lib/libhttp.so.1 lib/libhttp.so

lib/libhttp.so.1: lib/libhttp.so.1.2

lib/libhttp.so: lib/libhttp.so.1.2

# Rule to build all files generated by this target.
CMakeFiles/http.dir/build: lib/libhttp.so
.PHONY : CMakeFiles/http.dir/build

CMakeFiles/http.dir/requires: CMakeFiles/http.dir/src/http_event_init.o.requires
CMakeFiles/http.dir/requires: CMakeFiles/http.dir/src/http_get_line.o.requires
CMakeFiles/http.dir/requires: CMakeFiles/http.dir/src/http_recv_msg.o.requires
CMakeFiles/http.dir/requires: CMakeFiles/http.dir/src/http_event_accept.o.requires
CMakeFiles/http.dir/requires: CMakeFiles/http.dir/src/http_send_file.o.requires
CMakeFiles/http.dir/requires: CMakeFiles/http.dir/src/http_get_type.o.requires
CMakeFiles/http.dir/requires: CMakeFiles/http.dir/src/http_send_msg.o.requires
CMakeFiles/http.dir/requires: CMakeFiles/http.dir/src/http_create_msg.o.requires
CMakeFiles/http.dir/requires: CMakeFiles/http.dir/src/http_response.o.requires
.PHONY : CMakeFiles/http.dir/requires

CMakeFiles/http.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/http.dir/cmake_clean.cmake
.PHONY : CMakeFiles/http.dir/clean

CMakeFiles/http.dir/depend:
	cd /home/lpc/server/cserver && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lpc/server/cserver /home/lpc/server/cserver /home/lpc/server/cserver /home/lpc/server/cserver /home/lpc/server/cserver/CMakeFiles/http.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/http.dir/depend

