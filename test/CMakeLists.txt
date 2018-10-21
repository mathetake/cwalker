cmake_minimum_required(VERSION 3.12)

include(${PROJECT_SOURCE_DIR}/cmake/DownloadProject/DownloadProject.cmake)
download_project(PROJ googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG master
        UPDATE_DISCONNECTED 1
        )

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

add_executable(TestWalker walker_test.cpp)
target_link_libraries(TestWalker CWalker gtest_main)

include_directories(${PROJECT_SOURCE_DIR}/src)
include(GoogleTest)
gtest_add_tests(TARGET TestWalker)