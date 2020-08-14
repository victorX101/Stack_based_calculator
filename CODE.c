/*
INPUT FORMAT

First input is an integer representing number of testcases. Then each line has a string which needs to be solved.
Type space separated operators and integers(negative or positive).
Operators given the Image can be used here. End the string with # anything after # in a string will be ignored.
----------------------------------------------------

OUTPUT FORMAT

value of each string is printed in new lines or an ERROR string is printed and program exits if string expression is not in correct format.
------------------------------------------------------

Testcases
2
12 * 5 & 7 / 1#
123 + 12 << 1 - 6#
----
4
ERROR
----
1
12 + 1 * -34 == 12# 12 
-----------------------------------------------------
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int stack1[50],top1=-1,top2=-1;
char stack2[50];
int popnum()
{
	if(top1>-1)
	return stack1[top1--];
	return 0;
}

char popchar()
{
	if(top2>-1)
	return stack2[top2--];
}

//--------------------------------
int solveoper(int a,int b,char c);
int precedence(char c);
//-------------------------------
		
void pushnum(int value)
{
	if(top1<49)
	stack1[++top1]=value;
}

void pushchar(char value)
{
	if(top2==-1)
	{stack2[++top2]=value;
	return;}
	else
	{
		while((precedence(stack2[top2])>=precedence(value)) && (top2>-1))
		{	
			char oper = popchar();
			if(top1>=1)
			{
				int a = popnum();
				int b = popnum();
				int c = solveoper(b,a,oper);
				pushnum(c);
			}
			else
			{
				printf("Error\n");
				exit(0);
			}		
		}
		stack2[++top2]=value;
	}		
			
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void main()
{
	char s[100];
	char c;
	int t;
	scanf("%d",&t);
	while(t--)
	{top1 = -1;top2 = -1;
	c = scanf("%c",&c);
	scanf("%[^\n]s",s);
	
	int i=0,flag,ans,x,y;
	while(s[i]!='#' && s[i]!='\0')
	{
		if(s[i]>='0' && s[i]<='9')
		{
			flag=0;
			if(i!=0 && s[i-1]=='-')
			flag=1;
			int val=0;
			while(s[i]!=' ' && s[i]!='#')
			{
				val = val*10 + (s[i] - '0');
				i++;
			}
			if(flag==1)
			val = val*(-1);
			pushnum(val);
			
			
		}
		switch(s[i])
		{
			
			case '*':
			case '/':
			case '%':
			case '+':
			case '&':
			case '^':
			case '|':
			pushchar(s[i]);
			break;
		}
		if(s[i]=='-' && s[i+1]==' ')
		{
			pushchar('-');
		}	
		switch(s[i])
		{
			case '<':
			switch(s[i+1])
			{
				case ' ':
				pushchar(s[i]);
				i+=1;
				break;
				case '<':
				pushchar('a');
				i+=1;
				break;
				case '=':
				pushchar('c');
				i+=1;
				break;
				default:
				continue;
			}
			break;
			case '>':
			switch(s[i+1])
			{
				case ' ':
				pushchar(s[i]);
				i+=1;
				break;
				case '>':
				pushchar('b');
				i+=1;
				break;
				case '=':
				pushchar('d');
				i+=1;
				break;
				default:
				continue;
			}
			break;
		}
		if(s[i]=='=' && s[i+1]=='=')
		{pushchar('e');
		i+=1;}
		if(s[i]=='!' && s[i+1]=='=')
		{pushchar('f');
		i+=1;}
		if(s[i]=='@' || s[i]=='$')
		{
			printf("Error\n");
			continue;
		}	
		i++;
	}
	while(top2>0)
	{
		if(top1<1)
		{
			printf("\nError\n");
			
		}
		c = popchar();
		x = popnum();
		y = popnum();
		y = solveoper(y,x,c);
		
		pushnum(y);
	}
			if(top2>-1)
			{
				c = popchar();
				x = popnum();
				y = popnum();
				y = solveoper(y,x,c);
				printf("\n%d \n",y);
			}
		
	}	
}			
			
// Function to solve a binary equation-------------------------------------------------------------------------------

int solveoper(int a,int b,char c)
{
	switch(c)
	{
		case '*':
		return a*b;
		case '/':
		return a/b;
		case '%':
		return a%b;
		case '+':
		return a+b;
		case '-':
		return a-b;
		case '&':
		return a&b;
		case '^':
		return a^b;
		case '|':
		return a|b;
		case '<':
		if(a<b)
		return 1;
		return 0;
		case '>':
		if(a>b)
		return 1;
		return 0;
		case 'a':
		if(b<0)
		{
			printf("Error\n");
			exit(0);
		}	
		return a<<b;
		case 'b':
		if(b<0)
		{
			printf("Error\n");
			exit(0);
		}
		return a>>b;
		case 'c':
		if(a<=b)
		return 1;
		return 0;
		case 'd':
		if(a>=b)
		return 1;
		return 0;
		case 'e':
		if(a==b)
		return 1;
		return 0;
		case 'f':
		if(a!=b)
		return 1;
		return 0;
		
	}
}			

//-----------------------------------------RETURNS CHARACTER PRECIDENCE------------------------------------------------------------------

int precedence(char c)
{
	switch(c)
	{
		case '*':
		case '/':
		case '%':
		return 4;
		case '+':
		case '-':
		return 3;
		case 'a':
		case 'b':
		return 2;
		case 'c':
		case 'd':
		case '<':
		case '>':
		return 1;
		case 'e':
		case 'f':
		return 0;
		case '&':
		return -1;
		case '^':
		return -2;
		case '|':
		return -3;
		
	}
	return 0;
}		
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
					
