struct node {
	struct node* next;
	struct node* down;
	int value;
};

struct list {
	struct node* header;
	struct node* trailer;
	int length;
};

struct skip_list {
	struct list** inner_list;
	int level;
};

typedef struct node Node;
Node* create_node(int value, Node*);

typedef struct list List;
List* create_list();
void print_list(List*);
void destroy_list(List*);

typedef struct skip_list SkipList;
SkipList* create_skip_list(int level);
void append(int value, SkipList*);
void eliminate(int value, SkipList*);
int get_n(int index, SkipList*);
void print_skip_list(SkipList*);
void destroy_skip_list(SkipList*);
int length(SkipList*);
