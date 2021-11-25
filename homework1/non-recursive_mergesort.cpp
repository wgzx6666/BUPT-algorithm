#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<sstream>
#include<iostream>
#include<chrono>
#include<ratio>
#include<map>
using namespace std;
int a[30005];
#define num_len 20000
void mergesort(int a[],int n);
void mergepass(int x[],int y[],int s,int n);
void merge(int c[],int d[],int l,int m,int r);
int main()
{   
    string filename;
	filename="t5.txt";
    ifstream testfile;
    ofstream outfile;
    outfile.open("out55.txt",ios::out);
    testfile.open(filename, ios::in);
    if (testfile){
        
            for(int j = 0 ; j < 5 ; j++){
                for(int k = 0 ; k < num_len ; k++){
                    testfile >> a[k];
                }
                using namespace std::chrono;
                high_resolution_clock::time_point t1 = high_resolution_clock::now();
                mergesort(a,num_len);
                high_resolution_clock::time_point t2 = high_resolution_clock::now();
                cout<<"in millisecond time:";
                duration<double,std::ratio<1,1000>> duration_ms(t2-t1);
                cout<<duration_ms.count()<<" ms"<<endl;
                outfile << a[0];
                for(int k = 1 ; k < num_len ; k++){
                    outfile << " " << a[k];
                }
                outfile << "\n";
            }
        
    }
    else{
        cout << "ERROR" << endl;
    }
    testfile.close();
    outfile.close();
}
void mergesort(int a[],int n)
{
    int s=1;
    int *b = (int*)malloc(n*sizeof(int));
    while(s<n)
    {
        mergepass(a,b,s,n);
        s+=s;
        mergepass(b,a,s,n);
        s+=s;
    }
    free(b);
}
void mergepass(int x[],int y[],int s,int n)
{
    int i=0;
    while(i<=n-2*s)
    {
        merge(x,y,i,i+s-1,i+2*s-1);
        i=i+2*s;
    }
    if(i+s<n)
        merge(x,y,i,i+s-1,n-1);
    else
        for(int j=i;j<n;j++)
            y[j]=x[j];
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
