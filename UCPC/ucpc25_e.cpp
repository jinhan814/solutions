#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	sort(v.begin(), v.end());
	i64 acc = 0;
	for (int i = 0, j = 0; i < n; i = j) {
		while (j < n && v[i] == v[j]) j++;
		i64 cnt = j - i;
		acc += cnt * (cnt + 1) / 2;
	}
	cout << i64(n) * (n + 1) / 2 - acc + 1 << '\n';
}