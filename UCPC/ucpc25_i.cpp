#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	sort(v.begin(), v.end());
	int p = 0;
	for (int i = 0; i < n; i++) if (v[i] == p) p++;
	cout << (v[n - 1] ? p + 1 : 0) << '\n';
	for (int x : v) cout << x << ' ';
	cout << '\n';
}