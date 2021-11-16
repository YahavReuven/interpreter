#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <ctype.h>

#include "errors.h"
#include "variables.h"
#include "parse_utils.h"
#include "utils.h"
#include "consts.h"

typedef struct arithmetic_command_handler_table_s {
	char symbol;
	error_t (*handler)(value_t, value_t, value_t*);
} arithmetic_command_handler_table_t;

extern arithmetic_command_handler_table_t arithmetic_handlers[];

error_t handle_arithmetic_operation(char* instruction, value_t* result);

error_t get_num(char** instruction, value_t* result);

error_t handle_add(value_t num1, value_t num2, value_t* result);

error_t handle_sub(value_t num1, value_t num2, value_t* result);

error_t handle_mul(value_t num1, value_t num2, value_t* result);

error_t handle_div(value_t num1, value_t num2, value_t* result);
