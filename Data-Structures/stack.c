//
// Stack Implementation
//

#include <stdio.h>
#include <stdlib.h>

// Definition
typedef struct stack {
	int data;
	struct stack* next;
} stack;

// Initialization
void stack_init(stack** s, int d) {
	*s = (stack *)malloc(sizeof(stack));
	(*s)->data = d;
	(*s)->next = NULL;
}

// Traversal
void stack_traverse(stack *s) {
	if(s == NULL) printf("\n");
	else {
		printf("%d ", s->data);
		stack_traverse(s->next);
	}
}

// Push
void stack_push(stack **s, int d) {
	stack *new;
	
	stack_init(&new, d);
	
	new->next = *s;
	*s = new;
}


// Pop
int stack_pop(stack **s) {
	stack* front;
	int data;
	
	front = *s;
	data = front->data;
	*s = front->next;
	
	free(front);
	return data;
}
	
	
// Helper


int main(int argc, char *argv[]) {
	stack *stack_test;
	
	stack_init(&stack_test, 10);
	stack_push(&stack_test, 11);
	stack_push(&stack_test, 12);
	stack_push(&stack_test, 13);
	
	stack_traverse(stack_test);
	
	printf("%d\n", stack_pop(&stack_test));
	
	stack_traverse(stack_test);

	return 0;
}