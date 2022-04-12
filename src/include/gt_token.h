#ifndef GT_TOKEN
#define GT_TOKEN
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define cast_int(value) (int)value

#define FIRST_TOKEN_TYPE (UCHAR_MAX + 1)

// Single char are token it'self.
typedef enum TokenType {
    TK_AND = FIRST_TOKEN_TYPE,
    TK_AS,
    TK_BREAK,
    TK_CONST,
    TK_CONTINUE,
    TK_ELSE,
    TK_ENUM,
    TK_FALSE,
    TK_FN,
    TK_FOR,
    TK_IF,
    TK_IN,
    TK_LOOP,
    TK_MATCH,
    TK_RETURN,
    TK_STATIC,
    TK_STRUCT,
    TK_SUPER,
    TK_TRUE,
    TK_TYPE,
    TK_USE,
    TK_WHERE,
    TK_WHILE,

    // two character tokens.
    TL_EQ,  // Equal (==)
    TK_GE,  // Great then equal (>=)
    TK_LE,  // Less then equal (<=)
    TK_NE,  // Not equal (!=)
    TK_DC,  // Double collon(::)
    TK_AR,  // Arrow Right (->)
    TK_ARF, // Arrow Right Flat (=>)

    // Literals.
    TK_NAME,
    TK_STRING,
    TK_FLOAT,
    TK_INT,

    TK_EOF

} TokenType;

#define NUM_RESERVED cast_int((TK_WHILE - TK_AND))

typedef struct token {
    TokenType type;
    int line;
    char* lexeme;
} Token;

Token* token_new(TokenType p_type, int p_line, char* p_lexeme);

void delete_token(Token* t);

#endif // !GT_TOKEN
