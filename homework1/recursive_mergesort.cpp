#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<sstream>
#include<vector>
#include<iostream>
#include<chrono>
#include<ratio>
using namespace std;
#define num_len 15000
int a[30005],b[30005];
int a_count=0,max_count=0;
void merge(int c[],int d[],int l,int m,int r);
void copy(int a[],int b[],int l,int r);
void mergesort(int a[],int left,int right);
int main()
{
    string filename;
	filename="t4.txt";
    ifstream testfile;
    ofstream outfile;
    outfile.open("out4.txt",ios::out);
    testfile.open(filename, ios::in);
    if (testfile){
        
            for(int j = 0 ; j < 5 ; j++){
                int *a = new int[num_len];
                for(int k = 0 ; k < num_len ; k++){
                    testfile >> a[k];
                }
                using namespace std::chrono;
                high_resolution_clock::time_point t1 = high_resolution_clock::now();
                mergesort(a,0,num_len-1);
                high_resolution_clock::time_point t2 = high_resolution_clock::now();
                cout<<"in millisecond time:";
                duration<double,std::ratio<1,1000>> duration_ms(t2-t1);
                cout<<duration_ms.count()<<" ms"<<endl;
                cout <<"recursive level:"<<max_count<<endl;
                max_count=0;
                a_count=0;
                outfile << a[0];
                for(int k = 1 ; k < num_len ; k++){
                    outfile << " " << a[k];
                }
                outfile << "\n";
                delete a;
            }
        
    }
    else{
        cout << "ERROR" << endl;
    }
    testfile.close();
    outfile.close();
}
void mergesort(int a[],int left,int right)
{
    if(left<right)
    {
        a_count++;
        int i=(left+right)/2;
        mergesort(a,left,i);//左子问题
        mergesort(a,i+1,right);//右子问题
        max_count=max(max_count,a_count);
        a_count--;
        merge(a,b,left,i,right);//合并
        copy(a,b,left,right);//复制回数组a
    }
}
void merge(int c[],int d[],int l,int m,int r)
{
    int i=l,j=m+1,k=l;
    while((i<=m)&&(j<=r))
    {
        if(c[i]<=c[j])
            d[k++]=c[i++];
        else
            d[k++]=c[j++];
    }
    if(i>m)
        for(int q=j;q<=r;q++)
            d[k++]=c[q];
    else
        for(int q=i;q<=m;q++)
            d[k++]=c[q];
}
void copy(int a[],int b[],int l,int r)
{
    for (int k=l;k<=r;k++)
        a[k]=b[k];
}