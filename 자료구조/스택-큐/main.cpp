#include <iostream>
#include "stack.h"
#include "queue.h"
#include "ChainNode.h"
#include <string> // string을 다루므로 포함
#include <sstream> //stringsteam 사용하고자 포함
using namespace std;

int main() {
	string input;
	int num[2] = { 0, 0 }; // 기본으로 들어 있는 값은 0. 입력된 메뉴 번호를 담는 배열
	LinkedStack ms;
	LinkedQueue mq;

	cout << "\t----메뉴----\t" << endl;
	cout << "1. 스택에 삽입\t\t2. 큐에 삽입" << endl;
	cout << "3. 스택에 삭제\t\t4. 큐에서 삭제" << endl;
	cout << "5. 스택 내용 보기\t6. 큐 내용 보기" << endl;
	cout << "* 0 입력 시 종료" << endl; //아래의 무한반복을 끝내고 싶으면 사용하고자 삽입
	cout << "----------------------------------------" << endl;
	while (1) {
		cout << "▷ ";
		getline(cin, input); // 공백문자 포함해 입력 받음

	/* case 1) 1 30 입력 시 split으로 string 1과 30으로 바뀌고,
	while문에서 각각 int로 변환되어 num 배열에 순서대로 들어간다. ex) num: {1, 30} */
	/* case 2) 3만 입력 시 split으로 string3으로 바뀌고,
	while문에서 입력된 3만 int로 변환되어 num 배열 첫 번째 요소로 들어간다. ex) num:{3, 0} */
		stringstream split(input); // 공백문자를 기준으로 split할 input
		string temp; // split된 걸 담을 변수
		int i = 0; // 메뉴 입력 번호 담는 배열의 인덱스
		while (split >> temp) { // split돼 만들어진 개수만큼 반복
			int t; // split된 string을 int로 바꾸면 담을 변수
			stringstream s_to_int(temp); // split된 건 temp에 저장돼 있다
			s_to_int >> t; // temp에 있는 string을 int형으로 변경해 t에 담는다
			num[i++] = t; // 입력 받은 메뉴 번호(t)를 배열에 저장한다
		} // 작은 while문 끝

		switch (num[0]) {
		case 0: goto here; // while문 끝내는 0을 입력하면 같은 레이블이 붙은 문장으로 이동한다
		case 1: ms.Push(num[1]); break;
		case 2: mq.Push(num[1]); break;
		case 3: ms.Pop(num[1]); break;
		case 4: mq.Pop(num[1]); break;
		case 5: ms.Print(); break;
		case 6: mq.Print(); break;
		} // switch 끝
	} // 큰 while문 끝
here: // while문 내 switch, case 0일 시 여기로 온다.
	cout << ">> 프로그램 종료..." << endl;
}
