#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int a, b, c; cin >> a >> b >> c;
	int res = (c - a - 1) / (b - a);
	cout << 2 * res + 1 << '\n';
}