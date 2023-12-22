#include <stdio.h>

#include "lib/lexer.h"

#define BUFFER_SIZE 8192 // 8KB buffer size

int main(int argc, char **argv) {

	char *sourceName = argv[1];
	FILE *sourceFile;

	// "rb" for reading in binary mode
	if ((sourceFile = fopen(sourceName, "rb")) == NULL) {
		printf("Unable to open %s file\n", sourceName);
		return 1;
	}

	char buffer[BUFFER_SIZE];
	// Read the file 8KB at a time until the end
	
	// SourceBuffer buffer;
	
	
	size_t bytes_read;
	while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, sourceFile)) > 0) {
		parseBuffer(buffer, bytes_read);
	}

	fclose(sourceFile);
	return 0;
}