#ifndef TESTING_H
#define TESTING_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define runTest(test) (runTestImpl((test), #test))

#define assert(condition) (assertImpl((condition), (char*)__func__, __FILE__, __LINE__, #condition))

#define assertEqInt(a, b) (assertEqIntImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define assertEqUInt(a, b) (assertEqUIntImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define assertEqFloat(a, b) (assertEqFloatImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define assertEqString(a, b) (assertEqStringImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

typedef void (*TestCase)(void);

FILE *output;

void beginTesting(void);

void endTesting(void);

void runTestImpl(TestCase test, char *name);

void assertImpl(bool success, char *testName, char *fileName, unsigned int lineNumber, char *expression);

void assertEqIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void assertEqUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

#endif // TESTING_H
