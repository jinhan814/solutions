#include <bits/stdc++.h>
using namespace std;

struct union_find {
	union_find(int n) : p(n, -1) {}
	int find(int x) {
		return p[x] < 0 ? x : p[x] = find(p[x]);
	}
	int cnt(int x) {
		return -p[find(x)];
	}
	bool merge(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return 0;
		if (p[a] > p[b]) swap(a, b);
		p[a] += p[b];
		p[b] = a;
		return 1;
	}
private:
	vector<int> p;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, m; cin >> n >> m;
		union_find uf(n);
		int f = 1, mx = 1;
		for (int i = 0; i < m; i++) {
			int a, b; cin >> a >> b;
			f &= uf.merge(a, b);
			mx = max(mx, uf.cnt(a));
		}
		if (n <= 2) cout << -1 << '\n';
		else if (f == 0) cout << 0 << '\n';
		else cout << 4 - min(mx, 3) << '\n';
	}
}