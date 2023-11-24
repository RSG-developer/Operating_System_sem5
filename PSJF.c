#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct process
{
    char name[10];
    int at,bt,ct,tat,wt,tbt;
}process;

process p[10];

int processcnt,currenttime;

float totalwt,totaltat,avgtat,avgwt;



void readprocess()
{
    int i;
    printf("Enter number of process:");
    scanf("%d",&processcnt);
    for(i=0;i<processcnt;i++)
    {
        printf("Enter process name:");
        scanf("%s",&p[i].name);
        printf("Enter arrival time:");
        scanf("%d",&p[i].at);
        printf("Enter the burst time:");
        scanf("%d",&p[i].bt);
        p[i].tbt=p[i].bt;
    }
}

int getprocess()
{
    int i=0,min=999,p1=-1;
    for(i=0;i<processcnt;i++)
    {
        if(p[i].at <= currenttime && p[i].tbt!=0)
        {
            if(p[i].bt < min)
            {
                min=p[i].bt;
                p1=i;
            }
        }
    }
    return p1;
}

void scheduleprocess()
{
    int i=0,cnt=0;
    char currentprocess[10],prevprocess[10]="NULL";
    printf("\nGantt Chart\n");
    printf("\n------------------------------------------------\n");
    while(1)
    {
        i=getprocess();
        if(i==-1)
        {
            strcpy(currentprocess,"idle");
            if(strcmp(currentprocess,prevprocess)!=0)
            {
                printf("%d %s",currenttime,currentprocess);
            }
            strcpy(prevprocess,currentprocess);
            currenttime++;
        }
        else
        {
            p[i].tbt--;
            strcpy(currentprocess,p[i].name);
            if(strcmp(currentprocess,prevprocess)!=0)
            {
                printf("%d %s |",currenttime,currentprocess);
            }
            currenttime++;
            if(p[i].tbt==0)
            {
                p[i].ct=currenttime;
                p[i].tat=p[i].ct-p[i].at;
                p[i].wt=p[i].tat-p[i].bt;
                cnt++;
                totaltat+=p[i].tat;
                totalwt+=p[i].wt;
            }
            strcpy(prevprocess,currentprocess);
            if(cnt==processcnt)
                break;
        }
        
    }
    printf(" %d |",currenttime);
    avgtat=totaltat/processcnt;
    avgwt=totalwt/processcnt;

}

void displayprocess()
{
    int i;
    printf("\n--------------------------------------------------\n");
    printf("\nName  Arrival  Burst  CPU  WAiting  Turn Around");
    for(i=0;i<processcnt;i++)
    {
        printf("\n%s\t%d\t%d\t%d\t%d\t%d",p[i].name,p[i].at,p[i].bt,p[i].ct,p[i].wt,p[i].tat);
    }
    printf("\nTotal waiting time is %f",totalwt);
    printf("\nTotal turn around time is %f",totaltat);
    printf("\nAverage turn Around time is %f",avgtat);
    printf("\nAverage waiting time is %f",avgwt);
}

void main()
{
    readprocess();
    scheduleprocess();
    displayprocess();
}