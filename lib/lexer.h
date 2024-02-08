#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

#define BUFFER_SIZE 8192 // 8KB buffer size

typedef enum {
    TOKEN_EOF,                    //    END OF FILE
    // SYMBOLS
    TOKEN_PAREN_OPEN,             //    (
    TOKEN_PAREN_CLOSE,            //    )
    TOKEN_BRACKET_OPEN,           //    [
    TOKEN_BRACKET_CLOSE,          //    ]
    TOKEN_CURLY_OPEN,             //    {
    TOKEN_CURLY_CLOSE,            //    }
    TOKEN_ARROW_OPEN,             //    <
    TOKEN_LESS_EQUAL,             //    <=
    TOKEN_ARROW_CLOSE,            //    >
    TOKEN_GREATER_EQUAL,          //    >=
    TOKEN_EQUAL,                  //    =
    TOKEN_COMPARE,                //    ==
    TOKEN_PLUS,                   //    +
    TOKEN_INCREMENT,              //    ++
    TOKEN_PLUS_EQUAL,             //    +=
    TOKEN_MINUS,                  //    -
    TOKEN_DECREASE,               //    --
    TOKEN_MINUS_EQUAL,            //    -=
    TOKEN_STAR,                   //    *
    TOKEN_DOUBLE_POINTER,         //    **
    TOKEN_TIMES_EQUAL,            //    *=
    TOKEN_COMMENT_BLOCK_CLOSE,    //    */
    TOKEN_SLASH,                  //    /
    TOKEN_COMMENT_LINE,           //    //
    TOKEN_COMMENT_BLOCK_OPEN,     //    /*
    TOKEN_DIVIDE_EQUAL,           //    /=
    TOKEN_SLOSH,                  //	\    '
    TOKEN_ESCAPE_SLOSH,           //    \\   '
    TOKEN_BITWISE_OR,             //    |
    TOKEN_LOGIC_OR,               //    ||
    TOKEN_DOT,                    //    .
    TOKEN_COMMA,                  //    ,
    TOKEN_COLON,                  //    :
    TOKEN_BITWISE_AND,            //    &
    TOKEN_LOGIC_AND,              //    &&
    TOKEN_MODULO,                 //    %
    TOKEN_BANG,                   //    !
    TOKEN_NOT_EQUAL,              //    !=
    TOKEN_COMPILER_FLAG,          //    @
    TOKEN_QUOTE,                  //    "
    TOKEN_QUOTE_SINGLE,           //    '
    TOKEN_UNDERSCORE,             //    _
    // KEYWORDS
    TOKEN_IDENTIFIER,             //    hello
    TOKEN_KEYWORD,                //    int
    TOKEN_NUMBER,                 //    23
    TOKEN_UNKNOWN,                //    ?
} TokenKind;

typedef struct {
    TokenKind kind;
    char* value;
    size_t len;
} Token;

typedef struct {
    size_t index;
    size_t length;
    char data[BUFFER_SIZE];
} Buffer;

Token tokenizeBuffer(Buffer *buffer);

char tokenHere(Buffer *buffer);

int sniffToken(Buffer *buffer, const char c);
int checkToken(Buffer *buffer, const char c);

int checkNumber(Buffer *buffer);
int checkSkip(Buffer *buffer);
int checkAlpha(Buffer *buffer);
int checkKeyword(const char *keywords[], const char *name);

void printToken(Buffer *buffer, const char *name);

#endif // LEXER_H
