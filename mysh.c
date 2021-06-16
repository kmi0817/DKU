/* //////// 간단한 Shell 구현, mysh.c /////////////
	이름: 박경미
	날짜: 2020년 10월
/////////////////////////////////////////// */


#include <stdio.h>
#include <stdlib.h> // exit()
#include <unistd.h> // fork(), getcwd()
#include <fcntl.h>
#include <string.h> // strcmp(), strlen(), perror()
#include <sys/wait.h> // wait()
#include <sys/types.h>
#include <sys/stat.h> // stat 구조체

#define MAX_BUF 64

int  IsExit(char* buf) {
	if (strcmp(buf, "exit") == 0) {return 1;}
	else { return 0; }
}

int IsHelp(char* tokens[], const int cnt) {
	char* help = "help";
	int i;
	for (i = 0; i < cnt; i++){
		if (strcmp(tokens[i], help) == 0) {
			printf("-----------------------my shell------------------------\n");
			printf("  ** 해당  shell은 내부 명령어를 지원하지 않습니다. **\n");
			printf("\tBackground processing 지원\n");
			printf("\tRedirection processing 지원 **>, <  방향만 가능\n");
			printf("\thelp 지원\n");
			printf("\texit 지원\n");
			printf("-------------------------------------------------------\n");
			return 1;
		}
	}
	return 0;
}

int IsRedirection(char* tokens[], const int cnt) {
	int i, flag = 0; // flag == 0이면 redirection 없음

	for (i = 0; i < cnt; i++) {
		if (strcmp(tokens[i], ">") == 0) { flag = 1; break; } // output redirection
		else if (strcmp(tokens[i], "<") == 0) { flag = 2; break; } // input redirection
	}

	// tokens에 ">", "<" 없을 시 0 반환
	if (flag == 0) { return 0; }
	// >, < 다음 파일 입력되지 않을 시 오류 메시지 출력 후 prompt로 돌아감
	else if (tokens[i+1] == NULL) {
		printf("Wrong usage of redirection. should be e.g. 'cat a.txt > b.txt'\n"); return 1;
	}

	// flag == 1 or flag == 2일 시redirection 수행 후 1 반환
	else {
		struct stat st;
		int fd, fd1, read_size, write_size;
		char buf[MAX_BUF];
		pid_t fork_return;
		int status; // 자식 프로세스 상태 담을 변수, wait() 인자

		fork_return = fork();
		if (fork_return < 0) {perror("fork error"); return 1;} // return 실패 시 다시 prompt로 돌아감

		if (fork_return == 0) {
			if (flag == 1) { // output redirection
				// 두 파일 open 실패 시 자식 프로세스 종료 처리
				fd = open(tokens[i-1], O_RDONLY);
				if (fd < 0) {perror("can't open this file1"); exit(1);}

				// stat 함수 호출 실패 시 자식 프로세스 종료 처리
				if (stat(tokens[i-1], &st) < 0) {perror("can't read this file"); exit(1);}

				fd1 = open(tokens[i+1], O_RDWR | O_CREAT, st.st_mode);
				if (fd1 < 0) {perror("can't open this file2"); exit(1);}

				// redirection 지정
				dup2(fd1, STDOUT_FILENO);

				while(1) {
					read_size = read(fd, buf, MAX_BUF);

					if (read_size < 0) {perror("can't read this file"); exit(1);}
					if (read_size == 0) break;

					write_size = write(STDOUT_FILENO, buf, read_size);
				}
				close(fd); close(fd1);
				exit(0); // 입출력 재지정 끝나면 자식 프로세스 종료 처리
			}

			else if (flag == 2) { // input redirection
				fd1 = open(tokens[i+1], O_RDONLY);
				if (fd1 < 0) {perror("can't open this file2"); exit(1);}

				if (stat(tokens[i+1], &st) < 0) {perror("stat error"); exit(1);}

				fd = open(tokens[i-1], O_RDWR | O_CREAT, st.st_mode);
				if (fd < 0) {perror("can't open this file1"); exit(1);}

				dup2(fd, STDOUT_FILENO);

				while(1) {
					read_size = read(fd1, buf, MAX_BUF);

					if (read_size < 0) {perror("can't read this file"); exit(1);}
					if (read_size == 0) break;

					write_size = write(STDOUT_FILENO, buf, read_size);
				}
				close(fd); close(fd1);
				exit(0);
			}
		}
		
		else {wait(&status); return 1;} // 부모는 자식 끝날 때까지 기다림

	}
}

int tokenize(char* buf, char* tokens[]) {
	char* token;
	int token_count = 0;

	token = strtok(buf, " "); // 띄어쓰기 기준으로 PARSING
	tokens[token_count] = token; // tokens 첫 번째 요소 삽입
	while (token != NULL) {
		token = strtok(NULL, " ");
		tokens[++token_count] = token;
	}
	tokens[token_count] = NULL; // tokens 유효 길이 지정
	// execvp로 전달 시 NULL이 마지막임을 알려주니까

	return token_count;
}

int IsBackground(char* buf) {
	int i;
	for (i = 0; i < strlen(buf); i++) {
		if (buf[i] == '&') {
			buf[i] = ' '; // & 있는 부분을 공백으로 바꿈
			return 1; // background 실행O
		}
	}
	return 0; // for문 내 if문에 걸리지 않으면, background 실행X
}

int run(char* line) {
	char* tokens[100];
	int token_count, background;
	int status; // wait()에 넣을 인자, 자식 프로세스 상태 담음
	pid_t fork_return;

	// exit, tokenize, background, redirection, help start
	line[strlen(line)-1] = '\0'; // 맨 마지막의 개행 문자 제거

	if(IsExit(line)) { return 0; }; // 입력 line이 exit라면 0 반환 -> prompt while문 끝남

	background = IsBackground(line); // background면 1, 아니면 0

	token_count = tokenize(line, tokens);

	if (IsRedirection(tokens, token_count)) { return 1; } // redirection이었다면 다시 prompt로 이동	

	if (IsHelp(tokens, token_count)) {return 1;} // help 있으면 다시 prompt로 이동
	// end

	// External Command start
	fork_return = fork();
	if (fork_return < 0) { perror("fork error"); return 1;}
	
	else if (fork_return  == 0) {
		if (execvp(tokens[0], tokens) < 0) {
			// execvp 실패 == 해당 command가 /usr/bin/에없으면
			perror("execvp error"); // 출력하고
			exit(1); // 해당 자식 프로세스는 종료
		}
	}

	else if (background == 0) { wait(&status); }
	// External Command end

	return 1;
}

int main() {
	char current_dir[MAX_BUF]; // 디렉토리 이름 담을 변수
	char* buf = getcwd(current_dir, MAX_BUF); // getcwd()로 현재 작업 디렉토리 이름 받음
	char line[1024];

	while (1) {
		printf("%s $ ", current_dir);
		fgets(line, sizeof(line)-1, stdin);
		if (strcmp(line, "\n") == 0) continue; // 입력된 게 없으면 다시 while문 반복
		if (run(line) == 0) break;
	}
}
