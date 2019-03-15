# SoalShift_modul2_C04

##  No. 1
1.  Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
Catatan : Tidak boleh menggunakan crontab.


PENJELASAN:

##  No. 2
2.  Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
Catatan: Tidak boleh menggunakan crontab
PENJELASAN:
    -   Pertama lakukan proses pembuatan daemon seperti yang ada pada modul sisop karena kita perlu mengecek setiap 3 detik. Fungsi sleep() mempunyai parameter dalam satuan detik yang digunakan untuk mengecek program setiap 3 detik. 
    -   Kemudian lakukan inisialisasi direktori dan syarat. 
    ``
    char direktori[]="/home/andhika/sisop19/modul2/hatiku/elen.ku";
    char syarat[]="www-data";
    ``
    -   lalu kita chmod() file tersebut berdasarkan permission 0777, yang berarti USER,GROUP,OTHER memiliki permission read, write, dan execute
    ``
    chmod (direktori, 0777);
    ``
    -   lalu memanggil fungsi getpwuid() dan disimpan pada struct passwd untuk mendapatkan struct yang berisi nama dari UID tersebut, dan fungsi getgrgid() dan disimpan pada struct group untuk mendapatkan struct yang berisi nama dari GID tersebut
    ``
    struct stat info;
    stat(direktori, &info);  // Error check omitted
    struct passwd *pw = getpwuid(info.st_uid);
    struct group  *gr = getgrgid(info.st_gid);
    ``
    -   Selanjutnya adalah mengcompare apakah pw_name dan gr_name bernilai sama dengan www-data dengan strcmp(). Apabila hasilnya bernilai true maka lakukan remove file elen.ku
    ``
     if(strcmp(pw->pw_name,syarat)==0 && strcmp(gr->gr_name,syarat)==0)
      remove(direktori);
    ``

##  No. 3
3.  Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 
Buatlah program C yang dapat :
    i.  mengekstrak file zip tersebut.
    ii. menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. 
Catatan:  
- Gunakan fork dan exec.
- Gunakan minimal 3 proses yang diakhiri dengan exec.
- Gunakan pipe
- Pastikan file daftar.txt dapat diakses dari text editor

PENJELASAN:

##  No. 4
4.  Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).
Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.
Contoh:
File makan_enak.txt terakhir dibuka pada detik ke-1
Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt

Catatan: 
dilarang menggunakan crontab
Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst

``
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

#include <time.h>
//template from modul 2 daemon
int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  int i=1;
  while(1) 
  {
    
    char direktori[]="/home/andhika/Documents/makanan/makan_enak.txt";
    struct stat nama;
    stat(direktori, &nama);
    time_t x = nama.st_atime; //waktu akses
    time_t y = time(NULL); //waktu program berjalan
    
    if(difftime(y, x)<=30) // kiri-kanan
    {
      char x[100];
      sprintf(x, "%d", i);

      char direktori2[]="/home/andhika/Documents/makanan/makan_sehat";
      strcat(direktori2, x);
      strcat(direktori2,".txt");
      
      FILE *makanan = fopen(direktori2, "w"); 
      fclose(makanan);
      i++;
    }
    //waktu program
    sleep(5);
  }
  
  exit(EXIT_SUCCESS);
}
``

PENJELASAN:


##  No. 5
5.  Kerjakan poin a dan b di bawah:
Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
Ket:
Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
Per menit memasukkan log#.log ke dalam folder tersebut
‘#’ : increment per menit. Mulai dari 1
Buatlah program c untuk menghentikan program di atas.
NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.

PENJELASAN:
