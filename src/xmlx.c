#include <stdlib.h>
#include <stdio.h>
#include "xmlx.h"
#include "file.h"

bool inside_tag = false;

void print_token(Token *t) {
	printf("{%s} -> '%s'\n", token_type[t->type], t->content);
}

char *alloc_char(char c) {
	char *str = malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return str;
}

Token *parse_token(FILE *fp) {
	char c = file_peek_char(fp);
	char c2;
	char *str;
	Token *t = malloc(sizeof(Token));

	int k = 0;
	switch(c) {
	case EOF:
		t->content = alloc_char(c);
		t->type = END_OF_FILE;
		fgetc(fp);
		break;
	case '<':
		fgetc(fp);
		c2 = file_peek_char(fp);
		ungetc('<', fp);
		if(c2 == '/') {
			t->content = file_read_close_tag(fp);
			t->type = END_TAG;
		}
		else {
			t->content = file_read_open_tag(fp);
			t->type = BEGIN_TAG;
			inside_tag = true;
		}
		break;
	case '>':
		t->content = alloc_char(c);
		t->type = CLOSE_TAG;
		inside_tag = false;
		fgetc(fp);
		break;
	case '/':
		t->content = file_read_end_close_tag(fp);
		t->type = END_AND_CLOSE_TAG;
		inside_tag = false;
		break;
	case '"':
		t->content = file_read_attr_value(fp);
		t->type = ATTR_VALUE;
		break;
	case '=':
		t->content = alloc_char(c);
		t->type = EQUAL_SIGN;
		fgetc(fp);
		break;
	case ' ':
	case '\n':
	case '\t':
	case '\r':
		t->content = file_read_whitespace(fp);
		t->type = WHITESPACE;
		break;
	default:
		if(inside_tag) {
			t->content = file_read_attr_name(fp);
			t->type = ATTR_NAME;
		}
		else {
			t->content = file_read_text(fp);
			t->type = TEXT;
		}
		break;
	}
	return t;
}
