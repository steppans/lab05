cmake_minimum_required(VERSION 3.2)

project(tests)
set(CMAKE_CXX_STANDART 11)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletests)

add_executable(${PROJECT_NAME} tests.cpp)

add_library(banking STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/banking/Account.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/banking/Transaction.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
                      ${CMAKE_CURRENT_SOURCE_DIR}/banking
                      ${CMAKE_CURRENT_SOURCE_DIR}/googletests
                      )

target_link_libraries(${PROJECT_NAME} banking gtest gtest_main gmock_main)

#if(MSVC)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

	#	target_compile_options(
	#	${PROJECT_NAME} PRIVATE
	#	/W4
	#)
	#else()
	#target_compile_options(
	#	${PROJECT_NAME} PRIVATE
	#	-Wall -Wextra -pedantic -Werror
	#)
	#endif()
