#include "lexer.h"

const char* keywords[] = {
	"i8",
	"i16",
	"i32",
	"i64",
	"u8",
	"u16",
	"u32",
	"u64",
	"f32",
	"f64",
};

void printS(const char s, const char* name) {
	printf("%s '%c'\n", name, s);
}

void parseBuffer(SourceBuffer *buffer) {
	char currentChar = '\0';
	
	size_t start = 0;
	for (buffer->i = 0; buffer->i < buffer->len; buffer->i++) {

		currentChar = buffer->source[buffer->i];

		if (isSkip(currentChar) == 1)
			continue;

		switch (currentChar) {
			case '(':
				printS(currentChar, "ParenLeft");
				continue;
			case ')':
				printS(sourceCode[i], "ParenRight");
				continue;
			case '[':
				printS(sourceCode[i], "BracketLeft");
				continue;
			case ']':
				printS(sourceCode[i], "BracketRight");
				continue;
			case '{':
				printS(sourceCode[i], "CurlyLeft");
				continue;
			case '}':
				printS(sourceCode[i], "CurlyRight");
				continue;
			case '<': // check for EOF
				// sniff ahead to find if we can find an expected char
				if (sourceCode[i + 1] == '=') {
					printf("LessOrEqual \"<=\"\n");
					++i; // increment position because we used the next value
				} else
					printS(sourceCode[i], "ArrowLeft");
				continue;
			case '>': // check for EOF
				if (sourceCode[i + 1] == '=') {
					printf("MoreOrEqual \">=\"\n");
					++i;
				} else
					printS(sourceCode[i], "ArrowRight");
				continue;
			case '=': // check for EOF
				if (sourceCode[i + 1] == '=') {
					printf("CompareEqual \"==\"\n");
					++i;
				} else
					printS(sourceCode[i], "Assignment");
				continue;
			case '+': // check for EOF
				switch (sourceCode[i + 1]) {
					case '+':
						printf("Increment \"++\"\n");
						++i;
						break;
					case '=':
						printf("AssignPlus \"+=\"\n");
						++i;
						break;
					default:
						printS(sourceCode[i], "Plus");
						break;
				}
				continue;
			case '-': // check for EOF
				switch (sourceCode[i + 1]) {
					case '-':
						printf("Decrement \"--\"\n");
						++i;
						break;
					case '=':
						printf("AssignMinus \"-=\"\n");
						++i;
						break;
					default:
						printS(sourceCode[i], "Minus");
						break;
				}
				continue;
			case '*': // check for EOF
				//TODO: ** double pointer, pointer to a pointer
				if (sourceCode[i + 1] == '=') {
					printf("AssignTimes \"*=\"\n");
					++i;
				} else
					printS(sourceCode[i], "Star");
				continue;
			case '/': // check for EOF
				switch (sourceCode[i + 1]) {
					case '/':
						printf("CommentLine \"//\"\n");
						// for now we skip parsing the comment line
						while (sourceCode[i] != '\n' && i < sourceLength)
							++i;
						break;
					// case '*':
						// printf("CommentBlock \"/**/\"\n");
						// loop until you find "*/"
						// break;
					case '=':
						printf("AssignDivide \"/=\"\n");
						++i;
						break;
					default:
						printS(sourceCode[i], "Slash");
						break;
				}
				continue;
			case '\\':
				printS(sourceCode[i], "Slosh");
				continue;
			case '|':
				if (sourceCode[i + 1] == '|') {
					printf("LogicOr \"||\"\n");
					++i;
				} else
					printS(sourceCode[i], "BitwiseOr");
				continue;
			case '.':
				printS(sourceCode[i], "Dot");
				continue;
			case ',':
				printS(sourceCode[i], "Comma");
				continue;
			case ':':
				printS(sourceCode[i], "Colon");
				continue;
			case '&':
				if (sourceCode[i + 1] == '&') {
					printf("LogicAnd \"&&\"\n");
					++i;
				} else
					printS(sourceCode[i], "BitwiseAnd");
				continue;
			case '%':
				printS(sourceCode[i], "Modulo");
				continue;
			case '!':
				if (sourceCode[i + 1] == '=') {
					printf("NotEqual \"!=\"\n");
					++i;
				} else
					printS(sourceCode[i], "LogicNot");
				continue;
			case '@':
				printS(sourceCode[i], "CompFlagAt");
				continue;
			case '\"':
				printS(sourceCode[i], "String");
				// check for \" and skip it. if the " is prefixed by an escape, it's not a valid string closing
				++i; // eat " and move to the first char 
				while(sourceCode[i] != '"' && i < sourceLength) {
					++i;
				}
				continue;
			case '\'':
				printS(sourceCode[i], "Char");
				++i;
				while(sourceCode[i] != '\'' && i < sourceLength) {
					++i;
				}
				// Error, expected '
				continue;
			case '_':
			// this is not a case that could happen outside of a variable name or function name
			// consider removing
				printS(sourceCode[i], "UnderScore");
				continue;
			default:
				if (isNumber(currentChar) == 1) {
					start = i;
					// instead of checking if the next char is a number, create an expect rule
					// if it starts with a number, it's a numeric value so expect { 0..9, e, E, - }
					while (isNumber(sourceCode[i]) == 1 && i < sourceLength)
						++i;
					size_t numLen = i - start;

					char numVal[numLen + 1];

					strncpy(numVal, &sourceCode[start], numLen);
					numVal[numLen] = '\0';

					printf("NumericLiteral %s\n", numVal);
					--i; // ??
					continue;
				} else if (isAlpha(currentChar) == 1) {
					start = i;
					while (isAlpha(sourceCode[i]) == 1 || isNumber(sourceCode[i]) == 1 || sourceCode[i] == '_') {
						if (i < sourceLength) {
							++i;
						} else break;
					}
					size_t strLen = i - start;

					char strVal[strLen + 1];

					strncpy(strVal, &sourceCode[start], strLen);
					strVal[strLen] = '\0';

					printf("Identifier %s\n", strVal);
					--i; // ??
					continue;
				} else {
					printS(currentChar, "Unknown");
					continue;
				}
		}
	}
}

int isSkip(const char c) {
	if ((c ==  ' ') || (c == '\n') || (c == '\t') || (c == '\r'))
		return 1;
	return 0;
}

int isNumber(const char c) {
	if ((c >= '0') && (c <= '9'))
		return 1;
	return 0;
}

int isAlpha(const char c) {
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return 1;
	return 0;
}