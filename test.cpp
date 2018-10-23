#include <bits/stdc++.h>
#define pi acos(-1)
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int INF = 0x3f3f3f3f;
const LL ll_INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 1e5 + 10;
const int mod = 1e9 + 7;

#define ls l,m,rt<<1
#define rs m+1,r,rt<<1|1
LL sum[MAXN<<2], add[MAXN<<2], mul[MAXN<<2];
LL a[MAXN];
LL n, m, p;
struct LazyTag
{
    int mul, add, res;
}lz[MAXN<<2];

void PushUp(int rt) { sum[rt] = ( sum[rt<<1]+sum[rt<<1|1] )%p; }
void PushDown(int rt, int ln, int rn)
{
    sum[rt<<1] = ( sum[rt<<1]*mul[rt] + add[rt]*ln )%p;
    sum[rt<<1|1] = ( sum[rt<<1|1]*mul[rt] + add[rt]*rn )%p;

    mul[rt<<1] = ( mul[rt<<1]*mul[rt] )%p;
    mul[rt<<1|1] = ( mul[rt<<1|1]*mul[rt] )%p;

    add[rt<<1] = ( add[rt<<1]*mul[rt] + add[rt] )%p;
    add[rt<<1|1] = ( add[rt<<1|1]*mul[rt] + add[rt] )%p;

    mul[rt]=1;
    add[rt]=0;
    return ;
}

void Build(int l, int r, int rt)
{
    mul[rt]=1;
    add[rt]=0;
    if(l==r){
        sum[rt]=a[l];
        return;
    }
    int mid = (l+r)>>1;
    Build(l, mid, rt<<1);
    Build(mid+1, r, rt<<1|1);
    PushUp(rt);
}

//点的更新，假设A[L]+=C
void update_plus(int L, LL C, int l, int r, int rt)
{
    if(l==r){
        sum[rt]+=C;
        return;
    }
    int mid = (l+r)>>1;
    PushDown(rt, mid-l+1, r-mid);
    if(L <= mid) update_plus(L, C, l, mid, rt<<1);
    else         update_plus(L, C, mid+1, r, rt<<1|1);
    PushUp(rt);
}

//区间更新，假设A[L,R]+=C
void update_plus(int L, int R, LL C, int l, int r, int rt)
{
    if(L<=l && r<=R){
        sum[rt] = ( sum[rt] + C*(r-l+1) )%p;
        add[rt] = ( add[rt] + C )%p ;
        return ;
    }
    int mid = (l+r)>>1;
    PushDown(rt, mid-l+1, r-mid);
    if(L <= mid) update_plus(L, R, C, l, mid, rt<<1);
    if(R >  mid) update_plus(L, R, C, mid+1, r, rt<<1|1);
    PushUp(rt);
}

void update_mutiple(int L, int R, LL k, int l, int r, int rt)
{
    if(L<=l && r<=R){
        sum[rt] = ( sum[rt]*k )%p;
        mul[rt] = ( mul[rt]*k )%p;
        add[rt] = ( add[rt]*k )%p;
        return ;
    }
    int mid = (l+r)>>1;
    PushDown(rt, mid-l+1, r-mid);
    if(L <= mid) update_mutiple(L, R, k, l, mid, rt<<1);
    if(R >  mid) update_mutiple(L, R, k, mid+1, r, rt<<1|1);
    PushUp(rt);
}

//区间查询
LL Query(int L, int R, int l, int r, int rt)
{
    if(L<=l && r<=R){
        return sum[rt];
    }
    int mid = (l+r)>>1;
    PushDown(rt, mid-l+1, r-mid);
    LL ans=0;
    if(L<=mid) ans = ( ans + Query(L, R, l, mid, rt<<1) )%p ;
    if(R> mid) ans = ( ans + Query(L, R, mid+1, r, rt<<1|1) )%p;
    return ans;
}

int main()
{
    cin >> n >> m >> p;
    for(int i=1; i<=n; i++) scanf("%lld", &a[i]);
    Build(1, n, 1);
    int flag, x, y;
    LL k;
    for(int i=1; i<=m; i++){
        scanf("%d%d%d", &flag, &x, &y);
        if(flag==1){
            scanf("%lld", &k);
            update_mutiple(x, y, k, 1, n, 1);
        }
        else if(flag==2){
            scanf("%lld", &k);
            update_plus(x, y, k, 1, n, 1);
        }
        else if(flag==3){
            printf("%lld\n", Query(x, y, 1, n, 1) );
        }
    }
    return 0;
}
