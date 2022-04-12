#include "./include/gt_token.h"
#include <stdbool.h>
Token* token_new(TokenType p_type, int p_line, char* p_lexeme) {
    Token* token = (Token*)malloc(sizeof(Token));
    if (!token) {
        printf("Unavailable memory.\n");
        return NULL;
    }
    token->type = p_type;
    token->line = p_line;
    token->lexeme = p_lexeme;
    return token;
}

void delete_token(Token* self) {
    bool has_lexeme = false;
    switch (self->type) {
    case TK_NAME:
        has_lexeme = true;
        break;
    case TK_STRING:
        has_lexeme = true;
        break;
    case TK_FLOAT:
        has_lexeme = true;
        break;
    case TK_INT:
        has_lexeme = true;
        break;
    default:
        break;
    }
    if (!self) {
        return;
    }
    if (has_lexeme) {
        free(self->lexeme);
    }
    free(self);
}
