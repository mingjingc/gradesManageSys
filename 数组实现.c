#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define PASSWORD "123456"/*登陆密码*/
#define MAX_PEOPLE 300/*能处理的最多人数*/
#define COURSES 5/*课程个数*/

struct student
{
    int num;/*学号*/
	char name[20];/*姓名*/
	char sex[4];/*性别*/
    double Math;/*数学成绩*/
	double Chinese;/*语文成绩*/
	double English;/*英语成绩*/
    double Computer;/*计算机程序*/
	double PE;/*体育成绩*/
	double average;/*平均分*/
	double gross;/*gross是一个学生五门课的总分*/                                                

};
typedef struct student STUDENT;
STUDENT stu[MAX_PEOPLE];
int n;/* 全局变量是实际学生人数*/      
                                                          
struct course_data/*各科的的数据*/                                            
{
    double pass_rate;/*及格率*/
	double excellent_rate;/*优秀率*/
	double average;/*课程平均分*/
	double standard_deviation;/*标准差*/
	double highest_grade;/*最高分*/
	double lowest_grade;/*最低分*/
	
}Math,Chinese,English,Computer,PE;

void introduce();/*介绍*/
void Denglu(short *);/*登录*/
int menu();/*主菜单*/
void get_initial_data();/*给学生结构体赋初值*/


void sort();/*排序功能*/
void average_descending_sort();/*按学生总平均分降序排*/
void num_ascending_sort();/*按学号降序排*/
void Math_descending_sort();/*按数学成绩降序排序*/
void Chinese_descending_sort();
void English_descending_sort();
void Computer_descending_sort();
void PE_descending_sort();



void insert();/*插入功能*/
void insert_students_follow_student_num_ascending_order();/*按学号升序插入*/
void insert_students_follow_average_grades_descending_order();/*按学生总平均分降序插入*/
void insert_on_the_end();/*只将要插入的学生数据放在末尾*/

void search();/*查找一个学生数据功能*/
void half_search_a_student_data_according_to_num();/*根据学号升序折半查找*/
void sequential_search_a_student_data_according_to_num();/*跟据学号顺序查找*/


void Delete_a_student_according_to_num();/*删除一个学生数据*/

void calculate_all_courses_data();/*计算所有的课程数据*/

double  calculate_students_stardard_daviation();/*学生的标准差*/
void demonstrate();/*给用户筛选要展示的学生数据种类*/
void demonstrate_all_failing_at_least_a_course_students_data();/*不及格的*/
void demonstrate_all_excellent_students_datas();/*优秀的*/
void demonstrate_all_students_data();/*所有学生的*/
void demonstrate_all_courses_data();/*所有课程的*/

void save_present_student_data();/*保存当前的数据到文件*/


int main()
{
    short times=1;/*输入密码的的次数*/
	int choice;
	

    introduce();
    Denglu(&times);

	if(times>3)
		exit(0);
    printf("\n\n****欢迎登陆学生成绩管理系统****\n\n");

    do
	{
    
        choice=menu();
		switch(choice)
		{
		    
			case 1: get_initial_data();
				    break;
	        case 2: sort();
				    break;
			case 3: insert();
				    break;
			case 4: Delete_a_student_according_to_num();
				    break;
			case 5:search();
				   break;
			case 6:calculate_all_courses_data(); 
				   break;
			case 7:demonstrate();
                   break;
			case 8:save_present_student_data();
				   break;

        }
	}while(choice!=0);
	
	return 0;
}



/************************************************
Function:对程序的简单介绍
Parameter:无
**************************************************/
void introduce()
{
	printf("\n\n**************************************************************\n");
	    printf("** 该程序对学生成绩有排序、查询、插入、平均分、标准差等功能，**\n");
		printf("** 还可以计算各门课的最高最低分、平均分、及格优秀率、标准差，**\n");
		printf("** (全部数据.c)将成为全部数据的保存的文件名称，生成的stu.c， **\n");
		printf("** 存放的只有二进制文件的学生数据，下次要调用就将其放在C盘名 **\n");
		printf("** c的文件夹即可。                                           **\n");
		printf("**************************************************************\n");
}



/*******************************************
function:输入登陆密码
parameter:一个输入密码次数存放的地址
*********************************************/
void Denglu(short *times)
{
	char password[11];
	
	printf("请输入登录密码(输入超过三次就会自动退出):");
	while(*times<=3)
	{
	  gets(password);
	  
	  if(strcmp(password,PASSWORD)==0)
		return;
	  else
		  printf("密码错误!\n");
	  
	 (*times)++;
	}
	

}


/**************************
function:主菜单
parameter:无
*****************************/   
int menu()
{
	int choice;

	

	printf("\n\n0----------退出\n");
    printf("\n1----------初始化学生数据");
    printf("\n2----------排序\n");
	printf("\n3----------插入学生信息\n");
    printf("\n4----------根据学号删除一个学生数据\n");
    printf("\n5----------按学号查找一个学生信息\n");
	printf("\n6----------计算所有的课程数据\n");
    printf("\n7---------打印数据\n");
    printf("\n8---------保存当前的数据\n");

    printf("请输入一个数(0 to 8):\n");
    do
	{
		scanf("%d",&choice);
	}while(choice<0||choice>8);
	puts("\n");

	return choice;
}


/***************************************
Function:获得学生的初始数据
Parameter:无
****************************************/
void get_initial_data()
{
	int choice;
	printf("请选择得到学生数据的方式\n");
	printf("1----------键盘输入\n");
	printf("2----------文件导入\n");
	printf("0----------退出选择:");
		do
		{
			scanf("%d",&choice);
			if(choice==0)
				return;
		}while(choice<1||choice>2);
	if(choice==1)
	{
	  int i;
	  char t[20];
      printf("请输入要输入的学生人数(less than %d)\n"
		    "如果输入的人数为0，则退出该整个选择:",MAX_PEOPLE);
      do
	  {
	   scanf("%d%*c",&n);
	   if(n==0)
		   return;
	   if(n>MAX_PEOPLE)
		   printf("空间不足!");
	  }while(n<0||n>MAX_PEOPLE); /*输入的数据个数不能大于最大人数*/
      printf("\n请依次输入学生的学号+姓名+性别+五个科目的成绩\n"
		     "(数、语文、英、计算机、体育)\n\n");
    
	  for(i=0;i<n;i++)
	  {
       gets(t); stu[i].num=atoi(t);/*将字符串转化为整数*/
       
	   gets(stu[i].name);  
       
	   gets(stu[i].sex);   
	   
	   scanf("%lf %lf %lf %lf %lf",&stu[i].Math,&stu[i].Chinese,
		      &stu[i].English,&stu[i].Computer,&stu[i].PE);
       fflush(stdin); /*fflush(stdin)是清空输入缓冲区函数*/  
       puts("******************");
       stu[i].gross=(stu[i].Math+stu[i].Chinese+stu[i].English+
		             stu[i].Computer+stu[i].PE);
	   stu[i].average=(stu[i].Math+stu[i].Chinese+stu[i].English+
		             stu[i].Computer+stu[i].PE)/COURSES;
	   
                                                                    
	   
	  }
	  printf("输入数据成功!");
	}
	else if(choice==2)
    {
       FILE *out_fp;
	   int i=0;
	   char review;
       printf("\n\n你将会把放在C盘的名为c的文件夹的stu.c文件的先前输入并保存了\n"
 		   "的数据导入，请确认将导入的数据是否正确?(Y或N):  ");  /*检查要导入的文件*/
	   scanf("%c%*c",&review);
	   if(review=='N'||review=='n')
		return;
	    else
		{
		  if( (out_fp=fopen("C:\\c\\stu.c","rb")) !=NULL)
		  {
		    n=0;
		    while(fread(&stu[i],sizeof(STUDENT),1,out_fp)==1)
			{
			  n++;
			  if(n>=MAX_PEOPLE)  /*判断所导入的数据个数是否大于最大值*/
			  {
				  printf("没有足够位置放下全部学生数据,有些数据可能不能导入进来!");
				  return;         
			  }
			  i++;
			}
		  }
		}
		printf("导入学生数据成功!\n");
	}


}









/******************************
function:排序菜单
parameter:无
**********************************/
void sort()
{
	
	int choice;
	printf("请选择排序的方式:\n");
	printf("%-30s","1.按平均分降序排");  
    printf("%-30s","2.按学号升序排");
	putchar('\n');                         
	printf("%-30s","3.按数学成绩降序排");
	printf("%-30s","4.按语文成绩降序排");
	putchar('\n');
	printf("%-30s","5.按英语成绩降序排");
	printf("%-30s","6.按计算机成绩降序排");
	putchar('\n');
	printf("%-30s","7.按体育成绩降序排");
	printf("%-30s","0.退出该选择:");
	putchar('\n');
	do
	{
		scanf("%d",&choice);
		if(choice==0)
			return;
	}while(choice>7||choice<0);
	switch(choice)
	{
	   case 1:average_descending_sort();
		      break;
	   case 2:num_ascending_sort();
			  break;
	   case 3:Math_descending_sort();
			  break;
	   case 4:Chinese_descending_sort();
		      break;
	   case 5:English_descending_sort();
		      break;
	   case 6:Computer_descending_sort();
		      break;
	   case 7:PE_descending_sort();
		      break;
	}
}      


/******************************
function:按学生总平均分降序排
parameter:无
*******************************/
void average_descending_sort()
{
	STUDENT temp;
	int i,j,k;
	for(i=0;i<n-1;i++)
	{
		k=i;
		for(j=i+1;j<n;j++)
		{
			if( (stu[k].average) < (stu[j].average) )
				k=j;
		}
		if(i!=k)
		{
			temp=stu[k];
			stu[k]=stu[i];
			stu[i]=temp;
		}
	}
  
}

/**************************
function:按学号升序排
parameter:无
********************************/
void num_ascending_sort()
{
	STUDENT temp;     /*设临时结构体用作交换介质*/
	int i,j,k;
	for(i=0;i<n-1;i++) 
	{
		k=i;
		for(j=i+1;j<n;j++)
		{
			if( (stu[k].num) > (stu[j].num) )
				k=j;
		}
		if(i!=k)
		{
			temp=stu[k];
			stu[k]=stu[i];
			stu[i]=temp;
		}
	}
  
}

/**********************
function:按各科成绩降序排
parameter:无
***********************/
void Math_descending_sort()
{
	int i,j;
	STUDENT temp;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i;j++)
		{
			if(stu[j].Math<stu[j+1].Math)
			{
				temp=stu[j];
				stu[j]=stu[j+1];
				stu[j+1]=temp;
			}
		}
	}
}

void Chinese_descending_sort()
{
	int i,j;
	STUDENT temp;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i;j++)
		{
			if(stu[j].Chinese<stu[j+1].Chinese)
			{
				temp=stu[j];
				stu[j]=stu[j+1];
				stu[j+1]=temp;
			}
		}
	}
}
void English_descending_sort()
{
	int i,j;
	STUDENT temp;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i;j++)
		{
			if(stu[j].English<stu[j+1].English)
			{
				temp=stu[j];
				stu[j]=stu[j+1];
				stu[j+1]=temp;
			}
		}
	}
}
void Computer_descending_sort()
{
	int i,j;
	STUDENT temp;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i;j++)
		{
			if(stu[j].Computer<stu[j+1].Computer)
			{
				temp=stu[j];
				stu[j]=stu[j+1];
				stu[j+1]=temp;
			}
		}
	}
}
void PE_descending_sort()
{
	int i,j;
	STUDENT temp;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i;j++)
		{
			if(stu[j].PE<stu[j+1].PE)
			{
				temp=stu[j];
				stu[j]=stu[j+1];
				stu[j+1]=temp;
			}
		}
	}
}






/**********************************
function:插入学生数据的菜单
parameter:无
*************************************/
void insert()
{
	int choice; 
	printf("请选择插入方式:\n");
	printf("1----------学生平均分降序\n");
	printf("2----------学号升序\n");
	printf("3----------到末尾\n");
    printf("0----------退出该选择):");

	do
	{
       scanf("%d",&choice);
	   if(choice==0)
		   return;
	  
	}while(choice<0||choice>3);

	switch(choice)
	{
	   case 1:insert_students_follow_average_grades_descending_order();
		      break;
	   case 2:insert_students_follow_student_num_ascending_order();
		      break;
	   case 3:insert_on_the_end();
	}
}

/*********************************
function:按学号升序插入
parament:无
***********************************/
void insert_students_follow_student_num_ascending_order()
{
	int add_num,i,j;
	STUDENT *add_stu;
	printf("\n请输入要插入的学生人数(在这之前请将最输入的学生按学号升排序)\n,"
		    "如果输入的人数为0，则退出该选择:");
	do
	{
		scanf("%d",&add_num);
        if(add_num==0)
			return;	                     /*return 是要退出所在的函数*/
	    if((add_num+n)>=MAX_PEOPLE)
			printf("空间不够，请考虑输入一个更小值或退出\n");
	}while(add_num<=0||(add_num+n)>=MAX_PEOPLE);

    add_stu=(STUDENT *)malloc(add_num*sizeof(STUDENT));
    
    printf("\n请依次输入学生的学号+姓名+性别+五个科目的成绩\n"
		     "(数、语文、英、计算机、体育)\n\n");
	for(j=0;j<add_num;j++)
	{
       scanf("%d%*c",&add_stu[j]);
       
	   gets(add_stu[j].name);  
       
	   gets(add_stu[j].sex);   
	   
	   scanf("%lf %lf %lf %lf %lf",&add_stu[j].Math,&add_stu[j].Chinese,
		      &add_stu[j].English,&add_stu[j].Computer,&add_stu[j].PE);
       fflush(stdin);  
       puts("******************");
       add_stu[j].gross=(add_stu[j].Math+add_stu[j].Chinese+add_stu[j].English+
		             add_stu[j].Computer+add_stu[j].PE);
       
	   add_stu[j].average=(add_stu[j].Math+add_stu[j].Chinese+add_stu[j].English+
		             add_stu[j].Computer+add_stu[j].PE)/COURSES;
       
	   for(i=0;i<=n;i++)
	   {
		   if(i==n)
		   {
			   stu[n]=add_stu[j];
               n++;
			   break;
			   
		   }
		   if(add_stu[j].num<=stu[i].num)
		   {
			     int k;
			     for(k=n-1;k>=i;k--)
				 {
				   stu[k+1]=stu[k];
				 }
                 stu[i]=add_stu[j];
                 n++;
                 break;
		   }
	   }
	   
           
	}
    free(add_stu);
}

/*****************************************
function:按学生平均分降序插入
parameter:无
*******************************************/
void insert_students_follow_average_grades_descending_order()
{
	int add_num,i,j;
	STUDENT *add_stu;
	printf("\n请输入要插入的学生人数(在这之前请将输入的学生按平均分降排序)\n,"
		    "如果输入的人数为0，则退出该选择:");
	do
	{
		scanf("%d",&add_num);
        if(add_num==0)
			return;                                  /*return 是要退出所在的函数*/
        if((add_num+n)>=MAX_PEOPLE)
			printf("空间不够，请考虑输入一个更小值或退出!\n");
	}while(add_num<0||(add_num+n)>=MAX_PEOPLE);

    add_stu=(STUDENT *)malloc(add_num*sizeof(STUDENT));
    
    printf("\n请依次输入学生的学号+姓名+性别+五个科目的成绩\n"
		     "(数、语文、英、计算机、体育)\n\n");
	for(j=0;j<add_num;j++)
	{
       scanf("%d%*c",&add_stu[j]);
       
	   gets(add_stu[j].name);  
       
	   gets(add_stu[j].sex);   
	   
	   scanf("%lf %lf %lf %lf %lf",&add_stu[j].Math,&add_stu[j].Chinese,
		      &add_stu[j].English,&add_stu[j].Computer,&add_stu[j].PE);
       fflush(stdin);  
       puts("******************");
       add_stu[j].gross=(add_stu[j].Math+add_stu[j].Chinese+add_stu[j].English+
		             add_stu[j].Computer+add_stu[j].PE);
       
	   add_stu[j].average=(add_stu[j].Math+add_stu[j].Chinese+add_stu[j].English+
		             add_stu[j].Computer+add_stu[j].PE)/COURSES;
       
	   for(i=0;i<=n;i++)
	   {
		   if(i==n)
		   {
			   stu[n]=add_stu[j];
               n++;
			   break;
			   
		   }
		   if(add_stu[j].average>=stu[i].average)
		   {
			     int k;
			     for(k=n-1;k>=i;k--)
				 {
				   stu[k+1]=stu[k];
				 }
                 stu[i]=add_stu[j];
                 n++;
                 break;
		   }
	   }
	   
           
	}
    free(add_stu);
}
/*******************************
function:只将学生数据插入到末尾
parameter:无
********************************/
void insert_on_the_end()
{
   int add_num,j;

	printf("\n请输入要插入的学生人数\n,"
		    "(如果输入的人数为0，则退出该选择):");
	do
	{
		scanf("%d",&add_num);
        if(add_num==0)
			return;/*return 是要退出所在的函数*/
        if((add_num+n)>=MAX_PEOPLE)
			printf("空间不够，请考虑输入一个更小值或退出\n");
	}while(add_num<=0||(add_num+n)>=MAX_PEOPLE);

    
    
    printf("\n请依次输入学生的学号+姓名+性别+五个科目的成绩\n"
		     "(数、语文、英、计算机、体育)\n\n");

    for(j=0;j<add_num;j++)
	{
       scanf("%d%*c",&stu[n]);
       
	   gets(stu[n].name);  
       
	   gets(stu[n].sex);   
	   
	   scanf("%lf %lf %lf %lf %lf",&stu[n].Math,&stu[n].Chinese,
		      &stu[n].English,&stu[n].Computer,&stu[n].PE);
       fflush(stdin);  
       puts("******************");
       stu[n].gross=(stu[n].Math+stu[n].Chinese+stu[n].English+
		             stu[n].Computer+stu[n].PE);
       
	   stu[j].average=(stu[n].Math+stu[n].Chinese+stu[n].English+
		             stu[n].Computer+stu[n].PE)/COURSES;
	   n++;
	   if(n>MAX_PEOPLE)
	   { 
		   printf("已没有空位!");
		   return;
	   }
	}
	
}
       

/**********************************
function:以学号删除一个学生信息
parament:无
************************************/
void Delete_a_student_according_to_num()
{
	 int delete_num,i;
     printf("\n请输入一个要删除的学生学号\n"
		     "如果输入的学号为0，则退出该选择:");
	 do
	 {
		 scanf("%d",&delete_num);
		 if(delete_num==0)
			 return;
	 }while(delete_num<0);
	 for(i=0;i<n;i++)
	 {
		 if(delete_num==stu[i].num)
		 {
			 int k;
			 for(k=i+1;k<n;k++)
				 stu[k-1]=stu[k];
             printf("\nDelete successfully!");      /*为什么删除成功后这句话没有被打印出来*/
			 n--;
			 break;
		 }
	 }
	 if(i==n)
		 printf("没有要删除的学生数据!\n");
	 
     
}





/***********************************
function:查询菜单
parameter:无
*************************************/
void search()
{
	int choice;
	printf("请选择查找类型\n");
    printf("1----------按学号升序折半查找\n");
	printf("2----------按学号随机查找\n");
	printf("0----------退出该选择:");
	do
	{
		scanf("%d",&choice);
		if(choice==0)
			return;
	}while(choice<0||choice>2);
	switch(choice)
	{
	   case 1:half_search_a_student_data_according_to_num();
		      break;
	   case 2:sequential_search_a_student_data_according_to_num();
		      break;
	}
}

/*****************************
function:按学号升序折半查找
parameter:无
******************************/    
void half_search_a_student_data_according_to_num()    
{
	int search_num; 
    int mid=0,end,head;

	printf("请输入一个你要查找的学号(在此之前所给的学生数据必须是"
		     "按学号升序的)\n"
			  "如果输入的学号为0，则退出该选择:");
	do
	{
		scanf("%d",&search_num);
		if(search_num==0)
			return;
	}while(search_num<0);
    
	  
	  head=0;end=n-1;        /*折半查找*/
	  while(end>=head)
	  {
		mid=(head+end)/2;
		if(search_num>stu[mid].num)
		   head=mid+1;
		else if(search_num<stu[mid].num)
		   end=mid-1;
        else if(search_num==stu[mid].num)
		{
          printf("\n%d\n",stu[mid].num);
		  puts(stu[mid].name);
		  puts(stu[mid].sex);
		  printf("数学、语文、英语、计算机、体育:");
		  printf("%.2lf %.2lf %.2lf %.2lf %.2lf\n",stu[mid].Math,stu[mid].Chinese,
		           stu[mid].English,stu[mid].Computer,stu[mid].PE);
		  printf("平均分、总分:%.2lf  %.2lf\n\n",stu[mid].average,stu[mid].gross);
          puts("************");
		  return;
        }
	  }
	

	if(search_num!=stu[mid].num)
		printf("\n查找失败!\n");
    
}

/****************************
function:按学生学号顺序查找
parameter:无
*****************************/
void sequential_search_a_student_data_according_to_num()
{  
	int search_num;  /*要查找的学号*/
    int i;

	printf("请输入一个你要查找的学号"
		     "(如果输入的学号为0，则退出该选择):");
	do
	{
		scanf("%d",&search_num);
		if(search_num==0)
			return;
	}while(search_num<0);
    
	  
	  
	for(i=0;i<n;i++)
    {
		 if(search_num==stu[i].num)
		 {
          printf("\n%d\n",stu[i].num);
		  puts(stu[i].name);
		  puts(stu[i].sex);
		  printf("数学、语文、英语、计算机、体育:");
		  printf("%.2lf %.2lf %.2lf %.2lf %.2lf\n",stu[i].Math,stu[i].Chinese,
		           stu[i].English,stu[i].Computer,stu[i].PE);
		  printf("平均分、总分:%.2lf  %.2lf\n\n",stu[i].average,stu[i].gross);
          puts("************");
		  return;
        }
	} 
	

	if(search_num==n)
		printf("\n查找失败!\n");
    
}



/********************************
function:计算所有学生数据
parameter:无
***********************************/
void calculate_all_courses_data()
{
        int i,j;
		double Math_sum=0,Chinese_sum=0,English_sum=0,/*各科的总分*/
			   Computer_sum=0,PE_sum=0;
        
	    int Math_pass=0,     Math_excellent=0,/*pass是及格，excellent是优秀，这里的参数单位是人数*/
	        Chinese_pass=0,  Chinese_excellent=0,
			English_pass=0,  English_excellent=0,
		    Computer_pass=0, Computer_excellent=0,
			PE_pass=0,       PE_excellent=0;

		

       /*计算各学科的总分*/
		for(i=0;i<n;i++)
		{
				Math_sum+=stu[i].Math;
				Chinese_sum+=stu[i].Chinese;
				English_sum+=stu[i].English;
				Computer_sum+=stu[i].Computer;
				PE_sum+=stu[i].PE;
				
			
		}

        Math.average=Math_sum/n;
		Chinese.average=Chinese_sum/n;
		English.average=English_sum/n;
		Computer.average=Computer_sum/n;
		PE.average=PE_sum/n;
        

	
        /*总计各个学科的优秀和及格人数*/
		for(i=0;i<n;i++)
		{
			if(stu[i].Math>=60)
				Math_pass++;
			if(stu[i].Math>=90)
                Math_excellent++;

			if(stu[i].Chinese>=60)
                Chinese_pass++;
			if(stu[i].Chinese>=90)
				Chinese_excellent++;

			if(stu[i].English>=60)
				English_pass++;
			if(stu[i].English>=90)
				English_excellent++;
				
			

			if(stu[i].Computer>=60)
				Computer_pass++;
			if(stu[i].Computer>=90)
				Computer_excellent++;

			if(stu[i].PE>=60)
				PE_pass++;
			if(stu[i].PE>=90)
				PE_excellent++;
		}
        
	    /*计算各个学科的优秀率和及格率*/
		Math.pass_rate=(double)Math_pass/n;
	    Math.excellent_rate=(double)Math_excellent/n;

		Chinese.pass_rate=(double)Chinese_pass/n;
		Chinese.excellent_rate=(double)Chinese_excellent/n;

		English.pass_rate=(double)English_pass/n;
        English.excellent_rate=(double)English_excellent/n;
	

		Computer.pass_rate=(double)Computer_pass/n;
		Computer.excellent_rate=(double)Computer_excellent/n;

		PE.pass_rate=(double)PE_pass/n;
		PE.excellent_rate=(double)PE_excellent/n;

    /*计算各个学科的标准差*/
    for(j=0;j<COURSES;j++)
	{
       double sum1=0,sum2=0;
	   int i;
	  if(j==0)
	 {
	   for(i=0;i<n;i++)
         sum2+=(stu[i].Math-Math.average)*(stu[i].Math-Math.average);
	   Math.standard_deviation=sqrt(sum2/n);
	 }

     else if(j==1)
	 {
	   for(i=0;i<n;i++)
         sum2+=(stu[i].Chinese-Chinese.average)*(stu[i].Chinese-Chinese.average);
	   Chinese.standard_deviation=sqrt(sum2/n);
	 }
	 else if(j==2)
	 {
	   for(i=0;i<n;i++)
         sum2+=(stu[i].English-English.average)*(stu[i].English-English.average);
	   English.standard_deviation=sqrt(sum2/n);
	 } 
     else if(j==3)
	 {
	   for(i=0;i<n;i++)
         sum2+=(stu[i].Computer-Computer.average)*(stu[i].Computer-Computer.average);
	   Computer.standard_deviation=sqrt(sum2/n);
	 } 
     else if(j==4)
	 {
	   for(i=0;i<n;i++)
         sum2+=(stu[i].PE-PE.average)*(stu[i].PE-PE.average);
	   PE.standard_deviation=sqrt(sum2/n);
	 } 
	
    }

    /*下面是找出各科的最高和最低分*/
	Math.highest_grade=0;      Math.lowest_grade=stu[0].Math;
	Chinese.highest_grade=0;   Chinese.lowest_grade=stu[0].Chinese;
	English.highest_grade=0;   English.lowest_grade=stu[0].English;
	Computer.highest_grade=0;  Computer.lowest_grade=stu[0].Computer;
	PE.highest_grade=0;        PE.lowest_grade=stu[0].PE;
	for(i=0;i<n;i++)
	{
		if(Math.highest_grade<=stu[i].Math)
			Math.highest_grade=stu[i].Math;
		if(Math.lowest_grade>=stu[i].Math)
			Math.lowest_grade=stu[i].Math;

		if(Chinese.highest_grade<=stu[i].Chinese)
			Chinese.highest_grade=stu[i].Chinese;
		if(Chinese.lowest_grade>=stu[i].Chinese)
			Chinese.lowest_grade=stu[i].Chinese;

		if(English.highest_grade<=stu[i].English)
			English.highest_grade=stu[i].English;
		if(English.lowest_grade>=stu[i].English)
			English.lowest_grade=stu[i].English;

		if(Computer.highest_grade<=stu[i].Computer)
			Computer.highest_grade=stu[i].Computer;
		if(Computer.lowest_grade>=stu[i].Computer)
			Computer.lowest_grade=stu[i].Computer;

		if(PE.highest_grade<=stu[i].PE)
			PE.highest_grade=stu[i].PE;
		if(PE.lowest_grade>=stu[i].PE)
			PE.lowest_grade=stu[i].PE;
    }
}

/**************************************
function:计算全部学生的总平均分的标准差
patameter:无
return:double类型的学生标准差
***************************************/
double  calculate_students_stardard_daviation()
{
    double sum1=0,sum2=0;
	int i;
	for(i=0;i<n;i++)
    {
		sum1+=stu[i].average;
		
	}
	for(i=0;i<n;i++)
       sum2+=(stu[i].average-sum1/n)*(stu[i].average-sum1/n);
	return sqrt(sum2/n);
	
}




/************************************
function:展示各类数据的菜单
parameter:无
**************************************/
void demonstrate()
{
	int choice;
	printf("请选择打印的数据种类:\n");
	printf("1----------有不及格科目的学生\n");
	printf("2----------优秀生\n" );
	printf("3----------全体学生\n");
	printf("4----------全部课程\n");
	printf("5----------全部学生和课程:");
	do
	{
		scanf("%d",&choice);
	}while(choice<1||choice>5);
	switch(choice)
	{
	   case 1:demonstrate_all_failing_at_least_a_course_students_data();
		      break;
	   case 2:demonstrate_all_excellent_students_datas();
		      break;
	   case 3:demonstrate_all_students_data();
		      break;
	   case 4:demonstrate_all_courses_data();
		      break;
	   case 5:demonstrate_all_students_data();
		      demonstrate_all_courses_data();
			  break;
	}
}
	
/******************************
function:展示有不及格分数的学生
parameter:无
*******************************/
void demonstrate_all_failing_at_least_a_course_students_data()
{
	int i;
      puts("********************************************************************************");
      printf("%6s%8s%6s%8s%8s%8s%8s%8s%8s%8s\n","学号","姓名","性别","数学",
		      "语文","英语","计算机","体育","平均分","总分");
	for(i=0;i<n;i++)
	{
		if(stu[i].Math<60 ||stu[i].Chinese<60)
        {

		    printf("%6d",stu[i].num);
		    printf("%8s",stu[i].name);
		    printf("%6s",stu[i].sex);
		 
		    printf("%8.2lf%8.2lf%8.2lf%8.2lf%8.2lf",stu[i].Math,stu[i].Chinese,
		           stu[i].English,stu[i].Computer,stu[i].PE);
		    printf("%8.2lf %8.2lf\n",stu[i].average,stu[i].gross);
		}
		else if(stu[i].English<60||stu[i].Computer<60||stu[i].PE<60)
		{
            printf("%6d",stu[i].num);
		    printf("%8s",stu[i].name);
		    printf("%6s",stu[i].sex);
		 
		    printf("%8.2lf%8.2lf%8.2lf%8.2lf%8.2lf",stu[i].Math,stu[i].Chinese,
		           stu[i].English,stu[i].Computer,stu[i].PE);
		    printf("%8.2lf %8.2lf\n",stu[i].average,stu[i].gross);
		}
	   
	}
    puts("********************************************************************************");
}

/**************************
function:展示优秀生
parameter:无
***************************/
void demonstrate_all_excellent_students_datas()
{
	int i;
      puts("********************************************************************************");
      printf("%6s%8s%6s%8s%8s%8s%8s%8s%8s%8s\n","学号","姓名","性别","数学",
		      "语文","英语","计算机","体育","平均分","总分");
      for(i=0;i<n;i++)
	  {
          if(stu[i].average>=90)
		  {
		    printf("%6d",stu[i].num);
		    printf("%8s",stu[i].name);
		    printf("%6s",stu[i].sex);
		 
		    printf("%8.2lf%8.2lf%8.2lf%8.2lf%8.2lf",stu[i].Math,stu[i].Chinese,
		           stu[i].English,stu[i].Computer,stu[i].PE);
		    printf("%8.2lf %8.2lf\n",stu[i].average,stu[i].gross);
		  }
	  }
	  
      puts("********************************************************************************");
}

/**********************************
function:展示所有学生的数据
parameter:无
***********************************/
void demonstrate_all_students_data()
{
	  int i;
	  puts("********************************************************************************");
      printf("%6s%8s%6s%8s%8s%8s%8s%8s%8s%8s\n","学号","姓名","性别","数学",
		      "语文","英语","计算机","体育","平均分","总分");
      for(i=0;i<n;i++)
	  {
		  printf("%6d",stu[i].num);
		  printf("%8s",stu[i].name);
		  printf("%6s",stu[i].sex);
		 
		  printf("%8.2lf%8.2lf%8.2lf%8.2lf%8.2lf",stu[i].Math,stu[i].Chinese,
		           stu[i].English,stu[i].Computer,stu[i].PE);
		  printf("%8.2lf %8.2lf\n",stu[i].average,stu[i].gross);
	  }
	  printf("学生总数:%d\n",n);
	  printf("全部学生的成绩标准差是:%.2lf\n",
		      calculate_students_stardard_daviation());
      puts("********************************************************************************");
      
}     

/*******************************
function:展示所有课程的数据
parameter:无
*********************************/
void demonstrate_all_courses_data()
{
	
	 puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
     printf("\t%10s%10s%10s%10s%10s%10s\n","及格率","优秀率","最高分","最低分","平均分","标准差");
	 printf("%8s%10.2lf%10.2lf%10.2lf%10.2lf%10.2lf%10.2lf\n","数学",Math.pass_rate, Math.excellent_rate,
		      Math.highest_grade, Math.lowest_grade, Math.average, Math.standard_deviation);

	 printf("%8s%10.2lf%10.2lf%10.2lf%10.2lf%10.2lf%10.2lf\n","语文",Chinese.pass_rate, Chinese.excellent_rate,
		     Chinese.highest_grade,Chinese.lowest_grade,Chinese.average,Chinese.standard_deviation);

	 printf("%8s%10.2lf%10.2lf%10.2lf%10.2lf%10.2lf%10.2lf\n","英语",English.pass_rate,English.excellent_rate,
		     English.highest_grade,English.lowest_grade,English.average,English.standard_deviation);

	 printf("%8s%10.2lf%10.2lf%10.2lf%10.2lf%10.2lf%10.2lf\n","计算机",Computer.pass_rate,Computer.excellent_rate,
		      Computer.highest_grade,Computer.lowest_grade,Computer.average,Computer.standard_deviation);

	 printf("%8s%10.2lf%10.2lf%10.2lf%10.2lf%10.2lf%10.2lf\n","体育",PE.pass_rate,PE.excellent_rate,
		     PE.highest_grade,PE.lowest_grade,PE.average, PE.standard_deviation);
     puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
}


 




/****************************************************************
function:保存所有学生数据到stu.c,和全部数据到以用户名命名的文件中
parameter:无
*****************************************************************/
 void save_present_student_data()
 {
	 FILE *fp,*fp2;
     
	 int count,i;
	
	 /*保存学生数据到stu.c*/
	 if( (fp=fopen("stu.c","wb")) !=NULL)
	 {
         count=fwrite(stu,sizeof(STUDENT),n,fp);
		 if(count!=n)
			 return;

	 };
     fclose(fp);
     

	 /*保存全部数据到  user (要输入的用户名)*/

     
     if((fp2=fopen("全部数据.c","w"))!=NULL)
	 {
         
         fputs("*************************************************************************************\n",fp2);
      fprintf(fp2,"%6s %8s %6s %8s %8s %8s %8s %8s %8s %8s\n","学号","姓名","性别","数学",
		      "语文","英语","计算机","体育","平均分","总分");

      for(i=0;i<n;i++)
	  {
		  fprintf(fp2,"%6d ",stu[i].num);
		  fprintf(fp2,"%8s ",stu[i].name);
		  fprintf(fp2,"%6s ",stu[i].sex);
		 
		  fprintf(fp2,"%8.2lf %8.2lf %8.2lf %8.2lf %8.2lf",stu[i].Math,stu[i].Chinese,
		           stu[i].English,stu[i].Computer,stu[i].PE);
		  fprintf(fp2,"%8.2lf %8.2lf\n",stu[i].average,stu[i].gross);
	  }
      fprintf(fp2,"学生总数:%d\n",n);
	  fprintf(fp2,"全部学生的平均成绩标准差是:%.2lf\n",
		      calculate_students_stardard_daviation());
     fputs("****************************************************************************************\n",fp2);
      fputs("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n",fp2);
     fprintf(fp2,"\t %10s %10s %10s %10s %10s %10s\n","及格率","优秀率","最高分","最低分","平均分","标准差");
	 fprintf(fp2,"%8s %10.2lf %10.2lf %10.2lf %10.2lf %10.2lf %10.2lf\n","数学",Math.pass_rate, Math.excellent_rate, Math.highest_grade,
		      Math.lowest_grade, Math.average, Math.standard_deviation);
	 fprintf(fp2,"%8s %10.2lf %10.2lf %10.2lf %10.2lf %10.2lf %10.2lf\n","语文",Chinese.pass_rate, Chinese.excellent_rate,
		     Chinese.highest_grade, Chinese.lowest_grade, Chinese.average, Chinese.standard_deviation);

	 fprintf(fp2,"%8s %10.2lf %10.2lf %10.2lf %10.2lf %10.2lf %10.2lf\n","英语",English.pass_rate, English.excellent_rate,
		     English.highest_grade, English.lowest_grade, English.average, English.standard_deviation);

	 fprintf(fp2,"%8s %10.2lf %10.2lf %10.2lf %10.2lf %10.2lf %10.2lf\n","计算机",Computer.pass_rate, Computer.excellent_rate,
		      Computer.highest_grade, Computer.lowest_grade, Computer.average,Computer.standard_deviation);

	 fprintf(fp2,"%8s %10.2lf %10.2lf %10.2lf %10.2lf %10.2lf %10.2lf\n","体育",PE.pass_rate,PE.excellent_rate,
		      PE.highest_grade,PE.lowest_grade,PE.average,PE.standard_deviation);
     fputs("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++",fp2);
     
     fclose(fp2);
	 printf("已将以上的学生数据保存到了当前位置的stu.c和和全部数据保存在了() 文件中!");
	}
 }

