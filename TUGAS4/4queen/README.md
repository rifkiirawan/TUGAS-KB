# Penjelasan 4 queen
`int ld[30] `
ld adalah array di mana indeksnya mengindikasikan baris-col + N-1 (N-1) adalah untuk menggeser perbedaan untuk menyimpan indeks negatif

`int rd[30]`
rd adalah array di mana indeksnya mengindikasikan baris + col dan digunakan untuk memeriksa apakah ratu dapat ditempatkan di diagonal kanan atau tidak

`int cl[30]`
array kolom di mana indeksnya menunjukkan kolom dan digunakan untuk memeriksa apakah ratu dapat ditempatkan di baris itu atau tidak

`if (col >= N) 
        return true; `
Jika semua ratu telah ditempatkan kemudian mengembalikan true

Fungsi berulang untuk menyelesaikan 4 queen problem dan akan return false jika ratu tidak bisa ditempatkan di row mana saja di kolom ini
`bool solveNQUtil(int board[N][N], int col)`

Untuk mempertimbangkan kolom ini dan coba tempatkan ratu ini di semua baris satu per satu
`for (int i = 0; i < N; i++)`
     
mengecek apakah ratu bisa ditempatkan atau tidak
`if ((ld[i - col + N - 1] != 1 && rd[i + col] != 1) && cl[i] != 1)`
untuk menempatkan ratu
board[i][col] = 1
ld[i - col + N - 1] = rd[i + col] = cl[i] = 1

perulangan untuk menempatkan semua ratu
`if (solveNQUtil(board, col + 1)) 
return true`

Jika menempatkan ratu di papan [i] [col] tidak mengarah ke solusi, maka hapus ratu dari papan [i] [col]
`board[i][col] = 0; (BACKTRACKING) 
ld[i - col + N - 1] = rd[i + col] = cl[i] = 0`

Pada fungsi `bool solveNQ()` berfungsi untuk menyelesaikan masalah 4 Queen dengan backtracking, yang akan mereturn false jika queen tidak dapat diletakkan, dan return true dan menampilkan peletakan dari queen.
