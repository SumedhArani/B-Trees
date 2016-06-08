#include "node.h"

void insert(int, node**);
void insert_leaf(int, node*);
void insert_nonleaf(int, node*, node*);
void insert_parent(int, node*, node*, node*);
void overflow(int, node*, node*);