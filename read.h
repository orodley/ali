enum TokenType {
	/* Start the enum from 1, to avoid a clash with the EOF value */
	T_OPEN_PAREN = 1, T_CLOSE_PAREN = 2, T_STRING = 3,
	T_SYMBOL     = 4, T_INTEGER     = 5
};

struct Token {
	char *str;
	enum TokenType type;
};

struct LispObj *read_from_string(char str[]);
struct LispObj *read_from_stream(FILE *stream);
struct Token    get_token();
