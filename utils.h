#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <string.h>

#include "errors.h"

#define IS_IGNORE(chr) (chr == SPACE)

void replace_char(char* str, char find, char replace);
