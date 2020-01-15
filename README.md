# Egg-CommandLine

This is the command line library required by the Egg project - the Linux 
daemon handy SDK. The command line library requires the Egg::System, 
Egg::Variable and Egg::Registry to be installed.

# How to build?

Configure and install commandline library for Egg (Linux daemon SDK):

  - pushd build

  - configure using cmake: "cmake OPTIONS ..", where the options are:

    * -DBUILD_TESTS=ON|OFF (Default: OFF)
    * -DBUILD_SHARED_LIBS=ON|OFF
    * -DBUILD_STATIC_LIBS=OFF|ON
    * -DCMAKE_INSTALL_PREFIX:PATH=<phoenix prefix>
    * -G"Eclipse CDT4 - Unix Makefiles" (to embed in Eclipse as the project)

  - Typical configuration:

    cmake \
        -DCMAKE_INSTALL_PREFIX:PATH=/opt/egg  \
	-DBUILD_SHARED_LIBS=ON \
	-DBUILD_STATIC_LIBS=OFF \
	-DBUILD_TESTS=ON \
        -G"Eclipse CDT4 - Unix Makefiles" \
        ..

  - Build and install: make && make install

  - Clean up: rm -rf ./*

  - popd
