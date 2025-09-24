cmake_minimum_required(VERSION 3.14)
project(PersonalFinanceTracker)

# Compiler settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra)

#Google Test setup
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

# Find all source files except main.cpp
file(GLOB SOURCES "*.cpp")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

# Create library from source
add_library(finance_lib ${SOURCES})

# Main executable
add_executable(finance main.cpp)
target_link_libraries(finance finance_lib)

# Test executable
file(GLOB_RECURSE TEST_SOURCES "tests/**/*.cpp")
if(TEST_SOURCES)
    add_executable(tests ${TEST_SOURCES})
    target_link_libraries(tests finance_lib gtest_main)
    
    # Enable testing
    enable_testing()
    include(GoogleTest)
    gtest_discover_tests(tests)
endif()
