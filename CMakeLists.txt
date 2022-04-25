cmake_minimum_required(VERSION 3.12)
SET(COVERAGE OFF CACHE BOOL "Coverage")

project(tests)
set(CMAKE_CXX_STANDART 17)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/gtest)

add_executable(${PROJECT_NAME} test.cpp)

if(COVERAGE)
    target_compile_options(${PROJECT_NAME} PRIVATE --coverage)
    target_link_libraries(${PROJECT_NAME} PRIVATE  --coverage)
endif()
add_library(banking STATIC
           ${CMAKE_CURRENT_SOURCE_DIR}/banking/Account.cpp
           ${CMAKE_CURRENT_SOURCE_DIR}/banking/Transaction.cpp

)

target_include_directories(${PROJECT_NAME} PRIVATE
                        ${CMAKE_CURRENT_SOURCE_DIR}/banking)

target_link_libraries(${PROJECT_NAME} PRIVATE banking gtest gtest_main gmock_main) 
