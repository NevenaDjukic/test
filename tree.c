#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int size;

void addInQueue(NODE **phead, NODE_TREE *info)
{
	NODE *newLetter = (NODE *)malloc(sizeof(NODE));
	newLetter->info = (NODE_TREE*)malloc(sizeof(NODE_TREE));
	newLetter->info = info;
	newLetter->next = 0;
	if ((*phead) == 0)
		*phead = newLetter;
	else
	{
		NODE *p = *phead;
		while ((p->info->l->prob < newLetter->info->l->prob) && (p->next) != NULL)
			p = p->next;
		while ((p->info->l->prob == newLetter->info->l->prob) && (p->info->l->letter[0] < newLetter->info->l->letter[0])
			&& (p->next) != NULL)
			p = p->next;
		if ((p->info->l->prob > newLetter->info->l->prob) || 
			(p->info->l->prob == newLetter->info->l->prob && p->info->l->letter[0] > newLetter->info->l->letter[0]))
		{
			newLetter->info = p->info;
			p->info = info;
			newLetter->next = p->next;
			p->next = newLetter;
		}
		else
		{
			newLetter->next = p->next;
			p->next = newLetter;
		}
	}
}

NODE_TREE* removeFromQueue(NODE **phead)
{
	if (*phead == 0) return 0;
	NODE_TREE *info =(*phead)->info;
	NODE *p = *phead;
	*phead = (*phead)->next;
	free(p);
	return info;
}

void readFromFile(NODE **phead)
{
	FILE *f;
	int n = 0, capacity=10, num, p=1;
	char c;
	LETTER *arr = (LETTER *)calloc(capacity, sizeof(LETTER));
	if ((f = fopen("letters.txt", "r")) != NULL)
	{
		while ((c = fgetc(f)) != EOF)
		{
			if (n == capacity)
				arr = (LETTER *)realloc(arr, (capacity *= 2) * sizeof(LETTER));
			if (c == 'H')
			{
				arr[n++].letter[0] = c;
				fscanf(f, "%d ", &num);
				break;
			}
			if (c >= 'A' && c <= 'Z')
				arr[n++].letter[0] = c;
		}
		n = 0;
		arr[n++].prob = num;
		do
		{
			p = (fscanf(f, "%d ", &num)==1);
			if (p)
				arr[n++].prob = num;
		} while (p);
		size = n;
		NODE_TREE *tree = (NODE_TREE*)calloc(n, sizeof(NODE_TREE));
		for (int i = 0; i < n; i++)
		{
			tree[i].l = arr + i;
			strcpy(tree[i].l->code,"");
			addInQueue(phead, tree+i);
		}
		fclose(f);
	}
	else
		printf("Greska pri otvaranju datoteke letters.txt u rezimu za citanje!");
	
}

void writeQueue(NODE *head)
{
	while (head != 0)
	{
		printf("%s %d\n",head->info->l->letter, head->info->l->prob);
		head = head->next;
	}
}

NODE_TREE* search(NODE *head, char letter)
{
	for (; head && (strcmp(head->info->l->letter, &letter) != 0); head = head->next);
	return head->info;
}

NODE_TREE* newTreeNode(LETTER* info)
{
	NODE_TREE *newNode = (NODE_TREE *)malloc(sizeof(NODE_TREE));
	newNode->l = info;
	newNode->left = 0;
	newNode->right = 0;
	//printf("%s %d x\n", newNode->l->letter, newNode->l->prob);
	return newNode;
}

void huffman(NODE **phead)
{
	readFromFile(phead);
	for (int i = 1; i < size; i++)
	{
		LETTER *let = (LETTER*)malloc(sizeof(LETTER));;
		NODE_TREE *first, *second;
		first=removeFromQueue(phead);	
		second=removeFromQueue(phead);

		let->prob = first->l->prob + second->l->prob;
		strcpy(let->code, "");
		char *firstLetter = (char*)calloc(strlen(first->l->letter)+1,sizeof(char));
		strcpy(firstLetter, first->l->letter);
		char *secondLetter = (char*)calloc(strlen(second->l->letter) + 1, sizeof(char));
		strcpy(secondLetter, second->l->letter);
		strcpy(let->letter, firstLetter);
		strcat(let->letter, secondLetter);

		NODE_TREE *newNode = newTreeNode(let);
		newNode->left = first;
		newNode->right = second;
		addInQueue(phead, newNode);
	}
}

void code(NODE_TREE *root, NODE_TREE *node)
{
	static int j;
	if (root->l->prob == 100)
		j = 0;
	for (unsigned i = 0; root->left && (i < strlen(root->left->l->letter)); i++)
		if (root->left->l->letter[i] == node->l->letter[0])
		{
			node->l->code[j++] = '0';
			code(root->left, node);
		}
	for (unsigned i = 0;root->right && i < strlen(root->right->l->letter); i++)
		if (root->right->l->letter[i] == node->l->letter[0])
		{
			node->l->code[j++] = '1';
			code(root->right, node);
		}
	node->l->code[j] = '\0';
}
 
void preorder(NODE_TREE *root)
{
	if (root != 0)
	{
		printf("%s %d\n", root->l->letter, root->l->prob);
		preorder(root->left);
		preorder(root->right);
	}
}

char* messageCheck(char *message)
{
	for (unsigned i = 0; i < strlen(message); i++)
	{
		if ((message[i] > 'H' && message[i] <= 'Z') || message[i] > 'h' && message[i] <= 'z')
			message[i] = 'H';
		else if (message[i] >= 'a' && message[i] <= 'h')
			message[i] -= 0x20;
	}
	return message;
}
