## Penerapan Heuristic Dalam Penyelesaian 8 Puzzle

Dalam program ini diminta untuk menyelesaikan 8 puzzle menggunakan metode heuristic 1 dan 2. Dimana penjelasan heuristic 1 dan 2 ada dibawah. Jika menggunakan heuristic 1 maka yang dilihat yaitu banyaknya grid yang menempati tempat yg salah, tetapi jika menggunakan heuristic 2 maka yang dilihat yaitu total keseluruhan jarak tiap grid yang menempati tempat yang salah terhadap posisi grid yang benar, atau sering disebut dengan manhattan distance.

Jadi dalam penyelesainnya kita mengeluarkan hasil setiap langkah puzzle dengan melihat penempatan grid yang salah kemudian dicari penempatan grid yang benar untuk mencapai final state yang diinginkan.

Dalam program ini, penyelesaian dengaan menggunakan tree, seperti pada gmbar dibawah nantinya.
```
struct Node { 
	// stores the parent node of the current node helps in tracing path when the answer is found 
	Node* parent; 
	// stores matrix 
	int mat[N][N]; 
	// stores blank tile coordinates 
	int x, y; 
	// stores the number of misplaced tiles 
	int cost; 
	// stores the number of moves so far 
	int level; 
}; 
```

Kemudian setiap langkah pastinya memerlukan node untuk meletakkan grid nya, maka dari itu program dibawah ini untuk meyediakan node setiap langkah.
```
Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node* parent) { 
	Node* node = new Node; 
	// set pointer for path to root 
	node->parent = parent; 
	// copy data from parent node to current node 
	memcpy(node->mat, mat, sizeof node->mat); 
	// move tile by 1 position 
	swap(node->mat[x][y], node->mat[newX][newY]); 
	// set number of misplaced tiles 
	node->cost = INT_MAX; 
	// set number of moves so far 
	node->level = level; 
	// update new blank tile cordinates 
	node->x = newX; 
	node->y = newY; 
	return node; 
} 
```

Karena heuristic ini melihat posisi grid yang salah, maka fungsi program dibawah ini untuk menghitung banyak nya angka yang tidak sesuai dengan final state.
```
int calculateCost(int initial[N][N], int final[N][N]) { 
	int count = 0; 
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < N; j++) 
			if (initial[i][j] && initial[i][j] != final[i][j]) 
				count++; 
	return count; 
} 
```

Untuk bagian dibawah ini adalah pergerakan puzzle yang dimisalkan dengan `botton, left, top, right`
```
int row[] = { 1, 0, -1, 0 }; 
int col[] = { 0, -1, 0, 1 }; 
```

Setelah itu, fungsi dibawah ini untu megecek apakah posisi grid dimana angka didalamnya sudah sesuai dengan final statenya.
```
int isSafe(int x, int y) { 
	return (x >= 0 && x < N && y >= 0 && y < N); 
} 
```

Semua fungsi dijalankan dalam fungsi dibawah ini dimana untuk mengecek solusi penyelesaian menggunakan heuristic dengan initial awal puzzle yang dimasukkan kemudian final state yang diinginkan.
```
void solve(int initial[N][N], int x, int y, int final[N][N]) { 
	// Create a priority queue to store live nodes of search tree; 
	priority_queue<Node*, std::vector<Node*>, comp> pq; 
	// create a root node and calculate its cost 
	Node* root = newNode(initial, x, y, x, y, 0, NULL); 
	root->cost = calculateCost(initial, final); 
	// Add root to list of live nodes; 
	pq.push(root); 
	// Finds a live node with least cost, add its childrens to list of live nodes and 
	// finally deletes it from the list. 
	while (!pq.empty()) { 
		// Find a live node with least estimated cost 
		Node* min = pq.top(); 
		// The found node is deleted from the list of live nodes 
		pq.pop(); 
		// if min is an answer node 
		if (min->cost == 0) { 
			// print the path from root to destination; 
			printPath(min); 
			return; 
		} 
		// do for each child of min, max 4 children for a node 
		for (int i = 0; i < 4; i++) { 
			if (isSafe(min->x + row[i], min->y + col[i])) { 
				// create a child node and calculate its cost 
				Node* child = newNode(min->mat, min->x, 
							min->y, min->x + row[i], 
							min->y + col[i], 
							min->level + 1, min); 
				child->cost = calculateCost(child->mat, final); 

				// Add child to list of live nodes 
				pq.push(child); 
			} 
		} 
	} 
} 
```

![8p](https://user-images.githubusercontent.com/52326074/77151801-52e60b00-6ac9-11ea-84f6-e27a66305731.png)

8-puzzle adalah puzzle yang ditemukan dan dipopulerkan oleh Noyes Palmer Chapman pada tahun 1870-an. Ini dimainkan pada kotak 3-oleh-3 dengan 8 blok persegi berlabel 1 hingga 8 dan kotak kosong. Tujuan Anda adalah mengatur ulang blok agar sesuai. Anda diizinkan untuk menggeser blok secara horizontal atau vertikal ke dalam kotak kosong. Berikut ini menunjukkan urutan langkah hukum dari posisi dewan awal (kiri) ke posisi tujuan (kanan).

8-Puzzle merupakan salah satu jenis permainan puzzle dimana kita harus mencapai goal puzzle dari initial puzzle yang diberikan. Untuk mencapai goal puzzle, 8-puzzle ini menyediakan satu grid kosong agar grid-grid lain disekitarnya dapat digerakkan. Sebagai contoh Inisial State dan Goal State dari sebuah puzzle adalah :

![8ph](https://user-images.githubusercontent.com/52326074/77028971-f9001b00-69cc-11ea-9301-6be95c8f1df1.PNG)

Pada pembahasan kali ini, saya ingin menyelesaikan puzzle ini dengan suatu algoritma, yaitu Algoritma Greedy, dengan menggunakan dua fungsi heuristik. Algoritma Greedy merupakan algoritma yang sederhana dan lempeng (straightforward). Secara harfiah greedy artinya rakus atau tamak.

Algoritma Greedy membentuk solusi langkah per langkah. Terdapat banyak pilihan yang perlu dieksplorasi pada setiap langkah solusi. Oleh karena itu, pada setiap langkah harus dibuat keputusan yang terbaik dalam menentukan pilihan. 

Dalam bahasan ini, fungsi heuristik yang akan kita tampilkan yaitu adalah sebagai berikut.
- h₁(n) : sebagai banyak grid yang menempati tempat yang salah.
- h₂(n) : sebagai total keseluruhan jarak tiap grid yang menempati tempat yang salah terhadap posisi grid yang benar, atau sering disebut dengan manhattan distance.

Solusi Penyelesaian dengan fungsi Heuristik Pertama yaitu banyak grid yang menempati tempat yang salah

![8puzzle-heuristic1.1](https://user-images.githubusercontent.com/52326074/77029102-58f6c180-69cd-11ea-9571-7a69fe89de7d.PNG)
![8puzzle-heuristic1.2](https://user-images.githubusercontent.com/52326074/77029100-585e2b00-69cd-11ea-8d32-03512709f26c.PNG)
![8puzzle-heuristic1.3](https://user-images.githubusercontent.com/52326074/77029097-572cfe00-69cd-11ea-845e-7e8b50514214.PNG)

Solusi :
Initial State -> Right -> Up -> Right -> Down -> Down -> Left -> Up -> Right -> Down(Goal)

Solusi Penyelesai dengan fungsi Heuristik Kedua yaitu total keseluruhan jarak tiap grid yang menempati tempat yang salah terhadap posisi grid yang benar, atau sering disebut dengan manhattan distance.

![8puzzle-heuristic2.1](https://user-images.githubusercontent.com/52326074/77029181-8f344100-69cd-11ea-9799-24cda528fdd5.PNG)
![8puzzle-heuristic2.2](https://user-images.githubusercontent.com/52326074/77029178-8e9baa80-69cd-11ea-9d35-2282c1916e48.PNG)
![8puzzle-heuristic2.3](https://user-images.githubusercontent.com/52326074/77029175-8d6a7d80-69cd-11ea-8775-2fd302b4ad62.PNG)

Solusi :
Initial State -> Right -> Up -> Right -> Down -> Down -> Left -> Up -> Right -> Up(Goal)


Kesimpulannya, dari semua yang telah dipaparkan diatas, penggunaan dari dua fungsi heuristik Algoritma Greedy pada solusi penyelesaian 8-puzzle, baik fungsi heuristik pertama dan kedua sama sama mampu memberikan solusi penyelesaian dari awal state sampai ke goal state. Tetapi menurut pendapat saya, pada penggunaan fungsi heuristik pertama jumlah State puzzle yang memiliki fungsi heuristik yang sama lebih banyak dari pada penggunaan fungsi heuristik kedua. Jadi, penggunaan solusi dari fungsi heuristik kedua dalam contoh penyelesaian 8-puzzle diatas lebih optimal dari pada fungsi heuristik pertama.
