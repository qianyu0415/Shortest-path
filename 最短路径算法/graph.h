#pragma once
#include<iostream>
#include<iomanip>
#include<fstream>
#include<time.h>
using namespace std;

#define inf 10000//最大值
//邻接矩阵表示有向图
#define VertexData int
#define EdgeData int
#define NumVertices 20
typedef struct MTGraph
{
	VertexData vertex[NumVertices];
	EdgeData edge[NumVertices][NumVertices];
	int n;		//顶点数
	int e;		//边数
}MTGraph;