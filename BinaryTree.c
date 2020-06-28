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
#define TREEMAXNUM 9	//��������������������
#define NULLNODE ' '	//�սڵ�Ĺؼ��ֱ�ʶ


typedef int status;
typedef int ElemType; //����Ԫ�����Ͷ���
typedef char KeyElem;	//�ؼ���Ԫ�����Ͷ���

typedef struct BiNode {
	KeyElem key;	//�ؼ���
	ElemType data;	//����
	struct BiNode* lchild, *rchild;		//���Һ���ָ��
}BiTNode,*BiTree;	//���������ṹ��

typedef struct BiTList {
	BiTree Root;	//�����������
}BiTList;	//����������ṹ��

typedef BiTree Qelem;	//�ض���������������Ϊ������������

typedef struct QNode {
	Qelem data;		//����
	struct QNode* next;		//ָ����
}QNode,*QPtr;	//���н��ṹ��

typedef struct {
	QPtr front, rear;		//���ж��ס���βָ��
}LinkQueue;		//��������ṹ��

int num = 0;	//�����Ķ���������
char treename[TREEMAXNUM][20];	//�����Ķ�����������


//�Ӻ�������
status InitQueue(LinkQueue* Q);		//��ʼ������
status DestroyQueue(LinkQueue* Q);		//���ٶ���
status EnQueue(LinkQueue* Q, Qelem e);		//Ԫ�����
status DeQueue(LinkQueue* Q, Qelem* e);		//Ԫ�س���
status InitBiTree(BiTList** R);		//��ʼ��������
BiTree CreateBiTree(int count);		//����������
void ClearBiTree(BiTree* T);		//��ն�����
void DestroyBiTree(BiTList** R,int oplist);		//���ٶ�����
status BiTreeEmpty(BiTList R);		//�ж��ն�����
int BiTreeDepth(BiTree T);		//����������
BiTree Root(BiTList R);		//��ø����
void visit(KeyElem key, ElemType e);		//���ʶ������������
BiTree Vertex(BiTree T, KeyElem key);		//��ý��ָ��
ElemType Value(BiTree T, KeyElem key);		//��ý��ֵ
status Assign(BiTree T, KeyElem key, ElemType value);		//��㸳ֵ
BiTree Parent(BiTree T, KeyElem key);		//���˫�׽��
BiTree LeftChild(BiTree T, KeyElem key);		//������ӽ��
BiTree RightChild(BiTree T, KeyElem key);		//����Һ��ӽ��
BiTree LeftSibling(BiTree T, KeyElem key);		//������ֵܽ��
BiTree RightSibling(BiTree T, KeyElem key);		//������ֵܽ��
status InsertChild(BiTree T, KeyElem key, int LR, BiTree c);		//��������
status DeleteChild(BiTree T, KeyElem key, int LR);		//ɾ������
void PreOrderTraverse(BiTree T, void visit(KeyElem, ElemType));		//ǰ�����
void InOrderTraverse(BiTree T, void visit(KeyElem, ElemType));		//�������
void PostOrderTraverse(BiTree T, void visit(KeyElem, ElemType));		//�������
void LevelOrderTraverse(BiTree T, void visit(KeyElem, ElemType));		//�������
void SaveBiTNode(BiTree T, FILE* fp);		//�����������Ԫ�ش����ļ�
status SaveBiTreeElem(BiTList R);		//�������������ļ�
void LoadBiTNode(BiTree* T, FILE* fp);		//���ļ����ض��������Ԫ��
status LoadBiTreeElem(BiTList** R, int num, char* filename);		//���ļ����ض�����


//������
void main(void) {
	BiTList* T[TREEMAXNUM] = { NULL };		//������ָ������
	BiTree temptree=NULL;	//��ʱ���������ָ��
	char tempname[20];		//��ʱ����
	int op = 1;
	int temp;
	int oplist;		//ѡ��Ķ��������
	int count = num;		//��ʱ�����������Ĵ�������������
	KeyElem tempkey;
	ElemType elemdest, elemsrc;		//ԴԪ�أ�Ŀ��Ԫ��

	while (op)
	{
		system("cls");	printf("\n\n");
		printf("      Menu for Binary Tree On Chain Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. InitBiTree        12.RightChild\n");
		printf("    	  2. DestroyBiTree     13.LeftSibling\n");
		printf("    	  3. CreatBiTree       14.RightSibling\n");
		printf("    	  4. ClearBiTree       15.InsertChild\n");
		printf("    	  5. BiTreeEmpty       16.DeleteChild\n");
		printf("    	  6. BiTreeDepth       17.PreOrderTraverse \n");
		printf("          7. Root              18.InOrderTraverse\n");
		printf("    	  8. Value             19.PostOrderTraverse\n");
		printf("    	  9. Assign            20.LevelOrderTraverse\n");
		printf("    	  10.Parent            21.SaveBiTreeElem\n");
		printf("    	  11.LeftChild         22.LoadBiTreeElem\n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("Active Tree:\t");		//��ʾ��ǰ�ѽ����Ķ�����
		if (num)
			for (int i = 0; i < num; i++)
			{
				if ((i + 1) % 4 == 0)
					putchar('\n');
				printf("%d: %s\t", i, treename[i]);
			}
		printf("\n-------------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~22]:");
		scanf("%d", &op);

		if (op == 1)
		{	//����1���ʼ��������
			if (InitBiTree(&T[num % TREEMAXNUM]))
			{	//�������������ɹ���������ʱ����
				memset(tempname, 0, 20);
				strcat(tempname, "temp");
				_itoa(count, tempname + 4, 10);
				strcpy(treename[num % TREEMAXNUM], tempname);
				num = (num >= TREEMAXNUM ? TREEMAXNUM : num + 1);
				//���ѽ���������δ���������Ŀ����������������+1�����򱣳������Ŀ���䣨���������Ŀ�Ķ�����һֱ���ǵ�һ����������
				count++;	//������+1
				printf("\n��������ʼ���ɹ���\n");
			}
			else
				printf("\n��������ʼ��ʧ�ܣ�\n");
			system("pause");
		}
	
		else if (op == 22)
		{	//����22�����ļ��е�����
			printf("input file name: ");
			scanf("%s", tempname);
			if (LoadBiTreeElem(T,num,tempname))
			{	//�������ݳɹ���Զ���������Ϊ�ļ���
				strcpy(treename[num % TREEMAXNUM], tempname);
				num = (num >= TREEMAXNUM ? TREEMAXNUM : num + 1);
				printf("\n���������ݼ��سɹ�!\n");
			}
			else
				printf("\nFalse!\n");
			system("pause");
		}
		else if (op > 1 && op < 22)
		{	//��������ѡ��
			if (num > 1)
			{	//���ѽ�����������1�����ǰ��Ҫȷ��������������
				printf("���������������ţ�");
				scanf("%d", &oplist);
			}
			else	//������һ�������������Ĭ��Ϊ����������
				oplist = 0;

			if (oplist < 0 || oplist >= num || !T[oplist])
			{	//����������������������Ƿ�Ϸ� �Լ������Ķ������Ƿ����
				printf("\nBiTree is NOT EXIST!\n");
				system("pause");
			}
			else	//��������źϷ��Ҷ���������
				switch (op)
				{
				case 2:		//����2 ���ٶ�����
					DestroyBiTree(T,oplist);
					printf("\n������������!\n");
					system("pause");
					break;

				case 3:		//����3 ����������
					T[oplist]->Root = CreateBiTree(1);
					printf("�������ѽ����ɹ�!\n");
					system("pause");
					break;
				case 4:		//����4 ��ն�����
					if (T[oplist] && T[oplist]->Root)
					{
						ClearBiTree(&T[oplist]->Root);
						printf("\n�����������!\n");
					}
					else
						printf("\n���������ʧ�ܣ�\n");
					system("pause");
					break;

				case 5:		//�ж϶������Ƿ�Ϊ��
					if (BiTreeEmpty(*T[oplist]))
						printf("\nBiTree is empty!\n");
					else
						printf("\nBiTree is NOT empty!\n");
					system("pause");
					break;

				case 6:		//������������
					printf("\n���������Ϊ:%d\n", BiTreeDepth(T[oplist]->Root));
					system("pause");
					break;

				case 7:		//�����������㲢���
					if (temptree = Root(*T[oplist]))
					{
						printf("\n����㣺");
						visit(temptree->key, temptree->data);
					}
					else
						printf("\n�����Ϊ�գ�\n");
					putchar('\n');
					system("pause");
					break;

				case 8:		//��ȡ�������ֵ
					printf("�����������ؼ��֣�");
					scanf("%*c%c", &tempkey);
					elemdest = Value(T[oplist]->Root, tempkey);
					if ( elemdest== -1)
						printf("\n�ý��δ�ҵ���\n");
					else
						printf("\n�ý�����ҵ�������ֵ��%d\n", elemdest);
					system("pause");
					break;

				case 9:		//��㸳ֵ
					printf("�����������ؼ��֣�");
					scanf("%*c%c", &tempkey);
					printf("\n�������µ����ݣ�");
					scanf("%d", &elemsrc);
					if (Assign(T[oplist]->Root, tempkey, elemsrc))
						printf("\n��������¸�ֵ��\n");
					else
						printf("\n��㸳ֵʧ�ܣ�\n");
					system("pause");
					break;

				case 10:		//���˫�׽�㲢���
					printf("�����������ؼ��֣�");
					scanf("%*c%c", &tempkey);
					if (temptree = Parent(T[oplist]->Root, tempkey))
					{
						printf("\n��˫�׽��Ϊ ");
						visit(temptree->key, temptree->data);
						putchar('\n');
					}
					else
						printf("\n���˫�׻��ʧ�ܣ�\n");
					system("pause");
					break;

				case 11:		//������ӽ�㲢���
					printf("�����������ؼ��֣�");
					scanf("%*c%c", &tempkey);
					if (temptree = LeftChild(T[oplist]->Root, tempkey))
					{
						printf("\n�����ӽ��Ϊ ");
						visit(temptree->key, temptree->data);
						putchar('\n');
					}
					else
						printf("\n������ӻ��ʧ�ܣ�\n");
					system("pause");
					break;

				case 12:		//����Һ��ӽ�㲢���
					printf("�����������ؼ��֣�");
					scanf("%*c%c", &tempkey);
					if (temptree = RightChild(T[oplist]->Root, tempkey))
					{
						printf("\n���Һ��ӽ��Ϊ ");
						visit(temptree->key, temptree->data);
						putchar('\n');
					}
					else
						printf("\n����Һ��ӻ��ʧ�ܣ�\n");
					system("pause");
					break;

				case 13:		//������ֵܽ�㲢���
					printf("�����������ؼ��֣�");
					scanf("%*c%c", &tempkey);
					if (temptree = LeftSibling(T[oplist]->Root, tempkey))
					{
						printf("\n�����ֵܽ��Ϊ ");
						visit(temptree->key, temptree->data);
						putchar('\n');
					}
					else
						printf("\n������ֵܻ��ʧ�ܣ�\n");
					system("pause");
					break;

				case 14:		//������ֵܽ�㲢���
					printf("�����������ؼ��֣�");
					scanf("%*c%c", &tempkey);
					if (temptree = RightSibling(T[oplist]->Root, tempkey))
					{
						printf("\n�����ֵܽ��Ϊ ");
						visit(temptree->key, temptree->data);
						putchar('\n');
					}
					else
						printf("\n������ֵܻ��ʧ�ܣ�\n");
					system("pause");
					break;

				case 15:		//��������
					printf("������������c��\n");
					printf("������1�����\n������ؼ���:");
					scanf("%*c%c", &tempkey);	//�������������
					if (tempkey == NULLNODE)	//�����������Ϊ���򲻺Ϸ�
					{
						printf("\n�����������Ϸ���\n");
						system("pause");
						break;
					}
					
					temptree = (BiTree)malloc(sizeof(BiTNode));		//����������㲻Ϊ�ռ�������
					if (!temptree)
					{
						printf("��������ʧ�ܣ�\n");
						system("pause");
						break;
					}
					temptree->key = tempkey;
					printf("����������:");
					scanf("%d", &temptree->data);
					//temptree->father = NULL;//
					temptree->lchild = CreateBiTree(1);	//���ݹ鴴����������������������Ϊ��
					temptree->rchild = NULL;
				
					printf("\n�����������ؼ��֣�");
					scanf("%*c%c", &tempkey);
					printf("\n�������������(0.������/1.������):");
					scanf("%d", &temp);
					if (temp != 0 && temp != 1)
					{
						printf("\n�������!\n");
						system("pause");
						break;
					}
					if (InsertChild(T[oplist]->Root, tempkey, temp, temptree))
						printf("\n���������ɹ���\n");
					else
						printf("\n��������ʧ�ܣ�\n");
					system("pause");
					break;

				case 16:		//ɾ������
					printf("\n�����������ؼ��֣�");
					scanf("%*c%c", &tempkey);
					printf("\n�������������(0.������/1.������):");
					scanf("%d", &temp);
					if (temp != 0 && temp != 1)
					{
						printf("\n�������!\n");
						system("pause");
						break;
					}
					if (DeleteChild(T[oplist]->Root, tempkey, temp))
						printf("\nɾ�������ɹ���\n");
					else
						printf("\nɾ������ʧ�ܣ�\n");
					system("pause");
					break;

				case 17:
					printf("ǰ�������");
					PreOrderTraverse(T[oplist]->Root,visit);
					putchar('\n');
					system("pause");
					break;

				case 18:
					printf("���������");
					InOrderTraverse(T[oplist]->Root, visit);
					putchar('\n');
					system("pause");
					break;

				case 19:
					printf("���������");
					PostOrderTraverse(T[oplist]->Root, visit);
					putchar('\n');
					system("pause");
					break;

				case 20:
					printf("���������");
					LevelOrderTraverse(T[oplist]->Root, visit);
					putchar('\n');
					system("pause");
					break;
							
				case 21:		//���������е�Ԫ�ش��뵽�ļ���
					if (SaveBiTreeElem(*T[oplist]))
						printf("\n�����������ѱ���!\n");
					else
						printf("\n���������ݱ���ʧ�ܣ�\n");
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

	for (int i = 0; i < num; i++)		//�˳�ϵͳǰ���������ѽ�������
		DestroyBiTree(T,i);
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()


status InitQueue(LinkQueue* Q)
{	//��ʼ������
	Q->front = Q->rear = (QPtr)malloc(sizeof(QNode));	//������β���
	if (!Q->front)
		exit(OVERFLOW);
	Q->front->next = NULL;	//���ָ��Ϊ��
	return OK;
}

status DestroyQueue(LinkQueue* Q)
{	//���ٶ���
	while (Q->front)	//����ָ�벻Ϊ�����ͷŵ�ǰ��ָ���
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
	return OK;
}

status EnQueue(LinkQueue* Q, Qelem e)
{	//Ԫ�����
	QPtr p;
	p = (QPtr)malloc(sizeof(QNode));	//�������н��
	if (!p)
		return FALSE;
	p->data = e;		//�������ݸ�ֵ
	p->next = NULL;
	Q->rear->next = p;	//���׶�βָ�����
	Q->rear = p;
	return OK;
}

status DeQueue(LinkQueue* Q, Qelem* e)
{	//Ԫ�س���
	QPtr p;
	if (Q->front == Q->rear)	//����Ϊ�շ���ʧ��
		return ERROR;
	p = Q->front->next;
	*e = p->data;		//����Ԫ�ظ�ֵ
	Q->front->next = p->next;
	if (Q->rear == p)		//�����Ӻ�ӿ�����βָ��ָ��һ��
		Q->rear = Q->front;
	free(p);
	return OK;
}

status InitBiTree(BiTList** R)
{	//��ʼ��������R
	(*R) = (BiTList*)malloc(sizeof(BiTList));	//�����������ṹ��
	if (!(*R)->Root)
		return OVERFLOW;
	(*R)->Root = NULL;		//�������������Ϊ��ָ��
	return OK;
}

BiTree CreateBiTree(int count)
{	//������������countΪ��ǰ��������Ľ�����
	KeyElem e;
	BiTree New = NULL;
	printf("������%d�����\n������ؼ���:", count);
	scanf("%*c%c", &e);
	count--;	//�����������-1
	if (e != NULLNODE)		//������Ĺؼ��ֲ�Ϊ�սڵ��ʶ
	{
		New = (BiTree)malloc(sizeof(BiTNode));		//�������������
		if (!New)
			return FALSE;
		New->key = e;		//��㸳ֵ
		printf("����������:");
		scanf("%d", &New->data);
		//New->father = father;	//
		New->lchild = CreateBiTree(count + 2);		//�ݹ齨���ӽڵ�
		New->rchild = CreateBiTree(count + 1);
	}
	return New;		//���ض����������
}


void ClearBiTree(BiTree* T)
{	//��ն�����T
	if ((*T)->lchild)	//��������T���ӽڵ㲻Ϊ�����ȵݹ��������
		ClearBiTree(&(*T)->lchild);
	if ((*T)->rchild)
		ClearBiTree(&(*T)->rchild);
	if (!(*T)->lchild && !(*T)->rchild)		//��T��Ҷ�ӽ��
	{
		free(*T);	//���ͷŽ���ڴ�
		*T = NULL;	//ָ��ָ���
	}
}

void DestroyBiTree(BiTList** R,int oplist)
{	//���ٶ�����R[oplist]
	if(R[oplist]->Root)
		ClearBiTree(&R[oplist]->Root);	//����ն��������н��
	free(R[oplist]);	//�ͷŶ������ṹ��
	for (; oplist < num - 1; oplist++)
	{
		R[oplist] = R[oplist + 1];		//�����ٶ�������Ķ�����ǰ��
		strcpy(treename[oplist], treename[oplist + 1]);		//���ٶ�������Ķ���������ǰ��
	}
	memset(treename[oplist], 0, 20);	//���������������
	R[oplist] = NULL;		//������ָ��ָ���
	num--;		//�ѽ�������������-1
}


status BiTreeEmpty(BiTList R)
{	//�ж�R�Ƿ�Ϊ�ն�������TRUE���գ�FALSE����Ϊ��
	if (R.Root)		//������������㲻Ϊ��
		return FALSE;		//������Ϊ��
	else		//�������������Ϊ��
		return TRUE;	//�������Ϊ��
}

int BiTreeDepth(BiTree T)
{	//�������T����ȣ����ض�������ȵ�����
	int dep = 0;	//��ʼ���������Ϊ0
	int i, j;
	if (T)	//��T�ĸ�����㲻Ϊ��
	{
		dep++;		//�������+1
		i = BiTreeDepth(T->lchild);		//�ݹ�����������������
		j = BiTreeDepth(T->rchild);
		dep += i > j ? i : j;	//��T�����Ϊԭ���+������ȴ�����
	}
	return dep;		//�����������
}


BiTree Root(BiTList R)
{	//���ض�����R�ĸ����
	return R.Root;
}

void visit(KeyElem key, ElemType e)
{	//������ݷ���
	printf("%c:%d\t", key, e);		//������ؼ��ֺ�����
}

BiTree Vertex(BiTree T, KeyElem key)
{	//��ý�㣺���ض�����T��ָ��ؼ���Ϊkey�Ľ��ָ��
	BiTree temp1 = NULL, temp2 = NULL;
	if (T)		//����ǰ���T��Ϊ��
	{
		if (T->key == key)	//����ǰ���T�Ĺؼ��ּ�Ϊ����
			return T;		//��ֱ�ӷ��ص�ǰ���ָ��
		if (T->lchild)		//����ǰ��������ӽ��
			temp1 = Vertex(T->lchild, key);	//�ݹ�Ѱ�ҽ�㲢���ظ�temp1
		if (temp1)		//��temp1��Ϊ�������ҵ����
			return temp1;		//����temp1��ָ���ָ��
		if (T->rchild)		//��������δ�ҵ�������������
			temp2 = Vertex(T->rchild, key);		//�ݹ�Ѱ�ҽ�㲢���ظ�temp2
		return temp2;		//����temp2
	}
	return NULL;	//�������TΪ��ֱ�ӷ���NULL
}

ElemType Value(BiTree T, KeyElem key)
{	//��ý��ֵ�����ض�����T�йؼ���Ϊkey�Ľ�������ֵ��δ�ҵ�����-1
	BiTree temp = Vertex(T, key);	//tempΪָ��key����ָ��
	if (temp)		//��temp��Ϊ��
		return temp->data;		//�򷵻ؽ�������
	return -1;		//��tempΪ���򷵻�-1����ʾδ�ҵ���
}

status Assign(BiTree T, KeyElem key, ElemType value)
{	//��㸳ֵ����������T�йؼ���Ϊkey�Ľ�㸳ֵvalue
	BiTree temp = Vertex(T, key);		//tempΪָ��key����ָ��
	if (temp)		//��temp��Ϊ��
	{
		temp->data = value;		//�����������¸�ֵ
		return OK;		//���سɹ�
	}
	return ERROR;		//δ�ҵ�����ʧ��
}

BiTree Parent(BiTree T, KeyElem key)
{	//���˫�׽�㣺���ض�����T�йؼ���Ϊkey�Ľ���˫�׽��ָ�룬�����������NULL
	BiTree temp1 = NULL, temp2 = NULL;
	if (T)	//����ǰ�ڵ�T��Ϊ��
	{
		if (T->lchild && T->lchild->key == key)
			return T;		//��T�����������������Ĺؼ���Ϊkey�򷵻�T
		if (T->rchild && T->rchild->key == key)
			return T;		//��T�����������������Ĺؼ���Ϊkey�򷵻�T
		if (T->lchild)		//��T������
			temp1 = Parent(T->lchild, key);		//�ݹ�Ѱ��˫��
		if (temp1)
			return temp1;	//�����������ҵ�˫���򷵻�
		if (T->rchild)		//���������������Ҳ�����
			temp2 = Parent(T->rchild, key);
		return temp2;
	}
	return NULL;		//�������TΪ��ֱ�ӷ���NULL
}

BiTree LeftChild(BiTree T, KeyElem key)
{	//������ӽ�㣺���ض�����T�йؼ���Ϊkey�Ľ������ӽ��ָ��
	BiTree temp = Vertex(T, key);		//tempΪָ��key����ָ��
	if (temp)
		return temp->lchild;		//temp��Ϊ�շ�������ָ��
	return NULL;		//δ�ҵ�����NULL
}

BiTree RightChild(BiTree T, KeyElem key)
{	//����Һ��ӽ�㣺���ض�����T�йؼ���Ϊkey�Ľ����Һ��ӽ��ָ��
	BiTree temp = Vertex(T, key);		//tempΪָ��key����ָ��
	if (temp)
		return temp->rchild;		//temp��Ϊ�շ����Һ���ָ��
	return NULL;		//δ�ҵ�����NULL
}

BiTree LeftSibling(BiTree T, KeyElem key)
{	//������ֵܽ�㣺���ض�����T�йؼ���Ϊkey�Ľ������ֵܽ��ָ��
	BiTree dad = Parent(T, key);	//dadΪkey����˫�׽��
	if (dad && dad->lchild && dad->lchild->key != key)//��key�����˫�׽�㡢˫�׽�������������Ӳ�Ϊkey���
		return dad->lchild;		//����˫�׽�������
	return NULL;		//�����������NULL
}

BiTree RightSibling(BiTree T, KeyElem key)
{	//������ֵܽ�㣺���ض�����T�йؼ���Ϊkey�Ľ������ֵܽ��ָ��
	BiTree dad = Parent(T, key);	//dadΪkey����˫�׽��
	if (dad && dad->rchild && dad->rchild->key != key)//��key�����˫�׽�㡢˫�׽�����Һ������Һ��Ӳ�Ϊkey���
		return dad->rchild;		//����˫�׽����Һ���
	return NULL;		//�����������NULL
}

status InsertChild(BiTree T, KeyElem key, int LR, BiTree c)
{	//�����������ڶ�����T��key����LR��0Ϊ��/1Ϊ�ң�������������c
	BiTree p = Vertex(T, key);		//pָ��key���
	if (!p)		//�����δ�ҵ��򷵻�ʧ��
		return ERROR;
	if (LR)		//���뵽������
	{
		c->rchild = p->rchild;
		p->rchild = c;
	}
	else		//���뵽������
	{
		c->rchild = p->lchild;
		p->lchild = c;
	}
	return OK;		//���سɹ�
}

status DeleteChild(BiTree T, KeyElem key, int LR)
{	//ɾ��������ɾ��������T�йؼ���Ϊkey�Ľ���LR����
	BiTree p = Vertex(T, key);		//pΪkey���
	if (!p)		//�����δ�ҵ�����ʧ��
		return ERROR;
	if (LR && p->rchild)	//ɾ��������
		ClearBiTree(&p->rchild);
	else if (p->lchild)		//ɾ��������
		ClearBiTree(&p->lchild);
	return OK;		//���سɹ�
}

void PreOrderTraverse(BiTree T, void visit(KeyElem, ElemType))
{	//�������
	if (T)		//��ǰ��㲻Ϊ��
	{
		visit(T->key, T->data);		//�ȷ�������
		PreOrderTraverse(T->lchild, visit);		//�����εݹ����������������
		PreOrderTraverse(T->rchild, visit);
	}
}

void InOrderTraverse(BiTree T, void visit(KeyElem, ElemType))
{	//�������
	if (T)		//��ǰ��㲻Ϊ��
	{
		InOrderTraverse(T->lchild, visit);		//�ȵݹ��������������
		visit(T->key, T->data);		//�ٷ��ʵ�ǰ�ڵ�����
		InOrderTraverse(T->rchild, visit);		//���ݹ��������������
	}
}

void PostOrderTraverse(BiTree T, void visit(KeyElem, ElemType))
{	//�������
	if (T)		//��ǰ��㲻Ϊ��
	{
		PostOrderTraverse(T->lchild, visit);	//�����εݹ���������������
		PostOrderTraverse(T->rchild, visit);
		visit(T->key, T->data);		//����������
	}
}

void LevelOrderTraverse(BiTree T, void visit(KeyElem, ElemType))
{	//�������
	BiTree temp = T;	//tempָ������������
	LinkQueue Q;	
	if (!T)
		return;
	InitQueue(&Q);	//��ʼ������Q
	do {
		visit(temp->key, temp->data);	//�ȷ��ʵ�ǰ���
		if (temp->lchild)		//����ǰ������������������
			EnQueue(&Q, temp->lchild);
		if (temp->rchild)		//����ǰ�ڵ����Һ������Һ������
			EnQueue(&Q, temp->rchild);
	} while (DeQueue(&Q, &temp));	//�������ܳ���һ��Ԫ�������ѭ��������Ԫ�ظ�ֵ��temp
	DestroyQueue(&Q);
}

void SaveBiTNode(BiTree T, FILE* fp)
{	//�����T�����ݴ����ļ�
	KeyElem nullkey = NULLNODE;		//nullkeyΪ�ս���ʶ
	if (!T)		//����ǰ�ڵ�TΪ���������սڵ��ʶ
	{
		fwrite(&nullkey, sizeof(KeyElem), 1, fp);
		return;
	}
	fwrite(&T->key, sizeof(KeyElem), 1, fp);	//���T��Ϊ�������ζ���ؼ��ֺ�����
	fwrite(&T->data, sizeof(ElemType), 1, fp);
	SaveBiTNode(T->lchild, fp);		//�ݹ齫��ǰ�ڵ����Һ��Ӵ����ļ�
	SaveBiTNode(T->rchild, fp);
}

status SaveBiTreeElem(BiTList R)
{	//��������R�����ݴ����ļ�
	FILE* fp;
	char filename[30];
	printf("input file name: ");		//�����ļ���
	scanf("%s", filename);
	if ((fp = fopen(filename, "wb")) == NULL)
	{
		printf("File open error!\n ");
		return ERROR;
	}
	SaveBiTNode(R.Root, fp);	//�Ӹ����ݹ�����ļ�
	fclose(fp);
	return OK;
}

void LoadBiTNode(BiTree* T, FILE* fp)
{	//���ļ����ص����������T
	KeyElem tempkey;
	ElemType tempdata;
	if (fread(&tempkey, sizeof(KeyElem), 1, fp))	//���ȶ�ȡһ���ؼ���
	{
		if (tempkey == NULLNODE)		//�������Ϊ�սڵ��ʶ
		{
			*T = NULL;		//��ǰ���Ϊ�ղ�����
			return;
		}	
		fread(&tempdata, sizeof(ElemType), 1, fp);		//����ǰ�ڵ㲻Ϊ������������ݶ���
		(*T) = (BiTree)malloc(sizeof(BiTNode));		//����һ�����������
		(*T)->key = tempkey;		//��㸳ֵ
		(*T)->data = tempdata;
		LoadBiTNode(&(*T)->lchild, fp);		//�ݹ���ص�ǰ������������
		LoadBiTNode(&(*T)->rchild, fp);
	}
}

status LoadBiTreeElem(BiTList** R, int num, char* filename)
{	//��filename�ļ��ж������ݵ�������R[num]
	FILE* fp;

	if (!R[num])	//��������R[num]���������ʼ��������
		InitBiTree(&R[num]);
	else	//���Ѵ����������
		ClearBiTree(&R[num]->Root);
	if ((fp = fopen(filename, "rb")) == NULL)
	{
		printf("File open error!\n ");
		return ERROR;
	}
	LoadBiTNode(&R[num]->Root, fp);		//�Ӹ����ݹ�������ݵ����
	fclose(fp);
	return OK;
}

