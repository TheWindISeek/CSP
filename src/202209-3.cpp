#include <set>
#include <cstdio>
#include <map>
#include <iostream>
#include <vector>

using namespace std;

typedef struct info {
    int d, u, ri;
} info;

int main ()
{
    int n;
    int r, m, p;
    int d, u, ri;
    
    map<int, pair<int, int> > risk;
    set<int> s;
    vector<info> before[1020];//记录每天收到的信息
    //读取数据
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        //读取风险地区数和漫游信息数
        scanf("%d %d", &r, &m);
        //读取风险地区
        for(int k = 0; k < r; ++k) {
            scanf("%d", &p);
            //连续的情况
            if(risk[p].second >= i-1) {// 注意这里是i-1
                risk[p].second = i+6;
            } else { //不连续的情况
                risk[p].first = i; // 不然的话 重置日期
                risk[p].second = i+6;
            }
        }
        
        //读取漫游信息
        for(int k = 0; k < m; ++k) {
            scanf("%d %d %d", &d, &u, &ri);
            //记录到对应天中
            if(d <= i)
                before[i].push_back({d, u, ri}); 
        }
        s.clear();
        //判断哪些用户是危险的
        for(int k = (i >= 6 ? i-6 : 0); k <= i; ++k) { //近7日接受到的数据
            for(auto j = before[k].begin(); j != before[k].end(); ++j) {
                //首先这条信息得是7天内的 其次这天必须是当前连续危险地区
                //这里这么写的话 会出现risk自动创建的情况 这不是我希望见到的
                if(j->d+6 >= i 
                    && risk.find(j->ri) != risk.end() 
                    && risk[j->ri].first <= j->d && j->d <= risk[j->ri].second
                    && risk[j->ri].second >= i
                    && j->d <= i) {
                    s.insert(j->u);
                }
            }
        }
        //输出当前危险表
        printf("%d", i);
        for(int user : s) {
            printf(" %d", user);
        }
        printf("\n");
        //printf("输出结束\n");
    }
    return 0;
}
