# Project presets
#
# Configurure the server now as: "cmake <OPTIONS> <FLAGS>  .."
#
# Options:
#
# Flags:
#
# -DCMAKE_CXX_COMPILER= /usr/bin/g++
# -DCMAKE_INSTALL_PREFIX=/opt/phoenix
# -DCMAKE_BUILD_TYPE=debug | -DCMAKE_BUILD_TYPE=release

# Commons
PROJECT("Egg::CommandLine" CXX)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0 FATAL_ERROR)

# Describe project
SET ( PROJECT_VERSION_MAJOR	0				)
SET ( PROJECT_VERSION_MINOR	1				)
SET ( PROJECT_VERSION_PATCH	0				)
SET ( PROJECT_VERSION_TWEAK	1				)
SET ( PROJECT_VERSION		${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK} )

STRING( TIMESTAMP TODAY "%d/%m/%Y"					)

SET ( ABIMajor          1                                               )
SET ( ABIMinor          0                                               )
SET ( ABIPatch          0                                               )
SET ( ABIVersion        ${ABIMajor}.${ABIMinor}.${ABIPatch}             )

SET ( LibraryName	"egg-cmd"
	CACHE STRING	"Command line library ${PROJECT_VERSION}. ABI: ${ABIVersion}" FORCE )

SET ( Alias		"Go cat go"					)
SET ( Author		"Vladislav \\\"Tanuki\\\" Mikhailikov"		)
SET ( Copyright		"GNU GPLv3"					)
SET ( Description	"Egg (Linux daemon SDK) command line library"	)
SET ( SDKName		"EggSDK"					)

# Common build paramteres
OPTION ( BUILD_SHARED_LIBS    "Build shared libraries if ON or static if OFF" ON  )
OPTION ( BUILD_PKGCONFIG      "Generate pkgconfig configuration files"        ON  )
OPTION ( BUILD_TESTS          "Build tests"                                   OFF )

# Project directories
SET ( Project_Include_Dir     "${CMAKE_SOURCE_DIR}/include"   )
SET ( Project_Source_Dir      "${CMAKE_SOURCE_DIR}/source"    )

# Library search paths
SET ( LIBRARY_SEARCH_PATH "/lib"                              )
SET ( LIBRARY_SEARCH_PATH "${LIBRARY_SEARCH_PATH} /lib32"     )
SET ( LIBRARY_SEARCH_PATH "${LIBRARY_SEARCH_PATH} /lib64"     )
SET ( LIBRARY_SEARCH_PATH "${LIBRARY_SEARCH_PATH} /usr/lib"   )
SET ( LIBRARY_SEARCH_PATH "${LIBRARY_SEARCH_PATH} /usr/lib32" )
SET ( LIBRARY_SEARCH_PATH "${LIBRARY_SEARCH_PATH} /usr/lib64" )

# GNU install dirs
INCLUDE ( GNUInstallDirs )

# Load cmake script
INCLUDE ( ${CMAKE_INSTALL_FULL_DATAROOTDIR}/cmake/${SDKName}/egg-common.cmake )
IF ( NOT EggFound )
	MESSAGE ( ERROR "Egg::System script not found!" )
ENDIF ()

# Load cmake script
INCLUDE ( ${CMAKE_INSTALL_FULL_DATAROOTDIR}/cmake/${SDKName}/egg-variable.cmake )
IF ( NOT EggVariableIncludePath OR
     NOT EggVariableLibraryPath OR
     NOT EggVariableLibraryName )
  MESSAGE ( ERROR "Egg::Variable library not found!" )
ELSE ()
  FIND_LIBRARY (
    VARIABLE_LIBRARY
    ${EggVariableLibraryName}
    ${EggVariableLibraryPath} )
ENDIF ()

# Load cmake script
INCLUDE ( ${CMAKE_INSTALL_FULL_DATAROOTDIR}/cmake/${SDKName}/egg-registry.cmake )
IF ( NOT EggRegistryIncludePath OR
     NOT EggRegistryLibraryPath OR
     NOT EggRegistryLibraryName OR
     NOT EggRegistryFullLibraryName )
  MESSAGE ( ERROR "Egg::Registry library not found!" )
ELSE ()
  FIND_LIBRARY (
    REGISTRY_LIBRARY
    ${EggRegistryFullLibraryName}
    ${EggRegistryLibraryPath} )
ENDIF ()

# Includes
ADD_SUBDIRECTORY ( include )

# Sources
ADD_SUBDIRECTORY ( source )

# CMake scripts
CONFIGURE_FILE(
  egg-command-line.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/egg-command-line.cmake
  @ONLY )

INSTALL(
  FILES       ${CMAKE_CURRENT_BINARY_DIR}/egg-command-line.cmake
  DESTINATION ${CMAKE_INSTALL_FULL_DATAROOTDIR}/cmake/${SDKName} )

# PkgConfig
IF (BUILD_PKGCONFIG)

  CONFIGURE_FILE(
    egg-command-line.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/egg-command-line.pc
    @ONLY )

  INSTALL(
    FILES       ${CMAKE_CURRENT_BINARY_DIR}/egg-command-line.pc
    DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig )

ENDIF ()

# Tests
IF (BUILD_TESTS)
  ENABLE_TESTING()
  INCLUDE (CTest)
  ADD_SUBDIRECTORY ( test )
ENDIF ()

# End of file
