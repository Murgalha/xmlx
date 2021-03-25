#ifndef _XML_LEXER_H_
#define _XML_LEXER_H_

#define FOREACH(_)								\
	_(BEGIN_TAG)								\
	_(END_TAG)									\
	_(END_AND_CLOSE_TAG)						\
	_(CLOSE_TAG)								\
	_(ATTR_NAME)								\
	_(ATTR_VALUE)								\
	_(TEXT)										\
	_(EQUAL_SIGN)								\
	_(WHITESPACE)								\
	_(ERROR)									\
	_(END_OF_FILE)

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

typedef enum {
    FOREACH(GENERATE_ENUM)
} TOKENTYPE;

static const char *token_type[] = {
    FOREACH(GENERATE_STRING)
};

typedef struct {
	TOKENTYPE type;
	char *content;
} Token;

void print_token(Token *);
char *alloc_char(char);
Token *parse_token(FILE *);

#endif
