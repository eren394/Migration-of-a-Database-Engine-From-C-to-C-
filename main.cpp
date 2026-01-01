#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

// 1. Ürün Nesnesi Tanımı
class Urun {
public:
    int id;
    string ad;
    float fiyat;
    float alisFiyati;
    int adet;

    Urun(int _id = 0, string _ad = "", float _fiyat = 0.0, float _alis = 0.0, int _adet = 0) 
        : id(_id), ad(_ad), fiyat(_fiyat), alisFiyati(_alis), adet(_adet) {}

    // Dosya ve ekran işlemleri için operatörler
    friend ostream& operator<<(ostream& os, const Urun& u) {
        os << u.id << " " << u.ad << " " << u.fiyat << " " << u.alisFiyati << " " << u.adet;
        return os;
    }
};

// 2. Veritabanı Yönetim Sistemi
class VeritabaniModern {
private:
    vector<Urun> urunler;
    float toplamKar = 0;

public:
    // Hata Yönetimi: Güvenli sayı alma fonksiyonu
    float sayiAl(string mesaj) {
        string input;
        float deger;
        while (true) {
            cout << mesaj;
            cin >> input;
            try {
                deger = stof(input);
                if (deger < 0) throw 1;
                return deger;
            } catch (...) {
                cout << "!! Gecersiz giris. Pozitif bir sayi giriniz: ";
            }
        }
    }

    void ekle(int id, string ad, float satis, float alis, int miktar) {
        for (auto& u : urunler) {
            if (u.id == id) {
                u.adet += miktar;
                cout << ">> Stok guncellendi." << endl;
                return;
            }
        }
        urunler.push_back(Urun(id, ad, satis, alis, miktar));
        cout << ">> Yeni urun eklendi." << endl;
    }

    void sil(int id) {
        auto size_before = urunler.size();
        urunler.erase(remove_if(urunler.begin(), urunler.end(),
            [id](const Urun& u){ return u.id == id; }), urunler.end());
        
        if (urunler.size() < size_before) cout << ">> Urun silindi." << endl;
        else cout << "!! Urun bulunamadi." << endl;
    }

    void listele() {
        if (urunler.empty()) {
            cout << "\nListe su an bos!" << endl;
            return;
        }
        cout << "\n--- GUNCEL STOK LISTESI ---" << endl;
        for (const auto& u : urunler) {
            cout << "ID: " << u.id << " | Ad: " << u.ad 
                 << " | Satis: " << u.fiyat << " | Alis: " << u.alisFiyati 
                 << " | Adet: " << u.adet << endl;
        }
    }

    void fiyataGoreSirala() {
        sort(urunler.begin(), urunler.end(), [](const Urun& a, const Urun& b) {
            return a.fiyat < b.fiyat;
        });
        cout << ">> Fiyata gore siralandi." << endl;
    }

    void urunAra(string kelime) {
        bool bulundu = false;
        for (const auto& u : urunler) {
            if (u.ad.find(kelime) != string::npos) {
                cout << "ID: " << u.id << " | Ad: " << u.ad << " | Adet: " << u.adet << endl;
                bulundu = true;
            }
        }
        if (!bulundu) cout << "!! Sonuc bulunamadi." << endl;
    }

    void satisYap(int id, int miktar) {
        for (auto& u : urunler) {
            if (u.id == id) {
                if (u.adet >= miktar) {
                    u.adet -= miktar;
                    toplamKar += (u.fiyat - u.alisFiyati) * miktar;
                    cout << ">> Satis yapildi. Kar: " << (u.fiyat - u.alisFiyati) * miktar << " TL" << endl;
                } else {
                    cout << "!! Yetersiz stok!" << endl;
                }
                return;
            }
        }
        cout << "!! Urun bulunamadi." << endl;
    }

    void karRaporu() {
        cout << "\n--- FINANSAL DURUM ---" << endl;
        cout << "Toplam Net Kar: " << fixed << setprecision(2) << toplamKar << " TL" << endl;
    }

    void kaydet() {
        ofstream dosya("veritabani.txt");
        dosya << toplamKar << endl; // İlk satıra toplam kârı yazalım
        for (const auto& u : urunler) {
            dosya << u.id << " " << u.ad << " " << u.fiyat << " " << u.alisFiyati << " " << u.adet << endl;
        }
        dosya.close();
    }

    void yukle() {
        ifstream dosya("veritabani.txt");
        if (!dosya) return;
        
        dosya >> toplamKar; // Önce kârı oku
        int id, adet; string ad; float satis, alis;
        while (dosya >> id >> ad >> satis >> alis >> adet) {
            urunler.push_back(Urun(id, ad, satis, alis, adet));
        }
        dosya.close();
    }
};

// 3. Ana Program Döngüsü
int main() {
    VeritabaniModern db;
    db.yukle();

    int secim;
    string girdi;

    do {
        cout << "\n--- NEXBASE V2.0 (MODERN CPP) ---" << endl;
        cout << "1-Ekle | 2-Sil | 3-Listele | 4-Sirala | 5-Ara | 6-Satis | 7-Kar Raporu | 8-Cikis" << endl;
        cout << "Secim: ";
        cin >> girdi;

        try { secim = stoi(girdi); } catch (...) { secim = 0; }

        if (secim == 1) {
            int id = db.sayiAl("ID: ");
            string ad; cout << "Ad: "; cin >> ad;
            float satis = db.sayiAl("Satis Fiyati: ");
            float alis = db.sayiAl("Alis Fiyati: ");
            int miktar = db.sayiAl("Miktar: ");
            db.ekle(id, ad, satis, alis, miktar);
        }
        else if (secim == 2) {
            int id = db.sayiAl("Silinecek ID: ");
            db.sil(id);
        }
        else if (secim == 3) db.listele();
        else if (secim == 4) { db.fiyataGoreSirala(); db.listele(); }
        else if (secim == 5) {
            string ad; cout << "Aranacak kelime: "; cin >> ad;
            db.urunAra(ad);
        }
        else if (secim == 6) {
            int id = db.sayiAl("Urun ID: ");
            int miktar = db.sayiAl("Adet: ");
            db.satisYap(id, miktar);
        }
        else if (secim == 7) db.karRaporu();
        else if (secim == 8) {
            db.kaydet();
            cout << "Veriler kaydedildi. Gorusmek uzere!" << endl;
        }
        else cout << "!! Gecersiz secim." << endl;

    } while (secim != 8);

    return 0;
}