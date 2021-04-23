/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
		  singly-linked-list�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
	 	 - initialize�� �� �ٸ��� ���� �Ұ�
	 	 - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	printf("[----- [�ѹο�] [2018038047] -----]\n");
	 
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);
		switch (command) {
			/* �ʱ�ȭ */
		case 'z': case 'Z':
			initialize(&headnode);
			break;
			/* ����Ʈ ��� */
		case 'p': case 'P':
			printList(headnode);
			break;
			/* ������ ������ ��� ���� */
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
			/* ���ϴ� ��� ���� */
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
			/* �� �ڿ� ��� ���� */
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
			/* �� �� ��� ���� */
		case 'e': case 'E':
			deleteLast(headnode);
			break;
			/* �� �տ� ��� ���� */
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
			/* �� �� ��� ���� */
		case 't': case 'T':
			deleteFirst(headnode);
			break;
			/* ����Ʈ �������� ����� */
		case 'r': case 'R':
			invertList(headnode);
			break;
			/* ���� */
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/* ���� �����͸� ���� headNode�� �ּҰ��� ���� �޾Ƽ� h�� ���� �ٷ� �ٲ۴�.*/
int initialize(headNode** h) {
	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if (*h != NULL)
		freeList(*h);
	
	*h = (headNode*)malloc(sizeof(headNode)); // headNode�� �����Ϳ� ���� �Ҵ� ���ش�.
	(*h)->first = NULL; // first�� �ʱ�ȭ �����ش�.
	return 1;
}

int freeList(headNode* h) {
	listNode* node = h->first;
	listNode* prev = NULL;
	while(node != NULL){ // list�� node�� ����
		prev = node;
		node = node->rlink;
		free(prev);
	}
	free(h); // headnode ����
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	if(h == NULL){ // headnode�� �ʱ�ȭ ���� �ʾҴٸ� ����
		printf("Head Node is not initialized.\n");
		return 0;
	}
	listNode* Toend; // ����Ʈ ������ �� ������
	listNode* node = (listNode*)malloc(sizeof(listNode)); // ��� ����
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL;
	Toend = h->first;
	if(h->first == NULL) { // ����Ʈ�� ������¸� �� �տ� node ����
		h->first = node;
	}
	else {
		while(Toend->rlink != NULL) { // ����Ʈ ������ �̵�
			Toend = Toend->rlink;
		}
		Toend->rlink = node; // �� �ڿ� ����
		node->llink = Toend; // llink ����
	}
	return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	if(h == NULL){ // headnode�� �ʱ�ȭ ���� �ʾҴٸ� ����
		printf("Head Node is not initialized.\n");
		return 0;
	}	
	if(h->first == NULL){ // ����Ʈ�� �������� �˻�
		printf("list is empty!\n");
		return 0;
	}
	listNode* Toend; // ����Ʈ ������ �� ������
	Toend = h->first;
	if(h->first->rlink == NULL){ // ����Ʈ�� node�� �ϳ��� �����ϸ�
	h->first = NULL; // ����Ʈ�� ����
	free(Toend);
	}
	else{
	while(Toend->rlink != NULL){ // ����Ʈ �� ������ �̵�
		Toend = Toend->rlink;
	}
	Toend->llink->rlink = NULL; // �� ������ ���� link ����
	free(Toend);
	}
	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {
	if(h == NULL){ // headnode�� �ʱ�ȭ ���� �ʾҴٸ� ����
		printf("Head Node is not initialized.\n");
		return 0;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = NULL;
	if (h->first == NULL){ // ����Ʈ�� ������¸�
	h->first = node; // node�� head�� link
	node->rlink = NULL;
	}
	else{
		node->rlink = h->first; // node �� rlink�� ���� head�� ����
		h->first->llink = node;  // ���� head�� llink�� node�� ����
		h->first = node; // ��� ����
	}
	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
	if(h == NULL){ // headnode�� �ʱ�ȭ ���� �ʾҴٸ� ����
		printf("Head Node is not initialized.\n");
		return 0;
	}	
	if(h->first == NULL){ // ����Ʈ�� �������� �˻�
		printf("list is empty!\n");
		return 0;
	}

	listNode* deleted; // ���� ��� ����ų ������
	deleted = h->first;
	h->first = deleted->rlink; // ��� �������� �̵�
	free(deleted);  // ��� ����
	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
	if(h == NULL){ // headnode�� �ʱ�ȭ ���� �ʾҴٸ� ����
		printf("Head Node is not initialized.\n");
		return 0;
	}
	if(h->first == NULL){ // ����Ʈ�� �������� �˻�
		printf("list is empty!\n");
		return 0;
	}
	listNode* prev = NULL;
	/* ������ �̵��ϸ� �������� ���� */
	while(h->first->rlink != NULL){
		prev = h->first;
		h->first = h->first->rlink;
		prev->rlink = prev->llink;
		prev->llink = h->first;
	}
	h->first->rlink = h->first->llink;
	h->first->llink = NULL;
	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
	if(h == NULL){ // headnode�� �ʱ�ȭ ���� �ʾҴٸ� ����
		printf("Head Node is not initialized.\n");
		return 0;
	}
	listNode* findkey = h->first; // key �˻��� node
	listNode* prev = NULL; // key �˻��� node�� ���� node
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	if (h->first == NULL){ // ����Ʈ�� ������¸�
	h->first = node; // node�� head�� link
	node->rlink = NULL;
	}
	else{
		if(h->first->key > key){ // ù��° node�� key���� �Է¹��� node�� key�� ������ �� �տ� ����
			node->rlink = h->first; // node �� rlink�� ���� head�� ����
			h->first->llink = node;  // ���� head�� llink�� node�� ����
			h->first = node; // ��� ����
		}
		else{
			while(findkey != NULL && findkey->key <= key){ // �Է¹��� key���� ū key�� ���� node Ž��
				prev = findkey;
				findkey = findkey->rlink;
			}
			if(findkey != NULL){ // �Է¹��� key���� ū �� �߰��ϸ� �� ��� �տ� ����
				node->llink = findkey->llink;
				node->rlink = findkey;
				findkey->llink->rlink = node;
				findkey->llink = node;
			}
			else{ // �Է¹��� key���� ū ���� ������ �� �ڿ� ����
				node->rlink = NULL;
				node->llink = prev;
				prev->rlink = node;
			}
		}
	}
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
	if(h == NULL){ // headnode�� �ʱ�ȭ ���� �ʾҴٸ� ����
		printf("Head Node is not initialized.\n");
		return 0;
	}
	if(h->first == NULL){ // ����Ʈ�� �������� �˻�
		printf("list is empty!\n");
		return 0;
	}

	listNode* deleted; // ������ node �˻��� ������
	deleted = h->first;
	if(deleted->key == key) { // ������ node�� �� �տ� ������
		h->first = deleted->rlink; // head �̵�
		free(deleted);
	}
	else{
		while(deleted != NULL && deleted->key != key){ // ������ node �˻�
			deleted = deleted->rlink;
		}
		if(deleted == NULL){ // key�� ã�� ���ϸ� ����
			printf("Fail to find the key\n");
		}
		else{
		/* ������ node�� ���� node�� ���� node�� ��ũ ���� */
			if(deleted->rlink){ // ���� ��� node�� ���� ��尡 �����Ѵٸ� (���� ��� node�� �� �ڰ� �ƴϸ�)
			deleted->llink->rlink = deleted->rlink;
			deleted->rlink->llink = deleted->llink;
			}
			else{ // ���� ��� node�� �� �ڶ��
			deleted -> llink -> rlink = NULL;
			}
			free(deleted);
		}
	}
	return 1;
}


