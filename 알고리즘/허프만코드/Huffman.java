import java.util.*;
import java.io.*;

class TreeNode {
	public int weight;
	public char ch;
	public TreeNode lchild;
	public TreeNode rchild;
	
	// �� ��
	public TreeNode() {
		weight = 0;
		ch = 0;
		lchild = rchild = null;
	}
	
	// ���� ���Ͽ� ������ �Լ� (���ڿ� �󵵼� �Է�)
	public TreeNode(int weight, char ch) {
		this.weight = weight;
		this.ch = ch;
	}
}

class Heap {
	ArrayList<TreeNode> heap = new ArrayList<TreeNode>();
	
	public Heap() { heap.add(null); } // �ε��� 0�� ������� �ʴ´�.
	
	public void Insert(TreeNode t) {
		heap.add(t); // �ϴ� �����ϰ�
		
		// ���Ŀ� ����
		int child = heap.size()-1;
		int parent = child / 2;
			// heap �� �ڽ��� weight�� �θ��� weight���� ���� ����
		while (parent >= 1 && heap.get(child).weight < heap.get(parent).weight) {
			Collections.swap(heap, child, parent); // �ڽİ� �θ��� ��ġ�� �ٲ۴�
			
			child = parent;
			parent = child / 2;
		}
		//System.out.println("Insert() : " + t.weight);
	}
	
	public TreeNode Least() {
		if (heap.size() <= 1) return null; // �� heap�� ���
		
		TreeNode res = heap.get(1); // ��ȯ��
		heap.set(1, heap.get(heap.size()-1)); // ù ��° ���Ҹ� �� ������ ���ҷ� ��ü
		heap.remove(heap.size()-1); // ���� ������ ���� ����
		
		int p = 1;
		int lc = p * 2;
		int rc = p * 2 + 1;
		int min;
			// ��ȿ�� ���� ���� ���� �ݺ�
		while (lc <= heap.size() - 1) {
			if (rc > heap.size()-1) { // ������ �ڽ� ���� ���
				// ���� �ڽ��� weight ���� �θ��� weight���� ũ�ų� ������ break
				if (heap.get(lc).weight >= heap.get(p).weight) break;
				
				min = lc;
			}
			// ���� �ڽİ� ������ �ڽ� ��� ���� ���
			else { // ���ʰ� ������ �ڽ��� weight ���� ��� �θ��� weight���� ũ�ų� ������ break
				if (heap.get(lc).weight >= heap.get(p).weight && heap.get(rc).weight >= heap.get(p).weight) break;
				
				// ���� �ڽİ� ������ �ڽ��� weight �� �� ���� ���� �����Ѵ�.
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
	
	// heap ���� üũ�� �Լ�
	public void Print() {
		System.out.print("heap ����: ");
		for (int i = 1; i <= heap.size() - 1; i++)
			System.out.print(heap.get(i).weight + "\t");
		System.out.println();
	}
}

public class Huffman {
	public static HashMap<Character, Integer> weights = new HashMap<Character, Integer>();
	public static Heap huff = new Heap();
	public static int n = 0; // �պ� ���� ���� ī���� ����
	
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		System.out.print("���ϸ�: ");
		String fname = scan.next();
		scan.close();
		GetFreq(fname);
		TreeNode root = MakeTree();
		
		int huffmanCode [] = new int[weights.size() - 1];
		System.out.println("<���>");
		Encoding(root, huffmanCode, 0);
	}
	
	// ���� �а� �� ������ �󵵼��� �ؽø� weights�� �ִ� �Լ�
	public static void GetFreq(String filename) {
		try {
			String fname = "D:/�ܱ���/3-1/�˰���/����3/"; // path
			fname += filename; // add file name
	          
			// ���� ��ü ����
			File file = new File(fname);
	          
			// �Է� ��Ʈ�� ����
			FileReader reader = new FileReader(file);
			int cur = 0;
			while ((cur = reader.read()) != -1) {
				// System.out.print((char)cur);
				if (!(weights.containsKey((char)cur)))
					weights.put((char)cur, 1); // ������ �߰�
	             else // ������ value ������Ų��.
	            	 weights.put((char)cur, weights.get((char)cur)+1);
			}
			reader.close();
		} catch (FileNotFoundException e) {
			e.getStackTrace();
		} catch (IOException e) {
			e.getStackTrace();
		}
	}
	
	// ���� ó���� �պ� ������ ��� huff�� �����ϴ� �Լ�
	public static void InitialHuffman() {
		Set<Character> keys = weights.keySet();
		Iterator<Character> it = keys.iterator();
		while (it.hasNext()) { // ���� key�� �����ϴ� ����
			Character key = it.next(); // key �� �а�
			Integer value = weights.get(key); // value �� �а�
			TreeNode tmp = new TreeNode(value, key); // �� ��� ������
			huff.Insert(tmp); // �����Ѵ�.
			n++; // �պ� ���� ���� ����
		}
		//huff.Print();
	}
	
	// ������ Ʈ�� ����� �Լ�
	public static TreeNode MakeTree() {
		InitialHuffman(); // ���� ���� ��� �߰�
		//System.out.println("MakeTree ����");
		for (int i = 1; i < n; i++) {
			TreeNode pt = new TreeNode();
			pt.lchild = huff.Least();
			pt.rchild = huff.Least();
			pt.weight = (pt.lchild.weight) + (pt.rchild.weight);
			huff.Insert(pt);
			//huff.Print();
		}
		//System.out.println("MakeTree ��");
		return huff.Least();
	}
	
	// ������ Ʈ���� �̿��� �� ������ �ڵ带 �����ϴ� �Լ�
	public static void Encoding(TreeNode root, int codes[], int index) {
		if (root.lchild != null) { // ���� ���� ���� 0
			codes[index] = 0;
			Encoding(root.lchild, codes, index+1);
		}
		if (root.rchild != null) { // ������ ���� ���� 1
			codes[index] = 1;
			Encoding(root.rchild, codes, index+1);
		}
		if (root.lchild == null && root.rchild == null) { // �ܸ� ���
			System.out.print(root.ch + " (�󵵼� " + root.weight + ") �ڵ�: ");
			for (int i = 0; i < index; i++)
				System.out.print(codes[i]);
			System.out.println();
		}
	}
}