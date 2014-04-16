#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXLINE 4096

int main()
{
	int n,int1,int2;
	char line[MAXLINE];

	while((n = read(STDIN_FILENO,line,MAXLINE)) > 0)
	{
		line[n] = 0;
		if(sscanf(line,"%d%d",&int1,&int2) == 2)
		{
			sprintf(line,"%d\n",int1+int2);
			n = strlen(line);

			if(write(STDOUT_FILENO,line,n) != n)
			{
				printf("write error\n");
			}
		}
		else
		{
			if(write(STDOUT_FILENO,"invalid args\n",13) != 13)
			{
				printf("write error\n");
			}
		}
	}

	return 0;
}
