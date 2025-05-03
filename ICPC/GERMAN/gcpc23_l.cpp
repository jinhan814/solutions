#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	int p = 0, acc = 0;
	while (p < s.size()) { acc += s[p++] == '(' ? 1 : -1; if (!acc) break; }
	string t = s;
	rotate(t.begin(), t.begin() + p, t.end());
	cout << (s == t ? "no" : t) << '\n';
}