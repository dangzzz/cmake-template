#!/bin/bash

debugtype="DEBUG"

testtype=""

if [ "$1" == "d" ]
then
    debugtype="DEBUG"
    echo $debugtype
fi

if [ "$1" == "r" ]
then
    debugtype="RELEASE"
    echo $debugtype
fi



if [ "$2" != "" ]
then
    testtype=$2
    echo $testtype
fi

export testsource=$testtype

#git clean -f -d -x
#rm -rf /mnt/pmem/dz*
rm -rf bin
rm -rf lib
cmake CMakeLists.txt -DCMAKE_BUILD_TYPE=$debugtype
make