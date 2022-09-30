#include "ReadWriteFile.h"

void __write(CHARACTER* hero, const int* death) {
	FILE* out;
	out = fopen(FILE_NAME, "wb");
	if (out == NULL) {
		return;
	}
	for (int i = 0; i < MAX; i++) {
		fwrite(hero + i, sizeof(hero + i), sizeof(hero + i), out);
		fwrite(death + i, sizeof(int), 1, out);
	}
	fclose(out);

}

void __read(CHARACTER* hero, const int* death, FILE* in) {
	for (int i = 0; i < MAX; i++) {
		fread(hero + i, sizeof(hero + i), sizeof(hero + i), in);
		fread(death + i, sizeof(int), 1, in);
	}
}