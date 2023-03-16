#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

int n, l, s;

int p[52][52];

typedef struct node {
    int x,y;
    // node(int _x, int _y):x(_x), y(_y) {}
} node;

bool operator<(const struct node& a, const struct node& b)
{
    if(a.x != b.x) {
        return a.x < b.x;
    }
    return a.y < b.y;
}

set<node> st;

//以n点为最左边的点是否可以作为藏宝图的一部分
bool match(const node& n) {
    int x = n.x, y = n.y;
    for(int i = 0; i <= s; ++i) {
        for(int j = 0; j <= s; ++j) {
                if(x+i > l || y+j > l)
                    return false;
            if((p[i][j] && st.find({x+i, y+j}) == st.end())
               || (!p[i][j] && st.find({x+i, y+j}) != st.end()))
                return false;
        }
    }
    return true;
}
int main()
{
    scanf("%d %d %d", &n, &l, &s);
    int x,y;
    for(int i = 0; i < n; ++i) {
        scanf("%d %d", &x, &y);
        node no;
        no.x = x;
        no.y = y;
        st.insert(no);
    }

    for(int i = s; i >= 0; --i) {
        for(int j = 0; j <= s; ++j) {
            scanf("%d", &p[i][j]);
        }
    }

   /* for(const node &no : st) {
        cout << no.x << ' ' << no.y <<endl;
    }*/

    /*cout << endl;

    for(int i = s; i >= 0; --i) {
        for(int j = 0; j <= s; ++j) {
            printf("%4d", p[i][j]);
        }
        printf("\n");
    }*/
    int cnt = 0;
    for(const node &no : st) {
        //对于每一个都判断他是否可以作为
        if(match(no)) {
            cnt++;
        }
    }
    printf("%d", cnt);
    return 0;
}
