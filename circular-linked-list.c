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
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
		  singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
	 	 - initialize와 왜 다른지 이해 할것
	 	 - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
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

	printf("[----- [한민우] [2018038047] -----]\n");
	 
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
			/* 초기화 */
		case 'z': case 'Z':
			initialize(&headnode);
			break;
			/* 리스트 출력 */
		case 'p': case 'P':
			printList(headnode);
			break;
			/* 오름차 순으로 노드 삽입 */
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
			/* 원하는 노드 삭제 */
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
			/* 맨 뒤에 노드 삽입 */
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
			/* 맨 뒤 노드 삭제 */
		case 'e': case 'E':
			deleteLast(headnode);
			break;
			/* 맨 앞에 노드 삽입 */
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
			/* 맨 앞 노드 삭제 */
		case 't': case 'T':
			deleteFirst(headnode);
			break;
			/* 리스트 역순으로 만들기 */
		case 'r': case 'R':
			invertList(headnode);
			break;
			/* 종료 */
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

/* 이중 포인터를 통해 headNode의 주소값을 직접 받아서 h의 값을 바로 바꾼다.*/
int initialize(headNode** h) {
	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)
		freeList(*h);
	
	*h = (headNode*)malloc(sizeof(headNode)); // headNode의 포인터에 동적 할당 해준다.
	(*h)->first = NULL; // first를 초기화 시켜준다.
	return 1;
}

int freeList(headNode* h) {
	listNode* node = h->first;
	listNode* prev = NULL;
	while(node != NULL){ // list의 node들 해제
		prev = node;
		node = node->rlink;
		free(prev);
	}
	free(h); // headnode 해제
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
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	if(h == NULL){ // headnode가 초기화 되지 않았다면 오류
		printf("Head Node is not initialized.\n");
		return 0;
	}
	listNode* Toend; // 리스트 끝까지 갈 포인터
	listNode* node = (listNode*)malloc(sizeof(listNode)); // 노드 생성
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL;
	Toend = h->first;
	if(h->first == NULL) { // 리스트가 공백상태면 맨 앞에 node 삽입
		h->first = node;
	}
	else {
		while(Toend->rlink != NULL) { // 리스트 끝까지 이동
			Toend = Toend->rlink;
		}
		Toend->rlink = node; // 맨 뒤에 삽입
		node->llink = Toend; // llink 연결
	}
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	if(h == NULL){ // headnode가 초기화 되지 않았다면 오류
		printf("Head Node is not initialized.\n");
		return 0;
	}	
	if(h->first == NULL){ // 리스트가 공백인지 검사
		printf("list is empty!\n");
		return 0;
	}
	listNode* Toend; // 리스트 끝까지 갈 포인터
	Toend = h->first;
	if(h->first->rlink == NULL){ // 리스트에 node가 하나만 존재하면
	h->first = NULL; // 리스트가 공백
	free(Toend);
	}
	else{
	while(Toend->rlink != NULL){ // 리스트 맨 끝까지 이동
		Toend = Toend->rlink;
	}
	Toend->llink->rlink = NULL; // 맨 마지막 노드와 link 해제
	free(Toend);
	}
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	if(h == NULL){ // headnode가 초기화 되지 않았다면 오류
		printf("Head Node is not initialized.\n");
		return 0;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = NULL;
	if (h->first == NULL){ // 리스트가 공백상태면
	h->first = node; // node를 head로 link
	node->rlink = NULL;
	}
	else{
		node->rlink = h->first; // node 의 rlink를 기존 head에 연결
		h->first->llink = node;  // 기존 head의 llink를 node에 연결
		h->first = node; // 헤드 변경
	}
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	if(h == NULL){ // headnode가 초기화 되지 않았다면 오류
		printf("Head Node is not initialized.\n");
		return 0;
	}	
	if(h->first == NULL){ // 리스트가 공백인지 검사
		printf("list is empty!\n");
		return 0;
	}

	listNode* deleted; // 지울 노드 가리킬 포인터
	deleted = h->first;
	h->first = deleted->rlink; // 헤드 다음으로 이동
	free(deleted);  // 노드 삭제
	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	if(h == NULL){ // headnode가 초기화 되지 않았다면 오류
		printf("Head Node is not initialized.\n");
		return 0;
	}
	if(h->first == NULL){ // 리스트가 공백인지 검사
		printf("list is empty!\n");
		return 0;
	}
	listNode* prev = NULL;
	/* 끝까지 이동하며 역순으로 변경 */
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



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	if(h == NULL){ // headnode가 초기화 되지 않았다면 오류
		printf("Head Node is not initialized.\n");
		return 0;
	}
	listNode* findkey = h->first; // key 검색할 node
	listNode* prev = NULL; // key 검색할 node의 이전 node
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	if (h->first == NULL){ // 리스트가 공백상태면
	h->first = node; // node를 head로 link
	node->rlink = NULL;
	}
	else{
		if(h->first->key > key){ // 첫번째 node의 key보다 입력받은 node의 key가 작으면 맨 앞에 삽입
			node->rlink = h->first; // node 의 rlink를 기존 head에 연결
			h->first->llink = node;  // 기존 head의 llink를 node에 연결
			h->first = node; // 헤드 변경
		}
		else{
			while(findkey != NULL && findkey->key <= key){ // 입력받은 key보다 큰 key를 가진 node 탐색
				prev = findkey;
				findkey = findkey->rlink;
			}
			if(findkey != NULL){ // 입력받은 key보다 큰 값 발견하면 그 노드 앞에 삽입
				node->llink = findkey->llink;
				node->rlink = findkey;
				findkey->llink->rlink = node;
				findkey->llink = node;
			}
			else{ // 입력받은 key보다 큰 값이 없으면 맨 뒤에 삽입
				node->rlink = NULL;
				node->llink = prev;
				prev->rlink = node;
			}
		}
	}
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	if(h == NULL){ // headnode가 초기화 되지 않았다면 오류
		printf("Head Node is not initialized.\n");
		return 0;
	}
	if(h->first == NULL){ // 리스트가 공백인지 검사
		printf("list is empty!\n");
		return 0;
	}

	listNode* deleted; // 삭제할 node 검색할 포인터
	deleted = h->first;
	if(deleted->key == key) { // 삭제할 node가 맨 앞에 있으면
		h->first = deleted->rlink; // head 이동
		free(deleted);
	}
	else{
		while(deleted != NULL && deleted->key != key){ // 삭제할 node 검색
			deleted = deleted->rlink;
		}
		if(deleted == NULL){ // key를 찾지 못하면 오류
			printf("Fail to find the key\n");
		}
		else{
		/* 삭제될 node의 이전 node와 다음 node의 링크 연결 */
			if(deleted->rlink){ // 삭제 대상 node의 다음 노드가 존재한다면 (삭제 대상 node가 맨 뒤가 아니면)
			deleted->llink->rlink = deleted->rlink;
			deleted->rlink->llink = deleted->llink;
			}
			else{ // 삭제 대상 node가 맨 뒤라면
			deleted -> llink -> rlink = NULL;
			}
			free(deleted);
		}
	}
	return 1;
}


