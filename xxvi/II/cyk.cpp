#include <bits/stdc++.h>
#include "cyklib.hpp"
using namespace std;

/*
	Author: Rafal Starypan
	Contest: XXVI OI - II stage
	Problem name: Przesuniecie cykliczne
	Problem link: https://szkopul.edu.pl/problemset/problem/e86SVYtB-4G3yVTFi2unCZWa/site/?key=statement

	The solution scores 42 points.
*/

const int JUMP = 45;

int timer = 1;
map<long long, int> mp;

int main() {
	
	long long x = circular_shift(0);
	mp[x] = timer;
	timer++;
	
	for (int i = 0; i < JUMP-1; i++) {
		x = circular_shift(1);
		if (mp.count(x)) {
			give_answer(timer-1);
			return 0;
		}
		mp[x] = timer;
		timer++;
	}
	
	int jumpCnt = 1;
	while (true) {
		x = circular_shift(JUMP);
		if (mp.count(x)) {
			int tmp = JUMP - mp[x];
			int n = jumpCnt * JUMP + tmp;
			give_answer(n);
			return 0;
		}
		jumpCnt++;
	}
	
	
    return 0;
}
