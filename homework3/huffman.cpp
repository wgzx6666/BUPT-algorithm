#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>
#include<map>
#include<cmath>

using namespace std;

map <char,int> cha;
map <char,string> hcode;
string article;
typedef struct node
{
    int weight;//权重
    char ch;//字符
    string code;//编码
    int parent,left,right;//父节点 左孩子 右孩子
}huffmannode,*huffmantree;

void input();
void code();
void select(huffmantree ht,int len,int &s1,int &s2);
void encode(huffmantree ht,int m);
void statistic();

int main()
{
    input();
    code();
    statistic();
    return 0;
}
void input()
{
    string filename,temp;
    filename="huffman.txt";
    ifstream fin(filename,ios::in);
    while(getline(fin,temp))
    {
        for(int i=0;i<temp.size();i++)
        {
            char a=temp.at(i);
            if(a==' '||a==' ')
            {
                a='#';
            }
            string x=temp.substr(i,1);
            if(x==" ")
                article+="#";
            else
                article+=x;
            auto it=cha.find(a);
            if(it!=cha.end())
            {
                it->second++;
            }
            else
            {
                cha.insert(pair<char,int>{a,1});
            }
        }
    }
}
void code()
{
    int n=cha.size(),m=2*n-1;//叶子节点数目，节点总数
    huffmantree ht;
    if(n<1)
        return;
    ht=new huffmannode[m+1];
    for(int i=1;i<=m;i++)
    {
        ht[i].parent=0;
        ht[i].left=0;
        ht[i].right=0;
    }
    int i=1;
    for(auto it=cha.begin();i<=n;it++,i++)//叶子节点的权值赋值
    {
        ht[i].weight=it->second;
        ht[i].ch=it->first;
    }
    int s1,s2;
    for(int i=n+1;i<=m;i++)
    {
        select(ht,i-1,s1,s2);//选择节点中两个权值最小而且父节点为0的点
        ht[s1].parent=i;
        ht[s2].parent=i;
        ht[i].left=s1;
        ht[i].right=s2;
        ht[i].weight=ht[s1].weight+ht[s2].weight;//父节点权值
    }
    encode(ht,m);
    for(int i=1;i<=n;i++)
    {
        hcode.insert({ht[i].ch,ht[i].code});
    }
}
void select(huffmantree ht,int len,int &s1,int &s2)
{
    int i, min1 = 0x3f3f3f3f, min2 = 0x3f3f3f3f; //先赋予最大值
    for (i = 1; i <= len; i++)
    {
        if (ht[i].weight < min1 && ht[i].parent == 0)
        {
            min1 = ht[i].weight;
            s1 = i;
        }
    }
    int temp = ht[s1].weight; //将原值存放起来，然后先赋予最大值，防止s1被重复选择
    ht[s1].weight = 0x3f3f3f3f;
    for (i = 1; i <= len; i++)
    {
        if (ht[i].weight < min2 && ht[i].parent == 0)
        {
            min2 = ht[i].weight;
            s2 = i;
        }
    }
    ht[s1].weight = temp; //恢复原来的值
}
void encode(huffmantree ht,int m)
{
    if(m==0)
        return;
    int x,y,z;
    x=ht[m].parent;
    y=ht[m].left;
    z=ht[m].right;
    if(y!=0)
    {
        ht[y].code=ht[m].code+"0";
    }
    if(z!=0)
    {
        ht[z].code=ht[m].code+"1";
    }
    encode(ht,y);
    encode(ht,z);
}
void statistic()
{
    for(auto it=cha.begin();it!=cha.end();it++)
    {
        auto y=hcode.find(it->first);
        double x=(double)it->second*100/article.size();
        cout << it->first << " " << y->second << " " << it->second << " " << x << "%" << endl;
    }
    cout << "Fixed length coding:" << article.size()*(ceil(log2(cha.size()))) << endl;
    int coun=0;
    for(int i=0;i<article.size();i++)
    {
        char c=article.at(i); 
        auto x=hcode.find(c);
        coun+=x->second.size();
    }
    cout << "Haffman length coding:" << coun << endl;
}
