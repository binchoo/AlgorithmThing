#include "skip_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#define INT_MAX 2147483647

Node*
create_node(int value, Node* next) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->value = value;
	new_node->next = next;
	new_node->down = NULL;
	return new_node;
}

List*
create_list() {
	List* new_list = (List*)malloc(sizeof(List));
	new_list->trailer = create_node(INT_MAX, NULL);
	new_list->header = create_node(-1, new_list->trailer);
	new_list->length = 0;
	return new_list;
}

void
print_list(List* list) {
	Node* visit = list->header->next;
	Node* end = list->trailer;
	printf("List(%d) : HEAD - ", list->length);
	while(visit != end) {
		printf("%d - ", visit->value);
		visit = visit->next;
	}
	printf("TRAILER \n");
}

void
destroy_list(List* list) {
	Node* visit = list->header;
	Node* next;
	do {
		next = visit->next;
		free(visit);
		visit = next;
	} while (visit != NULL);
}

SkipList* 
create_skip_list(int level) {
	SkipList* new_skip_list = (SkipList*)malloc(sizeof(SkipList));
	assert(level > 0);
	List** inner_list = (List**)malloc(sizeof(List*)*level);
	for(int i = 0; i < level; i++) {
		inner_list[i] = create_list();
		if(i > 0) {
			inner_list[i]->header->down = inner_list[i-1]->header;
			inner_list[i]->trailer->down = inner_list[i-1]->trailer;

		}
	}

	new_skip_list->inner_list = inner_list;
	new_skip_list->level = level;
	return new_skip_list;
}

void 
append(int value, SkipList* skl) {
	int look_level = skl->level - 1;
	int rand_level = rand() % skl->level;
	Node* visit, *upper = NULL;

	printf("insert %d within hierarchy %d.\n", value, rand_level + 1);
	visit = skl->inner_list[look_level]->header;
	while(visit != NULL) {
		if(value <= visit->next->value) {
			if(look_level <= rand_level) {
				Node* new_node = create_node(value, visit->next);
				visit->next = new_node;
				if(upper != NULL) {
					upper->down = new_node;
				} 
				upper = new_node;
				skl->inner_list[look_level]->length++;
			}
			visit = visit->down;
			look_level--;
		} else {
			visit = visit->next;
		}				
	}
}

void 
eliminate(int value, SkipList* skl) {
	int look_level = skl->level - 1;
	Node* visit = skl->inner_list[look_level]->header;

	while(visit != NULL) {
		if(value == visit->next->value) {
			Node* target = visit->next;
			visit->next = target->next;
			free(target);
			visit = visit->down;
			skl->inner_list[look_level--]->length--;
		} else if(value < visit->next->value) {
			visit = visit->down;
			look_level--;
		} else {
			visit = visit->next;
		}				
	}
}

int get_n(int index, SkipList* skl) {
	assert(index < length(skl));
	Node* visit = skl->inner_list[0]->header;
	for(int i = 0; i <= index; i++)	{
		visit = visit->next;
	}
	return visit->value;
}

void 
print_skip_list(SkipList* skl) {

	int level = skl->level;
	for(int i = level-1; i >= 0; i--) {
		printf("PRINT @list%d ", i);
		print_list(skl->inner_list[i]);
	}
}

void 
destroy_skip_list(SkipList* skl) {
	int level = skl->level;
	for(int i = 0; i < level; i++)
		destroy_list(skl->inner_list[i]);
}

int 
length(SkipList* skl) {
	return skl->inner_list[0]->length;
}

int main() {

	srand(time(NULL));
	SkipList* skl = create_skip_list(4);
	int value;

	while(1) {
		printf("insert value : ");
		scanf("%d", &value);
		if(value == -1) break;
		append(value, skl);
		print_skip_list(skl);
	}

	while(1) {
		printf("delete value : ");
		scanf("%d", &value);
		if(value == -1) break;
		eliminate(value, skl);
		print_skip_list(skl);
	}

	while(1) {
		printf("call index : ");
		scanf("%d", &value);
		if(value == -1) break;
		printf("got %d\n", get_n(value, skl));
		print_skip_list(skl);
	}

	destroy_skip_list(skl);
	return 0;
}
