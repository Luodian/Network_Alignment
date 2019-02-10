#include"header.h"
#include"SCC.h"

using namespace std;
const int MAXN = 10010;
map<int, set<int> > cc;
set<int> graph[MAXN];
int parent[MAXN];
int grade[MAXN];
int cnt;//nums of CC
map<int, int> stats;

int father (int u)
{
	while (u != parent[u])
	{
		parent[u] = parent[parent[u]];
		u = parent[u];
	}
	return u;
}

bool connect (int u, int v) // union u and v
{
	int fu = father (u);
	int fv = father (v);
	if (fu == fv) return false;
	if (grade[fu] > grade[fv])
	{
		parent[fv] = fu;
		grade[fu] += grade[fv];
	}
	else
	{
		parent[fu] = fv;
		grade[fv] += grade[fu];
	}
	cnt--;
	return true;
}

bool isConnected (int u, int v)
{
	return father (u) == father (v);
}

void getCC (int n, string label)
{
	ofstream ofs;
	ofs.open ("./wcc_info_stats/" + label + "_out.txt", std::ofstream::out);
	for (int i = 0; i < n; i++)
	{
		parent[i] = i;
		grade[i] = 1;
	}
	cnt = n;
	for (int i = 0; i < n; i++)
	{
		for (set<int>::iterator it = graph[i].begin (); it != graph[i].end (); ++it)
		{
			connect (i, *it);
		}
	}
	cc.clear ();
	for (int i = 0; i < n; i++)
	{
		int fa = father (i);
		map<int, set<int> >::iterator it = cc.find (fa);
		if (it == cc.end ())
		{
			set<int> tmp;
			tmp.insert (i);
			cc[fa] = tmp;
		}
		else
		{
			(it->second).insert (i);
		}
	}
	ofs << "In this graph we can find: " << cnt + 1 << " connected component\n";
	int i = 0;
	for (map<int, set<int> >::iterator it = cc.begin (); it != cc.end (); it++)
	{
		ofs << "In connected component " << ++i << " there are vertexs : ";
		for (set<int>::iterator beg = (it->second).begin (); beg != (it->second).end (); beg++)
		{
			ofs << *beg << " ";
		}
		ofs << "\n";
	}
	ofs.close ();
}

void stat_degree (string label)
{
	for (int i = 0; i < MAXN; ++i)
	{
		if (graph[i].size () != 0)
		{
			set<int> st;
			st.clear ();
			for (set<int>::iterator it = graph[i].begin (); it != graph[i].end (); ++it)
			{
				st.insert (*it);
			}
			cout << "Node " << i << " have a degree of: " << st.size () << endl;
			map<int, int>::iterator it = stats.find (st.size ());
			if (it == stats.end ())
			{
				stats.insert (make_pair (st.size (), 1));
			}
			else
			{
				stats[st.size ()]++;
			}
		}
	}
	ofstream ofs;
	ofs.open (label + "_stats.txt", std::ofstream::out);
	for (auto it = stats.begin (); it != stats.end (); ++it)
	{
		for (int j = 0; j < it->second; ++j)
		{
			ofs << it->first << "\n";
		}
//		ofs << it->first << " " << it->second << endl;
	}
	ofs.close ();
}

int main ()
{
	int n, a, b;
#ifndef ONLINE_JUDGE
	freopen ("./graphs/s1.txt", "r", stdin);
#endif
	string label = "s1";
	ios::sync_with_stdio (false);
	cin.tie (nullptr);
	cout.tie (nullptr);
	cin >> n;
	while (cin >> a >> b)
	{
		graph[a].insert (b);
//		graph[b].insert (a);
	}
	getCC (n, label);
//	stat_degree (label);
//	cout << "Scc Test\n";
//	Tarjan A;
//	A.getInfo ("./graphs/" + label + ".txt");
//	A.find_scc ();
//	A.outputInfo (label);
}