void bsgs(ll y,ll z,ll p)//y^x=z(mod p)
{
    if(y==0 && z==0){puts("1");return ;}//几句特判 
    if(y==0 && z!=0){return;}//不存在
    
    hash.clear();
    ll m=ceil(sqrt(p));
    ll tmp=z%p;hash[tmp]=0;//右边z*A^j，当j=0时为z 
    for(ll i=1;i<=m;i++)
    {
        tmp=tmp*y%p;
        hash[tmp]=i;
    }
    
    ll t=power(y,m,p); 
    tmp=1;//左边y^(i*m)，当i=0时为1
    for(ll i=1;i<=m;i++)
    {
        tmp=tmp*t%p;//i每加1，多乘y^(i*m)
        if(hash[tmp])
        {
            ll ans=i*m-hash[tmp];
            printf("%lld\n",(ans%p+p)%p);
            return ;
        }
    }
    return;//不存在
}