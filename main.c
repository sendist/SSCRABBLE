#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//PROTOTYPE MODUL
void interfaceSelectMenu(int x, int y);
void mainMenu();
int cekKamus(char kata[]);
void komputerMengisiPapan(char kata[]);
void giliranKomputer();
int cekKosongKanan(int baris, int kolom, int hurufKe, int panjangKata);
int cekKosongBawah(int baris, int kolom, int hurufKe, int panjangKata);
void tambahHuruf(char huruf[]);
void gotoxy(int x, int y);
void isiPapanPemain(int* x, int* y);
void printPapan();
int tentukanPoin(char huruf);
void taruhBlok(char blok, int baris, int kolom);
void tukarHuruf(char huruf[]);
int validasiSekitarKata();
int validBaris(int baris, int kolom);
int validKolom(int baris, int kolom);
void eksekusiPengisian(int brsPpn, int kolPpn, int letakAwal, int jmlHrf, int posHrf, char kata[], char orientasi);
void giliranPemain();
void bersihkanPapan();
int periksaHuruf(char huruf);
void tampilHurufPemain();
void mulaiPermainan();
int tilesLeft();

//PROTOTYPE SEMENTARA
void print(char arr[15][15]);

//VARIABEL GLOBAL

char blokScrabble[100] = "AAAAAAAAABBCCDDDDEEEEEEEEEEEEFFGGGHHIIIIIIIIIJKLLLLMMNNNNNNOOOOOOOOPPQRRRRRRSSSSTTTTTTUUUUVVWWXYYZ  ";

char hurufKomputer[7] = "       ";
char hurufPemain[7] = "       ";
char tempHurufPemain[7];
int skorPemain = 0;
int skorKomputer = 0;
int kesulitan;
int timer;

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

int giliranKe = 1;
int batas = 10;
int batas2 = 10;

char tampungKata[15][15];
int idx = 0;

int main () {
    mainMenu();
    return 0;
}

//MODUL MULAI PERMAINAN
void mulaiPermainan() {
    SMALL_RECT windowSize2 = {0 , 0 , 104 , 57};
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize2);
    srand(time(NULL));
    
    printPapan();
    tambahHuruf(hurufKomputer);
    tambahHuruf(hurufPemain);
    tilesLeft();
    for(int i = 0; i < 10; i++) {
        tambahHuruf(hurufKomputer);
        tambahHuruf(hurufPemain);
        //gotoxy(100, 1+i);
        //puts(hurufKomputer);
        //gotoxy(110, 1+i);
        //puts(hurufPemain);
        gotoxy(x, y);
        tukarHuruf(hurufKomputer);
        giliranPemain();
        tilesLeft();
        giliranKe++;
        giliranKomputer();
        tilesLeft();
        giliranKe++;
    }
}

//prosedur print papan (((SEMENTARA)))
void print(char arr[15][15]) {
   for (int i = 0; i < 15; ++i ) {
       for (int j = 0; j < 15; ++j) {
           printf("%c", arr[i][j]);
       }
       printf("\n");
   }
}

//MODUL HITUNG HURUF YANG TERSISA
int tilesLeft() {
    int count = 0;
    for(int i = 0; i < 100; i++) {
        count += isalpha(blokScrabble[i]) ? 1 : 0;
    }
    gotoxy(40, 55);
    printf("%d  ", count);
    gotoxy(x, y);
    return count;
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

//MODUL MEMERIKSA KATA YANG MENEMPEL DENGAN KATA YANG BARU
int validasiSekitarKata() {
    int flag = 1, flag2 = 0;
    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 15; j++) {
            if(papan[i][j] != papan2[i][j]) {
                flag *= validBaris(i, j);
                flag *= validKolom(i, j);
                if((papan[i+1][j] != ' ' || papan[i-1][j] != ' ' || papan[i][j+1] != ' ' || papan[i][j-1] != ' ') || giliranKe == 1) {
                    flag2 = 1;
                }
            }
        }
    }
    return flag * flag2;
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

//MODUL ACAK HURUF
void tambahHuruf(char huruf[]) {
    int r = rand() % 100;
    for(int i = 0; i < 7; i++) {
        if(huruf[i] == ' ') {
            do {
                r = rand() % 100;
                huruf[i] = blokScrabble[r];
            } while(blokScrabble[r] == ' ');
            blokScrabble[r] = ' ';
        }
    }
}

//MODUL VALIDASI KATA
int cekKamus(char kata[]) {
    FILE *file = fopen("D:\\kamus2.txt", "r");
    char penampungFile[26];
    long long count;
    do {
        count = fscanf(file, "%s", penampungFile);
        if(strcmp(penampungFile, kata) == 0) {
            fclose(file); return 1;
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

//MODUL EKSEKUSI PENGISIAN
void eksekusiPengisian(int brsPpn, int kolPpn, int letakAwal, int jmlHrf, int posHrf, char kata[], char orientasi) {
    if(orientasi == 'k') {
        for(int i = 0, j = letakAwal; i < jmlHrf; i++, j++) {
            papan[brsPpn][j] = toupper(kata[i]);
            taruhBlok(papan[brsPpn][j], brsPpn, j);
            for(int k = 0; k < 7; k++) {
                if(hurufKomputer[k] == toupper(kata[i]) && i != posHrf) {
                    hurufKomputer[k] = ' '; kata[i] = ' ';
                }
            }
        }
    }
    else {
        for(int i = 0, j = letakAwal; i < jmlHrf; i++, j++) {
            papan[j][kolPpn] = toupper(kata[i]);
            taruhBlok(papan[j][kolPpn], j, kolPpn);
            for(int k = 0; k < 7; k++) {
                if(hurufKomputer[k] == toupper(kata[i]) && i != posHrf) {
                    hurufKomputer[k] = ' '; kata[i] = ' ';
                }
            }
        }
    }
}

//MODUL PENGISIAN PAPAN OLEH KOMPUTER
void komputerMengisiPapan(char kata[]) {
    int letakAwal, bisa = 0;
    for(int i = 0; i < strlen(kata); i++) {
        for(int j = 0; j < 15; j++) {
            for(int k = 0; k < 15; k++) {
                if(papan[j][k] == toupper(kata[i])) {
                    letakAwal = cekKosongKanan(j, k, i, strlen(kata));
                    if(letakAwal >= 0) {
                        bisa = 1;
                        for(int l = 0, m = letakAwal; l < strlen(kata); l++, m++) {
                            papan2[j][m] = toupper(kata[l]);
                        }
                        if(validasiSekitarKata()) {
                            eksekusiPengisian(j, k, letakAwal, strlen(kata), i, kata, 'k');
                            skorKomputer += tentukanSkor();
                        }else {
                            for(int i = 0; i < 15; i++) {
                                strcpy(papan2[i], papan[i]);
                            }
                        }
                    } else {
                        letakAwal = cekKosongBawah(j, k, i, strlen(kata));
                        if(letakAwal >= 0) {
                            bisa = 1;
                            for(int l = 0, m = letakAwal; l < strlen(kata); l++, m++) {
                                papan2[m][k] = toupper(kata[l]);
                            }
                            if(validasiSekitarKata()) {
                                eksekusiPengisian(j, k, letakAwal, strlen(kata), i, kata, 'b');
                                skorKomputer += tentukanSkor();
                            } else {
                                for(int i = 0; i < 15; i++) {
                                    strcpy(papan2[i], papan[i]);
                                }
                            }
                        }
                    }
                }
                if(bisa == 1) break;
            }
            if(bisa == 1) break;
        }
        if(bisa == 1) break;
    }
    //Membersihkan array tampungKata supaya bisa digunakan untuk giliran berikutnya
    for(int i = 0 ; i < 15; i++) {
        tampungKata[i][0] = '\0';
    }
    idx = 0;
}

//MODUL PENENTUAN KATA OLEH KOMPUTER
void giliranKomputer() {
    Sleep(5000);
    char *temp = (char*)malloc(sizeof(char)*7), penampungFile[26];
    FILE *file = fopen("D:\\4000word.txt", "r");
    long long count, hurufGaada;
    do {
        count = fscanf(file, "%s", penampungFile);
        strcpy(temp, hurufKomputer);
        for(int i = 0; i < strlen(penampungFile); i++) {
            hurufGaada = 1; 
            for(int j = 0; j < 7; j++) {
                if(toupper(penampungFile[i]) == temp[j]) {
                    temp[j] = ' '; hurufGaada = 0; break;
                }
            }
            if(hurufGaada == 1) {
                break;
            }
        }
        if(hurufGaada == 0) {
            komputerMengisiPapan(penampungFile); 
            gotoxy(85, 52);
            printf("%d", skorKomputer);
            fclose(file); break;
        }
    } while(!feof(file));
    fclose(file);
}

//VARIABEL UNTUK PEMBATASAN WAKTU
time_t second;
long long awalSecond, secondSebelum;

//MODUL UNTUK GILIRAN PEMAIN
void giliranPemain() {
    int selesai = 0;
    second = time(NULL);
    awalSecond = second;
    strcpy(tempHurufPemain, hurufPemain);
    tampilHurufPemain();
    while(second-awalSecond < timer && selesai == 0) {
        isiPapanPemain(&x, &y);
        if(validasiSekitarKata()) {
            skorPemain += tentukanSkor();
            gotoxy(18, 52);
            printf("%d", skorPemain);
            selesai = 1;
            strcpy(hurufPemain, tempHurufPemain);
            for(int i = 0; i < 15; i++) {
                strcpy(papan[i], papan2[i]);
            }
        }
        
    }
    if(!validasiSekitarKata()) {
            for(int i = 0; i < 15; i++) {
                strcpy(papan2[i], papan[i]);
            }
            strcpy(tempHurufPemain, hurufPemain);
            bersihkanPapan();
    }
    tampilHurufPemain();
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
        while(!kbhit() && second-awalSecond < timer) {
            second = time(NULL);
            if(second != secondSebelum) {
                gotoxy(21, 55);
                secondSebelum = second;
                printf("%ld ", timer-(second-awalSecond));
            }
            gotoxy(*x, *y);
        }
        get = getch();
        if(get == 75 && *x > 10) {
            *x -=6; K -=1;
        } else if(get == 72 && *y > 6) {
            *y -=3; B -=1;
        } else if(get == 77 && *x < 90) {
            *x +=6; K +=1;
        } else if(get == 80 && *y <= 45) {
            *y +=3; B +=1;
        } else if(isalpha(get) && !isalpha(papan2[B][K])&& get != 'K' && get != 'H' && get != 'M' && get != 'P' && periksaHuruf(get) == 1) {
            putchar(toupper(get));
            papan2[B][K] = toupper(get);
            taruhBlok(papan2[B][K], B, K);
            tampilHurufPemain();
        } else if(get == 8 && papan[B][K] == ' ') {
            for(int i = 0; i < 7; i++) {
                if(tempHurufPemain[i] == ' ') {
                    tempHurufPemain[i] = papan2[B][K]; break;
                }
            }
            printf(" "); papan2[B][K] = ' ';
            gotoxy(*x + 1, *y + 1);
            printf("  ");
            tampilHurufPemain();
        }
    } while(get != 13 && second-awalSecond < timer);
}

//MODUL PEMERIKSAAN HURUF DIMILIKI PEMAIN
int periksaHuruf(char huruf) {
    for(int i = 0; i < 7; i++) {
        if(tempHurufPemain[i] == toupper(huruf)) {
            tempHurufPemain[i] = ' ';
            return 1;           //Mengembalikan 1 jika huruf dimiliki
        }
    }
    return 0;       //Mengembalikan 0 jika huruf tidak dimiliki
}

//MODUL BERSIHKAN PAPAN
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
            printf("%d", tentukanPoin(tempHurufPemain[i]));
        }
    }
}

//MODUL UNTUK MENARUH BLOK SCRABBLE
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

//MODUL INTERFACE PILIH MENu
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
            kesulitan = 1;
            timer = 90;
        } else if(y == 6) {  //Memanggil modul help() ketika kursor berada pada tulisan HELP
            kesulitan = 2;
            timer = 60;
        } else if(y == 8 ) {    //Keluar permainan ketika kursor berada pada tulisan EXIT
            kesulitan = 3;
            timer = 45;
        }
        system("cls");
        mulaiPermainan();
    }else if(y == 6) {  //Memanggil modul help() ketika kursor berada pada tulisan HELP
        system("cls");
        printf("HELP");
    } else if(y == 8 ) {    //Keluar permainan ketika kursor berada pada tulisan EXIT
        system("cls");
        printf("BYE - BYE\n\n\n\n");
        exit(1);
    }
}



//MODUL PRINT PAPAN SCRABBLE
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
    for(int i = 0; i < 3; i++) {
        gotoxy(7, i+1);
        for(int j = 0; j < 91; j++) {
            printf("%c", headerPapan[i][j]);
        }
        printf("\n");
    }

    for(int i = 0; i < 46; i++) {
        gotoxy(7, 4+i);
        for(int j = 0; j < 91; j++) {
            printf("%c", papan[i][j]);
        }
        printf("\n");
    }

    for(int i = 0; i < 4; i++) {
        gotoxy(7, 50+i);
        for(int j = 0; j < 91; j++) {
            printf("%c", blokHurufPemain[i][j]);
        }
        printf("\n");
    }

    for(int i = 0; i < 3; i++) {
        gotoxy(7, 54+i);
        for(int j = 0; j < 91; j++) {
            printf("%c", footerPapan[i][j]);
        }
    }
    gotoxy(x, y);
}
