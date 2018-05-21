//in expression.c
static const OPERATOR operators[] = {
	/* �������� */  
    {2, 17, 1, left2right, oper_lparen},     // ������  
    {2, 17, 17, left2right, oper_rparen},    // ������  
    {2, 12, 12, left2right, oper_plus},      // ��  
    {2, 12, 12, left2right, oper_minus},     // ��  
    {2, 13, 13, left2right, oper_multiply},  // ��  
    {2, 13, 13, left2right, oper_divide},    // ��  
    {2, 13, 13, left2right, oper_mod},       // ģ  
    {2, 14, 14, left2right, oper_power},     // ��  
    {1, 16, 15, right2left, oper_positive},  // ����  
    {1, 16, 15, right2left, oper_negative},  // ����  
    {1, 16, 15, left2right, oper_factorial}, // �׳�  
    /* ��ϵ���� */  
    {2, 10, 10, left2right, oper_lt},        // С��  
    {2, 10, 10, left2right, oper_gt},        // ����  
    {2, 9, 9, left2right, oper_eq},          // ����  
    {2, 9, 9, left2right, oper_ne},          // ������  
    {2, 10, 10, left2right, oper_le},        // ������  
    {2, 10, 10, left2right, oper_ge},        // ��С��  
    /* �߼����� */  
    {2, 5, 5, left2right, oper_and},         // ��  
    {2, 4, 4, left2right, oper_or},          // ��  
    {1, 15, 15, right2left, oper_not},       // ��  
    /* ��ֵ */  
    // BASIC �и�ֵ��䲻���ڱ��ʽ��  
    {2, 2, 2, right2left, oper_assignment},  // ��ֵ  
    /* ��С���ȼ� */  
    {2, 0, 0, right2left, oper_min}          // ջ��  
} 

VARIANT eval( const char expr[])
{
	//...
	//һЩ�����Ķ�������
	
	
	//����׺���ʽת��Ϊ��׺���ʽ 
	list = infix2postfix();
	while(list){
		//ȡ��һ��token
		p = list;
		list = list->next;
		
		//����ǲ������ͱ�����stack��
		if(p->token.type == token_operand){
			p->next = stack;
			stack = p;
			continue;
		} 
		
		//����ǲ�����
		switch(p->token.ator.oper){
			//�ӷ�����
			case oper_plus:
			//ȡ��stack����ĩ����������
			op2 = stack;
			op1 = stack = stack->next;
			
			if(op1->token.var.type == var_double && op2->token.var.type == var_double){
				op1 -> token.var.i += op2->token.var.i;
			} else{
				//�ַ����ļӷ����ϲ������ַ���
				//�������һ������������Ҫת��Ϊ�ַ���
				if(op1 ->token.var.type == var_double){
					spintf(s1, "%g", op1->token.var.i);
				} else{
					strcpy(s1, op1->token.var.s);
				}
				if(op2 -> token.var.type = var_double){
					spintf(s2, "%g", op2->token.var.i);
				}else{
					strcpy(s2, op2->token.var.s);
				}
				op1->token.type = var_string;
				strcat(s1, s2);
				strcpy(op1->token.var.s, s1);
			}
			free(op2);
			break;
			//...
			//������������������
			default:
			//��Ч����������
				break; 
		} 
		free(p);
	} 
	
	value = stack->token.var;
	free(stack);
	
	//���һ��Ԫ�ؼ����ʽ��ֵ
	return value; 
}

//ת��׺���ʽ 
PTLIST infix2postfix(){
	PTLIST list = NULL, tail, p;
	PTLIST stack = NULL;
	//��ʼʱ����ʱ�ռ��һ�����ȼ���͵Ĳ�����
	//�����Ͳ����ж��Ƿ�Ϊ���ˣ��������
	stack = (PTLIST)calloc(1, sizeof(TOKEN_LIST));
	stack->next = NULL;
	stack->token.type = token_operator;
	stack->token.ator = operators[oper_min];
	//beforeΪȫ�ֱ��������ڱ���֮ǰ�Ĳ�����
	//�������òο������½�
	
	memset(&before, 0, sizeof(before));
	for(;;){
		p = (PTLIST)CALLOC(1, sizeof(TOKEN_LIST));
		// calloc�Զ���ʼ��
		p->next = NULL;
		p->token = next_token();
		if(p->token.type == token_operand){
			//����ǲ�������ֱ�����
			if(!list) {
				list = tail = p;
			}else{
				tail->next = p;
				tail = p;
			}
		} else if(p->token.type == token_operator){
			if(p->token.ator.oper == oper_rparen){
				//������
				free(p);
				while(stack->token.ator.oper != oper_lparen){
					p = stack;
					stack = stack->next;
					tail->next = p;
					tail = p;
					tail->next = NULL;
				} 
				p = stack;
				stack = stack->next;
				free(p);
				
			}else{
				while(stack -> token.ator.isp >= token.ator.icp){
					tail->next = stack;
					stack = stack->next;
					tail = tail->next;
					tail->next = NULL;
				}
				p->next = stack;
				stack = p;
			}
		}else{
			free(p);
			break;
		}
	}
	while(stack){
		p=stack;
		stack = stack->next;
		if(p->token.ator.oper != oper_min){
			p->next = NULL;
			tail->next = p;
			tail = p;
			
		}else{
			free(p);
		}
	}
	return list;
}

// ��ȡ��ʶ��
static TOKEN next_token(){
	TOKEN token = {0};
	STRING s;
	int i;
	if(e == NULL){
		return token;
	}
	//ȥ��ǰ���ո� 
	while( *e && isspace(*e)){
		e++;
	}
	if( *e == 0){
		return token;
	}
	if( *e == '"'){
		//�ַ���
		token.type = token_operand;
		token.var.token = var_string;
		e++;
		for(i=0;*e &&*e !='"';i++) {
			token.var.s[i] = *e;
			e++;
		}
		e++;
	}else if(isalpha(*e)){
		//������ַ�Ϊ��ĸ�����������
		//1.����
		//2.�߼�������
		token.type = token_operator;
		for(i=0;isalnum(*e);i++){
			s[i] = toupper(*e);
			e++;
		} 
		s[i] = 0;
		if(!strcmp(s, "AND")){
			token.ator = operators[oper_and];
		}else if(!strcmp(s,"OR")){
			token.ator = operators[oper_or];
		}else if(!strcmp(s,"NOT")){
			token.ator = operators[oper_not];
		}else if(i == 1){
			token.type = token_operand;
			token.var = memory[s[0]-'A'];
			if(token.var.type == var_null){
				memset(&token,0,sizeof(token));
				fpintf(stderr,"����%cδ��ֵ��/n",s[0]);
				exit(EXIT_FAILURE);
			}
		}else{
			goto errorhandler;
		}
	}else if(isdigit(*e) || *e == '.'){
		//����
		token.type = token.operand;
		token.var.type = var_double;
		for(i = 0;isdigit(*e) || *e== '.';i++){
			s[i] = *e;
			e++;
		} 
		s[i] = 0;
		if(sscanf(s, "%lf", &token.var.i)!=1){
			//��ȡ����ʧ��
			//������ 
		}
		
	}else{
		//ʣ������������͹�ϵ�����
		token.type = token_operator;
		switch(*e){
			case '(':
				token.ator = operators[oper_lparen];
				break;
			//...
			//�˴�ʡ�������������Ĵ���
			default:
				//����ʶ��Ĳ����� 
				break; 
		} 
		e++;
	}
	before = token;
	return token;
} 
