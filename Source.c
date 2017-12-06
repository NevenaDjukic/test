#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

int size;

int main()
{
	NODE *head = 0;
	NODE_TREE *root = 0;
	huffman(&head);
	root = removeFromQueue(&head);
	if (root->l->prob == 100)
	{
		readFromFile(&head);
		NODE_TREE **nodes = (NODE_TREE**)calloc(size, sizeof(NODE_TREE*));
		printf("== ==== =========\n");
		printf("SL VJER  KOD\n");
		printf("== ==== =========\n");
		for (int i = 0; i < size; i++)
		{
			nodes[i]=search(head, 'A' + i);
			code(root, nodes[i]);
			printf("%2s %3d  %-10s\n", nodes[i]->l->letter, nodes[i]->l->prob, nodes[i]->l->code);
		}
		printf("== ==== =========\n");
		char *message = (char*)calloc(30, sizeof(char));
		printf("Unesite poruku koju zelite kodirati: ");
		scanf("%s", message);
		message = messageCheck(message);
		for (unsigned i = 0; i < strlen(message); i++)
			printf("%s ", nodes[message[i] - 'A']->l->code);
		free(nodes);
		free(message);
	}
	else
		printf("Zbir vjerovatnoca nije 100. Unesena poruka se ne moze kodovati!\n");
	free(root);
	getchar();
	getchar();
	return 0;
}