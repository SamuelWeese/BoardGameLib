cmake_minimum_required(VERSION 3.5)

project(BoardGameLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread") # boost flag

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug
    CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

find_package(SFML 2.5
  COMPONENTS
    system window graphics network audio REQUIRED
    )
find_package( Boost 1.40 COMPONENTS program_options REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )

set( PROJECT_CPP_SOURCES
  boardtile.cpp
  board.cpp
  piece.cpp
  )

set ( TEMP_CPP_TESTING_SOURCES
  main.cpp
  chess.cpp
  )

add_executable(${PROJECT_NAME} ${PROJECT_CPP_SOURCES} ${TEMP_CPP_TESTING_SOURCES})

target_link_libraries(
 ${PROJECT_NAME}
 LINK_PUBLIC
 sfml-graphics
 ${Boost_LIBRARIES}
)


# Copy <filename> to build directory

set(copy_source_dir "${CMAKE_SOURCE_DIR}/resources/")
set(copy_dest_dir "/tmp/")
set(copy_file_name "*.png")

#add_custom_command(
#    TARGET ${PROJECT_NAME} POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E make_directory ${copy_dest_dir}
#)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${copy_source_dir}/${copy_file_name}" "${copy_dest_dir}/${copy_file_name}"
    COMMENT "Copying ${copy_file_name} to tmp directory"
)


