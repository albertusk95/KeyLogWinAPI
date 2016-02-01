Teknis Running Program
--------------------------
Albertus Kelvin / 13514100
--------------------------

1. Program dijalankan oleh file exe yang berada di folder bin. 
2. File teks dengan format YYYYMMDD-HHMMSS.txt akan terbentuk jika sebuah keystroke terdeteksi. 
   Jika saat dijalankan tidak ada keystroke yang terdeteksi, maka file teks tidak akan muncul.
   Jika ingin file teks muncul saat program di-run, bisa lewat CMDPrompt dengan cara meng-compile ulang
   source code (KeyLogger.cpp) di folder src dan langsung di run lewat CMDPrompt
3. Saat dijalankan, program akan merekam semua keystroke.
4. Program diberhentikan dengan cara menekan tombol kombinasi '[Ctrl]c' pada file exe, tombol 'close', atau lewat
   'End Task' pada Task Manager.
5. Data keystroke akan disimpan di dalam file teks yang sudah terbentuk sebelumnya dengan format output yang kami buat 
   sebagai berikut:
	- Judul file teks -> "Hasil rekaman keystroke per detik"
	- Log activity yang dikelompokkan ke dalam blok waktu yang memiliki format YYYY:MM:DD-HH:MM:DD [info lain]
	- Program akan membagi data keystroke menjadi beberapa blok waktu secara PER DETIK. Jadi, setiap 1 detik akan
	  dibuat sebuah blok waktu baru untuk menyimpan data keystroke
	- [info lain] akan berisi [Start] bila user memulai penekanan tombol. Hal ini memakai prinsip jika selang waktu	
	  antara sebuah keystroke dengan keystroke lain lebih dari 1 detik, maka akan dibentuk sebuah sesi rekaman baru
	  yang ditandai dengan [Start]
	- Contoh: 
		Hasil rekaman keystroke per detik
		---------------------------------

		2016:01:30-10:20:20 [Start]
		program[Space]mulai
		
		2016:01:30-10:20:21
		[Space]merekam[Space]
	
		2016:01:30-10:20:22
		keystrokeEnter

		2016:01:30-10:20:30 [Start]
		Caps LockMulai[Space]sesi

		2016:01:30-10:20:31
		[Space]baruEnter
	- Antara 10:20:22 dan 10:20:30 berbeda lebih dari 1 detik, maka dibuat sebuah sesi baru untuk rekaman keystroke
	  yang dimulai pada 10:20:30
	- Antara 10:20:22 dan 10:20:30 bisa dikatakan bahwa user tidak mengetik apapun pada keyboard