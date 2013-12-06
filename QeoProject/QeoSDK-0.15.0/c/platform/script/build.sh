#!/bin/bash
#Platform integrators: adapt this script to your own needs

set -e
SELF_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $SELF_DIR
platform_PATH_SRC=../src/qeo/
platform_PATH_INC=../include/
ARCH=`uname -m`
if [[ $ARCH == "arm"* ]]; then
    EXTRA_CFLAGS=""
else
    EXTRA_CFLAGS="-m32"
fi
gcc $EXTRA_CFLAGS -Wall -Werror -O0 -g -shared -I${platform_PATH_INC} -fPIC -o libqeoutil.so  ${platform_PATH_SRC}/*.c

echo "libqeoutil.so was successfully built !"
cd -

