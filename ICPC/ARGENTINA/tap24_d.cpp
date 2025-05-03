#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int a, b, c; cin >> a >> b >> c;
	if (a < b) swap(a, b);
	if (a < c) swap(a, c);
	cout << "SN"[a < b + c] << '\n';
}