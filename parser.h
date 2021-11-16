#pragma once

#include "utils.h"
#include "errors.h"
#include "parse_utils.h"
#include "variables.h"
#include "arithmetic.h"
#include "consts.h"

error_t parse_instruction(char* instruction);

error_t parse_assignment(char* instruction);
