#ifndef SRC_S21_SMART_CALC_V1_H_
#define SRC_S21_SMART_CALC_V1_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_MAX_SIZE 255
typedef int T;

typedef struct {
  T data[STACK_MAX_SIZE][STACK_MAX_SIZE];
  int prior[STACK_MAX_SIZE];
  size_t size;
} Stack_t;

typedef struct {
  double data[255];
  size_t size;
} Stack_number;

void push(Stack_t *stack, int *value, int prior);
void push_number(Stack_number *number, double value);
void pop(Stack_t *stack, int *arr);
double pop_number(Stack_number *number);
int peek_prior(Stack_t *stack);
int peek_func(Stack_t *stack);
char *del_space(char *string, char *result);
char *convert_string(char *string, char *result);
int split_string(int *stack, char *string, int count);
int check_number(int *number);
int check_func(int *func);
int check_sign(char *string, int location);
double translate_double(int *number);
double translate_dot(int *string, int skip);
double str_to_double(int *string);
int set_prior(int *arr);
void double_to_string(double number, char *str);
void empty_arr(int *arr);
double calc_arifm(double number1, double number2, int op);
double calc_func(double number, int *simbol);
void calcul(int *simbol, Stack_number *number, int *error);
double round_num(double number);
void if_polish(Stack_t *stack, Stack_number *number, int *str, int *simbol,
               int *error, int prior);
double polish(char *data, int *error);
int reverse_sign(char *string, char *result);

#endif  // SRC_S21_SMART_CALC_V1_H_
