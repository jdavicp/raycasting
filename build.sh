#!/bin/sh

c_compiler="gcc-14 -std=c23"
c_flags="-Wall -Wextra -Werror -pedantic -c"
c_source_files=`ls ./src/*.c`
obj_dir="./build/obj"
bin_dir="./build/bin"
program="rayengine"

inc_deps="-I/home/jdavicp/workspace/build/libs/raylib-5.0/include"
lib_deps="-L/home/jdavicp/workspace/build/libs/raylib-5.0/lib"
link_deps="-l:libraylib.a -lm"

mkdir -p $obj_dir
mkdir -p $bin_dir

remove_c_extension() {
    local filename=`basename $1 .c`
    echo $filename
}
print_and_exit() {
    status=$?
    local msg=$1
    if [ $status -ne 0 ]
    then
        echo "-----------------------------------------------------------"
        echo $msg
        echo "-----------------------------------------------------------"
        exit
    fi
}

while getopts 'gh' opt; do
    case "$opt" in
        g)
            c_flags="${c_flags} -g"
            ;;
        ?|h)
            echo "Usage: $(basename $0) [-g]"
            exit 1
            ;;
    esac
done
shift "$(($OPTIND -1))"

echo "------------------------ compiling ------------------------"

for file in $c_source_files
do
    objfile="$(remove_c_extension $file)"
    echo "$c_compiler $c_flags $inc_deps -o $obj_dir/$objfile.o $file"
    $c_compiler $c_flags $inc_deps $lib_deps -o $obj_dir/$objfile.o $file
    print_and_exit "can't compile"
done

echo "-----------------------------------------------------------"

echo "------------------------  linking  ------------------------"

obj_files=`ls ./build/obj/*.o | tr '\n' ' '`
echo "$c_compiler $lib_deps -o $bin_dir/$program $obj_files $link_deps"

$c_compiler $lib_deps -o $bin_dir/$program $obj_files $link_deps
print_and_exit "Can't linking files"

echo "-----------------------------------------------------------"

echo "------------------------ finished  ------------------------"
echo "you can now run: $bin_dir/$program"
