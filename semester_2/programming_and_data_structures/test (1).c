#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rand_malloc.h"

typedef struct {
	char** strings;
	size_t size;
	size_t capacity;
} BinaryArray;

static void initializeBinaryArray(BinaryArray* array);
static void freeBinaryArray(BinaryArray* array);
static char* readInputLine(void);
static char* trimWhitespace(char* str);
static int isValidBinaryString(const char* str);
static void appendStringToBinaryArray(BinaryArray* array, char* string);
static void cleanupOnAllocationFailure(BinaryArray* array, char* sumString,
									   char* inputBuffer);
static int processInput(BinaryArray* array);
static char* addBinaryStrings(const char* a, const char* b);
static char* computeTotalSum(BinaryArray* array);
static void printResults(BinaryArray* array, const char* totalSum);

int main(void)
{
	BinaryArray binaryArray;
	initializeBinaryArray(&binaryArray);

	if (!processInput(&binaryArray)) {
		freeBinaryArray(&binaryArray);
		return EXIT_FAILURE;
	}

	char* totalSumString = computeTotalSum(&binaryArray);
	if (!totalSumString) {
		freeBinaryArray(&binaryArray);
		return EXIT_FAILURE;
	}

	printResults(&binaryArray, totalSumString);

	free(totalSumString);
	freeBinaryArray(&binaryArray);
	return EXIT_SUCCESS;
}

static void initializeBinaryArray(BinaryArray* array)
{
	array->strings = NULL;
	array->size = 0;
	array->capacity = 0;
}

static void freeBinaryArray(BinaryArray* array)
{
	if (!array->strings)
		return;
	for (size_t i = 0; i < array->size; i++) {
		free(array->strings[i]);
	}
	free(array->strings);
	array->strings = NULL;
	array->size = array->capacity = 0;
}

static char* readInputLine(void)
{
	size_t capacity = 1, length = 0;
	char* buffer = malloc(capacity);
	if (!buffer) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	int c;
	while ((c = getchar()) != EOF && c != '\n') {
		if (length + 1 >= capacity) {
			capacity *= 2;
			char* newBuffer = realloc(buffer, capacity);
			if (!newBuffer) {
				free(buffer);
				fprintf(stderr, "Memory allocation failed\n");
				exit(EXIT_FAILURE);
			}
			buffer = newBuffer;
		}
		buffer[length++] = c;
	}
	if (c == EOF && length == 0) {
		free(buffer);
		return NULL;
	}
	buffer[length] = '\0';
	return buffer;
}

static char* trimWhitespace(char* str)
{
	char* start = str;
	while (*start && isspace((unsigned char)*start))
		start++;
	char* end = start + strlen(start);
	while (end > start && isspace((unsigned char)*(end - 1)))
		end--;
	*end = '\0';
	return start;
}

static int isValidBinaryString(const char* str)
{
	for (size_t i = 0; str[i]; i++) {
		if (str[i] != '0' && str[i] != '1')
			return 0;
	}
	return 1;
}

static void appendStringToBinaryArray(BinaryArray* array, char* string)
{
	if (array->size == array->capacity) {
		size_t newCapacity = array->capacity ? array->capacity * 2 : 1;
		char** newMemory =
			realloc(array->strings, newCapacity * sizeof *newMemory);
		if (!newMemory) {
			free(string);
			fprintf(stderr, "Memory allocation failed\n");
			exit(EXIT_FAILURE);
		}
		array->strings = newMemory;
		array->capacity = newCapacity;
	}
	array->strings[array->size++] = string;
}

static void cleanupOnAllocationFailure(BinaryArray* array, char* sumString,
									   char* inputBuffer)
{
	freeBinaryArray(array);
	if (sumString)
		free(sumString);
	if (inputBuffer)
		free(inputBuffer);
	fprintf(stderr, "Memory allocation failed\n");
	exit(EXIT_FAILURE);
}

static int processInput(BinaryArray* array)
{
	char* inputBuffer;
	while ((inputBuffer = readInputLine()) != NULL) {
		char* trimmed = trimWhitespace(inputBuffer);
		if (*trimmed == '\0') {
			free(inputBuffer);
			continue;
		}
		if (!isValidBinaryString(trimmed)) {
			fprintf(stderr, "Error: invalid input format\n");
			free(inputBuffer);
			return 0;
		}
		size_t length = strlen(trimmed);
		char* binaryString = malloc(length + 1);
		if (!binaryString)
			cleanupOnAllocationFailure(array, NULL, inputBuffer);
		strcpy(binaryString, trimmed);
		free(inputBuffer);
		appendStringToBinaryArray(array, binaryString);
	}
	return 1;
}

static char* addBinaryStrings(const char* a, const char* b)
{
	size_t idxA = strlen(a), idxB = strlen(b), revLen = 0;
	int carry = 0;
	char* revBuf = malloc(idxA + idxB + 2);
	if (!revBuf)
		return NULL;
	while (idxA || idxB || carry) {
		int sum = carry;
		if (idxA)
			sum += a[--idxA] - '0';
		if (idxB)
			sum += b[--idxB] - '0';
		revBuf[revLen++] = (sum & 1) ? '1' : '0';
		carry = sum >> 1;
	}
	while (revLen > 1 && revBuf[revLen - 1] == '0')
		revLen--;
	char* sumStr = malloc(revLen + 1);
	if (!sumStr) {
		free(revBuf);
		return NULL;
	}
	for (size_t i = 0; i < revLen; i++)
		sumStr[i] = revBuf[revLen - 1 - i];
	sumStr[revLen] = '\0';
	free(revBuf);
	return sumStr;
}

static char* computeTotalSum(BinaryArray* array)
{
	char* total = malloc(2);
	if (!total)
		cleanupOnAllocationFailure(array, NULL, NULL);
	strcpy(total, "0");
	for (size_t i = 0; i < array->size; i++) {
		char* newSum = addBinaryStrings(total, array->strings[i]);
		if (!newSum)
			cleanupOnAllocationFailure(array, total, NULL);
		free(total);
		total = newSum;
	}
	return total;
}

static void printResults(BinaryArray* array, const char* totalSum)
{
	printf("Sum:\n%s\n\nInput numbers:\n", totalSum);
	for (size_t i = 0; i < array->size; i++) {
		printf("%s\n", array->strings[i]);
	}
}
