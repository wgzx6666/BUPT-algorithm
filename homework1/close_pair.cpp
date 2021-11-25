#include<iostream>
#include<algorithm>
#include<cmath>
#include<string>
#include<fstream>
#include<utility>
using namespace std;
#define PI 3.141593
const double EARTH_RADIUS = 6378.137;
int coun=0;
int qw,er;//最近点对
double dis=2<<20;
struct point
{
    int NODEBID;
    double LONGITUDE;
    double LATITUDE;
    double dist;
}p[2000];
int n,temp[2000];
static double rad(double a)
{
    return  a*PI / 180.0;
}
static double GetDistance2(double lng1, double lat1, double lng2, double lat2)
{
//将对应的经纬度转化为弧度
    double radLat1 = rad(lat1);
    double radLat2 = rad(lat2);
    double radlng1 = rad(lng1);
    double radlng2 = rad(lng2);
//利用正弦余弦公式求距离
    double s = acos(cos(radLat1) * cos(radLat2) * cos(radlng1 -    radlng2) + sin(radLat1) * sin(radLat2));
    s = s * EARTH_RADIUS;
    s = s * 1000;
    if(s==0.0)
    return 2<<20;
    return s;
}
bool cmp(const point &A,const point &B)
{
    if(A.LONGITUDE==B.LONGITUDE)
        return A.LATITUDE<B.LATITUDE;
    else
        return A.LONGITUDE<B.LONGITUDE;
}
bool cmps(const int &a,const int &b)
{
    return p[a].LATITUDE<p[b].LATITUDE;
}
pair<double,pair<int,int>> merge(int left,int right)
{
    if(left==right)//为该点本身
    {
        return {dis,{left,right}};
    }
    if(left+1==right)//两点中间没有其他点
    {
        double yi=GetDistance2(p[left].LONGITUDE,p[left].LATITUDE,p[right].LONGITUDE,p[right].LATITUDE);
        if(yi!=0)
            return {yi,{left,right}};
        else
        {
            return {dis,{left,right}};
        }
    }
    int mid=(left+right)>>1;
    auto d1=merge(left,mid);
    auto d2=merge(mid+1,right);
    dis=min(d1.first,d2.first);
    if(d1.first<d2.first)
    {
        qw=d1.second.first;er=d1.second.second;
    }
    else
    {
        qw=d2.second.first;er=d2.second.second;
    }
    int k=0;
    for(int i=left;i<=right;i++)
        if(fabs(p[i].LONGITUDE-p[mid].LONGITUDE)<=dis)
            temp[k++]=i;
    sort(temp,temp+k,cmps);
    for(int i=0;i<k;i++)
        for(int j=i+1;j<k&&p[temp[j]].LATITUDE-p[temp[i]].LATITUDE<dis;j++)
        {
            if(dis>GetDistance2(p[temp[i]].LONGITUDE,p[temp[i]].LATITUDE,p[temp[j]].LONGITUDE,p[temp[j]].LATITUDE))
            {
                dis=GetDistance2(p[temp[i]].LONGITUDE,p[temp[i]].LATITUDE,p[temp[j]].LONGITUDE,p[temp[j]].LATITUDE);
                qw=temp[i];er=temp[j];
            }
        }
    return {dis,{qw,er}};
}
int main()
{
    string filename;
	filename="basedata.txt";
    ifstream testfile;
    string lineread;
    string token;
    int tmp;
    int i = 0;
    int j = 0;
    testfile.open(filename, ios::in);
    if (testfile)
    {
        getline(testfile,lineread);
        while(!testfile.eof())
        {
            testfile >> p[i].NODEBID;
            testfile >> p[i].LONGITUDE;
            testfile >> p[i].LATITUDE;
            testfile >> p[i].dist;
            i++;
        }
    }
    else
    {
        cout << "ERROR";
    }
    testfile.close();
	sort(p,p+n,cmp);
    auto x=merge(0,1032);
    cout << x.first << " " << p[x.second.first].NODEBID << " " << p[x.second.second].NODEBID << endl;
    return 0;
}