## 8 Queen (Hill Climbing)

Dalam program, bagian untuk mengecek apakah sebuah queen bisa diserang oleh queen lain bisa dilihat pada program dibawah ini.
```
int is_attack(int i,int j) {
    int k,l;
    //checking if there is a queen in row or column
    for(k=0;k<N;k++) {
        if((board[i][k] == 1) || (board[k][j] == 1))
            return 1;
    }
    //checking for diagonals
    for(k=0;k<N;k++) {
        for(l=0;l<N;l++) {
            if(((k+l) == (i+j)) || ((k-l) == (i-j))) {
                if(board[k][l] == 1)
                    return 1;
            }
        }
    }
    return 0;
}
```

Kemudian, setelah dirasa tidak ada queen yang menyerang, maka program dibawah ini merupakan bagian untuk meletakkan queen yang dirasa aman.
```
int N_queen(int n) {
    int i,j;
    //if n is 0, solution found
    if(n==0)
        return 1;
    for(i=0;i<N;i++) {
        for(j=0;j<N;j++) {
            //checking if we can place a queen here or not
            //queen will not be placed if the place is being attacked
            //or already occupied
            if((!is_attack(i,j)) && (board[i][j]!=1)) {
                board[i][j] = 1;
                //recursion wether we can put the next queen with this arrangment or not
                if(N_queen(n-1)==1) {
                    return 1;
                }
                board[i][j] = 0;
            }
        }
    }
    return 0;
}
```

Hill Climbing adalah pencarian heuristik yang digunakan untuk masalah optimasi matematis di bidang Inteligensi Buatan.

Dengan sejumlah besar input dan fungsi heuristik yang baik, ia mencoba untuk menemukan solusi yang cukup baik untuk masalah tersebut. Solusi ini mungkin bukan global optimal maksimum.
- Dalam definisi di atas, `Mathematical Optimization Problems` menyiratkan bahwa mendaki bukit memecahkan masalah di mana kita perlu memaksimalkan atau meminimalkan fungsi nyata yang diberikan dengan memilih nilai dari input yang diberikan. Contoh-Traveling salesman masalah di mana kita perlu meminimalkan jarak yang ditempuh oleh salesman.
- `Heuristic Search` berarti bahwa algoritma pencarian ini mungkin tidak menemukan solusi optimal untuk masalah tersebut. Namun, itu akan memberikan solusi yang baik dalam waktu yang wajar.
- `Heuristic Function` adalah fungsi yang akan memberi peringkat semua alternatif yang mungkin pada setiap langkah percabangan dalam algoritma pencarian berdasarkan informasi yang tersedia. Ini membantu algoritma untuk memilih rute terbaik dari rute yang mungkin.

![hc](https://user-images.githubusercontent.com/52326074/77150635-e36f1c00-6ac6-11ea-977e-153dd3b862e3.png)

## Fitur Hill Climbing
### a. Varian dari menghasilkan dan menguji algoritma

Ini adalah varian dari algoritma generate and test. Algoritma generate and test adalah sebagai berikut:
- Hasilkan solusi yang mungkin.
- Tes untuk melihat apakah ini solusi yang diharapkan.
- Jika solusinya telah ditemukan, keluar lagi, lanjutkan ke langkah 1.

Oleh karena itu kami menyebut Hill climbing sebagai varian dari algoritma hasil dan uji karena mengambil umpan balik dari prosedur pengujian. Kemudian umpan balik ini digunakan oleh generator dalam memutuskan langkah selanjutnya dalam ruang pencarian.

### b. Menggunakan Greedy Aproach

Pada titik mana pun di ruang keadaan, pencarian bergerak ke arah itu saja yang mengoptimalkan biaya fungsi dengan harapan menemukan solusi optimal di akhir.

## Jenis Hill Climbing
### a. Steepest-Ascent Hill Climbing

Pertama-tama memeriksa semua node tetangga dan kemudian memilih simpul yang paling dekat dengan keadaan solusi pada simpul berikutnya.

- Evaluasi keadaan awal. Jika status tujuan maka keluar dari yang lain jadikan status saat ini sebagai keadaan awal
- Ulangi langkah ini sampai solusi ditemukan atau keadaan saat ini tidak berubah
- Exit

### b. Simple Hill Climbing

Ini memeriksa node tetangga satu per satu dan memilih node tetangga pertama yang mengoptimalkan biaya saat ini sebagai node berikutnya. Ini memeriksa node tetangga satu per satu dan memilih node tetangga pertama yang mengoptimalkan biaya saat ini sebagai node berikutnya.

Algoritma Simple Hill climbing :
- Evaluasi keadaan awal. Jika itu adalah keadaan tujuan maka berhentilah dan kembalikan kesuksesan. Kalau tidak, jadikan kondisi awal sebagai kondisi saat ini.
- Loop sampai keadaan solusi ditemukan atau tidak ada operator baru yang dapat diterapkan ke keadaan saat ini.
- Exit

### c. Stochastic Hill Climbing

Itu tidak memeriksa semua node tetangga sebelum memutuskan node mana yang akan dipilih. Itu hanya memilih node tetangga secara acak dan memutuskan (berdasarkan jumlah peningkatan tetangga itu) apakah akan pindah ke tetangga itu atau untuk memeriksa yang lain.

## State Space Diagram untuk Hill Climbing

adalah representasi grafis dari himpunan status yang dapat dicapai oleh algoritma pencarian kami vs nilai fungsi objektif kami (fungsi yang ingin kami maksimalkan).

`X - axis` menunjukkan ruang keadaan yaitu keadaan atau konfigurasi yang dapat dicapai algoritma kami.

`Y - axis` menunjukkan nilai-nilai fungsi obyektif yang sesuai dengan keadaan tertentu.

Solusi terbaik adalah ruang negara di mana fungsi objektif memiliki nilai maksimum (global maksimum).

![8phc](https://user-images.githubusercontent.com/52326074/77142942-355a7680-6ab4-11ea-8c1d-66b86aaef6c9.png)
