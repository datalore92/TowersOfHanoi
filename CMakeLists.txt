cmake_minimum_required(VERSION 3.10)
project(TowersOfHanoi C)

# Find SDL2 packages
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Add executable
add_executable(hanoi main.c towers.c hanoi.c)

# Include directories
target_include_directories(hanoi PRIVATE 
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(hanoi PRIVATE 
    ${SDL2_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    SDL2_ttf  # Add explicit SDL2_ttf linkage
)
