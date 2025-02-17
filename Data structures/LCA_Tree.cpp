struct LCA_Tree{
    int n;
    int lgn;
    int T = 0;
    vector<int> tin;
    vector<int> tout;
    vector<vector<int>> up;

    LCA_Tree(vector<vector<int>>& g){
        n = g.size();
        lgn = __lg(n) + 1;
        tin.assign(n, 0);
        tout.assign(n, 0);
        up.assign(lgn, vector<int>(n));
        dfs(0, 0, g);
    }

    bool is_pred(int v, int u){
        return (tin[v] <= tin[u] && tout[u] <= tout[v]);
    }

    void dfs(int v, int pred, vector<vector<int>>& g){
        tin[v] = T++;
        up[0][v] = pred;
        for (int i = 1; i < lgn; i++){
            up[i][v] = up[i - 1][up[i - 1][v]];
        }
        for (int to : g[v]){
            if (to ^ pred){
                dfs(to, v, g);
            }
        }
        tout[v] = T++;
    }

    int get_lca(int v, int u){
        if (is_pred(v, u)){
            return v;
        }
        if (is_pred(u, v)){
            return u;
        }
        for (int i = lgn - 1; i >= 0; i--){
            if (!is_pred(up[i][v], u)){
                v = up[i][v];
            }
        }
        return up[0][v];
    }
};
