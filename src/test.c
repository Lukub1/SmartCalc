#include "check.h"
#include "s21_smartcalc_v1.h"

START_TEST(push_test) {
  Stack_t stack;
  int arr[2] = {0};
  arr[0] = 96;
  for (int i = 0; i < 26; i++) {
    arr[0] += 1;
    push(&stack, arr, i);
  }
  ck_assert_int_eq(stack.size, 26);
  ck_assert_int_eq(stack.data[stack.size - 1][0], 'z');
  for (int i = 0; i < 228; i++) {
    push(&stack, arr, i);
  }
  int arr2[255];
  for (int i = 0; i < 255; i++) {
    arr2[i] = 122;
  }
  push(&stack, arr2, 50);
  ck_assert_int_eq(stack.size, 255);
  ck_assert_int_eq(stack.data[stack.size - 1][stack.size - 1], 'z');
}
END_TEST

START_TEST(pop_test) {
  Stack_t stack;
  int arr[2] = {0};
  arr[0] = 96;
  for (int i = 0; i < 26; i++) {
    arr[0] += 1;
    push(&stack, arr, i);
  }
  ck_assert_int_eq(stack.size, 26);
  ck_assert_int_eq(stack.data[stack.size - 1][0], 'z');

  pop(&stack, arr);
  ck_assert_int_eq(stack.size, 25);
  ck_assert_int_eq(stack.data[stack.size - 1][0], 'y');
  ck_assert_int_eq(*arr, 'z');

  for (int i = 0; i < 24; i++) {
    pop(&stack, arr);
  }
  ck_assert_int_eq(stack.size, 1);
  ck_assert_int_eq(stack.data[stack.size - 1][0], 'a');
  ck_assert_int_eq(*arr, 'b');
}
END_TEST

START_TEST(convert_test) {
  char data[50];
  convert_string("Co  s(~3)", data);
  ck_assert_str_eq(data, "cos(~3)");
  empty_arr((int *)data);
  ((int *)data);
  convert_string("cos( - 3 - 4)", data);
  ck_assert_str_eq(data, "cos(~3-4)");
  empty_arr((int *)data);
  ((int *)data);
  convert_string("3,14*2", data);
  ck_assert_str_eq(data, "3.14*2");
  empty_arr((int *)data);
  (data);
  convert_string("sin (2 5/ (-3+ -2)*5)", data);
  ck_assert_str_eq(data, "sin(25/(~3+~2)*5)");
  empty_arr((int *)data);
  (data);
  convert_string("sin (2 5/ (-3+++ -2)*5)", data);
  ck_assert_str_eq(data, "");
}
END_TEST

START_TEST(polish_test) {
  double result = 0;
  char data[50];
  int error = 0;
  convert_string("cos( - 3.00000001 - 4)", data);
  result = polish(data, &error);
  ck_assert_double_eq_tol(result, 0.7539023, 1e-7);
  empty_arr((int *)data);
  (data);
  convert_string("sin (2 5/ (-3+ -2)*5)", data);
  result = polish(data, &error);
  ck_assert_int_eq((int)result, 0);
  empty_arr((int *)data);
  (data);
  convert_string("sin (2^+5/ (-3+ -2)*5)", data);
  result = polish(data, &error);
  ck_assert_int_eq((int)result, 0);
  empty_arr((int *)data);
  (data);
  convert_string("sin (2fg5/ (-3+ -2)*5)", data);
  result = polish(data, &error);
  ck_assert_int_eq((int)result, 0);
  empty_arr((int *)data);
  (data);
  convert_string("sin (25/ (-3,4+ -2,9,9)*5)", data);
  result = polish(data, &error);
  ck_assert_int_eq((int)result, 0);
  empty_arr((int *)data);
  (data);
  convert_string("sin (2.fg5/ (-3+ -2)*5)", data);
  result = polish(data, &error);
  ck_assert_int_eq((int)result, 0);
}
END_TEST

START_TEST(polish_func_1_test) {
  char data[50];
  convert_string("acos(0)", data);
  int error = 0;
  double result = polish(data, &error);
  ck_assert_double_eq_tol(result, 1.5707963, 1e-7);
  empty_arr((int *)data);
  (data);
  convert_string("asin(34-(10+4)-20)", data);
  result = polish(data, &error);
  ck_assert_int_eq((int)result, 0);
  empty_arr((int *)data);
  (data);
  convert_string("atan(34-(10+3)-20)", data);
  result = polish(data, &error);
  ck_assert_double_eq_tol(result, 0.7853981, 1e-7);
  empty_arr((int *)data);
  (data);
  convert_string("ln(25)", data);
  result = polish(data, &error);
  ck_assert_double_eq_tol(result, 3.2188758, 1e-7);
  empty_arr((int *)data);
  (data);
  convert_string("log(5)", data);
  result = polish(data, &error);
  ck_assert_double_eq_tol(result, 0.6989700, 1e-7);
  empty_arr((int *)data);
  (data);
  convert_string("tan(sin(cos(1*3)))", data);
  result = polish(data, &error);
  ck_assert_double_eq_tol(result, -1.1067422, 1e-7);
}
END_TEST

START_TEST(polish_func_2_test) {
  char data[50];
  int error = 0;
  convert_string("sqrt(169)", data);
  double result = polish(data, &error);
  ck_assert_int_eq((int)result, 13);
  empty_arr((int *)data);
  convert_string("sqrt-(169)", data);
  result = polish(data, &error);
  ck_assert_int_eq((int)result, 0);
  empty_arr((int *)data);
  convert_string("sqrt)", data);
  result = polish(data, &error);
  ck_assert_int_eq((int)result, 0);
  empty_arr((int *)data);
}
END_TEST

START_TEST(polish_func_3_test) {
  char data[50];
  int error = 0;
  convert_string("acos(0)", data);
  double result = polish(data, &error);
  ck_assert_double_eq_tol(result, 1.5707963, 1e-7);
  empty_arr((int *)data);
  convert_string("6mod4", data);
  result = polish(data, &error);
  ck_assert_int_eq((int)result, 2.);
  empty_arr((int *)data);
  convert_string("1.2e-15", data);
  result = polish(data, &error);
  ck_assert_double_eq_tol(result, 0, 1e-7);
  empty_arr((int *)data);
  convert_string("Asin(1) * aTaN(-1) + (-12/2) * (-1)", data);
  result = polish(data, &error);
  ck_assert_double_eq_tol(result, 4.76629944, 1e-7);
}
END_TEST

START_TEST(reverse_sign_test) {
  char data[50], result[50];
  int res = reverse_sign("-53", result);
  ck_assert_int_eq(strcmp(result, "53"), 0);
  ck_assert_int_eq(res, 1);
  empty_arr((int *)data);
  (data);
  reverse_sign("5.0003", result);
  ck_assert_int_eq(strcmp(result, "-5.0003"), 0);
  ck_assert_int_eq(res, 1);
  empty_arr((int *)data);
  (data);
  res = reverse_sign("cos(-1)", result);
  ck_assert_int_eq(res, 0);
}
END_TEST

Suite *s21_calc_suite(void) {
  Suite *suite;
  TCase *core;
  suite = suite_create("S21_calc");
  core = tcase_create("Core");

  tcase_add_test(core, push_test);
  tcase_add_test(core, pop_test);
  tcase_add_test(core, convert_test);
  tcase_add_test(core, polish_test);
  tcase_add_test(core, polish_func_1_test);
  tcase_add_test(core, polish_func_2_test);
  tcase_add_test(core, polish_func_3_test);
  tcase_add_test(core, reverse_sign_test);

  suite_add_tcase(suite, core);

  return (suite);
}

int main(void) {
  int failed = 0;
  Suite *suite;

  SRunner *runner;

  suite = s21_calc_suite();
  runner = srunner_create(suite);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
