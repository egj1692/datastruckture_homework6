/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
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
			headnode = initialize(headnode);
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

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	/* 새로운 노드 생성 */
	listNode *node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	/* 리스트에 노드가 하나도 없는 경우 */
	if(h->first == NULL){
		h->first = node;
		return 0;
	}

	/* list를 탐색하기 위한 (이중) 포인터 변수 선언 */
	listNode *temp = h->first;
	listNode *pre = h->first;
	
	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(temp != NULL){
		if (temp->key >= key){
		/* 입력한 key보다 큰 경우 */
			if (temp == h->first){
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
				h->first = node;
				node->link = temp;
			}
			else{
			/* 중간이거나 마지막인 경우 */
				pre->link = node;
				node->link = temp;
			}
			return 0;
		}
		/* list에서 다음 노드 입력 */
		pre = temp;
		temp = temp->link;
	}
	/* list의 모든 노드가 입력한 key보다 작으면 마지막에 삽입 */
	pre->link = node;
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	/* 새로운 노드 생성 */
	listNode *node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	/* 리스트에 노드가 하나도 없는 경우 */
	if(h->first == NULL){
		h->first = node;
		return 0;
	}

	/* list를 탐색하기 위한 (이중) 포인터 선언 */
	listNode *temp = h->first;
	listNode *pre = NULL;
	/* list의 마지막 노드를 찾는다 */
	while(temp != NULL){
		pre = temp;
		temp = temp->link;
	}
	/* 마지막 노드 뒤에 삽입 */
	pre->link = node;
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	/* 리스트에 노드가 하나도 없는 경우 */
	if(h->first == NULL){
		printf(" list is empty");
		return 0;
	}
	/* 첫번째 노드 포인터 선언 */
	listNode *node = h->first;
	/* head를 두번째 노드로 변경 */
	h->first = node->link;
	/* 첫번째 노드 할당해제 */
	free(node);

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	/* 리스트에 노드가 하나도 없는 경우 */
	if(h->first == NULL){
		printf(" list is empty");
		return 0;
	}

	/* list를 탐색하기 위한 (이중) 포인터 선언 */
	listNode *temp = h->first;
	listNode *pre = NULL;
	
	/* key를 기준으로 삭제할 위치를 찾는다 */
	while(temp != NULL){
		if (temp->key == key){
		/* 입력한 key와 같은 경우 */
			if (temp == h->first){
			/* 첫 노드를 삭제해야할 경우 */
				h->first = temp->link;
			}
			else{
			/* 중간이거나 마지막인 경우 */
				pre->link = temp->link;
			}
			/* 노드 할당해제 */
			free(temp);
			return 0;
		}
		/* list에서 다음 노드 입력 */
		pre = temp;
		temp = temp->link;
	}
	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	/* 리스트에 노드가 하나도 없는 경우 */
	if(h->first == NULL){
		printf(" list is empty");
		return 0;
	}

	/* list를 탐색하기 위한 (이중) 포인터 선언 */
	listNode *temp = h->first;
	listNode *pre = NULL;
	/* 노드가 한 개있는 경우 */
	if(temp->link == NULL){
		h->first = NULL;
		free(temp);
		return 0;
	}

	/* list의 마지막 위치를 찾는다 */
	while(temp->link != NULL){
		/* list에서 다음 노드 입력 */
		pre = temp;
		temp = temp->link;
	}
	pre->link = NULL;
	free(temp);

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	/* list를 탐색을 위한 (이중) 포인터 선언 */
	listNode *next = h->first;
	listNode *temp = NULL;
	listNode *pre = NULL;
	
	/* 리스트에 노드가 하나도 없는 경우 */
	if(h->first == NULL){
		printf(" list is empty");
		return 0;
	}
	/* list를 탐색하면서 순서 바꾸기 */
	while(next != NULL){
		pre = temp;
		temp = next;
		next = next->link;
		temp->link = pre;
	}
	/* head가 가리키는 노드를 마지막 노드로 변경 */
	h->first = temp;
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
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

