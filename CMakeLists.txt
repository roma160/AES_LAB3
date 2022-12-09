cmake_minimum_required(VERSION 3.15)
project(LAB3_AES VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

file("GLOB" "SOURCE_FILES" "*.cpp")
message(INFO ${SOURCE_FILES})
add_executable(main ${SOURCE_FILES})
target_include_directories(main PUBLIC "./")

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/program.txt" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(UNIX)
	target_link_libraries(main ncurses)
endif(UNIX)