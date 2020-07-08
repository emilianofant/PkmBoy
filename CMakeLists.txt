cmake_minimum_required(VERSION 3.0.0)

set (CMAKE_CXX_STANDARD 17)

project(pkmnboy)

# The Cmake find modules over win folder works finding SDL libraries
# both for Windows and Linux.
if (WIN32 OR UNIX)
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/win/")

  find_package(SDL2 REQUIRED)
  find_package(SDL2_image REQUIRED)
  find_package(SDL2_ttf REQUIRED)
endif (WIN32 OR UNIX)

# Specific CMAKE modules for macOS.
if (APPLE)
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/apple/")

  find_package(SDL2 REQUIRED)
  find_package(SDL2_image REQUIRED)
  find_package(SDL2_ttf REQUIRED)
endif (APPLE)

include_directories(include ${SDL2_INCLUDE_DIRS}
                            ${SDL2_IMAGE_INCLUDE_DIRS}
                            ${SDL2_TTF_INCLUDE_DIRS})

# Copy all assets (png, textures) to the output folder.
FILE(COPY assets DESTINATION "${CMAKE_BINARY_DIR}")

file(GLOB SOURCES "src/*.cpp")

add_executable(pkmnboy ${SOURCES})

target_link_libraries(pkmnboy ${SDL2_LIBRARIES}
                              ${SDL2_IMAGE_LIBRARIES}
                              ${SDL2_TTF_LIBRARIES})
