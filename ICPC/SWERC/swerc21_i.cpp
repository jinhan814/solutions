#include <bits/stdc++.h>
using namespace std;

template<typename T, typename F>
struct segtree {
	explicit segtree(int n, const T& e, const F& f) :
		sz(1 << __lg(n - 1) + 1), e(e), f(f), tree(sz << 1, e) {}
	void update(int i, T x) {
		tree[--i |= sz] = x;
		while (i >>= 1) tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
	}
	T query(int l, int r) const {
		T ret = e;
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret = f(ret, tree[l++]);
			if (~r & 1) ret = f(ret, tree[r--]);
		}
		return ret;
	}
private:
	const int sz; const T e; const F f;
	vector<T> tree;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n, a, b; cin >> n >> a >> b;
		vector p(n + 1, 0);
		for (int i = 1; i <= n; i++) cin >> p[i];

		const int inf = 1 << 30;
		segtree l(n, pair(-inf, 0), [](const auto& a, const auto& b) {
			return a.first > b.first ? a : b;
		});
		segtree r(n, pair(inf, 0), [](const auto& a, const auto& b) {
			return a.first < b.first ? a : b;
		});
		for (int i = 1; i <= n; i++) {
			l.update(i, { i + p[i], i });
			r.update(i, { i - p[i], i });
		}

		vector d(n + 1, -1);
		deque q(0, 0);
		auto update = [&](int i, int x) {
			d[i] = x;
			q.push_back(i);
			l.update(i, pair(-inf, 0));
			r.update(i, pair(inf, 0));
		};

		update(a, 0);
		while (q.size()) {
			int i = q.front(); q.pop_front();
			while (1) {
				auto [x, j] = l.query(max(1, i - p[i]), i);
				if (x < i) break;
				update(j, d[i] + 1);
			}
			while (1) {
				auto [x, j] = r.query(i, min(n, i + p[i]));
				if (x > i) break;
				update(j, d[i] + 1);
			}
		}
		cout << d[b] << '\n';
	}
}