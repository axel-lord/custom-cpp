cmake_minimum_required(VERSION 3.19.0)
project(cpp_tests VERSION 0.0.0)
include(CTest)
enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (MSVC)
	add_compile_options(/W4)
else()
	add_compile_options(-Wall -Wextra)
endif()

add_executable(
	twenty

	#source files
	"./src/main.cpp"

	#header files
	"./include/util/print.hpp"
	
	#template implementation files
	)

target_include_directories(twenty PUBLIC ./include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
