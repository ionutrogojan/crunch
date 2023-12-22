#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>
#include <string.h>
#include <stdio.h>

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

typedef enum {
	CHAR_SKIP,
	CHAR_SYMBOL,
	CHAR_ALPHA,
	CHAR_NUMBER,
	CHAR_UNKNOWN,
} charType;

typedef struct {
	size_t i;
	size_t len;
	const char *source;
} SourceBuffer;

int isSkip(const char c);

int isNumber(const char c);

int isAlpha(const char c);

void parseBuffer(SourceBuffer *sourceCode);

// sniff ahead for expected values
int sniff(const char* sourceCode, size_t position, size_t sourceLength);

#endif // LEXER_H