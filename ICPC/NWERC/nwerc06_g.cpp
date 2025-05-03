#include <bits/stdc++.h>
using namespace std;

auto construct = [] {
	vector c(10'000, 0);
	for (int i = 2; i * i < 10'000; i++) {
		if (c[i]) continue;
		for (int j = i * i; j < 10'000; j += i) c[j] = 1;
	}
	vector adj(10'000, vector(0, 0));
	for (int i = 1'000; i < 10'000; i++) {
		if (c[i]) continue;
		string s = to_string(i);
		for (int p = 0; p < 4; p++) {
			int prv = s[p];
			for (int x = 0; x < 10; x++) {
				s[p] = x + 48;
				int j = stoi(s);
				if (j < 1'000 || j == i) continue;
				if (!c[j]) adj[i].push_back(j);
			}
			s[p] = prv;
		}
	}
	return adj;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int a, b; cin >> a >> b;
		vector adj = construct();
		vector c(10'000, -1), q(0, 0);
		c[a] = 0, q.push_back(a);
		for (int d = 1; q.size(); d++) {
			vector nq(0, 0);
			for (int i : q) for (int j : adj[i]) {
				if (c[j] != -1) continue;
				c[j] = d, nq.push_back(j);
			}
			q.swap(nq);
		}
		if (c[b] != -1) cout << c[b] << '\n';
		else cout << "Impossible" << '\n';
	}
}