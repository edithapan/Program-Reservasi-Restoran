#include <iostream>
#include <string>
using namespace std;

void opsiPembayaran();

// Struktur Reservasi
struct Reservasi {
    string namaPelanggan;
    int jumlahOrang;
    string waktuReservasi;
    int nomorMeja;
    string pesananMenu;  // Menyimpan daftar menu yang dipesan
    string catatan; // Menyimpan catatan khusus
    long long totalHarga;  // Menyimpan total harga pesanan
    string opsiPembayaran; // Menyimpan jenis pembayaran yang dipilih
};

// Array
const int MAX_RESERVASI = 100; // Kapasitas maksimum reservasi
Reservasi daftarReservasi[MAX_RESERVASI];
int jumlahReservasi = 0;

// Fungsi untuk menambahkan reservasi
void tambahReservasi() {
    if (jumlahReservasi >= MAX_RESERVASI) {
        cout << "Reservasi penuh, tidak dapat menambahkan reservasi baru.\n";
        return;
    }

    Reservasi baru;
    cout << "Masukkan nama pelanggan: ";
    cin.ignore();
    getline(cin, baru.namaPelanggan);

    cout << "Masukkan jumlah orang: ";
    cin >> baru.jumlahOrang;

    cout << "Masukkan tanggal dan waktu reservasi (conto: 24-01-2025 14:30 ): ";
    cin.ignore();
    getline(cin, baru.waktuReservasi);

    // Validasi nomor meja
    bool mejaValid = false;
    while (!mejaValid) {
        cout << "Masukkan nomor meja: ";
        cin >> baru.nomorMeja;

        mejaValid = true; // Anggap nomor meja valid, lalu cek
        for (int i = 0; i < jumlahReservasi; i++) {
            if (daftarReservasi[i].nomorMeja == baru.nomorMeja && daftarReservasi[i].waktuReservasi == baru.waktuReservasi) {
                cout << "Nomor meja " << baru.nomorMeja << " sudah digunakan pada tanggal dan waktu " << baru.waktuReservasi << ". Silakan masukkan nomor meja yang berbeda.\n";
                mejaValid = false;
                break;
            }
        }
    }

    daftarReservasi[jumlahReservasi++] = baru;
    cout << "Reservasi berhasil untuk meja " << baru.nomorMeja << " pada tanggal dan waktu " << baru.waktuReservasi << ".\n";
}


// Fungsi untuk melihat semua reservasi
void lihatReservasi() {
    if (jumlahReservasi == 0) {
        cout << "Belum ada reservasi.\n";
        return;
    }
    cout << "\nDaftar Reservasi:\n";
    for (int i = 0; i < jumlahReservasi; ++i) {
        cout << "--------------------------\n";
        cout << "Reservasi " << i + 1 << ":\n";
        cout << "Nama Pelanggan: " << daftarReservasi[i].namaPelanggan << "\n";
        cout << "Jumlah Orang: " << daftarReservasi[i].jumlahOrang << "\n";
        cout << "Waktu Reservasi: " << daftarReservasi[i].waktuReservasi << "\n";
        cout << "Nomor Meja: " << daftarReservasi[i].nomorMeja << "\n";
        
        // Menampilkan menu yang dipesan
        if (!daftarReservasi[i].pesananMenu.empty()) {
            cout << "Menu yang Dipesan:\n" << daftarReservasi[i].pesananMenu << "\n";
        } else {
            cout << "Belum ada menu yang dipesan.\n";
        }

        // Menampilkan total harga
        cout << "Total Harga: ";
        if (daftarReservasi[i].totalHarga > 0) {
            cout << "Rp " << daftarReservasi[i].totalHarga << "\n";
        } else {
            cout << "Belum dihitung.\n";
        }

        // Menampilkan opsi pembayaran
        cout << "Opsi Pembayaran: ";
        if (!daftarReservasi[i].opsiPembayaran.empty()) {
            cout << daftarReservasi[i].opsiPembayaran << "\n";
        } else {
            cout << "Belum memilih opsi pembayaran.\n";
        }

        // Menampilkan catatan khusus
        if (!daftarReservasi[i].catatan.empty()) {
            cout << "Catatan Khusus: " << daftarReservasi[i].catatan << "\n";
        } else {
            cout << "Tidak ada catatan khusus.\n";
        }

        cout << "--------------------------\n";
    }
}


// Fungsi untuk menghapus reservasi
void hapusReservasi() {
    if (jumlahReservasi == 0) {
        cout << "Tidak ada reservasi untuk dihapus.\n";
        return;
    }

    int index;
    cout << "Masukkan nomor reservasi yang ingin dihapus: ";
    cin >> index;

    if (index < 1 || index > jumlahReservasi) {
        cout << "Nomor reservasi tidak valid.\n";
    } else {
        for (int i = index - 1; i < jumlahReservasi - 1; ++i) {
            daftarReservasi[i] = daftarReservasi[i + 1];
        }
        jumlahReservasi--;
        cout << "Reservasi berhasil dihapus.\n";
    }
}

// Fungsi menu reservasi restoran
void reservasiRestoran() {
    int pilihan;
    do {
        cout << "\n========== Reservasi Restoran ==========" << endl;
        cout << "1. Tambah Reservasi" << endl;
        cout << "2. Lihat Reservasi" << endl;
        cout << "3. Hapus Reservasi" << endl;
        cout << "4. Kembali ke Menu Utama" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahReservasi();
                break;
            case 2:
                lihatReservasi();
                break;
            case 3:
                hapusReservasi();
                break;
            case 4:
                cout << "Kembali ke Menu Utama.\n";
                break;
            default:
                cout << "Pilihan tidak valid, coba lagi.\n";
        }
    } while (pilihan != 4);
}

   void pemesananMenu() {
    if (jumlahReservasi == 0) {
        cout << "Tidak ada reservasi. Harap tambahkan reservasi terlebih dahulu.\n";
        return;
    }

    int nomorMeja;
    cout << "Masukkan nomor meja untuk memesan menu: ";
    cin >> nomorMeja;

    // Cari reservasi berdasarkan nomor meja
    int reservasiIndex = -1;
    for (int i = 0; i < jumlahReservasi; ++i) {
        if (daftarReservasi[i].nomorMeja == nomorMeja) {
            reservasiIndex = i;
            break;
        }
    }

    if (reservasiIndex == -1) {
        cout << "Nomor meja tidak ditemukan. Pastikan Anda telah membuat reservasi untuk meja tersebut.\n";
        return;
    }

    Reservasi &reservasi = daftarReservasi[reservasiIndex];

    // Struktur Data Menu Item
    struct MenuItem {
        string nama;
        int harga;
    };
    // Daftar Menu dalam Kategori
    const MenuItem makanan [] = {
        {"Nasi Goreng Kampung", 25000},
        {"Ayam Asam Manis", 30000},
        {"Beef Steak", 150000},
        {"Bak Mie Goreng", 25000},
        {"Cumi Goreng Mentega", 25000}
    };
    
    const MenuItem minuman [] = {
        {"Teh Mawar", 5000},
        {"Cappucino", 15000},
        {"Es Jeruk", 10000},
        {"Es Teh Manis", 6000},
        {"Es Milo", 15000}
    };
    
    const MenuItem dessert [] = {
        {"Tiramisu Cake", 25000},
        {"Caramel Dessert", 145000},
        {"Ice Cream", 25000},
        {"Donat Almond", 20000},
        {"Choco Puding", 35000}
    };
    
    const MenuItem paketCombo [] = {
        {"1 Ekor Ayam Asam Manis, 2 Nasi Putih, 2 Es Teh Manis, Donat Almond", 70000}
    };
    
    const MenuItem menuTambahan [] = {
        {"Nasi Putih", 10000},
        {"Lalapan", 10000},
        {"Sambel", 10000},
        {"Air Mineral", 10000}
    };
    
    // Deklarasi Variabel yang Digunakan 
    int pilihanKategori, pilihanMenu;
    char Pilihan;
    long long totalHarga = 0;
    int jumlahPesanan = 0;
    string totalMenu;
do {
    // Menampilkan Kategori
    cout << "Pilih Kategori Menu Yang Ingin Anda Pesan : " << endl;
    cout << "1. Makanan " << endl;
    cout << "2. Minuman " << endl;
    cout << "3. Dessert " << endl;
    cout << "4. PaketCombo " << endl;
    cout << "5. MenuTambahan " << endl;
    
    
     cout << "Masukkan Pilihan Menu (1-5) : ";
        cin >> pilihanKategori;
        cout << endl;
        
    // Menampilkan menu berdasarkan kategori
    if (pilihanKategori == 1) {
        cout << "\nMenu Makanan:\n";
        for (int i = 0; i < 5; i++) {
         cout << i + 1 << ". " << makanan[i].nama << " - Rp" << makanan[i].harga << endl;
        }
    }
        if (pilihanKategori == 2) {
        cout << "\nMenu Minuman:\n";
        for (int i = 0; i < 5; i++) {
         cout << i + 1 << ". " << minuman[i].nama << " - Rp" << minuman[i].harga << endl;
        }
    }
        if (pilihanKategori == 3) {
        cout << "\nMenu Dessert:\n";
        for (int i = 0; i < 5; i++) {
         cout << i + 1 << ". " << dessert[i].nama << " - Rp" << dessert[i].harga << endl;
        }
    }
        if (pilihanKategori == 4) {
        cout << "\nMenu Paket Combo:\n";
        for (int i = 0; i < 1; i++) {
         cout << i + 1 << ". " << paketCombo[i].nama << " - Rp" << paketCombo[i].harga << endl;
        }
    }
        if (pilihanKategori == 5) {
        cout << "\nMenu Makanan:\n";
        for (int i = 0; i < 4; i++) {
         cout << i + 1 << ". " << menuTambahan[i].nama << " - Rp" << menuTambahan[i].harga << endl;
        }
     }

    // Memilih menu dalam kategori
    char ulangi;
    do {
    cout << "Masukkan nomor menu yang ingin dipilih: ";
    cin >> pilihanMenu;
    
    //Meminta Jumlah Menu Yang Anda Pilih
    cout << "Masukkan jumlah pesanan: ";
    cin >> jumlahPesanan;

       if (pilihanKategori == 1 && pilihanMenu >= 1 && pilihanMenu <= 5) {
            totalHarga += makanan[pilihanMenu - 1].harga * jumlahPesanan;
            cout << makanan[pilihanMenu - 1].nama << " sebanyak " << jumlahPesanan << " ditambahkan ke pesanan. " << endl;
            //cout << "Total sementara: Rp" << totalHarga << endl;
            totalMenu += "- " + makanan[pilihanMenu - 1].nama + " x" + to_string(jumlahPesanan) + " = Rp" + to_string(makanan[pilihanMenu - 1].harga * jumlahPesanan) + "\n";

        } else if (pilihanKategori == 2 && pilihanMenu >= 1 && pilihanMenu <= 5) {
            totalHarga += minuman[pilihanMenu - 1].harga * jumlahPesanan;
            cout << minuman[pilihanMenu - 1].nama << " sebanyak " << jumlahPesanan << " ditambahkan ke pesanan. " << endl;
            //cout << "Total sementara: Rp" << totalHarga << endl;
            totalMenu += "- " + minuman[pilihanMenu - 1].nama + " x" + to_string(jumlahPesanan) + " = Rp" + to_string(minuman[pilihanMenu - 1].harga * jumlahPesanan) + "\n";
  
        } else if (pilihanKategori == 3 && pilihanMenu >= 1 && pilihanMenu <= 5) {
            totalHarga += dessert[pilihanMenu - 1].harga * jumlahPesanan;
            cout << dessert[pilihanMenu - 1].nama << " sebanyak " << jumlahPesanan << " ditambahkan ke pesanan. " << endl;
            //cout << "Total sementara: Rp" << totalHarga << endl;
            totalMenu += "- " + dessert[pilihanMenu - 1].nama + " x" + to_string(jumlahPesanan) + " = Rp" + to_string(dessert[pilihanMenu - 1].harga * jumlahPesanan) + "\n";

        } else if (pilihanKategori == 4 && pilihanMenu >= 1 && pilihanMenu <= 5) {
            totalHarga += paketCombo[pilihanMenu - 1].harga * jumlahPesanan;
            cout << paketCombo[pilihanMenu - 1].nama << " sebanyak " << jumlahPesanan << " ditambahkan ke pesanan. " << endl;
            //cout << "Total sementara: Rp" << totalHarga << endl;
            totalMenu += "- " + paketCombo[pilihanMenu - 1].nama + " x" + to_string(jumlahPesanan) + " = Rp" + to_string(paketCombo[pilihanMenu - 1].harga * jumlahPesanan) + "\n";

        } else if (pilihanKategori == 5 && pilihanMenu >= 1 && pilihanMenu <= 5) {
            totalHarga += menuTambahan[pilihanMenu - 1].harga * jumlahPesanan;
            cout << menuTambahan[pilihanMenu - 1].nama << " sebanyak " << jumlahPesanan << " ditambahkan ke pesanan. " << endl;
            //cout << "Total sementara: Rp" << totalHarga << endl;
            totalMenu += "- " + menuTambahan[pilihanMenu - 1].nama + " x" + to_string(jumlahPesanan) + " = Rp" + to_string(menuTambahan[pilihanMenu - 1].harga * jumlahPesanan) + "\n";
        } else {
          cout << "Pilihan menu tidak valid.\n";
        }

        //Pertanyaan Apakah Ingin Melanjutkan Memilih Atau Tidak
       cout << "Apakah Anda ingin memilih menu lagi dari kategori ini? (Y/T): ";
        cin >> ulangi;
      } while (ulangi == 'Y' || ulangi == 'y');
        cout << endl;
        
      // Menampilkan Total Menu Yang Sudah Dipilih
      cout << "Menu yang Anda Pilih : " << endl;
      cout << totalMenu << endl; 
      // Menampilkan Total Harga Sementara dari Semua Menu Yang Dipilih
      cout << "Total Sementara:" << endl;
      cout << "Rp " << totalHarga << endl;

      //Pertanyaan Apakah Ingin Lanjut Memesan Atau Tidak
      cout << "Apakah Ada Menu Yang Ingin Anda Pesan Lagi (Y/T) : ";
       cin >> Pilihan;
      } while (Pilihan != 'T' && Pilihan != 't');
      // Pertanyaan Apakah Ingin Menambahkan catatan khusus untuk menu
     
     // Meminta catatan khusus untuk menu
      cin.ignore(); // Membersihkan buffer input
       cout << "Apakah ada catatan khusus untuk menu ini? (Tekan Enter jika tidak ada): ";
       string catatan;
       getline(cin, catatan);     
      cout << endl;

      // Menampilkan Total Menu Yang Sudah Dipilih
      cout << "Menu yang Anda Pilih : " << endl;
      cout << totalMenu << endl; 
      
      // Menampilkan Total Harga Sementara dari Semua Menu Yang Dipilih
      cout << "Total Keseluruhan:" << " Rp " << totalHarga << endl;
      cout << "\n";
      //Menampilkan Catatan Yang Di Tambahkan
     if (catatan.empty()) {
     cout << "Tidak ada catatan khusus.\n"; //Jika Tidak Ada Catatan Khusus, maka ini yang akan ditampilkan
    } else {
     cout << "Catatan khusus: " << catatan << "\n";
     }
     // Menyimpan pesanan ke dalam reservasi
     daftarReservasi[jumlahReservasi - 1].pesananMenu = totalMenu;
     // Menyimpan total harga  ke dalam reservasi
     daftarReservasi[jumlahReservasi - 1].totalHarga = totalHarga;
     // Menyimpan catatan khusus ke dalam reservasi
     daftarReservasi[jumlahReservasi - 1].catatan = catatan;


     // Setelah selesai memesan, beri opsi pembayaran
     cout << "Anda telah memilih menu, sekarang lanjut ke pembayaran.\n";
     opsiPembayaran(); // Panggil fungsi pembayaran

}

// Fungsi pembayaran
void opsiPembayaran() {
    long long pembayaran;
    int opsi;
    
    // Total pembelian langsung menggunakan totalHarga dari pemesanan menu
    long long totalPembelian = daftarReservasi[jumlahReservasi - 1].totalHarga;

    cout << "=== Program Opsi Pembayaran ===" << endl;

    // Input data pengguna
    //cout << "Masukkan total pembelian: Rp ";
    //cin >> totalPembelian;

    // Pilihan opsi pembayaran
    cout << "\nPilih opsi pembayaran:" << endl;
    cout << "1. Cash" << endl;
    cout << "2. Kartu Kredit" << endl;
    cout << "Masukkan pilihan Anda (1 atau 2): ";
    cin >> opsi;

    if (opsi == 1) {
        cout << "\n=== Pembayaran Cash ===" << endl;
        cout << "Total yang harus dibayar: Rp " << totalPembelian << endl;

        cout << "Masukkan jumlah uang yang dibayar: Rp ";
        cin >> pembayaran;

        if (pembayaran >= totalPembelian) {
            cout << "Transaksi berhasil! Kembalian Anda: Rp " << pembayaran - totalPembelian << endl;
        } else {
            cout << "Uang tidak mencukupi. Transaksi dibatalkan." << endl;
        }
    } else if (opsi == 2) {
        cout << "\n=== Pembayaran Kredit ===" << endl;
        double bunga = 0.05; // bunga 5%
        long long totalKredit = totalPembelian + (totalPembelian * bunga);

        cout << "Total pembayaran (termasuk bunga 5%): Rp " << totalKredit << endl;
        cout << "Transaksi berhasil dengan pembayaran kredit." << endl;
    } else {
        cout << "\nPilihan tidak valid. Program selesai." << endl;
    }

    // Menyimpan metode pembayaran ke dalam daftarReservasi
    daftarReservasi[jumlahReservasi - 1].opsiPembayaran = (opsi == 1) ? "Cash" : " Kartu Kredit";
    cout << "Pembayaran dengan metode: " << daftarReservasi[jumlahReservasi - 1].opsiPembayaran << endl;
}

// Fungsi utama (menu utama)
int main() {
    int pilihan;
    do {
        cout << "\n========== Sistem Reservasi dan Pemesanan ==========" << endl;
        cout << "1. Reservasi Restoran" << endl;
        cout << "2. Pemesanan Menu" << endl;
        cout << "3. Opsi Pembayaran" << endl;
        cout << "4. Keluar" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                reservasiRestoran();
                break;
            case 2:
                pemesananMenu();
                break;
            case 3:
                opsiPembayaran();
                break;
            case 4:
                cout << "Terima kasih telah menggunakan sistem ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid, coba lagi.\n";
        }
    } while (pilihan != 4);

   return 0;
}
