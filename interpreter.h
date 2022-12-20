#ifndef INTERPRETER_H
#define INTERPRETER_H

int is_valid_expression(char *expression, int length);
void *calculate_expression(char *expression, int length);

#endif