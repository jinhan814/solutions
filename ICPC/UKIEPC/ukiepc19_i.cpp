#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n + 1, vector(n + 1, 0));
	for (int i = 1; i <= n; i++) v[n][i] = 1;
	for (int i = n - 1; i >= 1; i--) {
		for (int j = 1; j <= i; j++)
			v[i][j] = v[i + 1][j] + v[i + 1][j + 1];
	}
	if (v[1][1] > k) return cout << "impossible" << '\n', 0;
	for (int i = n; i >= 1; i--) v[i][1] += k - v[1][1];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++)
			cout << v[i][j] << " \n"[i == j];
	}
}