/*mycp.c : copy from a file and past it into another file, by 32191556 from Dankook Univ. SW, HW3 for SP */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_BUF 16

int main(int argc, char *argv[])
{
  struct stat mode;
  int fd1_mode; // 파일 접근 권한 담을 변수
  int state; // stat 에러 체크용변수

  int fd1, fd2, readSize, writeSize;
  char buf[MAX_BUF];

  // 인수 부족 시 에러처리
  if (argc != 3) { printf("USAGE: %s file_name1 file_name2\n", argv[0]); exit(-1); }

  //fd1 파일 open
  fd1 = open(argv[1], O_RDONLY);
  if (fd1 < 0 ) { printf("Can't open %s with errno %d\n", argv[1], errno); exit(-1); }

  //stat 이용해 첫 번째 파일 접근 권한 복사
  state = stat(argv[1], &mode);
  if (state < 0) { printf("Can't use stat with errno %d\n", errno); exit(-1); }
  fd1_mode = mode.st_mode;

  //fd2 파일 open
  fd2 = open(argv[2], O_WRONLY | O_CREAT | O_EXCL,fd1_mode);
  if (fd2 < 0) { printf("Cna't open %s with errno %d\n", argv[2], errno); exit(-1); }

  while (1) {
	readSize = read(fd1, buf, MAX_BUF);
	if (readSize < 0) { printf("Can't read %s with errno\n", argv[1], errno); exit(-1); }

	if (readSize == 0) break;

	writeSize = write(fd2, buf, readSize);
	}

  close(fd1);
  close(fd2);

}
