#pragma once

typedef struct l
{
	char letter[9], code[9];
	int prob;
}LETTER;

typedef struct tree
{
	LETTER *l;
	struct tree *left, *right;
}NODE_TREE;

typedef struct node
{
	NODE_TREE *info;
	struct node *next;
}NODE;

void addInQueue(NODE **, NODE_TREE *);
NODE_TREE* removeFromQueue(NODE **);
void readFromFile(NODE **);
void writeQueue(NODE *);
NODE_TREE* search(NODE *, char);
NODE_TREE* newTreeNode(LETTER *info);
void huffman(NODE **);
void code(NODE_TREE *, NODE_TREE *);
void preorder(NODE_TREE *);
char* messageCheck(char *);
