#include <stdio.h>
#include <time.h>

struct Zaman {
    int saat;
    int dakika;
    int saniye;
};

// Zaman bilgilerini tutan bileşenler
union Veri {
    struct Zaman zaman;
    time_t epochZamani;
};

// Zamanı epoch zamanına çeviren bir fonksiyon
time_t epochCevir(struct Zaman z) {
    struct tm t;
    t.tm_year = 70; // Epoch zamanının başladığı yıl 1970
    t.tm_mon = 0;
    t.tm_mday = 1;
    t.tm_hour = z.saat;
    t.tm_min = z.dakika;
    t.tm_sec = z.saniye;
    t.tm_isdst = -1; // Yaz saati gecerli değil

    return mktime(&t);
}

int main() {
    union Veri ilkZaman, ikinciZaman;

    // İlk aracın zamanı
    printf("Birinci aracın zamanı (hh mm ss) giriniz: ");
    scanf("%d %d %d",
          &ilkZaman.zaman.saat,
          &ilkZaman.zaman.dakika,
          &ilkZaman.zaman.saniye);

    // İkinci aracın zamanı
    printf("İkinci aracın zamanı (hh mm ss) giriniz: ");
    scanf("%d %d %d",
          &ikinciZaman.zaman.saat,
          &ikinciZaman.zaman.dakika,
          &ikinciZaman.zaman.saniye);

    // Epoch zamanını hesaplalar
    ilkZaman.epochZamani = epochCevir(ilkZaman.zaman);
    ikinciZaman.epochZamani = epochCevir(ikinciZaman.zaman);

    // Zaman farkını hesapla
    double fark = difftime(ikinciZaman.epochZamani, ilkZaman.epochZamani);

    // Sonuçları ekrana yazdırır
    printf("Birinci aracın epoch zamani: %ld\n", ilkZaman.epochZamani);
    printf("Ikinci aracın epoch zamani: %ld\n", ikinciZaman.epochZamani);
    printf("Iki arac arasindaki zaman farki (saniye cinsinden): %.0f\n", fark);

    return 0;
}
