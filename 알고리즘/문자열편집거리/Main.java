import java.util.*;

public class Main {
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		System.out.print("두 문자열의 길이 입력: ");
		int n = scan.nextInt();
		int m = scan.nextInt();

		System.out.println("두 문자열 입력:");
		String x = scan.next();
		String y = scan.next();
		scan.close();

		StringEdit se = new StringEdit(n, m);
		se.Get_cost(n, m, x, y);
		se.Get_edit(n, m);
		se.Print(n, m);
		se.Check(n, m, x, y);
	}
}

class StringEdit {
	private int cost[][];
	private String edit[][];
	
	// 생성자
	StringEdit(int n, int m) {
		cost = new int[n + 1][m + 1];
		edit = new String[n + 1][m + 1];
	}
	
	// 최소값 반환 함수
	private int Get_min(int delete, int change, int insert) {
		int min = change;

		if (delete <= min)
			min = delete;
		if (insert <= min)
			min = insert;

		return min;
	}
	
	// cost표 생성 함수
	public void Get_cost(int n, int m, String x, String y) {
		int i, j;
		for (i = 0; i <= n; i++)
			cost[i][0] = i;
		for (j = 0; j <= m; j++)
			cost[0][j] = j;

		for (i = 1; i <= n; i++) {
			for (j = 1; j <= m; j++) {
				// 만약 두 문자가 같으면 교체 비용X
				if (x.charAt(i - 1) == y.charAt(j - 1))
					cost[i][j] = cost[i - 1][j - 1];
				
				else {
					int delete = cost[i - 1][j];
					int change = cost[i - 1][j - 1];
					int insert = cost[i][j - 1];

					/* 삽입: 1, 삭제: 1, 교체: 2 */
					int min = Get_min(delete + 1, change + 2, insert + 1);
					cost[i][j] = min;
				}
			}
		}
		System.out.println(x + " -> " + y + "의 최소 비용: " + cost[n][m]);
		System.out.println();
	}
	
	// edit표 생성 함수
	public void Get_edit(int n, int m) {
		int i, j;
		edit[0][0] = "-";
		for (i = 1; i <= n; i++)
			edit[i][0] = "D";
		for (j = 1; j <= m; j++)
			edit[0][j] = "I";

		for (i = 1; i <= n; i++) {
			for (j = 1; j <= m; j++) {
				int delete = cost[i - 1][j];
				int change = cost[i - 1][j - 1];
				int insert = cost[i][j - 1];

				int min = Get_min(delete, change, insert);
				
				// 같은 값이 있더라도, 아래 if문 통해 1개만 edit 표에 반영됨
				if (min == delete)
					edit[i][j] = "D";
				if (min == insert)
					edit[i][j] = "I";
				if (min == change)
					edit[i][j] = "C";
			}
		}
	}
	
	// 편집 순서 확인용 함수
	public void Check(int n, int m, String x, String y) {
		System.out.println("<" + x + " -> " + y + " 편집 순서 확인>");
		
		// backtrace 배열: 편집 과정 담음
		String backtrace[] = new String[10];
		int index = 0;
		
		int i = n;
		int j = m;

		while (true) {
			// 1) i, j가 모두 0일 때는 처음 x 값에 도달한 것이므로 break
			if (i == 0 && j == 0) break;
			
			// 2) i == 0인데, j가 0보다 크면 삽입만
			else if (i == 0 && j > 0) {
				//System.out.println(y.charAt(j-1) + "(y" + j + ") 삽입");
				backtrace[index++] = y.charAt(j-1) + "(y" + j + ") 삽입";
				j--;
			}
			
			// 3) j == 0인데 i가 0보다 크면 삭제만
			else if (i > 0 && j == 0) {
				//System.out.println(x.charAt(i-1) + "(x" + i + ") 삭제");
				backtrace[index++] = x.charAt(i-1) + "(x" + i + ") 삭제";
				i--;
			}
			
			// 4) i, j가 모두 0보다 클 때는 현재 위치에서
			else { // 왼쪽, 위쪽, 대각선 방향의 값 중
				int delete = cost[i - 1][j];
				int change = cost[i - 1][j - 1];
				int insert = cost[i][j - 1];
				// 가장 작은 값 찾는다.
				int min = Get_min(delete, change, insert);
				// ㄱ) 만약 최소값이 현재 값과 같다면 i, j 값 감소
				if (min == cost[i][j]) {
					i--;
					j--;
				}
				// ㄴ) 현재 값과 최소 값이 다를 경우
				else { // 최소 값이 대각선, 왼쪽, 위쪽인지 찾는다.
					if (min == change) {
						//System.out.println(x.charAt(i-1) + "(x" + i + ")를 " + y.charAt(j-1) + "(y" + j + ")로 교체");
						backtrace[index++] = x.charAt(i-1) + "(x" + i + ")를 " + y.charAt(j-1) + "(y" + j + ")로 교체";
						i--;
						j--;
					} else if (min == insert) {
						//System.out.println(y.charAt(j-1) + "(y" + j + ") 삽입");
						backtrace[index++] = y.charAt(j-1) + "(y" + j + ") 삽입";
						j--;
					} else {
						//System.out.println(x.charAt(i-1) + "(x" + i + ") 삭제");
						backtrace[index++] = x.charAt(i-1) + "(x" + i + ") 삭제";
						i--;
					}
				}
			}
		}
		
		// backtrace에 담긴 내용을 거꾸로 출력한다.
		for (i = index - 1; i >= 0; i--)
			System.out.println(backtrace[i]);
	}

	public void Print(int n, int m) {
		int i, j;

		System.out.println("<c(i, j)표 출력>");
		System.out.print("j");
		for (j = 0; j <= m; j++)
			System.out.print("   " + j);
		System.out.println();
		System.out.println("---------------------");

		for (i = 0; i <= n; i++) {
			System.out.print("i=" + i + "|");
			for (j = 0; j <= m; j++)
				System.out.print(cost[i][j] + "   ");
			System.out.println();
		}
		System.out.println();

		System.out.println("<edit(i, j)표 출력>");
		System.out.print("j");
		for (j = 0; j <= m; j++)
			System.out.print("\t" + j);
		System.out.println();
		System.out.println("--------------------------------------------");

		for (i = 0; i < n + 1; i++) {
			System.out.print("i=" + i + "|");
			for (j = 0; j < m + 1; j++)
				System.out.print("\t" + edit[i][j]);
			System.out.println();
		}
		System.out.println();
	}
}