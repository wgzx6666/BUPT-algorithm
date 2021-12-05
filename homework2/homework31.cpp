#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
#include<cmath>
#include<iomanip>

using namespace std;
#define PI 3.141593
const double EARTH_RADIUS = 6378.137;
int w[30][30]/*记录边和弦权值*/,dp[30][30]/*记录子问题最优值*/,s[30][30]/*记录子问题最优划分点*/,sum=0,m[30][30]={0}/*记录弦是否计算过*/;
vector <double> longitude,latitude,value;
vector <int> num;
void putin();
void Triangulation();
static double rad(double a);
static double GetDistance(double lng1, double lat1, double lng2, double lat2);
int weight(int a,int b,int c);
void traceback(int a,int b);
int main()
{
    putin();
    Triangulation();
    return 0;
}
void putin()
{
    string filename,temp;
    filename="test32.txt";
    ifstream fin;
    int x;
    double y;
    fin.open(filename,ios::in);
    if(fin)
    {
        getline(fin,temp);
        while(!fin.eof())
        {
            fin >> x;
            num.push_back(x);
            fin >> y;
            longitude.push_back(y);
            fin >> y;
            latitude.push_back(y);
            fin >> x;
        }
    }
    else
    {
        cout << "ERROR";
    }
}
void Triangulation()
{
    int n=num.size()+1;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==j)
            {
                w[i][j]=0;
                continue;
            }
            w[i][j]=GetDistance(longitude[i],latitude[i],longitude[j],latitude[j]);
        }
    }
    for(int i=1;i<=n;i++)
    {
        dp[i][i]=0;
    }
    for(int len=2;len<=n;len++)//区间长度
    {
        for(int i=1;i<=n-len+1;i++)//区间起点
        {
            int j=i+len-1;//区间终点
            dp[i][j]=dp[i+1][j]+weight(i-1,i,j);
            s[i][j]=i;
            for(int k=i+1;k<j;k++)
            {
                int u=dp[i][k]+dp[k+1][j]+weight(i-1,k,j);
                if(u<dp[i][j])
                {
                    
                    dp[i][j]=u;
                    s[i][j]=k;
                }
                
            }
        }
        
    }
    cout << dp[1][n-2] << endl;
    traceback(1,n-2);
    cout << sum << endl;
}
static double rad(double a)
{
    return  a*PI / 180.0;
}
static double GetDistance(double lng1, double lat1, double lng2, double lat2)
{
//将对应的经纬度转化为弧度
    double radLat1 = rad(lat1);
    double radLat2 = rad(lat2);
    double radlng1 = rad(lng1);
    double radlng2 = rad(lng2);
//利用正弦余弦公式求距离
    double s = acos(cos(radLat1) * cos(radLat2) * cos(radlng1 - radlng2) + sin(radLat1) * sin(radLat2));
    s = s * EARTH_RADIUS;
    s = s * 1000;
    if(s==0.0)
    return 2<<20;
    return s;
}
int weight(int a,int b,int c)
{
    return w[a][b]+w[b][c]+w[a][c];
}
void traceback(int a,int b)
{
    if(a==b)
        return;
    int c=s[a][b];
    traceback(a,c);
    traceback(c+1,b);
    a-=1;
    
    if(m[a][b]==0)
    {
        sum+=w[a][b];
        m[a][b]=1;
        cout << longitude[a] << " " << latitude[a] << " and ";
        cout << longitude[b] << " " << latitude[b] << endl;
    }
    if(m[a][c]==0)
    {
        sum+=w[a][c];
        m[a][c]=1;
        cout << longitude[a] << " " << latitude[a] << " and ";
        cout << longitude[c] << " " << latitude[c] << endl;
    }
    if(m[c][b]==0)
    {
        sum+=w[b][c];
        m[c][b]=1;
        cout << longitude[c] << " " << latitude[c] << " and ";
        cout << longitude[b] << " " << latitude[b] << endl;
    }
}