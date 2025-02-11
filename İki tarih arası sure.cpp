#include <stdio.h>
#include <time.h>

// Tarih ve saat bilgisini tutan bir yapı (struct)
struct TarihSaat {
    int yil;
    int ay;
    int gun;
    int saat;
    int dakika;
    int saniye;
};

// Tarih ve Saat ve zaman farkı bilgilerini tutan bir birleştirme (union)
union Veri {
    struct TarihSaat tarihSaat;
    time_t epochZamani;
};

// Tarih ve saati epoch zamanına çeviren bir fonksiyon
time_t epochCevir(struct TarihSaat ts) {
    struct tm t;
    t.tm_year = ts.yil - 1900; // tm_year 1900'dan itibaren yıl sayısını tutar
    t.tm_mon = ts.ay - 1;      // tm_mon 0-11 arası ay sayısını tutar
    t.tm_mday = ts.gun;
    t.tm_hour = ts.saat;
    t.tm_min = ts.dakika;
    t.tm_sec = ts.saniye;
    t.tm_isdst = -1; // Yaz saati uygulaması geçerli değil

    return mktime(&t);
}

int main() {
    union Veri ilkTarih, ikinciTarih;

    // İlk tarih ve saat bilgilerini kullanıcıdan alır
    printf("Birinci tarih ve saat (YYYY MM DD hh mm ss) giriniz: ");
    scanf("%d %d %d %d %d %d",
          &ilkTarih.tarihSaat.yil,
          &ilkTarih.tarihSaat.ay,
          &ilkTarih.tarihSaat.gun,
          &ilkTarih.tarihSaat.saat,
          &ilkTarih.tarihSaat.dakika,
          &ilkTarih.tarihSaat.saniye);

    // İkinci tarih ve saat bilgilerini kullanıcıdan alır
    printf("İkinci tarih ve saat (YYYY MM DD hh mm ss) giriniz: ");
    scanf("%d %d %d %d %d %d",
          &ikinciTarih.tarihSaat.yil,
          &ikinciTarih.tarihSaat.ay,
          &ikinciTarih.tarihSaat.gun,
          &ikinciTarih.tarihSaat.saat,
          &ikinciTarih.tarihSaat.dakika,
          &ikinciTarih.tarihSaat.saniye);

    // Epoch zamanını hesaplalar
    ilkTarih.epochZamani = epochCevir(ilkTarih.tarihSaat);
    ikinciTarih.epochZamani = epochCevir(ikinciTarih.tarihSaat);

    // Zaman farkını hesapla
    double fark = difftime(ikinciTarih.epochZamani, ilkTarih.epochZamani);

    // Sonuçları ekrana yazdırır
    printf("Birinci tarih ve saatin epoch zamani: %ld\n", ilkTarih.epochZamani);
    printf("Ikinci tarih ve saatin epoch zamani: %ld\n", ikinciTarih.epochZamani);
    printf("Iki tarih arasindaki zaman farki (saniye cinsinden): %.0f\n", fark);

    return 0;
}
