# Parallel Array Summation using Pthreads

Program ini menjumlahkan elemen-elemen array secara paralel menggunakan Pthreads (POSIX Threads) dalam bahasa C.

## 📌 Fitur

- Input interaktif:
  - Ukuran array (hingga 100 juta elemen)
  - Jumlah thread (maksimal 32)
  - Metode inisialisasi: semua elemen bernilai 1 atau acak (`rand() % 10`)
- Pemrosesan paralel dengan Pthreads
- Output hasil penjumlahan setiap thread
- Total penjumlahan seluruh array dan waktu eksekusi

## ▶️ Cara Menjalankan

### Kompilasi

```bash
gcc -o sum_array_pthreads sum_array_pthreads.c -lpthread
