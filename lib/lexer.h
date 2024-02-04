#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

#define BUFFER_SIZE 8192 // 8KB buffer size

typedef enum {
	TOKEN_EOF, // END OF FILE
	// SYMBOLS
	TOKEN_PAREN_OPEN, //		(
	TOKEN_PAREN_CLOSE, //		)
	TOKEN_BRACKET_OPEN, //		[
	TOKEN_BRACKET_CLOSE, //		]
	TOKEN_CURLY_OPEN, //		{
	TOKEN_CURLY_CLOSE, //		}
	TOKEN_ARROW_LEFT, //		<
	TOKEN_ARROW_RIGHT, //		>
	TOKEN_EQUAL, //				=
	TOKEN_PLUS, //				+
	TOKEN_MINUS, //				-
	TOKEN_STAR, //				*
	TOKEN_SLASH, //				/
	TOKEN_SLOSH, //				\'
	TOKEN_VBAR, //				|
	TOKEN_DOT, //				.
	TOKEN_COMMA, //				,
	TOKEN_COLON, //				:
	TOKEN_AMPERSAND, //			&
	TOKEN_PERCENT, //			%
	TOKEN_BANG, //				!
	TOKEN_AT, //				@
	// KEYWORDS
	TOKEN_KEYWORD,
	TOKEN_INTEGER,
	TOKEN_FLOAT,
} tokenKind;

typedef struct {
	tokenKind kind;
	char* value;
	size_t len;
} token;

typedef struct {
    size_t index;
    size_t length;
    char data[BUFFER_SIZE];
} Buffer;

void tokenizeBuffer(Buffer *buffer);
char tokenNext(Buffer *buffer);
char tokenHere(Buffer *buffer); 

int sniffToken(Buffer *buffer, const char c);

int checkToken(Buffer *buffer, const char c);
int checkNumber(Buffer *buffer);
int checkSkip(Buffer *buffer);
int checkAlpha(Buffer *buffer);

void printToken(Buffer *buffer, const char *name);

#endif // LEXER_H
