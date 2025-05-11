# Set the LOADBALANCER_SOURCES variable to the list of all source files in the current directory
set(
    LOADBALANCER_SOURCES 
    loadBalancer.cpp
)

# Tell CMake to create an executable named 'loadBalancer' from the source files
add_executable(loadBalancer ${LOADBALANCER_SOURCES})

# Ensure that the cxxopts and common libraries are linked to the loadBalancer executable
target_link_libraries(loadBalancer PRIVATE cxxopts::cxxopts common spdlog::spdlog pugixml::pugixml Boost::regex)

# Include the common directory for headers (e.g. LoadBalancerProtocol.h)
target_include_directories(loadBalancer PRIVATE ${PROJECT_SOURCE_DIR}/common)
