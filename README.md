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
Pada folder YOUTUBER, setiap membuat folder permission foldernya akan otomatis menjadi 750. Juga ketika membuat file permissionnya akan otomatis menjadi 640 dan ekstensi filenya akan bertambah “.iz1”. File berekstensi “.iz1” tidak bisa diubah permissionnya dan memunculkan error bertuliskan “File ekstensi iz1 tidak boleh diubah permissionnya.”

Jawab : 

Kami sudah mencoba mengerjakannya, namun kami masih bingung cara memakai fungsi-fungsi fuse seperti xmp_mkdir, xmp_create, dll sehingga belom ada yang bisa dikerjakan dari nomor 4 ini. Kami tahu bahwa soal ini pasti menggunakan xmp_mkdir, xmp_create, dan xmp_chown namun kami masih bingung untuk memasukkan apa saja ke dalam fungsi-fungsi itu.

# SOAL 5
Ketika mengedit suatu file dan melakukan save, maka akan terbuat folder baru bernama Backup kemudian hasil dari save tersebut akan disimpan pada backup dengan nama namafile_[timestamp].ekstensi. Dan ketika file asli dihapus, maka akan dibuat folder bernama RecycleBin, kemudian file yang dihapus beserta semua backup dari file yang dihapus tersebut (jika ada) di zip dengan nama namafile_deleted_[timestamp].zip dan ditaruh ke dalam folder RecycleBin (file asli dan backup terhapus). Dengan format [timestamp] adalah yyyy-MM-dd_HH:mm:ss

- Untuk nomor 5, kelompok kami belum sempat mencoba untuk mengerjakan karena disaat yang bersamaan, kelompok kami memiliki banyak tugas yang baru diberikan minggu ini dan deadlinenya di minggu ini juga. Kita sudah sempat mencermati soalnya, namun masih belum terpikirkan cara untuk menyelesaikannya.
