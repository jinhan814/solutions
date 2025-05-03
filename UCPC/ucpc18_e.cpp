#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, x, p; cin >> n >> x >> p;

	vector a(0, 0), b(0, 0), buc{ p };
	for (int i = p / 2; i >= 1; i /= 2) a.push_back(i);
	while (buc.size()) {
		vector nbuc(0, 0);
		for (int x : buc) {
			b.push_back(x);
			if (2 * x <= n) nbuc.push_back(2 * x);
			if (2 * x + 1 <= n) nbuc.push_back(2 * x + 1);
		}
		buc.swap(nbuc);
	}

	if (a.size() > x - 1 || b.size() > n - x + 1) {
		cout << -1 << '\n';
		return 0;
	}

	vector v(n + 1, 0), c(n + 1, 0);
	for (int i = 1; i <= a.size(); i++) v[a[a.size() - i]] = i, c[i] = 1;
	for (int i : b) v[i] = x, c[x++] = 1;
	for (int i = 1, j = 1; i <= n; i++) {
		if (v[i]) continue;
		while (c[j]) j++;
		v[i] = j, c[j] = 1;
	}
	for (int i = 1; i <= n; i++) cout << v[i] << '\n';
}