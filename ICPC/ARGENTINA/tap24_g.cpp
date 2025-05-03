#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	vector v(128, 0);
	for (char c : s) v[c]++;
	cout << min({ v['T'], v['P'], v['A'] + v['U'] }) << '\n';
}