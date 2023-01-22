
#include<stdio.h>

#include<stdlib.h>

#include<conio.h>

#include<time.h>

#include<windows.h>

#include<string.h>

#define KEY "7688399"

#define MAXSEAT 600

typedef struct booked_passenger
{
    char name[20];           //订票客户姓名

    int bookednum;           //该客户已订票数

    int grade;               //机舱等级

    struct booked_passenger *next;    //指向下一客户的

}booked;

typedef booked* linklist;

typedef struct after_passenger
{
    char name[20];             //等待客户姓名

    int afternum;              //该客户订票数

    struct after_passenger *next;     //指向下一客户的

}afterbook;

typedef afterbook* qnode;

typedef struct air
{
    char num[10];             //航班号

    long type;                //机型

    char start[10];           //起点站名

    char over[20];            //终点站名

    char starttime[20];       //起飞时间

    char arrivaltime[20];     //预计到达时间

    float price1;             //票价1

    float price2;             //票价2

    float price3;             //票价3

	int first_seat;           //一等座座位数

    int second_seat;          //二等座座位数

    int third_seat;           //三等座座位数

    linklist  book;           //指向已订票客户的头结点指针

    qnode  afterqueue;   //指向等待客户队列的指针

}flight;

struct air s[20];            //航班上线

int m=0;                     //航班数


int find();

void make();

void keys();

void content ();

void booking();

void save_flight();

void load_flight();

void input_message();

void read_message();

void place_search();

void time_search();

void cancelbook();

void add_flight();

void delete_flight();

void search_flight();

void read_passenger();

void replace_print(int i);

void make_starttime(int t);

void make_arrivaltime(int t);

void insertqueue(qnode head,char name[],int amount);

void insertlink(linklist head,int amount,char name[],int grade);





int main()//------------------------主函数-------------------------
{

    keys();

    system("date /t");

    system("time /t");

	system("color 0e");

	while(1)
	{
	    content();

	    int a;

        printf("\n请输入您的选项:");

	    scanf("%d",&a);printf("\n");

	    switch(a)
	    {
	        case 1: input_message();break;

			case 2: search_flight();break;

			case 3: booking();break;

			case 4: cancelbook();break;

			case 5: delete_flight();break;

	        case 6: read_message();break;

	        case 7: make();break;

	        case 8: add_flight();break;

	        case 9: read_passenger();break;

	        case 0: exit (1);

	        default:printf("error\n");exit(0);
        }
	}
	system("pause");  return 0;
}

void save_flight()//----------------------航班信息存入磁盘------------------------
{
	FILE *fp;

	int i;

	if((fp=fopen("air.txt","wb"))==NULL)
	{
		printf("文本不能打开，出错！\n");

		exit (0);
	}

	for(i=0;i<m;i++)

		fwrite(&s[i],sizeof(struct air),1,fp);

		fclose(fp);
}

void load_flight()//----------------------航班信息读入内存------------------------
{
	FILE *fp;

	int i=0;

	if((fp=fopen("air.txt","rb"))==NULL)
	{
		printf("文本不能打开，出错！\n");

		exit (0);
	}

	while(!feof(fp))
	{
		fread(&s[i],sizeof(struct air),1,fp);

		i++;
	}
	m=i-1;

	fclose(fp);
}

void input_message()
{
    int i=0,j;  char ch;

    while(1)
    {
        printf("请输入航班号：");

        scanf("%s",s[i].num);

        printf("请输入起点站：");

        scanf("%s",s[i].start);

        printf("请输入终点站：");

        scanf("%s",s[i].over);

        printf("请输入起飞时间：");

        scanf("%s",s[i].starttime);

        printf("请输入预计到达时间：");

        scanf("%s",s[i].arrivaltime);

        printf("请输入一等舱价格：");

        scanf("%f",&s[i].price1);

        printf("请输入二等舱价格：");

        scanf("%f",&s[i].price2);

        printf("请输入三等舱价格：");

        scanf("%f",&s[i].price3);

		printf("请输入一等舱座位：");

        scanf("%d",&s[i].first_seat);

        printf("请输入二等舱座位：");

        scanf("%d",&s[i].second_seat);

        printf("请输入三等舱座位：");

        scanf("%d",&s[i].third_seat);

        m++;  i++;

        getchar();

        printf("结束录入请输入y否则输入任意值\n");

        ch=getchar();

        if(ch=='y'||ch=='Y')break;
    }
    	srand((int)time(0));

		for(i=0;i<m;i++)

			s[i].type=(rand()%1000)+2015000;

		for(i=1;i<m;i++)

            for(j=0;j<m-1;j++)
				{
					if(s[j].type==s[i].type)

                    s[i].type=(rand()%1000)+2015000;
				}

        for(i=0;i<m;i++)
            {
                s[i].book=(linklist)malloc(sizeof(booked));

                s[i].book->next=NULL;

                s[i].afterqueue=(qnode)malloc(sizeof(afterbook));

                s[i].afterqueue->next=NULL;
            }

        save_flight();

		printf("录入完成!2秒后返回主菜单\n");

		Sleep(2000);

		system("cls");
}
void content ()
{
    printf("*****************************航空客运订票系统********************************\n");
    printf("\n");printf("\n");
    printf("\t\t1 录入航班信息\t\t");
    printf("2 航班查询\n");
    printf("\n");
    printf("\t\t3 订票功能\t");
    printf("\t4 退票功能\n");
    printf("\n");
    printf("\t\t5 取消航班\t\t");
    printf("6 浏览航班\n");
    printf("\n");
    printf("\t\t7 修改航班信息");
    printf("\t\t8 增加航班\n");
    printf("\n\t\t9 浏览客户信息\t\t");
    printf("0 退出系统\n");
    printf("\n");printf("\n");
    printf("*****************************************************************************\n");
}

void read_message()
{
    int i;     load_flight();

	for(i=0;i<m;i++)
	{
		printf("\n");

	    printf("航班号\t机型\t起点站\t终点站\t  起飞时间\t  \t预计到达时间\n");

		printf(" %s\t%ld\t%s\t%s\t%s\t%s\n",s[i].num,s[i].type,s[i].start,s[i].over,s[i].starttime,s[i].arrivaltime);

		printf("\n");

		printf("一等票\t二等票\t三等票\t   一等舱余座\t   二等舱余座\t   三等舱余座\n");

		printf("%5.2f\t%5.2f\t%5.2f\t\t%d\t\t%d\t\t%d\n",s[i].price1,s[i].price2,s[i].price3,s[i].first_seat,s[i].second_seat,s[i].third_seat);

		printf("\n");

		printf("*****************************************************************************\n");
	}

	    system("pause");  system("cls");
}

void replace_print(int i)
{
    printf("\n");

    printf("航班号\t机型\t起点站\t终点站\t  起飞时间\t  \t预计到达时间\n");

    printf(" %s\t%ld\t%s\t%s\t%s\t%s\n",s[i].num,s[i].type,s[i].start,s[i].over,s[i].starttime,s[i].arrivaltime);

    printf("\n");

    printf("一等票\t二等票\t三等票\t   一等舱余座\t   二等舱余座\t   三等舱余座\n");

    printf("%5.2f\t%5.2f\t%5.2f\t\t%d\t\t%d\t\t%d\n",s[i].price1,s[i].price2,s[i].price3,s[i].first_seat,s[i].second_seat,s[i].third_seat);

    printf("\n");

    printf("*****************************************************************************\n");
}

void search_flight()
{
	system("cls");

	int a;   load_flight();

	printf("*****************************************************************************\n");

	printf("\n");

	printf("\t1 按站点查询\t");

	printf("\t2 按出发时间查询\n");

	printf("\n");

	printf("*****************************************************************************\n");

	printf("请输入您的选项：");

	scanf("%d",&a);

	switch(a)
	{
	    case 1:place_search();break;

	    case 2:time_search();break;

	    default:printf("error\n");
	}

   system("cls");
}

void place_search()
{
	int i;  int flag=0;   char a[15];   char b[15];

	printf("请输入起点站：");

	scanf("%s",a);

	printf("请输入终点站：");

	scanf("%s",b);

	for(i=0;i<m;i++)
	{
		if(strcmp(s[i].start,a)==0)

			if(strcmp(s[i].over,b)==0)
			{
				flag=1;

				replace_print(i);
			}
	}

	if(!flag)

		printf("不存在\n");

	system("pause");
}

void time_search()
{
    int i=0;   char a[11];   char b[15];  int flag=0;

    printf("请输入要查询的日期按回车结束格式如（2015-06-14）：");

    scanf("%s",b);

    printf("您要查询的日期为：%s\n",b);

    for(i=0;i<m;i++)
    {
        strncpy(a,s[i].starttime,10);   a[10]='\0';

        if(strcmp(b,a)==0)
        {
			flag=1;

			replace_print(i);
        }
    }
    if(!flag)

        printf("不存在\n");

    system("pause");
}

void booking()
{
    load_flight();

    int rank,num,d;   char name[10],ch;

    d=find();//printf("%4d\t%d",s[d].afterqueue,d);

    printf("请输入您的姓名：");

    scanf("%s",name);

    printf("请输入你要选择的舱的等级输入数字（1,2,3）按回车结束：");

    scanf("%d",&rank);

    printf("请输入您要订票的数量:");

    scanf("%d",&num);

	switch(rank)
	{
	case 1:if(s[d].first_seat>=num)
		   {
			   s[d].first_seat-=num;save_flight();

			   insertlink(s[d].book,num,name,rank);

			   printf("订票成功！\n");
		   }

		   else
		   {
		       printf("票数不够!输入y则进入排队等候;否则退出系统\n");

               getchar(); ch=getchar();

               if(ch=='y'||ch=='Y')
               {
                   insertqueue(s[d].afterqueue,name,num);

                   printf("排队成功\n");
               }
               else

                  exit(1);

            }
            break;

	case 2:if(s[d].second_seat>=num)
		   {
			   s[d].second_seat-=num;save_flight();

			   insertlink(s[d].book,num,name,rank);

			   printf("订票成功！\n");
		   }

		   else
            {
			   printf("票数不够!输入y则进入排队等候;否则退出系统\n");

               getchar(); ch=getchar();

               if(ch=='y'||ch=='Y')
               {
                   insertqueue(s[d].afterqueue,name,num);

                   printf("排队成功\n");
               }
               else

                  exit(1);
            }
            break;

	case 3:if(s[d].third_seat>=num)
		   {
			   s[d].third_seat-=num;save_flight();

			   insertlink(s[d].book,num,name,rank);

		       printf("订票成功！\n");
		   }
		   else
            {
              printf("票数不够!输入y则进入排队等候;否则退出系统\n");

               getchar(); ch=getchar();

               if(ch=='y'||ch=='Y')
               {
                   insertqueue(s[d].afterqueue,name,num);

                   printf("排队成功\n");
               }
               else

                  exit(1);
            }
            break;

	default:printf("error");
	}

	system("pause");

	system("cls");
}

void insertlink(linklist head,int amount,char name[],int grade)
{
    static linklist p1,new1;

    new1=(linklist)malloc(sizeof(booked));

    strcpy(new1->name,name);

    new1->bookednum=amount;

    new1->grade=grade;

    if(head->next==NULL)

        head->next=new1;

    else

        p1->next=new1;

    p1=new1;

    new1->next=NULL;
}

void insertqueue(qnode head,char name[],int amount)
{
    static qnode new2,p1;

    new2=(qnode)malloc(sizeof(afterbook));

    strcpy(new2->name,name);

    new2->afternum=amount;

    if(head->next==NULL)

        head->next=new2;

    else

        p1->next=new2;

    p1=new2;

    new2->next=NULL;
}

void read_passenger()
{
    load_flight();

    int i,flag=0;   char a[15];

    printf("请输入要查询的航班号（例如1001）：");

    scanf("%s",a);

    printf("\t姓名\t票数\t等级\n");

    for(i=0;i<m;i++)
    {
        if(strcmp(a,s[i].num)==0)
        {
            flag=1;

            break;
        }
    }
    if(!flag)
    {
        printf("不存在该航班\n");

        exit(1);
    }
    linklist p=s[i].book->next;

	while(p!=NULL)
    {
       printf("\t%s\t%d\t%d\n",p->name,p->bookednum,p->grade);

       p=p->next;
    }

    system("pause"); system("cls");
}


void cancelbook()
{
	load_flight();   read_passenger();

	int i,j,n,flag=0,flag1=0;  char a[15],b[15];

    printf("请输入您的的航班号（例如1001）：");

    scanf("%s",a);

    printf("请输入您的姓名：");

    scanf("%s",b);

    printf("请输入您的舱位等级：");

    scanf("%d",&n);

    for(i=0;i<m;i++)

        if(strcmp(a,s[i].num)==0)

           {flag=1;break;}

    if(i==m)  {printf("不存在！"); exit(1);}

    if(s[i].book==NULL)
	{
		printf("不存在该客户！\n"); exit(1);
	}

    static linklist p,pre,new1;   pre=s[i].book;   p=s[i].book->next;

    static qnode p1,pre1,temp;

    switch(n)
	{
	    case 1:s[i].first_seat+=s[i].book->next->bookednum;

		       save_flight(); break;

	    case 2:s[i].second_seat+=s[i].book->next->bookednum;

		       save_flight(); break;

	    case 3:s[i].third_seat+=s[i].book->next->bookednum;

		       save_flight(); break;

        default:printf("error");exit(1);
	}

			while(p)
			{
			    if(strcmp(p->name,b)==0)

                    {flag1=1;break;}

                pre=p;

                p=p->next;
			}
			if(p)
			{
			    pre->next=p->next;

			    free(p);   printf("退票成功\n");
			}

	if(!flag)

    {printf("不存在该航班\n");exit(1);}

    if(!flag1)

    {printf("不存在该航班\n");exit(1);}

     p1=s[i].afterqueue->next; pre1=s[i].afterqueue;

     printf("%s\t%d\t%d\t%d",p1->name,p1->afternum,p1,n);system("pause");

    if(!p1)

    {printf("该航班无等待顾客！");}

    else
    {
        temp=s[i].afterqueue->next;

        pre1->next=p1->next;

        //free(p1);

         new1=(linklist)malloc(sizeof(booked));

         strcpy(new1->name,temp->name);

         new1->bookednum=temp->afternum;

         new1->grade=n;

         new1->next=pre->next;

         pre->next=new1;

         if(n==1)

            {s[i].first_seat-=new1->bookednum;save_flight();}

         else if(n==2)

            {s[i].second_seat-=new1->bookednum;save_flight();}

         else

            {s[i].third_seat-=new1->bookednum;save_flight();}

            printf("排队顾客已成功订票\n");

    }

    system("pause");  system("cls");
}
int find()
{
    int c[20],i,j=0; int flag1=0,flag2=0,flag3=0;

    char a[15],b[15],d[20];  char t[15];

    printf("请输入您的出发日期按回车结束格式如（2015-06-14）：");

    scanf("%s",a);

    printf("请输入您的终点站：");

    scanf("%s",b);

    for(i=0;i<m;i++)
    {
        strncpy(t,s[i].starttime,10);  t[10]='\0';

        if(strcmp(t,a)==0)
        {
            flag1=1;

            if(strcmp(b,s[i].over)==0)
            {
                flag2=1;

                c[j]=i;  j++;

                replace_print(i);
            }
        }
    }
    if(!flag1)
    {
        system("cls");

        printf("不存在该航班请重新输入\n");

        booking();
    }
    if(!flag2)
    {
        system("cls");

        printf("不存在该航班请重新输入\n");

        booking();
    }

    printf("请输入您选择的航班的航班号：");

    scanf("%s",d);  i=0;

    while(i<j)
    {
        if(strcmp(d,s[c[i]].num)==0)
        {
            system("cls");flag3=1;

            printf("您所选择的航班为：");

            printf("\n");

            replace_print(c[i]);

            return c[i];
        }
        i++;
    }
    if(!flag3)
    {
        system("cls");

        printf("不存在该航班请重新输入\n");

        booking();
    }
}

void add_flight()//-------------------添加航班信息---------------------
{
    FILE *fp;

	int i=0;

	if((fp=fopen("air.txt","ab"))==NULL)
	{
		printf("文本不能打开，出错！\n");

		exit (0);
	}
	  printf("请输入航班号：");

        scanf("%s",s[m].num);

        printf("请输入起点站：");

        scanf("%s",s[m].start);

        printf("请输入终点站：");

        scanf("%s",s[m].over);

        printf("请输入起飞时间：");

        scanf("%s",s[m].starttime);

        printf("请输入预计到达时间：");

        scanf("%s",s[m].arrivaltime);

        printf("请输入一等舱价格：");

        scanf("%f",&s[m].price1);

        printf("请输入二等舱价格：");

        scanf("%f",&s[m].price2);

        printf("请输入三等舱价格：");

        scanf("%f",&s[m].price3);

		printf("请输入一等舱座位：");

        scanf("%d",&s[m].first_seat);

        printf("请输入二等舱座位：");

        scanf("%d",&s[m].second_seat);

        printf("请输入三等舱座位：");

        scanf("%d",&s[m].third_seat);

        getchar();

        srand((int)time(0));

        s[m].type=(rand()%1000)+2015000;

        for(i=m;i<=m;i++)

		fwrite(&s[i],sizeof(struct air),1,fp);

		fclose(fp);m++;

		printf("\n已成功添加该航班！\n");

        system("pause");  system("cls");
}

void make()
{
    system("cls");

    load_flight();

    int a,i,flag=0,t; char b[10];

    printf("请输入要修改的航班的航班号：");

    scanf("%s",b);

    for(i=0;i<m;i++)
    {
        if(strcmp(s[i].num,b)==0)
        {
            flag=1;

            t=i;
        }
    }
    if(!flag)
    {
        printf("不存在该航班\n");

        exit(1);
    }

    printf("\n******************************************\n");  printf("\n");

    printf("\t1 修改出发时间\n");  printf("\n");

    printf("\t2 修改预计到达时间\n");  printf("\n");

    printf("******************************************\n");  printf("\n");

    printf("请输入您的选项：");

    scanf("%d",&a);

    switch(a)
    {
        case 1:make_starttime(t);break;

        case 2:make_arrivaltime(t);break;

        default:printf("error\n");
    }

    system("pause");   system("cls");

}

void make_starttime(int t)
{
    printf("请输入新的起飞时间：");

    scanf("%s",s[t].starttime);

    save_flight();

    printf("修改成功\n");
}

void make_arrivaltime(int t)
{
     printf("请输入新的预计到达时间：");

    scanf("%s",s[t].arrivaltime);

    save_flight();

    printf("修改成功\n");
}

void delete_flight()
{
    load_flight();

    char a[10];  int i,j;

    printf("请输入该航班的航班号：");

    scanf("%s",a);

    for(i=0;i<m;i++)

        if(strcmp(s[i].num,a)==0)

            break;

    if(i==m)
    {
        printf("不存在该航班\n");

        exit(1);
    }

    for(j=i;j<m;j++) s[j]=s[j+1];

    m--;

    save_flight();

    printf("已成功取消该航班\n");

    system("pause");  system("cls");
}


void keys()//----------------------------------密码---------------------
 {
     printf("\n*******************************************************************************\n\n");

     printf("\n\t\t\t欢迎使用航空管理系统\t\n\n");

     printf("\n*******************************************************************************\n\n");

     char a[20],ch;   int i=0,j;

     for(j=0;j<3;j++)
     {
         printf("\n\t请输入密码 : ");

 	     ch =getch();
 	while((ch & 0xff) != 13)
 	{
 	    if ((ch == '\b'))
 		{
 		    printf("%c %c",ch,ch);

 		    i--;
        }
        else
        {
            printf("*");;

            a[i] = ch;  i++;
        }
    	ch =getch();
    }
    	a[i]='\0';

    	if (0==strcmp(KEY,a))
    	{
    	    printf("\n\n\t\t密码输入正确,两秒后进入系统!!!\n");

    	    Sleep(2000);   system("cls");

    	    break;
        }

        else
        {
            printf("\n\n\t\t密码输入错误!!!\n");

            i=0;
        }
     }
     if(j==3)

     exit(0);
}


