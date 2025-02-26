#/bin/sh
flags="-O -g3 -std=c99 -Wall -Wextra -Wpedantic"
includes="-Iinclude"
libraries=
sourceCommand="clang $flags $includes $libraries build/source.c -c -o build/source.o"
testCommand="clang $flags $includes $libraries build/source.o build/test.c -o binary/test"

createUnit() {
	for file in $(find $1 -type f ! -name "main.c")
	do
		echo "#include \"../$file\""
	done
}

clear
echo "---- BUILDING ----"

# Cleanup.
mkdir -p build binary
rm -rf build/* binary/*

# Create the source compilation unit and executable.
createUnit source > build/source.c
echo $sourceCommand
eval $sourceCommand
clang build/source.o source/main.c -o binary/run

# Create the test compilation unit and executable.
if [ $1 ]; then
	createUnit tests > build/test.c
	echo
	echo $testCommand
	eval $testCommand
fi
