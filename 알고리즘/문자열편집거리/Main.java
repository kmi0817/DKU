import java.util.*;

public class Main {
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		System.out.print("�� ���ڿ��� ���� �Է�: ");
		int n = scan.nextInt();
		int m = scan.nextInt();

		System.out.println("�� ���ڿ� �Է�:");
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
	
	// ������
	StringEdit(int n, int m) {
		cost = new int[n + 1][m + 1];
		edit = new String[n + 1][m + 1];
	}
	
	// �ּҰ� ��ȯ �Լ�
	private int Get_min(int delete, int change, int insert) {
		int min = change;

		if (delete <= min)
			min = delete;
		if (insert <= min)
			min = insert;

		return min;
	}
	
	// costǥ ���� �Լ�
	public void Get_cost(int n, int m, String x, String y) {
		int i, j;
		for (i = 0; i <= n; i++)
			cost[i][0] = i;
		for (j = 0; j <= m; j++)
			cost[0][j] = j;

		for (i = 1; i <= n; i++) {
			for (j = 1; j <= m; j++) {
				// ���� �� ���ڰ� ������ ��ü ���X
				if (x.charAt(i - 1) == y.charAt(j - 1))
					cost[i][j] = cost[i - 1][j - 1];
				
				else {
					int delete = cost[i - 1][j];
					int change = cost[i - 1][j - 1];
					int insert = cost[i][j - 1];

					/* ����: 1, ����: 1, ��ü: 2 */
					int min = Get_min(delete + 1, change + 2, insert + 1);
					cost[i][j] = min;
				}
			}
		}
		System.out.println(x + " -> " + y + "�� �ּ� ���: " + cost[n][m]);
		System.out.println();
	}
	
	// editǥ ���� �Լ�
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
				
				// ���� ���� �ִ���, �Ʒ� if�� ���� 1���� edit ǥ�� �ݿ���
				if (min == delete)
					edit[i][j] = "D";
				if (min == insert)
					edit[i][j] = "I";
				if (min == change)
					edit[i][j] = "C";
			}
		}
	}
	
	// ���� ���� Ȯ�ο� �Լ�
	public void Check(int n, int m, String x, String y) {
		System.out.println("<" + x + " -> " + y + " ���� ���� Ȯ��>");
		
		// backtrace �迭: ���� ���� ����
		String backtrace[] = new String[10];
		int index = 0;
		
		int i = n;
		int j = m;

		while (true) {
			// 1) i, j�� ��� 0�� ���� ó�� x ���� ������ ���̹Ƿ� break
			if (i == 0 && j == 0) break;
			
			// 2) i == 0�ε�, j�� 0���� ũ�� ���Ը�
			else if (i == 0 && j > 0) {
				//System.out.println(y.charAt(j-1) + "(y" + j + ") ����");
				backtrace[index++] = y.charAt(j-1) + "(y" + j + ") ����";
				j--;
			}
			
			// 3) j == 0�ε� i�� 0���� ũ�� ������
			else if (i > 0 && j == 0) {
				//System.out.println(x.charAt(i-1) + "(x" + i + ") ����");
				backtrace[index++] = x.charAt(i-1) + "(x" + i + ") ����";
				i--;
			}
			
			// 4) i, j�� ��� 0���� Ŭ ���� ���� ��ġ����
			else { // ����, ����, �밢�� ������ �� ��
				int delete = cost[i - 1][j];
				int change = cost[i - 1][j - 1];
				int insert = cost[i][j - 1];
				// ���� ���� �� ã�´�.
				int min = Get_min(delete, change, insert);
				// ��) ���� �ּҰ��� ���� ���� ���ٸ� i, j �� ����
				if (min == cost[i][j]) {
					i--;
					j--;
				}
				// ��) ���� ���� �ּ� ���� �ٸ� ���
				else { // �ּ� ���� �밢��, ����, �������� ã�´�.
					if (min == change) {
						//System.out.println(x.charAt(i-1) + "(x" + i + ")�� " + y.charAt(j-1) + "(y" + j + ")�� ��ü");
						backtrace[index++] = x.charAt(i-1) + "(x" + i + ")�� " + y.charAt(j-1) + "(y" + j + ")�� ��ü";
						i--;
						j--;
					} else if (min == insert) {
						//System.out.println(y.charAt(j-1) + "(y" + j + ") ����");
						backtrace[index++] = y.charAt(j-1) + "(y" + j + ") ����";
						j--;
					} else {
						//System.out.println(x.charAt(i-1) + "(x" + i + ") ����");
						backtrace[index++] = x.charAt(i-1) + "(x" + i + ") ����";
						i--;
					}
				}
			}
		}
		
		// backtrace�� ��� ������ �Ųٷ� ����Ѵ�.
		for (i = index - 1; i >= 0; i--)
			System.out.println(backtrace[i]);
	}

	public void Print(int n, int m) {
		int i, j;

		System.out.println("<c(i, j)ǥ ���>");
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

		System.out.println("<edit(i, j)ǥ ���>");
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