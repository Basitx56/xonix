cmake_minimum_required(VERSION 3.10)
project(Xonix)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML package
find_package(SFML 2.5 REQUIRED network audio graphics window system)

# Copy images and fonts to build directory
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/images" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Fonts" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")

# Add executable
add_executable(xonix main.cpp Menu.cpp)

# Link SFML libraries
target_link_libraries(xonix PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)