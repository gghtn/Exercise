#include "ReadWriteFile.h"

void __write(CHARACTER* hero, int* death) {
	FILE* out;
	out = fopen(FILE_NAME, "wb");
	if (out == NULL) {
		return;
	}
	for (int i = 0; i < MAX; i++) {
		fwrite(hero + i, sizeof(hero), 1, out);
		fwrite(death + i, sizeof(int), 1, out);
	}
	fclose(out);

}

void __read(CHARACTER* hero, int* death, FILE* in) {
	for (int i = 0; i < MAX; i++) {
		fread(hero + i, sizeof(hero), 1, in);
		fread(death + i, sizeof(int), 1, in);
	}
}