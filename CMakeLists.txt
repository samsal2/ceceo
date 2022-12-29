cmake_minimum_required(VERSION 3.23.1)

project(ceceo)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# declare the library 
add_executable(${PROJECT_NAME})

# features
set_target_properties(${PROJECT_NAME}
    PROPERTIES 
        CXX_STANDARD          20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS        OFF)

# add sources
add_subdirectory(${PROJECT_NAME})

# includes
target_include_directories(${PROJECT_NAME} 
  PRIVATE ${CMAKE_SOURCE_DIR})

# compile options
target_compile_options(${PROJECT_NAME} PUBLIC
	"$<$<COMPILE_LANG_AND_ID:CXX,Clang,AppleClang>:"
    -std=c++20
		-Wall
		-Wshadow
		-Wextra
		-Werror
		-Wpedantic
		-pedantic-errors
		-Walloca 
		-Wvla 
    -fdiagnostics-color=always
  ">"
	"$<$<AND:$<COMPILE_LANG_AND_ID:CXX,Clang,AppleClang>,$<CONFIG:Debug>>:"
		-O0
		-g
		-fsanitize=address
		-fsanitize=undefined
		-fsanitize=bounds
  ">"
	"$<$<AND:$<COMPILE_LANG_AND_ID:CXX,Clang,AppleClang>,$<CONFIG:Release>>:"
		-Ofast
  ">")

# link options
target_link_options(${PROJECT_NAME} PUBLIC
	"$<$<AND:$<COMPILE_LANG_AND_ID:CXX,Clang,AppleClang>,$<CONFIG:Debug>>:"
		-fsanitize=address
		-fsanitize=undefined
		-fsanitize=bounds
  ">")

