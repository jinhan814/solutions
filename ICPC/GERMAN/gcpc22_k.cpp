#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, m; cin >> n >> m;
	string s; cin >> s;
	int p = 0;
	for (char c : s) if (p ^ (c != 'L')) m--; else p ^= 1;
	cout << max(m, 0) << '\n';
}