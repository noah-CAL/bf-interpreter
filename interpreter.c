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
        if (strchr(TOKENS, c) == NULL) {
            printf("Token %c is not an acceptable input", c);
            return 0;
        }
    }
    if (bracket_count > 0) {  // TODO: add support for nested [] (i.e. make it work without allowing negative bracket_counts for the recursion)
        printf("Mismatched braces in %s", expression);
        return 0;
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
        return NULL;
    }
    for (int i = 0; i < length; i += 1) {
        char c = *(expression + i);
        int mem_ptr = memory->mem_ptr;
        switch (c) {
            case '\n':
                break;
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
                    calculate_expression(expression + i + 1, strlen(expression + i + 1));
                }
                for (int j = i; j < length; j += 1) {
                    char c = *(expression + j);
                    if (c == ']') {
                        i = j;
                        break;
                    }
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