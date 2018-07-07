/****************************************************************************
**					 SAKARYA ÜNÝVERSÝTESÝ
**			BÝLGÝSAYAR VE BÝLÝÞÝM BÝLÝMLERÝ FAKÜLTESÝ
**				BÝLGÝSAYAR MÜHENDÝSLÝÐÝ BÖLÜMÜ
**				  PROGRAMLAMAYA GÝRÝÞÝ DERSÝ
**
**				ÖDEV NUMARASI		: PROJE	
**				ÖÐRENCÝ ADI			: MUSTAFA YAYLALI	
**				ÖÐRENCÝ NUMARASI	: B140910051	
**				DERS GRUBU			: A
****************************************************************************/
#include <iostream>
#include <string>  // karakter ifadeler için
#include <fstream> // dosya iþlemi için
#include <iomanip> // setw için

using namespace std;

void menu()
{
	cout << "\n* * * * * * * ANA MENU * * * * * * *\n"<<endl;
	cout << "1- Hasta kaydi" << endl;
	cout << "2- Hasta kaydi guncelleme" << endl;
	cout << "3- Hasta silme" << endl;
	cout << "4- Randevu alma" << endl;
	cout << "5- Randevu silme" << endl;
	cout << "6- Randevu guncelleme" << endl;
	cout << "7- Hasta sorgulama" << endl;
	cout << "8- Hasta listesi alma" << endl;
	cout << "9- Hasta muayene kaydi" << endl;
	cout << "10- Cikis" << endl << endl;
	cout << "Ne yapmak istiyorsunuz ?  :";
}

int main()
{
	

	int secim;
	// hasta.txt dosyasýndakiler
	string tc_no;
	string hasta_adi;
	string hasta_soyadi;
	string hasta_tel;
	int hasta_yasi;
	char hasta_cinsiyet;

	// randevu .txt dosyasýndakiler
	string tarih;
	string doktor_adi;
	string saat;
	double ucret;

	// muayenede yer alacaklar
	string muayene_tahlil="-";  // randevu alýndýgýnda Muayene bilgileri bos kalmasýn diye
	string muayene_teshis="-";
	string muayene_ilac="-";

	char cevap = 'e'; // kayit eklerken tekrar eklensin mi sorusu için

	do
	{
		menu();
		cin >> secim;
		if (secim <= 0 || secim > 10) { cout << "\nLutfen gecerli bir secim yapiniz !" << endl; }; //secimin dogru yapilmasý saglaniyor

		if (secim == 1) // HASTA KAYIT 
		{
			ofstream dosya_yaz;
			dosya_yaz.open("Hasta.txt", ios::app);		// Hasta.txt olusturuyoruz eger dosya acýlmazsa donguye girmiyor
			if (!dosya_yaz) { cout << "Dosya acilmadi !!!"; }
			else {
				do
				{	
					cout << "\n------------HASTA KAYIT------------"<< endl;
					cout << "\nHasta Tc		:";			cin >> tc_no;
					cout << "Hasta Adi		:";			cin >> hasta_adi;
					cout << "Hasta Soyadi		:";		cin >> hasta_soyadi;
					cout << "Hasta Yasi		:";			cin >> hasta_yasi;
					cout << "Hasta Telefon Numarasi	:"; cin >> hasta_tel;
					cout << "Hasta Cinsiyet		:";		cin >> hasta_cinsiyet;

					dosya_yaz << tc_no << "	" << hasta_adi << '	' << hasta_soyadi << '	' << hasta_yasi << '	' << hasta_tel << '	' << hasta_cinsiyet << endl; //kullanýcýdan alýnan bilgileri dosyaya yaziyoruz
					cout << "\nHasta basari ile kaydedildi." << endl;
					cout << "\nBaska kayit yapicak misiniz? (e/h):";
					cin >> cevap;
				} while (cevap == 'e' || cevap == 'E');

				dosya_yaz.close();
				
			}
		}

		if (secim == 2) // HASTA GUNCELLEME
		{
			string tc_sorgu;
			int a = 0; // eger hasta var ise 1 olucak ve en son koþul(if) ile hasta bulunmadigi yazilir
			cout << "\n------------HASTA GUNCELLEME------------" << endl << endl;
			cout << "Hasta Tc no	:";	cin >> tc_sorgu;

			ifstream dosya_oku;
			dosya_oku.open("Hasta.txt", ios::app); // Hasta.txt dosyasini okuma modunda acýyoruz

			ofstream gecici;
			gecici.open("gecici.txt", ios::app); // guncelleme islemi icin gecici dosya acýyoruz

			string ifade = " "; // okurken en son ki veriyi tekrar yazmasýný engellemek için

			while (!dosya_oku.eof())
			{
				dosya_oku >> tc_no >> hasta_adi >> hasta_soyadi >> hasta_yasi >> hasta_tel >> hasta_cinsiyet;


				if (tc_no == tc_sorgu && tc_no != ifade) //ilk girisinde ifade tc ye eþit olacagý için bu sorguya 1 kere girmis olucak
				{
					cout << "\n---Hastanin Mevcut Bilgileri--- \n" << endl;
					cout << "Hasta Adi		:" << hasta_adi << endl;
					cout << "Hasta Soyadi		:" << hasta_soyadi << endl;
					cout << "Hasta Yasi		:" << hasta_yasi << endl;
					cout << "Hasta Telefon Numarasi	:" << hasta_tel << endl;
					cout << "Hasta Cinsiyet		:" << hasta_cinsiyet << endl;


					cout << "\n---Hastanin Yeni Bilgileri--- \n" << endl; //guncellenecek bilgileri alýyoruz
					cout << "Hasta Adi		:";			cin >> hasta_adi;
					cout << "Hasta Soyadi		:";		cin >> hasta_soyadi;
					cout << "Hasta Yasi		:";			cin >> hasta_yasi;
					cout << "Hasta Telefon Numarasi	:"; cin >> hasta_tel;
					cout << "Hasta Cinsiyet		:";		cin >> hasta_cinsiyet;

					gecici << tc_no << "	" << hasta_adi << '	' << hasta_soyadi << '	' << hasta_yasi << '	' << hasta_tel << '	' << hasta_cinsiyet << "\n"; // kullanicidan alinan bilgileri gecici dosyaya yaziyoruz

					a = 1; // bu degerin 1 olmasi hastanin olduðunu belirtiyor


					ifade = tc_no; //bu koþula bir daha girmemesi icin
					continue;

				}

				if (tc_no != tc_sorgu && tc_no != ifade) // en son ki veriyi tekrar yazmasýný engellemek için
				{
					gecici << tc_no << "	" << hasta_adi << '	' << hasta_soyadi << '	' << hasta_yasi << '	' << hasta_tel << '	' << hasta_cinsiyet << endl;
					ifade = tc_no;
				}


			}
			gecici.close();
			dosya_oku.close();
			remove("Hasta.txt");  // gecici dosyadakileri asil dosyaya ceviriyoruz
			rename("gecici.txt", "Hasta.txt"); //dosya isim degisikligi
			if (a == 0) { cout << "\nHasta bulunamadi !" << endl; }
			if (a == 1) { cout << "\nBasari ile guncellendi."<<endl; }
		}

		if (secim == 3) // HASTA SÝLME
		{
			string tc_sorgu; //kullanýcýdan alýncak tc
			int a = 0; // hastanýn bulunup bulunmadýgýný anlamak için
			cout << "\n------------HASTA SILME------------" << endl << endl;
			cout << "Hasta Tc no	:";
			cin >> tc_sorgu;

			ofstream gecici;  //gecici dosyayý yazma modunda olusturuyoruz
			gecici.open("gecicisil.txt", ios::app);

			ifstream dosya_oku;
			dosya_oku.open("Hasta.txt", ios::app);

			string ifade = " "; // okurken en son ki veriyi tekrar yazmasýný engellemek için

			while (!dosya_oku.eof())

			{
				dosya_oku >> tc_no >> hasta_adi >> hasta_soyadi >> hasta_yasi >> hasta_tel >> hasta_cinsiyet; //dosyadan verileri okuyoruz

				if (tc_no != tc_sorgu && tc_no != ifade)
				{
					gecici << tc_no << "	" << hasta_adi << '	' << hasta_soyadi << '	' << hasta_yasi << '	' << hasta_tel << '	' << hasta_cinsiyet << "\n";
					ifade = tc_no;
				}
				if (tc_no == tc_sorgu && tc_no!=ifade)
				{
					//////////////////////////////RANDEVU SÝLME ÝÞLEMÝ YAPILCAK
					ifstream dosyaoku2;
					dosyaoku2.open("Randevu.txt", ios::app);
					while (!dosyaoku2.eof())
					{
						dosyaoku2 >> tc_no >> tarih >> doktor_adi >> saat >> ucret >> muayene_tahlil >> muayene_teshis >> muayene_ilac;
						if (tc_no != tc_sorgu  && tc_no != ifade)
						{
							ofstream gecici_sil;
							gecici_sil.open("gecicisil2.txt", ios::app);
							gecici_sil << tc_no << " " << tarih << ' ' << doktor_adi << ' ' << saat << ' ' << ucret << '	' << muayene_tahlil << '	' << muayene_teshis << '	' << muayene_ilac << "\n";
							gecici_sil.close();
							ifade = tc_no; //son veriyi 2 kez yazmamasi için
						}
					}
					dosyaoku2.close();
					
					ifade = tc_no; //if þartýna 2 kere girmemesi için
					a = 1; // bu degerin 1 olmasi silinecek bir hasta kaydinin olduðunu belirtiyor}
				}
			}
			remove("Randevu.txt");
			rename("gecicisil2.txt", "Randevu.txt");

			gecici.close();
			dosya_oku.close();
			remove("Hasta.txt");
			rename("gecicisil.txt", "Hasta.txt");
			if (a == 0) { cout << "\nHasta bulunamadi !" << endl; }
			if (a == 1) { cout << "\nHasta basari ile silindi..." << endl; }
		}

		if (secim == 4)  // RANDEVU ALMA
			{
				string TC;
				int a = 0; // hasta olup olmadýgýný anlamak için
				cout << "\n------------RANDEVU ALMA------------" << endl << endl;
				cout << "Hasta TC :"; cin >> TC;
				
				ifstream DosyaOku("Hasta.txt");
				
				while (!DosyaOku.eof())
				{
					DosyaOku >> tc_no >> hasta_adi >>hasta_soyadi >> hasta_yasi >> hasta_tel >> hasta_cinsiyet;
					if (TC == tc_no) //hasta var ise randevu sorulcak
					{
						cout << "\n---Hastanin Mevcut Bilgileri--- \n" << endl;
						cout << "TC no		:" << tc_no << endl;
						cout << "Adi		:" << hasta_adi << endl;
						cout << "Soyadi		:" << hasta_soyadi << endl;
						cout << "Yasi		:" << hasta_yasi << endl;
						cout << "Telefonu	:" << hasta_tel << endl;
						cout << "Cinsiyeti	:" << hasta_cinsiyet << endl;
						cout << "\nRandevu istiyor mu? (e/h):";
						cin >> cevap;
						if (cevap == 'e')
						{
							DosyaOku.close();
							ofstream DosyaYaz;
							DosyaYaz.open("Randevu.txt", ios::app);
							cout << "\n---Randevu Bilgileri--- \n" << endl;
							cout << "Tarih		:"; cin >> tarih;
							cout << "Doktor Adi	:"; cin >> doktor_adi;
							cout << "Saat		:"; cin >> saat;
							cout << "Muayene Ucreti	:"; cin >> ucret;
							DosyaYaz << tc_no << " " << tarih << ' ' << doktor_adi << ' '<< saat << ' ' << ucret << '	' <<muayene_tahlil << '	' << muayene_teshis << '	' << muayene_ilac << "\n";
							DosyaYaz.close();
							a = 1; // randevu alýndýgýný belirtiyor
							break;
						}
						else
						{
							a = 2;
							cout << "\nRandevu islemi iptal edildi.."<<endl;
							break;
						}		
					}			
				}
				if (a == 0) // HASTANIN BULUNMADIGINI BELÝRTÝYOR ONCE HASTA KAYIT SONRA RANVDEVU ÝÞLEMÝ
				{
					cout << "\nHasta bulunamadi.Yeni hasta kayit islemi yapilacak ve sonra randevu alinacak !." << endl;
					////////////// HASTA KAYIT /////
					ofstream dosya_yaz;
					dosya_yaz.open("Hasta.txt", ios::app);		// Hasta.txt olusturuyoruz eger dosya acýlmazsa donguye girmiyor
					if (!dosya_yaz) { cout << "Dosya acilmadi !!!"; }
					else {
						
							cout << "\n------------HASTA KAYIT------------" << endl;
							cout << "\nHasta Tc		:"<<TC<<endl;
							cout << "Hasta Adi		:";			cin >> hasta_adi;
							cout << "Hasta Soyadi		:";		cin >> hasta_soyadi;
							cout << "Hasta Yasi		:";			cin >> hasta_yasi;
							cout << "Hasta Telefon Numarasi	:"; cin >> hasta_tel;
							cout << "Hasta Cinsiyet		:";		cin >> hasta_cinsiyet;

							dosya_yaz << TC << "	" << hasta_adi << '	' << hasta_soyadi << '	' << hasta_yasi << '	' << hasta_tel << '	' << hasta_cinsiyet << endl; //kullanýcýdan alýnan bilgileri dosyaya yaziyoruz
							cout << "\nHasta basari ile kaydedildi." << endl;
						dosya_yaz.close();
					////HASTA KAYIT-SON//////////////
					
					////RANDEVU KAYIT////
					
						ofstream DosyaYaz;
						DosyaYaz.open("Randevu.txt", ios::app);
						cout << "\n---Randevu Bilgileri--- \n" << endl;
						cout << "Tarih		:"; cin >> tarih;
						cout << "Doktor Adi	:"; cin >> doktor_adi;
						cout << "Saat		:"; cin >> saat;
						cout << "Muayene Ucreti	:"; cin >> ucret;
						DosyaYaz << TC << " " << tarih << ' ' << doktor_adi << ' ' << saat << ' ' << ucret << '	' << muayene_tahlil << '	' << muayene_teshis << '	' << muayene_ilac << "\n";
						DosyaYaz.close();
						a = 1; // randevu alýndýgýný belirtiyor
					/// RANDEVU KAYIT-SON///////
					}
				}
				if (a == 1) { cout << "\nBasari ile randevu alindi..." << endl; }
			}
			
		if (secim == 5) //RANDEVU SÝLME
			{
				string ifade = " ";
				int h = 0; // hastanýn olup olmadýgýný kontrol icin
				int r = 0; // randevunun olup olmadýgýný kontrol icin
				string Tc;
				cout << "\n------------RANDEVU SILME------------" << endl << endl;
				cout << "Hasta Tc	:"; cin >> Tc;
				ifstream dosyaoku;
				dosyaoku.open("Hasta.txt",ios::app);
				while (!dosyaoku.eof())
				{
						dosyaoku >> tc_no >> hasta_adi >> hasta_soyadi >> hasta_yasi >> hasta_tel >> hasta_cinsiyet;
						if (tc_no == Tc  && tc_no != ifade)
						{
							cout << "\n---Hastanin Mevcut Bilgileri--- \n" << endl;
							cout << "TC no		:" << tc_no << endl;
							cout << "Adi		:" << hasta_adi << endl;
							cout << "Soyadi		:" << hasta_soyadi << endl;
							cout << "Yasi		:" << hasta_yasi << endl;
							cout << "Telefonu	:" << hasta_tel << endl;
							cout << "Cinsiyeti	:" << hasta_cinsiyet << endl;
							
							ifstream dosyaoku2;
							dosyaoku2.open("Randevu.txt", ios::app);
							
							
								while (!dosyaoku2.eof())
								{
									dosyaoku2 >> tc_no >> tarih >> doktor_adi >> saat >> ucret >> muayene_tahlil >> muayene_teshis >> muayene_ilac;
									if (tc_no != Tc  && tc_no != ifade)
									{
										ofstream gecici_sil;
										gecici_sil.open("gecicisil.txt", ios::app);
										gecici_sil << tc_no << " " << tarih << ' ' << doktor_adi << ' ' << saat << ' ' << ucret << '	' << muayene_tahlil << '	' << muayene_teshis << '	' << muayene_ilac << "\n";
										gecici_sil.close();
										ifade = tc_no; //son veriyi 2 kez yazmamasi için
									}
									if (tc_no == Tc  && tc_no != ifade)
									{
										cout << "\nRandevu basari ile silindi..." << endl;
										ifade = tc_no; //son veriyi 2 kez yazmamasi için
										r = 1;
									}
								}
							
							dosyaoku2.close();
							h = 1;
							ifade = tc_no;

						}
				}
				dosyaoku.close();
				if (h != 1) { cout << "\nHasta bulunamadi !"<<endl; }
				if (h == 1)
				{
					remove("Randevu.txt");
					rename("gecicisil.txt", "Randevu.txt");
				}
				if (r != 1) { cout << "\nRandevu bulunmamaktadir !" << endl; }
			}
			
		if (secim == 6) // RANDEVU GUNCELLEME
			{
				string ifade = " ";
				int h = 0; // hastanýn olup olmadýgýný kontrol icin
				int r = 0; // randevunun olup olmadýgýný kontrol icin
				string Tc;
				cout << "\n------------RANDEVU GUNCELLEME------------" << endl << endl;
				cout << "Hasta Tc	:"; cin >> Tc;
				ifstream dosyaoku;
				dosyaoku.open("Hasta.txt", ios::app);
				while (!dosyaoku.eof())
				{
					dosyaoku >> tc_no >> hasta_adi >> hasta_soyadi >> hasta_yasi >> hasta_tel >> hasta_cinsiyet;
					if (tc_no == Tc  && tc_no != ifade)
					{
						cout << "\n---Hastanin Mevcut Bilgileri--- \n" << endl;
						cout << "TC no		:" << tc_no << endl;
						cout << "Adi		:" << hasta_adi << endl;
						cout << "Soyadi		:" << hasta_soyadi << endl;
						cout << "Yasi		:" << hasta_yasi << endl;
						cout << "Telefonu	:" << hasta_tel << endl;
						cout << "Cinsiyeti	:" << hasta_cinsiyet << endl;

						ifstream dosyaoku2;
						dosyaoku2.open("Randevu.txt", ios::app);

						ofstream gecici_sil;
						gecici_sil.open("gecicisil.txt", ios::app);

						while (!dosyaoku2.eof())
						{
							dosyaoku2 >> tc_no >> tarih >> doktor_adi >> saat >> ucret >> muayene_tahlil >> muayene_teshis >> muayene_ilac;
							if (tc_no != Tc  && tc_no != ifade)
							{
								
								gecici_sil << tc_no << " " << tarih << ' ' << doktor_adi << ' ' << saat << ' ' << ucret << '	' << muayene_tahlil << '	' << muayene_teshis << '	' << muayene_ilac << "\n";
								
								ifade = tc_no; //son veriyi 2 kez yazmamasi için
							}
							if (tc_no == Tc && tc_no != ifade)
							{
								cout << "\n---Yeni Randevu Bilgileri--- \n" << endl;
								cout << "Tarih		:"; cin >> tarih;
								cout << "Doktor Adi	:"; cin >> doktor_adi;
								cout << "Saat		:"; cin >> saat;
								cout << "Muayene Ucreti	:"; cin >> ucret;
								gecici_sil << tc_no << " " << tarih << ' ' << doktor_adi << ' ' << saat << ' ' << ucret << '	' << muayene_tahlil << '	' << muayene_teshis << '	' << muayene_ilac << "\n";

								cout << "\nRandevu basari ile guncellendi..."<<endl;
								ifade = tc_no; //son veriyi 2 kez yazmamasi için
							}
						}
						gecici_sil.close();
						dosyaoku2.close();
						h = 1;
						ifade = tc_no;

						if (r != 2) { cout << "\nRandevu bulunamadi !"<<endl; } // Randevu var mý yok mu?
						
					}
				}
				dosyaoku.close();
				if (h != 1) { cout << "\nHasta bulunamadi !" << endl; }
				if (h == 1)
				{
					remove("Randevu.txt");
					rename("gecicisil.txt", "Randevu.txt");
				}

			}
		
		if (secim == 7) // HASTA SORGULAMA
			{
				cout << "\n------------HASTA SORGULAMA------------" << endl << endl;
				string TC;
				string ifade = " ";
				int m = 0,n=0;
				cout << "Hasta TC :"; cin >> TC;
				ifstream dosyaoku;
				dosyaoku.open("Hasta.txt");
				while (!dosyaoku.eof())
				{
					dosyaoku >> tc_no >> hasta_adi >> hasta_soyadi >> hasta_yasi >> hasta_tel >> hasta_cinsiyet;
					if (TC == tc_no) //hasta var mý?
					{
						cout << "\n---Hastanin Mevcut Bilgileri--- \n" << endl;
						cout << "TC no		:" << tc_no << endl;
						cout << "Adi		:" << hasta_adi << endl;
						cout << "Soyadi		:" << hasta_soyadi << endl;
						cout << "Yasi		:" << hasta_yasi << endl;
						cout << "Telefonu	:" << hasta_tel << endl;
						cout << "Cinsiyeti	:" << hasta_cinsiyet << endl;
						m = 1;

						ifstream oku_randevu;
						oku_randevu.open("Randevu.txt");
						if (oku_randevu)
						{
							cout << "\n---Hastanin Randevu ve Muayene Bilgileri--- \n" << endl;
							cout << setw(10) << "Tarih" << setw(13) << "Doktor Adi" << setw(14) << "Saat" << setw(15) << "Ucret" <<setw(16)<<"Tahlil"<<setw(17)<<"Teshis"<<setw(18)<<"Ilac"<< endl;
							cout << setw(10) << "__________" << setw(13) << "___________" << setw(14) <<"_____" << setw(15) <<"______" << setw(16) <<"______" << setw(17) << "______" << setw(18) << "______" << endl;
							while (!oku_randevu.eof())
							{
								oku_randevu >> tc_no >> tarih >> doktor_adi >> saat >> ucret >> muayene_tahlil >> muayene_teshis >> muayene_ilac;
								if (TC == tc_no && tarih != ifade) //-randevu tarihleri farklý-.   ayný hastanýn randevularýný göstermek icin
								{
									cout << setw(10) << tarih << setw(13) << doktor_adi << setw(14) << saat << setw(15) << ucret << setw(16) << muayene_tahlil << setw(17) << muayene_teshis<< setw(18) << muayene_ilac<< endl;
									
									n = 1;
									ifade = tarih;
								}
							}
						}
						oku_randevu.close();
					}	
				}
				dosyaoku.close();
				if (m == 0)
				{
					cout << "\nHasta bulunamadi !!!" << endl;
				}
				if (m==1 && n==0)
				{
					cout << "\nHastaya ait randevu bulunamadi !!!" << endl;
				}
			}
			
		if (secim == 8) // HASTA LÝSTESÝ ALMA
			{
				string ifade =" ";
				
				ifstream dosyaoku;
				dosyaoku.open("Hasta.txt");
				if (dosyaoku)
				{
					cout << "\n------------HASTA LISTESI------------" << endl << endl;
					cout << setw(4) << "Tc" << setw(11) << "Adi" << setw(14) << "Soyadi" << setw(15) << "Telefon No" << endl;
					cout << setw(4) << "___" << setw(11) << "______" << setw(14) << "_______" << setw(15) << "_______" << endl;
					while (!dosyaoku.eof())
					{
						dosyaoku >> tc_no >> hasta_adi >> hasta_soyadi >> hasta_yasi >> hasta_tel >> hasta_cinsiyet;
						if (tc_no != ifade)
						{
							cout << setw(4) << tc_no << setw(11) << hasta_adi << setw(14) << hasta_soyadi << setw(15) << hasta_tel << endl;
							ifade = tc_no; // En son ki veriyi tekrar okumamasý için
						}
					}
				}
				else cout << "\nKayitli hasta bulunamadi !!"<<endl;
				dosyaoku.close();
			}
			
		if (secim == 9) // HASTA MUAYENE KAYDI
			{
				string ifade = " ";
				int h = 0; // hastanýn olup olmadýgýný kontrol icin
				int r = 0; // randevunun olup olmadýgýný kontrol icin
				string Tc;
				cout << "\n------------HASTA MUAYENE KAYDI------------" << endl << endl;
				cout << "Hasta Tc	:"; cin >> Tc;
				ifstream dosyaoku;
				dosyaoku.open("Hasta.txt", ios::app);
				while (!dosyaoku.eof())
				{
					dosyaoku >> tc_no >> hasta_adi >> hasta_soyadi >> hasta_yasi >> hasta_tel >> hasta_cinsiyet;
					if (tc_no == Tc  && tc_no != ifade)
					{
						cout << "\n---Hastanin Mevcut Bilgileri--- \n" << endl;
						cout << "TC no		:" << tc_no << endl;
						cout << "Adi		:" << hasta_adi << endl;
						cout << "Soyadi		:" << hasta_soyadi << endl;
						cout << "Yasi		:" << hasta_yasi << endl;
						cout << "Telefonu	:" << hasta_tel << endl;
						cout << "Cinsiyeti	:" << hasta_cinsiyet << endl;

						ifstream dosyaoku2;
						dosyaoku2.open("Randevu.txt", ios::app);

						ofstream gecici_sil;
						gecici_sil.open("gecicisil.txt", ios::app);

						while (!dosyaoku2.eof())
						{
							dosyaoku2 >> tc_no >> tarih >> doktor_adi >> saat >> ucret >> muayene_tahlil >> muayene_teshis >> muayene_ilac;
							if (tc_no != Tc  && tc_no != ifade)
							{
							
								gecici_sil << tc_no << " " << tarih << ' ' << doktor_adi << ' ' << saat << ' ' << ucret << '	' << muayene_tahlil << '	' << muayene_teshis << '	' << muayene_ilac << "\n";

								ifade = tc_no; //son veriyi 2 kez yazmamasi için
							}
							if (tc_no == Tc && tc_no != ifade) // HASTANANIN RANDEVUSU VAR ÝSE MUAYENE KAYDINI EKLÝYORUZ
							{
								cout << "\n---Muayene Kayit Bilgileri--- \n" << endl;
								cout << "Tahlil		:"; cin >> muayene_tahlil;
								cout << "Teshis		:"; cin >> muayene_teshis;
								cout << "Ilac		:"; cin >> muayene_ilac;
								
								gecici_sil << tc_no << " " << tarih << ' ' << doktor_adi << ' ' << saat << ' ' << ucret << '	' << muayene_tahlil << '	' << muayene_teshis << '	' << muayene_ilac << "\n";

								cout << "\nMuayene kaydi basari ile yapildi..." << endl;
								ifade = tc_no; //son veriyi 2 kez yazmamasi için
							}
						}
						gecici_sil.close();
						dosyaoku2.close();
						h = 1;
						ifade = tc_no;

						if (r != 2) { cout << "\nRandevu bulunamadi !"<<endl; } // Randevu var mý yok mu?
						
					}
				}
				dosyaoku.close();
				if (h != 1) { cout << "\nHasta bulunamadi !" << endl; }
				if (h == 1)
				{
					remove("Randevu.txt");
					rename("gecicisil.txt", "Randevu.txt");
				}
			}
			
		if (secim == 10) // programdan CIKIS
			{
				exit(0);
			}
		
		} while (secim != 10);

		cin.get();
		cin.ignore();
		return 0;
	
}