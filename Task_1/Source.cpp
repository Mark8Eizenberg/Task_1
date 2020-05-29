#include <iostream>
#include <vector>
#include "PostmanAlgo.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "russian");
	vector<vector<int>> graph;
	vector<bool> used;
	int top = 6,
		edge = 7;
	graph.push_back(vector<int>{-1, 0, 0, 0, 0, 0, 1});
	graph.push_back(vector<int>{1, -1, 0, 0, 0, 0, 0});
	graph.push_back(vector<int>{0, 1, -1, 0, 0, 0, 0});
	graph.push_back(vector<int>{0, 0, 1, 1, -1, 0, -1});
	graph.push_back(vector<int>{0, 0, 0, -1, 0, 1, 0});
	graph.push_back(vector<int>{0, 0, 0, 0, 1, -1, 0});
	
	int iChoice;
	cout << "\tЗадание 1\n1 - Вывести пример на экран \n2 - Ввести свой граф \n3 - Выход" << endl;
	cin >> iChoice;
	if(iChoice == 1)
	{
		Graph gr = Graph(top, edge, graph);
		gr.ShowData();
		cout << "Граф задачи имеет решение: " << gr.IsEilerGraph() << endl;
		gr.ShowEiler(0);
		cout << "\nВведите 3 для выхода" << endl;
		cin >> iChoice;
	}
	else if (iChoice == 2)
	{
		Graph gr = Graph();
		gr.ShowData();
		cout << "Граф задачи имеет решение: " << gr.IsEilerGraph() << endl;
		if (gr.IsEilerGraph())
			gr.ShowEiler(0);
		cout << "\nВведите 3 для выхода" << endl;
		cin >> iChoice;
	}
	else if (iChoice == 3)
	{
		cout << "Exiting program" << endl;
		exit(1);
	}
}