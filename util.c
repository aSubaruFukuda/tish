#include "util.h"

void fatal(char *s, int n) {
	fprintf(stderr, "Fatal: %s\n", s);
	exit(n);
}
