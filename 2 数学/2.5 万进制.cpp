#include<iostream>
#include<iomanip>

using namespace std;

int main(void){
    void factorial(int n);//阶乘函数||多次幂函数

    int n;
    while(cin >> n){
        factorial(n);
    }
}

void factorial(int n){
    int a[10001];
    int places,carry,i,j;

    a[0]=1;
    places=0;//当前数的总位数
    for(i=1;i<=n;i++){
        carry=0;
        for(j=0;j<=places;j++){
            a[j]=a[j]*i+carry;//如果是多次幂函数，将i改成数字即可
            carry=a[j]/10000;
            a[j]%=10000;
        }
        if(carry>0){
            places++;
            a[places]=carry;
        }
    }
    /*
     * 输出
     * 最高位原样输出
     * 其他位小于1000的，高位补0
     */
    cout <<a[places];
    for(i=places-1;i>=0;i--){
        cout << setw(4) << setfill('0') << a[i];
    }
    cout << endl;
}