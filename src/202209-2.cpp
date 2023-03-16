#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int min_cost = INT_MAX;

const int N = 50, M = 3e5+10;
int n, x, total;
int dp[N][M];
int price[N];

int main()
{

    scanf("%d %d", &n,&x);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &price[i]);
        total += price[i];
    }
    int m = total - x;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            dp[i][j] = dp[i-1][j];
            if(j >= price[i]) {
                dp[i][j] = max(dp[i][j], dp[i-1][j-price[i]] + price[i]);
            }
        }
    }
    printf("%d", total-dp[n][m]);
    return 0;
}
