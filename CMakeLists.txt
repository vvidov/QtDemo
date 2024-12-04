cmake_minimum_required(VERSION 3.16)
project(ThreadsExample VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Debug configuration
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -O0")
set(CMAKE_VERBOSE_MAKEFILE ON)

# Windows-specific settings
if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    # Assuming Qt is installed in the default location
    set(CMAKE_PREFIX_PATH "C:/Qt/6.6.1/msvc2019_64")
endif()

# Find Qt packages
find_package(Qt6 REQUIRED COMPONENTS Core)

# Enable testing
enable_testing()
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add library
add_library(threadslib SHARED
    src/sharedresource.h
    src/sharedresource.cpp
    src/threadworker.h
    src/threadworker.cpp
)

target_link_libraries(threadslib PUBLIC Qt6::Core)
target_include_directories(threadslib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add tests
add_executable(threads_test
    tests/thread_test.cpp
)

target_link_libraries(threads_test
    PRIVATE
    threadslib
    GTest::gtest_main
    Qt6::Core
)

include(GoogleTest)
gtest_discover_tests(threads_test)

# Install rules
install(TARGETS threadslib
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
