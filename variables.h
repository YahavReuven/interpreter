#pragma once

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "errors.h"
#include "consts.h"

#define IS_INT(value) (value.value_type == INT)
#define IS_FLOAT(value) (value.value_type == FLOAT)
#define IS_NUM(value) (IS_FLOAT(value) || IS_INT(value))

// assums that the value_t passed contains a number 
#define GET_NUM_VALUE(val) (IS_FLOAT(val) ? val.value.float_val : val.value.int_val)

#define CAPCAITY_SIZE_RATIO_REALLOCATION 2/3
#define CAPACITY_INCREASE_RATIO 2

typedef enum value_type_e {
	INT,
	FLOAT
} value_type_t;


typedef struct value_s {
	value_type_t value_type;
	union {
		int int_val;
		double float_val;
	} value;
} value_t;


typedef struct variable_s {
	char* name;
	value_t value;
} variable_t;


typedef struct variables_storage_s {
	int capacity;
	int size;
	variable_t* variables;
}variables_storage_t;

extern variables_storage_t variables;

error_t handle_assignment(char* name, value_t val);

int validate_var_name(char* name);

int get_var_name_len(char* name);

void print_val(value_t val);

error_t init_variables_storage(int n_vars);

error_t get_variable(char* name, value_t* result);

void free_variables_storage();