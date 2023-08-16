const int inf = (1 << 30) + 1;
 
struct Flow_Graph{
	struct Edge{
		int to;
		int cap;
		int flow;
	};
 
	vector<Edge> edges;
	vector<vector<int>> g;
	vector<int> last;
	vector<int> d;
	vector<int> used;
	int n;
 
	Flow_Graph(int n): n(n){
		g.resize(n);
		used.resize(n);
		last.resize(n);
		d.resize(n, -1);
	}
 
	void Add_Edge(int f, int t, int cap, int flow){
		g[f].push_back(edges.size());
		edges.push_back({t, cap, flow});
		g[t].push_back(edges.size());
		edges.push_back({f, 0, -flow});
	}
 
	void Bfs(int source, int flow_restrict){
		queue<int> q;
		q.push(source);
		d[source] = 0;
 
		while(!q.empty()){
			int v = q.front();
			q.pop();
			for (int edge_id : g[v]){
				auto& edge = edges[edge_id];
				if (d[edge.to] == -1 && edge.cap - edge.flow >= flow_restrict){
					d[edge.to] = d[v] + 1;
					q.push(edge.to);
				}
			}
		}
	}
 
	int Dfs(int v, int sink, int min_flow){
		used[v] = 1;
		if (v == sink){
			return min_flow;
		}
 
		for (;last[v] < g[v].size(); last[v]++){
			int edge_id = g[v][last[v]];
			auto& edge = edges[edge_id];
			auto& rev_edge = edges[edge_id ^ 1];
			if (d[edge.to] == d[v] + 1 && used[edge.to] != 1 && edge.cap - edge.flow > 0){
				int flow = Dfs(edge.to, sink, min(min_flow, edge.cap - edge.flow));
				if (flow > 0){
					edge.flow += flow;
					rev_edge.flow -= flow;
					return flow;
				}
			}
		}
 
		return 0;
	}
 
	long long Max_Flow(int source, int sink){
		long long flow = 0;
 
		for (int i = 15; i >= 0; i--){
			while(true){
				fill(used.begin(), used.end(), 0);
				fill(d.begin(), d.end(), -1);
				fill(last.begin(), last.end(), 0);
 
				Bfs(source, (1 << i));
 
				if (d[sink] == -1){
					break;
				}
 
				while(int pushed_flow = Dfs(source, sink, inf)){
					flow += pushed_flow;
					fill(used.begin(), used.end(), 0);
				}
			}
		}
 
		return flow;
	}
};