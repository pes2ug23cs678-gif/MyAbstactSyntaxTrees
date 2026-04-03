#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	char value;
	struct node * left;
	struct node * right;
}NODE;//We are having a syntax tree over here!!!

NODE * getNode(char val){
	NODE * Tempnode = (NODE*)malloc(sizeof(NODE));
	Tempnode->value = val;
	Tempnode->left = NULL;
	Tempnode->right = NULL;
	return Tempnode; //We are returning a new node over here!!!
}

char pop(char * Stack, int * top){
	if(*top == 0){
		printf("We cannot pop over here, for there are no elements to be seen now!!!");
		return ' ';
	}
	else{
		(*top)--;
		char a = Stack[*top]; //This is the success part over here!!!
		return a;
	}
}//This is where we would be popping the topmost element over here!!!!

int CheckGood(char c, char * list, int size){
	for(int i = 0; i < size; i++){
		if(list[i] == c){
			return 1;
		}
	}//This returns 1 if successful!!!
	return 0;
}//This is where we would be checking if this list is passable or not!!!

int push(int top, char * Stack, char c, int max){
	if(top == max){
		printf("Sorry, we cannot do this push any further!!!");
	}
	else{
		Stack[top] = c;
		top++;//This is the success case to be seen over here!!!
	}
	return top;
}//This is where we are creating these two stacks over here!!!


void Print(char * stack, int top){
	for(int i = 0; i < top; i++){
		printf("%c", stack[i]);
	}
}//This is another place where the DRY principle would be used over here!!!

char peek(char * String, int top){
	return String[top];
}

int push0(int top, NODE * stack[], NODE * Tempnode, int max){
	if(top == max){
		printf("Sorry, we cannot add in any new value further as of now!!!");
	}
	else{
		stack[top] = Tempnode;//This is where we are adding the new element over here!!!
		top++;
	}
	return top;
}

NODE * pop0(NODE * stack[], int * top3){
	if(*top3 == 0){
		printf("Sorry, we cannot do any more pop operation over here!!!");
		return NULL;
	}//This is the ending of the failure case to be seen over here!!!
	else{
		(*top3)--;
		return stack[*top3];
	}//This is the ending of the successful case over here!!!
}

void PrintTree(NODE * Root){
	if(Root == NULL){
		return ;
	}
	PrintTree(Root->left);
	printf("%c ", Root->value);
	PrintTree(Root->right);
}

int main(){
	int top1 = 0; //This would be the top pointer for the first stack over here!!!
	int top2 = 0; //This would be the top pointer for the second stack over here!!!
	int max = 9;//This is the maximum size over here!!!
	char List1[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	char List2[4] = {'+', '-', '*', '/'};//We have the passing lists to be seen over here!!!
	char NewList[max];//This is the initialization part to be seen over here!!!
	for(int i = 0; i < max; i++){
		char c;//We would be adding these one by one over here
		printf("Add the number or sign required over here: ");
		scanf(" %c", &c);
		if((CheckGood(c, List1, 10) == 1) || (CheckGood(c, List2, 4) == 1)){
			NewList[i] = c;//We are adding them one by one!!!
		}//We can continue over here!!!
	}//This is the first for loop over here!!!
	if(CheckGood(' ', NewList, max) == 1){
		printf("Sorry, we cannot continue any further over here, for we are having blank spaces present over here!!");
		return -1;//This is the failure case over here!!!
	}
	else{
		char stack1[max];
		char stack2[max];//This is yet another initialization phase over here!!!
		char list1[2] = {'+', '-'};
		char list2[2] = {'*', '/'};
		for(int j = 0; j < max; j++){
			if(CheckGood(NewList[j], List1,10) == 1){
				top1 = push(top1, stack1, NewList[j], max);
			}//Here, we would be using the help of the stack1!!!
			else{
				if(top2 == 0){
					top2 = push(top2, stack2, NewList[j], max);
				}
				else{
					if(CheckGood(NewList[j], list2, 2) == 1){
						if(CheckGood(peek(stack2, top2-1), list1, 2) == 1){
							top2 = push(top2, stack2, NewList[j], max);
						}//0
						else{
							char Top0 = pop(stack2, &top2);
							top1 = push(top1, stack1, Top0, max);
							top2 = push(top2, stack2, NewList[j], max);
						}
					}//1
					else{
						while(top2>0){
							char Top0 = pop(stack2, &top2);
							top1 = push(top1, stack1, Top0, max);
						}
						top2 = push(top2, stack2, NewList[j], max);
					}
				}//2
			}
		}
		char top0 = pop(stack2, &top2);
		top1 = push(top1, stack1, top0, max);
		NODE * stack[max]; //This would be there just in case over here!!!
		int top3 = 0;
		for(int k = 0; k < top1; k++){
			NODE * Tempnode = getNode(stack1[k]);//This is going to be there for each and every case present over here!!!
			if(CheckGood(Tempnode->value, List1, 10) == 1){
				top3 = push0(top3, stack, Tempnode, max);
			}
			else{
				NODE * Node0 = pop0(stack, &top3);
				NODE * Node1 = pop0(stack, &top3);//This is where we are going to do the pop, then we would slowly be building the tree and then, we shall push the tree back to the node!!!
				Tempnode->left = Node0;
				Tempnode->right = Node1;
				top3 = push0(top3, stack, Tempnode, max);
			}
		}
		PrintTree(stack[0]);
		printf("\n");
	}//We can continue further over here!!!
	return 0;//This is the ending of the successful implementation over here!!!
}//This would be our main function....we would be calling all the subfunctions from here!!
