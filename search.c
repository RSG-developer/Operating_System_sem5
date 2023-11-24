#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

void make_tokens(char *s,char *tok[])
{
    int i=0;
    char *p;
    p=strtok(s," ");
    while(p!=NULL)
    {
        tok[i++]=p;
        p=strtok(NULL," ");

    }
    tok[i]=NULL;
}

void search(char *filename,char option,char *patern)
{
    int fh,count=0,i=0,j=0;
    char buff[225],c,*p;
    fh=open(filename,O_RDONLY);
    if(fh==-1)
    {
        printf("Error occured ");
        return;
    }
    switch(option)
    {
        case 'f':
            while(read(fh,&c,1))
            {
                buff[j++]=c;
                if(c=='\n')
                {
                    buff[j]='\0';
                    j=0;
                    i++;
                    if(strstr(buff,patern))
                    {
                        printf("%d %s",i,buff);
                        break;
                    }
                }
            }
            break;
            case 'a':
                while(read(fh,&c,1))
                {
                    buff[j++]=c;
                    if(c=='\n')
                    {
                        buff[j]='\0';
                        p=buff;
                        j=0;
                        while((p=strstr(p,patern))!=NULL)
                        {
                            count++;
                            p++;
                        }
                    }
                    printf("total occurance %d",count);
                }
                break;
            case 'c':
                while(read(fh,&c,1))
                {
                    buff[j++]=c;
                    if(c=='\n')
                    {
                        j=0;
                        i++;
                        if(strstr(buff,patern))
                        {
                            printf("%d %s ",i,buff);
                        }
                    }
                } 
                break;
    }
    close(fh);
}

void main()
{
    int cmd[80],*args[10];
    int pid;
    while(1)
    {
        printf("myshell $");
        fflush(stdin);
        fgets(cmd,80,stdin);
        cmd[strlen(cmd)-1]='\0';
        make_tokens(cmd,args);

        if(strcmp(args[0],"search")==0)
            search(args[3],args[1][0],args[2]);
        else{
            pid=fork();
            if(pid>0)
                wait(NULL);
            else
            {
                if(execvp(args[0],args)==-1)
                    printf("Bad commands");

            }

        }
    }
}