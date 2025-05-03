#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int main() {
	auto ask = [](i64 n) { cout << "? " << n << endl; i64 x; cin >> x; return x; };
	i64 s = 1, x = 0;
	for (; (x = ask(s)) == s; s <<= 1);
	cout << "! " << s - x << endl;
}