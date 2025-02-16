// O(n) memory 
struct Virtual_Tree{
    int n;
    int lgn;
    int T;
    vector<vector<int>> tree;
    vector<int> jmp;
    vector<int> dep;
    vector<int> p;
    vector<int> tin;
    vector<int> tout;
 
    int virt_vert;
    vector<vector<int>> virt_tree;
    vector<int> on_vert;
 
    Virtual_Tree(vector<vector<int>> &g){
        n = g.size();
        T = 0;
        tree = g;
        jmp.assign(n, 0);
        dep.assign(n, 0);
        p.assign(n, 0);
        tin.assign(n, 0);
        tout.assign(n, 0);
        virt_tree.assign(n, vector<int>());
        init();
    }
 
    void dfs(int v, int pred){
        p[v] = pred;
        tin[v] = T++;
        dep[v] = dep[pred] + 1;
        if (v == pred){
            jmp[v] = v;
        }
        else{
            if (dep[jmp[pred]] - dep[pred] == dep[jmp[jmp[pred]]] - dep[jmp[pred]]){
                jmp[v] = jmp[jmp[pred]];
            }
            else{
                jmp[v] = pred;
            }
        }
        for (int to : tree[v]){
            if (to ^ pred){
                dfs(to, v);
            }
        }
        tout[v] = T++;
    }
 
    void init(){
        dep[0] = -1;
        dfs(0, 0);
    }
 
    bool is_pred(int v, int u){
        return (tin[v] <= tin[u] && tout[u] <= tout[v]);
    }
 
    int get_lca(int u, int v){
        if (is_pred(v, u)){
            return v;
        }
        if (is_pred(u, v)){
            return u;
        }
        while(1){
            if (!is_pred(jmp[v], u)){
                v = jmp[v];
            }
            else if (!is_pred(p[v], u)){
                v = p[v];
            }
            else{
                break;
            }
        }
        return p[v];
    }
 
    void create_virt_tree(vector<int> ver){
        int sz = ver.size();
        on_vert = ver;
 
        sort(ver.begin(), ver.end(), [&](const int& v, const int& u){
            if (tin[v] == tin[u]){
                return v < u;
            }
            return tin[v] < tin[u];
        });
        for (int i = 0; i < sz - 1; i++){
            ver.emplace_back(get_lca(ver[i], ver[i + 1]));
        }
        sort(ver.begin(), ver.end(), [&](const int& v, const int& u){
            if (tin[v] == tin[u]){
                return v < u;
            }
            return tin[v] < tin[u];
        });
        ver.erase(unique(ver.begin(), ver.end()), ver.end());
 
        for (int v : ver){
            virt_tree[v].clear();
        }
 
        sz = ver.size();
        vector<int> st = {ver[0]};
        for (int i = 1; i < sz; i++){
            while(st.size() > 1 && !is_pred(st.back(), ver[i])){
                int f = st[st.size() - 2];
                int t = st.back();
                virt_tree[f].push_back(t);
                virt_tree[t].push_back(f);
                st.pop_back();
            }
            st.emplace_back(ver[i]);
        }
        while(st.size() > 1){
            int f = st[st.size() - 2];
            int t = st.back();
            virt_tree[f].push_back(t);
            virt_tree[t].push_back(f);
            st.pop_back();
        }
        virt_vert = st[0];
    }
};
