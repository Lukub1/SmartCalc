#include "s21_smartcalc_v1.h"

void push(Stack_t *stack, int *value, int prior) {
  for (int i = 0; value[i] != 0; i++) {
    stack->data[stack->size][i] = value[i];
  }
  stack->prior[stack->size] = prior;
  stack->size++;
}

void push_number(Stack_number *number, double value) {
  number->data[number->size] = value;
  number->size++;
}

void pop(Stack_t *stack, int *arr) {
  stack->size--;
  int i = 0;
  while (stack->data[stack->size][i] != 0) {
    arr[i] = stack->data[stack->size][i];
    stack->data[stack->size][i] = 0;
    stack->prior[stack->size] = 0;
    i++;
  }
  stack->prior[stack->size] = 0;
}

double pop_number(Stack_number *number) {
  double result = number->data[number->size - 1];
  number->size--;
  number->data[number->size] = 0;
  return result;
}

int peek_prior(Stack_t *stack) {
  int result = -1;
  if (stack->size > 0) {
    result = stack->prior[stack->size - 1];
  }
  return result;
}

int peek_func(Stack_t *stack) {
  int func = (stack->data[stack->size - 1][0] >= 97 &&
              stack->data[stack->size - 1][0] <= 122)
                 ? 1
                 : 0;
  return func;
}

char *del_space(char *string, char *result) {
  char str[STACK_MAX_SIZE] = {0};
  int i = 0, y = 0;
  while (string[y] != 0) {
    if (string[y] == 32) {
      y++;
    } else {
      str[i] = string[y];
      i++;
      y++;
    }
  }

  while (i != -1) {
    result[i] = str[i];
    i--;
  }
  return string;
}

char *convert_string(char *string, char *result) {
  int i = 0, y = 0, check = 1;
  int br = 0;
  char convert[STACK_MAX_SIZE] = {0};
  del_space(string, convert);
  for (; convert[y] != 0; i++, y++) {
    if (convert[y] == 44) {
      result[i] = 46;
      continue;
    } else if (convert[y] >= 65 && convert[y] <= 90) {
      result[i] = convert[y] + 32;
      continue;
    } else if (convert[y] == 45 &&
               (!((result[y - 1] >= 48 && result[y - 1] <= 57) ||
                  result[y - 1] == 41) &&
                (convert[y + 1] >= 48 && convert[y + 1] <= 57))) {
      result[i] = 126;
      continue;
    } else if (convert[y] == 40) {
      br++;
    } else if (convert[y] == 41) {
      br--;
    } else if (convert[y] == 42 || convert[y] == 43 || convert[y] == 45 ||
               convert[y] == 47) {
      if (!check_sign(convert, y)) {
        check = 0;
      }
    } else if ((convert[y] == 'm' && convert[y + 1] == 'o') ||
               convert[y + 2] == 'd') {
      result[i] = 37;
      convert[i + 1] = 0;
      convert[i + 2] = 0;
      y += 2;
      continue;
    }
    result[i] = convert[y];
    result[i + 1] = 0;
  }

  if (br != 0 || !check) {
    result[0] = 0;
  }

  // while (i != -1) {
  //   string[i] = convert[i];
  //   i--;
  // }
  string = result;
  return string;
}

int split_string(int *stack, char *string, int count) {
  int count1 = 0, flag = 0;
  string += count;
  while ((*string >= 40 && *string <= 57) ||
         (*string >= 97 && *string <= 122) || *string == 94 || *string == 126 ||
         *string == 37) {
    if ((*string >= 40 && *string <= 43) || *string == 45 || *string == 47 ||
        *string == 94 || *string == 37) {
      flag += 1;
      break;
    } else {
      count1++;
      flag--;
    }
    string++;
  }
  string -= count1;
  if (count1 == 0) {
    count1++;
  }
  for (int i = 0; i < count1; i++) {
    stack[i] = *string++;
  }
  if (!(((*string >= 40 && *string <= 57)) ||
        (*string >= 97 && *string <= 122) || *string == 94 || *string == 126 ||
        *string == 37)) {
    count = 0, count1 = -1;
  }
  return count + count1;
}

int check_number(int *number) {
  int check = 1, flag = 0;
  if (number[0] == 126 && (number[1] >= 48 && number[1] <= 57)) {
    check = 1;
  }
  for (int i = check; number[i] != 0; i++) {
    if (!(number[i] >= 48 && number[i] <= 57) && number[i] != 46) {
      if ((number[i] == 101 || number[i] == 69) && number[i + 1] == 126) {
        for (int y = 0; number[y] != 0; y++) {
          number[y] = 0;
        }
      } else {
        check = 0;
      }
      break;
    } else if (number[i] == 46) {
      if (flag > 0) {
        check = 0;
        break;
      } else {
        if (!(number[i + 1] >= 48 && number[i + 1] <= 57)) {
          check = 0;
          break;
        }
      }
      flag += 1;
    }
  }
  return check;
}

int check_func(int *func) {
  char str[5] = {0};
  int check = 0;
  for (int y = 0; y < 5; y++) {
    str[y] = func[y];
  }
  switch (func[0]) {
    case 'c':
      check = (!strcmp(str, "cos")) ? 1 : 0;
      break;
    case 's':
      check = (!strcmp(str, "sin") || !strcmp(str, "sqrt")) ? 1 : 0;
      break;
    case 't':
      check = (!strcmp(str, "tan")) ? 1 : 0;
      break;
    case 'a':
      check = (!strcmp(str, "asin") || !strcmp(str, "atan")) ? 1 : 0;
      (!strcmp(str, "acos")) ? check = 1 : 0;
      break;
    case 'l':
      check = (!strcmp(str, "ln") || !strcmp(str, "log")) ? 1 : 0;
      break;
  }
  return check;
}

int check_sign(char *string, int location) {
  int check = 1;
  if (string[location] == 45 &&
      (string[location - 1] == 40 ||
       (string[location + 1] >= 48 && string[location + 1] <= 57))) {
    check = 1;
  } else if (string[location - 1] >= 97 && string[location - 1] <= 122) {
    check = 0;
  } else if (string[location + 1] == 41) {
    check = 0;
  }
  if (string[location - 1] == 42 || string[location - 1] == 43 ||
      string[location - 1] == 47 || string[location - 1] == 45) {
    check = 0;
  }
  return check;
}

double translate_double(int *number) {
  double result = 0;
  for (int i = 0; number[i] != 0; i++) {
    if (i > 0) {
      result *= 10;
    }
    result += number[i] - 48;
  }
  return result;
}

double translate_dot(int *string, int skip) {
  double result = 0;
  int number[STACK_MAX_SIZE] = {0};
  int i = 0;
  for (int y = skip; string[y] != 0; y++, i++) {
    number[i] = string[y];
    if (i == 6) {
      break;
    }
  }
  result = translate_double(number);
  if (result >= 1) {
    for (int y = 0; y < i; y++) {
      result /= 10;
    }
  }
  return result;
}

double str_to_double(int *string) {
  double result = 0;
  int number[STACK_MAX_SIZE] = {0}, i = 0, sign = 1;
  for (int y = 0; string[y] != 0; y++, i++) {
    if (string[y] == 46) {
      result = translate_dot(string, y + 1);
      break;
    } else if (string[y] == 126) {
      sign = -1;
      i--;
      continue;
    }
    number[i] = string[y];
  }
  result += translate_double(number);
  result *= sign;
  return result;
}

int set_prior(int *arr) {
  int prior = -1, flag = 0;
  prior = (arr[0] == '(') ? flag = 1 : -1;
  prior = (arr[0] == '+' || arr[0] == '-') ? flag = 2 : -1;
  prior = (arr[0] == '*' || arr[0] == '/') ? flag = 3 : -1;
  prior = (arr[0] == '^') ? flag = 4 : -1;
  prior = (arr[0] == '%') ? flag = 5 : -1;

  return (flag > 0) ? flag : prior;
}

void empty_arr(int *arr) {
  for (int y = 0; arr[y] != 0; y++) {
    arr[y] = 0;
  }
}

double mod(double number1, double number2) {
  double result = 0;
  int sign = (number1 > 0) ? 1 : -1;
  number1 = fabs(number1);
  while (result < number1) {
    result += number2;
  }
  result -= number2;
  result = number1 - result;
  result *= sign;
  return result;
}

double calc_arifm(double number1, double number2, int op) {
  double result = 0;
  if (op == 42) {
    result = number1 * number2;
  } else if (op == 43) {
    result = number1 + number2;
  } else if (op == 45) {
    result = number1 - number2;
  } else if (op == 47) {
    result = (number2 != 0) ? number1 / number2 : 0;
  } else if (op == 37) {
    result = (number2 != 0) ? mod(number1, number2) : 0;
  } else if (op == 94) {
    result = pow(number1, number2);
  }
  return result;
}

double calc_func(double number, int *simbol) {
  double result = 0;
  switch (*simbol) {
    case 'c':
      result = cos(number);
      break;
    case 's':
      if (simbol[1] == 'i') {
        result = sin(number);
      } else {
        result = sqrt(number);
      }
      break;
    case 't':
      result = tan(number);
      break;
    case 'l':
      if (simbol[1] == 'n') {
        result = log(number);
      } else {
        result = log10(number);
      }
      break;
    case 'a':
      if (simbol[1] == 'c') {
        result = acos(number);
      } else if (simbol[1] == 's') {
        result = asin(number);
      } else {
        result = atan(number);
      }
      break;
  }
  return result;
}

void calcul(int *simbol, Stack_number *number, int *error) {
  if (*simbol == 42 || *simbol == 43 || *simbol == 45 || *simbol == 47 ||
      *simbol == 37 || *simbol == 94) {
    double number2 = pop_number(number), number1 = pop_number(number);
    if ((*simbol == 47 || *simbol == 37) && number2 == 0) {
      *error = 1;
    }
    push_number(number, calc_arifm(number1, number2, *simbol));
  } else if (check_func(simbol)) {
    double number1 = pop_number(number);
    push_number(number, calc_func(number1, simbol));
  }
}
double round_num(double number) {
  double dot = 0., result = (number > 0) ? floor(number) : ceil(number);
  dot = number - result;
  dot *= pow(10, 8);
  dot = (number > 0) ? floor(dot) : ceil(dot);
  dot /= pow(10, 8);
  return result + dot;
}

void if_polish(Stack_t *stack, Stack_number *number, int *str, int *simbol,
               int *error, int prior) {
  if (*str == 126 || (*str >= 48 && *str <= 57)) {
    if (!(check_number(str))) {
      *error = 1;
    } else {
      push_number(number, str_to_double(str));
    }
  } else if (*str == '(') {
    push(stack, str, prior);
  } else if (*str == ')') {
    pop(stack, simbol);
    while (*simbol != '(') {
      calcul(simbol, number, error);
      empty_arr(simbol);
      pop(stack, simbol);
    }
    if (stack->data[stack->size - 1][0] == 45) {
      number->data[number->size - 1] *= -1;
      stack->data[stack->size - 1][0] = 43;
    }
    if (peek_func(stack)) {
      pop(stack, simbol);
      calcul(simbol, number, error);
    }
  } else if (check_func(str)) {
    push(stack, str, prior);
  } else if (peek_prior(stack) >= prior && stack->size != 0 &&
             number->size != 1) {
    while (peek_prior(stack) > prior &&
           stack->data[stack->size - 1][0] != '(') {
      pop(stack, simbol);
      calcul(simbol, number, error);
      empty_arr(simbol);
    }
    push(stack, str, prior);
  } else {
    push(stack, str, prior);
  }
}

double polish(char *data, int *error) {
  double result = 0;
  if (strlen(data) == 0) {
    result = -0;
    *error = 1;
  } else {
    Stack_t stack = {0};
    Stack_number number = {0};
    stack.size = 0;
    number.size = 0;
    int str[STACK_MAX_SIZE] = {0}, simbol[5] = {0}, start = 0, end = 0;
    while (end != -1) {
      end = split_string(str, data, start);
      int prior = set_prior(str);
      if_polish(&stack, &number, str, simbol, error, prior);
      start = end;
      empty_arr(str);
      empty_arr(simbol);
    }
    if ((number.size == 0 && stack.size != 0) ||
        (stack.size == 0 && number.size >= 2)) {
      *error = 1;
    } else if ((number.size) > 1) {
      while (number.size - 1 != 0) {
        pop(&stack, simbol);
        calcul(simbol, &number, error);
      }
    }
    if (!*error) {
      result = pop_number(&number);
    } else {
      result = 0;
    }
  }
  if (!(result >= 0 || result <= 0)) {
    *error = 1;
    result = 0;
  }
  result = round_num(result);
  return result;
}

int reverse_sign(char *string, char *result) {
  int check = 1;
  for (int i = 0; string[i] != 0; i++) {
    if (!((string[i] >= 48 && string[i] <= 57) || string[i] == 46 ||
          (i == 0 && string[i] == 45))) {
      check = 0;
      break;
    }
  }
  if (check) {
    int i = 0;
    if (string[0] != 45) {
      result[i] = 45;
      i++;
      while (string[i - 1] != 0) {
        result[i] = string[i - 1];
        i++;
      }
    } else {
      i++;
      while (string[i] != 0) {
        result[i - 1] = string[i];
        i++;
      }
    }
    result[i] = 0;
  }
  return check;
}
