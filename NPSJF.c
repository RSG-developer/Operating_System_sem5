#include<stdio.h>
#include<stdlib.h>

typedef struct process
{
    char name[10];
    int at,wt,ct,tbt,tat,bt;
}process;

process p[10];
int processcnt,currenttime;
float totalwt,totaltat,avgwt,avgtat;

void sort()
{
    int i,j;
    process temp;
    for(i=0;i<processcnt;i++)
    {
        for(j=0;j<processcnt-i-1;i++)
        {
            if(p[j].at > p[j+1].at)
            {
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
}

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
        printf("Enter burst time:");
        scanf("%d",&p[i].bt);
        p[i].tbt=p[i].bt;
    }
    sort();
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
    int i,cnt=0;
    printf("Gannt Chart");
    while(1)
    {
        i=getprocess();
        if(i==-1)
        {
            printf("%d idle",currenttime);
            currenttime=p[cnt].at;
            printf("%d |",currenttime);
        }
        else{
            printf("%d  ",currenttime);
            p[i].wt=currenttime-p[i].at;
            currenttime=currenttime+p[i].bt;
            p[i].ct=currenttime;
            p[i].tat=p[i].wt+p[i].bt;
            totaltat+=p[i].tat;
            totalwt+=p[i].bt;
            p[i].tbt=0;
            printf("%s",p[i].name);
            printf("%d",currenttime);
            i++;
            cnt++;
            if(cnt==processcnt)        
                break;
            }
    }
    avgtat=totaltat/processcnt;
    avgwt=totalwt/processcnt;
}

void displayprocess()
{
    printf("\nName\tArrival\tBurst\tCPU\tWaiting\tTurnAround\n");
    for(int i=0;i<processcnt;i++)
    {
        printf("\n%s\t%d\t%d\t%d\t%d\t%d",p[i].name,p[i].at,p[i].bt,p[i].ct,p[i].wt,p[i].tat);
    }

    printf("\nTotal turn aroundtime is %f",totaltat);
    printf("\nAverage Turn Around time : %f",avgtat);
    printf("\nTotal Waiting time is %f",totalwt);
    printf("\nAverage Turn Waiting time  : %f",avgwt);
}

void main()
{
    readprocess();
    scheduleprocess();
    displayprocess();
}