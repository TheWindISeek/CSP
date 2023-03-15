#include <cstdio>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;
//直接模拟拿不全
//需要算法性能的优化

int count[200003];

int main () {
	int n, m, k;
	
	scanf("%d %d %d", &n, &m, &k);
	while (n--) {
		int begin, check;
		int left, right;		
		scanf("%d %d", &begin, &check);
		left = begin - check - k+1 <= 0 ? 0 : begin-check-k+1;
		right = begin - k <= 0 ? 0 : begin-k;
		for(int i = left; i <= right; ++i) {
			++count[i];
		}
	}
	while (m--) {
		int time;
		scanf("%d", &time);
		printf("%d\n", count[time]);
	}
	return 0;
}