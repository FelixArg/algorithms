template <typename T>
struct min_queue{
	stack<pair<T, T>> s1, s2;
	T get_min(){
		if (s1.empty() || s2.empty()){
			return s1.empty() ? s2.top().second : s1.top().second;
		}
		else{
			return min(s1.top().second, s2.top().second);
		}
	}
	void push(T x){
		T minima = s1.empty() ? x : min(x, s1.top().second);
		s1.push(make_pair(x, minima));
	}
	void pop(){
		if (s2.empty())
		while (!s1.empty()) {
			T element = s1.top().first;
			s1.pop();
			T minima = s2.empty() ? element : min(element, s2.top().second);
			s2.push(make_pair(element, minima));
		}
		s2.pop();
	}
};
