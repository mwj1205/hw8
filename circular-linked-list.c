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
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
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

	printf("[----- [한민우] [2018038047] -----]\n");	
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

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
	if(h == NULL) return 0;
	listNode* fnode = h->rlink; // 해제할 노드 가리킬 포인터
	while(fnode != h){ // 리스트 돌면서 해제
		fnode = fnode->rlink;
		free(fnode->llink);
	}
	free(h); // headnode 해제
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
 * list에 key에 대한 노드하나를 추가
 */
// headnode의 왼쪽에 노드 추가
int insertLast(listNode* h, int key) {
	if(h == NULL){ // check initial state
		printf("headnode is not initialized!\n");
		return 0;
	}
	listNode* newnode = (listNode*)malloc(sizeof(listNode));
	newnode->key = key;
	newnode->rlink = h; // newnode의 rlink를 head에 연결
	newnode->llink = h->llink; // newnode의 llink를 기존에 마지막 노드에 연결
	h->llink->rlink = newnode; // 기존에 마지막 노드의 rlink를 newnode로 연결
	h->llink = newnode; // 노드의 맨 마지막(headnode 의 llink)을 newnode로 연결
	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
// headnode의 왼쪽 노드 삭제
int deleteLast(listNode* h) {
	if(h == NULL){ // check initial state
		printf("headnode is not initialized!\n");
		return 0;
	}
	if(h == h->llink){
		printf("circular linked list is empty.\n");
		return 0;
	}
	listNode* delnode = h->llink; // 삭제 대상 노드
	/* 삭제 대상 노드와 연결된 링크들을 옮김 */
	delnode->llink->rlink = delnode->rlink;
	delnode->rlink->llink = delnode->llink;
	free(delnode);
	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
// headnode의 오른쪽에 노드 추가
int insertFirst(listNode* h, int key) {
	if(h == NULL){ // check initial state
		printf("headnode is not initialized!\n");
		return 0;
	}
	listNode* newnode = (listNode*)malloc(sizeof(listNode));
	newnode->key = key;
	newnode->llink = h; // newnode의 llink를 head에 연결
	newnode->rlink = h->rlink; // newnode의 rlink를 기존에 맨 처음 노드에 연결
	h->rlink->llink = newnode; // 기존에 맨 처음 노드의 llink를 newnode로 연결
	h->rlink = newnode; // 노드의 맨 처음(headnode의 rlink)을 newnode로 연결

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
// headnode의 오른쪽 노드 삭제
int deleteFirst(listNode* h) {
	if(h == NULL){ // check initial state
		printf("headnode is not initialized!\n");
		return 0;
	}
	if(h == h->rlink){
		printf("circular linked list is empty.\n");
		return 0;
	}
	listNode* delnode = h->rlink; // 삭제 대상 노드
	/* 삭제 대상 노드와 연결된 링크들을 옮김 */
	delnode->llink->rlink = delnode->rlink;
	delnode->rlink->llink = delnode->llink;
	free(delnode);
	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
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
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 
 **/
int insertNode(listNode* h, int key) {
	if(h == NULL){ // check initial state
		printf("headnode is not initialized!\n");
		return 0;
	}
	listNode* findkey = h->rlink; // key 검색할 포인터
	listNode* newnode = (listNode*)malloc(sizeof(listNode));
	newnode->key = key;
	while(findkey != h && findkey->key < key){ // 입력받은 key보다 큰 key를 가진 노드 탐색
		findkey = findkey->rlink;
	}
	/* 검색한 노드 앞에 newnode 삽입 */
	newnode->rlink = findkey;
	newnode->llink = findkey->llink;
	findkey->llink->rlink = newnode;
	findkey->llink = newnode;

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
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
	while(delnode != h && delnode->key != key){ // 입력받은 key 탐색
		delnode = delnode->rlink;
	}
	if(delnode == h){ // 입력받은 key를 가진 노드가 존재하지 않으면
		printf("fail to find the key.\n");
	}
	else if (delnode->key == key){// 입력받은 key를 가진 노드를 찾으면
		delnode->llink->rlink = delnode->rlink;
		delnode->rlink->llink = delnode->llink;
		free(delnode);
	}
	else printf("unknown error \n");
	return 0;
}


