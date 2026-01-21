#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    int w;
};

struct DSU {
    vector<int> p, r;

    DSU(int n) {
        p.resize(n);
        r.assign(n, 0);
        iota(p.begin(), p.end(), 0);
    }

    int find(int x) {
        if(p[x] == x) return x;
        return p[x] = find(p[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if(a == b) return false;
        if(r[a] < r[b]) swap(a, b);
        p[b] = a;
        if(r[a] == r[b]) r[a]++;
        return true;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    long long K;
    cin >> N >> M >> K;

    vector<Edge> edges;
    edges.reserve(M);

    for(int i = 0; i < M; i++){
        int a, b, c;
        cin >> a >> b >> c;
        edges.push_back({a-1, b-1, c});
    }

    sort(edges.begin(), edges.end(),
         [](const Edge &x, const Edge &y){
            return x.w < y.w;
         });

    DSU dsu(N);
    long long mstCost = 0;
    vector<int> mstEdges;
    mstEdges.reserve(N-1);

    for(auto &e : edges){
        if(dsu.unite(e.u, e.v)){
            mstCost += e.w;
            mstEdges.push_back(e.w);
            if(mstEdges.size() == N-1) break;
        }
    }

    // 🔥 Important missing condition
    if(mstEdges.size() != N-1){
        cout << -1 << "\n";
        return 0;
    }

    if(mstCost <= K){
        cout << 0 << "\n";
        return 0;
    }

    sort(mstEdges.rbegin(), mstEdges.rend());

    long long need = mstCost - K;
    long long saved = 0;
    int ops = 0;

    for(int w : mstEdges){
        long long gain = w - 1;
        if(gain > 0){
            saved += gain;
            ops++;
            if(saved >= need) break;
        }
    }

    if(saved < need) cout << -1 << "\n";
    else cout << ops << "\n";
}
