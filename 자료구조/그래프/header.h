#pragma once
#ifndef Graph_h
#define Graph_h
class Graph {
private:
	int** length; // 이차원 배열
	int* dist; // 일차원 배열
	bool* s; // 일차원 배열
	int n; // 정점의 수
	int* path;
	int start; // 시작 정점을 담을 포인터 변수

public:
	Graph(const int);
	void InsertEdge(const int, const int, const int);
	int choose(const int);
	void ShortestPath(const int);

	void PrintLength();
	void PrintDist();
	void PrintPath();
};
#endif