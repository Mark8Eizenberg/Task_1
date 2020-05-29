#include "PostmanAlgo.h"
#include <iostream>
#include <stack>
#include <algorithm>

Graph::Graph(int iTop, int iEdge, vector<vector<int>> vInc)
{
	this->iNumTop = iTop;
	this->iNumEdge = iEdge;
	this->incMatrix = vInc;
	this->adjMatrix = ToAdjFromInc(vInc);
}

Graph::Graph()
{
	using namespace std;
	int iTop,
		iEdge;
	cout << "Введите количество вершин" << endl;
	cin >> iTop;
	cout << "Введите количество ребер" << endl;
	cin >> iEdge;
	vector<vector<int>> vInc = vector<vector<int>>(iTop);
	cout << "Введите матрицу инцидентности построчно, начиная с первой вершины через пробел, в конце строки введите Enter" << endl;
	int i_tmp;
	for(int i = 0; i < iTop; i++)
		for (int j = 0; j < iEdge; j++)
		{
			cin >> i_tmp;
			vInc[i].push_back(i_tmp);
		}
	this->iNumTop = iTop;
	this->iNumEdge = iEdge;
	this->incMatrix = vInc;
	this->adjMatrix = ToAdjFromInc(vInc);
}

Graph::~Graph()
{
	this->incMatrix.clear();
	this->adjMatrix.clear();
}

void Graph::ShowData()
{
	using namespace std;
	cout << "Количество вершин : " << this->iNumTop << endl;
	cout << "Количество ребер : " << this->iNumEdge << endl;
	cout << "Матрица инцидентнсти : " << endl;
	for (auto i : this->incMatrix)
	{
		for (auto j : i)
			cout << j << '\t';
		cout << endl;
	}
	cout << "Матрица смежности : " << endl;
	for (auto i : this->adjMatrix)
	{
		for (auto j : i)
			cout << j << '\t';
		cout << endl;
	}
}

vector<vector<int>> Graph::ToAdjFromInc(vector<vector<int>> vIn)
{
	vector<vector<int>> vAdjMatrix = vector<vector<int>>(vIn.size(), vector<int>(vIn.size(), 0));
	int t = 0,
		f = 0;
	for (int i = 0; i < this->iNumEdge; i++)
	{
		for (int j = 0; j < this->iNumTop; j++)
		{
			if (vIn[j][i] == -1)
				f = j;
			else if (vIn[j][i] == 1)
				t = j;
		}
		vAdjMatrix[f][t] = 1;
	}
	vAdjMatrix[0][0] = 0;

	return vAdjMatrix;
}

bool Graph::IsEilerGraph()
{
	int incoming = 0;
	int outcoming = 0;
	for (int i = 0; i < this->iNumTop; i++)
	{
		for (int j = 0; j < this->iNumTop; j++)
		{
			incoming += this->adjMatrix[i][j];
			outcoming += this->adjMatrix[j][i];
		}
		if (incoming != outcoming || ((incoming == 0) && (outcoming == 0)))
			return false;
		incoming = outcoming = 0;
	}
	return true;
}

void Graph::ShowEiler( int iStart)
{
	using namespace std;
	vector<int> v_deg(this->iNumTop);
	for (int i = 0; i < this->iNumTop; i++)
		for (int j = 0; j < this->iNumTop; j++)
			v_deg[i] += this->adjMatrix[i][j];
	vector<vector<int>> v_adg = this->adjMatrix;
	int iFirst = iStart;
	while (!v_deg[iFirst])
		++iFirst;
	int v1 = -1,
		v2 = -1;
	for (int i = 0; i < this->iNumTop; i++)
		if (v_deg[i] & 1)
			if (v1 == -1) v1 = i;
			else if (v2 == -1) v2 = i;
	if (v1 != -1)
	{
		++v_adg[v1][v2];
		++v_adg[v2][v1];
	}
	stack<int> st;
	st.push(iFirst);
	vector<int> res;
	while (!st.empty())
	{
		int v = st.top();
		int i;
		for (i = 0; i < this->iNumTop; i++)
			if (v_adg[v][i]>0)
				break;
		if (i == this->iNumTop)
		{
			res.push_back(v);
			st.pop();
		}
		else
		{
			--v_adg[v][i];
			--v_adg[i][v];
			st.push(i);
		}
	}
	if (v1 != -1)
		for (size_t i = 0; i + 1 < res.size(); ++i)
			if (res[i] == v1 && res[i + 1] == v2 || res[i] == v2 && res[i + 1] == v1)
			{
				vector<int> res2;
				for (size_t j = i + 1; j < res.size(); ++j)
					res2.push_back(res[j]);
				for (size_t j = 1; j <= i; ++j)
					res2.push_back(res[j]);
				res = res2;
				break;
			}
	reverse(res.begin(), res.end());
	cout << "Ейлеровский цикл графа (путь почтальона) :" << endl;
	for (size_t i = 0; i < res.size(); ++i)
		cout << res[i] + 1 << " ";

}



