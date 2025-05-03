#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	if (m < n / 2 || m == n) return cout << -1 << '\n', 0;
	int d = m - n / 2;
	string res;
	for (int i = 0; i < d >> 1; i++) res += "()";
	for (int i = 0; i < n / 2 - d; i++) res += "(";
	for (int i = 0; i < n / 2 - d; i++) res += ")";
	for (int i = 0; i < d + 1 >> 1; i++) res += "()";
	cout << res << '\n';
}