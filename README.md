# Migration of a Database Engine: From C to C++

Bu proje, temel bir veritabanı motorunun **Prosedürel C** dilinden **Modern Nesne Yönelimli C++** diline olan göç (migration) sürecini sergiler. 

##  Projenin Amacı
Aynı işlevselliği iki farklı dilde geliştirerek aralarındaki mimari farkları, bellek yönetimini ve modern yazılım pratiklerini (Modern C++) karşılaştırmalı olarak göstermek.

---

##  Teknik Karşılaştırma

| Özellik | C Versiyonu (Procedural) | C++ Versiyonu (Modern OOP) |
| :--- | :--- | :--- |
| **Veri Yapısı** | Singly Linked List (Manuel) | `std::vector` (STL Container) |
| **Bellek Yönetimi** | `malloc`, `free` | Otomatik (RAII) & `new`/`delete` |
| **Giriş/Çıkış** | `scanf`, `fwrite` (Binary) | `fstream`, Operator Overloading (Text) |
| **Silme Mantığı** | Manuel Pointer manipülasyonu | `std::remove_if` (Lambda Expression) |

---
Kriter,C (Legacy),C++ (Modern),Analiz Notu
Hız (10k Kayıt),~0.0016 sn,~0.0036 sn,"C, saf işaretçi kullanımıyla hafif önde."
Bellek Yönetimi,Manuel (malloc/free),Otomatik (RAII / Vector),C++ bellek sızıntılarını (leak) %100 engeller.
Kod Karmaşıklığı,Yüksek (Bağlı Liste),Düşük (Kütüphane Desteği),C++ kodunun bakımı ve geliştirilmesi çok daha kolay.
Veri Güvenliği,Yok (Çökme riski),Var (Try-Catch / Validation),C++ versiyonu hatalı girişlerde sistemi ayakta tutar.
---

##  Klasör Yapısı

- **/C_Core**: İşaretçi tabanlı, bağlı liste kullanılan çekirdek kodlar.
- **/CPP_Modern**: Vektörler, sınıflar ve lambda fonksiyonları kullanılan modern implementasyon.

##  Nasıl Çalıştırılır?
Her iki versiyon da standart bir C/C++ derleyicisi (GCC/Clang/MSVC) ile derlenebilir:
```bash
# C Versiyonu için:
gcc C_Core/main.c -o c_database

# C++ Versiyonu için:
g++ CPP_Modern/main.cpp -o cpp_database
