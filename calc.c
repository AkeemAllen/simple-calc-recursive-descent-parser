#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double parseSum(char **expression);

double parseFactor(char **expression) {
  double result = 0;
  while (**expression >= '0' && **expression <= '9') {
    result = (result * 10) + (**expression - '0');
    (*expression)++;
    if (**expression == '+' || **expression == '-' || **expression == '/' ||
        **expression == '*' || **expression == '\0' || **expression == '(' ||
        **expression == ')') {
      return result;
    }
  }

  if (**expression == '(') {
    (*expression)++;
    double inner_result = parseSum(expression);
    (*expression)++;
    return inner_result;
  }

  if (**expression == '-') {
    (*expression)++;
    return -parseFactor(expression);
  }

  printf("Error attempting to parse: %c \n", *expression[0]);
  assert(false);
}

double parseProduct(char **expression) {
  double fac1 = parseFactor(expression);

  // Instead of implicit multiplication, use preprocessing to add * between the
  // correct values
  while (**expression == '*' || **expression == '/' || **expression == '(') {
    int mulOrDiv = 1;
    if (**expression == '/')
      mulOrDiv = 0;

    if (**expression != '(')
      ++(*expression);
    double fac2 = parseFactor(expression);

    if (mulOrDiv == 1) {
      fac1 = fac1 * fac2;
    } else {
      if (fac2 == 0) {
        printf("Cannot Divide by Zero\n");
        assert(false);
      }
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

char *preProcessExpression(char *expression) {
  char *formattedExpression = malloc(strlen(expression) + 1);

  // Removing Whitespace from expression
  int j = 0;
  for (int i = 0; i < strlen(expression); i++) {
    if (expression[i] != ' ') {
      formattedExpression[j] = expression[i];
      j++;
    }
  }

  // Validate Open and Closed brackets
  char brackets[100];
  int k = -1;
  for (int i = 0; i < strlen(expression); i++) {
    if (formattedExpression[i] == '(') {
      k++;
      brackets[k] = formattedExpression[i];
    } else if (formattedExpression[i] == ')') {
      if (k == -1 || brackets[k] != '(') {
        printf("Missing Open Bracket\n");
        assert(false);
      }
      k--;
    }
  }

  if (k != -1) {
    printf("Missing Closing Bracket\n");
    assert(false);
  }

  return formattedExpression;
}

int main(int argc, char *argv[]) {
  char *expression = argv[1];

  char *formattedExpression = preProcessExpression(expression);
  double result = parseSum(&formattedExpression);

  printf("Result: %.2f\n", result);
  return 0;
}
