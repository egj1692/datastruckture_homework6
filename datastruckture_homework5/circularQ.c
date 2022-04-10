/* circularQ.c
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;        // front : Queue의 앞, rear : 가장 마지막
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);     // Queue
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
    
	QueueType *cQ = createQueue();      // Queue 할당
	element data;       // 원소를 입력받을 변수

	char command;

	do{
		printf("\n-----------------------------------------------------\n");
        printf("-----------[Lee Jun Gi]  [2017035135]----------------\n");
		printf("-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

        // command를 입력하여 Queue에 실행할 명령을 선택
		switch(command) {
		case 'i': case 'I':
            // Queue에 rear의 원소 1개 입력
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
            // Queue에 front의 원소 1개 제거
			deQueue(cQ,&data);
			break;
		case 'p': case 'P':
            // Queue에 모든 원소 출력
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));        // Queue 만큼 동적할당
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ);       // Queue 동적할당 해제
    return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);     // 원소 1개 입력
	return item;
}

// Queue가 비어있는지 확인하는 함수
int isEmpty(QueueType *cQ)
{
	if (cQ->front == cQ->rear){     // Queue의 front와 rear가 같으면
		printf("Circular Queue is empty!");     // Queue 가 비어있음
		return 1;
	}
	else return 0;
}

int isFull(QueueType *cQ)
{
    // CircularQ는 Full과 Emty를 구별하기 위해서 마지막에 하나를 비워둠
    // (rear+1)를 max_size로 나누면 사용하지 않는 Queue의 자리를 찾을 수 있음
    // 이것이 front와 같으면 full을 출력
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {
		printf(" Circular Queue is full!");
		return 1;
	}
	else return 0;
}

// Queue에 
void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)) return;  // Queue가 full이면 종료 
	else {      // full이 아니면
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;     // rear + 1 증가하지만 Max_size넘으면 다시 0으로 돌아감
		cQ->queue[cQ->rear] = item;
	}
}

void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ)) return;
	else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE;     // front + 1 증가하지만 Max_size넘으면 다시 0으로 돌아감
		*item = cQ->queue[cQ->front];     // Queue에서 뺀 원서 item에 입력해줌
		return;
	}
}

void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}