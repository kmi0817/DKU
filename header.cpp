#include "header.h"
#include <iostream>
#include <stack> // ���� ���
using namespace std;

#define INF 9999

Graph::Graph(const int vertices = 0) : n(vertices) {

	// length ���� �Ҵ�
	length = new int* [n];
	for (int i = 0; i < n; i++)
		length[i] = new int[n];
	// length �ʱ�ȭ 1. �밢���� 0, 2. �׿� ���Ѵ�
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) // �밢���� 0���� ä���
				length[i][j] = 0;
			else // �밢���� �ƴ� �κ��� �ϴ� ���Ѵ�� ä���
				length[i][j] = INF;
		}
	}

	// ������ �迭 ���� �Ҵ�
	dist = new int[n];
	s = new bool[n];
	path = new int[n];

	// �ϴ� ���� ������ -1�� �ʱ�ȭ
	start = -1;
}

void Graph::InsertEdge(const int start, const int end, const int e) {
	length[start][end] = e;
}

int Graph::choose(const int n) {
	int min = INF; //�ϴ� �ּ� ���� ���Ѵ�� �����Ѵ�
	int u = -1;

	for (int w = 0; w < n; w++) {
		// ���� s�� ���Ե��� �ʴ� ���� �� �ּ� ��
		if (!s[w] && dist[w] < min) {
			min = dist[w]; // ���� min���� �� ���� dist[w] ������ min ����
			u = w; // ������ w�� ����
		}
	}

	return u;
}

void Graph::ShortestPath(const int v) {
	start = v; // ���� ���� �ʱ�ȭ

	// ������ �迭 �ʱ�ȭ
	for (int i = 0; i < n; i++) {
		s[i] = false;
		dist[i] = length[v][i];
		path[i] = v; // path �ʱ� ���� ��� ��� ���� v
	}

	s[v] = true; // ���� ������ s�� ���Ե�
	dist[v] = 0; // ��� ������ dist ���� 0 (��� �ȴ�)

	for (int i = 0; i < n - 2; i++) { // ���� v�κ��� n-1�� ��� ����
		int u = choose(n); // s�� ���� �� �� ���� �� ���� dist �� ���� �Լ�
		s[u] = true; // s�� ������

		for (int w = 0; w < n; w++) {
			if (!s[w]) { // s ������ ���� �� �� ���̶��
				int sum = dist[u] + length[u][w];
				int original = dist[w];
				if (sum < original) { // ���� �ͺ��� �� ��ΰ� �� ª�ٸ�
					dist[w] = sum; // dist �� ����
					path[w] = u; // ���� ���� u ������ ���� ����Ǿ���.
				}
			}
		}
	}
}

void Graph::PrintLength() {
	cout << "<����ġ ���� �������>" << endl;
	for (int u = 0; u < n; u++) { // �� ����
		for (int v = 0; v < n; v++) { // ������ ���
			if (length[u][v] == INF) // ����ġ�� ���Ѵ��
				cout << "��"; // ��ȣ�� ���
			else
				cout << length[u][v];

			cout << "     ";
		}
		cout << endl;
	}
}

void Graph::PrintDist() {
	cout << "<���� ����� �迭 dist�� ��>" << endl;
	for (int i = 0; i < n; i++) {
		if (dist[i] == INF)
			cout << "��";
		else
			cout << dist[i];

		cout << "     ";
	}
	cout << endl;
}

void Graph::PrintPath() {
	cout << "<�� ���������� �ִ� ���>" << endl;

	stack<int> st; // int�� ���� ����

	for (int i = 0; i < n; i++) {
		if (dist[i] == INF) // dist ���� ���Ѵ�� �ִ� ��ΰ� ����
			cout << "����" << i << ": �ִ� ��� ����" << endl;

		else if (i != start) { // ���� i�� ���� ������ �ƴ� ��
			int w = i;
			// ���ÿ� ���� �ִ´�
			do {
				st.push(w);
				w = path[w];
			} while (w != start); // w ���� ���� ������ �Ͱ� ���ٸ� ����

			st.push(w); // ������ w ������ ����

			// ���ÿ��� ���� ���
			cout << "����" << i << ": ";
			while (!st.empty()) { // �� ������ �ƴ϶��
				cout << st.top() << "    "; // ������ top ���
				st.pop(); // ������ top ����
			}
			cout << endl;
		}
	}
}
