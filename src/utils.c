#include "utils.h"

int is_whitespace(char c) {
	return c == '\n' || c == '\r' || c == '\t' || c == ' ';
}

int is_namestartchar(char c) {
	return isalpha(c) || c == ':' || c == '_';
}

int is_namechar(char c) {
	return is_namestartchar(c) || isdigit(c) || c == '-' || c == '.';
}
