#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int a, b, c; cin >> a >> b >> c;
	if (a < b) swap(a, b);
	if (a < c) swap(a, c);
	cout << "SN"[a < b + c] << '\n';
}