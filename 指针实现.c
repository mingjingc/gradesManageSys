#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OR_STUS 10
#define COURSES 5
struct student
{
    int num;
	char name[30];
	char sex[4];
    double Math;
	double Chinese;
	double English;
    double Computer;
	double PE;
	double gross_average;
	struct student *next;
};
typedef struct student STUDENT;

struct course_average
{
	double Math;
	double Chinese;
	double English;
	double Computer;
	double PE;
}c_aver;

STUDENT *create()
{
    STUDENT *p1,*p2,*head;
	int i;


	head=NULL;
	p2=p1=(STUDENT *)malloc(sizeof(STUDENT));

    if(OR_STUS>=1)
        head=p1;
	  

	for(i=2;i<=OR_STUS;i++)
	{
	   p1=(STUDENT *)malloc(sizeof(STUDENT));
	   p2->next=p1;
	   p2=p1;
	}

	p2->next=NULL;
	return head;
}

void get_initial_data(STUDENT *head);
void calculate_initial_average(STUDENT *head);
void calculate_every_course_average(STUDENT *head,int stus);
void save_present_data(STUDENT *head);
void average_sort(STUDENT *head,int stus);
double calculate_a_student_gross_average(STUDENT *a_student);
STUDENT *insert_a_student_data(STUDENT *head);
void demonstrate_all_excellent_students_datas(STUDENT *head);
void demonstrate_all_failing_at_least_a_course_students_data(STUDENT *head);

int main()
{
    STUDENT *p,*head;
	head=p=create();

	get_initial_data(head);
    calculate_initial_average(head);
	calculate_every_course_average(head,OR_STUS);
	save_present_data(head);
    average_sort(head,OR_STUS);
    head=insert_a_student_data(head);
    demonstrate_all_failing_at_least_a_course_students_data(head);
    demonstrate_all_excellent_students_datas(head);

    return 0;
}



void get_initial_data(STUDENT *head)
{
	STUDENT *p;
	int i;
	char t[20];
    
    
	p=head;
	for(i=0;i<OR_STUS;i++)
	{
       gets(t); p->num=atoi(t);
       
	   gets(p->name);  
       
	   gets(p->sex);   
	   
	   scanf("%lf%lf%lf%lf%lf",&p->Math,&p->Chinese,
		      &p->English,&p->Computer,&p->PE);
       fflush(stdin);
	   p=p->next;
	}
}

void calculate_initial_average(STUDENT *head)
{
	STUDENT *p=head;
	if(head!=NULL)
	{
		while(p!=NULL)
		{
			p->gross_average=((p->Math)+(p->Chinese)+(p->English)+
				              (p->Computer)+(p->PE))/5.0;
			
		    p=p->next;
		}
	}
}

void calculate_every_course_average(STUDENT *head,int stus)
{
        STUDENT *p=head;
		double Math_sum=0,Chinese_sum=0,English_sum=0,
			   Computer_sum=0,PE_sum=0;
		if(head!=NULL)
		{
			while(p!=NULL)
			{
				Math_sum+=p->Math;
				Chinese_sum+=p->Chinese;
				English_sum+=p->English;
				Computer_sum+=p->Computer;
				PE_sum+=p->PE;
				p=p->next;
			}
		}

        c_aver.Math=Math_sum/stus;
		c_aver.Chinese=Chinese_sum/stus;
		c_aver.English=English_sum/stus;
		c_aver.Computer=Computer_sum/stus;
		c_aver.PE=PE_sum/stus;
}

void save_present_data(STUDENT *head)
{
	FILE *fp;
	STUDENT *p;
	p=head;
	

	fp=fopen("stu.c","wb");

	if(fp==NULL)
		exit(1);
   
    if(head!=NULL)
    {
		while(p!=NULL)
		{
            
			fwrite(p,sizeof(STUDENT),1,fp); 
			p=p->next;
		}
	}
    
	fclose(fp);
	fp=fopen("stu.c","ab");
	fwrite(&c_aver,sizeof(struct course_average),1,fp);

	fclose(fp);
}


void average_sort(STUDENT *head,int stus)
{
	STUDENT *p,temp;
	STUDENT *t;
	int i,j,k;
	FILE *fp,*sort_fp;
	fp=fopen("stu.c","rb");

	p=head;
    t=(STUDENT *)malloc(stus*sizeof(STUDENT));
    
	for(i=0;i<stus;i++)
	{
		fread((t+i),sizeof(STUDENT),1,fp);
	}

   
	for(i=0;i<stus-1;i++)
	{
		k=i;
		for(j=i+1;j<stus;j++)
		{
			if( (t[k].gross_average) < (t[j].gross_average) )
				k=j;
		}
		if(i!=k)
		{
			temp=t[k];
			t[k]=t[i];
			t[i]=temp;
		}
	}
  

	fclose(fp);
    sort_fp=fopen("stu-sort","wb");
	i=0;
    while(p!=NULL&&i<stus)
	{
		
		p->num=t[i].num;
		strcpy(p->name,t[i].name);
		strcpy(p->sex,t[i].sex);
		p->Math=t[i].Math;
		p->Chinese=t[i].Chinese;
		p->English=t[i].English;
		p->Computer=t[i].Computer;
		p->gross_average=t[i].gross_average;
		p->PE=t[i].PE;
	
		fwrite(p,sizeof(STUDENT),1,sort_fp);
		p=p->next;
		i++;
	}
    
	fclose(fp);
	free(t);
	

}


STUDENT *insert_a_student_data(STUDENT *head)
{ 
	  STUDENT *a_student,*p,*last_p;         
	  FILE *fp;
      a_student=(STUDENT *)malloc(sizeof(STUDENT));

      scanf("%d",&a_student->num);
	  fflush(stdin);
	  gets(a_student->name);
	  gets(a_student->sex);
	  scanf("%lf %lf %lf %lf %lf",&a_student->Math,&a_student->Chinese,
		      &a_student->English,&a_student->Computer,&a_student->PE);
      a_student->next=NULL;
      
	  a_student->gross_average = calculate_a_student_gross_average(a_student);
      

      p=head;
	  while(p!=NULL)
	  {
		  if((a_student->gross_average) >= (head->gross_average) )
          {
			   head=a_student;
			   a_student->next=p;
			   break;
		  }

		  else if((a_student->gross_average) >=(p->gross_average))
		  {
              last_p->next=a_student;
			  a_student->next=p;
			  break;
		  }
		  else if( p->next==NULL)
		  {
			  p->next=a_student;
			  a_student->next=NULL;
			  break;
		  }
		  else
		  {
			  last_p=p;
			  p=p->next;
		  }
	  }
	  
	  p=head;
      fp=fopen("new-stu-sort","wb");
	  while(p!=NULL)
	  {
		  fwrite(p,sizeof(STUDENT),1,fp);
		  p=p->next;
	  }
      fclose(fp);
      return head;
}
               
 double calculate_a_student_gross_average(STUDENT *a_student)
 {
	
	 return (a_student->Math + a_student->Chinese +a_student->English +
		      a_student->Computer+a_student->PE)/5.0;
 }

     
void demonstrate_all_excellent_students_datas(STUDENT *head)
{
	STUDENT *p;
	p=head;
	while(p!=NULL)
	{
		if(p->gross_average>=90)
		{
			printf("%d\n",p->num);
			puts(p->name);
			printf("%lf %lf %lf %lf %lf\n",p->Math,p->Chinese,
				   p->English,p->Computer,p->PE);
			printf("%lf\n",p->gross_average);
		}
		p=p->next;
	}
}


void demonstrate_all_failing_at_least_a_course_students_data(STUDENT *head)
{
	STUDENT *p;
    p=head;
	while(p!=NULL)
	{
		if(p->Math<60 ||p->Chinese<60)
        {

			printf("%d\n",p->num);
			puts(p->name);
			printf("%lf %lf %lf %lf %lf\n",p->Math,p->Chinese,
				   p->English,p->Computer,p->PE);
			printf("%lf\n",p->gross_average);
		}
		else if(p->English<60||p->Computer<60||p->PE<60)
		{
            printf("%d\n",p->num);
			puts(p->name);
			printf("%lf %lf %lf %lf %lf\n",p->Math,p->Chinese,
				   p->English,p->Computer,p->PE);
			printf("%lf\n",p->gross_average);
		}
	    p=p->next;
	}
}
       







		
		
		


