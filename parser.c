#include "parser.h"

error_t parse_instruction(char* instruction) {
	error_t err = ERROR_SUCCESS;
	value_t print = { 0 };

	replace_char(instruction, NEW_LINE, 0);

	if (is_assignment(instruction)) {
		err = parse_assignment(instruction);
		if (err != ERROR_SUCCESS) {
			return err;
		}
	}
	else {
		err = handle_arithmetic_operation(instruction, &print);
		if (err != ERROR_SUCCESS) {
			return err;
		}
		print_val(print);
	}


	return ERROR_SUCCESS;
}


error_t parse_assignment(char* instruction) {
	int name_len = 0;
	char* name = NULL;
	value_t val = { 0 };
	char* pos = NULL;
	error_t err = ERROR_SUCCESS;

	name_len = get_var_name_len(instruction);
	name = (char*)malloc(name_len * sizeof(char) + 1);
	if (!name) {
		return ERROR_MEM;
	}
	strncpy(name, instruction, name_len);
	*(name + name_len) = 0;

	if (!validate_var_name(name)) {
		return ERROR_INVALID_INPUT;
	}

	pos = strchr(instruction, EQUAL_SIGN);
	pos++;

	while (IS_IGNORE(*pos)) {
		pos++;
	}

	err = handle_arithmetic_operation(pos, &val);
	if (err != ERROR_SUCCESS) {
		return err;
	}

	err = handle_assignment(name, val);
	if (err != ERROR_SUCCESS) {
		return err;
	}

	return ERROR_SUCCESS;
}


