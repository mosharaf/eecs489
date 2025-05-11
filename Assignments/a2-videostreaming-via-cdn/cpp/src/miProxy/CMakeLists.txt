# Set the MIPROXY_SOURCES variable to the list of all source files in the current directory
set(
    MIPROXY_SOURCES 
    miproxy.cpp
)

# Tell CMake to create an executable named 'miProxy' from the source files
add_executable(miProxy ${MIPROXY_SOURCES})

# Ensure that the cxxopts and common libraries are linked to the miProxy executable
target_link_libraries(miProxy PRIVATE cxxopts::cxxopts common spdlog::spdlog pugixml::pugixml Boost::regex)

# Include the common directory for headers (e.g. LoadBalancerProtocol.h)
target_include_directories(miProxy PRIVATE ${PROJECT_SOURCE_DIR}/common)
