#include <bits/stdc++.h>
using namespace std;
#define ll long long

int bfs(int source[], int target, vector<int> adj[]) {
	queue<int> q;
	bool visited[] = {false};
	int distance[] = {0};

	q.push(source[0]);

	while(!q.empty()) {
		int u = q.front();
		q.pop();

		if(!visited[u]) {
			for(int v : adj[u]) {
				distance[v] = distance[u]+1;
				if(v == target) return distance[v];
				q.push(v);
			}

			visited[u] = true;
		}
	}
	return -1;
}

class Solution {
  public:

		void print(vector<int>& v){
			cout << "[";
			for(int i=0;i<v.size();i++){
					cout << v[i];
					if(i+1<v.size()) cout << ", ";
			}
			cout << "]\n";
		}

		vector<int> bfs(vector<vector<int>> &adj) {
			queue<int> q;
			vector<bool> visited(adj.size(), false);
			vector<int> list;
			
			q.push(0);
			
			while(!q.empty()) {
				int u = q.front();
				q.pop();
				
				if(!visited[u]) {
					visited[u] = true;
					list.push_back(u);

					for(int a : adj[u]) {
						q.push(a);
					}
				}
			}

			print(list);
		}
};

vector<int> bfs(vector<vector<int>> &adj) {
	queue<int> q;
	vector<bool> visited(adj.size(), false);
	vector<int> list;
	
	q.push(0);
	
	while(!q.empty()) {
		int u = q.front();
		q.pop();

		list.push_back(u);

		for(int a : adj[u]) {
			if(!visited[a]) {
				q.push(a);
				visited[a] = true;
			}
			
		}
	}

	return list;
}