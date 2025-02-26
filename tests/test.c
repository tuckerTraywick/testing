#include "testing.h"

void test1(void) {
	assertNeNString("abcdef", "abc123", 3);
}

int main(void) {
	output = stdout;
	beginTesting();
		runTest(test1);
	endTesting();
	return 0;
}
