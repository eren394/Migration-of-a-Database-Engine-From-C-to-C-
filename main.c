#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Urun {
    int id;
    char urunAdi[50];
    float fiyat;
    struct Urun *next;
} Urun;

Urun *head = NULL;

#include <time.h>

void c_performans_testi() {
    clock_t start = clock();
    
    for(int i = 0; i < 10000; i++) {
        urunEkle(i, "Test", 10.0);
    }
    
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("C Bagli Liste 10.000 kayit suresi: %f saniye\n", cpu_time_used);
}

void urunEkle(int id, char *ad, float fiyat) {
    Urun *kontrol = head;
    while (kontrol != NULL) {
        if (kontrol->id == id) {
            printf("\nHATA: Bu ID (%d) zaten mevcut!\n", id);
            return;
        }
        kontrol = kontrol->next;
    }

    Urun *yeni = (Urun*)malloc(sizeof(Urun));
    yeni->id = id;
    strcpy(yeni->urunAdi, ad);
    yeni->fiyat = fiyat;
    yeni->next = NULL;

    if (head == NULL) {
        head = yeni;
    } else {
        Urun *temp = head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = yeni;
    }
    printf(">> %s basariyla eklendi.\n", ad);
}

void listele() {
    Urun *temp = head;
    if(temp == NULL) {
        printf("\nListe su an bos!\n");
        return;
    }
    printf("\n--- GUNCEL STOK LISTESI ---\n");
    while (temp != NULL) {
        printf("ID: %d | Ad: %-15s | Fiyat: %.2f TL\n", temp->id, temp->urunAdi, temp->fiyat);
        temp = temp->next;
    }
}

void verileriKaydet() {
   FILE *dosya = fopen("veritabani.bin", "wb");
    if (!dosya) return;

    Urun *temp = head;
    while (temp != NULL) {
        // Okurken yaptığın sırayla tek tek yazıyoruz
        fwrite(&temp->id, sizeof(int), 1, dosya);
        fwrite(temp->urunAdi, sizeof(char), 50, dosya);
        fwrite(&temp->fiyat, sizeof(float), 1, dosya);
        
        temp = temp->next;
    }
    fclose(dosya);
    printf("\n>> Veriler guvenli bir sekilde diske yazildi.");
}

void urunSil(int silinecekId) {
    Urun *temp = head, *onceki = NULL;

    if (temp != NULL && temp->id == silinecekId) {
        head = temp->next;
        free(temp);
        printf(">> Urun silindi.\n");
        return;
    }
    while (temp != NULL && temp->id != silinecekId) {
        onceki = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf(">> Urun bulunamadi!\n");
        return;
    }
    onceki->next = temp->next;
    free(temp);
    printf(">> Urun silindi.\n");

}

void verileriYukle() {
    FILE *fp = fopen("veritabani.bin", "rb");
    if (!fp) return;
    int id; char ad[50]; float fiyat;
    while (fread(&id, sizeof(int), 1, fp) == 1) {
        fread(ad, sizeof(char), 50, fp);
        fread(&fiyat, sizeof(float), 1, fp);
        urunEkle(id, ad, fiyat);
    }
    fclose(fp);
}

// Güvenli şekilde bir satır oku ve sonundaki yeni satırı kırp
int read_input(char *buf, size_t size) {
    if (fgets(buf, size, stdin) == NULL) return 0;
    buf[strcspn(buf, "\r\n")] = 0;
    return 1;
}

void bellegiTemizle() {
    Urun *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    verileriYukle();
    int secim, id;
    char ad[50];
    float fiyat;
    char girdi[64]; // Kullanıcının seçimini geçici olarak tutacak

    do {
        printf("\n1-Ekle | 2-Sil | 3-Listele | 4-Cikis\nSecim: ");

        if (!read_input(girdi, sizeof girdi)) break;
        secim = (int)strtol(girdi, NULL, 10);

        if (secim == 1) {
            printf("ID: ");
            if (!read_input(girdi, sizeof girdi)) continue;
            id = (int)strtol(girdi, NULL, 10);

            printf("Ad: ");
            if (!read_input(ad, sizeof ad)) continue;

            printf("Fiyat: ");
            if (!read_input(girdi, sizeof girdi)) continue;
            fiyat = strtof(girdi, NULL);

            urunEkle(id, ad, fiyat);
        } else if (secim == 2) {
            printf("Silinecek ID: ");
            if (!read_input(girdi, sizeof girdi)) continue;
            id = (int)strtol(girdi, NULL, 10);
            urunSil(id);
        } else if (secim == 3) {
            listele();
        } else if (secim != 4) {
            printf("Gecersiz secim!\n");
        }
    } while (secim != 4);

    verileriKaydet();
    printf("Gorusmek uzere!\n");
    return 0;
}