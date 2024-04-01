#include "header.h"
#include <iostream>
#include <stack> // 스택 사용
using namespace std;

#define INF 9999

Graph::Graph(const int vertices = 0) : n(vertices) {

	// length 동적 할당
	length = new int* [n];
	for (int i = 0; i < n; i++)
		length[i] = new int[n];
	// length 초기화 1. 대각선은 0, 2. 그외 무한대
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) // 대각선은 0으로 채운다
				length[i][j] = 0;
			else // 대각선이 아닌 부분은 일단 무한대로 채운다
				length[i][j] = INF;
		}
	}

	// 일차원 배열 동적 할당
	dist = new int[n];
	s = new bool[n];
	path = new int[n];

	// 일단 시작 정점을 -1로 초기화
	start = -1;
}

void Graph::InsertEdge(const int start, const int end, const int e) {
	length[start][end] = e;
}

int Graph::choose(const int n) {
	int min = INF; //일단 최소 값을 무한대로 설정한다
	int u = -1;

	for (int w = 0; w < n; w++) {
		// 집합 s에 포함되지 않는 정점 중 최소 값
		if (!s[w] && dist[w] < min) {
			min = dist[w]; // 기존 min보다 더 작은 dist[w] 값으로 min 갱신
			u = w; // 간선도 w로 갱신
		}
	}

	return u;
}

void Graph::ShortestPath(const int v) {
	start = v; // 시작 정점 초기화

	// 일차원 배열 초기화
	for (int i = 0; i < n; i++) {
		s[i] = false;
		dist[i] = length[v][i];
		path[i] = v; // path 초기 값은 모두 출발 지점 v
	}

	s[v] = true; // 시작 정점은 s에 포함됨
	dist[v] = 0; // 출발 정점의 dist 값은 0 (없어도 된다)

	for (int i = 0; i < n - 2; i++) { // 정점 v로부터 n-1개 경로 결정
		int u = choose(n); // s에 포함 안 된 정점 중 가장 dist 값 고르는 함수
		s[u] = true; // s에 포함함

		for (int w = 0; w < n; w++) {
			if (!s[w]) { // s 정점에 포함 안 된 것이라면
				int sum = dist[u] + length[u][w];
				int original = dist[w];
				if (sum < original) { // 기존 것보다 새 경로가 더 짧다면
					dist[w] = sum; // dist 값 갱신
					path[w] = u; // 선택 정점 u 때문에 값이 변경되었다.
				}
			}
		}
	}
}

void Graph::PrintLength() {
	cout << "<가중치 갖는 인접행렬>" << endl;
	for (int u = 0; u < n; u++) { // 한 행의
		for (int v = 0; v < n; v++) { // 열들을 출력
			if (length[u][v] == INF) // 가중치가 무한대면
				cout << "∞"; // 기호로 출력
			else
				cout << length[u][v];

			cout << "     ";
		}
		cout << endl;
	}
}

void Graph::PrintDist() {
	cout << "<최종 결과인 배열 dist의 값>" << endl;
	for (int i = 0; i < n; i++) {
		if (dist[i] == INF)
			cout << "∞";
		else
			cout << dist[i];

		cout << "     ";
	}
	cout << endl;
}

void Graph::PrintPath() {
	cout << "<각 정점까지의 최단 경로>" << endl;

	stack<int> st; // int형 스택 선언

	for (int i = 0; i < n; i++) {
		if (dist[i] == INF) // dist 값이 무한대면 최단 경로가 없다
			cout << "정점" << i << ": 최단 경로 없음" << endl;

		else if (i != start) { // 정점 i가 시작 정점이 아닐 시
			int w = i;
			// 스택에 집어 넣는다
			do {
				st.push(w);
				w = path[w];
			} while (w != start); // w 값이 시작 정점의 것과 같다면 종료

			st.push(w); // 마지막 w 값까지 삽입

			// 스택에서 꺼내 출력
			cout << "정점" << i << ": ";
			while (!st.empty()) { // 빈 스택이 아니라면
				cout << st.top() << "    "; // 스택의 top 출력
				st.pop(); // 스택의 top 삭제
			}
			cout << endl;
		}
	}
}
