#include <stdio.h>
#include <string.h>

void* my_bsearch(const void* key, const void* array_start, size_t element_count, size_t element_size,
                 int (*compare)(const void*, const void*)) {
    size_t left = 0;
    size_t right = element_count;

    while (left < right) {
        size_t middle = left + (right - left) / 2;
        const void* middle_element = (const char*)array_start + middle * element_size;
        int result = compare(key, middle_element);

        if (result == 0) {
            return (void*)middle_element;
        } else if (result < 0) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }

    return NULL;
}

int compare_ints(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int compare_strings(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

typedef struct {
    int id;
    char name[20];
} Person;

int compare_persons_by_id(const void* a, const void* b) {
    return (((Person*)a)->id - ((Person*)b)->id);
}

void test_ints() {
    int numbers[] = {1, 3, 5, 7, 9, 11};
    int target = 7;
    int* result = my_bsearch(&target, numbers, 6, sizeof(int), compare_ints);
    if (result) printf("Found integer: %d at index %ld\n", *result, result - numbers);
    else printf("Integer not found\n");
}

void test_strings() {
    const char* words[] = {"apple", "banana", "cherry", "date"};
    const char* target = "cherry";
    const char** result = my_bsearch(&target, words, 4, sizeof(char*), compare_strings);
    if (result) printf("Found word: %s at index %ld\n", *result, result - words);
    else printf("Word not found\n");
}

void test_structs() {
    Person people[] = {{1, "Alice"}, {3, "Bob"}, {5, "Carol"}};
    Person target = {3, ""}; // we only compare ID
    Person* result = my_bsearch(&target, people, 3, sizeof(Person), compare_persons_by_id);
    if (result) printf("Found person: %s at index %ld\n", result->name, result - people);
    else printf("Person not found\n");
}

void test_duplicates() {
    int numbers[] = {1, 2, 2, 2, 3, 4};
    int target = 2;
    int* result = my_bsearch(&target, numbers, 6, sizeof(int), compare_ints);
    if (result) printf("Found one of duplicates: %d at index %ld\n", *result, result - numbers);
    else printf("Value not found\n");
}

void test_not_found() {
    int numbers[] = {2, 4, 6, 8};
    int target = 5;
    int* result = my_bsearch(&target, numbers, 4, sizeof(int), compare_ints);
    if (result) printf("Unexpectedly found: %d\n", *result);
    else printf("Correctly did not find value\n");
}

void test_empty_array() {
    int empty[] = {};
    int target = 10;
    int* result = my_bsearch(&target, empty, 0, sizeof(int), compare_ints);
    if (result) printf("Unexpectedly found in empty array\n");
    else printf("Correctly handled empty array\n");
}

void test_single_element_found() {
    int one[] = {42};
    int target = 42;
    int* result = my_bsearch(&target, one, 1, sizeof(int), compare_ints);
    if (result) printf("Found single element: %d at index %ld\n", *result, result - one);
    else printf("Single element not found\n");
}

void test_single_element_not_found() {
    int one[] = {42};
    int target = 99;
    int* result = my_bsearch(&target, one, 1, sizeof(int), compare_ints);
    if (result) printf("Unexpectedly found in single-element array\n");
    else printf("Correctly did not find in single-element array\n");
}

void test_first_element() {
    int numbers[] = {10, 20, 30, 40};
    int target = 10;
    int* result = my_bsearch(&target, numbers, 4, sizeof(int), compare_ints);
    if (result) printf("Found first element: %d at index %ld\n", *result, result - numbers);
    else printf("First element not found\n");
}

void test_last_element() {
    int numbers[] = {10, 20, 30, 40};
    int target = 40;
    int* result = my_bsearch(&target, numbers, 4, sizeof(int), compare_ints);
    if (result) printf("Found last element: %d at index %ld\n", *result, result - numbers);
    else printf("Last element not found\n");
}

void test_large_array() {
    int numbers[1000];
    for (int i = 0; i < 1000; ++i) numbers[i] = i * 2;
    int target = 198;
    int* result = my_bsearch(&target, numbers, 1000, sizeof(int), compare_ints);
    if (result) printf("Found in large array: %d at index %ld\n", *result, result - numbers);
    else printf("Value not found in large array\n");
}

int main(void) {
    test_ints();
    test_strings();
    test_structs();
    test_duplicates();
    test_not_found();
    test_empty_array();
    test_single_element_found();
    test_single_element_not_found();
    test_first_element();
    test_last_element();
    test_large_array();
    return 0;
}
