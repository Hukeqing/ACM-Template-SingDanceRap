#include<bits/stdc++.h>
#define mp make_pair
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef long long ll;
const double inf=1e200;
const double eps=1e-12;
const double pi=acos(-1.0);
const int maxn=1000010;
struct point{
    double x,y;
    point(){ }
    point(double xx,double yy):x(xx),y(yy){}
};
struct line{
    point a;//起点
    point p;//起点到终点的向量
    double angle;
};
struct Circle{
    point c; double r;
};
int dcmp(double x){ return fabs(x)<eps?0:(x<0?-1:1);}
point operator +(point A,point B) { return point(A.x+B.x,A.y+B.y);}
point operator -(point A,point B) { return point(A.x-B.x,A.y-B.y);}
point operator *(point A,double p){ return point(A.x*p,A.y*p);}
point operator /(point A,double p){ return point(A.x/p,A.y/p);}
point rotate(point A,double rad){ //向量的旋转
    return point(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));
}
bool operator ==(const point& a,const point& b) {
     return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;
}
double dot(point A,point B){ return A.x*B.x+A.y*B.y;}
double det(point A,point B){ return A.x*B.y-A.y*B.x;}
double dot(point O,point A,point B){ return dot(A-O,B-O);}
double det(point O,point A,point B){ return det(A-O,B-O);}
double length(point A){ return sqrt(dot(A,A));}
double dist(point A,point B){ return length(A-B);}
double angle(point A,point B){ return acos(dot(A,B)/length(A)/length(B));} //夹角
point jiaopoint(point p,point v,point q,point w)
{   //p+tv q+tw，点加向量表示直线，求直线交点
    //如果是线段，还应该实现判定是否相离； 必要时判是否平行
    point u=p-q;
    double t=det(w,u)/det(v,w);//如果平行，除0会有问题
    return p+v*t;
}
point llintersect(line A,line B) //直线交点，同上
{
    point C=A.a-B.a;
    double t=det(C,B.p)/det(B.p,A.p);
    return A.a+A.p*t;
}
point GetCirPoint(point a,point b,point c)
{
    point p=(a+b)/2;    //ab中点
    point q=(a+c)/2;    //ac中点
    point v=rotate(b-a,pi/2.0),w=rotate(c-a,pi/2.0);   //中垂线的方向向量
    if (dcmp(det(v,w))==0)    //平行
    {
        if(dcmp(length(a-b)+length(b-c)-length(a-c))==0) return (a+c)/2;
        if(dcmp(length(b-a)+length(a-c)-length(b-c))==0) return (b+c)/2;
        if(dcmp(length(a-c)+length(c-b)-length(a-b))==0) return (a+b)/2;
    }
    return jiaopoint(p,v,q,w);
}
point w[maxn];
void MinCir(int N) //增量法，玄学复杂度O(N)；如果精度要求不高，可以三分套三分。
{
    point C=w[1]; double r=0;
    rep(i,1,N){
        if(dist(C,w[i])>r) {
            C=w[i]; r=0;
            rep(j,1,i-1) {
                if(dist(C,w[j])>r) {
                    C=(w[i]+w[j])/2; r=dist(w[i],w[j])/2;
                    rep(k,1,j-1) {
                        if(dist(C,w[k])>r){
                            C=GetCirPoint(w[i],w[j],w[k]);
                            r=dist(C,w[i]);
                        }
                    }
                }
            }
        }
    }
    printf("%.2lf %.2lf %.2lf\n",C.x,C.y,r);
}
double area(vector<point>p){ //求面积
    double ans=0; int sz=p.size();
    for(int i=1;i<sz-1;i++) ans+=det(p[i]-p[0],p[i+1]-p[0]);
    return ans/2.0;
}
double seg(point O,point A,point B){ //返回比例
    if(dcmp(B.x-A.x)==0) return (O.y-A.y)/(B.y-A.y);
    return (O.x-A.x)/(B.x-A.x);
}
vector<point>pp[110];
pair<double,int>s[110*60];
double polyunion(vector<point>*p,int N){ //需要这些点是顺时针，N个多边形。
    double res=0;
    for(int i=0;i<N;i++){
        int sz=p[i].size();
        for(int j=0;j<sz;j++){
            int m=0;
            s[m++]=mp(0,0);
            s[m++]=mp(1,0);
            point a=p[i][j],b=p[i][(j+1)%sz];
            for(int k=0;k<N;k++){
                if(i!=k){
                    int sz2=p[k].size();
                    for(int ii=0;ii<sz2;ii++){
                        point c=p[k][ii],d=p[k][(ii+1)%sz2];
                        int c1=dcmp(det(b-a,c-a));
                        int c2=dcmp(det(b-a,d-a));
                        if(c1==0&&c2==0){
                            if(dcmp(dot(b-a,d-c))){
                                s[m++]=mp(seg(c,a,b),1);
                                s[m++]=mp(seg(c,a,b),-1);
                            }
                        }
                        else{
                            double s1=det(d-c,a-c);
                            double s2=det(d-c,b-c);
                            if(c1>=0&&c2<0) s[m++]=mp(s1/(s1-s2),1);
                            else if(c1<0&&c2>=0) s[m++]=mp(s1/(s1-s2),-1);
                        }
                    }
                }
            }
            sort(s,s+m);
            double pre=min(max(s[0].first,0.0),1.0),now,sum=0;
            int cov=s[0].second;
            for(int j=1;j<m;j++){
                now=min(max(s[j].first,0.0),1.0);
                if(!cov) sum+=now-pre;
                cov+=s[j].second;
                pre=now;
            }
            res+=det(a,b)*sum;
        }
    }
    return res/2;
}
void CirinterCir(point a,double r1,point b,double r2) //求圆和圆的交点
{
    //记得提前判断是否相交，如果相交就利用角度就可以求了
    double L=dist(a,b);
    if(L>r1+r2) return ;//相离
    if(L+r1<r2||L+r2<r1) return ;//包含
    double t=acos((r1*r1+L*L-r2*r2)/(2.0*r1*L));
    double base=atan2(b.y-a.y,b.x-a.x);  //atan2的范围是(-pi,pi]，这个很多时候用起来更直观，但是缺点是慢
    double ang1=base+t,ang2=base-t;
    point A=a+point{r1*cos(ang1),r1*sin(ang1)};
    point B=a+point{r1*cos(ang2),r1*sin(ang2)};
}
bool cmp1(point a,point b){ return a.x==b.x?a.y<b.y:a.x<b.x; } //x排序
void convexhull(point *a,int n,point *ch,int &top) //凸包
{
    sort(a+1,a+n+1,cmp1);//x排序
    top=0;
    for(int i=1;i<=n;i++){ //下凸包
        while(top>=2&&det(ch[top-1],ch[top],a[i])<=0) top--;
        ch[++top]=a[i];
    }
    int ttop=top;
    for(int i=n-1;i>=1;i--){ //上凸包
        while(top>ttop&&det(ch[top-1],ch[top],a[i])<=0) top--;
        ch[++top]=a[i];
    }
}
double rotating_calipers(point p[],int top) //求最远的点距离
{
    double ans=0; int now=2;
    rep(i,1,top-1){ //先求出凸包，然后凸包上旋转卡壳
        while(det(p[i],p[i+1],p[now])<det(p[i],p[i+1],p[now+1])){
            now++; //最远距离对应了最大面积。
            if(now==top) now=1;
        }
        ans=max(ans,dist(p[now],p[i]));
    }
    return ans;
}
point ch[2000000],p[2000000];
double getangle(point a){ return atan2(a.y,a.x);}
double getangle(line a){ return getangle(a.p);}
point ss[maxn]; line t[maxn],q[maxn]; int head,tail;
bool cmp2(line a,line b){ //方向的极角排序
    double A=getangle(a),B=getangle(b);
    point t=(b.a+b.p)-a.a;
    if(fabs(A-B)<eps) return det(a.p,t)>=0.0;
    return A<B;
}
bool onright(line P,line a,line b)
{
    point o=llintersect(a,b);
    point Q=o-P.a;
    return det(Q,P.p)>0; //如果同一直线上不能相互看到，则>=0
}
bool halfplaneintersect(int N)
{
    ss[N+1]=ss[1];
    rep(i,1,N) t[i].a=ss[i], t[i].p=ss[i+1]-ss[i];
    sort(t+1,t+N+1,cmp2);
    int tot=0;
    rep(i,1,N-1) {
        if(fabs(getangle(t[i])-getangle(t[i+1]))>eps)
          t[++tot]=t[i];
    }
    t[++tot]=t[N]; head=tail=0;
    rep(i,1,tot){
        while(tail>head+1&&onright(t[i],q[tail],q[tail-1])) tail--;
        while(tail>head+1&&onright(t[i],q[head+1],q[head+2])) head++;
        q[++tail]=t[i];
    }
    while(tail>head+1&&onright(t[head+1],q[tail],q[tail-1])) tail--;return tail-head>2;
}
double TriAngleCircleInsection(Circle C, point A, point B) //圆与多边形面积交
{
    //a[N+1]=a[1];  ans=0;。 拆成多个三角形，求矢量面积核
    //rep(i,1,N) ans+=TriAngleCircleInsection(C,a[i],a[i+1]);
    point OA=A-C.c,OB=B-C.c;
    point BA=A-B, BC=C.c-B;
    point AB=B-A, AC=C.c-A;
    double DOA=length(OA),DOB=length(OB),DAB=length(AB),r=C.r;
    if(dcmp(det(OA,OB))==0) return 0; //，三点一线，不构成三角形
    if(dcmp(DOA-C.r)<0&&dcmp(DOB-C.r)<0) return det(OA,OB)*0.5; //内部
    else if(DOB<r&&DOA>=r) //一内一外
    {
        double x=(dot(BA,BC)+sqrt(r*r*DAB*DAB-det(BA,BC)*det(BA,BC)))/DAB;
        double TS=det(OA,OB)*0.5;
        return asin(TS*(1-x/DAB)*2/r/DOA)*r*r*0.5+TS*x/DAB;
    }
    else if(DOB>=r&&DOA<r)// 一外一内
    {
        double y=(dot(AB,AC)+sqrt(r*r*DAB*DAB-det(AB,AC)*det(AB,AC)))/DAB;
        double TS=det(OA,OB)*0.5;
        return asin(TS*(1-y/DAB)*2/r/DOB)*r*r*0.5+TS*y/DAB;
    }
    else if(fabs(det(OA,OB))>=r*DAB||dot(AB,AC)<=0||dot(BA,BC)<=0)//弧
    {
        if(dot(OA,OB)<0){
            if(det(OA,OB)<0) return (-acos(-1.0)-asin(det(OA,OB)/DOA/DOB))*r*r*0.5;
            else  return ( acos(-1.0)-asin(det(OA,OB)/DOA/DOB))*r*r*0.5;
        }
        else      return asin(det(OA,OB)/DOA/DOB)*r*r*0.5; //小于90度，以为asin对应的区间是[-90度,90度]
    }
    else //弧+三角形
    {
        double x=(dot(BA,BC)+sqrt(r*r*DAB*DAB-det(BA,BC)*det(BA,BC)))/DAB;
        double y=(dot(AB,AC)+sqrt(r*r*DAB*DAB-det(AB,AC)*det(AB,AC)))/DAB;
        double TS=det(OA,OB)*0.5;
        return (asin(TS*(1-x/DAB)*2/r/DOA)+asin(TS*(1-y/DAB)*2/r/DOB))*r*r*0.5 + TS*((x+y)/DAB-1);
    }
}
double ltoseg(point p,point a,point b){
    point t=p-a;
    if(dot(t,b-a)<=0) return dist(p,a);
    else if(dot(p-b,a-b)<=0) return dist(p,b);
    return fabs(det(t,b-a))/dist(a,b);
}
bool isinside(point a) //O(N)判定是否在（任意多边形）内
{
//算法描述：首先，对于多边形的水平边不做考虑，其次，
//对于多边形的顶点和射线相交的情况，如果该顶点时其所属的边上纵坐标较大的顶点，则计数，否则忽略该点，
//最后，对于Q在多边形上的情形，直接判断Q是否属于多边形。
    int ncross=0; int N;
    rep(i,0,N-1) {
        point p1=p[i],p2=p[i+1];
        if(ltoseg(a,p[i],p[i+1])==0) return true; //在线段上
        if(p1.y==p2.y) continue; //默认做水平x轴的线，所以水平线不考虑
        if(a.y<min(p1.y,p2.y)) continue; //相离不考虑
        if(a.y>max(p1.y,p2.y)) continue;
        double t=det(a-p[i],a-p[i+1]);
        if((t>=0&&p[i].y<a.y&&p[i+1].y>=a.y)||(t<=0&&p[i+1].y<a.y&&p[i].y>=a.y)) ncross++;
    }
    return (ncross&1);
}
bool check(point A,int top) //二分点在（凸多边形）内
{
    int L=2,R=top-2,Mid;
    while(L<=R){
        Mid=(L+R)>>1;
        if(det(ch[Mid]-ch[1],A-ch[1])<0) R=Mid-1;
        else {
            if(det(ch[Mid+1]-ch[1],A-ch[1])<=0&&det(ch[Mid+1]-ch[Mid],A-ch[Mid])>=0)
                return true;
            L=Mid+1;
        }
    }
    return false;
}
int main()
{

}