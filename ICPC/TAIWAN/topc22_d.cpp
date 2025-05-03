#include <bits/stdc++.h>
using namespace std;

template<int sz = 17>
struct segtree {
	void update(int i) {
		--i |= 1 << sz;
		tree[i] = 1;
		while (i >>= 1) tree[i] = 1;
	}
	int get_left(int i) const {
		--i |= 1 << sz;
		while (!tree[i]) i = i & 1 ? i >> 1 : is_pow(i) ? i - 1 << 1 | 1 : i - 1;
		while (!(i >> sz)) i = i << 1 | tree[i << 1 | 1];
		return i - (1 << sz) + 1;
	}
	int get_right(int i) const {
		--i |= 1 << sz;
		while (!tree[i]) i = ~i & 1 ? i >> 1 : is_pow(i + 1) ? i + 1 >> 1 : i + 1;
		while (!(i >> sz)) i = i << 1 | !tree[i << 1];
		return i - (1 << sz) + 1;
	}
private:
	bitset<1 << sz + 1> tree;
	static bool is_pow(int n) { return n == (n & -n); }
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];

	auto sol = [&] {
		vector buc(n, vector(0, 0));
		for (int i = 1; i <= n; i++) buc[v[i]].push_back(i);
		segtree tree;
		vector res(0, pair(0, 0));
		if (buc[0].size() != 1) return res;
		for (int x = 1; x < n; x++) {
			for (int i : buc[x - 1]) tree.update(i);
			for (int i : buc[x]) {
				int l = tree.get_left(i);
				int r = tree.get_right(i);
				if (v[l] == v[i] - 1) res.push_back({ i, l });
				else if (v[r] == v[i] - 1) res.push_back({ i, r });
				else return res;
			}
		}
		return res;
	};

	auto res = sol();
	if (res.size() != n - 1) return cout << -1 << '\n', 0;
	for (auto [a, b] : res) cout << a << ' ' << b << '\n';
}