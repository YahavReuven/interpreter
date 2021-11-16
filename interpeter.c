#include "interpeter.h"

error_t handle_interpeter() {
	error_t err = ERROR_SUCCESS;
	variable_t var = { 0 };
	char command[MAX_BUFFER_SIZE] = { 0 };

	init_variables_storage(10);

	while (1) {
		printf(">>> ");
		fgets(command, MAX_BUFFER_SIZE, stdin);
		err = parse_instruction(command);
		if (err != ERROR_SUCCESS) {
			printf("ERROR: %d\n", err);
		}
	}

	free_variables_storage();

	return ERROR_SUCCESS;
}