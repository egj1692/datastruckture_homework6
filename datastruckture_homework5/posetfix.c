/* postfix.c
 *
 *  Created on: Apr 2, 2019
 *      Author: rsyoung
 */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위는 내림차순, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1  /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];
char postfixExp[MAX_EXPRESSION_SIZE];
char postfixStack[MAX_STACK_SIZE];
int evalStack[MAX_STACK_SIZE];

int postfixStackTop = -1;
int evalStackTop = -1;

int evalResult = 0;

void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	char command;

	do{
		printf("\n----------------------------------------------------------------\n");
		printf("--------------------[Lee Jun Gi]  [2017035135]------------------\n");
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();		// infix 연산식을 입력
			break;
		case 'p': case 'P':
			toPostfix();	// infix에서 postfix로 변경
			break;
		case 'e': case 'E':
			evaluation();	// postfix 식 계산
			break;
		case 'd': case 'D':
			debug();		// postfix, infix 계산
			break;
		case 'r': case 'R':
			reset();		// infix, postfix, eval result 값 초기화
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q');
	return 1;
}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;		// posetfixStack에 추가
}

char postfixPop()
{
	char x;
	/* 끝이 아니면 */
    if(postfixStackTop == -1)
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];		// posetfixStack에 추가
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x; 		// 계산할 때, 사용하는 evalstack에 추가
}

int evalPop()
{
    if(evalStackTop == -1)		// stack이 비어있지 않으면
        return -1;
    else
        return evalStack[evalStackTop--]; 		// 계산할 때, 사용하는 evalstack에서 빼기
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */

void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);		// infix 식 입력
}

precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	
	/* \0 문자이면 */
	if (postfixExp == '\0')
		/* 문자 복사 */
		strncpy(postfixExp, c, 1);
	else
		/* 문자 1개 postfixExp 뒤에 붙이기 */
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')
	{
		/* 피연산자이면 */
		if(getPriority(*exp) == operand)
		{
			x = *exp;
        	charCat(&x);
		}
		/* 왼쪽 괄호이면 */
        else if(getPriority(*exp) == lparen) {

        	postfixPush(*exp);	// postfixstack에 추가
        }
		/* 오른쪽 괄호이면 */
        else if(getPriority(*exp) == rparen)
        {
			/* stack에서 왼쪽 괄호가 아니면 postfixExp에 복사 반복 */
        	while((x = postfixPop()) != '(') {
        		charCat(&x);	
        	}
        }
		/* 연산자이면 */
        else
        {
			/* 스택의 top에 있는 연산자와 우선순위가 같거나 작으면 */
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))
            {
				/* 스택의 top에 있는 연산자 postfixExp에 입력*/
            	x = postfixPop();
            	charCat(&x);
            }
            postfixPush(*exp);	// postfixstack에 추가
        }
        exp++;
	}
	// /0문자를 만나면 stack에 남아있는 것을 postfixExp로 입력
    while(postfixStackTop != -1)
    {
    	x = postfixPop();
    	charCat(&x);
    }

}

void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);
 
	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);
	printf("\n");
}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

/**
 * postfixExp의 문자를 하나씩 읽어가면서 evalstack을 이용하여 연산을 한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void evaluation()
{
	int opr1, opr2, i;

	int length = strlen(postfixExp);		// postfix 길이
	char symbol;
	evalStackTop = -1;
	for(i = 0; i < length; i++)
	{
		symbol = postfixExp[i];
		/* 피연산자이면 */
		if(getToken(symbol) == operand) {
			evalPush(symbol - '0');
		}
		/* 연산자이면 */
		else {
			/* 스택에 있는 피연산자 2개 pop하고 */
			opr2 = evalPop();
			opr1 = evalPop();
			/* 2개의 피연산자로 연산 수행 */
			switch(getToken(symbol)) {
			case plus: evalPush(opr1 + opr2); break;
			case minus: evalPush(opr1 - opr2); break;
			case times: evalPush(opr1 * opr2); break;
			case divide: evalPush(opr1 / opr2); break;
			default: break;
			}
		}
	}
	/* 연산을 수행 후 stack에 입력 */
	evalResult = evalPop();
}