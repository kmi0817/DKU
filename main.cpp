#include "header.h"
#include <iostream>
using namespace std;

int main() {
	int n, m, u, v, weight, start;

	cout << "���� ���� ���� �� �Է� >";
	cin >> n >> m;

	Graph g(n); // �׷��� ��ü ����

	for (int i = 0; i < m; i++) {
		cout << i + 1 << "��° ������ ����ġ �Է� > ";
		cin >> u >> v >> weight;
		g.InsertEdge(u, v, weight); // start�� end���� weight �� ����
	}

	cout << endl << "���� ���� �Է�> ";
	cin >> start;
	cout << endl;

	g.ShortestPath(start);
	cout << endl;
	g.PrintLength();
	cout << endl;
	g.PrintDist();
	cout << endl;
	g.PrintPath();
}
