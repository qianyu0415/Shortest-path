#define _CRT_SECURE_NO_WARNINGS
#include"graph.h"

void CreateGraph(MTGraph* G)
{
	ifstream file("test.txt");
	file >> G->n;
	file >> G->e;
	// ��ʼ��
	for (int i = 0; i < G->n; i++)
	{
		for (int j = 0; j < G->n; j++)
			G->edge[i][j] = inf;
	}
	for (int i = 0; i < G->n; i++)
	{
		G->edge[i][i] = 0;	//�Խ��߳�ʼ��Ϊ0
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
int SelectMin(MTGraph* G,int dist[], bool s[])//��V-s���ҵ�w��ʹd[w]��С
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
		for (int v = 0; v < G->n; v++)//���붥��w�󣬸���dist[]��path[]
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
//��ӡ·��
void printroad(MTGraph* G, int start, int dist[], int path[])
{
	for (int i = 0; i < G->n; i++)
	{
		cout << start << "->" << i << ":";
		if (dist[i] == inf)
		{
			cout << "��·��";
			cout << endl;
		}
		else if (dist[i] == start)
		{
			cout << "·��:";
			cout << start << "->" << start;
			cout << "\t����:";
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
			cout << "·��:";
			while (j--)
			{
				cout << r[j];
				if (j != 0)
					cout << "->";
			}
			cout << "\t����:" << dist[i] << endl;
		}
	}
}
void ManageDijkstra(int mode)
{
	MTGraph* G = new MTGraph;
	CreateGraph(G);
	int dist[NumVertices];	//��Դ�㵽�ýڵ�i�ĵ�ǰ���·����
	int path[NumVertices];	//���·�������һ���ڵ�
	bool s[NumVertices];	//��¼�Ƿ��������ɵ����·��ͼ
	int start;
	cout << "������Դ�㣺" << endl;
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
//�ݹ��ӡ·��
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
//�����̾���������·������
//�����������������·�����Ⱥ����·��
void printFloyd_2(MTGraph* G, int dist[][NumVertices], int path[][NumVertices])
{
	cout << "��̾������" << endl;
	for (int i = 0; i < G->n; i++)
	{
		for (int j = 0; j < G->n; j++)
		{
			cout << setw(6) << dist[i][j];
		}
		cout << endl;
	}
	cout << "���·��" << endl;
	for (int i = 0; i < G->n; i++)
	{
		for (int j = 0; j < G->n; j++)
		{
			cout << setw(4) << path[i][j];
		}
		cout << endl;
	}
	cout << "���е�����·��:" << endl;
	for (int i = 0; i < G->n; i++)
	{
		for (int j = 0; j < G->n; j++)
		{
			if (i != j)
			{
				cout << i << "->" << j << ":" << endl;
				cout << "·����";
				cout << i<<"->";
				printpath(path, i, j);
				cout << j << endl;
				cout << "����:";
				cout << dist[i][j] << endl;
			}
		}
	}
}
//ÿ�����㵽ָ���յ�c������·���ͳ���
void printFloyd_3(MTGraph* G, int dist[][NumVertices], int path[][NumVertices])
{
	int c;
	cout << "�������յ�:";
	cin >> c;
	for (int i = 0; i < G->n; i++)
	{
		if (dist[i][c] == inf)
		{
			cout << i << "->" << c << ":";
			cout << "��·��" << endl;
		}
		cout << i << "->" << c << ":"<<endl;
		cout << "·��:";
		cout << i;
		cout << "->";
		printpath(path, i, c);
		cout << c << endl;
		cout << "����:" << dist[i][c] << endl;
	}

}
//ָ�������յ㣬������·���ͳ���
void printFloyd_4(MTGraph* G, int dist[][NumVertices], int path[][NumVertices])
{
	int a, b;
	cout << "��������������:" << endl;
	cin >> a >> b;
	if (dist[a][b] == inf)
		cout << a << "->" << b << " ��·��";
	else
	{
		cout << a << "->" << b << ":";
		cout << "·��:";
		cout << a << "->";
		printpath(path, a, b);
		cout << b << endl;
		cout << "����:" << dist[a][b] << endl;
	}
	if (dist[b][a] == inf)
		cout << b << "->" << a << " ��·��";
	else
	{
		cout << b << "->" << a << ":";
		cout << "·��:";
		cout << b << "->";
		printpath(path, b, a);
		cout << a << endl;
		cout << "����:" << dist[b][a] << endl;
	}

}
void ManageFloyd(int mode)
{
	MTGraph* G = new MTGraph;
	CreateGraph(G);
	int dist[NumVertices][NumVertices];	//��̾������
	int path[NumVertices][NumVertices];	//���·������
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
	//��ʼ���ɴ����
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
	//��̬�滮����
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
	//����ɴ����
	cout<< "�ɴ����Ϊ:" << endl;
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
		cout << "1.��Դ���·����Dijkstra�㷨" << endl;
		cout << "2.ȫ�����·����Floyd-Warshall�㷨" << endl;
		cout << "3.ָ���յ�����·��" << endl;
		cout << "4.ָ��һ�Զ��㻥������·��" << endl;
		cout << "5.Warshall�㷨��������ͼ�Ŀɴ����" << endl;
		cout << "0.�˳�����" << endl;
		int mode;
		cout << "��ѡ��ģʽ��" << endl;
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
