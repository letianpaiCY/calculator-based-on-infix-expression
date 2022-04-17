#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<iostream>
#include<windows.h>
using namespace std;
#define n 30
//�Զ�������ջ�����������׺���ת����׺�����㷨 
typedef struct stack
{
	int a[n];
	int top;
}ST;

int empty(ST *T)
{
	if (T->top < 0)
		return 1;
	else
		return 0;
}//�ж�ջ�Ƿ�Ϊ��

int full(ST *T)
{
	if (T->top == n - 1)
		return 1;
	else
		return 0;
}//�ж�ջ��

int gettop(ST* T)
{
	return T->a[T->top];
}//�õ�ջ��Ԫ��

int pop(ST* T)
{
	int x;
	if (T->top < 0)//��ջΪ��
	{
		printf("ջ�գ��޷���ջ\n");
		exit(0);
	}
	else
	{
		x = T->a[T->top];
		(T->top)--;
		return x;
	}
}//Ԫ�س�ջ

void push(ST* T, int a)
{
	if (T->top == n - 1)
	{
		printf("ջ�����޷���ջ,�������Ҫ�����������µ���n��ֵ������ջ\n");
		exit(0);
	}
	else
	{
		(T->top)++;
		T->a[T->top] = a;
	}
}//Ԫ����ջ��

void translation(char* in, char* out)//��׺ת��׺
{
	ST T;//����һ��ջ��
	int i, j;
	int mark = 0;
	int count;//mark,pcount�������ӳ����³���ԣ��ж������Ƿ�Ϸ���
	int l=0,r=0;//l.f��¼����ı��ʽ����������
	T.top=-1;
	for (i = 0, j = 0; in[i] != '\0'; i++)//����i++,�������i--����Ӧ�� 
	{
		switch (in[i])
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':for (count = 0; (in[i] <= '9' && in[i] >= '0') || in[i] == '.'; i++, j++)
		{
			out[j] = in[i];
			if (in[i] == '.') //��¼С������ֵĸ��� 
				count++;
		}
				i--;//���жϵ����ŵ�λ�õ�ʱ�� ������ѭ����
				if (count > 1)
				{
					printf("\n���ʽ�д���������С���㣬�������������!!!\n\n");
					exit(0);
				}
				out[j] = ' ';//�ÿո����ָ������� 
				j++;
				mark = 1;  //ĿǰΪ���֣���flagΪ1 
				break;
		case '(':if (mark==1)//�������ǰ�����֣�����ʽ���� 
		{
			printf("\n����ǰȱ����������������������!!!\n\n");
			exit(0);
		}
				push(&T, in[i]);
				l++;//�����Ÿ�����һ 
				break;
		case ')':r++;   //�����Ÿ�����һ 
			while (gettop(&T) != '(')
			{
				out[j] = pop(&T);
				j++;
			}//���������Ź۲�ջ��Ԫ���Ƿ�Ϊ�����ţ����Ǿ͵�����Ϊ��׺���ʽ 
			pop(&T);//���������� ����ʱ�������Ų������׺���ʽ����׺���ʽ�в��������� 
			break;
		case '+':
		case '-':if (!mark && i != 0)//��������ǰ�������������ʽ����
		//���ջ��Ϊ��������ּ���һ���µ������������i��=0��Ϊ���ж��ǲ��Ǹ��� 
		{
			printf("\n����������������������������������\n");
			exit(0);
		}
				while (!empty(&T) && gettop(&T) != '(')//ֻҪջ��Ԫ�ز�������������+-ʱջ��Ԫ�ض�Ҫ��ջ 
				{
					out[j] = pop(&T);
					j++;
				}
				push(&T, in[i]);
				mark = 0;//ĿǰΪ���ţ�����flagΪ0 
				break;
		case '*':
		case '/':if (!mark)//��������ǰ�������������ʽ���� 
		{
			printf("\n����������������������������������\n");
			exit(0);
		}
				while (!empty(&T) && (gettop(&T) == '/' || gettop(&T) == '*'))//ֻҪջ��Ԫ�غ��Լ�ͬ����ͳ�ջ�����׺���ʽ 
				{
					out[j] = pop(&T);
					j++;
				}
				push(&T, in[i]);
				mark = 0;
				break;
		default:printf("\n������ʽ���Ϸ����������������\n");
			exit(0);
		}
	}
	if (l != r)
	{
		printf("\n�������Ų�ƥ�䣬�������������\n");
		exit(0);
	}
	while (!empty(&T))
	{
		out[j] = pop(&T);
		j++;
	}
	out[j] = '\0'; 
}

float jisuan(char *out)//��׺���ʽ���� 
{
	int i,j ,top=-1,point;//point �ж��������Ƿ���С���� 
	int len;
	float temp,num[n];
	char ch[n];
	for(i=0,j;out[i]!='\0';i++)
	{
		if(out[i]>='0'&&out[i]<='9')//��ǰΪ���֣��Ѱ�char����ת��Ϊ�ɼ�������� 
		{
		point=0;
		j=0;
		while(out[i]!=' ')
		{
			if(out[i]=='.')
			point = 1;
			ch[j]=out[i];
			i++;
			j++;
	    }
		 ch[j]='\0';
		 if(point)
		 {
		 	for(j=0;ch[j]!='.';j++);//���󳤶ȣ��ҵ�j��λ�ã���ô����Ϊj-1 
					len=j-1;
				for(j=0,temp=0.;ch[j]!='.';j++)  //����С����ǰ�ĺ�
					temp+=(ch[j]-'0')*pow(10,len-j);
				for(j++,len++;ch[j]!='\0';j++)   //����С����ǰ�ĺ�
					temp+=(ch[j]-'0')*pow(10,len-j);
	     }
	    else//������С���� 
	    {
		    for(j=0;ch[j]!='\0';j++);//�����Ӧ�ĳ��� 
					len=j-1;
				for(j=0,temp=0.;ch[j]!='\0';j++)
					temp+=(ch[j]-'0')*pow(10,len-j);
	    }
	     top++;
	    num[top]=temp;
       }   
    else
	{
		switch(out[i])
		{
			case'+':temp=num[top];
			top--;
			temp=temp+num[top];
			num[top]=temp;//�����������ջ 
			break;
			case'-':temp=num[top];
			top--;
			temp=num[top]-temp;
			num[top]=temp;
			break;
			case'*':temp=num[top];
			top--;
			temp=temp*num[top];
			num[top]=temp;
			break;
			case'/':temp=num[top];
			top--;
			temp=num[top]/temp;
			num[top]=temp;
		}	
	}
	}
	return num[top];
}

int main()
{

	char mid[n],last[n];
	float daan=0;
	system("color f0");
	printf("��������������������������ӭʹ�ñ�������������������������������\n");
	printf("�������������������������ƿ�2001   ������������������������������\n\n") ;
	Sleep(1000);
	printf("��������Ҫ����ı��ʽ��(����ʱע����ʽ�Ƿ���ȷ,���롮# ���Խ�������ʹ��)��\n");
	scanf("%s",mid);
	while(1)
	{
		if(strcmp(mid,"#")==0)
		{
			printf("ллʹ��\n");
			break;
		}
		translation(mid,last);
		daan=jisuan(last);
		printf("%s = %5f\n",mid,daan);
	    printf("��������Ҫ����ı��ʽ��(����ʱע����ʽ�Ƿ���ȷ)��\n");
		scanf("%s",mid);
	}
	return 0;
}




