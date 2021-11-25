#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
using namespace std;

int n,m,max_weight=0,dp[105][1005];
bool record[105][1005]={false};//记录路径
vector<int>weight,value;
bool put[205];
void putin();
int main()
{
    putin();//01378 045810
    m=weight.size();
    for(int i=1;i<=m;i++)
    {
        for(int j=n;j>=0;j--)
        {
            if(j>=weight[i-1])
            {
                int x=dp[i-1][j-weight[i-1]]+value[i-1];
                int y=dp[i-1][j];
                if(x>y)
                {
                    dp[i][j]=x;
                    record[i][j]=true;
                }
                else
                {
                    dp[i][j]=y;
                    record[i][j]=false;
                }
            }
            else
            {
                dp[i][j]=dp[i-1][j];
            }
        }
    }
    for(int i=m,j=n;i>0&&j>0;i--)
    {
        if(record[i][j]==true)
        {
            put[i]=true;
            j-=weight[i-1];
        }
        else
        {
            put[i]=false;
        }
    }
    for(int i=1;i<=m;i++)
    {
        if(put[i])
        {
            max_weight+=weight[i-1];
            cout << "The id is:" << i << " the weight is:" << weight[i-1] << " the value is:" << value[i-1] << endl;
        }
    }
    cout << "The maximum weight is:" << max_weight << endl;
    cout << "The maximum value is:" << dp[m][n] << endl;
}
void putin()//输入
{
    string filename;
    filename="test42.txt";
    ifstream fin(filename,ios::in);
    string temp,token;
    getline(fin,temp);
    n=atoi(temp.c_str());//读取背包容量
    getline(fin,temp);
    for(auto it=temp.begin();it!=temp.end();it++)
    {
        if(*it!=' ')
        {
            token+=*it;
        }
        else
        {
            weight.push_back(atoi(token.c_str()));
            token.clear();
        }
    }
    getline(fin,temp);
    for(auto it=temp.begin();it!=temp.end();it++)
    {
        if(*it!=' ')
        {
            token+=*it;
        }
        else
        {
            value.push_back(atoi(token.c_str()));
            token.clear();
        }
    }
}