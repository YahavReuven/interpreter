// ----------------------------- DO NOT USE --------------------------------------- 

#include "instruction_parser.h"

error_t parse_instruction(char* instructionn) {


}


// TODO: what happens when a = is in the begining of an instruction
int find_assignment(char* instructionn) {
	int i = 0;
	while (*(instructionn + i)) {
		if (*instructionn == '=') {
			return i;
		}
		i++;
	}
	return 0;
}