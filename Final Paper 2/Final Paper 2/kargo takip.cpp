#include <iomanip> 
#include <cstring> 
#include <stdlib.h>
#include <conio.h>
#include <stdio.h> 
#include <fstream>                  
#include <iostream>

using namespace std;

struct Kargo
{
    char kargo_id[20];
    char gonderen_ad[80];
    char alici_ad[80];
    char durum[20];   // "Yolda", "Teslim Edildi", "Beklemede" vb.
};

void KargoEkle();
void KargoListeleme();
void KargoArama();
void KargoSil();
void KargoDuzenle();

int main(){
    char anamenu;
    do{
        system("cls");
        
        cout << "|-------Kargo Takip Sistemi------|" << endl ;
        cout << "|      Secim Yapiniz             |" << endl ;
        cout << "|   1- Kargo Ekleme              |" << endl ;
        cout << "|   2- Kargo Listeleme           |" << endl ;
        cout << "|   3- Kargo Arama               |" << endl;
        cout << "|   4- Kargo Sil                 | " << endl;
        cout << "|   5- Kargo Durumunu Düzenle    |" << endl;
        cout << "|--------------------------------|"<< endl ;
        
        char secim;
        cin >> secim;
        
        switch(secim) 
        {
            case '1': 
                KargoEkle();
                break;    
            case '2': 
                KargoListeleme();
                break;
            case '3': 
                KargoArama();
                break;
            case '4': 
                KargoSil();
                break;
            case '5': 
                KargoDuzenle();
                break;
        }
        
        cout << "Ana Menuye Donmek icin: a basin cikmak icin: c" << endl ; 
        anamenu = getche();
        
    } while (anamenu == 'a');

    return 0;
}

Kargo kargo;

void KargoEkle()
{
    ofstream yaz("kargo.dat", ios::binary | ios::app);
    char secim;
    int adet = 0;

    do {
        cout << "Kargo ID Giriniz: " << endl;
        cin >> kargo.kargo_id;
        cout << "Gonderen Adi Giriniz: " << endl;
        cin >> kargo.gonderen_ad;
        cout << "Alici Adi Giriniz: " << endl;
        cin >> kargo.alici_ad;
        cout << "Kargo Durumu Giriniz (Yolda/Teslim Edildi/Beklemede ): " << endl;
        cin >> kargo.durum;
        
        yaz.write((char*)&kargo, sizeof(kargo));    
        adet++;    
        cout << "Baska Kargo Eklemek Istermisiniz? (E/H): " << endl;
        secim = getche();
        cout << endl;
    } while(secim == 'e' || secim == 'E');
    
    cout << adet << " adet Kargo Ekledi.." << endl;
    yaz.close();
}

void KargoListeleme()
{
    ifstream oku("kargo.dat", ios::binary | ios::app);
    
    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(kargo);
    cout << "Toplam Kargo Kayit Sayisi: " << kayits << endl;
    
    if(kayits > 0)
    {
        for(int i = 0; i < kayits; i++)
        {
            oku.seekg(i * sizeof(kargo));
            oku.read((char*)&kargo, sizeof(kargo));  
            
            cout << i+1 << ". Kargo Bilgileri" << endl;
            cout << "Kargo ID: " << kargo.kargo_id << endl;
            cout << "Gonderen Adi: " << kargo.gonderen_ad << endl;
            cout << "Alici Adi: " << kargo.alici_ad << endl;
            cout << "Kargo Durumu: " << kargo.durum << endl;
        }
    }
    else
    {
        cout << "Kayit Bulunamadi..." << endl;
    }
    oku.close();
}

void KargoArama()
{
    ifstream oku("kargo.dat", ios::binary | ios::app);
    
    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(kargo);

    cout << "Aranan Kargo ID'sini Giriniz: " << endl;
    char kargo_id[20];
    cin >> kargo_id;
    
    if(kayits > 0)
    {
        for(int i = 0; i < kayits; i++)
        {
            oku.seekg(i * sizeof(kargo));
            oku.read((char*)&kargo, sizeof(kargo));
            
            if(strcmp(kargo.kargo_id, kargo_id) == 0)
            {
                cout << "Bulunan Kargo Bilgileri" << endl;
                cout << "Kargo ID: " << kargo.kargo_id << endl;
                cout << "Gonderen Adi: " << kargo.gonderen_ad << endl;
                cout << "Alici Adi: " << kargo.alici_ad << endl;
                cout << "Kargo Durumu: " << kargo.durum << endl;
            }
        }
    }
    else
    {
        cout << "Kayit Bulunamadi..." << endl;
    }
    oku.close();
}

void KargoSil()
{
    char kargo_id[20];
    char secim = ' ';
    bool var = false;
    
    ifstream oku("kargo.dat", ios::binary | ios::app);
    oku.seekg(0, ios::end);
    int kayitsayisi = oku.tellg() / sizeof(kargo);
    
    cout << "Silmek Istediginiz Kargo ID'sini Giriniz: ";
    cin >> kargo_id;
    
    for(int i = 0; i < kayitsayisi; i++)
    {
        oku.seekg(i * sizeof(kargo));
        oku.read((char*)&kargo, sizeof(kargo));
        
        if(strcmp(kargo.kargo_id, kargo_id) == 0)
        {
            cout << "\nKargo Bilgileri: " << endl;
            cout << "Kargo ID: " << kargo.kargo_id << endl;
            cout << "Gonderen Adi: " << kargo.gonderen_ad << endl;
            cout << "Alici Adi: " << kargo.alici_ad << endl;
            cout << "Durum: " << kargo.durum << endl;
            
            cout << "\nSilmek Istediginiz Kayit Bu Mu? (E/H): ";
            secim = getche();
            if(secim == 'E' || secim == 'e')
            {
                var = true;
            }
        }
    }
    oku.close();
    
    if(var)
    {
        remove("kargo.dat");
        rename("Yedek.dat", "kargo.dat");
        cout << "\nKargo Kaydi Silindi." << endl;
    }
    else
    {
        cout << "\nKargo Kaydi Bulunamadi!" << endl;
    }
}

void KargoDuzenle()
{
    char kargo_id[20];
    char secim = ' ';
    bool var = false;
    
    ifstream oku("kargo.dat", ios::binary | ios::app);
    oku.seekg(0, ios::end);
    int kayitsayisi = oku.tellg() / sizeof(kargo);
    
    cout << "Duzeltmek Istediginiz Kargo ID'sini Giriniz: ";
    cin >> kargo_id;
    
    for(int i = 0; i < kayitsayisi; i++)
    {
        oku.seekg(i * sizeof(kargo));
        oku.read((char*)&kargo, sizeof(kargo));
        
        if(strcmp(kargo.kargo_id, kargo_id) == 0)
        {
            cout << "\nKargo Bilgileri: " << endl;
            cout << "Kargo ID: " << kargo.kargo_id << endl;
            cout << "Gonderen Adi: " << kargo.gonderen_ad << endl;
            cout << "Alici Adi: " << kargo.alici_ad << endl;
            cout << "Durum: " << kargo.durum << endl;
            
            cout << "\nDuzeltmek Istediginiz Kayit Bu Mu? (E/H): ";
            secim = getche();
            if(secim == 'E' || secim == 'e')
            {
                var = true;
                cout << "\nYeni Gonderen Adini Giriniz: ";
                cin >> kargo.gonderen_ad;
                cout << "Yeni Alici Adini Giriniz: ";
                cin >> kargo.alici_ad;
                cout << "Yeni Durumu Giriniz: ";
                cin >> kargo.durum;
            }
        }
    }
    oku.close();
    
    if(var)
    {
        ofstream dosya("Yedek.dat", ios::app | ios::binary);
        dosya.write((char*)&kargo, sizeof(kargo));
        dosya.close();
        
        remove("kargo.dat");
        rename("Yedek.dat", "kargo.dat");
        cout << "\nKargo Kaydi Duzeltildi." << endl;
    }
    else
    {
        cout << "\nKargo Kaydi Bulunamadi!" << endl;
    }
}

