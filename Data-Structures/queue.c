//
// Queue Implementation
//

#include <stdio.h>
#include <stdlib.h>

//
// Queue Definition
//

typedef struct queue {
	int data;
	struct queue* next;
} queue;

// Initialization Functions
void queue_init(queue **q, int d) {
	*q = (queue *)malloc(sizeof(queue));
	(*q)->data = d;
	(*q)->next = NULL;
}

// Traversal
void queue_traverse(queue *q) {
	if(q == NULL) printf("\n");
	else {
		printf("%d ", q->data);
		queue_traverse(q->next);
	}
}

// Push
void queue_push(queue **q, int d) {
	queue* new;
	
	queue_init(&new, d);
	new->next = *q;
	*q = new;
}

// Pop
queue *find_eol(queue *q);
queue *find_pred(queue *q, int d);

int queue_pop(queue *q) {
	queue *tail;
	queue *pred;
	int data;
	
	tail = find_eol(q);
	data = tail->data;
	pred = find_pred(q, data);
	
	pred->next = NULL;
	free(tail);
	return data;
}
	
// Helper
queue *find_eol(queue *q) {
	if(q->next == NULL) return q;
	else return find_eol(q->next);
}

queue *find_pred(queue *q, int d) {
	if(q->next->data == d) return q;
	else return find_pred(q->next, d);
}
	

int main(int argc, char *argv[]) {
	queue* queue_test;

	queue_init(&queue_test, 10);
	
	queue_traverse(queue_test);
	
	queue_push(&queue_test, 11);
	queue_push(&queue_test, 12);
	queue_push(&queue_test, 13);
	queue_traverse(queue_test);
	
	printf("%d\n", queue_pop(queue_test));
	queue_traverse(queue_test);
	
	return 0;
}