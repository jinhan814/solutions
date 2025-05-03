#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(0, 0LL);
	for (int i = 0; i < n; i++) {
		auto x = 0LL; cin >> x;
		if (x) v.push_back(x);
	}
	sort(v.begin(), v.end());
	int res = 0;
	for (int i = 0, j = 0; i < v.size(); i = j) {
		while (j < v.size() && v[i] == v[j]) j++;
		if (j - i & 1) res = 1;
	}
	cout << (res ? "Rami" : "Yessine");
}