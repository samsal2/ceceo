cmake_minimum_required(VERSION 3.17.3)

project(ceceo)

# C options
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CXX_STANDARD_REQUIRED ON)

# Misc
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add library
add_executable(${PROJECT_NAME} ceceo/main.cpp)

# add library sources
add_subdirectory(${PROJECT_NAME})

# include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})

set(OTTER_CXX_CLANG_BASE_COMPILE_FLAGS 
		-Wall
		-Wshadow
		-Wextra
		-Werror
		-Wpedantic
		-pedantic-errors
		-Walloca 
		-Wcast-qual 
		-Wconversion 
		-Wformat=2 
		-Wformat-security 
		-Wnull-dereference 
		-Wstack-protector 
		-Wstrict-overflow=3 
		-Wvla 
		-Warray-bounds 
		-Warray-bounds-pointer-arithmetic 
		-Wassign-enum 
		-Wbad-function-cast 
		-Wconditional-uninitialized 
		-Wconversion 
		-Wfloat-equal 
		-Wformat-type-confusion 
		-Widiomatic-parentheses 
		-Wimplicit-fallthrough 
		-Wloop-analysis 
		-Wpointer-arith 
		-Wshift-sign-overflow 
		-Wshorten-64-to-32 
		-Wswitch-enum 
		-Wtautological-constant-in-range-compare 
		-Wunreachable-code-aggressive)


set(OTTER_CXX_CLANG_DEBUG_COMPILE_FLAGS
		-O0
		-g
		-fsanitize=address
		-fsanitize=undefined
		-fsanitize=bounds)

set(OTTER_CXX_CLANG_RELEASE_COMPILE_FLAGS
		-O3)

set(OTTER_CXX_CLANG_DEBUG_LINK_FLAGS
		-fsanitize=address
		-fsanitize=undefined
		-fsanitize=bounds)
		
target_compile_options(${PROJECT_NAME} PRIVATE
	"$<$<CXX_COMPILER_ID:Clang,AppleClang>:${OTTER_CXX_CLANG_BASE_COMPILE_FLAGS}>"
	"$<$<AND:$<CXX_COMPILER_ID:Clang,AppleClang>,$<CONFIG:Debug>>:${OTTER_CXX_CLANG_DEBUG_COMPILE_FLAGS}>"
	"$<$<AND:$<CXX_COMPILER_ID:Clang,AppleClang>,$<CONFIG:Release>>:${OTTER_CXX_CLANG_RELEASE_COMPILE_FLAGS}>")

target_link_options(${PROJECT_NAME} PUBLIC
	"$<$<AND:$<CXX_COMPILER_ID:Clang,AppleClang>,$<CONFIG:Debug>>:${OTTER_CXX_CLANG_DEBUG_LINK_FLAGS}>")
