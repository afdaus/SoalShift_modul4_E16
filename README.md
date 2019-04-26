# SoalShift_modul4_E16
# SOAL 1
# SOAL 2
# SOAL 3
Sebelum diterapkannya file system ini, Atta pernah diserang oleh hacker LAPTOP_RUSAK yang menanamkan user bernama “chipset” dan “ic_controller” serta group “rusak” yang tidak bisa dihapus. Karena paranoid, Atta menerapkan aturan pada file system ini untuk menghapus “file bahaya” yang memiliki spesifikasi:
Owner Name 	: ‘chipset’ atau ‘ic_controller’
Group Name	: ‘rusak’
Tidak dapat dibaca
Jika ditemukan file dengan spesifikasi tersebut ketika membuka direktori, Atta akan menyimpan nama file, group ID, owner ID, dan waktu terakhir diakses dalam file “filemiris.txt” (format waktu bebas, namun harus memiliki jam menit detik dan tanggal) lalu menghapus “file bahaya” tersebut untuk mencegah serangan lanjutan dari LAPTOP_RUSAK.

- Untuk menyelesaikan soal nomor 3, maka terlebih dahulu kita mengambil owner dan group name dari sebuah file. Hal ini dapat dilakukan dengan menggunakan `getpwuid(st.st_uid)` untuk mengambil nama owner, dan `getgrgid(st.st_uid)` untuk mengambil nama group.
- Untuk mengambil file yang sesuai dengan permintaan soal, maka dapat menggunakan `strcmp`, serta menggunakan `st.st_atime` untuk mengambil waktu diaksesnya sebuah file. Setelah itu, untuk memasukkan ke dalam file, maka dapat menggunakan `FILE` pada c, dan menggunakan `fprintf` untuk mencetak ke dalam file tersebut.
- Untuk nomor 3, kelompok kami masih belum benar, terutama karna file yang seharusnya tidak dimasukkan ke dalam folder tujuan itu tetap muncul pada folder tujuan, serta pada filemiris.txt file yang bersangkutan masih terbaca ownernya sebagai kami.
# SOAL 4
# SOAL 5
Ketika mengedit suatu file dan melakukan save, maka akan terbuat folder baru bernama Backup kemudian hasil dari save tersebut akan disimpan pada backup dengan nama namafile_[timestamp].ekstensi. Dan ketika file asli dihapus, maka akan dibuat folder bernama RecycleBin, kemudian file yang dihapus beserta semua backup dari file yang dihapus tersebut (jika ada) di zip dengan nama namafile_deleted_[timestamp].zip dan ditaruh ke dalam folder RecycleBin (file asli dan backup terhapus). Dengan format [timestamp] adalah yyyy-MM-dd_HH:mm:ss

- Untuk nomor 5, kelompok kami belum sempat mencoba untuk mengerjakan karena disaat yang bersamaan, kelompok kami memiliki banyak tugas yang baru diberikan minggu ini dan deadlinenya di minggu ini juga. Kita sudah sempat mencermati soalnya, namun masih belum terpikirkan cara untuk menyelesaikannya.
