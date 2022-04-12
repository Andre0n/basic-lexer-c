#include "./include/gt_lexer.h"
#include <stdio.h>
#include <stdlib.h>

char* char_from_file(char* file_path) {
    FILE* fp = fopen(file_path, "rb");
    if (!fp) {
        fprintf(stderr, "Can't open file\n");
        exit(64);
    }
    fseek(fp, 0L, SEEK_END);
    size_t lSize = ftell(fp);
    rewind(fp);
    char* buffer = calloc(1, lSize + 1);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed!\n");
        fclose(fp);
        exit(1);
    }
    if (1 != fread(buffer, lSize, 1, fp)) {
        fclose(fp);
        free(buffer);
        fputs("entire read fails", stderr);
        exit(1);
    }
    fclose(fp);
    return buffer;
}

int main(int argc, char* argv[]) {
    char* s = char_from_file("../../../../examples/hello.exp");

    Lexer* lexer = new_lexer(s);
    if (!lexer) {
        exit(1);
    }
    Token* t = scan(lexer);
    while (t->type != TK_EOF) {
        printf("Type: %d, Line: %d, Lexeme: %s\n", t->type, t->line, t->lexeme);
        delete_token(t);
        t = scan(lexer);
        if (!t) {
            fprintf(stderr, "Not valid Token found!\n");
            exit(1);
        }
    }
    delete_token(t);
    free(lexer);
    free(s);
    return 0;
};
