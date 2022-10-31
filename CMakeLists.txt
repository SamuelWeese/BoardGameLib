cmake_minimum_required(VERSION 3.5)

project(BoardGameLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug
    CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

find_package(SFML 2.5
  COMPONENTS
    system window graphics network audio REQUIRED)

set( PROJECT_CPP_SOURCES
  main.cpp
  boardtile.cpp
  board.cpp
  piece.cpp
  )

set ( TEMP_CPP_TESTING_SOURCES
  chess.cpp
  )


add_executable(${PROJECT_NAME} ${PROJECT_CPP_SOURCES} ${TEMP_CPP_TESTING_SOURCES})
target_link_libraries(
 BoardGameLib
 sfml-graphics
)
