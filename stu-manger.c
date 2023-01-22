

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include <conio.h>
#define KEY "7688399"
#define SIZE 500
void save();
void input_message();
void content();
void read_message();
void serch();
void serch_id();
void serch_name();
void load();
void sort_count();
void sort_subject();
void science_sort();
void math_sort();
void english_sort();
void count_subject();
void science_count();
void math_count();
void english_count();
void delete_make();
void delete1();
void id_delete();
void name_delete();
void make();
void make_science(int c);
void make_math(int c);
void make_english(int c);
void add_message();
void keys();
struct student
{
	char name[10];
	int num;
	char sex;
	int score[3];
	float ave;
	float sum;
};

struct student stud[SIZE];
int m=0;

void main()//-------------------主函数-------------------------
{
     keys();

	system("color 0e");

	while(1)
	{
	content();
	int a;
	printf("请输入您的选项:");
	scanf("%d",&a);

	switch(a)
	{
	case 1: input_message();break;
	case 2: read_message();break;
	case 3: serch();break;
	case 4: sort_count();break;
	case 5: delete_make();break;
	case 6: add_message();break;
	case 7: exit (0);
	default:printf("error\n");exit(0);
	}

	}
	system("pause");
}


void save()//----------------------信息存入磁盘------------------------
{
	FILE *fp;
	int i;

	if((fp=fopen("stu.dat","wb"))==NULL)
	{
		printf("文本不能打开，出错！\n");
		exit (0);
	}

	for(i=0;i<m;i++)
		fwrite(&stud[i],sizeof(struct student),1,fp);

		fclose(fp);
}

void input_message()//------------------------录入信息------------------------
{
	int i,j;
	char ch;

	for(i=0;;i++)
		{
		printf("请输入学生姓名:");
        scanf("%s",stud[i].name);
        getchar();

        printf("请输入学生性别:");
        scanf("%c",&stud[i].sex);
        getchar();

        printf("请输入计算机成绩:");
        scanf("%d",&stud[i].score[0]);
        getchar();

        printf("请输入数学成绩:");
        scanf("%d",&stud[i].score[1]);
        getchar();

        printf("请输入英语成绩:");
        scanf("%d",&stud[i].score[2]);
        getchar();

			m++;
            for(j=0;j<m;j++)
		    stud[i].sum=0;
                stud[i].sum=stud[i].score[0]+stud[i].score[1]+stud[i].score[2];
			    stud[i].ave=stud[i].sum/3;

			printf("结束录入请输入y否则输入任意值\n");
			ch=getchar();
			if(ch=='y'||ch=='Y')
				break;
        }
		srand((int)time(0));
		for(i=0;i<m;i++)

		{
			stud[i].num=(rand()%1000)+2014000;
		}

		for(i=1;i<m;i++)

		{

	     for(j=0;j<m-1;j++)
				{
					if(stud[j].num==stud[i].num)
						stud[i].num=(rand()%1000)+2014000;
				}
        }

        save();
		printf("录入完成!2秒后返回主菜单\n");
		Sleep(2000);
		system("cls");
}
void content()//----------------------------输出目录---------------------------------
{
	printf("=================================================================\n");
	printf("                                                               \n");
	printf("**********************学生成绩管理系统***************************\n");
	printf("                                                               \n");
	printf("           1 学生信息录入  ");
	printf("  2 学生信息浏览\n");
	printf("                                                               \n");
	printf("           3 学生信息查询   ");
    printf(" 4 成绩排序与统计\n");
	printf("                                                               \n");
	printf("           5 学生信息删除与修改");
	printf("    6 添加学生信息\n");
	printf("                                                               \n");
	printf("           7 退出\n");
	printf("                                                               \n");
	printf("==================================================================\n");

}
void read_message()//-----------------------浏览信息------------------------------
{

		int i;
		load();

	printf("姓名\t学号\t性别\tScience\tMath\tEnglish\t总分\t平均分\n");
	for(i=0;i<m;i++)
	{
		printf("%s\t%5d\t %c\t%3d\t%3d\t%3d\t%6.2f%\t%6.2f\n",stud[i].name,stud[i].num,stud[i].sex,stud[i].score[0],stud[i].score[1],stud[i].score[2],stud[i].sum,stud[i].ave);
	}

	    system("pause");
		system("cls");
}

void serch()//--------------------查询功能-----------------------------
{
    system("cls");
	printf("\n------查询功能--------\n");
	printf("\n1 按学号查询\n");
	printf("\n");
	printf("2 按姓名查询\n");
	printf("\n----------------------\n");
	load();
	char ch;

	int a;
	printf("请输入您的选项：");
	scanf("%d",&a);

	switch(a)
	{
	case 1:serch_id();break;
	case 2:serch_name();break;
	default:printf("error\n");
	}

	printf("返回上级菜单请输入y返回主菜单输入任意键\n");
	getchar();
	ch=getchar();
	if(ch=='y'||ch=='Y')
		serch();
	system("pause");
	system("cls");
}
void serch_id()//-----------------------------按学号查找---------------------------------
{

	int i;
	long a;

	printf("请输入您要查找的学号:");
	scanf("%ld",&a);
	printf("\n");

	for(i=0;i<m;i++)
	{
		if(a==stud[i].num)
		{
		    printf("姓名\t学号\t性别\tScience\tMath\tEnglish\t总分\t平均分\n");
            printf("\n");
		printf("%s\t%5d\t %c\t%3d\t%3d\t%3d\t%6.2f%\t%6.2f\n",stud[i].name,stud[i].num,stud[i].sex,stud[i].score[0],stud[i].score[1],stud[i].score[2],stud[i].sum,stud[i].ave);
		break;
		}
    }
	if(i==m)
	{
		printf("不存在\n");
	}
}
void serch_name()//-------------------------------按姓名查找-----------------------------------
{
		int i,flag=0;
		char a[10];

	printf("请输入您要查找的学生姓名:");
	scanf("%s",a);
	printf("姓名\t学号\t性别\tScience\tMath\tEnglish\t总分\t平均分\n");

	for(i=0;i<m;i++)
	{
		if(strcmp(a,stud[i].name)==0)
		{
			flag=1;
			printf("\n");

			printf("%s\t%5d\t %c\t%3d\t%3d\t%3d\t%6.2f%\t%6.2f\n",stud[i].name,stud[i].num,stud[i].sex,stud[i].score[0],stud[i].score[1],stud[i].score[2],stud[i].sum,stud[i].ave);
		}
    }

			if(!flag)
		{
			printf("不存在\n");
		}
}
void load()//-----------------------------信息读入内存--------------------------------
{
	FILE *fp;
	int i=0;

	if((fp=fopen("stu.dat","rb"))==NULL)
	{
		printf("文本不能打开，出错！\n");
		exit (0);
	}

	while(!feof(fp))
	{
		fread(&stud[i],sizeof(struct student),1,fp);
		i++;
	}

	m=i-1;
	fclose(fp);
}
void sort_count()//---------------------------排序与统计功能-------------------------
{
    system("cls");
	load();
	printf("\n");
	printf("-------------排序与统计功能------------------  \n");
	printf("\n");
	printf("      1 按照指定的要求对学生记录进行排序\n");
	printf("\n");
	printf("      2 按照指定的学科对成绩进行统计\n");
	printf("\n");
	printf("------------------------------------------\n");

	int i,a;
	char ch;

	printf("请输入您的选项:");
	scanf("%d",&a);
	switch(a)
	{
	case 1:sort_subject();break;
	case 2:count_subject();break;
	default:printf("error\n");
	}

    printf("返回上级菜单请输入y返回主菜单输入任意键\n");
	getchar();
	ch=getchar();
	if(ch=='y'||ch=='Y')
		sort_count();
	system("pause");
	system("cls");

}

void sort_subject()//--------------------------------学科排序---------------------------------------
{
    system("cls");
	printf("\n-------------------------------\n");
	printf(" 1 Science\n");
	printf("\n");
	printf(" 2 Math\n ");
	printf("\n");
	printf(" 3 English");
	printf("\n-------------------------------\n");
	int i,a;
	printf("请输入您的选项\n");
	scanf("%d",&a);
	switch(a)
	{
	case 1:science_sort();break;
	case 2:math_sort();break;
	case 3:english_sort();break;
	default:printf("error\n");
	}

}
void science_sort()//----------------------------按计算机成绩排序----------------------------------------
{
	int i,j;
	struct student temp;
	for(i=0;i<m-1;i++)
		for(j=0;j<m-1-i;j++)
			if(stud[j].score[0]<stud[j+1].score[0])
			{
				temp=stud[j];
				stud[j]=stud[j+1];
				stud[j+1]=temp;
			}
		read_message();
}
void math_sort()//----------------------------按数学成绩排序----------------------------------------
{
	int i,j;
	struct student temp;
	for(i=0;i<m-1;i++)
		for(j=0;j<m-1-i;j++)
			if(stud[j].score[1]<stud[j+1].score[1])
			{
				temp=stud[j];
				stud[j]=stud[j+1];
				stud[j+1]=temp;
			}
		read_message();
}
void english_sort()//----------------------------按英语成绩排序----------------------------------------
{
	int i,j;
	struct student temp;
	for(i=0;i<m-1;i++)
		for(j=0;j<m-1-i;j++)
			if(stud[j].score[2]<stud[j+1].score[2])
			{
				temp=stud[j];
				stud[j]=stud[j+1];
				stud[j+1]=temp;
			}
			read_message();
}
void count_subject()//------------------------------学科统计-----------------------------------------------
{
    system("cls");

	printf("\n-------------------------------\n");
	printf(" 1 Science\n");
	printf("\n");
	printf(" 2 Math\n ");
	printf("\n");
	printf(" 3 English");
	printf("\n-------------------------------\n");
	int i,a;
	printf("请输入您的选项\n");
	scanf("%d",&a);
	switch(a)
	{
	case 1:science_count();break;
	case 2:math_count();break;
	case 3:english_count();break;
	default:printf("error\n");
	}

}
void science_count()//-----------------------------------统计计算机成绩------------------------------------------
{

	int max,min,i,sum=0;
	float ave;
	int a=0,b=0,c=0,d=0,e=0;

	max=stud[0].score[0];
	min=stud[0].score[0];

	for(i=0;i<m;i++)
		if(max<stud[i].score[0])
			max=stud[i].score[0];

	for(i=0;i<m;i++)
		if(min>stud[i].score[0])
            min=stud[i].score[0];

    for(i=0;i<m;i++)
		sum+=stud[i].score[0];

	ave=(float)sum/m;
	for(i=0;i<m;i++)
	{
		if(stud[i].score[0]>90)
			e++;
		else if(stud[i].score[0]>80)
			d++;
		else if(stud[i].score[0]>70)
			c++;
		else if(stud[i].score[0]>60)
			b++;
		else
			a++;
	}
	printf("science\t最高分\t最低分\t平均分\t\t[0,59]\t[60,69]\t[70,79]\t[80,89]\t[90,100]\n");
	printf("  \t%d\t%d\t%f\t%3d\t%3d\t%3d\t%3d\t%3d\n",max,min,ave,a,b,c,d,e);

}
void math_count()//-----------------------------------统计数学成绩------------------------------------------
{
	int max,min,i,sum=0;
	float ave;
	int a=0,b=0,c=0,d=0,e=0;

	max=stud[0].score[1];
	min=stud[0].score[1];

	for(i=0;i<m;i++)
		if(max<stud[i].score[1])
			max=stud[i].score[1];

	for(i=0;i<m;i++)
		if(min>stud[i].score[1])
		    min=stud[i].score[1];

	for(i=0;i<m;i++)
		sum+=stud[i].score[1];

	ave=(float)sum/m;
	for(i=0;i<m;i++)
	{
		if(stud[i].score[1]>90)
			e++;
		else if(stud[i].score[1]>80)
			d++;
		else if(stud[i].score[1]>70)
			c++;
		else if(stud[i].score[1]>60)
			b++;
		else
			a++;
	}
	printf("math\t最高分\t最低分\t平均分\t\t[0,59]\t[60,69]\t[70,79]\t[80,89]\t[90,100]\n");
	printf("  \t%d\t%d\t%f\t%3d\t%3d\t%3d\t%3d\t%3d\n",max,min,ave,a,b,c,d,e);


}
void english_count()//-----------------------------------统计英语成绩------------------------------------------
{
	int max,min,i,sum=0;
	float ave;
	int a=0,b=0,c=0,d=0,e=0;

	max=stud[0].score[2];
	min=stud[0].score[2];

	for(i=0;i<m;i++)
		if(max<stud[i].score[2])
			max=stud[i].score[2];

	for(i=0;i<m;i++)
		if(min>stud[i].score[2])
		    min=stud[i].score[2];

	for(i=0;i<m;i++)
		sum+=stud[i].score[2];

	ave=(float)sum/m;
	for(i=0;i<m;i++)
	{
		if(stud[i].score[0]>90)
			e++;
		else if(stud[i].score[0]>80)
			d++;
		else if(stud[i].score[0]>70)
			c++;
		else if(stud[i].score[0]>60)
			b++;
		else
			a++;
	}
	printf("english\t最高分\t最低分\t平均分\t\t[0,59]\t[60,69]\t[70,79]\t[80,89]\t[90,100]\n");
	printf("  \t%d\t%d\t%f\t%3d\t%3d\t%3d\t%3d\t%3d\n",max,min,ave,a,b,c,d,e);

}
void delete_make()//-------------------------删除与修改---------------------------------
{
    system("cls");
	load();
	printf("\n---------删除与修改功能-----------\n");
	printf("\n1 删除学生信息\n");
	printf("\n");
	printf("2 修改学生信息\n");
	printf("\n----------------------------------\n");
	int b;
	char ch;
	printf("请输入您的选项:");
	scanf("%d",&b);
	switch(b)
	{
	case 1:delete1();break;
	case 2:make();break;
	default:printf("error\n");
	}
	printf("返回上级菜单请输入y返回主菜单输入任意键\n");
	getchar();
	ch=getchar();
	if(ch=='y'||ch=='Y')
		delete_make();
	system("pause");
	system("cls");
}
void delete1()//-----------------------------删除功能---------------------------------
{
    system("cls");
    char ch;
    printf("************删除功能**********\n");
    printf("\n");
    printf("     1 按学号删除\n");
    printf("\n");
    printf("     2 按姓名删除\n");
    printf("\n");
    printf("******************************\n");
    int a;
    printf("请输入您的选项;");
    scanf("%d",&a);
    switch(a)
    {
        case 1:id_delete();break;
        case 2:name_delete();break;
        default:printf("error\n");
    }
        save();
        read_message();
}
void id_delete()//----------------------按学号删除----------------
{
    int a,i,j;

	printf("请输入该学生学号\n");
	scanf("%d",&a);

    for(i=0;i<m;i++)
        if(stud[i].num==a)
			break;

    if(i==m)
            printf("不存在\n");

    else
    {
        for(j=i;j<m;j++)
        stud[j]=stud[j+1];
        m--;
        printf("删除成功\n");
    }
}
void name_delete()//----------------按姓名删除----------
{
    int i,j,flag=0;
    int n=0;
    char a[10];

    printf("请输入您要删除的学生姓名:");
    scanf("%s",a);

    for(i=0;i<m;i++)
    {
        if(strcmp(stud[i].name,a)==0)
        {
            n++;
            flag=1;
            for(j=i;j<m;j++)
            stud[j]=stud[j+1];
			i=i-1;
        }
    }
    if(!flag)
		{
			printf("不存在\n");
		}
    else
    {
         m-=n;
         printf("删除成功\n");
    }
}
void make()//--------------------------------修改功能------------------------------
{
    system("cls");
	int a,b,c,i;
	char ch;

	printf("请输入该学生学号\n");
	scanf("%d",&a);
	  for(i=0;i<m;i++)
        if(stud[i].num==a)
		{
			c=i;
			break;
		}
		if(i==m)
            printf("不存在\n");
        else
        {
        printf("--------------修改选项------------");
		printf("        \n1 计算机成绩\n");
		printf("        \n2 数学成绩\n");
		printf("        \n3 英语成绩\n");
		printf("----------------------------------\n");
		printf("请输入要修改的学科的序号:");

		scanf("%d",&b);
		switch(b)
		{
		case 1:make_science(c);break;
		case 2:make_math(c);break;
		case 3:make_english(c);break;
		default:printf("error\n");
		}
		read_message();
		}
}
void make_science(int c)//--------------------------修改计算机成绩-----------------------------
{
	int a;
	printf("请输入您修改过后的成绩\n");
	scanf("%d",&stud[c].score[0]);
	stud[c].sum=0;
    stud[c].sum=stud[c].score[0]+stud[c].score[1]+stud[c].score[2];
    stud[c].ave=stud[c].sum/3;
	save();
	printf("修改成功\n");

}
void make_math(int c)//-------------------------------修改数学成绩---------------------------
{
	int a;
	printf("请输入您修改过后的成绩\n");
	scanf("%d",&stud[c].score[1]);
	stud[c].sum=0;
    stud[c].sum=stud[c].score[0]+stud[c].score[1]+stud[c].score[2];
    stud[c].ave=stud[c].sum/3;
	save();
	printf("修改成功\n");

}
void make_english(int c)//---------------------------修改英语成绩-----------------------------
{

	int a;
	printf("请输入您修改过后的成绩\n");
	scanf("%d",&stud[c].score[2]);
	stud[c].sum=0;
    stud[c].sum=stud[c].score[0]+stud[c].score[1]+stud[c].score[2];
    stud[c].ave=stud[c].sum/3;
	save();
	printf("修改成功\n");
}
void add_message()//-------------------添加学生信息---------------------
{

		FILE *fp;
	int i=0;
	if((fp=fopen("stu.dat","ab"))==NULL)
	{
		printf("文本不能打开，出错！\n");
		exit (0);
	}
	printf("请输入学生姓名:");

			scanf("%s",stud[m].name);
			getchar();
			printf("请输入学生性别:");
			scanf("%c",&stud[m].sex);
			getchar();
			printf("请输入计算机成绩:");
			scanf("%d",&stud[m].score[0]);
			getchar();
			printf("请输入数学成绩:");
			scanf("%d",&stud[m].score[1]);
			getchar();
			printf("请输入英语成绩:");
			scanf("%d",&stud[m].score[2]);
			getchar();
			stud[m].sum=0;
			stud[m].sum=stud[m].score[0]+stud[m].score[1]+stud[m].score[2];
			stud[m].ave=stud[m].sum/3;
			srand((int)time(0));
		    stud[m].num=(rand()%1000)+2014000;
		    for(i=m;i<=m;i++)
		fwrite(&stud[i],sizeof(struct student),1,fp);

		fclose(fp);m++;

			system("pause");
			system("cls");
}
void keys()//----------------------------------密码---------------------
 {
     char a[20];
     char ch;
     int i=0,j;
     for(j=0;j<3;j++)
     {
     printf("\t请输入密码 : ");
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
            a[i] = ch;
            i++;
        }
    	ch =getch();
    }
    	a[i]='\0';

    	if (0==strcmp(KEY,a))
    	{
    	    printf("\n密码输入正确,两秒后进入系统\n");
    	    Sleep(2000);
    	    system("cls");
    	    break;
        }

        else
        {
            printf("\n密码输入错误\n");
            i=0;
        }
     }
     if(j==3)
     exit(0);
}








