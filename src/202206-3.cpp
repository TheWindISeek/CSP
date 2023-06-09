#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cstring>

using namespace std;

typedef struct info{
	set<string> ops;
	set<string> res_type;
	set<string> res_name;
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
	for(const string& _op: role.ops) {
		if(_op.compare("*") == 0 || _op.compare(op) == 0) {
			flag = false;
			break;
		}
	}
	if(flag) return false;
	flag = true;
	//判断资源种类
	for(const string& _res_type: role.res_type) {
		if(_res_type.compare("*") == 0 || _res_type.compare(res_type) == 0) {
			flag = false;
			break;
		}
	}
	if(flag) return false;
	flag = true;
	//判断资源名称
	if(role.res_name.size() == 0) return true; //空数组的情况
	for(const string& _res_name: role.res_name) {
		if(_res_name.compare(res_name) == 0) {
			flag = false;
			break;
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
			bool b = canDo(roles[_conn.first], op, res_type, res_name);
			if(b)
				return true;
		}
	}
	//查看哪些角色被被授权给当前用户组
	for(auto& _conn: conns) {
		for(string& _group: groups) {
			if(_conn.second.group.find(_group) != _conn.second.group.end()) {
				bool b = canDo(roles[_conn.first], op, res_type, res_name);
				if(b)
					return true;
			}
		}
	}
	//都没找到
	return false;
}

int main () {
	cin.tie(0);
	int n, m, q;//角色数量 角色关联数量 待检查的操作数量
	scanf("%d %d %d", &n, &m, &q);
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
			role.ops.insert(s);
		}
		//资源种类
		scanf("%d", &no);
		while(no--) {
			cin >> s;
			role.res_type.insert(s);
		}
		//资源名称
		scanf("%d", &nn);
		while(nn--) {
			cin >> s;
			role.res_name.insert(s);
		}
		roles[name] = role;
	}
	
	for(int i = 0; i < m; ++i) {
		string name;
		int ns;
		Conn* conn;
		cin >> name >> ns;
		if(conns.find(name) == conns.end()) {
			conn = new Conn();
		} else {
			conn = &(conns[name]);
		}
		//读取角色关联
		for(int j = 0; j < ns; ++j) {
			string type, s;
			cin >> type >> s;
			if(strcmp(type.c_str(), "u") == 0) {
				conn->user.insert(s);
			} else {
				conn->group.insert(s);
			}
		}
		if(conns.find(name) == conns.end())
			conns[name] = *conn;
		//conns不能用map 因为有多重映射 不对 应该是用map 但是需要关联前后数据
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