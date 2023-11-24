#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct process{
    char name[10];
    int at,bt,tbt,tat,ct,wt;
}process;

process p[10];

int processcnt,tq,q,x;
float avgtat,avgwt,totaltat,totalwt;

void readprocess()
{
    int i;
    printf("Enter number of process:");
    scanf("%d",&processcnt);
    printf("Enter time quantum :");
    scanf("%d",&q);
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
}

int getprocess()
{
    int p1;
    if(x==processcnt)
        x=0;
    p1=x;
    x++;
    return p1;
}


void scheduleprocess()
{
    int i,cnt=0,currenttime=0;
    char currentprocesss[10],prevprocess[10]="NULL";
    printf("\n\tGantt Chart\n\n");
    printf("\n-------------------------------------------------\n");
    while(1)
    {
        tq=0;
        i=getprocess();
        if(p[i].tbt==0)
        {
            tq=q;
        }
        while(tq!=q)
        {
            p[i].tbt--;
            strcpy(currentprocesss,p[i].name);
            if(strcmp(currentprocesss,prevprocess)!=0)
            {
                printf("%d |%s",currenttime,currentprocesss);
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
            strcpy(prevprocess,currentprocesss);
            if(p[i].tbt==0 && tq!=q)
                break;
            tq++;
        }
        if(cnt==processcnt)
            break;
    }
    printf("  %d |",currenttime);
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
