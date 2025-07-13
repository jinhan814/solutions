#include <bits/stdc++.h>
using namespace std;

struct union_find {
	union_find(int n) : p(n, -1) {}
	int find(int x) {
		return p[x] < 0 ? x : p[x] = find(p[x]);
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
	int n; cin >> n;
	vector v(n, 0), h(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	for (int i = 1; i < n; i++) {
		if (v[i - 1] < v[i]) h[i] = h[i - 1];
		else h[i] = h[i - 1] + 1;
	}
	vector idx(n, 0);
	iota(idx.begin(), idx.end(), 0);
	sort(idx.begin(), idx.end(), [&](int i, int j) {
		if (v[i] != v[j]) return v[i] < v[j];
		return h[i] < h[j];
	});
	union_find uf(n);
	int res = n;
	for (int i = 1; i < n; i++) {
		if (h[i - 1] != h[i]) continue;
		if (v[i - 1] + 1 == v[i]) res -= uf.merge(i - 1, i);
	}
	for (int i = 1; i < n; i++) {
		if (v[idx[i - 1]] != v[idx[i]]) continue;
		if (h[idx[i - 1]] + 1 == h[idx[i]]) res -= uf.merge(idx[i - 1], idx[i]);
	}
	cout << res << '\n' << n << '\n';
}