#include <stdio.h>
#include "logging.h"
#include "testing.h"

void test1(void) {
	
}

int main(void) {
	testOutput = errorOutput = stdout;
	beginTesting();
		runTest(test1);
	endTesting();
	return 0;
}
