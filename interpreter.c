#include <stdio.h>
#include <string.h>
#include "interpreter.h"

#define TOKENS "<>+-[]."
/* Initialize 1 KiB of DMEM (by default)*/
#define MEM_SIZE 1024
char memory[MEM_SIZE];

int main(int argc, char* argv) {
    return 0;
}

/**
 * Checks if EXPRESSION is a valid BF expression. A valid expression consists
 * of <>+-. tokens, or a matching set of [] with proper enclosed tokens.
 * RETURNS:
 * 0 (false) if EXPRESSION is not a valid BF expression.
 * 1 (true) otherwise.
*/
int is_valid_expression(char *expression, int length) {
    int bracket_count = 0;
    for (int i = 0; i < length; i += 1) {
        char c = *(expression + i);
        if (c == '[') {
            bracket_count += 1;
        }
        if (c == ']') {
            bracket_count -= 1;
        }
        if (bracket_count < 0 || strstr(TOKENS, &c) != NULL) {
            return 0;
        }
    }
    return 1;
}

/**
 * Runs EXPRESSION through the interpreter and returns NONE by default,
 * and the result if executing a print statement.
*/
char *calculate_expression(char *expression, int length) {
    return 0;
}