#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>

using namespace std;

vector <int> num,rec;
int x=0,y=0,xx=0,yy=0,coun=-2147483648;
int rec1,rec2;

void putin();
void subsegmentsum();

int main()
{
    putin();
    subsegmentsum();
    return 0;
}
void putin()
{
    string filename,temp;
    filename="test21.txt";
    ifstream fin(filename,ios::in);
    while(getline(fin,temp))
    {
        num.push_back(atoi(temp.c_str()));
    }
}
void subsegmentsum()
{
    for(int i=0;i<num.size();i++)
    {
        rec1=rec2;
        if(i==0)
        {
            rec1=num[i];
        }
        else
        {
            if(num[i]<(num[i]+rec1))
            {
                rec2=num[i]+rec1;
                yy++;
            }
            else
            {
                rec2=num[i];
                xx=i;
                yy=i;
            }
        }
        if(rec2>coun)
        {
            coun=rec2;
            x=xx;
            y=yy;
        }
    }
    cout << coun << endl;
    cout << "start:serial number:" << x+1 << " value:" << num[x] << endl;
    cout << "end:  serial number:" << y+1 << " value:" << num[y] << endl;
}