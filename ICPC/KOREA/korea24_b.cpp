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
	void merge(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return;
		if (p[a] > p[b]) swap(a, b);
		p[a] += p[b], p[b] = a;
	}
private:
	vector<int> p;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];
	union_find uf(1'000'001);
	for (int i = 0; i < n; i++) uf.merge(a[i], b[i]);
	vector c(1'000'001, 0);
	for (int i = 0; i < n; i++) c[uf.find(a[i])]++;
	int res = 0;
	for (int i = 0; i < 1'000'001; i++) {
		if (i != uf.find(i)) continue;
		res += min(uf.cnt(i), c[i]);
	}
	cout << res << '\n';
}