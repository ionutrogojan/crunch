#include "lexer.h"

const char *keywords[] = {
    // Numeric Literals
    "u8",
    "u16",
    "u32",
    "u64",
    "uint",
    "i8",
    "i16",
    "i32",
    "i64",
    "int",
    "f32",
    "f64",
    "float",
    // 
    "byte",
    "bool",
    "nil",
    "void",
    //
    "self",
    "return",
    "continue",
    "break",
    "const",
    "enum",
    "struct",
    // Builtin Function
    "if",
    "else",
    "elif",
    "for",
    "while",
    "match",
    // Compiler Flags
    /*
    "define",
    "import",
    "syscall"
    */
    NULL
};

Token tokenizeBuffer(Buffer *buffer) {
   // start offset for non-symbol tokens
    size_t start = 0;
    Token token = { .value = &buffer->data[buffer->index], .len = 1 };

    if (buffer->index < buffer->length) {

        if (checkSkip(buffer)) {
            buffer->index++;
            return tokenizeBuffer(buffer);
        }

        switch (tokenHere(buffer)) {
            case '(':
                // printToken(buffer, "OpenParen");
                token.kind = TOKEN_PAREN_OPEN;
                break;
            case ')':
                // printToken(buffer, "CloseParen");
                token.kind = TOKEN_PAREN_CLOSE;
                break;
            case '[':
                // printToken(buffer, "OpenBracket");
                token.kind = TOKEN_BRACKET_OPEN;
                break;	
            case ']':
                // printToken(buffer, "CloseBracket");
                token.kind = TOKEN_BRACKET_CLOSE;
                break;
            case '{':
                // printToken(buffer, "OpenCurly");
                token.kind = TOKEN_CURLY_OPEN;
                break;	
            case '}':
                // printToken(buffer, "CloseCurly");
                token.kind = TOKEN_CURLY_CLOSE;
                break;
            case '<':
                if (sniffToken(buffer, '=')) {
                    // printToken(buffer, "LessOrEqual");
                    token.kind = TOKEN_LESS_EQUAL;
                    token.len = 2;
                    buffer->index++;
                } else {
                    // printToken(buffer, "Less");
                    token.kind = TOKEN_ARROW_OPEN;
                }
                break;
            case '>':
                if (sniffToken(buffer, '=')) {
                    // printToken(buffer, "GreaterOrEqual");
                    token.kind = TOKEN_GREATER_EQUAL;
                    token.len = 2;
                    buffer->index++;
                } else {
                    // printToken(buffer, "Greater");
                    token.kind = TOKEN_ARROW_CLOSE;
                }
                break;
            case '=':
                if (sniffToken(buffer, '=')) {
                    // printToken(buffer, "Compare");
                    token.kind = TOKEN_COMPARE;
                    token.len = 2;
                    buffer->index++;
                } else {
                    // printToken(buffer, "Equal");
                    token.kind = TOKEN_EQUAL;
                }
                break;
            case '+':
                if (sniffToken(buffer, '+')) {
                    // printToken(buffer, "Increment");
                    token.kind = TOKEN_INCREMENT;
                    token.len = 2;
                    buffer->index++;
                } else if (sniffToken(buffer, '=')) {
                    // printToken(buffer, "PlusEqual");
                    token.kind = TOKEN_PLUS_EQUAL;
                    token.len = 2;
                    buffer->index++;
                } else {
                    // printToken(buffer, "Plus");
                    token.kind = TOKEN_PLUS;
                }
                break;
            case '-':
                if (sniffToken(buffer, '-')) {
                    // printToken(buffer, "Decrease");
                    token.kind = TOKEN_DECREASE;
                    token.len = 2;
                    buffer->index++;
                } else if (sniffToken(buffer, '=')) {
                    // printToken(buffer, "MinusEqual");
                    token.kind = TOKEN_MINUS_EQUAL;
                    token.len = 2;
                    buffer->index++;
                } else {
                    // printToken(buffer, "Minus");
                    token.kind = TOKEN_MINUS;
                }
                break;
            case '*':
                if (sniffToken(buffer, '*')) {
                    // printToken(buffer, "DoublePointer");
                    token.kind = TOKEN_DOUBLE_POINTER;
                    token.len = 2;
                    buffer->index++;
                } else if (sniffToken(buffer, '=')) {
                    // printToken(buffer, "TimesEqual");
                    token.kind = TOKEN_TIMES_EQUAL;
                    token.len = 2;
                    buffer->index++;
                } else if (sniffToken(buffer, '/')) {
                    // printToken(buffer, "CloseComment");
                    token.kind = TOKEN_TIMES_EQUAL;
                    token.len = 2;
                    buffer->index++;
                } else {
                    // printToken(buffer, "Star");
                    token.kind = TOKEN_STAR;
                }
                break;
            case '/':
                if (sniffToken(buffer, '/')) {
                    // printToken(buffer, "CommentLine");
                    token.kind = TOKEN_COMMENT_LINE;
                    token.len = 2;
                    buffer->index++;
                } else if (sniffToken(buffer, '*')) {
                    // printToken(buffer, "OpenComment");
                    token.kind = TOKEN_COMMENT_BLOCK_OPEN;
                    token.len = 2;
                    buffer->index++;
                } else if (sniffToken(buffer, '=')) {
                    // printToken(buffer, "DivideEqual");
                    token.kind = TOKEN_DIVIDE_EQUAL;
                    token.len = 2;
                    buffer->index++;
                } else {
                    // printToken(buffer, "Slash");
                    token.kind = TOKEN_SLASH;
                }
                break;
            case '\\':
                if (sniffToken(buffer, '\\')) {
                    // printToken(buffer, "EscapeSlosh");
                    token.kind = TOKEN_ESCAPE_SLOSH;
                    token.len = 2;
                    buffer->index++;
                } else {
                    // printToken(buffer, "Slosh");
                    token.kind = TOKEN_SLOSH;
                }
                break;
            case '|':
                if (sniffToken(buffer, '|')) {
                    // printToken(buffer, "LogicOr");
                    token.kind = TOKEN_LOGIC_OR;
                    token.len = 2;
                    buffer->index++;
                } else {
                    // printToken(buffer, "BitwiseOr");
                    token.kind = TOKEN_BITWISE_OR;
                }
                break;
            case '.':
                // printToken(buffer, "Dot");
                token.kind = TOKEN_DOT;
                break;
            case ',':
                // printToken(buffer, "Comma");
                token.kind = TOKEN_COMMA;
                break;
            case ':':
                // printToken(buffer, "Colon");
                token.kind = TOKEN_COLON;
                break;
            case '&':
                if (sniffToken(buffer, '&')) {
                    // printToken(buffer, "LogicAnd");
                    token.kind = TOKEN_LOGIC_AND;
                    token.len = 2;
                    buffer->index++;
                } else
                    // printToken(buffer, "BitwiseAnd");
                    token.kind = TOKEN_BITWISE_AND;
                break;
            case '%':
                // printToken(buffer, "Modulo");
                token.kind = TOKEN_MODULO;
                break;
            case '!':
                if (sniffToken(buffer, '=')) {
                    // printToken(buffer, "NotEqual");
                    token.kind = TOKEN_NOT_EQUAL;
                    token.len = 2;
                    buffer->index++;
                } else
                    // printToken(buffer, "LogicNot");
                    token.kind = TOKEN_BANG;
                break;
            case '@':
                // printToken(buffer, "CompilerFlag");
                token.kind = TOKEN_COMPILER_FLAG;
                break;
            case '"':
                // printToken(buffer, "Quotations");
                token.kind = TOKEN_QUOTE;
                break;
            case '\'':
                // printToken(buffer, "SingleQuote");
                token.kind = TOKEN_QUOTE_SINGLE;
                break;
            case '_':
                // printToken(buffer, "Underscore");
                token.kind = TOKEN_UNDERSCORE;
                break;
            default:
                if (checkNumber(buffer)) {

                    start = buffer->index;
                    // this does not support floats, scientific notation, or hex
                    while (checkNumber(buffer)) {
                        if (buffer->index < buffer->length)
                            buffer->index++;
                        else break;
                    }

                    size_t numLen = buffer->index - start;
                    char numVal[numLen + 1];

                    snprintf(numVal, numLen + 1, "%s", &buffer->data[start]);

                    // printf("%04lu %s %s\n", start, numVal, "NumericLiteral");
                    // TOKEN_NUMERIC_VALUE
                    token.kind = TOKEN_NUMBER;
                    token.len = numLen;
                } else if (checkAlpha(buffer)) {

                    start = buffer->index;

                    // string literals need to start with an alphabetic char but can contain numeric values or _
                    while (checkAlpha(buffer) || checkNumber(buffer) || checkToken(buffer, '_')) {
                        if (buffer->index < buffer->length)
                            buffer->index++;
                        else break;
                    }

                    size_t strLen = buffer->index - start;
                    char strVal[strLen + 1];

                    snprintf(strVal, strLen + 1, "%s", &buffer->data[start]);

                    // printf("%04lu %s %s\n", start, strVal, "StringLiteral");
                    if (checkKeyword(keywords, strVal) != -1)
                        token.kind = TOKEN_KEYWORD;
                    else token.kind = TOKEN_IDENTIFIER;
                    token.len = strLen;
                } else {
                    // printToken(buffer, "Unknown"); 
                    token.kind = TOKEN_UNKNOWN;
                }
                break;
        }
        buffer->index++;
        return token;
    }
    token.kind = TOKEN_EOF;
    token.value = NULL;
    token.len = 0;
    return token;
}

void printToken(Buffer *buffer, const char *name) {
    printf("%04lu %c %s\n", buffer->index, tokenHere(buffer), name);
}

char tokenHere(Buffer *buffer) {
    return buffer->data[buffer->index];
}

char tokenNext(Buffer *buffer) {
    if (buffer->index++ < buffer->length) return tokenHere(buffer);
    return '\0';
}

int sniffToken(Buffer *buffer, const char c) {
    size_t i = buffer->index + 1;
    if (i < buffer->length)
        return buffer->data[i] == c;
    return 0;
}

int checkToken(Buffer *buffer, const char c) {
    return buffer->data[buffer->index] == c;
}

int checkNumber(Buffer *buffer) {
    const char c = buffer->data[buffer->index];
    return ((c >= '0') && (c <= '9'));
}

int checkSkip(Buffer *buffer) {
    const char c = buffer->data[buffer->index];
    return ((c == ' ') || (c == '\n') || (c == '\t') || (c == '\r'));
}

int checkAlpha(Buffer *buffer) {
    const char c = buffer->data[buffer->index];
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int checkKeyword(const char *keywords[], const char *name) {
    int same = -1;
    for (int i = 0; keywords[i] != NULL; i++) {
        const char *keyword = keywords[i];
        const char *namePtr = name;
        while (*keyword == *namePtr && *keyword && *namePtr) {
            keyword++;
            namePtr++;

            if (*keyword == '\0' && *namePtr == '\0') {
                same = i;
                break;
            }
        }
    }
    return same;
}
