# Define language
ENABLE_LANGUAGE ( CXX )

# Define includes
INCLUDE_DIRECTORIES (
  ${CMAKE_BINARY_DIR}/include
  ${CMAKE_INSTALL_FULL_INCLUDEDIR}
  ${EggVariableIncludePath}
  )

# Sources
SET (
  Sources

  "utility.cpp"
  "description.cpp"
  "option.cpp"
  "options.cpp"
  "processor.cpp"
)

# Shared library
IF ( BUILD_SHARED_LIBS )

  ADD_LIBRARY (
    ${LibraryName} SHARED
    ${Sources}
    ${Public_Include} )

  SET_TARGET_PROPERTIES (
    ${LibraryName}		PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY	"${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY	"${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY	"${CMAKE_BINARY_DIR}/bin"
    COMPILE_FLAGS		"${EggCxxFlags}"
    LINK_FLAGS			"${EggLdFlags}"
    VERSION			"${ABIVersion}"
    SOVERSION			"${ABIMajor}" )

ENDIF ()

# Static library
IF ( BUILD_STATIC_LIBS )

SET_TARGET_PROPERTIES (
  ${LibraryName}		PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY	"${CMAKE_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY	"${CMAKE_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY	"${CMAKE_BINARY_DIR}/bin"
  COMPILE_FLAGS			"${EggCxxFlags}" )

  ADD_LIBRARY (
    ${LibraryName}	STATIC
    ${Sources}
    ${PublicIncludes} )

ENDIF ()

# Libraries
TARGET_LINK_LIBRARIES ( ${LibraryName} "${VARIABLE_LIBRARY}" )
TARGET_LINK_LIBRARIES ( ${LibraryName} "${REGISTRY_LIBRARY}" )

# Install library
INSTALL (
  TARGETS     ${LibraryName} LIBRARY
  DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR} )

# End of file
