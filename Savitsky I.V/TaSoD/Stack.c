#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
unsigned long long power( int a, int b){
	if (b == 0) return 1;
	int i = 1;unsigned long long n=a;
	while (i < b) { n *= a; i++; }
	return n;
}

struct stack_over { 
	unsigned long long int data;
	struct stack_over* ptr_next;
};

void push(struct stack_over** top_ptr, const unsigned long long int symbol)
{
	struct stack_over* new_ptr = NULL;

	new_ptr = (struct stack_over*)malloc(4*sizeof(struct stack_over));

	if (new_ptr != NULL)
	{
		memset(new_ptr, 0x00, sizeof(struct stack_over));
		new_ptr->data = symbol;
		new_ptr->ptr_next = *top_ptr;
		*top_ptr = new_ptr;
	}
}

unsigned long long int pop(struct stack_over** top_ptr)
{
	struct stack_over* temp_ptr = NULL;
	unsigned long long int pop_symbol = '\0';

	if (*top_ptr == NULL)
	{
		return EXIT_SUCCESS;
	}

	temp_ptr = *top_ptr;
	pop_symbol = (*top_ptr)->data;
	*top_ptr = (*top_ptr)->ptr_next;

	free(temp_ptr);

	return pop_symbol;
}

int main(int argc, char* argv[])
{
	struct stack_over* stack_pop = NULL;
	struct stack_over* stack_number = NULL;
	struct stack_over* stack_result = NULL;
	enum znak { WSPORNIK = 1, DODATEK, MNOZENIE, POTEGOWANIE };
	int choice = 0;
	char  dump = '\0', polska[2501] = "\0";
	int value1 = 0, value2 = 0, index = 0,  i = 0,   flag=0, type=0;
	unsigned long long int number = 0, result = 0, b = 0, a = 0, symbol = 0;
	char nameof[256]="\0";
	printf("Enter the primer>");
	if (stdin != NULL) {
		while (1) {
			symbol = fgetc(stdin);
			if (symbol == '\n') break;
			if (symbol >= '0' && symbol <= '9') {
				polska[index] = symbol;
				index++;
			}
			else {
				
				if (symbol != '(' && symbol != '\n') { polska[index] = ' ';index++; }
				if (symbol == '(') { dump = fgetc(stdin);if (dump == '-') { flag = 1; } ungetc(dump, stdin); }
				if (symbol == '(' || symbol == ')')value1 = WSPORNIK;
				else if (symbol == '+' || symbol == '-')value1 = DODATEK;
				else if (symbol == '*' || symbol == '/' || symbol == '%')value1 = MNOZENIE;
				else if (symbol == '^')value1 = POTEGOWANIE;
				else continue;
				if (stack_pop != NULL) {
					if (stack_pop->data == '(' || stack_pop->data == ')')value2 = WSPORNIK;
					if (stack_pop->data == '+' || stack_pop->data == '-') value2 = DODATEK;
					if (stack_pop->data == '*' || stack_pop->data == '/' || stack_pop->data == '%')value2 = MNOZENIE;
					if (stack_pop->data == '^')value2 = POTEGOWANIE;
				}
				if (symbol == ')') {
					while (stack_pop != NULL && stack_pop->data != '(') {
						if (stack_pop == NULL) { printf("Error");return EXIT_SUCCESS; }
						polska[index] = pop(&stack_pop);index++;
						if (stack_pop != NULL && stack_pop->data != '(') { polska[index] = ' ';index++; }
						else {

							pop(&stack_pop);
							break;

						}
					}
				}
				else if (value1 > value2 || symbol == '(') {
					if (stack_pop != NULL && stack_pop->data == '(' && symbol == '-' && flag==1) { polska[index] = '0';
					index++;polska[index] = ' ';index++;flag = 0;//push(&stack_pop, (char)symbol);
					}
					push(&stack_pop, (char)symbol);
				}
				else if (value1 == value2) { polska[index] = pop(&stack_pop);
				index++;polska[index] = ' ';index++;push(&stack_pop, (char)symbol);}
				else { while (stack_pop != NULL) { polska[index] = pop(&stack_pop);index++;polska[index] = ' ';index++; }push(&stack_pop, (char)symbol); }
				value1 = 0;value2 = 0;
			}
		}
	}
	while (stack_pop != NULL) { polska[index] = ' ';index++;polska[index] = pop(&stack_pop);index++; }
		index = 0;
		
		while (polska[index] != '\0') { 
			if (polska[index] >= '0' && polska[index] <= '9') { 
				i++; 
				if (i > 19 ||(i==19 && polska[index]>'7'))type = 1;
			} 
			else i = 0; 
			index++;
			
		}
		index = 0;
		do {
			symbol = polska[index];
			index++;
			if (symbol >= '0' && symbol <= '9') {
				push(&stack_number, symbol - '0');
			}
			if (symbol == ' ' && stack_number != NULL) {
				i = 0;
				while (stack_number != NULL) { 
					number += power(10, i) * pop(&stack_number);
					i++; }

				push(&stack_result, number);number = 0;
			}
			if (symbol == '+') {
				b = pop(&stack_result);if (stack_result == NULL)a = 0; else a = pop(&stack_result); result = a + b;push(&stack_result, result);result = 0;
			}
			if (symbol == '-') {
				b = pop(&stack_result);
				//result = -b;
				if (stack_result == NULL) { a = 0; }
				else { a = pop(&stack_result);  }
				//result = a + result;
				result = a - b;
				push(&stack_result, result);result = 0;
			}
			if (symbol == '*') {
				b = pop(&stack_result);a = pop(&stack_result);result = a * b;push(&stack_result, result);result = 0;
			}
			if (symbol == '/') {
				b = pop(&stack_result);a = pop(&stack_result);if (b == 0) { printf("Proshu prosh'eniya, delit' na nol' nel'zya");return EXIT_SUCCESS; } result = a / b;push(&stack_result, result);result = 0;
			}
			if (symbol == '%') {
				b = pop(&stack_result);a = pop(&stack_result);
				if (b == 0) { printf("Proshu prosh'eniya, delit' na nol' nel'zya");return EXIT_SUCCESS; }
				if (a < 0) {
					a *= (-1);
					result = a % b;
					result = b - result;
				}
				else result = a % b;push(&stack_result, result);result = 0;
			}
			if (symbol == '^') {
				b = pop(&stack_result);a = pop(&stack_result);if (b < 0) { if (a == 0){ printf("Infinity\n");return; }  a = 0; printf("This calculator don't work with floating point numbers\n"); }if (b == 0)a = 1; i = 1;result = a; while (i < b) { i++; result *= a; }push(&stack_result, result);
			}

		} while (symbol != '\0');
		
		printf("Polska nagrywac jest %s", polska);
		if(type)
		printf("\nResult is %llu", pop(&stack_result));
		else printf("\nResult is %lld", pop(&stack_result));
		return EXIT_SUCCESS;
	}
	