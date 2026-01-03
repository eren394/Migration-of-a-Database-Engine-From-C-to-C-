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
Bu proje, bir "Legacy" (eski) sistemin modern yazılım mimarisine göç sürecini ve sonuçlarını kapsar.

    Hız ve Performans: 10.000 kayıt testinde C versiyonu 0.0016 sn, C++ versiyonu ise 0.0036 sn sonuç vermiştir. Aradaki fark mikrosaniye düzeyinde olup, C++'ın sunduğu mimari avantajlar için kabul edilebilir bir maliyettir.

    Bellek Güvenliği: Manuel bellek yönetimi (C) yerine otomatik bellek yönetimine (C++ RAII/Vector) geçilerek bellek sızıntıları ve çökme riskleri tamamen ortadan kaldırılmıştır.

    Sürdürülebilirlik: Karmaşık işaretçi (pointer) operasyonları yerini standart kütüphane fonksiyonlarına bırakmış, kodun okunabilirliği ve geliştirilme hızı artırılmıştır.

    Hata Yönetimi: Eski sistemdeki çökme riskine karşın, yeni sisteme eklenen Try-Catch blokları ve Input Validation ile yazılımın çalışma kararlılığı (robustness) en üst seviyeye çıkarılmıştır.
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
