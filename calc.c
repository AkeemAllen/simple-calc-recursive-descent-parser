#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double parseFactor(char **expression) {
  double result = 0;

  while (**expression >= '0' && **expression <= '9') {
    result = (result * 10) + (**expression - '0');
    (*expression)++;
    if (**expression == '+' || **expression == '-' || **expression == '/' ||
        **expression == '*' || **expression == '\0') {
      return result;
    }
  }

  if (**expression == '-') {
    (*expression)++;
    return -parseFactor(expression);
  } else {
    printf("Not a digit\n");
  }
  return 0;
}

double parseProduct(char **expression) {
  double fac1 = parseFactor(expression);
  while (**expression == '*' || **expression == '/') {
    int mulOrDiv = 1;
    if (**expression == '/')
      mulOrDiv = 0;

    ++(*expression);
    double fac2 = parseFactor(expression);
    if (mulOrDiv == 1) {
      fac1 = fac1 * fac2;
    } else {
      fac1 = fac1 / fac2;
    }
  }
  return fac1;
};

double parseSum(char **expression) {
  double fac1 = parseProduct(expression);

  while (**expression == '+' || **expression == '-') {
    int addOrSub = 1;
    if (**expression == '-')
      addOrSub = 0;

    ++(*expression);
    double fac2 = parseProduct(expression);
    if (addOrSub == 1) {
      fac1 = fac1 + fac2;
    } else {
      fac1 = fac1 - fac2;
    }
  }

  return fac1;
};

int main(int argc, char *argv[]) {
  char *expression = argv[1];

  double result = parseSum(&expression);

  printf("Result: %.2f\n", result);
  return 0;
}
