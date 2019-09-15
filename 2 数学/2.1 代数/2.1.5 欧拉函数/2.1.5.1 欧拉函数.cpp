//O(logn)的时间求一个数的phi
ll euler(ll n){
    ll rt = n;
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0){
            rt -= rt / i;
            while(n % i == 0){
                n /= i;
            }
        }
    }
    if(n > 1){
        rt -= rt / n;
    }
    return rt;
}

//给出一个N，求[1,n]中与N互质的数的和就是这个公式: n*phi[n]/2

//用一个数组求欧拉值
ll phi[maxn];
void ZyfPhi() {
    phi[1] = 0;
    for(int i = 2; i < maxn; i++){
        phi[i] = i;
    }
    for(int i = 2; i < maxn; i++){
        if(phi[i] == i){
            for(int j = i; j < maxn; j += i){
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
    for (int i = 2; i < maxn; i++) {
        phi[i] = phi[i] + phi[i - 1];
    }
}

//O(n)得到欧拉函数phi[], 素数表prime[], 素数个数tot
bool vis[maxn];
int tot, phi[maxn], prime[maxn];
void Phi(){
    phi[1] = 0;
    for(int i = 2; i < maxn; i++){
        if(!vis[i]){
            prime[tot++] = i, phi[i] = i - 1;
            for(int j = 0; j < tot; j++){
                if(i * prime[j] > maxn){
                    break;
                }
                vis[i * prime[j]] = 1;
                if(i % prime[j] == 0){
                    phi[i * prime[j]] = phi[i] * prime[j];
                    break;
                }else{
                    phi[i * prime[j]] = phi[i] * (prime[j] - 1);
                }
            }
        }
    }
}