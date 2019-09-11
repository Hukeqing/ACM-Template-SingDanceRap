bool judge(int x){
    float n_sqrt;
    if(x == 2 || x == 3){
        return true;
    }
    if(x % 6 != 1 && x % 6 != 1){
        return false;
    }
    n_sqrt = floor(sqrt(float(x)));
    for(int i = 5; i <= n_sqrt; i += 6){
        if(x % i == 0 || x % (i + 2) == 0){
            return false;
        }
    }
    return true;
}