#/bin/sh
./build.sh $1

if [ $1 ]; then
	echo
	echo "---- TESTING ----"
	./binary/test
fi

echo
echo "---- RUNNING ----"
./binary/run
