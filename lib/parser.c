#include "parser.h"
#include "lexer.h"
#include <stdio.h>

const char *kindName[] = {
	"TOKEN_EOF",                    //    END OF FILE
    // SYMBOLS
    "TOKEN_PAREN_OPEN",             //    (
    "TOKEN_PAREN_CLOSE",            //    )
    "TOKEN_BRACKET_OPEN",           //    [
    "TOKEN_BRACKET_CLOSE",          //    ]
    "TOKEN_CURLY_OPEN",             //    {
    "TOKEN_CURLY_CLOSE",            //    }
    "TOKEN_ARROW_OPEN",             //    <
    "TOKEN_LESS_EQUAL",             //    <=
    "TOKEN_ARROW_CLOSE",            //    >
    "TOKEN_GREATER_EQUAL",          //    >=
    "TOKEN_EQUAL",                  //    =
    "TOKEN_COMPARE",                //    ==
    "TOKEN_PLUS",                   //    +
    "TOKEN_INCREMENT",              //    ++
    "TOKEN_PLUS_EQUAL",             //    +=
    "TOKEN_MINUS",                  //    -
    "TOKEN_DECREASE",               //    --
    "TOKEN_MINUS_EQUAL",            //    -=
    "TOKEN_STAR",                   //    *
    "TOKEN_DOUBLE_POINTER",         //    **
    "TOKEN_TIMES_EQUAL",            //    *=
    "TOKEN_COMMENT_BLOCK_CLOSE",    //    */
    "TOKEN_SLASH",                  //    /
    "TOKEN_COMMENT_LINE",           //    //
    "TOKEN_COMMENT_BLOCK_OPEN",     //    /*
    "TOKEN_DIVIDE_EQUAL",           //    /=
    "TOKEN_SLOSH",                  //	\    '
    "TOKEN_ESCAPE_SLOSH",           //    \\   '
    "TOKEN_BITWISE_OR",             //    |
    "TOKEN_LOGIC_OR",               //    ||
    "TOKEN_DOT",                    //    .
    "TOKEN_COMMA",                  //    ,
    "TOKEN_COLON",                  //    :
    "TOKEN_BITWISE_AND",            //    &
    "TOKEN_LOGIC_AND",              //    &&
    "TOKEN_MODULO",                 //    %
    "TOKEN_BANG",                   //    !
    "TOKEN_NOT_EQUAL",              //    !=
    "TOKEN_COMPILER_FLAG",          //    @
    "TOKEN_QUOTE",                  //    "
    "TOKEN_QUOTE_SINGLE",           //    '
    "TOKEN_UNDERSCORE",             //    _
    // KEYWORDS
    "TOKEN_IDENTIFIER",             //    hello
    "TOKEN_KEYWORD",                //    int
    "TOKEN_NUMBER",                 //    23
    "TOKEN_UNKNOWN",                //    ?
};

void parseBuffer(Buffer *buffer) {
    Token token;

    while((token = tokenizeBuffer(buffer)).kind != TOKEN_EOF) {

		/*
        switch(token.kind) {
            case TOKEN_EOF:

                break;
            case TOKEN_KEYWORD:
				{
					Token identifier = tokenizeBuffer(buffer);
					if (expectToken(TOKEN_IDENTIFIER, tokenizeBuffer(buffer)))
						printf("Variable Declaration [ ]\n");

				}
                break;
            default:
                break;
        }
		*/
		char value[token.len + 1];
		snprintf(value, token.len + 1, "%s", token.value);
		printf("%-8s %s\n", value, kindName[token.kind]);
		// printf("parsed %d %s, %zu;\n", token.kind, token.value, token.len);
    }
}

void parseStatement(Token token) {

}

int expectToken(TokenKind kind, Token token) {
    return token.kind == kind;
}
