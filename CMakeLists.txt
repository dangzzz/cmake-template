cmake_minimum_required(VERSION 3.10)
cmake_policy(VERSION 3.10)
project(amap)

#SET(CMAKE_BUILD_TYPE "DEBUG")
SET(CMAKE_C_FLAGS_DEBUG "-DTEMPLATEDEBUG -O0 -g3 -Wall")
SET(CMAKE_C_FLAGS_RELEASE " -O3 -fno-omit-frame-pointer -fPIC")


#make时显式输出执行的命令
set(CMAKE_VERBOSE_MAKEFILE ON)

#指定库的输出位置
set (LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/lib)

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/bin)

#添加头文件搜索目录,相当于-I
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

#将src目录下所有的源文件加入列表lsmalloc_src中
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src ${CMAKE_PROJECT_NAME}_src)

#添加目标静态库文件lsmalloc_static,生成所用的源文件是lsmalloc_src
add_library(${CMAKE_PROJECT_NAME}_static STATIC ${${CMAKE_PROJECT_NAME}_src})

#为lsmalloc_static添加编译器flag
target_compile_options(${CMAKE_PROJECT_NAME}_static PRIVATE -g3 -Wall -pipe -funroll-loops -O0 -D_GNU_SOURCE -D_REENTRANT)

#设置lsmalloc_static输出时叫lsmalloc
set_target_properties(${CMAKE_PROJECT_NAME}_static PROPERTIES OUTPUT_NAME "${CMAKE_PROJECT_NAME}")

#下面是测试的自动生成
enable_testing()

#只需要在下面一行加入你测试文件的文件名就可以了,测试文件要放在test/src/
set(testsource )
string(APPEND testsource $ENV{testsource})

list(LENGTH testsource testsourcelength)
math(EXPR testsourcelength "${testsourcelength}-1")

if(NOT ${testsource} MATCHES "NOTFOUND")
list(LENGTH testsource testsourcelength)
math(EXPR testsourcelength "${testsourcelength}-1")


foreach(i  RANGE ${testsourcelength})
list(GET testsource ${i} testsourcename)
string(REGEX REPLACE "\\.[^.]*$" "" testname ${testsourcename})
message("-- add test ${testname}")
add_executable(${testname} ${CMAKE_CURRENT_LIST_DIR}/test/src/${testsourcename})
target_compile_options(${testname} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-std=c++11> -g3 -Wall -O0 -D_GNU_SOURCE -D_REENTRANT)
target_link_libraries(${testname} ${CMAKE_PROJECT_NAME}_static)
add_test(${testname} ${EXECUTABLE_OUTPUT_PATH}/${testname})
endforeach(i)
endif()
