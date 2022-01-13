#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//PROTOTYPE MODUL

//MODUL UNTUK USER INTERFACE
void mainMenu();
void interfaceSelectMenu(int x, int y);
void printPapan();
void tampilHurufPemain();
void bersihkanPapan();
void taruhBlok(char blok, int baris, int kolom);
void help();

//MODUL UNTUK KECERDASAN KOMPUTER/BOT
void giliranKomputer(char kataDariPapan[], int baris, int kolom, int* selesai, char orientasi);
void komputerMengisiPapan(char kata[]);
void eksekusiPengisian(int brsPpn, int kolPpn, int letakAwal, int jmlHrf, int posHrf, char kata[], char orientasi);
int cekKosongKanan(int baris, int kolom, int hurufKe, int panjangKata);
int cekKosongBawah(int baris, int kolom, int hurufKe, int panjangKata);
void cariKataDariPapan();

//MODUL UNTUK PEMAIN
void giliranPemain();
void isiPapanPemain(int* x, int* y);
int periksaHuruf(char huruf);

//MODUL UMUM
void mulaiPermainan();
int cekKamus(char kata[]);
void tambahHuruf(char huruf[]);
int tentukanPoin(char huruf);
void tukarHuruf(char huruf[]);
int validasiSekitarKata();
int validBaris(int baris, int kolom);
int validKolom(int baris, int kolom);
int tilesLeft();
void gotoxy(int x, int y);
void resetAll();
int akhirPermainan();
int hurufPertama();
void tentukanPemenang();

//VARIABEL GLOBAL
char blokScrabble[100] = "AAAAAAAAABBCCDDDDEEEEEEEEEEEEFFGGGHHIIIIIIIIIJKLLLLMMNNNNNNOOOOOOOOPPQRRRRRRSSSSTTTTTTUUUUVVWWXYYZ  ";
char blokScrabble2[100] = "AAAAAAAAABBCCDDDDEEEEEEEEEEEEFFGGGHHIIIIIIIIIJKLLLLMMNNNNNNOOOOOOOOPPQRRRRRRSSSSTTTTTTUUUUVVWWXYYZ  ";
char hurufKomputer[7] = "       ";
char hurufPemain[7] = "       ";
char tempHurufPemain[7];
int giliranKe = 1;
int skorPemain = 0;
int skorKomputer = 0;
int kesulitan;
int timer;
int lewati = 0;
int akhir = 0;

typedef struct {
    int B, K;
} koordinat;
koordinat barisKolom;

int x = 10,  y = 5, K = 0, B = 0; 
    char papan[15][15] = {
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' '}
    };

    //Papan2 digunakan untuk pengisian sementara. Sehingga ketika kata yang dimasukkan
    //user tidak valid, maka papan bisa dikembalikan ke kondisi semula.
    char papan2[15][15] = {
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ',' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };

char tampungKata[15][15];
int idx = 0;

//MODUL UTAMA (MAIN MODULE)
int main () {
    while(1) {
        mainMenu();
        getch();
    }
    return 0;
}

//MODUL MULAI PERMAINAN
void mulaiPermainan() {
    //Mengubah ukuran console/terminal
    SMALL_RECT windowSize2 = {0 , 0 , 104 , 57};
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize2);

    srand(time(NULL));
    printPapan();
    tambahHuruf(hurufKomputer);
    tambahHuruf(hurufPemain);
    gotoxy(40, 55);
    printf("%d  ", tilesLeft());
    //LOOP BERJALAN SAMPAI AKHIR PERMAINAN TERCAPAI
    while(akhirPermainan() == 0 && akhir == 0) {
        gotoxy(x, y);
        tukarHuruf(hurufKomputer);
        giliranPemain();
        gotoxy(40, 55);
        printf("%d  ", tilesLeft());
        giliranKe++;
        cariKataDariPapan();
        gotoxy(40, 55);
        printf("%d  ", tilesLeft());
        giliranKe++;
    }
    tentukanPemenang();
    resetAll();
}

//MODUL HITUNG HURUF YANG TERSISA
//Menghitung huruf yang tersisa di kantung (tiles bag)
int tilesLeft() {
    int count = 0;
    for(int i = 0; i < 100; i++) {
        count += isalpha(blokScrabble[i]) ? 1 : 0;
    }
    return count;
}

//MODUL UNTUK MEMERIKSA KATA YANG MENEMPEL DENGAN KATA YANG BARU
//Kata yang dibentuk juga harus menempel dengan huruf yang telah ada, kecuali giliran pertama
int validasiSekitarKata() {
    int flag = 1, flag2 = 0;
    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 15; j++) {
            if(papan[i][j] != papan2[i][j]) {
                flag *= validBaris(i, j);
                flag *= validKolom(i, j);
                if((papan[i+1][j] != ' ' || papan[i-1][j] != ' ' || papan[i][j+1] != ' ' || papan[i][j-1] != ' ') || (tilesLeft() == 84 && strlen(tempHurufPemain) == 7)) {
                    flag2 = 1;
                }
            }
        }
    }
    //Membuat pemain harus memasukan kata pertama melewati bagian tengah papan
    if((tilesLeft() == 84 && !isalpha(papan2[7][7])) || (papan2[6][7] == ' ' && papan2[8][7] == ' ' && papan2[7][6] == ' ' && papan2[7][8] == ' ')) {
        flag2 = 0;
    }
    return flag * flag2;
}

//MODUL MEMERIKSA KATA SEJAJAR BARIS YANG MENEMPEL DENGAN KATA YANG BARU
int validBaris(int baris, int kolom) {
    char kata[15];
    while(isalpha(papan2[baris][kolom])) {
        --baris;
    }
    int i;
    for(i = baris + 1; isalpha(papan2[i][kolom]); i++) {
        kata[i-baris-1] = tolower(papan2[i][kolom]);
    }
    kata[i-baris-1] = '\0';
    if(strlen(kata) > 1) {
        if(strcmp(tampungKata[idx-1], kata) != 0 || idx == 0) {
            strcpy(tampungKata[idx], kata); idx++;
        }
        return cekKamus(kata);
    }
}

//MODUL MEMERIKSA KATA SEJAJAR KOLOM YANG MENEMPEL DENGAN KATA YANG BARU
int validKolom(int baris, int kolom) {
    char kata[15];
    while(isalpha(papan2[baris][kolom])) {
        --kolom;
    }
    int i;
    for(i = kolom + 1; isalpha(papan2[baris][i]); i++) {
        kata[i-kolom-1] = tolower(papan2[baris][i]);
    }
    kata[i-kolom-1] = '\0';
    if(strlen(kata) > 1) {
        if(strcmp(tampungKata[idx-1], kata) != 0 || idx == 0) {
            strcpy(tampungKata[idx], kata); idx++;
        }
        return cekKamus(kata);
    }
}

//MODUL MENENTUKAN SKOR KATA 
int tentukanSkor() {
    for(int i = 0; i < 15; i++) {
        for(int j = i+1; j < 15; j++) {
            if(strcmp(tampungKata[i], tampungKata[j]) == 0) {
                tampungKata[j][0] = '\0';
            }
        }
    }
    int skor = 0;
    for(int i = 0; i < 15; i++) {
        if(isalpha(tampungKata[i][0])) {
            for(int j = 0; isalpha(tampungKata[i][j]); j++) {
                skor += tentukanPoin(toupper(tampungKata[i][j]));
            }
        }
    }
    return skor;
}

//MODUL TUKAR HURUF
//Menukar semua huruf yang dimiliki
void tukarHuruf(char huruf[]) {
    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 100; j++) {
            if(blokScrabble[j] == ' ') {
                blokScrabble[j] = huruf[i];
                huruf[i] = ' ';
            }
        }
    }
    tambahHuruf(huruf);
}

//MODUL TAMBAH HURUF
//Menambahkan huruf ketika huruf telah digunakan/ditaruh ke papan
void tambahHuruf(char huruf[]) {
    int r = rand() % 100;   
    for(int i = 0; i < 7; i++) {
        if(huruf[i] == ' ') {
            do {
                r = rand() % 100;       //Mengambil huruf dari kantung (tiles bag) secara acak
                huruf[i] = blokScrabble[r];
            } while(blokScrabble[r] == ' ' && tilesLeft() > 0);
            blokScrabble[r] = ' ';
        }
    }
}

//MODUL VALIDASI KATA
int cekKamus(char kata[]) {
    FILE *file = fopen("D:\\kamus2.txt", "r");
    char penampungFile[26];
    long long count;
    //Membandingkan parameter kata dengan kata yang ada di kamus (194,000 kata)
    do {
        count = fscanf(file, "%s", penampungFile);
        if(strcmp(penampungFile, kata) == 0) {
            fclose(file); return 1;         //Ketika ada kata yang sama, maka akan dikembalikan nilai 1
        }
    } while(!feof(file));
    fclose(file);
    return 0;
}

//MODUL CEK APAKAH BARIS PAPAN BISA DIISI
int cekKosongKanan(int baris, int kolom, int hurufKe, int panjangKata) {
    int counter = 0;
    for(int i = kolom - 1; i >= kolom - hurufKe && i >= 0; i--) {
        if(papan[baris][i] != ' ') {
            break;
        }
        counter += papan[baris][i] == ' ' ? 1 : 0;
    }
    for(int i = kolom + 1; i < kolom + panjangKata - hurufKe && i <= 14; i++) {
        if(papan[baris][i] != ' ') {
            break;
        }
        counter += papan[baris][i] == ' ' ? 1 : 0;
    }
    if(counter >= panjangKata - 1) {
        return kolom - hurufKe;
    }
    return -1;
}

//MODUL CEK APAKAH KOLOM PAPAN BISA DIISI
int cekKosongBawah(int baris, int kolom, int hurufKe, int panjangKata) {
    int counter = 0;
    for(int i = baris - 1; i >= baris - hurufKe && i >= 0; i--) {
        if(papan[i][kolom] != ' ') {
            break;
        }
        counter += papan[i][kolom] == ' ' ? 1 : 0;
    }
    for(int i = baris + 1; i < baris + panjangKata - hurufKe && i <= 14; i++) {
        if(papan[i][kolom] != ' ') {
            break;
        }
        counter += papan[i][kolom] == ' ' ? 1 : 0;
    }
    if(counter >= panjangKata - 1) {
        return baris - hurufKe;
    }
    return -1;
}

//MODUL EKSEKUSI PENGISIAN PAPAN DENGAN KATA YANG TELAH DITENTUKAN KOMPUTER
//menampilkan huruf ke papan dan juga menyimpannya ke papan
void eksekusiPengisian(int brsPpn, int kolPpn, int letakAwal, int jmlHrf, int posHrf, char kata[], char orientasi) {
    //pengisian untuk horizontal atau ke kanan
    if(orientasi == 'k') {
        for(int i = 0, j = letakAwal; i < jmlHrf; i++, j++) {
            papan[brsPpn][j] = toupper(kata[i]);
            Sleep(900);
            taruhBlok(papan[brsPpn][j], brsPpn, j);
            for(int k = 0; k < 7; k++) {
                if(hurufKomputer[k] == toupper(kata[i]) && i != posHrf) {
                    hurufKomputer[k] = ' '; kata[i] = ' ';
                }
            }
        }
    }
    //pengisian untuk vertikal atau ke bawah
    else {
        for(int i = 0, j = letakAwal; i < jmlHrf; i++, j++) {
            papan[j][kolPpn] = toupper(kata[i]);
            Sleep(900);
            taruhBlok(papan[j][kolPpn], j, kolPpn);
            for(int k = 0; k < 7; k++) {
                if(hurufKomputer[k] == toupper(kata[i]) && i != posHrf) {
                    hurufKomputer[k] = ' '; kata[i] = ' ';
                }
            }
        }
    }
}

//Modul Pengisian papan oleh komputer
int komputerMengisiPapan2(char kata[], int baris, int kolom, char orientasi) {
    int berhasil = 0;
    //Untuk orientasi horizontal atau ke kanan
    if(orientasi == 'k') {
        int K = kolom;
        for(int i = 0; i < strlen(kata); i++, K++) {
            papan2[baris][K] = toupper(kata[i]);
        }
        //jika bisa diisi, maka akan dicek apakah kata di sekitarnya akan valid atau tidak
        if(validasiSekitarKata()) {
            eksekusiPengisian(baris, kolom, kolom, strlen(kata), kata[0], kata, 'k');
            skorKomputer += tentukanSkor();
            berhasil = 1;
        }else {
            for(int i = 0; i < 15; i++) {
                strcpy(papan2[i], papan[i]);
            }
        }

        //untuk orientasi vertikal atau ke bawah
    } else {
        int B = baris;
        for(int i = 0 ; i < strlen(kata); i++, B++) {
            papan2[B][kolom] = toupper(kata[i]);
        }
        if(validasiSekitarKata()) {
            eksekusiPengisian(baris, kolom, baris, strlen(kata), kata[0], kata, 'b');
            skorKomputer += tentukanSkor();
            berhasil = 1;
        }else {
            for(int i = 0; i < 15; i++) {
                strcpy(papan2[i], papan[i]);
            }
        }
    }
    //Membersihkan array tampungKata supaya bisa digunakan untuk giliran berikutnya
    for(int i = 0 ; i < 15; i++) {
        tampungKata[i][0] = '\0';
    }
    idx = 0;
    return berhasil;
}

//MODUL UNTUK MENGAMBIL KATA YANG TELAH ADA DI PAPAN
void cariKataDariPapan() {
    int selesai = 0;
    char kataDariPapan[15];
    //Mencari kata dari papan dengan orientasi horizontal atau ke kanan
    for(int k = 0; k < 15 && selesai == 0; k++) {
        for(int l = 0; l < 15 && selesai == 0; l++) {
            if(papan[k][l] != ' ') {
                int m;
                for(m = l; papan[k][m] != ' '; m++) {
                    kataDariPapan[m-l] = papan[k][m];
                }
                kataDariPapan[m-l] = '\0';
                //ketika kata telah diambil, maka akan dicari kata lain yang dapat dibentuk
                giliranKomputer(kataDariPapan, k, m-1, &selesai, 'k');
                kataDariPapan[0] = '\0';
                l = m;
            }
        }
    }
    //Jika tidak bisa, maka akan dicari kata yang orientasinya vertikal atau ke bawah
    if(selesai == 0) {
        for(int k = 0; k < 15 && selesai == 0; k++) {
            for(int l = 0; l < 15 && selesai == 0; l++) {
                if(papan[l][k] != ' ') {
                    int m;
                    for(m = l; papan[m][k] != ' '; m++) {
                        kataDariPapan[m-l] = papan[m][k];
                    }
                    kataDariPapan[m-l] = '\0';
                    giliranKomputer(kataDariPapan, m-1, k, &selesai, 'b');
                    kataDariPapan[0] = '\0';
                    l = m;
                }
            }
        }
    }
}

//MODUL PENENTUAN KATA OLEH KOMPUTER SERTA GILIRAN KOMPUTER
void giliranKomputer(char kataDariPapan[], int baris, int kolom, int *selesai, char orientasi) {
        char *temp = (char*)malloc(sizeof(char)*7), penampungFile[26], sisaKamus[26];
        FILE *file;
        int bisa, berhasil;
        switch(kesulitan) {
            case 1 : file = fopen("D:\\1000word.txt", "r");
            case 2 : file = fopen("D:\\4000word.txt", "r");
            case 3 : file = fopen("D:\\10000word.txt", "r");
        }
        long long count, hurufGaada;

        do {
            count = fscanf(file, "%s", penampungFile);
            strcpy(temp, hurufKomputer);
            bisa = 1;
            for(int n = 0; n < strlen(kataDariPapan); n++) {
                if(kataDariPapan[n] != toupper(penampungFile[n])) {
                    bisa = 0; break;
                }
            }

            if(bisa == 1) {
                int p, o;
                for(o = strlen(kataDariPapan)-1, p = 0; o < strlen(penampungFile); o++, p++) {
                    sisaKamus[p] = toupper(penampungFile[o]);
                }
                sisaKamus[p] = '\0';
                //Menentukan apakah huruf-huruf dari kata dimiliki oleh komputer
                for(int i = 1; i < strlen(sisaKamus); i++) {
                    hurufGaada = 1; 
                    for(int j = 0; j < 7; j++) {
                        if(toupper(sisaKamus[i]) == temp[j]) {
                            temp[j] = ' '; hurufGaada = 0; break;
                        }
                    }
                    if(hurufGaada == 1) {
                        break;
                    }
                }
            }

            //Jika semua huruf ada, maka akan dicari tempat yang tepat untuk menaruh kata tersebut
            if(hurufGaada == 0) {
                berhasil = komputerMengisiPapan2(sisaKamus, baris, kolom, orientasi); 
                gotoxy(85, 52);
                printf("%d", skorKomputer);
                gotoxy(x, y);
                fclose(file); break;
            }
        } while(!feof(file));

        if(berhasil == 1) {
            *selesai = 1;
        }
    if(tilesLeft() == 0 && hurufGaada == 1) {
        lewati += 1;
    }
    fclose(file);
    tambahHuruf(hurufKomputer);
}

//VARIABEL UNTUK PEMBATASAN WAKTU
time_t second;
long long awalSecond, secondSebelum;

//MODUL UNTUK GILIRAN PEMAIN
void giliranPemain() {
    int selesai = 0;
    lewati = 0;
    barisKolom.B = -1;
    second = time(NULL);
    awalSecond = second;
    strcpy(tempHurufPemain, hurufPemain);
    tampilHurufPemain();
    while(second-awalSecond < timer && selesai == 0 && akhir == 0) {
        for(int i = 0 ; i < 15; i++) {
            tampungKata[i][0] = '\0';
        }
        idx = 0;
        isiPapanPemain(&x, &y);

        //Menentukan skor pemain ketika kata yang dimainkan valid
        if(validasiSekitarKata()) {
            gotoxy(70, 55);
            printf("\033[42m VALID WORD \033[0m      \n");
            skorPemain += tentukanSkor();
            gotoxy(18, 52);
            printf("%d", skorPemain);
            selesai = 1;
            strcpy(hurufPemain, tempHurufPemain);
            for(int i = 0; i < 15; i++) {
                strcpy(papan[i], papan2[i]);
            }
        } else {
            gotoxy(70, 55);
            printf("\033[41m NOT A VALID WORD \033[0m\n");
        }
        
    }

    //Jika waktu habis dan kata tidak valid, maka papan dibersihkan
    if(!validasiSekitarKata()) {
            for(int i = 0; i < 15; i++) {
                strcpy(papan2[i], papan[i]);
            }
            strcpy(tempHurufPemain, hurufPemain);
            bersihkanPapan();
    }
    tambahHuruf(hurufPemain);
    strcpy(tempHurufPemain, hurufPemain);
    tampilHurufPemain();
    Sleep(1000);
    gotoxy(70, 55);
    printf("                          ");

    //Membersihkan array tampungKata supaya bisa digunakan untuk giliran berikutnya
    for(int i = 0 ; i < 15; i++) {
        tampungKata[i][0] = '\0';
    }
    idx = 0;
    gotoxy(x, y);
}


//prosedur untuk menggerakan kursor
void isiPapanPemain(int* x, int* y) {
    char get;
    do {
        while(!kbhit() && second-awalSecond < timer) {      //Algoritma untuk timer
            second = time(NULL);
            if(second != secondSebelum) {
                gotoxy(21, 55);
                secondSebelum = second;
                printf("%ld ", timer-(second-awalSecond));
            }
            gotoxy(*x, *y);
        }
        get = getch();
        //kondisi untuk menggerakan kursor dengan tombol panah
        if(get == 75 && *x > 10) {              //Gerak kursor ke kiri
            *x -=6; K -=1;
        } else if(get == 72 && *y > 6) {        //Gerak kursor ke atas
            *y -=3; B -=1;
        } else if(get == 77 && *x < 90) {       //Gerak kursor ke kanan
            *x +=6; K +=1;
        } else if(get == 80 && *y <= 45) {      //Gerak kursor ke bawah
            *y +=3; B +=1;

            //Kondisi untuk menaruh kata ke papan
        } else if(isalpha(get) && !isalpha(papan2[B][K])&& get != 'K' && get != 'H' && get != 'M' && get != 'P' && periksaHuruf(get) >= 0) {
            if((hurufPertama() == 0 || barisKolom.B == B || K == barisKolom.K) && (hurufPertama() == 0 || (isalpha(papan2[B+1][K]) || isalpha(papan2[B-1][K]) || isalpha(papan2[B][K+1]) || isalpha(papan2[B][K-1])) || (isalpha(papan[B+1][K]) || isalpha(papan[B-1][K]) || isalpha(papan[B][K+1]) || isalpha(papan[B][K-1])))) {
                putchar(toupper(get));                      //Menaruh blok ke papan ketika huruf dipunyai pemain
                papan2[B][K] = toupper(get);
                taruhBlok(papan2[B][K], B, K);
                tempHurufPemain[periksaHuruf(get)] = ' ';
                tampilHurufPemain();
                if(hurufPertama() == 1) {
                    barisKolom.B = B; barisKolom.K = K;
                }
            }
        } else if(get == 8 && papan[B][K] == ' ') {     //Menghapus blok dari papan ketika user menekan BACKSPACE
            for(int i = 0; i < 7; i++) {
                if(tempHurufPemain[i] == ' ') {
                    tempHurufPemain[i] = papan2[B][K]; break;
                }
            }
            printf(" "); papan2[B][K] = ' ';
            gotoxy(*x + 1, *y + 1);
            printf("  ");
            tampilHurufPemain();
            gotoxy(70, 55);
            printf("                          ");

            //Shortcut fitur permainan
        } else if(get == '1') {
            tukarHuruf(hurufPemain);
            awalSecond -= 100;
        } else if(get == '2') {
            lewati += 1;
            awalSecond -= 100;
        } else if(get == '3') {
            resetAll();
            mulaiPermainan();
        } else if(get == '4') {
            resetAll();
            mainMenu();
        } else if(get == '5') {
            akhir = 1;
        }
    } while(get != 13 && second-awalSecond < timer && akhir == 0);    //Keluar ketika user menekan ENTER atau waktu sudah habis
}

//MODUL PEMERIKSAAN INPUTAN HURUF PERTAMA
int hurufPertama() {
    int count = 0, i, j; 
    for(i = 0; i < 15 && count <= 2; i++) {
        for(j = 0; j < 15 && count <= 2; j++) {
            count += papan[i][j] != papan2[i][j] ? 1 : 0;
        }
    }
    return count;
}

//MODUL PEMERIKSAAN APAKAH HURUF DIMILIKI PEMAIN
int periksaHuruf(char huruf) {
    for(int i = 0; i < 7; i++) {
        if(tempHurufPemain[i] == toupper(huruf)) {
            return i;           //Mengembalikan 1 jika huruf dimiliki
        }
    }
    return -1;       //Mengembalikan -1 jika huruf tidak dimiliki
}

//MODUL UNTUK MEMBERSIHKAN BLOK DARI PAPAN
void bersihkanPapan() {
    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 15; j++) {
            if(papan[i][j] == ' ') {
                gotoxy(j*6+10, i*3+5);
                printf(" ");
                gotoxy(j*6+11, i*3+6);
                printf("  ");
            }
        }
    }
    gotoxy(x, y);
}

//MODUL UNTUK MENAMPILKAN HURUF YANG DIMILIKI PEMAIN
void tampilHurufPemain() {
    for(int i = 0; i < 7; i++) {
        gotoxy(34+i*6, 51);
        putchar(tempHurufPemain[i]);
        gotoxy(35+i*6, 52);
        if(tempHurufPemain[i] == ' ') {
            printf("  ");
        } else {
            if(tentukanPoin(tempHurufPemain[i]) < 10) {
                printf("%d ", tentukanPoin(tempHurufPemain[i]));
            } else {
                printf("%d", tentukanPoin(tempHurufPemain[i]));
            }
        }
    }
    gotoxy(x, y);
}

//MODUL UNTUK MENARUH BLOK SCRABBLE KE PAPAN
void taruhBlok(char blok, int baris, int kolom) {
    gotoxy(kolom*6+10, baris*3+5);
    putchar(blok);
    gotoxy(kolom*6+11, baris*3+6);
    printf("%d", tentukanPoin(blok));
}

//MODUL UNTUK MENENTUKAN POIN HURUF
int tentukanPoin(char huruf) {
    int poin;
    if(huruf == 'A' || huruf == 'E' || huruf == 'I' || huruf == 'L' || huruf == 'N' || huruf == 'O' || huruf == 'R' || huruf == 'S' || huruf == 'T' || huruf == 'U') {
        poin = 1;
    } else if(huruf == 'D' || huruf == 'G') {
        poin = 2;
    } else if(huruf == 'B' || huruf == 'C' || huruf == 'M' || huruf == 'P' ) {
        poin = 3;
    } else if(huruf == 'F' || huruf == 'H' || huruf == 'V' || huruf == 'W' || huruf == 'Y') {
        poin = 4;
    } else if(huruf == 'K') {
        poin = 5;
    } else if(huruf == 'J' || huruf == 'X') {
        poin = 8;
    } else if(huruf == 'Q' || huruf == 'Z') {
        poin = 10;
    }
    return poin;
}

//MODUL PINDAH POSISI KURSOR
void gotoxy(int x, int y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//MODUL INTERFACE PILIH MENU
void interfaceSelectMenu(int x, int y) {
    char select[2][11] = {
        {218, 196, 196, 196, 196, 196, 196, 196, 196, 191},
        {192, 196, 196, 196, 196, 196, 196, 196, 196, 217}
    };
    for(int i = 0; i < 4; i++) {
        gotoxy(5, i*2+4);
        printf("               ");
        if(i < 3) {
            gotoxy(10, i*2+5);
            printf(" ");
            gotoxy(19, i*2+5);
            printf(" ");
        }
    }
    gotoxy(10, y);
    puts(select[0]);
    gotoxy(10,y+2);
    puts(select[1]);
    gotoxy(10, y+1); printf("%c", 179);
    gotoxy(19, y+1); printf("%c", 179);
    gotoxy(x, y+1);
}

//MODUL MAIN MENU
void mainMenu() {

    //INTERFACE MAIN MENU
    system("cls");
    SMALL_RECT windowSize = {0 , 0 , 29 , 13};
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
    int x = 0, y = 4;

    gotoxy(4, 1);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191);
    gotoxy(4, 2); printf("%c", 179); gotoxy(25, 2); printf("%c", 179);
    gotoxy(4, 3); 
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 180);
    for(int i = 0; i < 7; i++) {
        gotoxy(4, 4+i); printf("%c", 179); gotoxy(25, 4+i); printf("%c", 179);
    }   
    gotoxy(4,11);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217);

    gotoxy(11, 2);
    printf("SSCRABBLE");
    gotoxy(13, 5);
    printf("PLAY");
    gotoxy(13, 7);
    printf("HELP");
    gotoxy(13, 9);
    printf("EXIT\n\n\n");

    //ALGORITMA PEMILIHAN MENU
    char get;
    do {
        gotoxy(x, y);
        interfaceSelectMenu(x, y);
        get = getch();
        if(get == 72 && y > 4) {
            y -=2;
        } else if(get == 80 && y < 8) {
            y +=2;
        }
    } while (get != 13);
    gotoxy(10, 12);
    if(y == 4) {        //Memanggil modul mulaiPermainan() ketika kursor berada pada tulisan PLAY
        gotoxy(13, 5);
        printf("EASY");
        gotoxy(12, 7);
        printf("MEDIUM");
        gotoxy(13, 9);
        printf("HARD");

        //Algoritma pemilihan tingkat kesulitan
        do {
            gotoxy(x, y);
            interfaceSelectMenu(x, y);
            get = getch();
            if(get == 72 && y > 4) {
                y -=2;
            } else if(get == 80 && y < 8) {
                y +=2;
            }
        } while (get != 13);
        gotoxy(10, 12);
        if(y == 4) {        //Mengubah tingkat kesulitan menjadi 1 dan batas waktu menjadi 90 detik
            kesulitan = 1;
            timer = 90;
        } else if(y == 6) {  //Mengubah tingkat kesulitan menjadi 2 dan batas waktu menjadi 60 detik
            kesulitan = 2;
            timer = 60;
        } else if(y == 8 ) {    //Mengubah tingkat kesulitan menjadi 3 dan batas waktu menjadi 45 detik
            kesulitan = 3;
            timer = 45;
        }
        system("cls");
        mulaiPermainan();
    }else if(y == 6) {  //Memanggil modul help() ketika kursor berada pada tulisan HELP
        help();
        if(getch() != '\0') {
            mainMenu();
        }
    } else if(y == 8 ) {    //Keluar permainan ketika kursor berada pada tulisan EXIT
        system("cls");
        //Mengubah ukuran console/terminal
        SMALL_RECT windowSize2 = {0 , 0 , 94, 6};
        SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize2);
        printf("\n\n\t\t\t\t\tSELAMAT TINGGAL\n\n\t\t\t\t\t  TERIMAKASIH\n");
        getch();
        exit(1);
    }
}

//MODUL MEMUNCULKAN HELP
void help() {
    //Mengubah ukuran console/terminal
    SMALL_RECT windowSize2 = {0 , 0 , 104 , 34};
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize2);
    system("cls");
    FILE *file = fopen("D:\\help.txt", "r");
    char tampung[2000];
    long long count;
        count = fread(tampung, sizeof(char), 2000, file);
        tampung[count] = '\0';
        puts(tampung);
    fclose(file);
}

//MODUL UNTUK MEMERIKSA APAKAH AKHIR PERMAINAN TERCAPAI
int akhirPermainan() {
    if(lewati == 2) {
        return 1;
    }
    int end = 1;
    end = !tilesLeft();
    for(int i = 0; i < 7; i++) {
        if(isalpha(hurufPemain[i]) || isalpha(hurufKomputer[i])) {
            end = 0;
        }
    }
    return end;
}

//MODUL MENENTUKAN PEMENANG
void tentukanPemenang() {
    if(skorPemain > skorKomputer) {
        gotoxy(70, 55);
        printf("\033[42m YOU WIN \033[0m\n");
    } else if(skorPemain < skorKomputer) {
        gotoxy(70, 55);
        printf("\033[41m YOU LOSE \033[0m\n");
    } else {
        gotoxy(70, 55);
        printf("\033[44m TIE \033[0m\n");
    }
}

//MODUL UNTUK RESTART (RESET SEMUA VARIABEL)
void resetAll() {
    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 15; j++) {
            papan[i][j] = ' ';
        }
        strcpy(papan2[i], papan[i]);
        if(i < 7) {
            hurufKomputer[i] = ' ';
        }
    }
    strcpy(hurufPemain, hurufKomputer);
    strcpy(tempHurufPemain, hurufPemain);
    skorPemain = 0; skorKomputer = 0;
    giliranKe = 1;
    akhir = 0;
    strcpy(blokScrabble, blokScrabble2);
    x = 10; y = 5; B = 0; K = 0;
}

//MODUL PRINT PAPAN SCRABBLE (INTERFACE KETIKA DI DALAM PERMAINAN)
void printPapan() {
    system("cls");
    char headerPapan[3][91] = {
        {218, 196, 196,196,196,196,196, 196,196,196,196, 196, 196, 196,196,196,196, 196, 196, 196, 196,196,196,196,196, 196,196,196,196, 196, 196, 196,196,196,196, 196, 196, 196, 196,196,196,196,196, 196,196,196,196, 196, 196, 196,196,196,196, 196, 196, 196, 196,196,196,196,196, 196,196,196,196, 196, 196, 196,196,196,196, 196, 196, 196, 196,196,196,196,196, 196,196,196,196, 196, 196, 196,196,196,196, 196, 191},
        {179, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'S', 'S', 'C', 'R', 'A', 'B', 'B', 'L', 'E', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 179},
        {192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217}
    };

    char papan[46][91] = {
        {218, 196, 196,196,196,196,194, 196,196,196,196, 196, 194, 196,196,196,196, 196, 194, 196, 196,196,196,196,194, 196,196,196,196, 196, 194, 196,196,196,196, 196, 194, 196, 196,196,196,196,194, 196,196,196,196, 196, 194, 196,196,196,196, 196, 194, 196, 196,196,196,196,194, 196,196,196,196, 196, 194, 196,196,196,196, 196, 194, 196, 196,196,196,196,194, 196,196,196,196, 196, 194, 196,196,196,196, 196, 191},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {195, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 180},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {195, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 180},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {195, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 180},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {195, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 180},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {195, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 180},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {195, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 180},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {195, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 180},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {195, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 180},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {195, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 180},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {195, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 180},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {195, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 180},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {195, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 180},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {195, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 180},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {195, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 180},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179},
        {192, 196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 217}
    };

    char blokHurufPemain[4][91] = {
        {218, 196, 196,196,196,196,196, 196,196,196,196, 196, 196, 196,196,196,196, 196, 196, 196, 196,196,196,191,218, 196,196,196,196, 196, 194, 196,196,196,196, 196, 194, 196, 196,196,196,196,194, 196,196,196,196, 196, 194, 196,196,196,196, 196, 194, 196, 196,196,196,196,194, 196,196,196,196, 196, 191, 218,196,196,196, 196, 196, 196, 196,196,196,196,196, 196,196,196,196, 196, 196, 196,196,196,196, 196, 191},
        {179, ' ', ' ', ' ', ' ', ' ', ' ', 'Y', 'o', 'u', 'r', ' ', 'S', 'c', 'o', 'r', 'e', ' ', ' ' , ' ', ' ', ' ', ' ', 179, 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, 179, ' ', ' ', ' ', 'C', 'o', 'm', 'p', 'u', 't', 'e', 'r', '\'', 's', ' ', 'S', 'c', 'o', 'r', 'e', ' ', ' ', ' ', 179},
        {179, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' , ' ', ' ', ' ', ' ', 179, 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, ' ', ' ', ' ', ' ', ' ', 179, 179, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 179},
        {192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217, 192, 196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 217, 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217}
    };

    char footerPapan[3][91] = {
        {218, 196, 196,196,196,196,196, 196,196,196,196, 196, 196, 196,196,196,196, 196, 196, 196, 196,196,196,196,196, 196,196,196,196, 196, 196, 196,196,196,196, 196, 196, 196, 196,196,196,196,196, 196,196,196,196, 196, 196, 196,196,196,196, 196, 196, 196, 196,196,196,196,196, 196,196,196,196, 196, 196, 196,196,196,196, 196, 196, 196, 196,196,196,196,196, 196,196,196,196, 196, 196, 196,196,196,196, 196, 191},
        {179, ' ', 'T', 'i', 'm', 'e', ' ', 'L', 'e', 'f', 't', ' ', ':', ' ', ' ', ' ', ' ', ' ', 'T', 'i', 'l', 'e', 's', ' ', 'I', 'n', ' ', 'B', 'a', 'g', ' ', ':', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 179},
        {192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217}
    };

    //Print header papan
    for(int i = 0; i < 3; i++) {
        gotoxy(7, i+1);
        for(int j = 0; j < 91; j++) {
            printf("%c", headerPapan[i][j]);
        }
        printf("\n");
    }

    //Papan scrabble
    for(int i = 0; i < 46; i++) {
        gotoxy(7, 4+i);
        for(int j = 0; j < 91; j++) {
            printf("%c", papan[i][j]);
        }
        printf("\n");
    }

    //Print rak huruf pemain
    for(int i = 0; i < 4; i++) {
        gotoxy(7, 50+i);
        for(int j = 0; j < 91; j++) {
            printf("%c", blokHurufPemain[i][j]);
        }
        printf("\n");
    }
    
    //Print footer papan
    for(int i = 0; i < 3; i++) {
        gotoxy(7, 54+i);
        for(int j = 0; j < 91; j++) {
            printf("%c", footerPapan[i][j]);
        }
    }
    gotoxy(x, y);
}
