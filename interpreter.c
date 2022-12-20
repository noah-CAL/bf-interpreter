#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"

const char *TOKENS = "<>+-[].";

/* Initialize 1 KiB of DMEM (by default)*/
#define MEM_SIZE 1024

typedef struct {
    char *data;
    int mem_ptr;
} DMEM;

DMEM *memory;

void initialize_data_memory() {
    memory = (DMEM *) malloc(sizeof(DMEM));
    memory->data = (char *) calloc(MEM_SIZE, sizeof(char));
    memory->mem_ptr = 0;
}

void free_data_memory() {
    free(memory->data);
    free(memory);
}

int main(int argc, char *argv[]) {
    initialize_data_memory();
    char *input = "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.";
    if (argc > 1) {
        input = argv[1];
    }
    if (!is_valid_expression(input, strlen(input))) {
        printf("Invalid expression");
        return -1;
    }
    calculate_expression(input, strlen(input));
    free_data_memory();
    return 0;
}

/**
 * Goes through each command one-by-one and passes its contents to 
 * the calculate_expression function. For loops, passes the contents
 * of each self-contained block.
 * Returns VOID
*/
// void parse_input(char *input, int length) {
    /* Separates each portion of the input by the [ ] delimeters
    * in order to evaluate loops. */
// }

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
        if (bracket_count < 0 || strchr(TOKENS, c) == NULL) {
            return 0;
        }
    }
    return 1;
}

/**
 * Runs EXPRESSION through the interpreter and returns NONE by default,
 * and the result if executing a print statement. Returns -1 upon an error.
*/
// TODO: make function return non-void value
void *calculate_expression(char *expression, int length) {
    if (!is_valid_expression(expression, length)) {
        printf("Invalid expression: %s", expression);
        return NULL;
    }
    for (int i = 0; i < length; i += 1) {
        char c = *(expression + i);
        int mem_ptr = memory->mem_ptr;
        switch (c) {
            case '<':
                memory->mem_ptr -= 1;
                break;
            case '>':
                memory->mem_ptr += 1;
                break;
            case '+':
                memory->data[mem_ptr] += 1;
                break;
            case '-':
                memory->data[mem_ptr] -= 1;
                break;
            case '[':
                while (memory->data[mem_ptr] != 0) {
                    /* Begin one char after [ */
                    calculate_expression(expression + 1, strlen(expression + 1));
                }
                break;
            case ']':
                return NULL;
            case '.':
                printf("%c", memory->data[mem_ptr]);
                break;
        }
    }
    return 0;
}