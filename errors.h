#pragma once

typedef enum errors_e {
	ERROR_SUCCESS,  //the function executed without errors
	ERROR_MATH,  //a math error has occured
	ERROR_INVALID_INPUT,  //the user entered an nvalid input
	ERROR_MEM  //a problem handling memory
} error_t;
