#pragma once
#include<iostream>
#include<iomanip>
#include<fstream>
#include<time.h>
using namespace std;

#define inf 10000//���ֵ
//�ڽӾ����ʾ����ͼ
#define VertexData int
#define EdgeData int
#define NumVertices 20
typedef struct MTGraph
{
	VertexData vertex[NumVertices];
	EdgeData edge[NumVertices][NumVertices];
	int n;		//������
	int e;		//����
}MTGraph;