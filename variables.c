#include "variables.h"

variables_storage_t variables = { 0 };

error_t handle_assignment(char* name, value_t val) {
	variable_t var = { 0 };
	error_t err = ERROR_SUCCESS;

	var.name = name;
	memcpy(&var.value, &val, sizeof(value_t));

	err = add_variable(var);
	if (err != ERROR_SUCCESS) {
		return err;
	}
}


int validate_var_name(char* name) {
	char invalid_name_chars[] = {
		ADD_SIGN, SUB_SIGN, MUL_SIGN,
		DIV_SIGN, SPACE
	};
	return (!isdigit(*name)) && (!strpbrk(name, invalid_name_chars));
}


int get_var_name_len(char* name) {
	int i = 0;
	int len = 0;
	while (isdigit(*(name + i)) || isalpha(*(name + i))) {
		i++;
		len++;
	}
	return len;
}

void print_val(value_t val) {
	if (val.value_type == INT) {
		printf("%d\n", val.value.int_val);
	}
	else if (val.value_type == FLOAT) {
		printf("%f\n", val.value.float_val);
	}
}



error_t init_variables_storage(int n_vars) {
	variables.variables = (variable_t*)malloc(n_vars * sizeof(variable_t));
	if (!variables.variables) {
		return ERROR_MEM;
	}
	variables.capacity = n_vars;
	return ERROR_SUCCESS;
}


static error_t add_variable(variable_t var) {
	error_t err = ERROR_SUCCESS;
	memcpy(variables.variables + variables.size, &var, sizeof(variable_t));
	variables.size++;
	if (check_change_capacity()) {
		err = increase_variables_storage();
		if (err != ERROR_SUCCESS) {
			return err;
		}
	}
	return ERROR_SUCCESS;
}


error_t get_variable(char* name, value_t* result) {
	for (int i = 0; i < variables.size; i++) {
		if (!strcmp(name, variables.variables[i].name)) {
			memcpy(result, &variables.variables[i].value, sizeof(value_t));
			return ERROR_SUCCESS;
		}
	}
	return ERROR_INVALID_INPUT;
}


static int check_change_capacity() {
	return variables.size > variables.capacity * CAPCAITY_SIZE_RATIO_REALLOCATION;
}


static error_t increase_variables_storage() {
	int new_capacity = variables.capacity * CAPACITY_INCREASE_RATIO;
	variables.variables = (variable_t*)realloc(variables.variables ,new_capacity * sizeof(variable_t));
	if (!variables.variables) {
		return ERROR_MEM;
	}
	variables.capacity = new_capacity;
	return ERROR_SUCCESS;
}


void free_variables_storage() {
	int i = 0;
	for (i = 0; i < variables.size; i++) {
		free(variables.variables[i].name);
	}
	free(variables.variables);
}