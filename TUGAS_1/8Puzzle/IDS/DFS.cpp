/*Mengambil program dari geeksforgeeks setelah melihat tutorial
youtube yang mengatakan bahwa branch and bound merupakan algoritma
Depth First Search yang akan mengambil tiap node secara level per level
(memeriksa tipa node ke yang paling dalam terlebih dahulu, baru dilanjutkan
kembali ke node berikutnya yang terletak di level atas, namun hal ini akan
pencarian tidak akan selesai)
layaknya penggunaan stack
https://www.geeksforgeeks.org/8-puzzle-problem-using-branch-and-bound/*/

// Program to print path from root node to destination node 
// for N*N -1 puzzle algorithm using Branch and Bound 
// The solution assumes that instance of puzzle is solvable 
#include <bits/stdc++.h> 
using namespace std; 
#define N 3 

// state space tree nodes 
struct Node 
{ 
	// stores the parent node of the current node 
	// helps in tracing path when the answer is found 
	Node* parent; 

	// stores matrix 
	int mat[N][N]; 

	// stores blank tile coordinates 
	int x, y;

	// stores the number of moves so far 
	int level; 
}; 

// Function to print N x N matrix 
int printMatrix(int mat[N][N]) 
{ 
	for (int i = 0; i < N; i++) 
	{ 
		for (int j = 0; j < N; j++){
			printf("%d ", mat[i][j]); 
		}
		printf("\n"); 
	} 
} 

// Function to allocate a new node 
Node* newNode(int mat[N][N], int x, int y, int newX, 
			int newY, int level, Node* parent) 
{ 
	Node* node = new Node; 

	// set pointer for path to root 
	node->parent = parent; 

	// copy data from parent node to current node 
	memcpy(node->mat, mat, sizeof node->mat); 

	// move tile by 1 position 
	swap(node->mat[x][y], node->mat[newX][newY]); 

	// set number of moves so far 
	node->level = level; 

	// update new blank tile cordinates 
	node->x = newX; 
	node->y = newY; 

	return node; 
} 

// botton, left, top, right 
int row[] = { 1, 0, -1, 0 }; 
int col[] = { 0, -1, 0, 1 }; 


// Function to check if (x, y) is a valid matrix cordinate 
int isSafe(int x, int y) 
{ 
	return (x >= 0 && x < N && y >= 0 && y < N); 
} 

// print path from root node to destination node 
void printPath(Node* root) 
{ 
	if (root == NULL){
		return;
	}
	printPath(root->parent); 
	printMatrix(root->mat); 
	printf("\n"); 
} 

bool testing (int mat[N][N],int final [N] [N])
 {
 	for (int i = 0; i < N; i++) 
	{ 
		for (int j = 0; j < N; j++) 
			if (mat [i] [j] != final [i] [j]) 
			return false;
	}
 	return true;
 }

// Function to solve N*N - 1 puzzle algorithm using 
// Branch and Bound. x and y are blank tile coordinates 
// in initial state 
void solve(int initial[N][N], int x, int y, 
		int final[N][N]) 
{ 
	// Create a priority stack to store live nodes of 
	// search tree; 
	stack <Node*> pq;
	
	// create a root node and calculate its cost 
	Node* root = newNode(initial, x, y, x, y, 0, NULL); 
	
	// Add root to list of live nodes; 
	pq.push(root); 

	// Finds a live node with least cost, 
	// add its childrens to list of live nodes and 
	// finally deletes it from the list. 
	while (!pq.empty()) 
	{ 
		// Find a live node with least estimated cost 
		Node* min = pq.top();

		// The found node is deleted from the list of 
		// live nodes 
		pq.pop(); 

	
		// if min is an answer node 
		if (testing (min->mat, final)) 
		{ 
			// print the path from root to destination; 
			printPath(min);
			printf ("Move: %d", min->level);
			return; 
		} 
		
		// do for each child of min 
		// max 4 children for a node 
		for (int i = 0; i < 4; i++) 
		{ 
			if (isSafe(min->x + row[i], min->y + col[i])) 
			{ 
				// create a child node and calculate 
				// its cost 
				Node* child = newNode(min->mat, min->x, 
							min->y, min->x + row[i], 
							min->y + col[i], 
							min->level + 1, min);  

				// Add child to list of live nodes 
				pq.push(child); 
			} 
		} 
	} 
} 

// Driver code 
int main() 
{ 
	// Initial configuration 
	// Value 0 is used for empty space 
	int initial[N][N] = 
	{ 
		{1, 2, 3}, 
		{5, 6, 0}, 
		{7, 8, 4} 
	}; 

	// Solvable Final configuration 
	// Value 0 is used for empty space 
	
	int final[N][N] = 
	{ 
		{1, 2, 3}, 
		{5, 8, 6}, 
		{0, 7, 4} 
	}; 

	// Blank tile coordinates in initial 
	// configuration 
	int x = 1, y = 2; 

	solve(initial, x, y, final); 

	return 0; 
} 

