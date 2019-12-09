#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<ctime>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
#define m 5//row
#define n 5
#define down 1
#define right 2
#define left 4
#define up 8
vector <int> block_row;
vector <int> block_column;
vector <int> block_direct;
struct point{
    int x;
    int y;
}start,end;
int x_num=1,y_num=1;
int a[100][100];
void init(){//将地图全部置1=wall
    for(int i=0;i<=m+1;i++){
        for(int j=0;j<=n+1;j++){
            a[i][j]=1;//wall
        }
    }
    a[1][1]=2;
    start.x=1;//定义起始点
    start.y=1;
}
void push_into_vec(int x,int y,int direct){//把一组数据存放进三个vector容器中
    block_row.push_back(x);
    block_column.push_back(y);
    block_direct.push_back(direct);
}
int count(){//计算当前位置周围 墙的个数
    int cnt=0;
    if(x_num+1<=m){
        push_into_vec(x_num+1,y_num,down);
        cnt++;
    } //down
    if(y_num+1<=n){
        push_into_vec(x_num,y_num+1,right);
        cnt++;
    } //right
    if(x_num-1>=1){
        push_into_vec(x_num-1,y_num,up);
        cnt++;
    } //up
    if(y_num-1>=1){
        push_into_vec(x_num,y_num-1,left);
        cnt++;
    } //left
    return cnt;
}
int main(){
    init();
    srand((unsigned)time(NULL));//随机数种子
    count();
    while(block_row.size()){//第一步压入两堵墙（起点右边和起点下面）进入循环
        int num=block_row.size();
        int randnum=rand()%num;//生成0-num-1之间的随机数，同时也是vector里的下标
        x_num=block_row[randnum];
        y_num=block_column[randnum];
        switch(block_direct[randnum]){//选择一个方向进行后续操作，起始点 邻块 目标块 三块区域在同一直线上 随后移动到目标块的位置
            case down:{
                x_num++;
                break;
            }
            case right:{
                y_num++;
                break;
            }
            case left:{
                y_num--;
                break;
            }
            case up:{
                x_num--;
                break;
            }
        }
        if(a[x_num][y_num]==1){//目标块如果是墙
            a[block_row[randnum]][block_column[randnum]]=2;//打通墙
            a[x_num][y_num]=2;//打通目标块
            count();//再次计算当前位置周围的邻墙个数并保存进vector
        }
        block_row.erase(block_row.begin()+randnum);//删除这堵墙(把用不了的墙删了，对于那些已经施工过了不必再施工了，同时也是确保我们能跳出循环)
        block_column.erase(block_column.begin()+randnum);
        block_direct.erase(block_direct.begin()+randnum);
    }

    for(int i=0;i<=m+1;i++){
        printf("%d:\t",i);
        for(int j=0;j<=n+1;j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    //switch 1->0 2->1 wall 3;
    for(int i=0;i<=m+1;i++){
        for(int j=0;j<=n+1;j++) {
            if(i==0||j==0||i==m+1||j==n+1){
                a[i][j]=3;
            }
            if(a[i][j]==2){
                a[i][j]=1;
            }else if(a[i][j]==1){
                a[i][j]=0;
            }
        }
    }

    for(int i=0;i<=m+1;i++){
        printf("%d:\t",i);
        for(int j=0;j<=n+1;j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    int r=m+2;
    int l=n+2;
    vector<vector<string>> vv;
    //wall
    for(int i=0;i<r;i++){
        vector<string> v;
        for(int j=0;j<l;j++) {
            v.push_back("02");
        }
        vv.push_back(v);
    }


    //inside element
    for(int i=1;i<vv.size()-1;i++){
        for(int j=1;j<vv[0].size()-1;j++){
            vv[i][j]="03";
        }
    }

    //inside
    for(int i=1;i<vv.size()-1;i++){
        for(int j=1;j<vv[0].size()-1;j++){

            if(vv[i + 1][j]=="02"){
                vv[i][j] = "00";
                if(vv[i][j+1]!="02"){
                    vv[i][j+1]="01";
                }
                j++;
            }else{
                vv[i][j] = "00";
                vv[i + 1][j] = "10";
                if(vv[i][j+1]=="02"||vv[i+1][j+1]=="02"){
                    j++;
                }else{
                    vv[i][j+1]="01";
                    vv[i+1][j+1]="11";
                    j++;
                }
            }
        }
        i++;
    }

    //print
    for(int i=0;i<vv.size();i++){
        for(int j=0;j<vv[0].size();j++){
            if(j==vv[0].size()-1){
                cout<<vv[i][j];
            }else{
                cout<<vv[i][j]<<",";
            }
        }
        cout<<endl;
    }
    cout<<endl;



    //if eq==0 add random 13,22,23
    int ram=0;
    for(int i=1;i<vv.size();i++){
        for(int j=1;j<vv[0].size();j++){
            if(a[i][j]==0){
                ram=rand()%3;
                switch(ram){
                    case 0:
                        vv[i][j]="13";
                        break;
                    case 1:
                        vv[i][j]="22";
                        break;
                    case 2:
                        vv[i][j]="23";
                        break;
                    default:
                        break;
                }

            }
        }
    }

    //print
    for(int i=0;i<vv.size();i++){
        for(int j=0;j<vv[0].size();j++){
            if(j==vv[0].size()-1){
                cout<<vv[i][j];
            }else{
                cout<<vv[i][j]<<",";
            }
        }
        cout<<endl;
    }
    cout<<endl;


    return 0;
}