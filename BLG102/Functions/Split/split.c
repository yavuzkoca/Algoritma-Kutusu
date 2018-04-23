#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char ** explode(char *str,char c,int *size)
{
	char **result;
	int i=0;
	
	int result_size=0;
	for(int k=0;str[i]!='\0';k++)
	{
		
		if(k==0)
		{
			result=(char**)malloc(sizeof(char*)*1);
		}
		else
		{
			result=(char**)realloc(result,sizeof(char*)*(k+1));
		}
		int j;
		for(j=0;str[i]!=c&&str[i]!='\0';j++)
		{
			if(j==0)
			{
				result[k]=(char *)malloc(sizeof(char)*1);
				
			}
			else
			{
				result[k]=(char *)realloc(result[k],sizeof(char)*(j+1));
			}
			result[k][j]=str[i];	
			i++;		
		}
		if(str[i]==c)
		{
			i++;
		}
		result[k]=(char *)realloc(result[k],sizeof(char)*(j+1));
		result[k][j]='\0';
		result_size=k+1;
	}

	*size=result_size;
	return result;
}
int main()
{
	
	char *str="hello,world,i,xyz";
	
	int size;
	char** x = explode(str,',',&size);
	
	for(int m=0;m<size;m++)
	{
		printf("%s\n",x[m]);
	}
	
	return 0;
}
