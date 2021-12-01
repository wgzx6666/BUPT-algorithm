#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>

using namespace std;

string string_a,string_b,string_c,string_d;
int c[1100][1100],d[1100][1100];

void putin();
void sub_seq(string& a,string& b);//最长公共子序列
void sub_str(string& a,string& b);//最长公共子串
int main()
{
    putin();
    sub_seq(string_a,string_b);
    sub_str(string_b,string_d);
    return 0;
}
void putin()
{
    string filename;
    filename="test1.txt";
    ifstream fin(filename,ios::in);
    getline(fin,string_a);
    getline(fin,string_b);
    getline(fin,string_c);
    getline(fin,string_d);
}
void sub_seq(string& a,string& b)
{
    string rresult;
    for(int i=0;i<=a.size();i++)
    {
        for(int j=0;j<=b.size();j++)
        {
            if(i==0||j==0)
            {
                c[i][j]=0;
            }
            else if(a.at(i-1)==b.at(j-1))
            {
                c[i][j]=c[i-1][j-1]+1;
            }
            else
            {
                c[i][j]=max(c[i][j-1],c[i-1][j]);
            }
        }
    }
    // cout << c[a.size()][b.size()] << endl;
    int x=a.size()-1,y=b.size()-1;
    while(x>=0&&y>=0&&c[x+1][y+1]>0)
    {
        if(a.at(x)==b.at(y))
        {
            rresult+=a.at(x);
            x--;
            y--;
        }
        else
        {
            if(c[x+1][y]>c[x][y+1])
            {
                y--;
            }
            else
            {
                x--;
            }
        }
    }
    string result(rresult.rbegin(),rresult.rend());
    cout << result << endl;
}
void sub_str(string& a,string& b)
{
    string rresult;
    int max_count=0,recx=0,recy=0;
    for(int i=0;i<=a.size();i++)
    {
        for(int j=0;j<=b.size();j++)
        {
            if(i==0||j==0)
            {
                d[i][j]=0;
            }
            else if(a.at(i-1)==b.at(j-1))
            {
                d[i][j]=d[i-1][j-1]+1;
                if(d[i][j]>max_count)
                {
                    max_count=d[i][j];
                    recx=i;
                    recy=j;
                }
            }
            else
            {
                d[i][j]=0;
            }
        }
    }
    cout << max_count << " " << recx << " " << recy << endl;
    int x=recx-1,y=recy-1;
    while(x>=0&&y>=0&&d[x+1][y+1]>0)
    {
        if(a.at(x)==b.at(y))
        {
            rresult+=a.at(x);
            x--;
            y--;
        }
        else
        {
            break;
        }
    }
    string result(rresult.rbegin(),rresult.rend());
    cout << result << endl;
}