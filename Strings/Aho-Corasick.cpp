struct Aho_Corasick{
    const static int al = 26;
    struct Node{
        Node* to[al];
        Node* go[al];
        Node* link = nullptr;
        char pred_ch;
        Node* pred = nullptr;
        Node(char _pred_ch, Node* _pred): pred_ch(_pred_ch), pred(_pred){
            memset(to, 0, sizeof(to));
            memset(go, 0, sizeof(go));
        }
    };

    Node* root = nullptr;
    void add(const string& s, int val){
        Node* cur = root;
        for (char ch : s){
            if (!cur->to[ch - 'a']){
                cur->to[ch - 'a'] = new Node(ch, cur);
            }
            cur = cur->to[ch - 'a'];
        }
    }

    Node* find(const string& s){
        Node* cur = root;
        for (char ch : s){
            if (!cur->to[ch - 'a']){
                return nullptr;
            }
            cur = cur->to[ch - 'a'];
        }
        return cur;
    }

    //Node* go(Node* v, char ch);

    Node* link(Node* v){
        if (!v->link){
            if (v == root || v->pred == root){
                v->link = root;
            }
            else{
                v->link = go(link(v->pred), v->pred_ch);
            }
        }
        return v->link;
    }

    Node* go(Node* v, char ch){
        if (!v->go[ch - 'a']){
            if (v->to[ch - 'a']){
                v->go[ch - 'a'] = v->to[ch - 'a'];
            }
            else if (v == root){
                v->go[ch - 'a'] = root;
            }
            else{
                v->go[ch - 'a'] = go(link(v), ch);
            }
        }
        return v->go[ch - 'a'];
    }

    void bfs(){
        if (root == nullptr){
            return;
        }
        vector<Node*> q;
        q.push_back(root);
        for (int i = 0; i < q.size(); i++){
            for (int j = 0; j < al; j++){
                if (q[i]->to[j]){
                    q.push_back(q[i]->to[j]);
                }
            }
        }
        for (int i = 0; i < q.size(); i++){
            if (q[i] != nullptr){
                delete q[i];
            }
        }
    }

    Aho_Corasick(): root(new Node(0, nullptr)){}
    ~Aho_Corasick(){ bfs();};
};
