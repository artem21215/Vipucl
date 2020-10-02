#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long

using namespace std;

struct Node{
    int sum;
    ll minim=100000000000000000ll,maxim=-100000000000000000ll;
    //bool isAssigned;
};

int treeSize;
vector<Node> tree;

void recalculate(int v){
    tree[v].sum=tree[2*v].sum+tree[2*v+1].sum;
    tree[v].minim=min(tree[2*v].minim,tree[2*v+1].minim);
    tree[v].maxim=max(tree[2*v].maxim,tree[2*v+1].maxim);
}

void init(const vector<int> &a){
    int n=a.size();
    treeSize=1;
    while (treeSize<=n)
        treeSize*=2;
    tree.assign(treeSize*2,Node{0,0,false});

    for (size_t i=0;i<n;++i) {
        tree[treeSize + i].sum = a[i];
        tree[treeSize + i].minim = a[i];
        tree[treeSize + i].maxim = a[i];
    }
    for (size_t i=treeSize-1;i>0;--i)
        recalculate(i);
}

ll minimum(ll v,ll l,ll r, ll query_l, ll query_r){
    if (r<query_l || query_r < l)
        return 100000000000000000ll;
    if (query_l <=l && r<=query_r)
        return tree[v].minim;

    ll mid=(l+r)/2;
    return min(minimum(v*2,l,mid,query_l,query_r), minimum(v*2+1,mid+1,r,query_l,query_r));
}

ll maximum(ll v,ll l,ll r, ll query_l, ll query_r){
    if (r<query_l || query_r < l)
        return -100000000000000000ll;
    if (query_l <=l && r<=query_r)
        return tree[v].maxim;

    ll mid=(l+r)/2;
    return max(maximum(v*2,l,mid,query_l,query_r), maximum(v*2+1,mid+1,r,query_l,query_r));
}

int main(){
    ll n,x,y;
    vector<int> arr(100001);
    for (ll i=0;i<=100000;++i){
        arr[i]=((i%12345ll)*(i%12345ll))%12345ll+((i%23456ll)*(i%23456ll)*(i%23456ll))%23456ll;
    }
    init(arr);
    cin >> n;
    for (int i=0;i<n;i++){
        cin >> x >> y;
        if (x>0){
            cout << maximum(1,1,n,x,y)-minimum(1,1,n,x,y) << endl;
        }
        else{
            int it=treeSize-1+abs(x);
            while (it!=0){
                tree[it/2].minim=min(tree[it/2].minim,y);
                tree[it/2].maxim=max(tree[it/2].maxim,y);
                it/=2;
            }
        }
    }

    return 0;
}
