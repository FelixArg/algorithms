const int inf = (1 << 30) + 1;
 
struct Min_Cost_Max_Flow_Graph{
	struct Edge{
		int to;
		int cap;
		int flow;
		int cost;
	};
 
	int n;
	vector<Edge> edges;
	vector<vector<int>> g;
	vector<int> d;
	vector<int> p;
	vector<int> pe;
 
	Min_Cost_Max_Flow_Graph(int n): n(n){
		g.resize(n);
	}
 
	void Add_Edge(int f, int t, int cap, int cost){
		g[f].push_back(edges.size());
		edges.push_back({t, cap, 0, cost});
		g[t].push_back(edges.size());
		edges.push_back({f, 0, 0, -cost});
	}
 
	void Spfa(int s){
		d.assign(n, inf);
		p.assign(n, -1);
		pe.assign(n, -1);
 
		vector<bool> inq(n, false);
		queue<int> q;
		q.push(s);
		d[s] = 0;
		inq[s] = 1;
 
		while(!q.empty()){
			auto v = q.front();
			q.pop();
			inq[v] = false;
 
			for (int edge_id : g[v]){
				auto& edge = edges[edge_id];
				if (edge.cap - edge.flow == 0){
					continue;
				}
 
				if (d[edge.to] > d[v] + edge.cost){
					d[edge.to] = d[v] + edge.cost;
					p[edge.to] = v;
					pe[edge.to] = edge_id;
					if (!inq[edge.to]){
						inq[edge.to] = true;
						q.push(edge.to);
					}
				}
			}
		}
	}
 
	pair<int,int> Augment(int s, int t){
		Spfa(s);
		if (p[t] == -1){
			return {0, 0};
		}
		int pushed_flow = inf;
		int sum_cost = 0;
		int v = t;
		while(v != s){
			auto& edge = edges[pe[v]];
			pushed_flow = min(pushed_flow, edge.cap - edge.flow);
			sum_cost += edge.cost;
			v = p[v];
		}
		v = t;
		while(v != s){
			auto& edge = edges[pe[v]];
			auto& rev_edge = edges[pe[v] ^ 1];
			edge.flow += pushed_flow;
			rev_edge.flow -= pushed_flow;
			v = p[v];
		}
		return {pushed_flow, sum_cost};
	}
 
	pair<int,int> Min_Cost_Max_Flow(int source, int sink){
		int flow = 0;
		int cost = 0;
		while(true){
			auto [cur_flow, cur_cost] = Augment(source, sink);
			if (cur_flow == 0){
				break;
			}
			flow += cur_flow;
			cost += cur_cost;
		}
		return {flow, cost};
	}
};