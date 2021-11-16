#include "interpeter.h"

error_t handle_interpeter() {
	error_t err = ERROR_SUCCESS;
	variable_t var = { 0 };
	char command[MAX_BUFFER_SIZE] = { 0 };
	//int i = 0; //TODO: delete. for debug

	init_variables_storage(10);

	while (1) {
		printf(">>> ");
		fgets(command, MAX_BUFFER_SIZE, stdin);
		err = parse_instruction(command);
		if (err != ERROR_SUCCESS) {
			printf("ERROR: %d\n", err);
		}

		// TODO: delete. for debug
		//for (int i = 0; i < variables.size; i++) {
		//	var = variables.variables[i];
		//	printf("name: %s, type: %d\nint: %d, float: %f\n",
		//		var.name, var.value.value_type, var.value.value.int_val, var.value.value.float_val);
		//}
	}

	free_variables_storage();

	return ERROR_SUCCESS;
}