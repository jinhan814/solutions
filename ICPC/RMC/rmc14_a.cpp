#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, m; cin >> n >> m;
	int p = 0, acc = 0;
	for (; p < n; p++) {
		int x; cin >> x;
		acc += x;
		if (acc > m) break;
	}
	cout << p << '\n';
}