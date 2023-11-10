#define _CRT_SECURE_NO_WARNINGS
#include"graph.h"

void CreateGraph(MTGraph* G)
{
	ifstream file("test.txt");
	file >> G->n;
	file >> G->e;
	//初始化
	for (int i = 0; i < G->n; i++)
	{
		for (int j = 0; j < G->n; j++)
			G->edge[i][j] = inf;
	}
	for (int i = 0; i < G->n; i++)
	{
		G->edge[i][i] = 0;	//对角线初始化为0
	}
	for (int i = 0; i < G->n; i++)
	{
		file >> G->vertex[i];
	}
	for (int i = 0; i < G->e; i++)
	{
		int a, b, w;
		file >> a >> b >> w;
		G->edge[a][b] = w;
	}

}
int SelectMin(MTGraph* G,int dist[], bool s[])//在V-s中找到w，使d[w]最小
{
	int temp = inf;
	int w = 0;
	for (int i = 0; i < G->n; i++)
	{
		if (!s[i] && dist[i] < temp)
		{
			temp = dist[i];
			w = i;
		}
	}

	return w;
}
void Dijkstra(MTGraph* G, int start, int dist[], int path[], bool s[])
{
	for (int i = 0; i < G->n; i++)
	{
		dist[i] = G->edge[start][i];
		path[i] = start;
		s[i] = false;
	}
	s[start] = true;
	for (int i = 0; i < G->n - 1; i++)
	{
		int w = SelectMin(G, dist, s);
		s[w] = true;
		for (int v = 0; v < G->n; v++)//加入顶点w后，更新dist[]和path[]
		{
			if (!s[v])
			{
				int sum = dist[w] + G->edge[w][v];;
				if (sum < dist[v])
				{
					dist[v] = sum;
					path[v] = w;
				}
			}
		}
		
	}
}
//打印路径
void printroad(MTGraph* G, int start, int dist[], int path[])
{
	for (int i = 0; i < G->n; i++)
	{
		cout << start << "->" << i << ":";
		if (dist[i] == inf)
		{
			cout << "无路径";
			cout << endl;
		}
		else if (dist[i] == start)
		{
			cout << "路径:";
			cout << start << "->" << start;
			cout << "\t距离:";
			cout << 0 << endl;
		}
		else
		{
			int j = 0;
			int r[NumVertices];
			int temp = i;
			while (temp != start)
			{
				r[j++] = temp;
				temp = path[temp];
			}
			r[j++] = start;
			cout << "路径:";
			while (j--)
			{
				cout << r[j];
				if (j != 0)
					cout << "->";
			}
			cout << "\t距离:" << dist[i] << endl;
		}
	}
}
void ManageDijkstra(int mode)
{
	MTGraph* G = new MTGraph;
	CreateGraph(G);
	int dist[NumVertices];	//从源点到该节点i的当前最短路径长
	int path[NumVertices];	//最短路径上最后一个节点
	bool s[NumVertices];	//记录是否在已生成的最短路经图
	int start;
	cout << "请输入源点：" << endl;
	cin >> start;
	if (mode == 1)
	{
		Dijkstra(G, start, dist, path, s);
		printroad(G, start, dist, path);
	}

}
void Floyd(MTGraph* G, int dist[][NumVertices], int path[][NumVertices])
{
	for (int i = 0; i < G->n; i++)
	{
		for (int j = 0; j < G->n; j++)
		{
			dist[i][j] = G->edge[i][j];
			path[i][j] = -1;
		}
	}
	for (int k = 0; k < G->n; k++)
	{
		for (int i = 0; i < G->n; i++)
		{
			for (int j = 0; j < G->n; j++)
			{
				if (dist[i][k] + dist[k][j] < dist[i][j])
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = k;
				}
			}
		}
	}
}
//递归打印路径
void printpath(int path[][NumVertices], int i, int j)
{
	int k = path[i][j];
	if (k != -1)
	{
		printpath(path, i, k);
		cout << k << "->";
		printpath(path, k, j);
	}
}
//输出最短距离矩阵、最短路径矩阵，
//任意两个顶点间的最短路径长度和最短路径
void printFloyd_2(MTGraph* G, int dist[][NumVertices], int path[][NumVertices])
{
	cout << "最短距离矩阵" << endl;
	for (int i = 0; i < G->n; i++)
	{
		for (int j = 0; j < G->n; j++)
		{
			cout << setw(6) << dist[i][j];
		}
		cout << endl;
	}
	cout << "最短路径" << endl;
	for (int i = 0; i < G->n; i++)
	{
		for (int j = 0; j < G->n; j++)
		{
			cout << setw(4) << path[i][j];
		}
		cout << endl;
	}
	cout << "所有点的最短路径:" << endl;
	for (int i = 0; i < G->n; i++)
	{
		for (int j = 0; j < G->n; j++)
		{
			if (i != j)
			{
				cout << i << "->" << j << ":" << endl;
				cout << "路径：";
				cout << i<<"->";
				printpath(path, i, j);
				cout << j << endl;
				cout << "距离:";
				cout << dist[i][j] << endl;
			}
		}
	}
}
//每个顶点到指定终点c的所有路径和长度
void printFloyd_3(MTGraph* G, int dist[][NumVertices], int path[][NumVertices])
{
	int c;
	cout << "请输入终点:";
	cin >> c;
	for (int i = 0; i < G->n; i++)
	{
		if (dist[i][c] == inf)
		{
			cout << i << "->" << c << ":";
			cout << "无路径" << endl;
		}
		cout << i << "->" << c << ":"<<endl;
		cout << "路径:";
		cout << i;
		cout << "->";
		printpath(path, i, c);
		cout << c << endl;
		cout << "距离:" << dist[i][c] << endl;
	}

}
//指定起点和终点，输出最短路径和长度
void printFloyd_4(MTGraph* G, int dist[][NumVertices], int path[][NumVertices])
{
	int a, b;
	cout << "请输入两个顶点:" << endl;
	cin >> a >> b;
	if (dist[a][b] == inf)
		cout << a << "->" << b << " 无路径";
	else
	{
		cout << a << "->" << b << ":";
		cout << "路径:";
		cout << a << "->";
		printpath(path, a, b);
		cout << b << endl;
		cout << "长度:" << dist[a][b] << endl;
	}
	if (dist[b][a] == inf)
		cout << b << "->" << a << " 无路径";
	else
	{
		cout << b << "->" << a << ":";
		cout << "路径:";
		cout << b << "->";
		printpath(path, b, a);
		cout << a << endl;
		cout << "长度:" << dist[b][a] << endl;
	}

}
void ManageFloyd(int mode)
{
	MTGraph* G = new MTGraph;
	CreateGraph(G);
	int dist[NumVertices][NumVertices];	//最短距离矩阵
	int path[NumVertices][NumVertices];	//最短路径矩阵
	Floyd(G, dist, path);
	if (mode == 2)
		printFloyd_2(G, dist, path);
	else if (mode == 3)
		printFloyd_3(G, dist, path);
	else
		printFloyd_4(G, dist, path);
}

void Warshall()
{
	MTGraph* G = new MTGraph;
	CreateGraph(G);
	int nn[NumVertices][NumVertices];
	//初始化可达矩阵
	for (int i = 0; i < G->n; i++)
	{
		for (int j = 0; j < G->n; j++)
		{
			if (G->edge[i][j] == inf)
				nn[i][j] = 0;
			else
				nn[i][j] = 1;
		}
	}
	//动态规划问题
	for (int k = 0; k < G->n; k++)
	{
		for (int i = 0; i < G->n; i++)
		{
			for (int j = 0; j < G->n; j++)
			{
				if (nn[i][k] && nn[k][j])
					nn[i][j] = 1;
			}
		}
	}
	//输出可达矩阵
	cout<< "可达矩阵为:" << endl;
	for (int i = 0; i < G->n; i++)
	{
		for (int j = 0; j < G->n; j++)
		{
			cout << nn[i][j] << " ";
		}
		cout << endl;
	}
}
void test()
{
	while (1)
	{
		cout << "1.单源最短路径的Dijkstra算法" << endl;
		cout << "2.全局最短路径的Floyd-Warshall算法" << endl;
		cout << "3.指定终点的最短路径" << endl;
		cout << "4.指定一对顶点互相的最短路径" << endl;
		cout << "5.Warshall算法计算有向图的可达矩阵" << endl;
		cout << "0.退出程序" << endl;
		int mode;
		cout << "请选择模式：" << endl;
		cin >> mode;
		switch (mode)
		{
		case 1:
			ManageDijkstra(1);
			break;
		case 2:
			ManageFloyd(2);
			break;
		case 3:
			ManageFloyd(3);
			break;
		case 4:
			ManageFloyd(4);
			break;
		case 5:
			Warshall();
			break;
		case 0:
			return;
		}
		
	}
}
int main()
{
	test();
	return 0;
}
