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
CMAKE_SOURCE_DIR = /home/griffin/Documents/gr-ntsc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/griffin/Documents/gr-ntsc/build

# Include any dependencies generated for this target.
include lib/CMakeFiles/gnuradio-ntsc.dir/depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/gnuradio-ntsc.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/gnuradio-ntsc.dir/flags.make

lib/CMakeFiles/gnuradio-ntsc.dir/encntsc.cpp.o: lib/CMakeFiles/gnuradio-ntsc.dir/flags.make
lib/CMakeFiles/gnuradio-ntsc.dir/encntsc.cpp.o: ../lib/encntsc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/griffin/Documents/gr-ntsc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/gnuradio-ntsc.dir/encntsc.cpp.o"
	cd /home/griffin/Documents/gr-ntsc/build/lib && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gnuradio-ntsc.dir/encntsc.cpp.o -c /home/griffin/Documents/gr-ntsc/lib/encntsc.cpp

lib/CMakeFiles/gnuradio-ntsc.dir/encntsc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gnuradio-ntsc.dir/encntsc.cpp.i"
	cd /home/griffin/Documents/gr-ntsc/build/lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/griffin/Documents/gr-ntsc/lib/encntsc.cpp > CMakeFiles/gnuradio-ntsc.dir/encntsc.cpp.i

lib/CMakeFiles/gnuradio-ntsc.dir/encntsc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gnuradio-ntsc.dir/encntsc.cpp.s"
	cd /home/griffin/Documents/gr-ntsc/build/lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/griffin/Documents/gr-ntsc/lib/encntsc.cpp -o CMakeFiles/gnuradio-ntsc.dir/encntsc.cpp.s

lib/CMakeFiles/gnuradio-ntsc.dir/encntsc.cpp.o.requires:

.PHONY : lib/CMakeFiles/gnuradio-ntsc.dir/encntsc.cpp.o.requires

lib/CMakeFiles/gnuradio-ntsc.dir/encntsc.cpp.o.provides: lib/CMakeFiles/gnuradio-ntsc.dir/encntsc.cpp.o.requires
	$(MAKE) -f lib/CMakeFiles/gnuradio-ntsc.dir/build.make lib/CMakeFiles/gnuradio-ntsc.dir/encntsc.cpp.o.provides.build
.PHONY : lib/CMakeFiles/gnuradio-ntsc.dir/encntsc.cpp.o.provides

lib/CMakeFiles/gnuradio-ntsc.dir/encntsc.cpp.o.provides.build: lib/CMakeFiles/gnuradio-ntsc.dir/encntsc.cpp.o


lib/CMakeFiles/gnuradio-ntsc.dir/encoder_impl.cc.o: lib/CMakeFiles/gnuradio-ntsc.dir/flags.make
lib/CMakeFiles/gnuradio-ntsc.dir/encoder_impl.cc.o: ../lib/encoder_impl.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/griffin/Documents/gr-ntsc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/CMakeFiles/gnuradio-ntsc.dir/encoder_impl.cc.o"
	cd /home/griffin/Documents/gr-ntsc/build/lib && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gnuradio-ntsc.dir/encoder_impl.cc.o -c /home/griffin/Documents/gr-ntsc/lib/encoder_impl.cc

lib/CMakeFiles/gnuradio-ntsc.dir/encoder_impl.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gnuradio-ntsc.dir/encoder_impl.cc.i"
	cd /home/griffin/Documents/gr-ntsc/build/lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/griffin/Documents/gr-ntsc/lib/encoder_impl.cc > CMakeFiles/gnuradio-ntsc.dir/encoder_impl.cc.i

lib/CMakeFiles/gnuradio-ntsc.dir/encoder_impl.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gnuradio-ntsc.dir/encoder_impl.cc.s"
	cd /home/griffin/Documents/gr-ntsc/build/lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/griffin/Documents/gr-ntsc/lib/encoder_impl.cc -o CMakeFiles/gnuradio-ntsc.dir/encoder_impl.cc.s

lib/CMakeFiles/gnuradio-ntsc.dir/encoder_impl.cc.o.requires:

.PHONY : lib/CMakeFiles/gnuradio-ntsc.dir/encoder_impl.cc.o.requires

lib/CMakeFiles/gnuradio-ntsc.dir/encoder_impl.cc.o.provides: lib/CMakeFiles/gnuradio-ntsc.dir/encoder_impl.cc.o.requires
	$(MAKE) -f lib/CMakeFiles/gnuradio-ntsc.dir/build.make lib/CMakeFiles/gnuradio-ntsc.dir/encoder_impl.cc.o.provides.build
.PHONY : lib/CMakeFiles/gnuradio-ntsc.dir/encoder_impl.cc.o.provides

lib/CMakeFiles/gnuradio-ntsc.dir/encoder_impl.cc.o.provides.build: lib/CMakeFiles/gnuradio-ntsc.dir/encoder_impl.cc.o


# Object files for target gnuradio-ntsc
gnuradio__ntsc_OBJECTS = \
"CMakeFiles/gnuradio-ntsc.dir/encntsc.cpp.o" \
"CMakeFiles/gnuradio-ntsc.dir/encoder_impl.cc.o"

# External object files for target gnuradio-ntsc
gnuradio__ntsc_EXTERNAL_OBJECTS =

lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: lib/CMakeFiles/gnuradio-ntsc.dir/encntsc.cpp.o
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: lib/CMakeFiles/gnuradio-ntsc.dir/encoder_impl.cc.o
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: lib/CMakeFiles/gnuradio-ntsc.dir/build.make
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/lib/x86_64-linux-gnu/libboost_system.so
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /home/griffin/gnuradio/lib/libgnuradio-runtime.so
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /home/griffin/gnuradio/lib/libgnuradio-pmt.so
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_cudabgsegm.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_cudaobjdetect.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_cudastereo.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_shape.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_stitching.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_superres.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_videostab.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_viz.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_cudafeatures2d.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_cudacodec.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_cudaoptflow.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_cudalegacy.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_calib3d.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_cudawarping.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_features2d.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_flann.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_objdetect.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_highgui.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_ml.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_photo.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_cudaimgproc.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_cudafilters.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_cudaarithm.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_video.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_videoio.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_imgcodecs.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_imgproc.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_core.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: /usr/local/lib/libopencv_cudev.so.3.2.0
lib/libgnuradio-ntsc-1.0.0git.so.0.0.0: lib/CMakeFiles/gnuradio-ntsc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/griffin/Documents/gr-ntsc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library libgnuradio-ntsc-1.0.0git.so"
	cd /home/griffin/Documents/gr-ntsc/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gnuradio-ntsc.dir/link.txt --verbose=$(VERBOSE)
	cd /home/griffin/Documents/gr-ntsc/build/lib && $(CMAKE_COMMAND) -E cmake_symlink_library libgnuradio-ntsc-1.0.0git.so.0.0.0 libgnuradio-ntsc-1.0.0git.so.0.0.0 libgnuradio-ntsc-1.0.0git.so
	cd /home/griffin/Documents/gr-ntsc/build/lib && /usr/bin/cmake -E create_symlink libgnuradio-ntsc-1.0.0git.so.0.0.0 /home/griffin/Documents/gr-ntsc/build/lib/libgnuradio-ntsc.so
	cd /home/griffin/Documents/gr-ntsc/build/lib && /usr/bin/cmake -E create_symlink libgnuradio-ntsc-1.0.0git.so.0.0.0 /home/griffin/Documents/gr-ntsc/build/lib/libgnuradio-ntsc-1.0.0git.so.0
	cd /home/griffin/Documents/gr-ntsc/build/lib && /usr/bin/cmake -E touch libgnuradio-ntsc-1.0.0git.so.0.0.0

lib/libgnuradio-ntsc-1.0.0git.so: lib/libgnuradio-ntsc-1.0.0git.so.0.0.0
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libgnuradio-ntsc-1.0.0git.so

# Rule to build all files generated by this target.
lib/CMakeFiles/gnuradio-ntsc.dir/build: lib/libgnuradio-ntsc-1.0.0git.so

.PHONY : lib/CMakeFiles/gnuradio-ntsc.dir/build

lib/CMakeFiles/gnuradio-ntsc.dir/requires: lib/CMakeFiles/gnuradio-ntsc.dir/encntsc.cpp.o.requires
lib/CMakeFiles/gnuradio-ntsc.dir/requires: lib/CMakeFiles/gnuradio-ntsc.dir/encoder_impl.cc.o.requires

.PHONY : lib/CMakeFiles/gnuradio-ntsc.dir/requires

lib/CMakeFiles/gnuradio-ntsc.dir/clean:
	cd /home/griffin/Documents/gr-ntsc/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/gnuradio-ntsc.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/gnuradio-ntsc.dir/clean

lib/CMakeFiles/gnuradio-ntsc.dir/depend:
	cd /home/griffin/Documents/gr-ntsc/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/griffin/Documents/gr-ntsc /home/griffin/Documents/gr-ntsc/lib /home/griffin/Documents/gr-ntsc/build /home/griffin/Documents/gr-ntsc/build/lib /home/griffin/Documents/gr-ntsc/build/lib/CMakeFiles/gnuradio-ntsc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/gnuradio-ntsc.dir/depend

