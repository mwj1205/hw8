/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	printf("[----- [�ѹο�] [2018038047] -----]\n");	
	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
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


int initialize(listNode** h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* �޸� ���� */
int freeList(listNode* h){
	if(h == NULL) return 0;
	listNode* fnode = h->rlink; // ������ ��� ����ų ������
	while(fnode != h){ // ����Ʈ ���鼭 ����
		fnode = fnode->rlink;
		free(fnode->llink);
	}
	free(h); // headnode ����
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
// headnode�� ���ʿ� ��� �߰�
int insertLast(listNode* h, int key) {
	if(h == NULL){ // check initial state
		printf("headnode is not initialized!\n");
		return 0;
	}
	listNode* newnode = (listNode*)malloc(sizeof(listNode));
	newnode->key = key;
	newnode->rlink = h; // newnode�� rlink�� head�� ����
	newnode->llink = h->llink; // newnode�� llink�� ������ ������ ��忡 ����
	h->llink->rlink = newnode; // ������ ������ ����� rlink�� newnode�� ����
	h->llink = newnode; // ����� �� ������(headnode �� llink)�� newnode�� ����
	return 1;
}


/**
 * list�� ������ ��� ����
 */
// headnode�� ���� ��� ����
int deleteLast(listNode* h) {
	if(h == NULL){ // check initial state
		printf("headnode is not initialized!\n");
		return 0;
	}
	if(h == h->llink){
		printf("circular linked list is empty.\n");
		return 0;
	}
	listNode* delnode = h->llink; // ���� ��� ���
	/* ���� ��� ���� ����� ��ũ���� �ű� */
	delnode->llink->rlink = delnode->rlink;
	delnode->rlink->llink = delnode->llink;
	free(delnode);
	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
// headnode�� �����ʿ� ��� �߰�
int insertFirst(listNode* h, int key) {
	if(h == NULL){ // check initial state
		printf("headnode is not initialized!\n");
		return 0;
	}
	listNode* newnode = (listNode*)malloc(sizeof(listNode));
	newnode->key = key;
	newnode->llink = h; // newnode�� llink�� head�� ����
	newnode->rlink = h->rlink; // newnode�� rlink�� ������ �� ó�� ��忡 ����
	h->rlink->llink = newnode; // ������ �� ó�� ����� llink�� newnode�� ����
	h->rlink = newnode; // ����� �� ó��(headnode�� rlink)�� newnode�� ����

	return 1;
}

/**
 * list�� ù��° ��� ����
 */
// headnode�� ������ ��� ����
int deleteFirst(listNode* h) {
	if(h == NULL){ // check initial state
		printf("headnode is not initialized!\n");
		return 0;
	}
	if(h == h->rlink){
		printf("circular linked list is empty.\n");
		return 0;
	}
	listNode* delnode = h->rlink; // ���� ��� ���
	/* ���� ��� ���� ����� ��ũ���� �ű� */
	delnode->llink->rlink = delnode->rlink;
	delnode->rlink->llink = delnode->llink;
	free(delnode);
	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {
	if(h == NULL){ // check initial state
		printf("headnode is not initialized!\n");
		return 0;
	}
	if(h == h->rlink){
		printf("circular linked list is empty.\n");
		return 0;
	}
	listNode* curr = h->rlink;
	listNode* prev = h;
	do{
		curr->llink = curr->rlink;
		curr->rlink = prev;
		prev = curr;
		curr = curr->llink;
	}while(prev != h);
	return 0;
}



/**
 *  ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� 
 **/
int insertNode(listNode* h, int key) {
	if(h == NULL){ // check initial state
		printf("headnode is not initialized!\n");
		return 0;
	}
	listNode* findkey = h->rlink; // key �˻��� ������
	listNode* newnode = (listNode*)malloc(sizeof(listNode));
	newnode->key = key;
	while(findkey != h && findkey->key < key){ // �Է¹��� key���� ū key�� ���� ��� Ž��
		findkey = findkey->rlink;
	}
	/* �˻��� ��� �տ� newnode ���� */
	newnode->rlink = findkey;
	newnode->llink = findkey->llink;
	findkey->llink->rlink = newnode;
	findkey->llink = newnode;

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {
	if(h == NULL){ // check initial state
		printf("headnode is not initialized!\n");
		return 0;
	}
	if(h == h->rlink){
		printf("circular linked list is empty.\n");
		return 0;
	}
	if(h->key == key){
		printf("deletion of headnode is not permitted.\n");
		return 0;
	}

	listNode* delnode = h->rlink;
	while(delnode != h && delnode->key != key){ // �Է¹��� key Ž��
		delnode = delnode->rlink;
	}
	if(delnode == h){ // �Է¹��� key�� ���� ��尡 �������� ������
		printf("fail to find the key.\n");
	}
	else if (delnode->key == key){// �Է¹��� key�� ���� ��带 ã����
		delnode->llink->rlink = delnode->rlink;
		delnode->rlink->llink = delnode->llink;
		free(delnode);
	}
	else printf("unknown error \n");
	return 0;
}


