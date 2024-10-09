#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n; cin >> n;
	vector v(n + 1, 1);
	for (int i = 2; i <= n; i++) { int x; cin >> x; v[x + 1] = i; }
	for (int i = 0; i < n; i++) cout << v[i] << ' ';
	cout << '\n';
}