#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	string s; cin >> s;
	vector v(128, 0);
	for (char c : s) v[c]++;
	cout << min({ v['T'], v['P'], v['A'] + v['U'] }) << '\n';
}