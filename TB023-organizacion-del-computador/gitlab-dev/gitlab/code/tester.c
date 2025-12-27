#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib.h"

#define assert cr_assert

#define ASSERT_ARRAY_EQUALS(lhs, lhsSize, rhs, rhsSize)            \
do {                                                               \
  int areEqual = 1;                                                \
  if (lhsSize == rhsSize) {                                        \
    for (size_t index = 0; index < lhsSize && areEqual; ++index) { \
      if ((lhs)[index] != (rhs)[index]) {                          \
        areEqual = 0;                                              \
      }                                                            \
    }                                                              \
  } else {                                                         \
    areEqual = 0;                                                  \
  }                                                                \
  assert(areEqual);                                                \
} while (0)

Test(ExampleTests, 1) {
  {
    const int values[] = { 1 };
    const int expected[] = { 1 };
    const size_t expectedCount = sizeof(expected)/sizeof(expected[0]);
    
    size_t actualCount = 0;
    int *actual = distinct(values, sizeof(values)/sizeof(values[0]), &actualCount);
    
    ASSERT_ARRAY_EQUALS(expected, expectedCount, actual, actualCount);
    free(actual);
  }
}
Test(ExampleTests, 2){
  {
    const int values[] = { 1,2 };
    const int expected[] = { 1,2 };
    const size_t expectedCount = sizeof(expected)/sizeof(expected[0]);
    
    size_t actualCount = 0;
    int *actual = distinct(values, sizeof(values)/sizeof(values[0]), &actualCount);
    
    ASSERT_ARRAY_EQUALS(expected, expectedCount, actual, actualCount);
    free(actual);
  }
}

Test(ExampleTests, 3){
  {
    const int values[] = { 1,1,2 };
    const int expected[] = { 1,2 };
    const size_t expectedCount = sizeof(expected)/sizeof(expected[0]);
    
    size_t actualCount = 0;
    int *actual = distinct(values, sizeof(values)/sizeof(values[0]), &actualCount);
    
    ASSERT_ARRAY_EQUALS(expected, expectedCount, actual, actualCount);
    free(actual);
  }
}

Test(ExampleTests, 4){
  {
    const int values[] = { 1,1,1,2,3,4,5 };
    const int expected[] = { 1,2,3,4,5 };
    const size_t expectedCount = sizeof(expected)/sizeof(expected[0]);
    
    size_t actualCount = 0;
    int *actual = distinct(values, sizeof(values)/sizeof(values[0]), &actualCount);
    
    ASSERT_ARRAY_EQUALS(expected, expectedCount, actual, actualCount);
    free(actual);
  }
}
Test(ExampleTests, 5){
  {
    const int values[] = { 1,2,2,3,3,4,4,5,6,7,7,7 };
    const int expected[] = { 1,2,3,4,5,6,7 };
    const size_t expectedCount = sizeof(expected)/sizeof(expected[0]);
    
    size_t actualCount = 0;
    int *actual = distinct(values, sizeof(values)/sizeof(values[0]), &actualCount);
    
    ASSERT_ARRAY_EQUALS(expected, expectedCount, actual, actualCount);
    free(actual);
  }
}
Test(ExampleTests, 6){
  {
    const int values[] = { 1,1,1,1,1,1,1,1,1,1,1,1 };
    const int expected[] = { 1 };
    const size_t expectedCount = sizeof(expected)/sizeof(expected[0]);
    
    size_t actualCount = 0;
    int *actual = distinct(values, sizeof(values)/sizeof(values[0]), &actualCount);
    
    ASSERT_ARRAY_EQUALS(expected, expectedCount, actual, actualCount);
    free(actual);
  }
}

Test(ExampleTests, 7){
  {
    const int values[] = { 1,1,1,1,1,1,1,2,1,1,1,1,1,0 };
    const int expected[] = { 1,2,0 };
    const size_t expectedCount = sizeof(expected)/sizeof(expected[0]);
    
    size_t actualCount = 0;
    int *actual = distinct(values, sizeof(values)/sizeof(values[0]), &actualCount);
    
    ASSERT_ARRAY_EQUALS(expected, expectedCount, actual, actualCount);
    free(actual);
  }
}
