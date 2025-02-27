#ifndef TESTING_H
#define TESTING_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define runTest(test) (runTestImpl((test), #test))

#define testAssert(condition) (testAssertImpl((condition), (char*)__func__, __FILE__, __LINE__, #condition))

#define testAssertEqInt(a, b) (testAssertEqIntImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define testAssertNeInt(a, b) (testAssertNeIntImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define testAssertGtInt(a, b) (testAssertGtIntImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define testAssertLtInt(a, b) (testAssertLtIntImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define testAssertGeInt(a, b) (testAssertGeIntImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define testAssertLeInt(a, b) (testAssertLeIntImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define testAssertEqUInt(a, b) (testAssertEqUIntImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define testAssertEqFloat(a, b) (testAssertEqFloatImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define testAssertEqString(a, b) (testAssertEqStringImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define testAssertNeString(a, b) (testAssertNeStringImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define testAssertEqNString(a, b, n) (testAssertNeNStringImpl((a), (b), (n), (char*)__func__, __FILE__, __LINE__, #a, #b))

#define testAssertNeNString(a, b, n) (testAssertNeNStringImpl((a), (b), (n), (char*)__func__, __FILE__, __LINE__, #a, #b))

typedef void (*TestCase)(void);

void beginTesting(void);

void endTesting(void);

void runTestImpl(TestCase test, char *name);

void testAssertImpl(bool success, char *testName, char *fileName, unsigned int lineNumber, char *expression);

void testAssertEqIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void testAssertNeIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void testAssertGtIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void testAssertLtIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void testAssertGeIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void testAssertLeIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void testAssertEqUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void testAssertNeUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void testAssertGtUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void testAssertLtUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void testAssertGeUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void testAssertLeUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void testAssertEqFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void testAssertNeFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void testAssertGtFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void testAssertLtFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void testAssertGeFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void testAssertLeFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void testAssertEqStringImpl(char *a, char *b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void testAssertNeStringImpl(char *a, char *b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void testAssertEqNStringImpl(char *a, char *b, size_t n, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

void testAssertNeNStringImpl(char *a, char *b, size_t n, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB);

#endif // TESTING_H
