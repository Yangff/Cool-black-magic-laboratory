#include "sdk.h"
#include <math.h>

int crossProduct(Pos A,Pos B,Pos C)//向量AB叉乘AC
{
    return (B.x-A.x)*(C.y-A.y)-(C.x-A.x)*(B.y-A.y);
}
bool cross(Pos A,Pos B,Pos C,Pos D)//判断线段AB与CD是否有公共点
{
    return (long long)crossProduct(A,B,C)*crossProduct(A,B,D)<=0 && (long long)crossProduct(C,D,A)*crossProduct(C,D,B)<=0;
}
bool checkOnLine(Pos A,Pos B,Pos C)//判断AB连线是否与C（方格）有交点
{
    if(A==B)
        return false;
    Pos a(A.x*2,A.y*2),b(B.x*2,B.y*2),c(C.x*2,C.y*2);
    return cross(a,b,Pos(c.x+1,c.y+1),Pos(c.x+1,c.y-1))
        ||cross(a,b,Pos(c.x+1,c.y+1),Pos(c.x-1,c.y+1))
        ||cross(a,b,Pos(c.x-1,c.y-1),Pos(c.x+1,c.y-1))
        ||cross(a,b,Pos(c.x-1,c.y-1),Pos(c.x-1,c.y+1));
}
int dis2(Pos A,Pos B)//欧氏距离平方
{
    return (A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y);
}
double dis(Pos A,Pos B)//欧几里得距离
{
    return sqrt(dis2(A,B));
}
bool operator==(Pos A,Pos B)//相等
{
    return A.x==B.x && A.y==B.y;
}
bool operator!=(Pos A,Pos B)//不等
{
    return !(A==B);
}
Pos operator+ (Pos A,Pos B)//加法
{
    return Pos(A.x+B.x,A.y+B.y);
}
Pos operator- (Pos A,Pos B)//减法
{
    return Pos(A.x-B.x,A.y-B.y);
}
Pos operator* (Pos A,int _)//数乘
{
    return Pos(A.x*_,A.y*_);
}
Pos operator* (int _,Pos A)//数乘
{
    return Pos(_*A.x,_*A.y);
}

//以下面对DPos定义的函数其功能与面对Pos的同名函数相同
const double _zero = 1e-10;
double crossProduct(DPos A,DPos B,DPos C)
{
    return (B.x-A.x)*(C.y-A.y)-(C.x-A.x)*(B.y-A.y);
}
bool cross(DPos A,DPos B,DPos C,DPos D)
{
    return crossProduct(A,B,C)*crossProduct(A,B,D)<=_zero && crossProduct(C,D,A)*crossProduct(C,D,B)<=_zero;
}
bool checkOnLine(DPos A,DPos B,DPos C)
{
    if(A==B)
        return false;
    return cross(A,B,Pos(C.x+0.5,C.y+0.5),Pos(C.x+0.5,C.y-0.5))
        ||cross(A,B,Pos(C.x+0.5,C.y+0.5),Pos(C.x-0.5,C.y+0.5))
        ||cross(A,B,Pos(C.x-0.5,C.y-0.5),Pos(C.x+0.5,C.y-0.5))
        ||cross(A,B,Pos(C.x-0.5,C.y-0.5),Pos(C.x-0.5,C.y+0.5));
}
double dis2(DPos A,DPos B)
{
    return (A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y);
}
double dis(DPos A,DPos B)
{
    return sqrt(dis2(A,B));
}
bool operator==(DPos A,DPos B)
{
    return fabs(A.x-B.x)<=_zero && fabs(A.y-B.y)<=_zero;
}
bool operator!=(DPos A,DPos B)
{
    return !(A==B);
}
DPos operator+ (DPos A,DPos B)
{
    return DPos(A.x+B.x,A.y+B.y);
}
DPos operator- (DPos A,DPos B)
{
    return DPos(A.x-B.x,A.y-B.y);
}
DPos operator* (DPos A,double _)
{
    return DPos(A.x*_,A.y*_);
}
DPos operator* (double _,DPos A)
{
    return DPos(_*A.x,_*A.y);
}

