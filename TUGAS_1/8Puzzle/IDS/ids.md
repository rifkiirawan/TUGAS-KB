## Penerapan IDS Dalam Penyelesaian 8 Puzzle

Dalam program berikut, melakukan pencarian state yang benar untuk menyelesaikan 8 puzzle dengan metode `Iterative Deepening Search`. Metode ini adalah sama seperti metode `Depth First Search` namun dalam implementasinya ditambahkan limit dalam pencarian statenya yang dilakukan bertahap dari iterasi 0 hingga mencapai goal yang ditentukan.
```
int dfs(int idsdepth){
		deque<Node> toexpand;
		
		if (idsdepth==-1) idsdepth = sizeof(int);
		
		toexpand.push_back(*this);
		while ( !toexpand.empty() ){
				if (toexpand.back().depth < idsdepth){
					if ( toexpand.back().s.goal()==1 ){ 
						if (idsdepth != sizeof(int))  
							cout << "------|IDS|------" << endl;
						cout << "Solution found!" << endl;
						toexpand.back().print();
						toexpand.clear();
						return cost;
					}
					else{
						Node t;
						t= toexpand.back().copy();
						toexpand.pop_back();
						t.expand(&toexpand);
					}
				}
				else return 0;
		}
		if ( toexpand.empty() ) cout << endl << "Solution NOT found!" << endl;
		return 0;
	}
	
	int ids(){
		for(int i=0;;i++){
			int t = dfs(i);
			if (t!=0) return t; 
		}
	}
```

`Iterative Deepening Search` (IDS) merupakan sebuah strategi umum yang biasanya dikombinasikan dengan Depth First tree search, yang akan menemukan berapa depth limit terbaik untuk digunakan. Hal ini dilakukan dengan secara menambah limit secara bertahap, mulai dari 0,1, 2, dan seterusnya sampai goal sudah ditemukan.

![ids](https://user-images.githubusercontent.com/52326074/77226305-dd05a080-6ba9-11ea-8a8e-4216c8be6935.png)

Iterative Deepening DFS dengan kata-kata sederhana menjalankan DFS dengan secara bertahap meningkatkan batas kedalaman - 0, kemudian mengulangi DFS dari awal dengan batas kedalaman 1, kemudian mengulangi DFS dari awal dengan tingkat kedalaman 2, dan seterusnya, hingga solusi ditemukan . Jadi bagaimana ini menggabungkan manfaat DFS dan BFS?

Ini memiliki persyaratan memori sederhana seperti DFS yaitu O (bm)

Sejak menjalankan DFS (meskipun dengan meningkatkan level kedalaman dengan setiap iterasi), persyaratan memorinya akan sama dengan DFS.

Ini optimal asalkan biaya jalur adalah fungsi nececreasing dari kedalaman node, seperti BFS. Karena Anda mengulangi strategi DFS dengan meningkatkan batas kedalaman dengan setiap iterasi, Anda dapat yakin bahwa Anda melintasi saudara kandung leluhur Anda dalam iterasi sebelumnya yang pada gilirannya menjamin bahwa tidak ada keadaan solusi yang ada pada level yang lebih dangkal.

Lengkap seperti BFS asalkan faktor percabangannya terbatas. Karena itu melintasi lebar juga - karena Anda mengulangi DFS dengan tingkat kedalaman yang meningkat - itu tidak bisa terjebak pada jalur yang tak terbatas.
