#include <stdio.h>
#include<stdlib.h>
#define smax 10
#define emax 255
double power(int x,double y)
{
	int t;double s=1;
	for (t=0; t<x;t++)
		s=s*y;
	return s;
}

double calc(char op, double x, double y)
{
	double num;
	if (op=='+')
		num=x+y;
	else if (op=='-')
		num=y-x;
	else if (op=='*')
		num=y*x;
	else if (op=='/')
		num=y/x;
	else if (op=='^')
		num=power((int)x,y);
	return num;
}
int rank(char op)
{
	int r;
	if (op=='+') r=0;
	else if (op=='-') r=1;
	else if (op=='*') r=2;
	else if (op=='/') r=2;
	else if (op=='^') r=3;
	return r;
}

double calculate(char ex[])
{
	//stack
	int d=0;
	double s[smax];
	char op[smax];
	int top=0;
	int otop=0;
	int i;double num,x,y;
	double ans=0;
	double rtop,rinput;
	char o;

	i=0;
	num=0;
	s[0]=0;
	top=1;
	op[0]='+';
	otop=1;
	while (1)
	{
		if (ex[i] >=48 && ex[i]<58)
		{
			num=num*10+ex[i]-48;
		}
        else if(ex[i]=='.')
        {int b;
        b=i+1;d=0;
        while(ex[b]>=48&&ex[b]<58)
        {d++;b++;}
        }
		else
		{
			int c=0;
			while(c<d)
			{num=num/10;c++;}
			s[top]=num;
			top=top+1;
			num=0;
			if (ex[i]==0) 
				break;
			else
			{
				rinput=rank(ex[i]);
				otop=otop-1;
				o=op[otop];
				rtop=rank(o);
				
				while (rtop>=rinput && rtop!=0)
				{
					top=top-1;
					x=s[top];
					top=top-1;
					y=s[top];
					s[top]=calc(o,x,y);
					top=top+1;
					otop=otop-1;
					o=op[otop];
					if (o=='+') 
						rtop=0;
					else 
						if (o=='-') rtop=1;	
				}
				op[otop]=o;
				otop=otop+1;
				op[otop]=ex[i];
				otop=otop+1;
			}
		}
		i=i+1;
	}
	while (otop!=0)
	{
		top=top-1;
		x=s[top];
		top=top-1;
		y=s[top];
	
		otop=otop-1;
		o=op[otop];
		s[top]=calc(o,x,y);
		top=top+1;
	}
	ans=s[0];
	
	return ans;
	
}
void num(char ex[])
{
    int i,j,k=0,m=0,n=0;
    char ex2[emax];  
    for(k=0;k<emax;k++)
    {
    i=emax;j=0;
    while(ex[i]=='(')
    {n=i;
    while(ex[i+1]!=')')
    {ex2[j]=ex[i+1];j++;i++;}   
    i=n;
    ex[i]=char(calculate(ex2)+48);
    for(m=i;m<emax;m++)
    ex[m+1]=ex[m+j+2];
    i--;}
    }   
     
}
int main()
{
    char ex[emax];
    scanf("%s",ex);
    num(ex);
    printf("%s=%f\n",ex,calculate(ex));
    getchar();
	putchar(getchar());
}


   
