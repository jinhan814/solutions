#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	string s; cin >> s;
	int p = 0;
	for (char c : s) if (p ^ (c != 'L')) m--; else p ^= 1;
	cout << max(m, 0) << '\n';
}