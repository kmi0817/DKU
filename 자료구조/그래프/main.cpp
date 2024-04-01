#include "header.h"
#include <iostream>
using namespace std;

int main() {
	int n, m, u, v, weight, start;

	cout << "정점 수와 간선 수 입력 >";
	cin >> n >> m;

	Graph g(n); // 그래프 객체 생성

	for (int i = 0; i < m; i++) {
		cout << i + 1 << "번째 간선과 가중치 입력 > ";
		cin >> u >> v >> weight;
		g.InsertEdge(u, v, weight); // start행 end열에 weight 값 삽입
	}

	cout << endl << "시작 정점 입력> ";
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
