//
// Created by 李博 on 2019/2/7.
//

#ifndef NETWORK_ALIGNMENT_CONNECTED_COMPONENT_H
#define NETWORK_ALIGNMENT_CONNECTED_COMPONENT_H
#include "header.h"

using namespace std;
const int maxn = 10005;

class Tarjan
{
	private:
	int n, m;
	vector<int> G[maxn];
	int pre[maxn];
	int sccno[maxn];
	vector<int> scc[maxn];
	int dfs_clock;
	int scc_cnt;
	stack<int> backPoint;
	void init ()
	{
		for (int i = 0; i < maxn; ++i)
		{
			scc[i].clear ();
			G[i].clear ();
		}
		mem(pre);
		mem(sccno);
		dfs_clock = 0;
		scc_cnt = 0;
		while (!backPoint.empty ())
		{
			backPoint.pop ();
		}
	}
	int dfs (int u)
	{
		int lowlinku = pre[u] = ++dfs_clock;
		backPoint.push (u);
		for (int i = 0; i < G[u].size (); ++i)
		{
			int v = G[u][i];
			if (!pre[v])
			{
				int lowlinkv = dfs (v);
				lowlinku = min (lowlinku, lowlinkv);
			}
				//存在可以回退的点
			else if (!sccno[v])
			{
				lowlinku = min (lowlinku, pre[v]);
			}
		}
		if (lowlinku == pre[u])
		{
			scc_cnt++;
			scc[scc_cnt].clear ();
			while (1)
			{
				int x = backPoint.top ();
				backPoint.pop ();
				sccno[x] = scc_cnt;
				scc[scc_cnt].push_back (x);
				if (x == u)
				{
					break;
				}
			}
		}
		return lowlinku;
	}
	public:
	Tarjan ()
	{
		init ();
	}
	~Tarjan ()
	{
		//
	}
	void find_scc ()
	{
		dfs_clock = scc_cnt = 0;
		mem(sccno);
		mem(pre);
		for (int i = 0; i < n; ++i)
		{
			if (!pre[i])
			{
				dfs (i);
			}
		}
	}
	void getInfo (const string &filepath)
	{
		fstream infile;
		infile.open (filepath, ios::in);
		infile >> n >> m;
		int u, v;
		while (infile >> u >> v)
		{
			// if this edge don't appear before.
			if (find (G[u].begin (), G[u].end (), v) == G[u].end ())
			{
				G[u].push_back (v);
			}
		}
	}
	void outputInfo (string label)
	{
		ofstream ofs;
		ofs.open ("./scc_info_stats/" + label + "_out.txt", std::ofstream::out);
		ofs << "In this graph, we can find: " << scc_cnt << " strong connected component.\n";
		for (int i = 1; i <= scc_cnt; ++i)
		{
			ofs << "In the " << i << " th scc, there are vertexs : ";
			for (int j = 0; j < scc[i].size (); ++j)
			{
				ofs << scc[i][j] << " ";
			}
			ofs << "\n";
		}
		ofs.close ();
	}
};

#endif //NETWORK_ALIGNMENT_CONNECTED_COMPONENT_H
