#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>

using namespace std;

vector <int> num;
int d[500][500];

void putin();
void diminish();//最长递减子序列
int main()
{
    putin();
    diminish();
    return 0;
}
void putin()
{
    string filename,temp;
    filename="test22.txt";
    ifstream fin(filename,ios::in);
    while(getline(fin,temp))
    {
        num.push_back(atoi(temp.c_str()));
    }
}
void diminish()
{
    vector <int> temp(num);
    sort(temp.begin(),temp.end(),greater<int>());//递减排序
    for(int i=0;i<=num.size();i++)
    {
        for(int j=0;j<=temp.size();j++)
        {
            if(i==0||j==0)
            {
                d[i][j]=0;
            }
            else if(num[i-1]==temp[j-1])
            {
                d[i][j]=d[i-1][j-1]+1;
            }
            else
            {
                d[i][j]=max(d[i][j-1],d[i-1][j]);
            }
        }
    }
    // cout << d[num.size()][num.size()] << endl;
    vector <int> rresult;
    int x=num.size()-1,y=num.size()-1;
    while(x>=0&&y>=0&&d[x+1][y+1]>0)
    {
        if(num[x]==temp[y])
        {
            rresult.push_back(num[x]);
            x--;
            y--;
        }
        else
        {
            if(d[x+1][y]>d[x][y+1])
            {
                y--;
            }
            else
            {
                x--;
            }
        }
    }
    cout << "total number is:" << rresult.size() << endl;
    for(int i=rresult.size()-1;i>=0;i--)
    {
        cout << rresult[i] << endl;
    }
}