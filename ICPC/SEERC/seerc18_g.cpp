#include <bits/stdc++.h>
using namespace std;

template<int sz>
struct data_structure { // 1-indexed
	data_structure() {
		for (int i = 0; i <= sz; i++) cnt[i] = 1 << (sz - i);
		tree.set();
	}
	void flip(int i) {
		tree[--i |= 1 << sz].flip();
		for (int lvl = sz - 1; i >>= 1; lvl--) {
			if (tree[i]) cnt[sz - lvl]--, tree[i] = 0;
			if (lvl < sz - 1 && (!tree[i << 1] || !tree[i << 1 | 1])) continue;
			if (tree[i << (sz - lvl)] != tree[i << (sz - lvl) | (1 << (sz - lvl - 1))]) continue;
			cnt[sz - lvl]++, tree[i] = 1;
		}
	}
	int get(int n, int x) const {
		int res = cnt[x];
		res -= (1 << sz) - (1 << n) >> x;
		return res;
	}
private:
	int cnt[sz + 1];
	bitset<1 << sz + 1> tree;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	data_structure<20> d1, d2;
	auto query = [&] {
		auto res = 1LL;
		for (int i = n; i > 0; i--) {
			auto a = (1LL << n - i) - d1.get(n, i);
			auto b = (1LL << n - i) - d2.get(n, i);
			res += (a + b << n - i) - a * b << 2;
		}
		return res;
	};
	while (q--) {
		int a, b; cin >> a >> b;
		if (a) d1.flip(b);
		else d2.flip(b);
		cout << query() << '\n';
	}
}