#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "file.h"

char file_peek_char(FILE *fp) {
	char c = fgetc(fp);
	ungetc(c, fp);
	return c;
}

char file_read_char(FILE *fp) {
	char c = fgetc(fp);
	return c;
}

char *file_read_bytes(FILE *fp, int n) {
	char *str = malloc(sizeof(char) * n + 1);
	int bytes_read = fread(str, sizeof(char), n, fp);

	if(bytes_read != n) {
		printf("ERROR: Could not read %d bytes from file\n", n);
		free(str);
		return NULL;
	}
	str[n] = '\0';
	return str;
}

char *file_read_whitespace(FILE *file) {
	int capacity = 2, len = 0;
	char *str = malloc(sizeof(char) * capacity);
	char c;

	do {
		if(capacity == len) {
			capacity <<= 1;
			str = realloc(str, sizeof(char) * capacity);
		}
		c = fgetc(file);
		str[len++] = c;
	} while(is_whitespace(c));

	len--;
	ungetc(c, file);

	str[len] = '\0';
	return str;
}

char *file_read_text(FILE *file) {
	int capacity = 2, len = 0;
	char *str = malloc(sizeof(char) * capacity);
	char c;

	do {
		if(capacity == len) {
			capacity = capacity << 1;
			str = realloc(str, sizeof(char) * capacity);
		}
		c = file_read_char(file);
		str[len++] = c;
	} while(c != '<');
	len--;
	ungetc(c, file);

	str[len] = '\0';
	str = realloc(str, sizeof(char) * len);

	return str;
}

char *file_read_open_tag(FILE *file) {
	int capacity = 2, len = 0;
	char *str = malloc(sizeof(char) * capacity);
	char c;

	do {
		if(capacity == len) {
			capacity <<= 1;
			str = realloc(str, sizeof(char) * capacity);
		}
		c = fgetc(file);
		str[len++] = c;
	} while(!is_whitespace(c) && c != '>' && c != '/');

	len--;
	ungetc(c, file);
	str[len] = '\0';
	return str;
}

char *file_read_close_tag(FILE *file) {
	int capacity = 2, len = 0;
	char *str = malloc(sizeof(char) * capacity);
	int k = 0;
	char c;

	do {
		if(capacity == len) {
			capacity <<= 1;
			str = realloc(str, sizeof(char) * capacity);
		}
		c = fgetc(file);
		str[len++] = c;
	} while(c != '>');

	len--;
	ungetc(c, file);
	str[len] = '\0';
	return str;
}

char *file_read_attr_name(FILE *file) {
	int capacity = 2, len = 0;
	char *str = malloc(sizeof(char) * capacity);
	int k = 0;
	char c;

	do {
		if(capacity == len) {
			capacity <<= 1;
			str = realloc(str, sizeof(char) * capacity);
		}
		c = fgetc(file);
		str[len++] = c;
	} while(c != '=');

	len--;
	ungetc(c, file);
	str[len] = '\0';
	return str;
}

char *file_read_attr_value(FILE *file) {
	int capacity = 2, len = 0;
	char *str = malloc(sizeof(char) * capacity);
	int k = 0;
	char c;
	str[len++] = fgetc(file);

	do {
		if(capacity == len) {
			capacity <<= 1;
			str = realloc(str, sizeof(char) * capacity);
		}
		c = fgetc(file);
		str[len++] = c;
	} while(c != '"');
	if(len > capacity) {
		str = realloc(str, sizeof(char) * (capacity + 1));
	}
	str[len] = '\0';
	return str;
}

char *file_read_end_close_tag(FILE *file) {
	int k = 0;
	char c;

	char *str = file_read_bytes(file, 2);
	if(str[1] != '>') {
		printf("ERROR: Malformed END_AND_CLOSE_TAG\n");
		return NULL;
	}

	return str;
}
