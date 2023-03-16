#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
    //最早开始时间
    int early[380];
    //最晚开始时间
    int later[380];
    //依赖关系
    int a[120];
    //花费时间
    int cost[120];

    int n, m;
    int flag = 1;
    scanf("%d %d", &n, &m);
    //读取依赖关系
    for(int i = 1; i <= m; ++i) {
        scanf("%d", &a[i]);
    }
    //所需天数
    for(int i = 1; i <= m; ++i) {
        scanf("%d", &cost[i]);
    }
    //初始化0天
    early[0] = 0;
    cost[0] = 1;

    //计算最早完成时间
    for(int i = 1; i <= m; ++i) {
        early[i] = early[a[i]] + cost[a[i]];
        //无法正常完成
        if(early[i] + cost[i] > n+1) {
            flag = 0;
        }
    }
    //输出最早开始时间
    for(int i = 1; i <= m; ++i) {
        printf("%d", early[i]);
        if(i != m) {
            printf(" ");
        }
    }
    //判断是否需要计算最晚完成时间
    if(flag) {
        for(int i = 1; i <= m; ++i) {
            later[i] = n+1;
        }
        for(int i = m; i >= 1; --i) {
            int value = n+1;
            for(int j = i; j <= m; ++j) {
                    //如果依赖项是当前的
                if(a[j] == i) {
                    value = min(value, later[j]);
                }
            }
            later[i] = value - cost[i];
            /*
            later[i] -= cost[i];
          //  printf("\ni-later:%d\n", later[i]);
            if(later[a[i]] > later[i]-cost[a[i]]) {
                later[a[i]] = later[i];
            }
            */
        }
        printf("\n");
        //输出最晚开始时间
        for(int i = 1; i <= m; ++i) {
            printf("%d", later[i]);
            if(i != m) {
                printf(" ");
            }
        }
    }
    return 0;
}
