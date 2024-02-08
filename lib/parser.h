#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

void parseBuffer(Buffer *buffer);

int expectToken(TokenKind kind, Token token);

#endif // PARSER_H
