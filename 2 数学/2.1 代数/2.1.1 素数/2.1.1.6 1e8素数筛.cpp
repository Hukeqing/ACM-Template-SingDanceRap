//6*N法高效素数筛by fcy
#include<bits/stdc++.h> //空间和时间都非常优秀
using namespace std;
typedef unsigned int UI;
UI ans,N,A,B,C,D;
bitset<1000000001/3>p;
void add(UI x){ ans++;}
void prime()
{
    add(2); add(3); //加入素数表。
    for(UI i=5,d=2;i<=N;i+=d,d=6-d) {
       if(!p[i/3]){
          add(i); if(i>N/i) continue;
          for(UI j=i*i,v=d;j<=N;j+=i*v,v=6-v) p[j/3] = 1;
       }
    }
}
int main() {
   scanf("%u",&N);
   prime();
   printf("%u\n", ans);
   return 0;
}