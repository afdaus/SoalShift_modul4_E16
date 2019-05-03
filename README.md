# SoalShift_modul4_E16
# SOAL 1
Semua nama file dan folder harus terenkripsi
Enkripsi yang Atta inginkan sangat sederhana, yaitu Caesar cipher. Namun, Kusuma mengatakan enkripsi tersebut sangat mudah dipecahkan. Dia menyarankan untuk 				 
character list diekspansi,tidak hanya alfabet, dan diacak. Berikut character list yang dipakai:

qE1~ YMUR2"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\8s;g<{3.u*W-0

Misalkan ada file bernama “halo” di dalam folder “INI_FOLDER”, dan key yang dipakai adalah 17, maka:
“INI_FOLDER/halo” saat belum di-mount maka akan bernama “n,nsbZ]wio/QBE#”, saat telah di-mount maka akan otomatis terdekripsi kembali menjadi “INI_FOLDER/halo” .
Perhatian: Karakter ‘/’ adalah karakter ilegal dalam penamaan file atau folder dalam *NIX, maka dari itu dapat diabaikan

Jawab :
- Jadi kami membuat fungsi enkripsi dan dekripsi sendiri dengan menggunakan character list di atas sebagai acuan. 
- Selanjutnya diatur pemakaian fungsi enkripsi dan dekripsi tersebut dalam xmp_readdir dan xmp_getattr sesuai permintaan soal.
- Dekripsi yang terdapat dalam xmp_readdir akan menampilkan nama file di folder tujuan dengan kondisi sudah di dekripsi.
- Lalu dalam xmp_getattr dimasukkan fungsi enkripsi supaya file dapat menemukan lokasi sesungguhnya dengan nama semula.

# SOAL 2
Semua file video yang tersimpan secara terpecah-pecah (splitted) harus secara otomatis tergabung (joined) dan diletakkan dalam folder “Videos”
Urutan operasi dari kebutuhan ini adalah:
- Tepat saat sebelum file system di-mount
  1.	Secara otomatis folder “Videos” terbuat di root directory file system
  2.	Misal ada sekumpulan file pecahan video bernama “computer.mkv.000”, “computer.mkv.001”, “computer.mkv.002”, dst. Maka secara otomatis file pecahan tersebut akan di-join menjadi file video “computer.mkv”
Untuk mempermudah kalian, dipastikan hanya video file saja yang terpecah menjadi beberapa file. File pecahan tersebut dijamin terletak di root folder fuse
  3.	Karena mungkin file video sangat banyak sehingga mungkin saja saat menggabungkan file video, file system akan membutuhkan waktu yang lama untuk sukses ter-mount. Maka pastikan saat akan menggabungkan file pecahan video, file system akan membuat 1 thread/proses(fork) baru yang dikhususkan untuk menggabungkan file video tersebut
  4.	Pindahkan seluruh file video yang sudah ter-join ke dalam folder “Videos”
  5.	Jangan tampilkan file pecahan di direktori manapun
- Tepat saat file system akan di-unmount
  1.	Hapus semua file video yang berada di folder “Videos”, tapi jangan hapus file pecahan yang terdapat di root directory file system
  2.	Hapus folder “Videos” 
  
- Langkah
  1. Mengatur init agar dapat membuat folder Videos jika belum ada.
  2. Membuat thread yang dapat menggabungkan video.
  3. Untuk menghapus Videos dapat menggunakan destroy dan fungsi remove_directory.
# SOAL 3
Sebelum diterapkannya file system ini, Atta pernah diserang oleh hacker LAPTOP_RUSAK yang menanamkan user bernama “chipset” dan “ic_controller” serta group “rusak” yang tidak bisa dihapus. Karena paranoid, Atta menerapkan aturan pada file system ini untuk menghapus “file bahaya” yang memiliki spesifikasi:
Owner Name 	: ‘chipset’ atau ‘ic_controller’
Group Name	: ‘rusak’
Tidak dapat dibaca
Jika ditemukan file dengan spesifikasi tersebut ketika membuka direktori, Atta akan menyimpan nama file, group ID, owner ID, dan waktu terakhir diakses dalam file “filemiris.txt” (format waktu bebas, namun harus memiliki jam menit detik dan tanggal) lalu menghapus “file bahaya” tersebut untuk mencegah serangan lanjutan dari LAPTOP_RUSAK.
- Untuk menyelesaikan soal nomor 3, maka terlebih dahulu kitamengambil owner dan group name dari sebuah file. Hal ini dapat dilakukan dengan menggunakan `getpwuid(st.st_uid)` untuk mengambil namawner, dan `getgrgid(st.st_uid)` untuk mengambil nama group.
- Untuk mengambil file yang sesuai dengan permintaan soal, maka dapat menggunakan `strcmp`, serta menggunakan `st.st_atime` untuk mengambil waktu diaksesnya sebuah file. Setelah itu, untuk memasukkan ke dalam file, maka dapat menggunakan `FILE` pada c, dan menggunakan `fprintf` untuk mencetak ke dalam file tersebut.

# SOAL 4
Pada folder YOUTUBER, setiap membuat folder permission foldernya akan otomatis menjadi 750. Juga ketika membuat file permissionnya akan otomatis menjadi 640 dan ekstensi filenya akan bertambah “.iz1”. File berekstensi “.iz1” tidak bisa diubah permissionnya dan memunculkan error bertuliskan “File ekstensi iz1 tidak boleh diubah permissionnya.”

Jawab : 

Fungsi yang digunakan : mkdir, create, chmod, ekstension(untuk thread)

Penjelasan :
Jadi untuk membuat folder yang permission foldernya akan otomatis menjadi 750 akan berada pada fungsi mkdir. Dari path yang ada akan dicek apakah ada /YOUTUBER di path tersebut, jika ada maka folder akan otomatis terbuat dengan file permission 750 (-rwxr-x---). Sedangkan file yang dibuat permissionnya akan otomatis menjadi 640, akan berada pada fungsi create. Prinsipnya sama seperti fungsi mkdir, jika menemukan string /YOUTUBER maka file permission akan otomatis diubah menjadi 640. Lalu selain mkdir dan create kami memakai fungsi lain yaitu fungsi chmod untuk mengecek file yang berada pada folder YOUTUBER, jika ekstensionnya .iz1 maka file permission tersebut tidak dapat diubah. 

# SOAL 5
Ketika mengedit suatu file dan melakukan save, maka akan terbuat folder baru bernama Backup kemudian hasil dari save tersebut akan disimpan pada backup dengan nama namafile_[timestamp].ekstensi. Dan ketika file asli dihapus, maka akan dibuat folder bernama RecycleBin, kemudian file yang dihapus beserta semua backup dari file yang dihapus tersebut (jika ada) di zip dengan nama namafile_deleted_[timestamp].zip dan ditaruh ke dalam folder RecycleBin (file asli dan backup terhapus). Dengan format [timestamp] adalah yyyy-MM-dd_HH:mm:ss

Jawab :

Fungsi yang digunakan : write, unlink

Penjelasan :
Dalam fungsi write, jika ada file-file yang diupdate maka folder bernama BackUp akan otomatis terbuat dan isi dari BackUp itu adalah isi file yang sudah terupdate.
Sedangkan dalam fungsi unlink, pada saat file di hapus, akan terbuat folder RecycleBin secara otomatis untuk menampung file yang di hapus setelah di zip terlebih dahulu. Setelah dipindah ke RecycleBin, file asli akan terhapus.
