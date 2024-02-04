#include "lexer.h"

void tokenizeBuffer(Buffer *buffer) {
   // start offset for non-symbol tokens
    size_t start = 0;

    while (buffer->index < buffer->length) {

        if (checkSkip(buffer)) {
            buffer->index++;
            continue;
        }

        switch (tokenHere(buffer)) {
            case '(':
                printToken(buffer, "OpenParen");
                break;
            case ')':
                printToken(buffer, "CloseParen");
                break;
            case '[':
                printToken(buffer, "OpenBracket");
                break;	
            case ']':
                printToken(buffer, "CloseBracket");
                break;
            case '{':
                printToken(buffer, "OpenCurly");
                break;	
            case '}':
                printToken(buffer, "CloseCurly");
                break;
            case '<':
                if (sniffToken(buffer, '=')) {
                    printToken(buffer, "LessOrEqual");
                    buffer->index++;
                } else {
                    printToken(buffer, "Less");
                }
                break;
            case '>':
                if (sniffToken(buffer, '=')) {
                    printToken(buffer, "GreaterOrEqual");
                    buffer->index++;
                } else {
                    printToken(buffer, "Greater");
                }
                break;
            case '=':
                if (sniffToken(buffer, '=')) {
                    printToken(buffer, "Compare");
                    buffer->index++;
                } else {
                    printToken(buffer, "Equal");
                }
                break;
            case '+':
                if (sniffToken(buffer, '+')) {
                    printToken(buffer, "Increment");
                    buffer->index++;
                } else if (sniffToken(buffer, '=')) {
                    printToken(buffer, "PlusEqual");
                    buffer->index++;
                } else {
                    printToken(buffer, "Plus");
                }
                break;
            case '-':
                if (sniffToken(buffer, '-')) {
                    printToken(buffer, "Decrease");
                    buffer->index++;
                } else if (sniffToken(buffer, '=')) {
                    printToken(buffer, "MinusEqual");
                    buffer->index++;
                } else {
                    printToken(buffer, "Minus");
                }
                break;
            case '*':
                if (sniffToken(buffer, '*')) {
                    printToken(buffer, "DoublePointer");
                    buffer->index++;
                } else if (sniffToken(buffer, '=')) {
                    printToken(buffer, "TimesEqual");
                    buffer->index++;
                } else if (sniffToken(buffer, '/')) {
                    printToken(buffer, "CloseComment");
                    buffer->index++;
                } else {
                    printToken(buffer, "Star");
                }
                break;
            case '/':
                if (sniffToken(buffer, '/')) {
                    printToken(buffer, "CommentLine");
                    buffer->index++;
                } else if (sniffToken(buffer, '*')) {
                    printToken(buffer, "OpenComment");
                    buffer->index++;
                } else if (sniffToken(buffer, '=')) {
                    printToken(buffer, "DivideEqual");
                    buffer->index++;
                } else {
                    printToken(buffer, "Slash");
                }
                break;
            case '\\':
                if (sniffToken(buffer, '\\')) {
                    printToken(buffer, "EscapeSlosh");
                    buffer->index++;
                } else {
                    printToken(buffer, "Slosh");
                }
                break;
            case '|':
                if (sniffToken(buffer, '|')) {
                    printToken(buffer, "LogicOr");
                    buffer->index++;
                } else {
                    printToken(buffer, "BitwiseOr");
                }
                break;
            case '.':
                printToken(buffer, "Dot");
                break;
            case ',':
                printToken(buffer, "Comma");
                break;
            case ':':
                printToken(buffer, "Colon");
                break;
            case '&':
                if (sniffToken(buffer, '&')) {
                    printToken(buffer, "LogicAnd");
                    buffer->index++;
                } else
                    printToken(buffer, "BitwiseAnd");
                break;
            case '%':
                printToken(buffer, "Modulo");
                break;
            case '!':
                if (sniffToken(buffer, '=')) {
                    printToken(buffer, "NotEqual");
                    buffer->index++;
                } else
                    printToken(buffer, "LogicNot");
                break;
            case '@':
                printToken(buffer, "CompilerFlag");
                break;
            case '"':
                printToken(buffer, "Quotations");
                break;
            case '\'':
                printToken(buffer, "SingleQuote");
                break;
            case '_':
                printToken(buffer, "Underscore");
                break;
            default:
                if (checkNumber(buffer)) {

                    start = buffer->index;

                    while (checkNumber(buffer)) {
                        if (buffer->index < buffer->length)
                            buffer->index++;
                        else break;
                    }

                    size_t numLen = buffer->index - start;
                    char numVal[numLen + 1];

                    snprintf(numVal, numLen + 1, "%s", &buffer->data[start]);

                    printf("%04lu %s %s\n", start, numVal, "NumericLiteral");
                    continue;
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

                    printf("%04lu %s %s\n", start, strVal, "StringLiteral");
                    continue;
                } else {
                    printToken(buffer, "Unknown"); 
                }
                break;
        }
        buffer->index++;
    }
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
