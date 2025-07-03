#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define MAKS_MK 10
#define MAKS_KEGIATAN 50
#define MAKS_JADWAL 50
#define MAKS_TRANSKRIP 9
#define MAKS_STRING 100
#define MAKS_KODE 15
#define MAKS_PASSWORD 20
#define MAKS_NIM 15

typedef struct {
    char kode[MAKS_KODE];
    char nama[MAKS_STRING];
    int sksA;
    int sksB;
    char keterangan[MAKS_STRING];
} MataKuliah;

typedef struct {
    char kode[MAKS_KODE];
    char nama[MAKS_STRING];
    int sks;
    char nilai;
    float ak;
} HasilStudi;

typedef struct {
    char namaKegiatan[MAKS_STRING];
    int poin;
} KegiatanKeaktifan;

typedef struct {
    KegiatanKeaktifan daftarKegiatan[MAKS_KEGIATAN];
    int jumlahKegiatan;
    int totalPoin;
} KeaktifanMahasiswa;

typedef struct {
    char kode[MAKS_KODE];
    char nama[MAKS_STRING];
    char hari[15];
    char jam[15];
} JadwalKuliah;

typedef struct {
    int no;
    char kode[MAKS_KODE];
    char nama[MAKS_STRING];
    int sks;
    char nilai;
    int ak;
    char tahunAmbil[20];
} Transkrip;

int sudahRegistrasiUlang = 0;
int jumlahMK = 0;
MataKuliah mk[MAKS_MK];
HasilStudi hasil[MAKS_MK];
KeaktifanMahasiswa keaktifan = {.jumlahKegiatan = 0, .totalPoin = 0};
int jumlahHasil = 0;
JadwalKuliah jadwal[MAKS_JADWAL];
int jumlahJadwal = 0;

Transkrip transkrip[MAKS_TRANSKRIP] = {
    {1, "TC512D", "PENGANTAR TEKNOLOGI INFORMASI", 3, 'A', 12, "2024-2025/1"},
    {2, "TC511E", "MATEMATIKA DISKRIT", 3, 'A', 12, "2024-2025/1"},
    {3, "TC513B", "DASAR-DASAR PEMROGRAMAN", 3, 'A', 12, "2024-2025/1"},
    {4, "TC514D", "BAHASA INGGRIS", 3, 'A', 12, "2024-2025/1"},
    {5, "TC515G", "SISTEM BASIS DATA", 3, 'A', 12, "2024-2025/1"},
    {6, "MU114G", "PANCASILA", 2, 'A', 8, "2024-2025/2"},
    {7, "MU116C", "BAHASA INDONESIA", 2, 'A', 8, "2024-2025/2"},
    {8, "MU117E", "PENDIDIKAN AGAMA (KRISTEN)", 2, 'A', 8, "2024-2025/2"},
    {9, "TC521D", "ALJABAR LINIER DAN MATRIX", 2, 'A', 8, "2024-2025/2"}
};

void bersihkanLayar() {
    system("cls");
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void garisPendek() {
    for (int i = 0; i < 30; i++) {
        printf("%c", 196);
    }
    printf("\n");
}

void garisPanjang() {
    for (int i = 0; i < 80; i++) {
        printf("%c", 205);
    }
    printf("\n");
}

void tampilkanWaktu() {
    time_t t;
    struct tm *tm_info;
    char time_str[30];

    time(&t);
    tm_info = localtime(&t);
    strftime(time_str, sizeof(time_str), "%a %b %d %H:%M:%S %Y", tm_info);
    printf("%s", time_str);
}

void pauseProgram() {
    gotoxy(40, 21);
    printf("Tekan Enter untuk melanjutkan...");
    fflush(stdin);
    getchar();
}

void tampilkanHeader() {
    gotoxy(40, 1);
    tampilkanWaktu();
    gotoxy(113, 1);
    printf("SIA.SAT");
    gotoxy(40, 2);
    garisPanjang();
}

void tampilkanDataMahasiswa() {
    gotoxy(40, 4);
    printf("672024105 - Maulida");
    gotoxy(40, 5);
    printf("FAKULTAS TEKNOLOGI INFORMASI - S1 TEKNIK INFORMATIKA");
    gotoxy(40, 6);
    printf("SEMESTER 3 TA 2024/2025");
    gotoxy(40, 7);
    printf("BATAS SKS: 20");
    gotoxy(40, 9);
    garisPanjang();
}

void tampilkanFooter() {
    gotoxy(40, 22);
    garisPanjang();
}

int login() {
    char nim[MAKS_NIM];
    char password[MAKS_PASSWORD];
    int i = 0;
    char ch;

    bersihkanLayar();
    tampilkanHeader();

    gotoxy(65, 4);
    printf("Selamat Datang Di SIASAT UKSW");
    gotoxy(40, 6);
    garisPanjang();

    gotoxy(65, 8);
    printf("NIM      : ");
    gotoxy(65, 9);
    garisPendek();
    gotoxy(65, 10);
    printf("Password : ");
    gotoxy(65, 11);
    garisPendek();

    tampilkanFooter();

    gotoxy(76, 8);
    if (scanf("%14s", nim) != 1) {
        gotoxy(50, 12);
        printf("Input tidak valid!");
        pauseProgram();
        return 0;
    }

    gotoxy(76, 10);
    i = 0;
    while (i < MAKS_PASSWORD - 1) {
        ch = getch();
        if (ch == 13) {
            password[i] = '\0';
            break;
        } else if (ch == 8 && i > 0) {
            i--;
            printf("\b \b");
        } else if (ch != 8 && ch >= 32 && ch <= 126) {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';

    if (strcmp(nim, "672024105") == 0 && strcmp(password, "admin") == 0) {
        gotoxy(60, 14);
        printf("Login berhasil! Selamat datang, Maulida.");
        Sleep(1500);
        return 1;
    } else {
        gotoxy(60, 14);
        printf("Login gagal. NIM atau password salah.");
        pauseProgram();
        return 0;
    }
}

void menuRegistrasiUlang() {
    int pilihan = 1;
    int tombol;

    while (1) {
        bersihkanLayar();
        tampilkanHeader();
        tampilkanDataMahasiswa();
        tampilkanFooter();

        gotoxy(70, 11);
        printf("REGISTRASI ULANG");
        gotoxy(40, 13);
        printf(pilihan == 1 ? ">> Lanjut Kuliah" : "   Lanjut Kuliah");
        gotoxy(40, 14);
        printf(pilihan == 2 ? ">> Jeda Kuliah" : "   Jeda Kuliah");
        gotoxy(40, 15);
        printf(pilihan == 3 ? ">> Kembali" : "   Kembali");

        tombol = getch();
        if (tombol == 0 || tombol == 224) {
            tombol = getch();
            if (tombol == 72) {
                pilihan = (pilihan == 1) ? 3 : pilihan - 1;
            } else if (tombol == 80) {
                pilihan = (pilihan == 3) ? 1 : pilihan + 1;
            }
        } else if (tombol == 13) {
            if (pilihan == 3) return;

            bersihkanLayar();
            tampilkanHeader();
            tampilkanDataMahasiswa();

            sudahRegistrasiUlang = 1;
            gotoxy(40, 11);
            if (pilihan == 1) {
                printf("Anda memilih: Lanjut Kuliah");
            } else {
                printf("Anda memilih: Jeda Kuliah");
            }
            gotoxy(40, 12);
            printf("Registrasi ulang berhasil!");

            pauseProgram();
            return;
        }
    }
}

void transkripNilai() {
    int totalSks = 0;
    int totalAk = 0;
    float ipk;

    bersihkanLayar();
    tampilkanHeader();
    tampilkanDataMahasiswa();

    gotoxy(60, 10);
    printf("TRANSKRIP NILAI");
    gotoxy(40, 12);
    garisPanjang();
    gotoxy(40, 13);
    printf(" No  Kode     Mata Kuliah                    SKS  Nilai  AK   Tahun Ambil");
    gotoxy(40, 14);
    garisPanjang();

    for (int i = 0; i < MAKS_TRANSKRIP; i++) {
        gotoxy(40, 15 + i);
        printf(" %-3d %-8s %-30s %-4d %-6c %-4d %-12s",
               transkrip[i].no,
               transkrip[i].kode,
               transkrip[i].nama,
               transkrip[i].sks,
               transkrip[i].nilai,
               transkrip[i].ak,
               transkrip[i].tahunAmbil);

        totalSks += transkrip[i].sks;
        totalAk += transkrip[i].ak;
    }

    gotoxy(40, 15 + MAKS_TRANSKRIP);
    garisPanjang();
    gotoxy(40, 16 + MAKS_TRANSKRIP);
    printf(" Total                                       %d         %d", totalSks, totalAk);

    ipk = (totalSks > 0) ? (float)totalAk / totalSks : 0.0;
    gotoxy(40, 17 + MAKS_TRANSKRIP);
    printf(" IPK: %.2f", ipk);

    fflush(stdin);
    getchar();
}

void registrasiMataKuliah() {
    typedef struct {
        char kode[MAKS_KODE];
        char nama[MAKS_STRING];
        int sksA;
        int sksB;
        char keterangan[MAKS_STRING];
    } TemplateMK;

    typedef struct {
        char kode[MAKS_KODE];
        char nama[MAKS_STRING];
        int sksA;
        int sksB;
        char hari[20];
        char jam[20];
    } JadwalPilihan;

    TemplateMK pilihanMK[] = {
        {"TC105", "TBO", 3, 2, "Ineke Pakereng"},
        {"TC112", "IMK", 3, 2, "Sinta "}
    };

    JadwalPilihan jadwalPilihan[2][2] = {
        {
            {"TC105B", "TEORI BAHASA DAN OTOMATA", 3, 2, "Senin", "08:00 - 09:40"},
            {"TC105A", "TEORI BAHASA DAN OTOMATA", 3, 2, "Rabu", "13:00 - 14:40"}
        },
        {
            {"TC112A", "INTERAKSI MANUSIA DAN KOMPUTER", 3, 2, "Selasa", "10:00 - 11:40"},
            {"TC112C", "INTERAKSI MANUSIA DAN KOMPUTER", 3, 2, "Kamis", "15:00 - 16:40"}
        }
    };

    int jumlahPilihan = sizeof(pilihanMK) / sizeof(pilihanMK[0]);
    int pilihan = 1;
    int tombol;

    while (1) {
        bersihkanLayar();
        tampilkanHeader();
        tampilkanDataMahasiswa();
        tampilkanFooter();

        gotoxy(60, 10);
        printf("REGISTRASI MATA KULIAH");
        gotoxy(40, 12);
        garisPanjang();

        for (int i = 0; i < jumlahPilihan; i++) {
            gotoxy(40, 14 + i);
            printf(pilihan == i + 1 ? ">> %s - %s" : "   %s - %s", pilihanMK[i].kode, pilihanMK[i].nama);
        }

        gotoxy(40, 15 + jumlahPilihan);
        printf(pilihan == jumlahPilihan + 1 ? ">> Kembali" : "   Kembali");

        tombol = getch();
        if (tombol == 0 || tombol == 224) {
            tombol = getch();
            if (tombol == 72) {
                pilihan = (pilihan == 1) ? jumlahPilihan + 1 : pilihan - 1;
            } else if (tombol == 80) {
                pilihan = (pilihan == jumlahPilihan + 1) ? 1 : pilihan + 1;
            }
        } else if (tombol == 13) {
            if (pilihan == jumlahPilihan + 1) return;

            int indexMK = pilihan - 1;
            int pilihanJadwal = 1;

            while (1) {
                bersihkanLayar();
                tampilkanHeader();
                tampilkanDataMahasiswa();
                tampilkanFooter();

                gotoxy(50, 10);
                printf("PILIH JADWAL UNTUK MATA KULIAH");
                gotoxy(40, 12);
                printf("Kode: %s", pilihanMK[indexMK].kode);
                gotoxy(40, 13);
                printf("Nama: %s", pilihanMK[indexMK].nama);
                gotoxy(40, 14);
                garisPanjang();

                for (int j = 0; j < 2; j++) {
                    gotoxy(40, 16 + j);
                    printf(pilihanJadwal == j + 1 ? ">> [%s] %s | SKS A:%d B:%d | %s %s"
                           : "   [%s] %s | SKS A:%d B:%d | %s %s",
                           jadwalPilihan[indexMK][j].kode,
                           jadwalPilihan[indexMK][j].nama,
                           jadwalPilihan[indexMK][j].sksA,
                           jadwalPilihan[indexMK][j].sksB,
                           jadwalPilihan[indexMK][j].hari,
                           jadwalPilihan[indexMK][j].jam);
                }

                gotoxy(40, 18);
                printf(pilihanJadwal == 3 ? ">> Kembali" : "   Kembali");

                tombol = getch();
                if (tombol == 0 || tombol == 224) {
                    tombol = getch();
                    if (tombol == 72) {
                        pilihanJadwal = (pilihanJadwal == 1) ? 3 : pilihanJadwal - 1;
                    } else if (tombol == 80) {
                        pilihanJadwal = (pilihanJadwal == 3) ? 1 : pilihanJadwal + 1;
                    }
                } else if (tombol == 13) {
                    if (pilihanJadwal == 3) break;

                    if (jumlahMK >= MAKS_MK || jumlahJadwal >= MAKS_JADWAL) {
                        gotoxy(40, 20);
                        printf("Kapasitas mata kuliah atau jadwal penuh.");
                        pauseProgram();
                        return;
                    }

                    JadwalPilihan *jp = &jadwalPilihan[indexMK][pilihanJadwal - 1];

                    strcpy(mk[jumlahMK].kode, jp->kode);
                    strcpy(mk[jumlahMK].nama, jp->nama);
                    mk[jumlahMK].sksA = jp->sksA;
                    mk[jumlahMK].sksB = jp->sksB;
                    strcpy(mk[jumlahMK].keterangan, pilihanMK[indexMK].keterangan);
                    jumlahMK++;

                    strcpy(jadwal[jumlahJadwal].kode, jp->kode);
                    strcpy(jadwal[jumlahJadwal].nama, jp->nama);
                    strcpy(jadwal[jumlahJadwal].hari, jp->hari);
                    strcpy(jadwal[jumlahJadwal].jam, jp->jam);
                    jumlahJadwal++;

                    gotoxy(40, 20);
                    printf("Mata kuliah dan jadwal berhasil ditambahkan!");
                    pauseProgram();
                    return;
                }
            }
        }
    }
}


void kartuStudi() {
    int pilihanMenu = 0;

    while (1) {
        bersihkanLayar();
        tampilkanHeader();
        tampilkanDataMahasiswa();
        tampilkanFooter();

        gotoxy(60, 10);
        printf("KARTU STUDI");

        if (jumlahMK == 0) {
            gotoxy(40, 12);
            printf("Belum ada data mata kuliah yang terdaftar.");
            gotoxy(40, 13);
            printf("Silakan registrasi mata kuliah terlebih dahulu.");
            pauseProgram();
            return;
        }

        gotoxy(40, 12);
        printf("No  Kode     Mata Kuliah                            SKS A  SKS B  Keterangan");
        gotoxy(40, 13);
        garisPanjang();

        for (int i = 0; i < jumlahMK; i++) {
            gotoxy(40, 14 + i);
            printf("%-3d %-8s %-40s %-6d %-6d %-s",
                   i + 1,
                   mk[i].kode,
                   mk[i].nama,
                   mk[i].sksA,
                   mk[i].sksB,
                   mk[i].keterangan);
        }

        gotoxy(40, 14 + jumlahMK);
        garisPanjang();

        gotoxy(45, 21 + jumlahMK);
        if (pilihanMenu == 0) {
            printf(">> HAPUS <<                                               KEMBALI");
        } else {
            printf("   HAPUS                                               >> KEMBALI <<");
        }

        char tombol = getch();
        if (tombol == 0 || tombol == -32) {

            tombol = getch();
            if (tombol == 75) {
                pilihanMenu = 0;
            } else if (tombol == 77) {
                pilihanMenu = 1;
            }
        } else if (tombol == 13) {
            if (pilihanMenu == 1) {
                return;
            } else {
                int hapus;
                gotoxy(45, 18 + jumlahMK);
                printf("Pilih nomor mata kuliah yang ingin dihapus (atau 0 untuk batal): ");
                scanf("%d", &hapus);

                if (hapus == 0) {
                    continue;
                } else if (hapus > 0 && hapus <= jumlahMK) {
                    for (int i = hapus - 1; i < jumlahMK - 1; i++) {
                        mk[i] = mk[i + 1];
                    }
                    jumlahMK--;

                    gotoxy(45, 20 + jumlahMK);
                    printf("Mata kuliah berhasil dihapus.");
                    pauseProgram();
                } else {
                    gotoxy(45, 20 + jumlahMK);
                    printf("Nomor tidak valid. Silakan coba lagi.");
                    pauseProgram();
                }
            }
        }
    }
}

void hasilStudi() {
    int pilihanMenu = 0;

    if (jumlahMK == 0) {
        bersihkanLayar();
        tampilkanHeader();
        tampilkanDataMahasiswa();
        tampilkanFooter();
        gotoxy(40, 10);
        printf("Belum ada data mata kuliah yang terdaftar.");
        gotoxy(40, 11);
        printf("Silakan registrasi mata kuliah terlebih dahulu.");
        pauseProgram();
        return;
    }

    while (1) {
        bersihkanLayar();
        tampilkanHeader();
        tampilkanDataMahasiswa();
        tampilkanFooter();

        gotoxy(60, 10);
        printf("HASIL STUDI");
        gotoxy(50, 11);
        printf("SEMESTER 3 TA 2024-2025");
        gotoxy(40, 13);
        printf("No  Kode     Mata Kuliah                     B/U  SKS  Nilai  AK");
        gotoxy(40, 14);
        garisPanjang();

        float totalAK = 0;
        int totalSKS = 0;

        for (int i = 0; i < jumlahMK; i++) {
            hasil[i].nilai = 'A';
            hasil[i].sks = mk[i].sksA;
            hasil[i].ak = hasil[i].sks * 4.0;
            strcpy(hasil[i].kode, mk[i].kode);
            strcpy(hasil[i].nama, mk[i].nama);

            gotoxy(40, 15 + i);
            printf("%-3d %-8s %-30s B    %-3d %-6c %-3.0f",
                   i + 1,
                   hasil[i].kode,
                   hasil[i].nama,
                   hasil[i].sks,
                   hasil[i].nilai,
                   hasil[i].ak);

            totalAK += hasil[i].ak;
            totalSKS += hasil[i].sks;
        }

        gotoxy(40, 15 + jumlahMK);
        garisPanjang();
        gotoxy(40, 16 + jumlahMK);
        printf("Total SKS: %-3d    Total AK: %-3.0f", totalSKS, totalAK);
        gotoxy(40, 17 + jumlahMK);
        if (totalSKS > 0) {
            printf("IPK: %.2f", totalAK / totalSKS);
        }

        gotoxy(45, 19 + jumlahMK);
        if (pilihanMenu == 0) {
            printf(">> HAPUS <<                                             KEMBALI");
        } else {
            printf("   HAPUS                                          >> KEMBALI <<");
        }

        char tombol = getch();
        if (tombol == 0 || tombol == -32) {
            tombol = getch();
            if (tombol == 75) {
                pilihanMenu = 0;
            } else if (tombol == 77) {
                pilihanMenu = 1;
            }
        } else if (tombol == 13) {
            if (pilihanMenu == 1) {
                return;
            } else {
                gotoxy(45, 21 + jumlahMK);
                printf("Fitur HAPUS hasil studi belum tersedia.");
                pauseProgram();
            }
        }
    }
}

void registrasiJadwalKuliah() {
    if (jumlahMK == 0) {
        bersihkanLayar();
        tampilkanHeader();
        gotoxy(40, 10);
        printf("Belum ada mata kuliah yang terdaftar.");
        gotoxy(40, 11);
        printf("Silakan registrasi mata kuliah terlebih dahulu.");
        pauseProgram();
        return;
    }

    while (1) {
        bersihkanLayar();
        tampilkanHeader();
        tampilkanDataMahasiswa();
        tampilkanFooter();

        gotoxy(55, 10);
        printf("REGISTRASI JADWAL KULIAH");
        gotoxy(40, 12);
        printf("Mata Kuliah yang Tersedia:");

        for (int i = 0; i < jumlahMK; i++) {
            gotoxy(40, 13 + i);
            printf("%d. %s (%s)", i + 1, mk[i].nama, mk[i].kode);
        }
        gotoxy(40, 13 + jumlahMK);
        printf("%d. Kembali", jumlahMK + 1);

        gotoxy(40, 15 + jumlahMK);
        printf("Pilih mata kuliah (1-%d): ", jumlahMK + 1);

        int pilihan;
        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid!");
            fflush(stdin);
            pauseProgram();
            continue;
        }

        if (pilihan == jumlahMK + 1) {
            break;
        } else if (pilihan < 1 || pilihan > jumlahMK) {
            printf("Pilihan tidak valid!");
            pauseProgram();
            continue;
        } else {
            if (jumlahJadwal >= MAKS_JADWAL) {
                printf("Kapasitas jadwal penuh (%d dari %d)!", jumlahJadwal, MAKS_JADWAL);
                pauseProgram();
                continue;
            }

            strcpy(jadwal[jumlahJadwal].kode, mk[pilihan - 1].kode);
            strcpy(jadwal[jumlahJadwal].nama, mk[pilihan - 1].nama);
            fflush(stdin);

            printf("Masukkan hari: ");
            fgets(jadwal[jumlahJadwal].hari, sizeof(jadwal[jumlahJadwal].hari), stdin);
            jadwal[jumlahJadwal].hari[strcspn(jadwal[jumlahJadwal].hari, "\n")] = '\0';

            printf("Masukkan jam: ");
            fgets(jadwal[jumlahJadwal].jam, sizeof(jadwal[jumlahJadwal].jam), stdin);
            jadwal[jumlahJadwal].jam[strcspn(jadwal[jumlahJadwal].jam, "\n")] = '\0';

            jumlahJadwal++;
            printf("\nJadwal berhasil didaftarkan!");
            pauseProgram();
        }
    }
}

void tampilkanJadwalKuliah() {
    bersihkanLayar();
    tampilkanHeader();
    tampilkanDataMahasiswa();
    tampilkanFooter();

    gotoxy(60, 10);
    printf("JADWAL KULIAH");

    if (jumlahJadwal == 0) {
        gotoxy(40, 12);
        printf("Jadwal kuliah belum tersedia.");
        gotoxy(40, 13);
        printf("Silakan daftarkan jadwal terlebih dahulu.");
        pauseProgram();
        return;
    }

    gotoxy(40, 12);
    printf("No  Kode     Mata Kuliah                    Hari       Jam");
    gotoxy(40, 13);
    garisPanjang();

    for (int i = 0; i < jumlahJadwal; i++) {
        gotoxy(40, 14 + i);
        printf("%-3d %-8s %-30s %-10s %-10s",
               i + 1,
               jadwal[i].kode,
               jadwal[i].nama,
               jadwal[i].hari,
               jadwal[i].jam);
    }

    gotoxy(40, 14 + jumlahJadwal);
    garisPanjang();
    pauseProgram();
}

void menuJadwalKuliah() {
    int pilihan = 1;
    int tombol;

    while (1) {
        bersihkanLayar();
        tampilkanHeader();
        tampilkanDataMahasiswa();
        tampilkanFooter();

        gotoxy(60, 11);
        printf("MENU JADWAL KULIAH");
        gotoxy(40, 13);
        printf(pilihan == 1 ? ">> Tampilkan Jadwal" : "   Tampilkan Jadwal");
        gotoxy(40, 14);
        printf(pilihan == 2 ? ">> Kembali" : "   Kembali");

        tombol = getch();
        if (tombol == 0 || tombol == 224) {
            tombol = getch();
            if (tombol == 72) {
                pilihan = (pilihan == 1) ? 2 : 1;
            } else if (tombol == 80) {
                pilihan = (pilihan == 2) ? 1 : 2;
            }
        } else if (tombol == 13) {
            switch (pilihan) {
                case 1:
                    tampilkanJadwalKuliah();
                    break;
                case 2:
                    return;
            }
        }
    }
}


void tagihan() {
    bersihkanLayar();
    tampilkanHeader();
    tampilkanDataMahasiswa();
    tampilkanFooter();

    gotoxy(60, 10);
    printf("TAGIHAN PERKULIAHAN");

    if (jumlahJadwal == 0) {
        gotoxy(40, 12);
        printf("Belum ada jadwal kuliah yang terdaftar.");
        gotoxy(40, 13);
        printf("Silakan daftarkan jadwal terlebih dahulu.");
        pauseProgram();
        return;
    }

    float totalBiaya = 0.0;

    gotoxy(40, 12);
    garisPanjang();
    gotoxy(40, 13);
    printf("No  Kode     Mata Kuliah                        SKS B   Biaya (Rp)");
    gotoxy(40, 14);
    garisPanjang();

    for (int i = 0; i < jumlahJadwal; i++) {
        int found = 0;
        for (int j = 0; j < jumlahMK; j++) {
            if (strcmp(jadwal[i].kode, mk[j].kode) == 0) {
                float biayaMK = 0.0;
                int sksB = mk[j].sksB;

                switch (sksB) {
                    case 1:
                        biayaMK = 250000.0;
                        break;
                    case 2:
                        biayaMK = 500000.0;
                        break;
                    case 3:
                        biayaMK = 750000.0;
                        break;
                    case 4:
                        biayaMK = 1000000.0;
                        break;
                    default:
                        biayaMK = sksB * 250000.0;
                        break;
                }

                biayaMK += sksB * 100000.0;

                gotoxy(40, 15 + i);
                printf("%-3d %-8s %-30s %-6d Rp %-10.2f",
                       i + 1,
                       mk[j].kode,
                       mk[j].nama,
                       sksB,
                       biayaMK);

                totalBiaya += biayaMK;
                found = 1;
                break;
            }
        }

        if (!found) {
            gotoxy(40, 15 + i);
            printf("%-3d %-8s %-30s %-6s %-s", i + 1, jadwal[i].kode, jadwal[i].nama, "N/A", "N/A");
        }
    }

    gotoxy(40, 16 + jumlahJadwal);
    garisPanjang();
    gotoxy(40, 17 + jumlahJadwal);
    printf("Total Tagihan: Rp %.2f", totalBiaya);

    pauseProgram();
}


void inputPoin() {
    char namaKegiatan[MAKS_STRING];
    int poin;

    bersihkanLayar();
    tampilkanHeader();
    tampilkanDataMahasiswa();
    tampilkanFooter();

    gotoxy(60, 10);
    printf("INPUT POIN KEAKTIFAN");

    if (keaktifan.jumlahKegiatan >= MAKS_KEGIATAN) {
        gotoxy(40, 12);
        printf("Penyimpanan kegiatan sudah penuh.");
        pauseProgram();
        return;
    }

    fflush(stdin);
    gotoxy(40, 13);
    printf("Masukkan nama kegiatan: ");
    fgets(namaKegiatan, sizeof(namaKegiatan), stdin);
    namaKegiatan[strcspn(namaKegiatan, "\n")] = '\0';

    gotoxy(40, 14);
    printf("Masukkan poin keaktifan: ");
    if (scanf("%d", &poin) != 1 || poin < 0) {
        gotoxy(40, 15);
        printf("Input tidak valid!");
        pauseProgram();
        return;
    }

    strcpy(keaktifan.daftarKegiatan[keaktifan.jumlahKegiatan].namaKegiatan, namaKegiatan);
    keaktifan.daftarKegiatan[keaktifan.jumlahKegiatan].poin = poin;
    keaktifan.jumlahKegiatan++;
    keaktifan.totalPoin += poin;

    gotoxy(40, 16);
    printf("Poin berhasil ditambahkan. Total poin saat ini: %d", keaktifan.totalPoin);

    pauseProgram();
}


void lihatPoin() {
    bersihkanLayar();
    tampilkanHeader();
    tampilkanDataMahasiswa();
    tampilkanFooter();

    gotoxy(60, 10);
    printf("DAFTAR POIN KEAKTIFAN");

    if (keaktifan.jumlahKegiatan == 0) {
        gotoxy(40, 12);
        printf("Belum ada poin keaktifan yang dimasukkan.");
        pauseProgram();
        return;
    }

    gotoxy(40, 12);
    garisPanjang();
    gotoxy(40, 13);
    printf("No  Nama Kegiatan                                Poin");
    gotoxy(40, 14);
    garisPanjang();

    for (int i = 0; i < keaktifan.jumlahKegiatan; i++) {
        gotoxy(40, 15 + i);
        printf("%-3d %-40s %-4d",
               i + 1,
               keaktifan.daftarKegiatan[i].namaKegiatan,
               keaktifan.daftarKegiatan[i].poin);
    }

    gotoxy(40, 16 + keaktifan.jumlahKegiatan);
    garisPanjang();
    gotoxy(40, 17 + keaktifan.jumlahKegiatan);
    printf("Total Poin Keaktifan: %d", keaktifan.totalPoin);

    gotoxy(40, 19 + keaktifan.jumlahKegiatan);
    printf("Tekan Enter untuk kembali ke menu...");
    getch();
}


void keaktifanMahasiswa() {
    int pilihan = 1;
    while (1) {
        bersihkanLayar();
        tampilkanHeader();


        gotoxy(40, 4);
        printf(pilihan == 1 ? ">> Input Poin" : "   Input Poin");
        gotoxy(40, 5);
        printf(pilihan == 2 ? ">> Lihat Poin" : "   Lihat Poin");
        gotoxy(40, 6);
        printf(pilihan == 3 ? ">> Kembali" : "   Kembali");

        int tombol = getch();
        if (tombol == 0 || tombol == 224) {
            tombol = getch();
            if (tombol == 72) {
                pilihan--;
                if (pilihan < 1) pilihan = 3;
            } else if (tombol == 80) {
                pilihan++;
                if (pilihan > 3) pilihan = 1;
            }
        } else if (tombol == 13) {
            switch (pilihan) {
                case 1:
                    inputPoin();
                    break;
                case 2:
                    lihatPoin();
                    break;
                case 3:
                    return;
            }
        }
    }
}

int main() {
    while (!login()) {
    }

    int menu = 1;
    int tombol;

    while (1) {
        bersihkanLayar();
        tampilkanHeader();
        tampilkanDataMahasiswa();
        tampilkanFooter();

        gotoxy(40, 11);
        printf(menu == 1 ? ">> REGISTRASI ULANG" : "   REGISTRASI ULANG");
        gotoxy(40, 12);
        printf(menu == 2 ? ">> REGISTRASI MATA KULIAH" : "   REGISTRASI MATA KULIAH");
        gotoxy(40, 13);
        printf(menu == 3 ? ">> KARTU STUDI" : "   KARTU STUDI");
        gotoxy(40, 14);
        printf(menu == 4 ? ">> HASIL STUDI" : "   HASIL STUDI");
        gotoxy(40, 15);
        printf(menu == 5 ? ">> JADWAL KULIAH" : "   JADWAL KULIAH");
        gotoxy(40, 16);
        printf(menu == 6 ? ">> TRANSKRIP NILAI" : "   TRANSKRIP NILAI");
        gotoxy(40, 17);
        printf(menu == 7 ? ">> TAGIHAN" : "   TAGIHAN");
        gotoxy(40, 18);
        printf(menu == 8 ? ">> KEAKTIFAN MAHASISWA" : "   KEAKTIFAN MAHASISWA");
        gotoxy(108, 23);
        printf(menu == 9 ? ">> LOGOUT <<" : "   LOGOUT");

        tombol = getch();
        if (tombol == 0 || tombol == 224) {
            tombol = getch();
            if (tombol == 72) {
                menu = (menu == 1) ? 9 : menu - 1;
            } else if (tombol == 80) {
                menu = (menu == 9) ? 1 : menu + 1;
            }
        } else if (tombol == 13) {
            switch (menu) {
                case 1:
                    menuRegistrasiUlang();
                    break;
                case 2:
                    registrasiMataKuliah();
                    break;
                case 3:
                    kartuStudi();
                    break;
                case 4:
                    hasilStudi();
                    break;
                case 5:
                    menuJadwalKuliah();
                    break;
                case 6:
                    transkripNilai();
                    break;
                case 7:
                    tagihan();
                    break;
                case 8:
                    keaktifanMahasiswa();
                    break;
                case 9:
                    bersihkanLayar();
                    gotoxy(60, 10);
                    printf("Terima kasih telah menggunakan SIASAT UKSW");
                    gotoxy(65, 12);
                    printf("Sampai jumpa lagi!");
                    gotoxy(60, 14);
                    printf("Tekan Enter untuk keluar...");
                    getch();
                    return 0;
            }
        }
    }

    return 0;
}
