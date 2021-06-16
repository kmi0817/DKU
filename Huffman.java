import java.util.*;
import java.io.*;

class TreeNode {
	public int weight;
	public char ch;
	public TreeNode lchild;
	public TreeNode rchild;
	
	// 그 외
	public TreeNode() {
		weight = 0;
		ch = 0;
		lchild = rchild = null;
	}
	
	// 실제 파일용 생성자 함수 (문자와 빈도수 입력)
	public TreeNode(int weight, char ch) {
		this.weight = weight;
		this.ch = ch;
	}
}

class Heap {
	ArrayList<TreeNode> heap = new ArrayList<TreeNode>();
	
	public Heap() { heap.add(null); } // 인덱스 0은 사용하지 않는다.
	
	public void Insert(TreeNode t) {
		heap.add(t); // 일단 삽입하고
		
		// 이후에 정리
		int child = heap.size()-1;
		int parent = child / 2;
			// heap 내 자식의 weight가 부모의 weight보다 작을 동안
		while (parent >= 1 && heap.get(child).weight < heap.get(parent).weight) {
			Collections.swap(heap, child, parent); // 자식과 부모의 위치를 바꾼다
			
			child = parent;
			parent = child / 2;
		}
		//System.out.println("Insert() : " + t.weight);
	}
	
	public TreeNode Least() {
		if (heap.size() <= 1) return null; // 빈 heap일 경우
		
		TreeNode res = heap.get(1); // 반환값
		heap.set(1, heap.get(heap.size()-1)); // 첫 번째 원소를 맨 마지막 원소로 대체
		heap.remove(heap.size()-1); // 기존 마지막 원소 제거
		
		int p = 1;
		int lc = p * 2;
		int rc = p * 2 + 1;
		int min;
			// 유효한 원소 있을 동안 반복
		while (lc <= heap.size() - 1) {
			if (rc > heap.size()-1) { // 오른쪽 자식 없을 경우
				// 왼쪽 자식의 weight 값이 부모의 weight보다 크거나 같으면 break
				if (heap.get(lc).weight >= heap.get(p).weight) break;
				
				min = lc;
			}
			// 왼쪽 자식과 오른쪽 자식 모두 있을 경우
			else { // 왼쪽과 오른쪽 자식의 weight 값이 모두 부모의 weight보다 크거나 같으면 break
				if (heap.get(lc).weight >= heap.get(p).weight && heap.get(rc).weight >= heap.get(p).weight) break;
				
				// 왼쪽 자식과 오른쪽 자식의 weight 중 더 작은 것을 선택한다.
				if(heap.get(lc).weight <= heap.get(rc).weight)
					min = lc;
				else
					min = rc;
			}
			// swap
			Collections.swap(heap, min, p);
			
			p = min;
			lc = p * 2;
			rc = p * 2 + 1;
		}
		//System.out.println("Least() : " + res.weight);
		return res;
	}
	
	// heap 내부 체크용 함수
	public void Print() {
		System.out.print("heap 내부: ");
		for (int i = 1; i <= heap.size() - 1; i++)
			System.out.print(heap.get(i).weight + "\t");
		System.out.println();
	}
}

public class Huffman {
	public static HashMap<Character, Integer> weights = new HashMap<Character, Integer>();
	public static Heap huff = new Heap();
	public static int n = 0; // 합병 파일 개수 카운팅 변수
	
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		System.out.print("파일명: ");
		String fname = scan.next();
		scan.close();
		GetFreq(fname);
		TreeNode root = MakeTree();
		
		int huffmanCode [] = new int[weights.size() - 1];
		System.out.println("<결과>");
		Encoding(root, huffmanCode, 0);
	}
	
	// 파일 읽고 각 문자의 빈도수를 해시맵 weights에 넣는 함수
	public static void GetFreq(String filename) {
		try {
			String fname = "D:/단국대/3-1/알고리즘/과제3/"; // path
			fname += filename; // add file name
	          
			// 파일 객체 생성
			File file = new File(fname);
	          
			// 입력 스트림 생성
			FileReader reader = new FileReader(file);
			int cur = 0;
			while ((cur = reader.read()) != -1) {
				// System.out.print((char)cur);
				if (!(weights.containsKey((char)cur)))
					weights.put((char)cur, 1); // 없으면 추가
	             else // 있으면 value 증가시킨다.
	            	 weights.put((char)cur, weights.get((char)cur)+1);
			}
			reader.close();
		} catch (FileNotFoundException e) {
			e.getStackTrace();
		} catch (IOException e) {
			e.getStackTrace();
		}
	}
	
	// 가장 처음에 합병 파일을 모두 huff에 삽입하는 함수
	public static void InitialHuffman() {
		Set<Character> keys = weights.keySet();
		Iterator<Character> it = keys.iterator();
		while (it.hasNext()) { // 다음 key가 존재하는 동안
			Character key = it.next(); // key 값 읽고
			Integer value = weights.get(key); // value 값 읽고
			TreeNode tmp = new TreeNode(value, key); // 새 노드 생성해
			huff.Insert(tmp); // 삽입한다.
			n++; // 합병 파일 개수 증가
		}
		//huff.Print();
	}
	
	// 허프만 트리 만드는 함수
	public static TreeNode MakeTree() {
		InitialHuffman(); // 먼저 단일 노드 추가
		//System.out.println("MakeTree 시작");
		for (int i = 1; i < n; i++) {
			TreeNode pt = new TreeNode();
			pt.lchild = huff.Least();
			pt.rchild = huff.Least();
			pt.weight = (pt.lchild.weight) + (pt.rchild.weight);
			huff.Insert(pt);
			//huff.Print();
		}
		//System.out.println("MakeTree 끝");
		return huff.Least();
	}
	
	// 허프만 트리를 이용해 각 문자의 코드를 결정하는 함수
	public static void Encoding(TreeNode root, int codes[], int index) {
		if (root.lchild != null) { // 왼쪽 노드로 가면 0
			codes[index] = 0;
			Encoding(root.lchild, codes, index+1);
		}
		if (root.rchild != null) { // 오른쪽 노드로 가면 1
			codes[index] = 1;
			Encoding(root.rchild, codes, index+1);
		}
		if (root.lchild == null && root.rchild == null) { // 단말 노드
			System.out.print(root.ch + " (빈도수 " + root.weight + ") 코드: ");
			for (int i = 0; i < index; i++)
				System.out.print(codes[i]);
			System.out.println();
		}
	}
}