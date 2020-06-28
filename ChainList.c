/* �������� */


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include<string.h>

//������ʶ�궨��
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define LISTMAXNUM 9	//������������������


typedef int status;
typedef int ElemType; //����Ԫ�����Ͷ���

typedef struct LNode{
	ElemType data;
	struct LNode* next;
}*Link;	//����ڵ�ṹ��

typedef struct {
	Link head;
	int len;
}LinkList;			//��������ṹ��

int num = 0;		//�������������
char listname[LISTMAXNUM][20];	//���������������


//�Ӻ�������
status InitList(LinkList** L);		//��ʼ������
status CreateList(LinkList* L);		//���������㲢����
status ListExist(LinkList* L);		//�ж������Ƿ����
status DestoryList(LinkList** L, int oplist);		//��������
status ClearList(LinkList* L);		//�������
status ListEmpty(LinkList L);		//�ж������Ƿ�Ϊ�ձ�
int ListLength(LinkList L);		//��������
status GetELem(LinkList L, int i, ElemType* e);		//���Ԫ��
status compare(struct LNode node, ElemType e);		//�ȽϺ���
int LocateElem(LinkList L, ElemType e, status compare(struct LNode, ElemType));		//������������Ԫ��
status PriorElem(LinkList L, ElemType cur_e, ElemType* pre_e);		//���ǰ��
status NextElem(LinkList L, ElemType cur_e, ElemType* next_e);		//��ú��
status ListInsert(LinkList* L, int i, ElemType e);		//����Ԫ��
status ListDelete(LinkList* L, int i, ElemType* e);		//ɾ��Ԫ��
status ListTraverse(LinkList L, void (*visit)(ElemType));		//��������
void visit(ElemType);		//���ʽ����Ԫ��
status SaveElem(LinkList L);		//����Ԫ�ش����ļ�
status LoadElem(LinkList** L, int num, char* filename);		//���ļ���������Ԫ��


//��������������͵����Ӻ���Ԥ����
void main(void) {
	LinkList* L[LISTMAXNUM] = { NULL };		//����ָ������
	char tempname[20];		//��ʱ����
	int op = 1;
	int temp;
	int oplist;		//ѡ����������
	int count=num;		//��ʱ��������Ĵ�������������
	ElemType elemdest,elemsrc;		//ԴԪ�أ�Ŀ��Ԫ��

	while (op) 
	{
		system("cls");	printf("\n\n");
		printf("      Menu for Linear Table On Chain Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. InitList        8. PriorElem\n");
		printf("    	  2. DestroyList     9. NextElem \n");
		printf("    	  3. ClearList       10.ListInsert \n");
		printf("    	  4. ListEmpty       11.ListDelete\n");
		printf("    	  5. ListLength      12.ListTrabverse\n");
		printf("    	  6. GetElem         13.SaveElem \n");
		printf("          7. LocateElem      14.LoadElem\n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("Active List:\t");		//��ʾ��ǰ�ѽ���������
		if (num)
			for (int i = 0; i < num; i++)
			{
				if ((i + 1) % 4 == 0)
					putchar('\n');
				printf("%d: %s\t", i, listname[i]);	
			}
		printf("\n-------------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~14]:");
		scanf("%d", &op);

		if (op == 1)
		{	//����1���ʼ������ͬʱ����������������
			if (InitList(&L[num%LISTMAXNUM]) && CreateList(L[num%LISTMAXNUM]))
			{	//����������ɹ���������ʱ����
				memset(tempname, 0, 20);
				strcat(tempname, "temp");
				_itoa(count, tempname + 4, 10);
				strcpy(listname[num%LISTMAXNUM], tempname);
				num = (num >= LISTMAXNUM ? LISTMAXNUM : num + 1);
				//���ѽ�������δ���������Ŀ������������+1�����򱣳������Ŀ���䣨���������Ŀ������һֱ���ǵ�һ������
				count++;	//������+1
				printf("\n���Ա����ɹ���\n");
			}
			else
				printf("\n���Ա���ʧ�ܣ�\n");
			system("pause");
		}
		else if (op == 14)
		{	//����14�����ļ��е�����
			printf("input file name: ");
			scanf("%s", tempname);
			if (LoadElem(L,num%9,tempname))
			{	//�������ݳɹ������������Ϊ�ļ���
				strcpy(listname[num % LISTMAXNUM], tempname);
				num = (num >= LISTMAXNUM ? LISTMAXNUM : num+1);
				printf("\n�������ݳɹ�!\n");
			}
			else
				printf("\nFalse!\n");
			system("pause");
		}
		else if(op>1&&op<14)
		{	//��������ѡ��
			if (num > 1)
			{	//���ѽ�����������1�����ǰ��Ҫȷ��������������
				printf("���������������ţ�");
				scanf("%d", &oplist);
			}
			else	//������һ�������������Ĭ��Ϊ����������
				oplist = 0;

			if (oplist<0||oplist>=num||!ListExist(L[oplist]))
			{	//�������������������Ƿ�Ϸ� �Լ������������Ƿ����
				printf("\nList is NOT EXIST!\n");
				system("pause");
			}
			else	//������źϷ����������
				switch (op)
				{
				case 2:		//����2 ��������
				if (DestoryList(L,oplist))
					printf("\n���Ա���ɾ����\n");
				else
					printf("\nFalse!\n");
				system("pause");
				break;

				case 3:		//����3 �������
					if (ClearList(L[oplist]))
						printf("\n���Ա�����գ�\n");
					else
						printf("\nFalse!\n");
					system("pause");
					break;

				case 4:		//�ж������Ƿ�Ϊ��
					if (ListEmpty(*L[oplist]))
						printf("\nList is empty!\n");
					else
						printf("\nList is NOT empty!\n");
					system("pause");
					break;

				case 5:		//��������ȣ�Ԫ�ظ�����
					printf("\nThe length of the list is:%d\n", ListLength(*L[oplist]));
					system("pause");
					break;

				case 6:		//��ȡ����ĳԪ��
					printf("\n�������ȡ��Ԫ����ţ�");
					scanf("%d", &temp);
					if (GetELem(*L[oplist], temp, &elemdest))
						printf("\n��ȡ�ɹ���%d\n", elemdest);
					else
						printf("\n��ȡʧ�ܣ�\n");
					system("pause");
					break;

				case 7:		//���������ȶ�Ԫ��������
					printf("\n��������ȶ����ݣ�");
					scanf("%d", &elemsrc);
					printf("\n��һ�������������ţ�%d\n", LocateElem(*L[oplist], elemsrc, compare));
					system("pause");
					break;

				case 8:		//���ĳԪ�ص�ǰ��
					printf("\n������һ������Ԫ�أ�");
					scanf("%d", &elemsrc);
					if (PriorElem(*L[oplist], elemsrc, &elemdest))
						printf("\n��ȡ�ɹ���%d\n", elemdest);
					else
						printf("\n��ȡʧ�ܣ�\n");
					system("pause");
					break;

				case 9:		//���ĳԪ�صĺ��
					printf("\n������һ������Ԫ�أ�");
					scanf("%d", &elemsrc);
					if (NextElem(*L[oplist], elemsrc, &elemdest))
						printf("\n��ȡ�ɹ���%d\n", elemdest);
					else
						printf("\n��ȡʧ�ܣ�\n");
					system("pause");
					break;
				
				case 10:		//����Ԫ��
					printf("\n���������Ԫ����ţ�");
					scanf("%d", &temp);
					printf("\n���������Ԫ����ֵ��");
					scanf("%d", &elemsrc);
					if (ListInsert(L[oplist], temp, elemsrc))
						printf("\n����ɹ�!\n");
					else
						printf("\nFalse!\n");
					system("pause");
					break;

				case 11:		//ɾ��Ԫ��
					printf("\n������ɾ��Ԫ����ţ�");
					scanf("%d", &temp);
					if (ListDelete(L[oplist], temp, &elemdest))
						printf("\nɾ���ɹ�: Delete %d\n", elemdest);
					else
						printf("\nFalse!\n");
					system("pause");
					break;

				case 12:		//��������
					if (!ListTraverse(*L[oplist], visit))
						printf("���Ա��ǿձ�\n");
					system("pause");
					break;

				case 13:		//�������е�Ԫ�ش��뵽�ļ���
					if(SaveElem(*L[oplist]))
						printf("\n�������ݳɹ�!\n");
					else
						printf("\nFalse!\n");
					system("pause");
					break;
				}
		}
		else if (op)	//������������
		{
			printf("\n�������!\n");
			system("pause");
		}
	}//end of while

	for (int i = 0; i < num; i++)		//�˳�ϵͳǰ���������ѽ�����
		DestoryList(L, i);
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()




status InitList(LinkList** L)
{	//��ʼ��������������ṹ�壨*L��������ͷ���
	(*L) = (LinkList*)malloc(sizeof(LinkList));
	(*L)->head = (Link)malloc(sizeof(struct LNode));	//������ͷ�ڵ�
	(*L)->head->next = NULL;
	if (!(*L)->head)
		return OVERFLOW;
	(*L)->len = 0;
	return OK;
}

status CreateList(LinkList* L)
{	//����������������L�Ľڵ㲢�������ݣ�����0ʱ����������
	Link end, New;
	int e;
	end = L->head;
	printf("Input Element:");
	scanf("%d", &e);
	if (!e)		//��ʼ����0�򲻴�������Ӻ�������
		return ERROR;
	while (e)
	{
		New = (Link)malloc(sizeof(struct LNode));	//�������
		if (!New)
			return OVERFLOW;
		New->data = e;		//���ݸ�ֵ
		New->next = end->next;
		end->next = New;
		end = New;
		L->len++;	//������+1
		scanf("%d", &e);
	}
	return OK;
}

status ListExist(LinkList* L)
{	//�������L�Ƿ���ڣ�FALSE�����ڣ�TRUE����
	if (!L)
		return FALSE;
	return TRUE;
}

status DestoryList(LinkList** L, int oplist)
{	//��������L[oplist]
	Link cur, next;
	cur = L[oplist]->head;
	while (cur)		//����������
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	free(L[oplist]);	//��������ṹ��
	for (; oplist < num - 1; oplist++)
	{
		L[oplist] = L[oplist + 1];		//����������������ǰ��
		strcpy(listname[oplist], listname[oplist + 1]);		//����������������ǰ��
	}
	memset(listname[oplist], 0, 20);	//�������������
	L[oplist] = NULL;
	num--;		//�ѽ���������-1
	return OK;
}

status ClearList(LinkList* L)
{	//�������L��ʹ�����Ԫ�ؽ���ͷţ�����ͷ���
	Link cur, next;
	cur = L->head->next;
	while (cur)		//�ͷ�Ԫ�ؽ��
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	L->head->next = NULL;
	L->len = 0;		//��ǰ��������0
	return OK;
}

status ListEmpty(LinkList L)
{	//�������L�Ƿ�Ϊ�ձ�TRUEΪ�ձ�FLASE��Ϊ��
	if (L.head->next)
		return FALSE;
	return TRUE;
}

int ListLength(LinkList L)
{	//��������L�ĳ���
	//Link temp;
	//int len;
	//for (len = 0, temp = L.head->next; temp; temp = temp->next)
	//	len++;
	//return len;
	return L.len;
}

status GetELem(LinkList L, int i, ElemType* e)
{	//��ȡ����L��i��Ԫ�ز�����e��
	Link temp;
	int j;
	if (i <= 0 || i > L.len)	//i�ĺϷ��Լ��
		return ERROR;
	for (j = 1, temp = L.head->next; j < i; temp = temp->next, j++);//ʹtempָ�������Ԫ�صĽ��
	*e = temp->data;//Ԫ�ظ�ֵ��e
	return OK;
}

status compare(struct LNode node, ElemType e)
{	//�ȽϺ�����������е�Ԫ�ش���e�򷵻�TRUE�����򷵻�FALSE�����Զ��壩
	if (node.data > e)
		return TRUE;
	else
		return FALSE;
}

int LocateElem(LinkList L, ElemType e, status compare(struct LNode, ElemType))
{	//���ݱȽϺ���compare�������������ĵ�һ��Ԫ�ص����
	Link temp;
	int i;
	for (i = 1, temp = L.head->next; temp; temp = temp->next, i++)
		if (compare(*temp, e))	//���������ԱȽ�
			return i;
	return 0;
}

status PriorElem(LinkList L, ElemType cur_e, ElemType* pre_e)
{	//��������L��Ԫ��Ϊcur_e��ǰ��Ԫ�ص�pre_e��
	Link pre = L.head, cur = pre->next;
	if (!cur || cur_e == cur->data)		//��������Ƿ�Ϊ�ձ�ͬʱcur_e��Ϊ��һ��Ԫ��
		return ERROR;
	for (; cur; pre = cur, cur = cur->next)
		if (cur_e == cur->data)		//�ж��Ƿ�Ϊcur_e
		{
			*pre_e = pre->data;
			return OK;
		}
	return ERROR;	//δ�ҵ�����ERROR
}

status NextElem(LinkList L, ElemType cur_e, ElemType* next_e)
{	//��������L��Ԫ��Ϊcur_e�ĺ��Ԫ�ص�next_e��
	Link cur = L.head->next, next;
	if (!cur)	//��������Ƿ�Ϊ�ձ�
		return ERROR;
	next = cur->next;
	for (; next; cur = next, next = next->next)	//���������������ڶ���Ԫ��
		if (cur_e == cur->data)		//�ж��Ƿ�Ϊcur_e
		{
			*next_e = next->data;
			return OK;
		}
	return ERROR;	//δ�ҵ�����ERROR
}

status ListInsert(LinkList* L, int i, ElemType e)
{	//������L�ĵ�i��1<=i<=len+1����Ԫ��ǰ����Ԫ��e
	Link temp, New;
	int j;
	if (i<1 || i>L->len + 1)	//���i�ĺϷ��ԣ����Ϸ�����ERROR
		return ERROR;
	for (j = 1, temp = L->head; j < i; j++, temp = temp->next);	//������������λ��
	New = (Link)malloc(sizeof(struct LNode));		//�½����
	if (!New)
		return ERROR;
	New->data = e;		//��㸳ֵ
	New->next = temp->next;		//������ӵ�����
	temp->next = New;
	L->len++;	//������+1
	return OK;
}

status ListDelete(LinkList* L, int i, ElemType* e)
{	//ɾ������L�ĵ�i��Ԫ�ز�����ֵ����e
	Link temp, dest;
	int j;
	if (i<1 || i>L->len)	//���i�ĺϷ��ԣ����Ϸ�����ERROR
		return ERROR;
	for (j = 1, temp = L->head; j < i; j++, temp = temp->next);	//��������ɾ��λ��
	dest = temp->next;
	*e = dest->data;		//��ɾ��ֵ����e
	temp->next = dest->next;
	free(dest);		//�ͷŽ��
	L->len--;		//������-1
	return OK;
}


status ListTraverse(LinkList L, void (*visit)(ElemType))
{	//ʹ��vist������������L
	Link temp;
	if (!L.head->next)
		return ERROR;
	for (temp = L.head->next; temp; temp = temp->next)
		visit(temp->data);
	putchar('\n');
	return OK;
}

void visit(ElemType e)
{	//���ʣ���������node��Ԫ��
	printf("%d\t", e);
}

status SaveElem(LinkList L)
{	//������L�е�Ԫ�ش����ļ���
	Link temp;
	FILE* fp;
	char filename[30];
	printf("input file name: ");		//�����ļ���
	scanf("%s", filename);
	if ((fp = fopen(filename, "wb")) == NULL)
	{
		printf("File open error!\n ");
		return ERROR;
	}
	for (temp = L.head->next; temp; temp = temp->next)
		fwrite(&temp->data, sizeof(ElemType), 1, fp);	//��ÿ������е�Ԫ��д���ļ���
	fclose(fp);
	return OK;
}

status LoadElem(LinkList** L, int num, char* filename)
{	//�����ļ���Ϊfilename�е�Ԫ�ص�����L[num]��
	FILE* fp;
	Link end, New;
	ElemType temp;
	if (!ListExist(L[num]))		//������L[num]���������ʼ��
		InitList(&L[num]);
	else
		ClearList(L[num]);		//������L[num]�Ѵ������������
	if ((fp = fopen(filename, "rb")) == NULL)
	{
		printf("File open error!\n ");
		return ERROR;
	}
	end = L[num]->head;
	while (fread(&temp, sizeof(ElemType), 1, fp))
	{	//ÿ�ζ���һ�����ݲ����뵽��������������
		New = (Link)malloc(sizeof(struct LNode));
		New->data = temp;
		New->next = end->next;
		end->next = New;
		end = New;
		L[num]->len++;
	}
	return OK;
}

