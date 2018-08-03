cmake_minimum_required(VERSION 3.10.0)

if(EXISTS test/gtest/src/gtest-all.cc)
else()
	execute_process(COMMAND mkdir test/gtest)
	execute_process(COMMAND wget https://github.com/google/googletest/archive/release-1.8.0.tar.gz -O test/gtest/googletest.tar.gz)
	execute_process(COMMAND tar -xvf test/gtest/googletest.tar.gz -C test/gtest/)
	execute_process(COMMAND mv test/gtest/googletest-release-1.8.0/googletest/src test/gtest/src)
	execute_process(COMMAND mv test/gtest/googletest-release-1.8.0/googletest/include test/gtest/include)
endif()

project(robotTests)
add_library(gtest test/gtest/src/gtest-all.cc)
target_include_directories(gtest PUBLIC test test/gtest test/gtest/include)
target_compile_options(gtest PUBLIC -pthread)
target_link_libraries(gtest pthread)

add_executable(testDriver test/testDriver.cpp)
target_link_libraries(testDriver gtest)
