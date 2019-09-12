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