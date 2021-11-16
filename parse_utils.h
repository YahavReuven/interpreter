#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "errors.h"
#include "variables.h"
#include "arithmetic.h"
#include "consts.h"

#define END_OF_INSTRUCTION(instruction) (*instruction == 0)

int is_assignment(char* instruction);

error_t parse_num(char** instruction, value_t* result);

error_t parse_integer(char** instruction, value_t* result, int integer_len);

error_t parse_float(char** instruction, value_t* result, int len_before_d_point);