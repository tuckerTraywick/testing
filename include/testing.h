#ifndef TESTING_H
#define TESTING_H

#include <stdio.h>

#define runTest(test) (runTestImpl((test), #test))

typedef void (*TestCase)(void);

FILE *testOutput;
FILE *errorOutput;

unsigned int testsRun;
unsigned int testsPassed;
unsigned int testsFailed;
unsigned int assertionsRun;
unsigned int assertionsPassed;
unsigned int assertionsFailed;

void beginTesting(void);

void endTesting(void);

void runTestImpl(TestCase test, char *name);

#endif // TESTING_H
