# SoalShift_modul2_C04

##  No. 1
1.  Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
Catatan : Tidak boleh menggunakan crontab.

PENJELASAN:
```
while(1){
	long int i;
	struct dirent *file;
    	DIR *dr = opendir("/home/haikal/Modul2/raw/");
   	while ((file = readdir(dr)) != NULL)
	{
		char direct[256]="/home/haikal/Modul2/raw/";
		
		i=strlen(file->d_name);
       	 	char newdirect[256]="/home/haikal/Modul2/gambar/";
		char newName[256]="";

		if(file->d_name[i-1]=='g' && file->d_name[i-2]=='n' && file->d_name[i-3]=='p'&& file->d_name[i-4]=='.')
		{
			for(i=0;i<strlen(file->d_name)-4;i++)
			{
				newName[i]=file->d_name[i];
			}
		  strcat(direct,file->d_name);
		  strcat(newName,"_grey.png");
		  strcat(newdirect,newName);
		  rename(direct, newdirect);
		}
	}
 	sleep(5);
  }
  exit(EXIT_SUCCESS);
}
```
-   Buat folder Modul2 dulu dan buat Modul2/raw/

-   ```struct dirent *file; DIR *dr = opendir("/home/haikal/Modul2/raw/");```untuk mengakses directory
-   Selanjutnya masuk ke kondisi perulangan, kita buka asal directory foldernya. 
-   variabel i digunakan untuk mengecek panjang dari nama file.  buat variabel newdirect untuk menyimpan karakter "/home/haikal/Modul2/gambar/"
-   ketika saat dibaca filenya ada, maka kita buat ngecek menggunakan strstr jika sama dengan .png
-   Jika iya, maka kita memisahkan nama file dengan png. Lalu kita menduplicate nama baru dengan nama lama. Nama lama ditambahin .png, sedangkan nama baru ditambahkan _grey.png. Lalu digabungkan directory lama dengan nama lama dan directory baru dengan nama baru.
-   Langkah terakhir gunakan fungsi rename untuk mengganti nama sekaligus memindahkan file



##  No. 2
2.  Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
Catatan: Tidak boleh menggunakan crontab
PENJELASAN:
    -   Pertama lakukan proses pembuatan daemon seperti yang ada pada modul sisop karena kita perlu mengecek setiap 3 detik. Fungsi sleep() mempunyai parameter dalam satuan detik yang digunakan untuk mengecek program setiap 3 detik. 
    -   Kemudian lakukan inisialisasi direktori dan syarat. 
    ```
    char direktori[]="/home/andhika/sisop19/modul2/hatiku/elen.ku";
    char syarat[]="www-data";
    ```
    -   lalu kita chmod() file tersebut berdasarkan permission 0777, yang berarti USER,GROUP,OTHER memiliki permission read, write, dan execute
    ```
    chmod (direktori, 0777);
    ```
    -   lalu memanggil fungsi getpwuid() dan disimpan pada struct passwd untuk mendapatkan struct yang berisi nama dari UID tersebut, dan fungsi getgrgid() dan disimpan pada struct group untuk mendapatkan struct yang berisi nama dari GID tersebut
    ```
    struct stat info;
    stat(direktori, &info);  // Error check omitted
    struct passwd *pw = getpwuid(info.st_uid);
    struct group  *gr = getgrgid(info.st_gid);
    ```
    -   Selanjutnya adalah mengcompare apakah pw_name dan gr_name bernilai sama dengan www-data dengan strcmp(). Apabila hasilnya bernilai true maka lakukan remove file elen.ku
    ```
     if(strcmp(pw->pw_name,syarat)==0 && strcmp(gr->gr_name,syarat)==0)
      remove(direktori);
    ```

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


``` 
    char direktori[]="/home/andhika/Documents/makanan/makan_enak.txt";
    struct stat nama;
    stat(direktori, &nama);
    time_t x = nama.st_atime; //waktu akses
    time_t y = time(NULL); //waktu program berjalan
    
    if(difftime(y, x)<=30) // kiri-kanan{
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
```

PENJELASAN:
-   langkah pertama masukan direktori yang dituju yaitu "/home/andhika/Documents/makanan/makan_enak.txt" pada variabel bernama direktori
-   struct stat digunakan untuk mendapatkan informasi mengenai atribut dari sebuah file
-   masuk ke kondisi percabangan, apabila hasil selisih diatara kedua bilangan tersebut kurang dari 30 maka:
-   buat variabel bertipe karakter dengan nama x tujuannya untuk menyalin nilai bertipe integer dari variabel i ke dalam bentuk karakter
-   setelah itu buat variabel bertipe char dengan nama direktori2 untuk memasukkan direktori nama file yang akan dibuat yaitu "/home/andhika/Documents/makanan/makan_sehat"; gabungkan variabel x tadi ke bagian belakang variabel direktori2 kemudian simpan di variabel direktori2 lalu gabungkan text ".txt" dengan direktori2. 
-   Kemudian buat file dengan letak direktori sesuai dengan variabe direktori2
-   program tersebut selalu berjalan setiap 5 detik


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

-   Pertama, kita mengcopy waktu dengan format dd:mm:yyyy-HH:MM ke dalam variable char my_time menggunakan 

```
strftime(my_time, sizeof(my_time), "%d:%m:%Y-%H:%M", tmp);
```
-   Selanjutnya, my_time akan dicopy kedalam variable untuk nama folder, disini kami menggunakan namaFolder yang berisi direktori dari folder tersebut. Jika sudah, maka folder tersebut akan dibuat dengan mkdir seperti berikut dengan tambahan syarat i sebagai counter menit % 30 = 0 yang artinya setiap 30 menit akan dibuat folder baru.

```
if(i%30 == 0)
	{
		strcpy(namaFolder,my_time);
		strcpy(path,"/home/haikal/Modul2/log/");
		strcat(path,namaFolder);
		strcat(path, "/");
		mkdir(path, 0777);
	}
```

-   Untuk membuat nama file digunakan logno sebagai indeks dari log dan menyimpan format nama pada string namaFile sebagai berikut

```
int logno = i+1;
char newLog[100];
sprintf(newLog, "log%d", logno);
strcat(newLog,".log");
strcpy(namaFile, path);
strcat(namaFile, newLog);
```

-   Terakhir, untuk mengcopy seluruh isi dari syslog ke file tersebut digunakan FILE dan fopen pada syslog dan log baru tesebut dengan ketentuan syslog yang di read dan log baru yang di write. Untuk mengcopy seluruh isi tersebut digunakan fgetc dan fputc. kemudian fclose semua file tersebut. kode seperti berikut

```
FILE *slog, *nlog;
int c;
slog=fopen("/var/log/syslog", "r");
nlog=fopen(namaFile, "w");
while(1){
	    c=fgetc(slog);
            if(feof(slog)){
                break;
            }
            fputc(c, nlog);
}
fclose(slog);
fclose(nlog);
```

-   Seluruh program tersebut dimasukkan kedalam daemon dengan sleep(60) (60 detik) dan mengincrement nilai i sebagai minute counter.

-   untuk menghentikan program tersebut digunakan pkill -9, berhubung proses tersebut bernama soal5a, maka dapat digunakan program seperti berikut

```
int main(){
	char *argv[] = {"pkill", "-9", "soal5a", NULL};
	execv("/usr/bin/pkill", argv);
}
```
