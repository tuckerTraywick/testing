#ifndef TESTING_H
#define TESTING_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define runTest(test) (runTestImpl((test), #test))

#define assert(condition) (assertImpl((condition), (char*)__func__, __FILE__, __LINE__, #condition))

#define assertEqInt(a, b) (assertEqIntImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define assertNeInt(a, b) (assertNeIntImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define assertGtInt(a, b) (assertGtIntImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define assertLtInt(a, b) (assertLtIntImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define assertGeInt(a, b) (assertGeIntImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define assertLeInt(a, b) (assertLeIntImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define assertEqUInt(a, b) (assertEqUIntImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define assertEqFloat(a, b) (assertEqFloatImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define assertEqString(a, b) (assertEqStringImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define assertNeString(a, b) (assertNeStringImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define assertEqNString(a, b, n) (assertNeNStringImpl((a), (b), (n), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define assertNeNString(a, b, n) (assertNeNStringImpl((a), (b), (n), (char*)__func__, __FILE__, __LINE__, #a, #b))

typedef void (*TestCase)(void);

// Must be set before testing.
extern FILE *output;

void beginTesting(void);

void endTesting(void);

void runTestImpl(TestCase test, char *name);

void assertImpl(bool success, char *testName, char *fileName, unsigned int lineNumber, char *expression);

void assertEqIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void assertNeIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void assertGtIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void assertLtIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void assertGeIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void assertLeIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void assertEqUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void assertNeUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void assertGtUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void assertLtUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void assertGeUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void assertLeUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void assertEqFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void assertNeFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void assertGtFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void assertLtFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void assertGeFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void assertLeFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void assertEqStringImpl(char *a, char *b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void assertNeStringImpl(char *a, char *b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void assertEqNStringImpl(char *a, char *b, size_t n, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void assertNeNStringImpl(char *a, char *b, size_t n, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

#endif // TESTING_H
