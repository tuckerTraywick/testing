#include "testing.h"

void test1(void) {
	assert(1 == 2);
	*(char*)123 = 1;
	assert(1 == 1);
}

void test2(void) {
	assert(1 == 2);
}

int main(void) {
	output = stdout;
	beginTesting();
		runTest(test1);
		runTest(test2);
	endTesting();
	return 0;
}
