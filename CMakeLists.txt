cmake_minimum_required(VERSION 3.12)

project(tests)
set(CMAKE_CXX_STANDART 17)

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

