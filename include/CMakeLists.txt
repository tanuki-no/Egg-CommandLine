# Public headers

# Copy Egg::CommandLine library includes
FILE (
	COPY "${CMAKE_CURRENT_SOURCE_DIR}/egg/commandline/description.hpp"
	DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/egg/commandline" )

FILE (
	COPY "${CMAKE_CURRENT_SOURCE_DIR}/egg/commandline/option.hpp"
	DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/egg/commandline" )

FILE (
	COPY "${CMAKE_CURRENT_SOURCE_DIR}/egg/commandline/options.hpp"
	DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/egg/commandline" )

FILE (
	COPY "${CMAKE_CURRENT_SOURCE_DIR}/egg/commandline/processor.hpp"
	DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/egg/commandline" )

FILE (
	COPY "${CMAKE_CURRENT_SOURCE_DIR}/egg/commandline/utility.hpp"
	DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/egg/commandline" )

# Egg public includes
SET (
  Public_Include

  "${CMAKE_CURRENT_BINARY_DIR}/egg/commandline/description.hpp"
  "${CMAKE_CURRENT_BINARY_DIR}/egg/commandline/option.hpp"
  "${CMAKE_CURRENT_BINARY_DIR}/egg/commandline/options.hpp"
  "${CMAKE_CURRENT_BINARY_DIR}/egg/commandline/processor.hpp"

  CACHE INTERNAL "Common headers" )


# Install the Egg::CommandLine library
INSTALL(
  FILES       ${Public_Include}
  DESTINATION "${CMAKE_INSTALL_FULL_INCLUDEDIR}/egg/commandline" )

# End of file
