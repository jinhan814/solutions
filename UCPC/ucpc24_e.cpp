#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector c(n, 0), v(n, 0);
	for (int i = 0; i < n; i++) cin >> c[i];
	for (int i = 0; i < n; i++) cin >> v[i];

	int p = 0;
	while (p < n && !c[p]) p++;
	if (p == n) return cout << 0 << ' ' << 0 << '\n', 0;

	for (int i = 0; i < n; i++) {
		if (!c[i]) continue;
		int j = i + 1;
		while (!c[j % n]) j++;
		for (int k = i + 1; k != j; k++) {
			if (c[i] == c[j % n]) c[k % n] = c[i];
			else if (k - i < j - k) c[k % n] = c[i];
			else if (k - i > j - k) c[k % n] = c[j % n];
		}
	}

	i64 a = 0, b = 0;
	vector buc(0, 0);
	for (int i = 0; i < n; i++) {
		if (c[i] == 0) buc.push_back(v[i]);
		else if (c[i] == 1) a += v[i];
		else if (c[i] == 2) b += v[i];
	}
	sort(buc.begin(), buc.end(), greater{});
	for (int i = 0; i < buc.size(); i++) {
		if (~i & 1) a += buc[i];
		else b += buc[i];
	}
	cout << a << ' ' << b << '\n';
}