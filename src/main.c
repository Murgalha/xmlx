#include <stdlib.h>
#include <stdio.h>
#include "xmlx.h"

int main(int argc, char *argv[]) {
	if(argc != 2) {
		printf("Invalid number of arguments\n");
		exit(1);
	}

	FILE *fp = fopen(argv[1], "r+");

	Token *t;
	while(!feof(fp)) {
		t = parse_token(fp);

		print_token(t);

		free(t->content);
		free(t);
	}

	fclose(fp);
	return 0;
}
