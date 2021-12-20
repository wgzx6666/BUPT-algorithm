#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>
#include<map>
#include<cmath>
#include<cstring>
#include<stack>

using namespace std;

const int N=42;//基站数
double dist[50];//节点到起点距离
double graph[50][50];//邻接矩阵
int path[50]={-1};
bool jud[50];//节点是否确定了最小距离
stack <int> pa;

void input();
void dijkstra(int a);

int main()
{
    input();
    dijkstra(20);
    for(int i=1;i<=N;i++)
    {
        cout << dist[i] << " ";
        pa.push(i);
        int p=i;
        while(path[p]!=0)
        {
            pa.push(path[p]);
            p=path[p];
        }
        while(pa.size()>0)
        {
            if(pa.size()==1)
            {
                cout << pa.top();
                pa.pop();
                break;
            }
            cout << pa.top() << "->";
            pa.pop();
        }
        cout << endl;
    }
    
    return 0;
}
void input()
{
    string filename;
    filename="matrix2.txt";
    ifstream fin(filename,ios::in);
    for(int i=0;i<=N;i++)
    {
        for(int j=0;j<=N;j++)
        {
            double temp;
            fin >> temp;
            if(temp==-1)
                temp=100000.0;//cout << temp <<endl;}
            graph[i][j]=temp;
        }
    }
}
void dijkstra(int a)//参数为起点标号
{
    for(int i=0;i<=N;i++)
        dist[i]=100000.0;
    dist[a]=0;
    for(int i=N;i>0;i--)//n个点
    {
        int t=-1;
        for(int i=1;i<=N;i++)
        {
            if(jud[i]==false&&(t==-1||dist[t]>dist[i]))
            {
                t=i;
            }
        }
        jud[t]=true;
        for(int i=1;i<=N;i++)
        {
            if(jud[i]==false)
            {
                if(dist[i]>(dist[t]+graph[t][i]))
                {
                    dist[i]=dist[t]+graph[t][i];
                    path[i]=t;
                }
            }
        }
    }
}