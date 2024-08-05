#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_BORROW_BOOKS 10 
struct book
{
	char name[20];//���� 
	char author[20];//���� 
	char publisher[20];//������ 
	int time;//���ʱ�� 
	int Num;//�����
	int borrow_Num;//������ 
};
struct Node
{
	struct book data;
	struct Node* next;
};
 struct Node* list=NULL;
struct Node* createHead()
{
	struct Node* headNode=(struct Node*)malloc(sizeof(struct Node));
	headNode->next=NULL;
	return headNode;
}

//�����ڵ� 
struct Node* createNode(struct book data)
{
	struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
	newNode->data =data;
	newNode->next=NULL;
	return newNode;
}

//���ĵ��鼮 
struct BorrowedBook
 {  
    struct book data;  
};  

//�����û�
typedef struct
{
	char name[20];
	char password[20];
	struct BorrowedBook borrowedBooks[MAX_BORROW_BOOKS];  //ÿ������10���� 
    int borrowCount; // �û���ǰ���ĵ�ͼ������  
 } User;
 
//�������Ա 
typedef struct
{
	char name[20];
	char password[20];
}Admin;

	User users[100];
	Admin admins[10];
	int userCount=0;
	int adminCount=0;
	char username[20];
	char userpassword[20];
	char adminname[20];
	char adminpassword[20];
//�û���¼ 
int currentUserIndex = -1;
int user_login(User users[],int userCount,char* username,char* password)
{
	
	for(int i=0;i<userCount;i++)
	{
		if(strcmp(users[i].name,username)==0&&strcmp(users[i].password,password)==0)
		{
			currentUserIndex = i;
			return 1;
		}
		
	}
	return 0;
 }
  
//����Ա��¼ 
  
  int admin_login(Admin admins[],int adminCount,char* adminname,char* password)
{
	for(int i=0;i<adminCount;i++)
	{
		if(strcmp(admins[i].name,adminname)==0&&strcmp(admins[i].password,password)==0)
		{
			return 1;
		}
	}
	return 0;
 }
//�û�ע��
int registerUser(User users[],int* userCount )
{
	User user;
	printf("�������û�����\n");
	scanf("%s",&user.name);
	printf("���������룺\n");
	scanf("%s",&user.password);
	users[*userCount]=user;
	(*userCount)++;
	FILE* fp;
	if((fp=fopen("users.txt","a"))==NULL)
	{
		printf("�ļ���ʧ��\n");
		return 0;
	}
	fprintf(fp,"%s\t%s\n",user.name,user.password);
	fclose(fp);
	return 1;
} 
//����Աע��
 int registerAdmin(Admin admins[],int* adminCount )
{
	Admin admin;
	printf("�������û�����\n");
	scanf("%s",&admin.name);
	printf("���������룺\n");
	scanf("%s",&admin.password);
	admins[*adminCount]=admin;
	(*adminCount)++;
	FILE* fp;
	if((fp=fopen("admins.txt","a"))==NULL)
	{
		printf("�ļ���ʧ��\n");
		return 0;
	}
	fprintf(fp,"%s\t%s\n",admin.name,admin.password);
	fclose(fp);
	return 1;
} 
//ͳ��ͼ��ݿ���� 
int bookSum(struct Node* headNode)
{
	int sum=0;
	struct Node* posNode=headNode->next;
 	while(posNode!=NULL)
 	{
 		sum+=posNode->data.Num;
 		posNode =posNode->next;
	 }
	 return sum;
 } 
//ͳ��ͼ��ݽ����� 
int bookBorrowSum(struct Node* headNode)
{
	int sum=0;
	struct Node* posNode=headNode->next;
 	while(posNode!=NULL)
 	{
 		sum+=posNode->data.borrow_Num;
 		posNode =posNode->next;
	 }
	 return sum;
 } 
//����ͼ�飬ǰ�巨���� 
void addBook(struct Node* headNode,struct book data)
{
	struct Node* newNode=createNode(data);
	newNode->next =headNode->next;
	headNode->next=newNode;
}
//��ʾͼ����Ϣ 
void printBook(struct Node* headNode)
{
	struct Node* pMove=headNode->next;
	printf("����\t����\t������\t���ʱ��  �����   ������\n");
	while(pMove!=NULL)
	{
		printf("%s\t%s\t%s\t%d\t%d\t%d\n",pMove->data.name,pMove->data.author, pMove->data.publisher ,pMove->data.time,pMove->data.Num,pMove->data.borrow_Num );
		pMove=pMove->next;
	}
}
//ɾ��ͼ��
void deletBook(struct Node* headNode,char *bookName)
{
	struct Node* posLeftNode=headNode;
	struct Node* posNode=headNode->next;
	while(posNode!=NULL&&strcmp(posNode->data.name,bookName))
	{
		posLeftNode=posNode;
		posNode=posLeftNode->next;
	 } 
	 if(posNode==NULL)
	 return;
	 else
	 {
	 	printf("ɾ���ɹ���\n"); 
	 	posLeftNode->next =posNode->next;
	 	free(posNode);
	 	posNode=NULL;
	 }
 } 
 
 //����ͼ��
 void sortBook(struct Node* headNode)
 {
 	for(struct Node* p=headNode->next ;p!=NULL;p=p->next )
 	{
 		for(struct Node* q=headNode->next;q->next!=NULL;q=q->next )
 		{
 			if(strcmp(q->data.name ,q->next->data.name)>0)//���������� 
 			{
 				struct book tempData=q->data;
 				q->data =q->next->data;
 				q->next->data =tempData; 
			 }//ð������ 
		 }
		 
	 }
 }
  
 //����ͼ��
 struct Node* searchBook(struct Node* headNode,char* bookName)
 {
 	struct Node* posNode=headNode->next;
 	while(posNode!=NULL&& strcmp(posNode->data.name ,bookName))
 	{
 		posNode =posNode->next;
	 }
	 return posNode;
 }
 
  //�޸�ͼ��
  void changeBook(struct Node* headNode, char* bookName, struct book newData)
  {
  	struct Node* posNode=headNode->next;
 	while(posNode!=NULL&& strcmp(posNode->data.name ,bookName))
 	{
 		posNode =posNode->next;
	 }
	 posNode->data =newData;
	 printf("�޸ĳɹ���\n");
   } 
   
 // �û�����ͼ��  
void user_borrowBook(struct Node* headNode, User &user,char* bookName ) 
{   
      
    // ����ͼ��ڵ� 
    struct Node* currentNode = headNode->next; 
	 while(currentNode!=NULL&& strcmp(currentNode->data.name ,bookName))
 	{
 		currentNode =currentNode->next;
	 }
    while (currentNode != NULL && currentNode->data.Num > 0) {  
        if (strcmp(currentNode->data.name, bookName) == 0) {  
            // �������  
            if (currentNode->data.Num > 0)
			 {  
                currentNode->data.Num--;  
                currentNode->data.borrow_Num++;  
                  
                // ��ӵ��û������б�  
                if (user.borrowCount < MAX_BORROW_BOOKS) 
				{   
                    user.borrowedBooks[user.borrowCount].data = currentNode->data;  
                    user.borrowCount++; 
					printf("%d",user.borrowCount); 
                } 
				else 
				{  
                    printf("���������Ѵﵽ���ޣ�\n");  
                }  
                return;  
            }  
            break;  
        }  
        currentNode = currentNode->next;  
    }  
    printf("ͼ�鲻���ڻ��治�㣡\n");  
}  
//����Ա�����鼮 
void admin_borrowBook(struct Node* headNode,char* bookName ) 
{   
      
    // ����ͼ��ڵ� 
    struct Node* currentNode = headNode->next; 
	 while(currentNode!=NULL&& strcmp(currentNode->data.name ,bookName))
 	{
 		currentNode =currentNode->next;
	 }
    while (currentNode != NULL && currentNode->data.Num > 0) {  
        if (strcmp(currentNode->data.name, bookName) == 0) {  
            // �������  
            if (currentNode->data.Num > 0)
			 {  
                currentNode->data.Num--;  
                currentNode->data.borrow_Num++;  
                return;  
            }  
            break;  
        }  
        currentNode = currentNode->next;  
    }  
    printf("ͼ�鲻���ڻ��治�㣡\n");  
}  


// �û��黹ͼ��  
void user_returnBook(struct Node* headNode, User &user, char* bookName)
 {  
    // �����û����ĵ�ͼ��  
    for (int i = 0; i < user.borrowCount; i++)
	 {  
        if (strcmp(user.borrowedBooks[i].data.name,bookName) == 0)
		 {   
            struct Node* currentNode = headNode->next; 
			 while(currentNode!=NULL&& strcmp(currentNode->data.name ,bookName))
 			{
 				currentNode =currentNode->next;
	 		}
            while (currentNode != NULL)
			 {  
                if (strcmp(currentNode->data.name, user.borrowedBooks[i].data.name) == 0) 
				{  
                    currentNode->data.Num++;  
                    currentNode->data.borrow_Num--;  
                      
                    // ���û������б����Ƴ�  
                    for (int j = i; j < user.borrowCount - 1; j++) 
					{  
                        user.borrowedBooks[j] = user.borrowedBooks[j + 1];  
                    }  
                    user.borrowCount--;  
                    return;  
                }  
                currentNode = currentNode->next;  
            }  
            break; // ����Ҳ����ڵ㣬��Ӧִ�к������� 
        }  
    }  
    printf("δ�ҵ����ļ�¼��ͼ����Ϣ����ȷ��\n");  
}  

// ����Ա�黹ͼ��  
void admin_returnBook(struct Node* headNode, char* bookName)
 {  
    struct Node* posNode=headNode->next;
 	while(posNode!=NULL&& strcmp(posNode->data.name ,bookName))
 	{
	 	
 		posNode =posNode->next;
 		posNode->data.Num++;  
        posNode->data.borrow_Num--; 
	 } 
}  

// �û��鿴������Ϣ  
void showBorrowedBooks(User user) {
    
    if (user.borrowCount == 0) {
        printf("����δ�����鼮\n");
    } else {
        printf("����ǰ���ĵ�ͼ�����£�\n");
        printf("����\t����\t������\n");
        for (int i = 0; i < user.borrowCount; i++) {
            printf("%s\t%s\t%s\n", user.borrowedBooks[i].data.name, user.borrowedBooks[i].data.author, user.borrowedBooks[i].data.publisher);
        }
    }
}

 //�ļ������ 
 void saveInfoToFile(const char* fileName,struct Node* headNode)
 {
 	FILE *fp=fopen(fileName,"w");
 	struct Node* pMove=headNode->next;
	 while(pMove!=NULL)
	 {
	 	fprintf(fp,"%s\t%s\t%s\t%d\t%d\t%d\n",pMove->data.name,pMove->data.author,pMove->data.publisher,pMove->data.time,pMove->data.Num,pMove->data.borrow_Num);
	 	pMove=pMove->next;
	  } 
 	fclose(fp);
} 

 //�ļ�������
 void readInfoFromFile(const char* fileName, struct Node* headNode)
 {
 	FILE* fp=fopen(fileName,"r");//����ļ�����ֱ�Ӷ� 
 	if(fp==NULL)
 	{
 		fp=fopen(fileName,"W+");//�����ھʹ���һ���ļ� 
	 }
	 struct book tempData;
	 while(fscanf(fp,"%s\t%s\t%s\t%d\t%d\t%d\n",tempData.name,tempData.author,tempData.publisher,&tempData.time,&tempData.Num,&tempData.borrow_Num )!=EOF)
	 {
	 	addBook(list,tempData);
	 }
 	fclose(fp);
  } 
  
  
void menu()
{
	printf("--------ͼ�����ϵͳ--------\n");
	printf("\t1.�û���¼\n");
	printf("\t2.����Ա��¼\n");
	printf("\t3.�û�ע��\n");
	printf("\t4.����Աע��\n");
	printf("\t0.�˳�\n"); 
	printf("----------------------------\n");
	printf("��������Ҫ���еĲ���\n");
 } //���˵�
 
 void Admin_menu()
 {
 	struct book tempBook;//��ʱ���� 
 	struct Node* result =NULL;//��ʱ����һ��ָ�� 
 	while(1)
	 {
 		printf("---------����Ա�˵�--------\n");
 		printf("\t1.����ͼ��\n");
 		printf("\t2.ɾ��ͼ��\n");
 		printf("\t3.�޸�ͼ��\n");
 		printf("\t4.��ѯͼ��\n");
 		printf("\t5.����ͼ��\n");
 		printf("\t6.ע���û�\n");
 		printf("\t7.����ͼ��\n");
 		printf("\t8.�黹ͼ��\n");
 		printf("\t9.ͼ��ͳ��\n");
 		printf("\t10.������ͳ��\n");
 		printf("\t11.��ʾͼ����Ϣ\n");
 		printf("\t0.�˳�\n");
 		printf("------------------\n");
 		printf("��������Ĳ�����\n"); 
 		int choice;
 		scanf("%d",&choice);
 		switch(choice)
 		{
 			case 1:
 				{
 					printf("�������鼮��Ϣ�����������ߣ������磬���ʱ�䣬���������������\n");
					scanf("%s%s%s%d%d%d",tempBook.name,tempBook.author,tempBook.publisher ,&tempBook.time ,&tempBook.Num ,&tempBook.borrow_Num ); 
					addBook(list,tempBook);
					tempBook.borrow_Num ++;
					tempBook.Num--;
					saveInfoToFile("bookinfo.txt",list);
					break;
				 }
			case 2:
				{
					printf("��������Ҫɾ��ͼ�������:\n");
					scanf("%s",tempBook.name);
					deletBook(list,tempBook.name);
					saveInfoToFile("bookinfo.txt",list);
					break;
				}
			case 3:
				{
					printf("��������Ҫ�޸ĵ�����:\n");
					 scanf("%s",tempBook.name );
					result=searchBook(list,tempBook.name);
					if(result==NULL)
					{
						printf("δ�ҵ������Ϣ��\n");
					 } 
					 else
					 {
					 	printf("����\t����\t������\t���ʱ��  �����   ������\n");
					 	printf("%s\t%s\t%s\t%d\t%d\t%d\n",result->data.name ,result->data.author ,result->data.publisher ,result->data.time ,result->data.Num ,result->data.borrow_Num);
					 	printf("���������޸ĺ��ͼ����Ϣ��\n");
					 	struct book newBook;
					 	scanf("%s%s%s%d%d%d",newBook.name,newBook.author ,newBook.publisher ,&newBook.time ,&newBook.Num ,&newBook.borrow_Num);
					 	changeBook(list, tempBook.name , newBook);
					 }
					 saveInfoToFile("bookinfo.txt",list);
					break;
				}
			case 4:
				{
					printf("��������Ҫ�����鼮���ƣ�\n");
					scanf("%s",tempBook.name); 
					result=searchBook(list,tempBook.name);
					if(result==NULL)
					{
						printf("δ�ҵ������Ϣ��\n");
					 } 
					 else
					 {
					 	printf("����\t����\t������\t���ʱ��  �����   ������\n");
					 	printf("%s\t%s\t%s\t%d\t%d\t%d\n",result->data.name ,result->data.author ,result->data.publisher ,result->data.time ,result->data.Num ,result->data.borrow_Num);
					 }
					break;
				}
			case 5:
				{
					sortBook(list);
					break;
				}
 			case 6:
				{
					if(registerUser(users,&userCount))
					{
						printf("ע��ɹ���\n");
					}
					else
					{
						printf("ע��ʧ�ܣ�\n");
					}
					break;
				}
			case 7:
				{
					printf("��������Ҫ���ĵ�������\n");
		 			scanf("%s",tempBook.name); 
					admin_borrowBook(list,tempBook.name );
					printf("���ĳɹ���\n");
		 			saveInfoToFile("bookinfo.txt",list);
					break;
				}
			case 8:
				{
					printf("��������Ҫ�黹��������\n");
		 			scanf("%s",tempBook.name); 
		 			admin_returnBook(list, tempBook.name);
		 			printf("�黹�ɹ���\n");
		 			saveInfoToFile("bookinfo.txt",list);
					break;
				}
			case 9:
				{
					printf("��ͼ����ڵ�ͼ��һ����%d��\n",bookSum(list));
					break;
				}
			case 10:
				{
					printf("��ͼ��ݽ�����һ����%d��\n",bookBorrowSum(list));
					break;
				}
			case 11:
				{
					printBook(list);
					break;
				}
			case 0:
				{
					printf("�˳��ɹ�\n"); 
					exit(0); 
					break;
				}
		 }
	 }
 	
 }
 
 //�û��˵�
void user_menu()
{
	struct book tempBook;//��ʱ���� 
	struct Node* result =NULL;//��ʱ����һ��ָ�� 
	while(1)
	{
		printf("-------�û��˵�---------\n");
		printf("\t1.ע�����˺�\n");
		printf("\t2.��ѯͼ��\n");
		printf("\t3.�����鼮\n");
		printf("\t4.�黹�鼮\n");
		printf("\t5.������ͳ��\n");
		printf("\t6.��ʾ�����鼮\n");
		printf("\t0.�˳�\n");
 		printf("------------------\n");
 		printf("��������Ĳ�����\n"); 
 		int choice;
 		scanf("%d",&choice);
 		switch(choice)
 		{
		 	case 1: 
		 	{
		 			if(registerUser(users,&userCount))
					{
						printf("ע��ɹ���\n");
					}
					else
					{
						printf("ע��ʧ�ܣ�\n");
					}
		 		break;
			 }
			 case 2: 
		 	{
		 			printf("��������Ҫ�����鼮���ƣ�\n");
					scanf("%s",tempBook.name); 
					result=searchBook(list,tempBook.name);
					if(result==NULL)
					{
						printf("δ�ҵ������Ϣ��\n");
					 } 
					 else
					 {
					 	printf("����\t����\t������\t���ʱ��  �����   ������\n");
					 	printf("%s\t%s\t%s\t%d\t%d\t%d\n",result->data.name ,result->data.author ,result->data.publisher ,result->data.time ,result->data.Num ,result->data.borrow_Num);
					 }
		 		break;
			 }
			 case 3: 
		 	{
		 		printf("��������Ҫ���ĵ�������\n");
		 		scanf("%s",tempBook.name); 
		 		user_borrowBook(list, users[currentUserIndex],tempBook.name );
		 		printf("���ĳɹ���\n");
		 		saveInfoToFile("bookinfo.txt",list);
		 		break;
			 }
			 case 4: 
		 	{
		 		printf("��������Ҫ�黹��������\n");
		 		scanf("%s",tempBook.name); 
		 		user_returnBook(list, users[currentUserIndex],tempBook.name);
		 		printf("�黹�ɹ���\n");
		 		saveInfoToFile("bookinfo.txt",list);
		 		break;
			 }
			 case 5: 
		 	{
		 		printf("���û��Ľ���ͼ������Ϊ��%d��\n",users[currentUserIndex].borrowCount);
		 		break;
			 }
			 case 6: 
		 	{
		 		showBorrowedBooks(users[currentUserIndex]);
		 		break;
			 }
			 case 0: 
		 	{
		 		printf("�˳��ɹ�\n");
		 		exit(0);
		 		break;
			 }
			 
		}
  }  
}
	
 void keydown()
 {
 	int choice;
 	scanf("%d",&choice);
 	switch(choice)
 	{
 		case 1:
 		{
 				printf("�������û�����\n");
				scanf("%s",username);
				printf("���������룺\n");
				scanf("%s",userpassword);
				if(user_login(users,userCount,username,userpassword))
				{
					printf("��¼�ɹ���\n");
					
					user_menu(); 
				}	
				else
				{
					printf("��½ʧ�ܣ�\n");
				}
				break;

		}
 		case 2:
		 {
 			printf("�������û�����\n");
			scanf("%s",adminname);
			printf("���������룺\n");
			scanf("%s",adminpassword);
			if(admin_login(admins,adminCount,adminname,adminpassword))
			{
				printf("��¼�ɹ���\n");
				Admin_menu() ;
			}	
			else
			{
				printf("��½ʧ�ܣ�\n");
			}
			break;
		 }
		 case 3:
		 {
		 	if(registerUser(users,&userCount))
				{
					printf("ע��ɹ���\n");
				}
				else
				{
					printf("ע��ʧ�ܣ�\n");
				}
				break;

		  } 
		  case 4:
		 {
		 	if(registerAdmin(admins,&adminCount))
				{
					printf("ע��ɹ���\n");
				}
				else
				{
					printf("ע��ʧ�ܣ�\n");
				}
				break;

		  } 
		case 0:
		{
			printf("�˳��ɹ�\n");
			exit(0);
		}
	 }
 }
 

int main()
{
	
	list= createHead();
	readInfoFromFile("bookinfo.txt",list);
	
	FILE *fp;
	if((fp=fopen("users.txt","r"))!=NULL)
	{
		while(fscanf(fp,"%s %s",users[userCount].name ,users[userCount].password )!=EOF)
		{
			userCount++;
		}
		fclose(fp);
	 } 
	 if((fp=fopen("admins.txt","r"))!=NULL)
	 {
	 	while(fscanf(fp,"%s %s",admins[adminCount].name,admins[adminCount].password)!=EOF)
	 	{
	 		adminCount++;
		 }
		fclose(fp);
	 }

	while(1)
	{
		menu();
		keydown();
	}
	
	return 0;	
} 
