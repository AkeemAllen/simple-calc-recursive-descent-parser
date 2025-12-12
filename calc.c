#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parseFactor(char **expression) {
  if (**expression >= '0' && **expression <= '9') {
    int result = **expression - '0';
    (*expression)++;
    return result;
  } else {
    printf("Not a digit");
  }
  return 0;
}

int parseProduct(char **expression) {
  int fac1 = parseFactor(expression);
  while (**expression == '*') {
    ++(*expression);
    int fac2 = parseFactor(expression);
    fac1 = fac1 * fac2;
  }
  return fac1;
};

int parseQuotient(char **expression) {
  int fac1 = parseProduct(expression);
  while (**expression == '/') {
    ++(*expression);
    int fac2 = parseProduct(expression);
    fac1 = fac1 / fac2;
  }
  return fac1;
};

int parseSum(char **expression) {
  int fac1 = parseQuotient(expression);
  while (**expression == '+') {
    ++(*expression);
    int fac2 = parseQuotient(expression);
    fac1 = fac1 + fac2;
  }
  return fac1;
};

int parseDiff(char **expression) {
  int fac1 = parseSum(expression);
  while (**expression == '-') {
    ++(*expression);
    int fac2 = parseSum(expression);
    fac1 = fac1 - fac2;
  }
  return fac1;
};

int main(int argc, char *argv[]) {
  char *expression = argv[1];

  int result = parseDiff(&expression);

  printf("Result: %d\n", result);
  return 0;
}
