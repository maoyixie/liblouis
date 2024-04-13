#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "../../liblouis/liblouis.h"
#include <filesystem>

extern "C" int
LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
	if (Size == 0 || Data == NULL) {
		return 0;
	}

	// Create null-terminated strings for tableList and inString
	char *tableList = (char *)malloc(Size / 2 + 1);
	char *inString = (char *)malloc(Size / 2 + 1);

	if (!tableList || !inString) {
		free(tableList);
		free(inString);
		return 0;
	}

	// Split the input data into two parts for tableList and inString
	memcpy(tableList, Data, Size / 2);
	memcpy(inString, Data + Size / 2, Size / 2);

	// Ensure both strings are null-terminated
	tableList[Size / 2] = '\0';
	inString[Size / 2] = '\0';

	// Call the target function with the fuzzed input
	int ret = lou_compileString(tableList, inString);

	// Cleanup and return
	free(tableList);
	free(inString);
	return 0;
}