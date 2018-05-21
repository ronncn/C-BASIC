//in basic_io.h
#define MEMORY_SIZE (26)
#define PROGRAM_SIZE (10000)

typedef enum{
	var_null = 0,
	var_double ,
	var_string
} variant_type;
typedef char STRING[128];
typedef struct{
	variant_type type;
	union{
		double i;
		STRING s;
	};
} VARIANT;

typedef struct{
	int ln;
	STRING line;
}CODE;

extern VARIANT memory[MEMORY_SZIE];
extern CODE code[PROGRAM_SIZE];
extern int cp;
extern int code_size;

