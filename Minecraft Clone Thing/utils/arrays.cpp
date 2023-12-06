#include "arrays.h"

//I think this works, and if it doesn't, it won't matter for a long time
void popItem(void* basepointer, size_t sizeofitem, int index, size_t sizeofarray) {
	char* basepointerC = (char*)basepointer;

	char* arrayEnd = basepointerC + sizeofarray;

	char* item = basepointerC + (sizeofitem * index);

	memcpy(item, arrayEnd - sizeofitem, sizeofitem);

	memset(arrayEnd - sizeofitem, NULL, sizeofitem);
}


