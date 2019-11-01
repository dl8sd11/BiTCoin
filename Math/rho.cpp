#define lll __int128

lll c = 1;
lll g(lll x, lll n){
    return (x*x+c)%n;
}

lll gcd(lll a, lll b){
    if (b==0) return a;
    return gcd(b,a%b);
}

lll po(lll n){
    lll x = 2, y = 2, d = 1;
    while (d==1){
        x = g(x,n); y = g(g(y,n),n); 
        d = gcd(x>y?x-y:y-x,n);
    }
    if (d==n) return -1;
    return d;
}

ll fac(ll n){
    if (n%2==0) return 2;
    lll ans = -1; 
    for (int i = 0; i<5 && ans==-1; i++) {
        c++; if (c==2) c++;
        ans = po(n);
    }
    return ans;
}

main(){
    ll test = 1709049187;
    lll moo = test;
    ll ans = po(moo);
    cout<<ans<<endl;
    
} 
