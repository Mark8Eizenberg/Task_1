#pragma once
#include <vector>

using std::vector;

class Graph
{
	vector<vector<int>> incMatrix;
	vector<vector<int>> adjMatrix;
	int iNumTop;
	int iNumEdge;
public:
	Graph(int iTop, int iEdge, vector<vector<int>> vInc);
	Graph();
	~Graph();
	void ShowData();
	vector<vector<int>> ToAdjFromInc(vector<vector<int>> vIn);
	bool IsEilerGraph();
	void ShowEiler(int iStart);
};
