#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_BORROW_BOOKS 10 
struct book
{
	char name[20];//书名 
	char author[20];//作者 
	char publisher[20];//出版社 
	int time;//入库时间 
	int Num;//库存量
	int borrow_Num;//借阅数 
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

//创建节点 
struct Node* createNode(struct book data)
{
	struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
	newNode->data =data;
	newNode->next=NULL;
	return newNode;
}

//借阅的书籍 
struct BorrowedBook
 {  
    struct book data;  
};  

//定义用户
typedef struct
{
	char name[20];
	char password[20];
	struct BorrowedBook borrowedBooks[MAX_BORROW_BOOKS];  //每人最多借10本书 
    int borrowCount; // 用户当前借阅的图书数量  
 } User;
 
//定义管理员 
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
//用户登录 
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
  
//管理员登录 
  
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
//用户注册
int registerUser(User users[],int* userCount )
{
	User user;
	printf("请输入用户名：\n");
	scanf("%s",&user.name);
	printf("请输入密码：\n");
	scanf("%s",&user.password);
	users[*userCount]=user;
	(*userCount)++;
	FILE* fp;
	if((fp=fopen("users.txt","a"))==NULL)
	{
		printf("文件打开失败\n");
		return 0;
	}
	fprintf(fp,"%s\t%s\n",user.name,user.password);
	fclose(fp);
	return 1;
} 
//管理员注册
 int registerAdmin(Admin admins[],int* adminCount )
{
	Admin admin;
	printf("请输入用户名：\n");
	scanf("%s",&admin.name);
	printf("请输入密码：\n");
	scanf("%s",&admin.password);
	admins[*adminCount]=admin;
	(*adminCount)++;
	FILE* fp;
	if((fp=fopen("admins.txt","a"))==NULL)
	{
		printf("文件打开失败\n");
		return 0;
	}
	fprintf(fp,"%s\t%s\n",admin.name,admin.password);
	fclose(fp);
	return 1;
} 
//统计图书馆库存量 
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
//统计图书馆借阅量 
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
//增加图书，前插法插入 
void addBook(struct Node* headNode,struct book data)
{
	struct Node* newNode=createNode(data);
	newNode->next =headNode->next;
	headNode->next=newNode;
}
//显示图书信息 
void printBook(struct Node* headNode)
{
	struct Node* pMove=headNode->next;
	printf("书名\t作者\t出版社\t入库时间  库存量   借阅量\n");
	while(pMove!=NULL)
	{
		printf("%s\t%s\t%s\t%d\t%d\t%d\n",pMove->data.name,pMove->data.author, pMove->data.publisher ,pMove->data.time,pMove->data.Num,pMove->data.borrow_Num );
		pMove=pMove->next;
	}
}
//删除图书
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
	 	printf("删除成功！\n"); 
	 	posLeftNode->next =posNode->next;
	 	free(posNode);
	 	posNode=NULL;
	 }
 } 
 
 //排序图书
 void sortBook(struct Node* headNode)
 {
 	for(struct Node* p=headNode->next ;p!=NULL;p=p->next )
 	{
 		for(struct Node* q=headNode->next;q->next!=NULL;q=q->next )
 		{
 			if(strcmp(q->data.name ,q->next->data.name)>0)//按姓名排序 
 			{
 				struct book tempData=q->data;
 				q->data =q->next->data;
 				q->next->data =tempData; 
			 }//冒泡排序 
		 }
		 
	 }
 }
  
 //查找图书
 struct Node* searchBook(struct Node* headNode,char* bookName)
 {
 	struct Node* posNode=headNode->next;
 	while(posNode!=NULL&& strcmp(posNode->data.name ,bookName))
 	{
 		posNode =posNode->next;
	 }
	 return posNode;
 }
 
  //修改图书
  void changeBook(struct Node* headNode, char* bookName, struct book newData)
  {
  	struct Node* posNode=headNode->next;
 	while(posNode!=NULL&& strcmp(posNode->data.name ,bookName))
 	{
 		posNode =posNode->next;
	 }
	 posNode->data =newData;
	 printf("修改成功！\n");
   } 
   
 // 用户借阅图书  
void user_borrowBook(struct Node* headNode, User &user,char* bookName ) 
{   
      
    // 查找图书节点 
    struct Node* currentNode = headNode->next; 
	 while(currentNode!=NULL&& strcmp(currentNode->data.name ,bookName))
 	{
 		currentNode =currentNode->next;
	 }
    while (currentNode != NULL && currentNode->data.Num > 0) {  
        if (strcmp(currentNode->data.name, bookName) == 0) {  
            // 检查库存量  
            if (currentNode->data.Num > 0)
			 {  
                currentNode->data.Num--;  
                currentNode->data.borrow_Num++;  
                  
                // 添加到用户借阅列表  
                if (user.borrowCount < MAX_BORROW_BOOKS) 
				{   
                    user.borrowedBooks[user.borrowCount].data = currentNode->data;  
                    user.borrowCount++; 
					printf("%d",user.borrowCount); 
                } 
				else 
				{  
                    printf("借阅数量已达到上限！\n");  
                }  
                return;  
            }  
            break;  
        }  
        currentNode = currentNode->next;  
    }  
    printf("图书不存在或库存不足！\n");  
}  
//管理员借阅书籍 
void admin_borrowBook(struct Node* headNode,char* bookName ) 
{   
      
    // 查找图书节点 
    struct Node* currentNode = headNode->next; 
	 while(currentNode!=NULL&& strcmp(currentNode->data.name ,bookName))
 	{
 		currentNode =currentNode->next;
	 }
    while (currentNode != NULL && currentNode->data.Num > 0) {  
        if (strcmp(currentNode->data.name, bookName) == 0) {  
            // 检查库存量  
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
    printf("图书不存在或库存不足！\n");  
}  


// 用户归还图书  
void user_returnBook(struct Node* headNode, User &user, char* bookName)
 {  
    // 查找用户借阅的图书  
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
                      
                    // 从用户借阅列表中移除  
                    for (int j = i; j < user.borrowCount - 1; j++) 
					{  
                        user.borrowedBooks[j] = user.borrowedBooks[j + 1];  
                    }  
                    user.borrowCount--;  
                    return;  
                }  
                currentNode = currentNode->next;  
            }  
            break; // 如果找不到节点，则不应执行后续代码 
        }  
    }  
    printf("未找到借阅记录或图书信息不正确！\n");  
}  

// 管理员归还图书  
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

// 用户查看借阅信息  
void showBorrowedBooks(User user) {
    
    if (user.borrowCount == 0) {
        printf("您还未借阅书籍\n");
    } else {
        printf("您当前借阅的图书如下：\n");
        printf("书名\t作者\t出版社\n");
        for (int i = 0; i < user.borrowCount; i++) {
            printf("%s\t%s\t%s\n", user.borrowedBooks[i].data.name, user.borrowedBooks[i].data.author, user.borrowedBooks[i].data.publisher);
        }
    }
}

 //文件存操作 
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

 //文件读操作
 void readInfoFromFile(const char* fileName, struct Node* headNode)
 {
 	FILE* fp=fopen(fileName,"r");//如果文件存在直接读 
 	if(fp==NULL)
 	{
 		fp=fopen(fileName,"W+");//不存在就创建一个文件 
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
	printf("--------图书管理系统--------\n");
	printf("\t1.用户登录\n");
	printf("\t2.管理员登录\n");
	printf("\t3.用户注册\n");
	printf("\t4.管理员注册\n");
	printf("\t0.退出\n"); 
	printf("----------------------------\n");
	printf("请输入你要进行的操作\n");
 } //主菜单
 
 void Admin_menu()
 {
 	struct book tempBook;//临时储存 
 	struct Node* result =NULL;//临时储存一个指针 
 	while(1)
	 {
 		printf("---------管理员菜单--------\n");
 		printf("\t1.增加图书\n");
 		printf("\t2.删除图书\n");
 		printf("\t3.修改图书\n");
 		printf("\t4.查询图书\n");
 		printf("\t5.排序图书\n");
 		printf("\t6.注册用户\n");
 		printf("\t7.借阅图书\n");
 		printf("\t8.归还图书\n");
 		printf("\t9.图书统计\n");
 		printf("\t10.借阅量统计\n");
 		printf("\t11.显示图书信息\n");
 		printf("\t0.退出\n");
 		printf("------------------\n");
 		printf("请输入你的操作：\n"); 
 		int choice;
 		scanf("%d",&choice);
 		switch(choice)
 		{
 			case 1:
 				{
 					printf("请输入书籍信息（书名，作者，出版社，入库时间，库存量，借阅数）\n");
					scanf("%s%s%s%d%d%d",tempBook.name,tempBook.author,tempBook.publisher ,&tempBook.time ,&tempBook.Num ,&tempBook.borrow_Num ); 
					addBook(list,tempBook);
					tempBook.borrow_Num ++;
					tempBook.Num--;
					saveInfoToFile("bookinfo.txt",list);
					break;
				 }
			case 2:
				{
					printf("请输入你要删除图书的书名:\n");
					scanf("%s",tempBook.name);
					deletBook(list,tempBook.name);
					saveInfoToFile("bookinfo.txt",list);
					break;
				}
			case 3:
				{
					printf("请输入你要修改的书名:\n");
					 scanf("%s",tempBook.name );
					result=searchBook(list,tempBook.name);
					if(result==NULL)
					{
						printf("未找到相关信息！\n");
					 } 
					 else
					 {
					 	printf("书名\t作者\t出版社\t入库时间  库存量   借阅量\n");
					 	printf("%s\t%s\t%s\t%d\t%d\t%d\n",result->data.name ,result->data.author ,result->data.publisher ,result->data.time ,result->data.Num ,result->data.borrow_Num);
					 	printf("请输入你修改后的图书信息：\n");
					 	struct book newBook;
					 	scanf("%s%s%s%d%d%d",newBook.name,newBook.author ,newBook.publisher ,&newBook.time ,&newBook.Num ,&newBook.borrow_Num);
					 	changeBook(list, tempBook.name , newBook);
					 }
					 saveInfoToFile("bookinfo.txt",list);
					break;
				}
			case 4:
				{
					printf("请输入你要查找书籍名称：\n");
					scanf("%s",tempBook.name); 
					result=searchBook(list,tempBook.name);
					if(result==NULL)
					{
						printf("未找到相关信息！\n");
					 } 
					 else
					 {
					 	printf("书名\t作者\t出版社\t入库时间  库存量   借阅量\n");
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
						printf("注册成功！\n");
					}
					else
					{
						printf("注册失败！\n");
					}
					break;
				}
			case 7:
				{
					printf("请输入你要借阅的书名：\n");
		 			scanf("%s",tempBook.name); 
					admin_borrowBook(list,tempBook.name );
					printf("借阅成功！\n");
		 			saveInfoToFile("bookinfo.txt",list);
					break;
				}
			case 8:
				{
					printf("请输入你要归还的书名：\n");
		 			scanf("%s",tempBook.name); 
		 			admin_returnBook(list, tempBook.name);
		 			printf("归还成功！\n");
		 			saveInfoToFile("bookinfo.txt",list);
					break;
				}
			case 9:
				{
					printf("该图书馆内的图书一共：%d本\n",bookSum(list));
					break;
				}
			case 10:
				{
					printf("该图书馆借阅量一共：%d本\n",bookBorrowSum(list));
					break;
				}
			case 11:
				{
					printBook(list);
					break;
				}
			case 0:
				{
					printf("退出成功\n"); 
					exit(0); 
					break;
				}
		 }
	 }
 	
 }
 
 //用户菜单
void user_menu()
{
	struct book tempBook;//临时储存 
	struct Node* result =NULL;//临时储存一个指针 
	while(1)
	{
		printf("-------用户菜单---------\n");
		printf("\t1.注册新账号\n");
		printf("\t2.查询图书\n");
		printf("\t3.借阅书籍\n");
		printf("\t4.归还书籍\n");
		printf("\t5.借阅量统计\n");
		printf("\t6.显示所借书籍\n");
		printf("\t0.退出\n");
 		printf("------------------\n");
 		printf("请输入你的操作：\n"); 
 		int choice;
 		scanf("%d",&choice);
 		switch(choice)
 		{
		 	case 1: 
		 	{
		 			if(registerUser(users,&userCount))
					{
						printf("注册成功！\n");
					}
					else
					{
						printf("注册失败！\n");
					}
		 		break;
			 }
			 case 2: 
		 	{
		 			printf("请输入你要查找书籍名称：\n");
					scanf("%s",tempBook.name); 
					result=searchBook(list,tempBook.name);
					if(result==NULL)
					{
						printf("未找到相关信息！\n");
					 } 
					 else
					 {
					 	printf("书名\t作者\t出版社\t入库时间  库存量   借阅量\n");
					 	printf("%s\t%s\t%s\t%d\t%d\t%d\n",result->data.name ,result->data.author ,result->data.publisher ,result->data.time ,result->data.Num ,result->data.borrow_Num);
					 }
		 		break;
			 }
			 case 3: 
		 	{
		 		printf("请输入你要借阅的书名：\n");
		 		scanf("%s",tempBook.name); 
		 		user_borrowBook(list, users[currentUserIndex],tempBook.name );
		 		printf("借阅成功！\n");
		 		saveInfoToFile("bookinfo.txt",list);
		 		break;
			 }
			 case 4: 
		 	{
		 		printf("请输入你要归还的书名：\n");
		 		scanf("%s",tempBook.name); 
		 		user_returnBook(list, users[currentUserIndex],tempBook.name);
		 		printf("归还成功！\n");
		 		saveInfoToFile("bookinfo.txt",list);
		 		break;
			 }
			 case 5: 
		 	{
		 		printf("该用户的借阅图书数量为：%d本\n",users[currentUserIndex].borrowCount);
		 		break;
			 }
			 case 6: 
		 	{
		 		showBorrowedBooks(users[currentUserIndex]);
		 		break;
			 }
			 case 0: 
		 	{
		 		printf("退出成功\n");
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
 				printf("请输入用户名：\n");
				scanf("%s",username);
				printf("请输入密码：\n");
				scanf("%s",userpassword);
				if(user_login(users,userCount,username,userpassword))
				{
					printf("登录成功！\n");
					
					user_menu(); 
				}	
				else
				{
					printf("登陆失败！\n");
				}
				break;

		}
 		case 2:
		 {
 			printf("请输入用户名：\n");
			scanf("%s",adminname);
			printf("请输入密码：\n");
			scanf("%s",adminpassword);
			if(admin_login(admins,adminCount,adminname,adminpassword))
			{
				printf("登录成功！\n");
				Admin_menu() ;
			}	
			else
			{
				printf("登陆失败！\n");
			}
			break;
		 }
		 case 3:
		 {
		 	if(registerUser(users,&userCount))
				{
					printf("注册成功！\n");
				}
				else
				{
					printf("注册失败！\n");
				}
				break;

		  } 
		  case 4:
		 {
		 	if(registerAdmin(admins,&adminCount))
				{
					printf("注册成功！\n");
				}
				else
				{
					printf("注册失败！\n");
				}
				break;

		  } 
		case 0:
		{
			printf("退出成功\n");
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
