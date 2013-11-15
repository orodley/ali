typedef enum TokenType {
	/* Start the enum from 1, to avoid a clash with the EOF value */
	T_OPEN_PAREN = 1, T_CLOSE_PAREN = 2, T_STRING = 3,
	T_SYMBOL     = 4, T_INTEGER     = 5, T_CHAR   = 6
} TokenType;

typedef struct Token {
	char *str;
	enum TokenType type;
} Token;

LispObj *read_from_string(char str[]);
LispObj *read_from_yybuf(YY_BUFFER_STATE yy_buf);
LispObj *read_from_stream(FILE *stream);
Token    get_token();
