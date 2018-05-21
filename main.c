// in mian.c
typedef enum{
	key_input = 0;
	key_print,
	key_for,
	key_next,
	key_while,
	key_wend,
	key_if,
	key_else,
	key_endif,
	key_goto,
	key_let
} keywords;

keywords yacc(const STRING line){
	if(!strnicmp(line,"INPUT ",6)){
		return key_input;
	}else if(!strnicmp(line,"PRINT ",6)){
		return key_print;
	}else if(!strnicmp(line,"FOR ",4)){
		return key_for; 
	}else if(!strnicmp(line,"NEXT")){
		return key_next
	}else if(!strnicmp(line,"WHILE ", 6)){
		return key_while;
	}else if(!strnicmp(line,"WEND")){
		return key_wend;
	}else if(!strnicmp(line,"IF " ,3)){
		return key_id;
	}else if(!strnicmp(line,"ELSE")){
		return key_else;
	}else if(!strnicmp(line,"END IF")){
		return key_endif;
	}else if(!strnicmp(line,"GOTO ",5)){
		return key_goto;
	}else if(!strnicmp(line,"LET ",4)){
		return key_let;
	}
	return -1;
} 

void (*key_func[])(cosnt STRING) = {
	exec_input,
	exec_print,
	exec_for,
	exec_nextl,
	exec_while,
	exec_wend,
	exec_if,
	exec_else,
	exec_endif,
	exec_goto,
	exec_assignment
};

int main(int argc, char *argv[]){
	if(argc != 2){
		fprintf(stderr, "usage: %s basic_script_file/n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	load_program(argv[1]);
	
	while(cp<code_size){
		(*key_func[yacc(code[cp].line)])(code[cp].line);
		cp++;
	}
	
	return EXIT_SUCCESS;
}
