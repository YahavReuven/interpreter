#include "parse_utils.h"

int is_assignment(char* instruction){
	return strchr(instruction, EQUAL_SIGN);
}


// from the first number
error_t parse_num(char** instruction, value_t* result) {
	char* string_num = NULL;
	int val = 0;
	int str_len = 0;
	error_t res = ERROR_SUCCESS;

	while (isdigit(*(*instruction + str_len))) {
		str_len++;
	}

	if (*(*instruction + str_len) == DECIMAL_POINT) {
		res = parse_float(instruction, result, str_len);
		if (res != ERROR_SUCCESS) {
			return res;
		}
	}
	else {
		res = parse_integer(instruction, result, str_len);
		if (res != ERROR_SUCCESS) {
			return res;
		}
	}

	return ERROR_SUCCESS;
}


error_t parse_integer(char** instruction, value_t* result, int integer_len) {
	char* string_integer = NULL;
	int val = 0;
	error_t res = ERROR_SUCCESS;

	string_integer = (char*)malloc(integer_len * sizeof(char) + 1);
	if (!string_integer) {
		printf("malloc failed.\n");
		return ERROR_MEM;
	}

	strncpy(string_integer, *instruction, integer_len);
	*(string_integer + integer_len) = 0;

	val = atoi(string_integer);

	free(string_integer);

	result->value_type = INT;
	result->value.int_val = val;

	*instruction += integer_len;

	return ERROR_SUCCESS;
}


error_t parse_float(char** instruction, value_t* result, int len_before_d_point) {
	int str_len = 0;
	char* string_float = NULL;
	double val = 0;
	error_t res = ERROR_SUCCESS;

	str_len = len_before_d_point;
	str_len++; //for the decimal point

	while (isdigit(*(*instruction + str_len))) {
		str_len++;
	}

	string_float = (char*)malloc(str_len * sizeof(char) + 1);
	if (!string_float) {
		printf("malloc failed.\n");
		return ERROR_MEM;
	}

	strncpy(string_float, *instruction, str_len);
	*(string_float + str_len) = 0;

	val = atof(string_float);

	free(string_float);

	result->value_type = FLOAT;
	result->value.float_val = val;

	*instruction += str_len;

	return ERROR_SUCCESS;
}