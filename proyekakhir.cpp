#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <map>
using namespace std;

// Array 1D untuk barang
string namaBarang[] = {
    "Sabun", "Sampo", "Pasta Gigi", "Minyak Goreng", "Gula",
    "Beras 5kg", "Telur 1kg", "Kopi", "Teh", "Kecap",
    "Saus", "Susu", "Tissue", "Roti", "Mie Instan"
};
int hargaBarang[] = {
    5000, 30000, 15000, 20000, 12000,
    60000, 25000, 10000, 8000, 9000,
    8500, 25000, 7000, 20000, 3000
};
const int jmlData = sizeof(namaBarang) / sizeof(namaBarang[0]);

int totalPenjualan[jmlData] = {0};

struct Beli {
    string nama;
    int qty;
    int harga;
    long long total;  
};

struct Transaksi {
    string waktu;
    vector<Beli> items;
    long long totalBelanja;  
    double diskon;
    long long bayar;  
};


// Searching barang
int searchBarang(string key) {
    // pengulangan
    for (int i = 0; i < jmlData; i++) {
        // percabangan
        if (namaBarang[i] == key) return i;
    }
    return -1;
}

// Input Barang satu transaksi
void inputBarang(vector<Beli> &belanja, long long &totalBelanja) {
    string input;
    // pengulangan
    while (true) {
        cout << "Nama barang: ";
        getline(cin, input);

        // percabangan
        if (input == "selesai") break;

        int index = searchBarang(input);   
        // percabangan
        if (index == -1) {
            cout << "Barang tidak ditemukan! Silakan ulangi.\n";
            continue;
        }

        cout << "Jumlah: ";
        getline(cin, input);
        int qty;
        // percabaganan
        try {
            qty = stoi(input);
        } catch (...) {
            cout << "Input jumlah tidak valid! Silakan ulangi.\n";
            continue;
        }

        // percabangan
        if (qty <= 0) {
            cout << "Jumlah harus lebih dari 0! Silakan ulangi.\n";
            continue;
        }

        Beli item;
        item.nama = namaBarang[index];
        item.qty = qty;
        item.harga = hargaBarang[index];
        item.total = (long long)qty * hargaBarang[index];
        belanja.push_back(item);
        totalBelanja += item.total;
        totalPenjualan[index] += qty; 

        cout << endl;
    }
}
\
// Hitung Diskon
double hitungDiskon(long long total) {
    // percabangan
    if (total >= 300000) return 0.20;
    else if (total >= 200000) return 0.10;
    return 0.0;
}

// Sorting nama barang menggunakan Bubble Sort
void sortBarang(vector<Beli> &arr) {
    int n = arr.size();
    // pengulangan
    for (int i = 0; i < n - 1; i++) {
        // pengulangan
        for (int j = 0; j < n - i - 1; j++) {
            // percabangan
            if (arr[j].nama > arr[j + 1].nama) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Cetak Struk untuk transaksi
void cetakStruk(const Transaksi &transaksi) {
    cout << "\n=============================================\n";
    cout << "                STRUK BELANJA               \n";
    cout << "Waktu: " << transaksi.waktu << "\n";
    cout << "=============================================\n";
    cout << setw(20) << left << "Nama Barang"
         << setw(10) << "Qty"
         << setw(10) << "Harga"
         << setw(10) << "Total" << endl;
    cout << "---------------------------------------------\n";

    // pengulangan
    for (const auto &item : transaksi.items) {
        cout << setw(20) << left << item.nama
             << setw(10) << item.qty
             << setw(10) << item.harga
             << setw(10) << item.total << endl;
    }

    cout << "---------------------------------------------\n";
    cout << setw(30) << left << "Total Belanja:" << transaksi.totalBelanja << endl;
    cout << setw(30) << left << "Diskon (" << transaksi.diskon * 100 << "%):" << (long long)(transaksi.totalBelanja * transaksi.diskon) << endl;  // Casting untuk tampilan
    cout << setw(30) << left << "Total Bayar:" << transaksi.bayar << endl;
    cout << "=============================================\n";
    cout << "Terima kasih telah berbelanja!\n";
}


// Sorting transaksi menggunakan Bubble Sort
void sortTransaksi(vector<Transaksi> &riwayat) {
    int n = riwayat.size();
    // pengulangan
    for (int i = 0; i < n - 1; i++) {
        // pengulangan
        for (int j = 0; j < n - i - 1; j++) {
            // percabangan
            if (riwayat[j].bayar < riwayat[j + 1].bayar) {
                swap(riwayat[j], riwayat[j + 1]);
            }
        }
    }
}

// menampilkan rekap transaksi
void tampilRekap(const vector<Transaksi> &riwayat) {
    // percabangan
    if (riwayat.empty()) {
        cout << "Belum ada transaksi.\n";
        return;
    }

    cout << "\n=============================================\n";
    cout << "              REKAP TRANSAKSI               \n";
    cout << "=============================================\n";
    cout << setw(20) << left << "Waktu"
         << setw(15) << "Total Belanja"
         << setw(10) << "Diskon"
         << setw(10) << "Bayar" << endl;
    cout << "---------------------------------------------\n";

    // pengulangan
    for (const auto &t : riwayat) {
        cout << setw(20) << left << t.waktu
             << setw(15) << t.totalBelanja
             << setw(10) << (t.diskon * 100) << "%"
             << setw(10) << t.bayar << endl;
    }
    cout << "=============================================\n";
}

// menampilkan 5 terlaris
void tampilProdukTerlaris() {
    vector<pair<int, string>> produk;
    // pengulangan
    for (int i = 0; i < jmlData; i++) {
        produk.push_back({totalPenjualan[i], namaBarang[i]});
    }
    // bubble sort
    int n = produk.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // percabangan
            if (produk[j].first < produk[j + 1].first) {
                swap(produk[j], produk[j + 1]);
            }
        }
    }

    cout << "\n=============================================\n";
    cout << "            5 PRODUK TERLARIS               \n";
    cout << "=============================================\n";
    cout << setw(20) << left << "Nama Barang"
         << setw(10) << "Terjual" << endl;
    cout << "---------------------------------------------\n";

    // pengulangan
    for (int i = 0; i < min(5, (int)produk.size()); i++) {
        cout << setw(20) << left << produk[i].second
             << setw(10) << produk[i].first << endl;
    }
    cout << "=============================================\n";
}

// pembuatan waktu
string getCurrentTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

// main program
int main() {
    vector<Transaksi> riwayat;
    int pilihan;

    cout << "=== PROGRAM KASIR SEDERHANA ===\n";

    // pengulangan
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Lakukan Transaksi\n";
        cout << "2. Lihat Rekap Transaksi\n";
        cout << "3. Lihat 5 Produk Terlaris\n";
        cout << "4. Keluar\n";
        cout << "Pilih: ";
        string input;
        getline(cin, input);
        // percabangan
        try {
            pilihan = stoi(input);
        } catch (...) {
            cout << "Pilihan tidak valid!\n";
            continue;
        }

        // percabangan
        switch (pilihan) {
            case 1: {
                vector<Beli> belanja;
                long long totalBelanja = 0; 

                cout << "\nKetik 'selesai' untuk mengakhiri input.\n\n";
                inputBarang(belanja, totalBelanja);

                // === PERCABANGAN ===
                if (!belanja.empty()) {
                    sortBarang(belanja);
                    double diskon = hitungDiskon(totalBelanja);
                    long long potongan = (long long)(totalBelanja * diskon); 
                    long long bayar = totalBelanja - potongan;  

                    Transaksi transaksi;
                    transaksi.waktu = getCurrentTime();
                    transaksi.items = belanja;
                    transaksi.totalBelanja = totalBelanja;
                    transaksi.diskon = diskon;
                    transaksi.bayar = bayar;

                    riwayat.push_back(transaksi);
                    cetakStruk(transaksi);
                } else {
                    cout << "Tidak ada barang yang dibeli.\n";
                }
                break;
            }
            case 2: {
                sortTransaksi(riwayat);
                tampilRekap(riwayat);
                break;
            }
            case 3: {
                tampilProdukTerlaris();
                break;
            }
            case 4: {
                cout << "Terima kasih!\n";
                return 0;
            }
            default: {
                cout << "Pilihan tidak valid!\n";
            }
        }
    }

    return 0;
}
