#include "arithmetic.h"

arithmetic_command_handler_table_t arithmetic_handlers[] = {
	{ADD_SIGN, handle_add},
	{SUB_SIGN, handle_sub},
	{MUL_SIGN, handle_mul},
	{DIV_SIGN, handle_div}
};


//from the start of the first value
error_t handle_arithmetic_operation(char* instruction, value_t* result) {
	value_t num1 = { 0 };
	value_t num2 = { 0 };
	char input_operator = 0;
	error_t err = ERROR_SUCCESS;

	err = get_num(&instruction, &num1);
	if (err != ERROR_SUCCESS) {
		return err;
	}
	
	while (IS_IGNORE(*instruction)) {
		instruction++;
	}
	if (END_OF_INSTRUCTION(instruction)) {
		memcpy(result, &num1, sizeof(value_t));
		return ERROR_SUCCESS;
	}
	input_operator = *instruction;
	instruction++;
	while (IS_IGNORE(*instruction)) {
		instruction++;
	}

	err = get_num(&instruction, &num2);
	if (err != ERROR_SUCCESS) {
		return err;
	}

	for (int i = 0; i < sizeof(arithmetic_handlers) / sizeof(arithmetic_command_handler_table_t); i++) {
		// TODO: change in the future for further conplication of operations
		if (input_operator == arithmetic_handlers[i].symbol) {
			err = arithmetic_handlers[i].handler(num1, num2, result);
			return ERROR_SUCCESS;
		}
	}

	// cant find the appropriate operator
	return ERROR_MATH;
}

error_t get_num(char** instruction, value_t* result) {
	error_t err = ERROR_SUCCESS;
	int name_len = 0;
	char* name = NULL;
	if (isdigit(**instruction)) {
		err = parse_num(instruction, result);
	}
	else {
		name_len = get_var_name_len(*instruction);
		name = (char*)malloc(name_len * sizeof(char) + 1);
		if (!name) {
			return ERROR_MEM;
		}
		name = strncpy(name, *instruction, name_len);
		*(name + name_len) = 0;

		*instruction += name_len;

		err = get_variable(name, result);

		free(name);
	}
	return err;
}

error_t handle_add(value_t num1, value_t num2, value_t* result) {
	if (!(IS_NUM(num1) && IS_NUM(num2))) {
		return ERROR_MATH;
	}

	if (IS_FLOAT(num1) || IS_FLOAT(num2)) {
		result->value_type = FLOAT;
		result->value.float_val = GET_NUM_VALUE(num1) + GET_NUM_VALUE(num2);
	}
	else {
		result->value_type = INT;
		result->value.int_val = GET_NUM_VALUE(num1) + GET_NUM_VALUE(num2);
	}

	return ERROR_SUCCESS;
}

error_t handle_sub(value_t num1, value_t num2, value_t* result) {
	if (!(IS_NUM(num1) && IS_NUM(num2))) {
		return ERROR_MATH;
	}

	if (IS_FLOAT(num1) || IS_FLOAT(num2)) {
		result->value_type = FLOAT;
		result->value.float_val = GET_NUM_VALUE(num1) - GET_NUM_VALUE(num2);
	}
	else {
		result->value_type = INT;
		result->value.int_val = GET_NUM_VALUE(num1) - GET_NUM_VALUE(num2);
	}

	return ERROR_SUCCESS;
}


error_t handle_mul(value_t num1, value_t num2, value_t* result) {
	if (!(IS_NUM(num1) && IS_NUM(num2))) {
		return ERROR_MATH;
	}

	if (IS_FLOAT(num1) || IS_FLOAT(num2)) {
		result->value_type = FLOAT;
		result->value.float_val = GET_NUM_VALUE(num1) * GET_NUM_VALUE(num2);
	}
	else {
		result->value_type = INT;
		result->value.int_val = GET_NUM_VALUE(num1) * GET_NUM_VALUE(num2);
	}

	return ERROR_SUCCESS;
}


error_t handle_div(value_t num1, value_t num2, value_t* result) {
	if (!(IS_NUM(num1) && IS_NUM(num2))) {
		return ERROR_MATH;
	}

	if (GET_NUM_VALUE(num2) == 0) {
		return ERROR_MATH;
	}

	if (IS_FLOAT(num1) || IS_FLOAT(num2)) {
		result->value_type = FLOAT;
		result->value.float_val = GET_NUM_VALUE(num1) / GET_NUM_VALUE(num2);
	}
	else {
		result->value_type = INT;
		result->value.int_val = GET_NUM_VALUE(num1) / GET_NUM_VALUE(num2);
	}

	return ERROR_SUCCESS;
}