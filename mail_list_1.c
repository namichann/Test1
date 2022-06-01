#include <stdio.h>
#include <stdlib.h>
#include "../../include/mystring.h"

enum return_val{N = 100,SUCCESS,FAIL};

//功能：统计人数，添加人数，菜单，查找，删除，
typedef struct pnode
{
	int num;  //编号
	char name[N];  //姓名 
	char phone[N];  //电话号码（用字符数组保存）
	char address[N]; // 地址
	

	struct pnode * prior;
	struct pnode * next;
}Pnode,* Plink;

//菜单
void menu()
{
	char ch;
	printf("---------------添加联系人（1）   显示联系人（2）---------------\n");
	printf("---------------修改联系人（3）   删除联系人（4）---------------\n");
	printf("---------------查找联系人（5）   退出通讯录 (0) ---------------\n");
	printf("\n");
}

//判断malloc是否成功
int link_create_success(Plink head)
{
	if(NULL == head)
	{
		printf("malloc error!\n");
		return FAIL;
	}

	return SUCCESS;
}

//初始化
void init_link(Plink * head)
{
	*head = (Plink)malloc(sizeof(Pnode));
	if(FAIL == link_create_success(*head))
	{
		printf("init error!\n");
		return;
	}
	(*head)->next = NULL;
	(*head)->num = 0;
	
	printf("init success!\n");
}

//尾插
void insert_tail(Plink head)
{
	Plink p = NULL;
	Plink q = NULL;
	int i = 0;

	q = head;
	p = (Plink)malloc(sizeof(Pnode));
	if(FAIL == link_create_success(p))
	{
		printf("添加失败！\n");
	}

	printf("请输入要添加的联系人姓名：");
	scanf("%s",p->name);
	getchar();

	printf("请输入要添加的联系人号码：");
	scanf("%s",p->phone);
	getchar();
	
	printf("请输入要添加的联系人地址：");
	scanf("%s",p->address);
	getchar();

	while(NULL != q->next)
	{	
		i++;
		q = q->next;
	}

	head->num = ++i;
	p->num = head->num;

	p->next = q->next;
	q->next = p;
}

//输出当前结点内所有数据
void printf_link(Plink p)
{
	printf("联系人编号：%d  ",p->num);
	printf("姓名：%s  ",p->name);
	printf("号码：%s  ",p->phone);
	printf("地址：%s",p->address);
	printf("\n");
}

//查找链表
void search_link(Plink head)
{
	int search_num = 0;
	Plink p = NULL;
	p = head->next;

	printf("请输入联系人编号：");
	scanf("%d",&search_num);

	while(search_num != p->num)
	{
		p = p->next;
	}

	printf_link(p);

}


//遍历
void display_link(Plink head)
{
	Plink p = NULL;
	
	p = head->next;

	if(NULL == p)
	{
		printf("通讯录无联系人！\n");
	}
	else
	{
		printf("通讯录中有%d位联系人!\n",head->num);
		while(NULL != p)
		{
			printf_link(p);
	//		printf("联系人编号：%d  ",p->num);
	//		printf("姓名：%s  ",p->name);
	//		printf("号码：%s  ",p->phone);
	//		printf("地址：%s",p->address);
	//		printf("\n");
			p = p->next;
		}
	}
}

//清空链表
int make_empty(Plink head)
{
	Plink p = NULL;

	p = head->next;

	while(NULL != p)
	{
		head->next = p->next;
		free(p);
		p = p->next;
	}
	
	if(NULL != p)
	{
		printf("清空链表失败！\n");
		return FAIL;
	}
	else
	{
		printf("清空链表成功！\n");
		return SUCCESS;
	}
}

//更新链表
void update_link(Plink head)
{
	Plink p = NULL;
	int num;

	p = head->next;
	printf("请输入需要修改的联系人编号：");
	scanf("%d",&num);

	while(num != p->num)
	{
		p = p->next;
	}

	printf("请输入需要修改的联系人姓名：");
	scanf("%s",p->name);
	getchar();

	printf("请输入需要修改的联系人号码：");
	scanf("%s",p->phone);
	getchar();

	printf("请输入需要修改的联系人地址：");
	scanf("%s",p->address);
	getchar();

}

//删除结点
void delete_link(Plink head)
{	
	Plink q = NULL;
	Plink p = NULL;
	int num;
	
	q = head;
	p = head->next;
	printf("请输入需要删除的联系人编号：");
	scanf("%d",&num);
	getchar();

	while(num != p->num)
	{
		q = p;
		p = p->next;
	}

	q->next = p->next;
	free(p);
	
	head->num = --head->num;

	while(NULL != p->next)
	{
		p->next->num = --p->next->num;
		p = p->next;
	}

	if(NULL == p)
	{
		printf("删除联系人成功！\n");
	}
}

//删除链表
void release_link(Plink * head)
{
	Plink p = NULL;

	if(SUCCESS == make_empty(*head))
	{
		p = *head;
		*head = (*head)->next;
		free(p);
		if(NULL == *head)
		{
			printf("删除链表成功！\n");
		}
	}
	else
	{
		printf("删除链表失败！\n");
	}
}

//主函数
int main()
{
	Plink head = NULL;
	int func = 1;

	init_link(&head);
	menu();

	while(1)
	{
		printf("\n");
		printf("请输入想要操作的指令编号：");
		scanf("%d",&func);  //用int型就不需要考虑输入垃圾的影响

		switch(func)
		{
			case 1:
				{
					insert_tail(head);
					break;
				}
			case 2:
				{
					display_link(head);
					break;
				}
			case 3:
				{
					update_link(head);
					break;
				}
			case 4:
				{
					delete_link(head);
					break;
				}
			case 5:
			{
				search_link(head);
				break;
			}
			case 0:
				{
					release_link(&head);
					break;
				}
			default :
				{
					break;
				}
		}
		
		if(0 == func)
		{
			break;
		}

	}

	
	return 0;
}
