## Minimax - Tic Tac Toe

Dalam permasalahan minimax, selain menentukan nilai min maupun max dalam sekelompok angka, namun juga bisa diaplikasikan dalam penyelesaian tic tac toe game. Pastinya dalam menjalankan permainan ini, dilakukan secara bergiliran untuk meletakkan karakter pada kolom yang disediakan.

Pada bagian dibawah ini untuk mendeteksi pada kolom apakah sudah terisi karakter `X` atau `O` atau bahkan kosong ` `.
```
char gridChar(int i) {
    switch(i) {
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
    }
}
```

Untuk bagian dibawah ini, mencetak board tic tac toe.
```
void draw(int b[9]) {
    printf(" %c | %c | %c\n",gridChar(b[0]),gridChar(b[1]),gridChar(b[2]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",gridChar(b[3]),gridChar(b[4]),gridChar(b[5]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",gridChar(b[6]),gridChar(b[7]),gridChar(b[8]));
}
```

Kemudian, fungsi program dibawah ini untuk mengecek setelah player melakukan langkah / mengisi karakter pada board itu mencapai kemenangan (sudah terbentuk garis).
```
int win(const int board[9]) {
    //determines if a player has won, returns 0 otherwise.
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(board[wins[i][0]] != 0 &&
           board[wins[i][0]] == board[wins[i][1]] &&
           board[wins[i][0]] == board[wins[i][2]])
            return board[wins[i][2]];
    }
    return 0;
}
```

Sedangkan untuk bagian dibawah ini, untuk berjalannya tic tac toe dengan mengecek perpindahan player meletakkan karakter pada board dengan menggunakan metode minimax.
```
int minimax(int board[9], int player) {
    //How is the position like for player (their turn) on board?
    int winner = win(board);
    if(winner != 0) return winner*player;

    int move = -1;
    int score = -2;//Losing moves are preferred to no move
    int i;
    for(i = 0; i < 9; ++i) {//For all moves,
        if(board[i] == 0) {//If legal,
            board[i] = player;//Try the move
            int thisScore = -minimax(board, player*-1);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }//Pick the one that's worst for the opponent
            board[i] = 0;//Reset board after try
        }
    }
    if(move == -1) return 0;
    return score;
}
```

Bagian dibawah ini untuk lawan / dalam hal ini dibuat computer sebagai lawan untuk berjalan menentukan letak karakter.
```
void computerMove(int board[9]) {
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(board[i] == 0) {
            board[i] = 1;
            int tempScore = -minimax(board, -1);
            board[i] = 0;
            if(tempScore > score) {
                score = tempScore;
                move = i;
            }
        }
    }
    //returns a score based on minimax tree at a given node.
    board[move] = 1;
}
```

Sedangkan bagian dibawah ini untuk player utama berjalan menentukan letak karakter.
```
void playerMove(int board[9]) {
    int move = 0;
    do {
        printf("\nInput move ([0..8]): ");
        scanf("%d", &move);
        printf("\n");
    } while (move >= 9 || move < 0 && board[move] == 0);
    board[move] = -1;
}
```

Tic Tac Toe merupakan permainan yang dimainkan oleh 2 pemain dengan menempatkan ‘buah’ yang berlainan untuk tiap pemain pada kotak 3 x 3. Penempatan ‘buah’ dilakukan secara bergantian sehingga salah satu pemain menjadi pemenang atau seluruh kotak terisi oleh ‘buah’. Salah satu pemain dikatakan menang jika dapat menempatkan ‘buah’ berjajar sebanyak 3 buah baik secara horisontal, vertikal atau diagonal.

Dalam permainan ini kita harus berusaha untuk memaksimalkan kemungkinan untuk mencapai kemenangan pemain pertama dan meminimalkan kemungkinan kemenangan lawan (pemain kedua).

Komponen penelusuran dalam aplikasi minimax pada permainan Tic Tac Toe ini adalah :

- `Initial state` merupakan keadaan saat pencarian akan dilakukan, pada saat permainan mulai dilakukan (jika pemain pertama jalan pertama), initial statenya adalah :

![tictactoe.1](https://user-images.githubusercontent.com/52326074/77034748-4dab9200-69dd-11ea-8215-48c660f28237.JPG)

Initial state selalu berubah saat giliran jalan pemain pertama.
- `Operator (rule/ilegal moves)`, Operator pada permainan ini adalah pemain dapat meletakkan ‘buah’ nya secara sembarang di kotak yang masih kosong.
- `Terminal Test` adalah keadaan dimana komposisi terbaik yang dilakukan pemain pertama setelah diadakan penelusuran.
- `Utility function` pada permainan ini adalah mencari kemungkinan kemenangan bagi pemain pertama dikurangi dengan kemungkinan kemenangan dari pemain lawan. Pada saat permainan dimulai masing-masing kemungkinan kemenangan tiap pemain adalah 8 yaitu 3 horisontal + 3 vertikal + 2 diagonal.

![tictactoe.2](https://user-images.githubusercontent.com/52326074/77034890-b561dd00-69dd-11ea-9a93-b8adca75b3e8.JPG)

Contoh pada komposisi :

![tictactoe.3](https://user-images.githubusercontent.com/52326074/77034911-c4488f80-69dd-11ea-904e-87b6294917db.JPG)

Kemungkinan kemenangan pemain pertama adalah 6, sedangkan kemungkinan kemenangan pemain kedua adalah 5.

![tictactoe.4](https://user-images.githubusercontent.com/52326074/77034938-d88c8c80-69dd-11ea-845c-596e936eaad9.JPG)

Jadi nilai untuk komposisi di atas adalah 6 – 5 = 1.

Dari keadaan permainan dimulai, graph minimax untuk Two-Ply Search dapat digambarkan sebagai berikut (X = pemain pertama, O = pemain kedua):

![tictactoe.5](https://user-images.githubusercontent.com/52326074/77034975-efcb7a00-69dd-11ea-97ae-2ff5b0943d04.JPG)

Nilai node E sampai P didapat dari utility function yang telah didefinisikan sebelumnya sehingga didapatkan :
```
E = 6 – 5 = 1
F = 5 – 5 = 0
G = 6 – 5 = 1
H = 5 – 5 = 0
I = 4 – 5 = -1
J = 5 – 4 = 1
K = 6 – 4 = 2
L = 5 – 6 = -1
M = 5 – 5 = 0
N = 5 – 6 = -1
O = 6 – 6 = 0
P = 4 – 6 = -2
```

Ada sembilan langkah yang mungkin dilakukan oleh pemain pertama karena kotak kosongnya berjumlah 9, tapi pada diagram diatas hanya diambil 3 kemungkinan (node B,C dan D), karena 6 kemungkinan lainnya setara dengan ke-3 komposisi di atas, misalnya :

![tictactoe.6](https://user-images.githubusercontent.com/52326074/77035007-083b9480-69de-11ea-9932-0b194195291b.JPG)

Dari node B seharusnya didapatkan node anak sebanyak 8 node, dengan mengabaikan node yang setara node anak dari B menjadi E, F, G, H dan I. Dengan cara yang sama didapatkan node anak dari C yaitu J dan K, sedangkan node anak dari D yaitu L, M, N, O dan P.

Karena hanya menggunakan Two-Ply Search, node-node anak dari B, C dan D dicari nilainya, kemudian dicari yang terkecil (min) masing-masing untuk dijadikan nilai B, C dan D. Selanjutnya dicari nilai terbesar (max) dari ketiga nilai tersebut untuk menentukan langkah pemain pertama.

Pada diagram yang digambarkan diatas, node anak dari B bernilai masing-masing E=1, F=0, G=1, H=0 dan I=-1 jadi nilai B diambil yang terkecil yaitu –1.

Node anak dari C bernilai masing-masing J=1 dan K=2 jadi nilai C diambil yang terkecil yaitu 1. Kemudian node anak dari D bernilai masing-masing L=-1, M=0, N=-1, O=0 dan P=-2 jadi nilai C diambil yang terkecil yaitu –2.

Selanjutnya dari nilai node B=-1, C=1, dan D=-2 diambil nilai terbesar yaitu C=1, yang berarti langkah terbaik yang harus dilakukan oleh pemain pertama adalah node C.

Setelah pemain kedua menempatkan buahnya, keadaan saat itu dijadikan initial state dan dilakukan kembali pelacakan dengan langkah yang telah dijelaskan di atas. Contoh : Misalkan pemain kedua meletakkan buahnya seperti gambar berikut :

![tictactoe.7](https://user-images.githubusercontent.com/52326074/77035046-21444580-69de-11ea-89a1-5eeb2dd345c4.JPG)

Dari keadaan ini, graph minimax untuk Two-Ply Search dapat digambarkan sebagai berikut (X = pemain pertama, O = pemain kedua):

![tictactoe.8](https://user-images.githubusercontent.com/52326074/77035066-2e613480-69de-11ea-816d-f67b069d2523.JPG)

Dari diagram diatas, langkah terbaik yang dapat dilakukan oleh pemain pertama terdapat dua pilihan yaitu B(1) dan D(1).
