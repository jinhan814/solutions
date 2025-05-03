#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(0, string{});
	for (int i = 0; i < n; i++) {
		int k; cin >> k >> k;
		while (k--) { string s; cin >> s; v.push_back(s); }
	}
	sort(v.begin(), v.end());
	int mx = 0, cnt = 0;
	string res;
	for (int i = 0, j = 0; i < v.size(); i = j) {
		while (j < v.size() && v[i] == v[j]) j++;
		if (mx < j - i) mx = j - i, cnt = 0;
		if (mx == j - i) cnt++, res = v[i];
	}
	cout << (cnt > 1 ? "-1" : res) << '\n';
}