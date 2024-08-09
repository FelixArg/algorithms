struct Suffix_Automaton{
    const static int AL = 26;
    struct Node{
        int nxt[AL];
        int link;
        int len;
        int& operator[](int ch){
            return nxt[ch];
        }
        Node(): link(-1), len(0){
            memset(nxt, -1, sizeof(nxt));
        }
    };

    vector<Node> data;
    int last;

    Suffix_Automaton(){
        data.emplace_back();
        last = 0;
    }

    void extend(int c){
        int cur = data.size();
        data.emplace_back();
        data[cur].len = data[last].len + 1;
        int p = last;
        while(p != -1 && data[p][c] == -1){
            data[p][c] = cur;
            p = data[p].link;
        }
        if (p == -1){
            data[cur].link = 0;
        }
        else{
            int q = data[p][c];
            if (data[p].len + 1 == data[q].len){
                data[cur].link = q;
            }
            else{
                int nw = data.size();
                data.push_back(data[q]);
                data[nw].len = data[p].len + 1;
                while(p != -1 && data[p][c] == q){
                    data[p][c] = nw;
                    p = data[p].link;
                }
                data[cur].link = data[q].link = nw;
            }
        }
        last = cur;
    }

    size_t size(){
        return data.size();
    }

    Node& operator[](int i){
        return data[i];
    }
};
