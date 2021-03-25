# xmlx

## About
This program parses an XML file passed as a command line argument and spits out to stdout the following structure for each token:
```
{TOKEN TYPE} -> LEXEME
```

## Lexing
There are currently 11 token types that the parser identifies (but will increase with time):
- **BEGIN_TAG** '<NAME'
- **END_TAG** '>'
- **END_AND_CLOSE_TAG** '/>'
- **CLOSE_TAG** '</NAME>
- **ATTR_NAME** Text inside tag before EQUAL_SIGN
- **ATTR_VALUE** Text inside tag after EQUAL_SIGN that is between quotes
- **TEXT** Pure text inside a tag
- **EQUAL_SIGN** '='
- **WHITESPACE** ' \n\r\t'
- **END_OF_FILE** Special EOF character
- **ERROR** Any other case that does not fit

## Compiling and running
To compile and run, a Makefile is provided, so simply run:
```
make
./xmlx FILE
```
