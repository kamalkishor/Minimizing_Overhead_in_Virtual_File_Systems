/***********************************************
*	Kamal Kishor Sharma y10uc139
*	Rachit Mathur y10uc245
*	Pankaj Gupta y10uc208
*    OS Project Code for file storage management
*
************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<time.h>
#include<string.h>
int inode=1,me=0,at=0;
int sind=1072717824,da=450561,frees=409601; //global variables
char co=' ';
FILE *fp;
void read(FILE *fp1)// To read file data from data space
{
	int a,b,c,d,e;
	char g,namre[15],m,re[100];
	printf("\nEnter the name of the file with extension you want to read\n");
	g=getchar();
	gets(namre);
	printf("Enter no.of characters you want to read\n");
	scanf("%d",&e);
	a=search_f(namre);
	if(a==1)
	{
		printf("\nFile does not exist\n");
	}
	else
	{
		fseek(fp1,a+31,0);
		fread(&m,1,1,fp1);
		if(m=='w')
		{
			printf("\nUser has write only permisssion so can't read\n");
		}
		else
		{
			fseek(fp1,a+26,0);
			b=getw(fp1);
			fseek(fp1,b,0);
			c=getw(fp1);
			if(c==0)
			printf("\nFile is empty\n");
			else
			{
			fseek(fp1,c,0);
			fread(re,e,1,fp1);
			printf("%s\n",re);
			}
		}	

	}
	
	
	
}

void stat(FILE *fp1) // To give information about file metadata
{
	int a,in,size,sind;
	char g,fnam[15],m;
	printf("\nEnter the filename with extension for which you want to get information\n");
	g=getchar();
	gets(fnam);
	a=search_f(fnam);
	if(a==1)
	{
		printf("\nFile does not exist\n");
	}
	else
	{
		fseek(fp1,a,0);
		in=getw(fp1);
		printf("Inode No: %d\n",in);
		printf("File Name: %s\n",fnam);
		fseek(fp1,17,1);
		size=getw(fp1);
		printf("File Size: %d\n",size);
		fseek(fp1,1,1);
		sind=getw(fp1);
		printf("Single Indirect block Address: %d\n",sind);
		fseek(fp1,1,1);
		fread(&m,1,1,fp1);
			if(m=='s')
			printf("Read and write permission\n");
			if(m=='r')
			printf("Read only permission\n");
			if(m=='w')
			printf("Write only permission\n");
	}
	return;
}		 


int search_f(char com[15]) // To find location of metadata for a particular file
{	
	int d=1,e=307201;
	char bu[15]="mm";	
	fseek(fp,307201,0);
	while(strcmp(bu,com)!=0 && e<=409600)
	{
		fscanf(fp,"%s",bu);	
		if(strcmp(bu,com)==0)
		{
			fseek(fp,1,1);
			d=getw(fp);
			return d;
		}
		else
		{
		fseek(fp,5,1);
		e=e+21;
	}
	}
		if(d==1)
		return d;
	
}

void write(FILE *fp1) // To write data at the dataspace for a file
{
	int a,u,si,free_point,da2=1,siz;
	char cm[15],g,h,inpdat[100],m,c;
	printf("\nEnter the file name with extension you want to write in\n");
	g=getchar();
	gets(cm);
	a=search_f(cm);
	if(a==1)
	printf("\nFile does not exist\n");
	else
	{
		fseek(fp1,a+31,0);
		fread(&m,1,1,fp1);
		if(m=='r')
		{
			printf("\nUser has read only permisssion so can't write\n");
		}
		else
		{	
			fseek(fp1,a+26,0);
			si=getw(fp1);
			fseek(fp1,frees,0);
	
	while(da2!=0)
	{       
         	da2=getw(fp1);
		printf("\n%d\n",da2);
		if(da2==0)
		{
			fseek(fp1,-4,1);
                        putw(da,fp1);
			//fseek(fp1,frees,0);
			//u=getw(fp1);
			//printf("%d",u);
			//fseek(fp1,4,1);
                        fwrite(&co,1,1,fp1);
      		}
		else
		{		
			fseek(fp1,frees+4,1);
			da=da+102400;	
		}
	}
	        fseek(fp1,si,0);
		putw(da,fp1);
		fwrite(&co,1,1,fp1);
		//printf("%d",da);
		fseek(fp1,da,0);
		printf("\nEnter the data you want to put in a file\n");
		h=getchar();
		gets(inpdat);
		siz=strlen(inpdat);
		fwrite(inpdat,100,1,fp1);
		fseek(fp1,a+21,0);
		putw(siz+1,fp1);
		
		}
	}		
}
		
void create(FILE *fp1) // To create files with their name, extension and permission
{
	int n,q;
	char nam[15],g;
	int size=0;
	
	char m;
	char tim[27];
	//time_t clock = time(NULL);
	//strcpy(tim,ctime(&clock));
	g=getchar();
	printf("\nEnter the name of file with extension\n");
	gets(nam);
	
	printf("Enter one of the choices: \n1.  user  has read and write  permission\n2.  user has read permission\n3.user has write permission \n");
	scanf("%d",&q);
	
	switch(q)
	{
		case 1:
		m='s';
		break;
		case 2:
		m='r';
		break;
		case 3:
		m='w';
		break;
		default:
		printf("\nEnter a given value");
	}
	
	fseek(fp,me,0);
	putw(inode,fp1);
	fwrite(&co,1,1,fp1);
	fwrite(nam,15,1,fp1);
	fwrite(&co,1,1,fp1);
	putw(size,fp1);
	fwrite(&co,1,1,fp1);
	putw(sind,fp1);
	fwrite(&co,1,1,fp1);
	fwrite(&m,1,1,fp1);
	fwrite(&co,1,1,fp1);
	//fwrite(tim,27,1,fp1);
	
	fseek(fp,307201+at,0);
	fwrite(nam,15,1,fp1);
	fwrite(&co,1,1,fp1);
	putw(me,fp);
	fwrite(&co,1,1,fp1);
	
	me=me+33;
	at=at+21;
	sind=sind+10240;
	inode++;
        return ;
}


int main()
{
 int choice;
 fp=fopen("file_system.txt","r+");
 do{
         printf("Choose the function \n 1.Create\n 2.Read\n 3.Write\n 4.File information\n    5.Exit\n");
         scanf("%d",&choice);

	switch(choice)
	{
		case 1:	create(fp);
			break;
		case 2:	read(fp);
			break;
		case 3:	write(fp);
			break;
		case 4: stat(fp);
			break;
		case 5: exit(0);
			break;
		default: printf("Enter a valid choice\n");
	}
}while(choice!=5);

return 0;
}
