#include<iostream>
#include<stdlib.h>
#include<iomanip>
#include<queue>
using namespace std;
int checkarrival(int t[50][3],int n)
{
    int i;
    while(i<n-1)
    {
        if(t[i][1]!=t[i+1][1])
            break;
        i++;
    }
    if(i==n-1)
        return 1;
    else
        return 0;
}
void rndrbin(int tab[50][3],int n,int tq)
{
    queue<int>q;
    int time,temp,id;
    int droptime[n],rt[n];
    int wt[n],tat[n];
    for(int i=0;i<n;i++)
        wt[i]=0;
    for(int i=0;i<n;i++)
        rt[i]=tab[i][2];
    for(int i=0;i<n;i++)
        droptime[i]=0;
    int samearrival;
    samearrival=checkarrival(tab,n);
    if(samearrival==1)
    {
       for(int i=0;i<n;i++)
            q.push(i);
    }
    else
    {
        for(int i=0;i<n;i++)
            for(int j=0;j<n-i-1;j++)
            {
                if(tab[j][1]>tab[j+1][1])
                {
                    swap(tab[j][0],tab[j+1][0]);
                    swap(tab[j][1],tab[j+1][1]);
                    swap(tab[j][2],tab[j+1][2]);
                }
            }
        for(int i=0;i<n;i++)
            q.push(tab[i][0]);
    }
       temp=q.front();
       q.pop();
       time=tab[temp][1]+tq;
       droptime[temp]=time;
       rt[temp]=rt[temp]-tq;
       q.push(temp);
       while(!q.empty())
       {
           id=q.front();
           q.pop();
           if(rt[id]<=tq)
           {
               wt[id]=wt[id]+(time-droptime[id]);
               time=time+rt[id];
               tat[id]=time-tab[id][1];
               rt[id]=0;
           }
           else
                if(rt[id]>tq)
                {
                    rt[id]=rt[id]-tq;
                    wt[id]=wt[id]+(time-droptime[id]);
                    time=time+tq;
                    droptime[id]=time;
                    q.push(id);
                }
       }
    cout<<"----------------------------------------------------------------------"<<endl;
    cout<<"process      arrival      burst      waiting-time      turnaround-time"<<endl;
    cout<<"----------------------------------------------------------------------"<<endl;
    for(int a=0;a<n;a++)
        cout<<left<<setw(13)<<tab[a][0]<<left<<setw(13)<<tab[a][1]<<left<<setw(11)<<tab[a][2]<<left<<setw(18)<<wt[a]<<setw(15)<<tat[a]<<endl;
    cout<<"----------------------------------------------------------------------"<<endl;
    int twt=0,tt=0;
    for(int i=0;i<n;i++)
    {
        twt=twt+wt[i];
        tt=tt+tat[i];
    }
    cout<<endl<<"Average waiting time:"<<(float)twt/(float)n<<endl<<endl<<"Average turn-around time:"<<(float)tt/(float)n<<endl;
}
int main()
{
    int n,quantum;
    cout<<"Enter the number of processes:";
    cin>>n;
    cout<<"Enter the time quantum:";
    cin>>quantum;
    int table[n][3];
    for(int i=0;i<n;i++)
    {
       table[i][0]=i;
    }
    cout<<"Enter the arrival times of the processes"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"P["<<i<<"]=";
        cin>>table[i][1];
    }
    cout<<"Enter the burst times:"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"P["<<i<<"]=";
        cin>>table[i][2];
    }
    rndrbin(table,n,quantum);
}
