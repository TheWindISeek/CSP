#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cstring>

using namespace std;

typedef struct info{
	vector<string> ops;
	vector<string> res_type;
	vector<string> res_name;
}Role;

typedef struct connection {
	set<string> group;
	set<string> user;
}Conn;

map<string, Role> roles;//角色名对应 相关操作信息
map<string, Conn> conns;//角色名对应 可被授权的组信息

//角色role是否可执行操作op 对资源类型为res_type 资源名称为res_name
bool canDo(Role& role, string& op, string& res_type, string& res_name) {
	bool flag = true;
	//判断操作
	for(string& _op: role.ops) {
		if(_op.compare("*") == 0 && _op.compare(op) == 0) {
			flag = false;
			break;
		}
	}
	if(flag) return false;
	//判断资源种类
	for(string& _res_type: role.res_type) {
		if(_res_type.compare("*") == 0 && _res_type.compare(res_type) == 0) {
			flag = false;
			break;
		}
	}
	if(flag) return false;
	//判断资源名称
	if(role.res_name.size() == 0) return true; //空数组的情况
	for(string& _res_name: role.res_name) {
		if(_res_name.compare(res_name) == 0) {
			flag = false;
		}
	}
	if(flag) return false;

	return true;
}
//对于用户名称为user_name 所属的组为groups 
//是否可执行操作为op 资源类型为res_type 资源名称为res_name的操作
bool check(string& user_name, vector<string>& groups,
			string& op, string& res_type, string& res_name) {
	//检查哪些角色可被授权给当前用户
	for(auto& _conn: conns) {
		if(_conn.second.user.find(user_name) != _conn.second.user.end()) {
			if(canDo(roles[_conn.first], op, res_type, res_name))
				return true;
		}
	}
	//查看哪些角色被被授权给当前用户组
	for(auto& _conn: conns) {
		for(string& _group: groups) {
			if(_conn.second.group.find(user_name) != _conn.second.group.end()) {
				if(canDo(roles[_conn.first], op, res_type, res_name))
					return true;
			}
		}
	}
	//都没找到
	return false;
}

int main () {
	/*
		验证用户的身份
			通过用户提供的口令password是否正确

		验证用户的权限
			验证用户提供的智能卡是否正确
			必须是在口令正确的前提下再去验证智能卡

		在授权的步骤中
			权限策略会被用于判断用户是否能给操作系统中的某个资源

		首先设定多个角色
			角色绑定了多个清单
				允许访问的资源的种类
				资源的名称
				对资源的操作

		接着将前一步骤中的用户和一个和多个角色关联
		这些角色的操作并集就是用户可执行的多个操作

		用户
			用户名称： 字符串 唯一标识一个用户
			用户组： 数组 若干字符串 表示该用户所属的用户组

		待授权的行为
			主体：用户 包括上述两个信息
			操作 字符串 （动词 Read Open Close）
			资源：操作对象 资源种类和资源名称描述 资源种类是唯一的

		鉴别过程就会对用户名称和所属用户组进行识别

		角色
			名称 字符串 唯一标识一个角色
			操作清单 数组 包含一个或者多个操作
			资源种类清单 数组 包含一个或多个资源种类 允许进行种类集合
			资源名称清单 数组 包含若干资源名称 表示该角色允许操作的资源的名称集合

		检查操作清单
			如果不包含该操作 并且 不包含 *
				return false
			检查资源清单
				如果不包含该资源 并且 不包含 *
					return false
				检查资源名称清单
					如果不包含该资源的名称 并且 资源名称清单不是空数组
						return false
					return true

		角色关联
			角色名称：字符串 指明角色
			授权对象清单 数组 一个或多个用户名称或用户组名称

		检查所有角色关联的授权对象名单
			如果清单中包含该用户的名称 或者 该清单中包含该用户所属的某一个用户组的名称
				给用户授权该角色
			对于所有匹配的角色
				如果存在一个可执行的角色
					执行
				不能执行该操作
		


		一个角色的操作清单 只能用允许列表的方式列举该角色允许进行的操作
		而不能禁止角色进行某个操作
		不能存储用户和用户组的关联 应该根据每次待授权的行为进行独立判断
	*/	
	int n, m, q;//角色数量 角色关联数量 待检查的操作数量
	
	for(int i = 0; i < n; ++i) {
		string name;
		string s;
		int nv, no, nn;
		Role role;
		//读取角色信息
		cin >> name;
		//可执行的操作
		scanf("%d", &nv);
		while(nv--) {
			cin >> s;
			role.ops.push_back(s);
		}
		//资源种类
		scanf("%d", &no);
		while(no--) {
			cin >> s;
			role.res_type.push_back(s);
		}
		//资源名称
		scanf("%d", &nn);
		while(nn--) {
			cin >> s;
			role.res_name.push_back(s);
		}
		roles[name] = role;
	}

	for(int i = 0; i < m; ++i) {
		string name;
		int ns;
		Conn conn;
		cin >> name >> ns;
		//读取角色关联
		for(int j = 0; j < ns; ++j) {
			string type, s;
			cin >> type >> s;
			if(strcmp(type.c_str(), "u") == 0) {
				conn.user.insert(s);
			} else {
				conn.group.insert(s);
			}
		}
		conns[name] = conn;
	}

	while(q--) {
		string user_name;
		vector<string> groups;
		int ng;
		
		cin >> user_name >> ng;
		while(ng--) {
			string s;
			cin >> s;
			groups.push_back(s);	
		}
		//将要执行的操作 资源种类 资源名称
		string op, res_type, res_name;
		cin >> op >> res_type >> res_name;
		//判断是否可以执行操作
		if(check(user_name, groups, op, res_type, res_name)) {
			printf("1");
		} else {
			printf("0");
		}
		printf("\n");
	}
	return 0;
}