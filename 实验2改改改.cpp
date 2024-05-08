#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 

const int OVERFLOW = 0;
const int OK = 1;
const int STACK_INIT_SIZE = 10;
const int TURE = 1;
const int FALSE = 0;
const int ERROR = 0;

typedef int Status;
typedef struct Card
{
	char value; //数值 
	char color; //花色 
}Card;

typedef struct Node
{
	Card data;
	struct Node *next;
}Node, *LinkList;

//初始化链表 
LinkList InitList() 
{
	Node *head = (Node *)malloc(sizeof(Node));
	head->next = head;
	return head;
}

//链表插入 
Status InsertList(LinkList L,Card a)
{
	Node *temp = L->next; 
	Node *newnode = (Node *)malloc(sizeof(Node));
	if(!newnode) return ERROR;
	while(temp->next != L)
	{
		temp = temp->next;
	}
		newnode->data = a;
		newnode->next = temp->next;
		temp->next = newnode;
		return OK;
} 

//链表删除
void DeleteList(LinkList L,Node *a)
{
	Node *temp = L->next;
	if(a == L)
	{
		while(temp->next != a)
		{
		temp = temp->next; 
		}
		temp->next = L->next;
		L = L->next;
 	}
	else 
	{
		while(temp->next != a)
		{
		temp = temp->next; 
		}
		temp->next = a->next;
	}
	free(a);
} 

//定义链栈
typedef struct StackNode
{
	Card data;
	struct StackNode *next;
}StackNode,*LinkStack;

//判断栈空
Status isEmpty(LinkStack top)
{
	if(top == NULL)
	return OK;
	else
	return ERROR;	
} 

//入栈
Status Push_LinkStack(LinkStack &top,Card e)
{
	struct StackNode *s;
	s = (StackNode *)malloc(sizeof(StackNode));
	s->data = e;
	s->next = top;
	top = s;
	return OK;
} 

//出栈
Card Pop_LinkStack(LinkStack &top,Card e)
{
	StackNode *p;
	e = top->data;
	p = top;
	top = top->next;
	free(p);
	return e;
}

//洗牌
LinkList shuffle(Card *cards) {
    srand(time(NULL));
    LinkList L = InitList();
    int len = 54;
    int count = 0;
    int randomIndex = rand() % len + 1;
    L->data = cards[randomIndex-1];
    while(count<54) 
	{
    	randomIndex = rand() % len + 1;
        if(cards[randomIndex-1].color != 'Z')
        {
        InsertList(L,cards[randomIndex-1]);
        cards[randomIndex-1].color = 'Z';
        count++;
    	}
    }
    return L;
}

//找大小王
Node *Find(LinkList L)
{
	Node *temp = L->next;
	while(temp != L)
	{
		if(temp->data.color == 'X' || temp->data.color == 'Y')
		return temp;
		temp = temp->next;
	}
	return NULL;
} 

//出牌
void Play(LinkList L,int m)
{
	Node *cur = Find(L);
	int count = 0;
	LinkStack A;
	Card e;
	e.color = 'A';
	e.value = '0';
	int playcount = 1;
	while(cur->next != cur && playcount<54)
	{
		if(count==m)
		{
			if(cur->data.color == 'A')
			{
				Push_LinkStack(A,cur->data);
			}
			if(cur == L)
			{
				L = cur->next;
			}
			printf("打出牌：%c%c\n",cur->data.color,cur->data.value);
			Node *temp = cur;
			cur = cur->next;
			DeleteList(L,temp);
			count = 0;
			playcount++;
		}
		else
		{
			cur = cur->next;
		} 
		count++;
	}
		if(cur->data.color == 'A')
			{
				Push_LinkStack(A,cur->data);
			}
	printf("最后一张牌：%c%c\n",cur->data.color,cur->data.value);
	printf("最后五张A开头的牌：");
	for(int i = 0;i<5;i++)
	{
		if(isEmpty(A) != 1)
		{
		e = Pop_LinkStack(A,e);
		printf("%c%c ",e.color,e.value);
		}
	}
} 

int main() 
{
    // 初始化顺序表
    Card *cards = (Card *)malloc(sizeof(Card) * 54);
    char color[] = {'A', 'B', 'C', 'D'};
    char values[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K'};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            cards[i * 13 + j].color = color[i];
            cards[i * 13 + j].value = values[j];
        }
    }
    cards[52].color = 'X';
    cards[52].value = 'X';
    cards[53].color = 'Y';
    cards[53].value = 'Y';
    
    LinkList L = InitList();
    L = shuffle(cards);
	Play(L,3);
	free(cards);
}
