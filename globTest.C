#include <glob.h>
#include <stdio.h>

int main() {

	glob_t globbuf;
	int err = glob("*", 0, NULL, &globbuf);
	if(err == 0) {
		for(size_t i = 0; i < globbuf.gl_pathc; i++) {
			printf("%s\n", globbuf.gl_pathv[i]);
		}
		globfree(&globbuf);
	}
	return 0;
}
