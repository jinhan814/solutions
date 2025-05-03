#include <bits/stdc++.h>
using namespace std;

struct fenwick {
	fenwick(int n) : sz(n), tree(n + 1) {}
	void update(int i, int x) {
		for (; i <= sz; i += i & -i) tree[i] += x;
	}
	int query(int i) const {
		int ret = 0;
		for (; i; i -= i & -i) ret += tree[i];
		return ret;
	}
private:
	int sz;
	vector<int> tree;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int q; cin >> q;
	vector v(q, array<int, 5>{});
	for (auto& [a, b, c, d, e] : v) {
		cin >> a >> b >> c;
		if (a == 2) cin >> d >> e;
	}

	// x compress
	{
		vector buc(0, 0);
		for (auto& [a, b, c, d, e] : v) {
			buc.push_back(b);
			if (a == 2) buc.push_back(d);
		}
		sort(buc.begin(), buc.end());
		buc.erase(unique(buc.begin(), buc.end()), buc.end());
		auto get_idx = [&](int x) { return ranges::lower_bound(buc, x) - buc.begin() + 1; };
		for (auto& [a, b, c, d, e] : v) {
			b = get_idx(b);
			if (a == 2) d = get_idx(d);
		}
	}

	// y compress
	{
		vector buc(0, 0);
		for (auto& [a, b, c, d, e] : v) {
			buc.push_back(c);
			if (a == 2) buc.push_back(e);
		}
		sort(buc.begin(), buc.end());
		buc.erase(unique(buc.begin(), buc.end()), buc.end());
		auto get_idx = [&](int x) { return ranges::lower_bound(buc, x) - buc.begin() + 1; };
		for (auto& [a, b, c, d, e] : v) {
			c = get_idx(c);
			if (a == 2) e = get_idx(e);
		}
	}

	vector res(q, 0LL);

	fenwick tree(2 * q);

	auto dnc1 = [&](const auto& self, int l, int r) -> void {
		if (l == r) return;
		int mid = l + r >> 1;
		self(self, l, mid);
		self(self, mid + 1, r);

		vector buc(0, 0);
		for (int i = l; i <= mid; i++) {
			if (v[i][0] == 2) continue;
			buc.push_back(i);
		}
		sort(buc.begin(), buc.end(), [&](int i, int j) {
			return v[i][1] < v[j][1] || v[i][1] == v[j][1] && v[i][2] < v[j][2];
		});

		vector idx(0, 0);
		for (int i = mid + 1; i <= r; i++) {
			if (v[i][0] == 1) continue;
			idx.push_back(i);
			idx.push_back(i + q);
		}
		sort(idx.begin(), idx.end(), [&](int i, int j) {
			int a = i < q ? v[i][1] - 1 : v[i - q][3];
			int b = j < q ? v[j][1] - 1 : v[j - q][3];
			return a < b;
		});

		int p = 0;
		for (int i : idx) {
			if (i < q) {
				int x = v[i][1] - 1;
				while (p < buc.size() && v[buc[p]][1] <= x) tree.update(v[buc[p++]][2], 1);
				res[i] -= tree.query(v[i][4]);
				res[i] += tree.query(v[i][2] - 1);
			}
			else {
				int x = v[i -= q][3];
				while (p < buc.size() && v[buc[p]][1] <= x) tree.update(v[buc[p++]][2], 1);
				res[i] += tree.query(v[i][4]);
				res[i] -= tree.query(v[i][2] - 1);
			}
		}
		while (p--) {
			tree.update(v[buc[p]][2], -1);
		}
	};

	auto dnc2 = [&](const auto& self, int l, int r) -> void {
		if (l == r) return;
		int mid = l + r >> 1;
		self(self, l, mid);
		self(self, mid + 1, r);

		vector buc(0, 0);
		for (int i = l; i <= mid; i++) {
			if (v[i][0] == 1) continue;
			buc.push_back(i);
			buc.push_back(i + q);
		}
		sort(buc.begin(), buc.end(), [&](int i, int j) {
			int a = i < q ? v[i][1] : v[i - q][3] + 1;
			int b = j < q ? v[j][1] : v[j - q][3] + 1;
			return a < b;
		});

		vector idx(0, 0);
		for (int i = mid + 1; i <= r; i++) {
			if (v[i][0] == 2) continue;
			idx.push_back(i);
		}
		sort(idx.begin(), idx.end(), [&](int i, int j) {
			return v[i][1] < v[j][1] || v[i][1] == v[j][1] && v[i][2] < v[j][2];
		});

		int p = 0;
		for (int i : idx) {
			while (p < buc.size()) {
				if (buc[p] < q) {
					int x = v[buc[p]][1];
					if (x > v[i][1]) break;
					tree.update(v[buc[p]][2], 1);
					tree.update(v[buc[p]][4] + 1, -1);
					p++;
				}
				else {
					int x = v[buc[p] - q][3] + 1;
					if (x > v[i][1]) break;
					tree.update(v[buc[p] - q][2], -1);
					tree.update(v[buc[p] - q][4] + 1, 1);
					p++;
				}
			}
			res[i] += tree.query(v[i][2]);
		}
		while (p--) {
			if (buc[p] < q) {
				int x = v[buc[p]][1];
				tree.update(v[buc[p]][2], -1);
				tree.update(v[buc[p]][4] + 1, 1);
			}
			else {
				int x = v[buc[p] - q][3] + 1;
				tree.update(v[buc[p] - q][2], 1);
				tree.update(v[buc[p] - q][4] + 1, -1);
			}
		}
	};

	dnc1(dnc1, 0, q - 1);
	dnc2(dnc2, 0, q - 1);

	for (int i = 1; i < q; i++) res[i] += res[i - 1];
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}