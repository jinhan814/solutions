#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n; cin >> n;
	int pa = -1, pb = -1, f = 1;
	for (int i = 0; i < n; i++) {
		int a, b; cin >> a >> b;
		if (pa > a) f = 0;
		if (pb > b) f = 0;
		pa = a, pb = b;
	}
	cout << (f ? "yes" : "no") << '\n';
}