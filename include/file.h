#ifndef _FILE_H_
#define _FILE_H_

#include <stdbool.h>
#include "utils.h"

char file_peek_char(FILE *);
char file_read_char(FILE *);
char *file_read_bytes(FILE *, int);
char *file_read_whitespace(FILE *);
char *file_read_text(FILE *);
char *file_read_open_tag(FILE *);
char *file_read_close_tag(FILE *);
char *file_read_attr_name(FILE *);
char *file_read_attr_value(FILE *);
char *file_read_end_close_tag(FILE *);

#endif
