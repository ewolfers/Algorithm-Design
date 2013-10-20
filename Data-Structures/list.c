//
// Linked List Implementation
//

#include <stdio.h>
#include <stdlib.h>

//
// Linked List Definitions
//

// Singly-Linked
typedef struct slist {
	int data;
	struct slist *next;
} slist;

// Doubly-Linked
typedef struct dlist {
	int data;
	struct dlist *next;
	struct dlist *prev;
} dlist;

// Initialization Functions
void slist_init(slist **l, int d) {
	*l = (slist *)malloc(sizeof(slist));
	(*l)->data = d;
	(*l)->next = NULL;
}

void dlist_init(dlist **l, int d) {
	*l = (dlist *)malloc(sizeof(dlist));
	(*l)->data = d;
	(*l)->next = (*l)->prev = NULL;
}

//
// Traversal, Add, Remove Functions
//

// Traversal
void slist_traverse(slist *l) {
	if(l == NULL) printf("\n");
	else {
		printf("%d ", l->data);
		slist_traverse(l->next);
	}
}

void dlist_traverse(dlist *l) {
	if(l == NULL) printf("\n");
	else {
		printf("%d ", l->data);
		dlist_traverse(l->prev);
	}
}

// Add
void slist_add(slist **l, int d) {
	slist *new;
	
	slist_init(&new, d);
	new->next = *l;
	*l = new;
}

void dlist_add(dlist **l, int d) {
	dlist *new;
	
	dlist_init(&new, d);
	(*l)->prev = new;
	new->next = *l;
	*l = new;
}

// Remove
int slist_exists(slist *l, int d);
slist *slist_find(slist *l, int d);
slist *slist_find_predecessor(slist *l, int d);

int dlist_exists(dlist *l, int d);
dlist *dlist_find(dlist *l, int d);
dlist *dlist_find_predecessor(dlist *l, int d);

void slist_remove(slist **l, int d) {
	slist *dead;
	slist *pred;
	
	if(slist_exists(*l, d)) {
		dead = slist_find(*l, d);
		pred = slist_find_predecessor(*l, d);
		
		if(pred == NULL) *l = dead->next; // Dead node = head of list
		else pred->next = dead->next; // General case
	
		free(dead);
	}
}

void dlist_remove(dlist **l, int d) {
	dlist *dead;
	dlist *pred;
	
	if(dlist_exists(*l, d)) {
		dead = dlist_find(*l, d);
		pred = dlist_find_predecessor(*l, d);
		
		if(pred == NULL) {
			dead->next->prev = NULL;
			*l = dead->next;
		} else {
			dead->next->prev = pred;
			pred->next = dead->next;
		}
		
		free(dead);
	}
}
	
// Helper Functions
int slist_exists(slist *l, int d) {
	if(l == NULL) return 0;
	if(l->data == d) return 1;
	else return slist_exists(l->next, d);
}

int dlist_exists(dlist *l, int d) {
	if(l == NULL) return 0;
	if(l->data == d) return 1;
	else return dlist_exists(l->next, d);
}

slist *slist_find(slist *l, int d) {
	if(l == NULL) return NULL;
	if(l->data == d) return l;
	else slist_find(l->next, d);
}

dlist *dlist_find(dlist *l, int d) {
	if(l == NULL) return NULL;
	if(l->data == d) return l;
	else dlist_find(l->next, d);
}

slist *slist_find_predecessor(slist *l, int d) {
	if(l->data == d) return NULL;
	if(l->next->data == d) return l;
	else return slist_find_predecessor(l->next, d);
}

dlist *dlist_find_predecessor(dlist *l, int d) {
	if(l->data == d) return NULL;
	if(l->next->data == d) return l;
	else return dlist_find_predecessor(l->next, d);
}

dlist *dlist_find_eol(dlist *l) {
	if(l->next == NULL) return l;
	else return(dlist_find_eol(l->next));
}

int main() {
	slist *slist_test;
	dlist *dlist_test;
	
	slist_init(&slist_test, 15);
	slist_add(&slist_test, 10);
	slist_add(&slist_test, 11);
	slist_add(&slist_test, 12);
	slist_add(&slist_test, 13);
	slist_remove(&slist_test, 15);
	slist_traverse(slist_test);
	
	dlist_init(&dlist_test, 20);
	dlist_add(&dlist_test, 10);
	dlist_add(&dlist_test, 11);
	dlist_add(&dlist_test, 12);
	dlist_add(&dlist_test, 13);
	dlist_remove(&dlist_test, 11);
	dlist_traverse(dlist_find_eol(dlist_test));
}