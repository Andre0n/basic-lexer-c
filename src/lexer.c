#include "./include/gt_lexer.h"
#include "./include/gt_token.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Lexer* new_lexer(char* source) {
    Lexer* lexer = (Lexer*)calloc(1, sizeof(Lexer));
    if (!lexer) {
        fprintf(stderr, "Memory allocation failed!\n");
        return NULL;
    }
    lexer->source = source;
    lexer->line = 1;
    lexer->cursor = 0;
    lexer->current = lexer->source[lexer->cursor];
    return lexer;
}
void advance(Lexer* self) {
    self->cursor++;
    if (!isAtEnd(self)) {
        self->current = self->source[self->cursor - 1];
    } else {
        self->current = '\0';
    }
}

bool isAtEnd(Lexer* self) { return self->cursor > strlen(self->source); }

bool match(Lexer* self, char expected) {
    if (!isAtEnd(self)) {
        return self->source[self->cursor] == expected;
    }
    return false;
}

char peek_next(Lexer* self) {
    if (!isAtEnd(self)) {
        return self->source[self->cursor];
    }
    return '\0';
}

Token* parse_number(Lexer* self) {
    char* num = calloc(1, sizeof(char));
    bool has_dot = false;
    while (isdigit(self->current)) {
        num = realloc(num, sizeof(num) + 2);
        char tmp[] = {self->current, '\0'};
        strcat(num, tmp);
        advance(self);
    }
    if (self->current == '.' && isdigit(peek_next(self))) {
        has_dot = true;
        num = realloc(num, sizeof(num) + 2);
        char tmp[] = {self->current, '\0'};
        strcat(num, tmp);
        advance(self);
        while (isdigit(self->current)) {
            num = realloc(num, sizeof(num) + 2);
            char tmp[] = {self->current, '\0'};
            strcat(num, tmp);
            advance(self);
        }
    }
    if (has_dot) {
        return token_new(TK_FLOAT, self->line, num);
    } else {
        return token_new(TK_INT, self->line, num);
    }
}

Token* parse_string(Lexer* self) {
    char* string = calloc(1, sizeof(char));
    advance(self); // Skip the "
    while (self->current != '"' && self->current != '\n' && !isAtEnd(self)) {
        string = realloc(string, sizeof(string) + 2);
        char tmp[] = {self->current, '\0'};
        strcat(string, tmp);
        advance(self);
    }
    if (self->current != '"' || isAtEnd(self)) {
        free(string);
        return NULL;
    }
    advance(self);
    return token_new(TK_STRING, self->line, string);
}

Token* scan(Lexer* self) {
    while (!isAtEnd(self)) {
        switch ((char)self->current) {
        case '/':
            if (match(self, '/')) {
                while (self->current != '\n') {
                    advance(self);
                }
                break;
            }
        case ' ':
            advance(self);
            break;
        case '\r':
            advance(self);
            break;
        case '\t':
            advance(self);
            break;
        case '\n':
            self->line++;
            advance(self);
            break;
        case '"':
            return parse_string(self);
        default:
            if (isdigit(self->current)) {
                return parse_number(self);
            } else if (isalpha(self->current)) {
                char* word = calloc(1, sizeof(char));
                while (isalpha(self->current)) {
                    word = realloc(word, sizeof(word) + 2);
                    char tmp[] = {self->current, '\0'};
                    strcat(word, tmp);
                    advance(self);
                }
                return token_new(TK_NAME, self->line, word);
            } else {
                char lexeme[] = {self->current, '\0'};
                advance(self);
                return token_new(lexeme[0], self->line, lexeme);
            }
            advance(self);
        }
    }
    return token_new(TK_EOF, self->line, "EOF");
}
