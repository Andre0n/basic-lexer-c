#ifndef GT_LEXER
#define GT_LEXER
#include "./gt_token.h"
#include <stdbool.h>

typedef struct lexer {
    char* source; // source code.
    char current;
    int line;
    int cursor;
} Lexer;

Lexer* new_lexer(char* source);
Token* scan(Lexer* self);
bool isAtEnd(Lexer* self);
void advance(Lexer* self);

#endif // !GT_LEXER
