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

// Array untuk tracking total penjualan per produk
int totalPenjualan[jmlData] = {0};

struct Beli {
    string nama;
    int qty;
    int harga;
    int total;
};

struct Transaksi {
    string waktu;
    vector<Beli> items;
    int totalBelanja;
    double diskon;
    double bayar;
};

// Searching barang
int searchBarang(string key) {
    for (int i = 0; i < jmlData; i++) {
        if (namaBarang[i] == key) return i;
    }
    return -1;
}

// Input Barang untuk satu transaksi
void inputBarang(vector<Beli> &belanja, int &totalBelanja) {
    string input;
    while (true) {
        cout << "Nama barang: ";
        getline(cin, input);

        if (input == "selesai") break;

        int index = searchBarang(input);   
        if (index == -1) {
            cout << "Barang tidak ditemukan! Silakan ulangi.\n";
            continue;
        }

        cout << "Jumlah: ";
        getline(cin, input);
        int qty;
        try {
            qty = stoi(input);
        } catch (...) {
            cout << "Input jumlah tidak valid! Silakan ulangi.\n";
            continue;
        }

        Beli item;
        item.nama = namaBarang[index];
        item.qty = qty;
        item.harga = hargaBarang[index];
        item.total = qty * hargaBarang[index];
        belanja.push_back(item);
        totalBelanja += item.total;
        totalPenjualan[index] += qty;  // Update penjualan produk

        cout << endl;
    }
}

// Hitung Diskon
double hitungDiskon(int total) {
    if (total >= 300000) return 0.20;
    else if (total >= 200000) return 0.10;
    return 0.0;
}

// Sorting barang berdasarkan nama
void sortBarang(vector<Beli> &arr) {
    sort(arr.begin(), arr.end(), [](const Beli &a, const Beli &b) {
        return a.nama < b.nama;
    });
}

// Cetak Struk untuk satu transaksi
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

    for (const auto &item : transaksi.items) {
        cout << setw(20) << left << item.nama
             << setw(10) << item.qty
             << setw(10) << item.harga
             << setw(10) << item.total << endl;
    }

    cout << "---------------------------------------------\n";
    cout << setw(30) << left << "Total Belanja:" << transaksi.totalBelanja << endl;
    cout << setw(30) << left << "Diskon (" << transaksi.diskon * 100 << "%):" << transaksi.totalBelanja * transaksi.diskon << endl;
    cout << setw(30) << left << "Total Bayar:" << transaksi.bayar << endl;
    cout << "=============================================\n";
    cout << "Terima kasih telah berbelanja!\n";
}

// Sorting transaksi (berdasarkan total bayar descending)
void sortTransaksi(vector<Transaksi> &riwayat) {
    sort(riwayat.begin(), riwayat.end(), [](const Transaksi &a, const Transaksi &b) {
        return a.bayar > b.bayar;
    });
}

// Tampilkan Rekap Transaksi
void tampilRekap(const vector<Transaksi> &riwayat) {
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

    for (const auto &t : riwayat) {
        cout << setw(20) << left << t.waktu
             << setw(15) << t.totalBelanja
             << setw(10) << (t.diskon * 100) << "%"
             << setw(10) << t.bayar << endl;
    }
    cout << "=============================================\n";
}

// Tampilkan 5 Produk Terlaris
void tampilProdukTerlaris() {
    vector<pair<int, string>> produk;
    for (int i = 0; i < jmlData; i++) {
        produk.push_back({totalPenjualan[i], namaBarang[i]});
    }
    sort(produk.rbegin(), produk.rend());  // Sort descending berdasarkan penjualan

    cout << "\n=============================================\n";
    cout << "            5 PRODUK TERLARIS               \n";
    cout << "=============================================\n";
    cout << setw(20) << left << "Nama Barang"
         << setw(10) << "Terjual" << endl;
    cout << "---------------------------------------------\n";

    for (int i = 0; i < min(5, (int)produk.size()); i++) {
        cout << setw(20) << left << produk[i].second
             << setw(10) << produk[i].first << endl;
    }
    cout << "=============================================\n";
}

// Fungsi untuk mendapatkan waktu saat ini
string getCurrentTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

// Main Program
int main() {
    vector<Transaksi> riwayat;
    int pilihan;

    cout << "=== PROGRAM KASIR SEDERHANA ===\n";

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Lakukan Transaksi\n";
        cout << "2. Lihat Rekap Transaksi\n";
        cout << "3. Lihat 5 Produk Terlaris\n";
        cout << "4. Keluar\n";
        cout << "Pilih: ";
        string input;
        getline(cin, input);
        try {
            pilihan = stoi(input);
        } catch (...) {
            cout << "Pilihan tidak valid!\n";
            continue;
        }

        switch (pilihan) {
            case 1: {
                vector<Beli> belanja;
                int totalBelanja = 0;

                cout << "\nKetik 'selesai' untuk mengakhiri input.\n\n";
                inputBarang(belanja, totalBelanja);

                if (!belanja.empty()) {
                    sortBarang(belanja);
                    double diskon = hitungDiskon(totalBelanja);
                    double potongan = totalBelanja * diskon;
                    double bayar = totalBelanja - potongan;

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