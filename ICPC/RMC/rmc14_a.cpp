#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	int p = 0, acc = 0;
	for (; p < n; p++) {
		int x; cin >> x;
		acc += x;
		if (acc > m) break;
	}
	cout << p << '\n';
}