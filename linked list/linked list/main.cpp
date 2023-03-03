#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>`
#include<stdlib.h>
#include <string.h>
const char* delim = ",";//切割符號
struct Node
{
	char flight[15];//;航班編號
	char destination[15];//目的地
	char take_off[15];//起飛時間
	char landing[15];//降落時間
	Node *next;
};
void addNode(Node*, char*);//新增節點
void printlist(Node*);//顯示所有航班資料
void printDes(Node*);//顯示所有目的地
void Sort(Node*, Node*);//排序
Node* FindTail(Node*);//尋找list尾巴
int Statistics_Flight(Node*, Node*);//統計航班
void addDes(const char*, Node*);//新增目的地
bool Des_cmp(const char*, Node*);//目的地比較
void printNode(Node*);//顯示單一航班資料
void Search(Node*list, char*);//搜尋指定航班
void clearlist(Node*);//刪除list
void main()
{
	FILE*pf = fopen("ChinaAirLine.csv", "r");
	Node* list = (Node*)malloc(sizeof(Node));//dummy node
	list->next = NULL;
	char* Data = (char*)malloc(sizeof(Node));//存放未整理的資料
	fgets(Data, 100, pf);//忽略第一筆資料
	while (fgets(Data, 100, pf))
		addNode(list, Data);
	printlist(list);
	fclose(pf);
	puts("==============================================================");
	Node* Des_list = (Node*)malloc(sizeof(Node));//統計目的地
	Des_list->next = NULL;
	printf("All destinaton:%d\n", Statistics_Flight(list, Des_list));
	printDes(Des_list);
	puts("==============================================================");
	char searchDes[15];
	printf("Enter where you want to go:");
	scanf("%s", &searchDes);
	Search(list, searchDes);
	clearlist(Des_list);
	clearlist(list);
}
void addNode(Node*list, char* Data)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	strcpy(temp->flight, strtok(Data, delim));
	strcpy(temp->destination, strtok(NULL, delim));
	strcpy(temp->take_off, strtok(NULL, delim));
	strcpy(temp->landing, strtok(NULL, delim));
	temp->next = NULL;
	Sort(list, temp);//sort
}
void printlist(Node* list)
{
	for (list = list->next; list; list = list->next)
		printf("%12s ->%12s->%12s->%12s", list->flight, list->destination, list->take_off, list->landing);
}
Node* FindTail(Node* list)
{
	while (list->next)
		list = list->next;
	return list;
}
void Sort(Node*list, Node*temp)
{
	while (list)
		if (list->next)
			if (strcmp(temp->take_off, list->next->take_off) <= 0)//insert fornt Node
			{
				temp->next = list->next;
				list->next = temp;
				break;
			}
			else //Next node compare
				list = list->next;
		else//No next node,insert behind
		{
			list->next = temp;
			break;
		}
}
int Statistics_Flight(Node* list, Node* Des_list)
{
	int count = 0;
	Node*temp = (Node*)malloc(sizeof(Node));
	temp->next = NULL;
	list = list->next;//neglect first judge
	strcpy(temp->destination, list->destination);
	Des_list->next = temp;
	count++;
	while (list = list->next)
		if (Des_cmp(list->destination, Des_list))
		{
			addDes(list->destination, Des_list);
			count++;
		}
	return count;
}
bool Des_cmp(const char*list_temp, Node*Des_list)
{
	while (Des_list = Des_list->next)
		if (strcmp(Des_list->destination, list_temp) == 0)//both same
			return 0;
	return 1;
}
void addDes(const char* destination, Node*list)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->next = NULL;
	strcpy(temp->destination, destination);
	FindTail(list)->next = temp;
}
void printDes(Node* list)
{
	for (list = list->next; list; list = list->next)
		printf("%s\n", list->destination);
}
void printNode(Node*list)
{
	puts("");
	printf("%12s ->%12s ->%12s ->%12s\n", list->flight, list->destination, list->take_off, list->landing);
}
void Search(Node*list, char*searchDes)
{
	for (list = list->next; list; list = list->next)
		if (!strcmp(list->destination, searchDes))
			printNode(list);
}
void clearlist(Node*list)
{
	while (list)
	{
		Node* temp = list;
		list = list->next;
		free(temp);
	}
}