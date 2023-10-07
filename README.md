# Multithread Huffman Coding 
Bu proje, Huffman algoritmasının farklı versiyonlarını kullanarak daha optimize hale getirme çabalarını içerir. Toplamda 8 farklı versiyon üzerinde çalışıldı.

## Nasıl Çalıştırılır?

Kodları derlemek için aşağıdaki komutu kullanabilirsiniz:

```shell
g++ -O3 -std=c++17 -lpthread -pthread versiyon1.cpp -o program
```

Derleme zamanındaki süreleri görmek için aşağıdaki komutu kullanabilirsiniz:
```shell
time ./program
```


## Versiyonlar

### Versiyon 1

Bu versiyon, en temel ve ilkel Huffman algoritmasıdır. İçinde 5 adet dosya ve pointerlar bulunur.

### Versiyon 2

Versiyon 2, Versiyon 1'deki while döngülerini optimize etmek için for döngülerine dönüşüm yapar. Ayrıca, gereksiz dosya açma işlemlerini kaldırarak iyileştirmeler sağlar.

### Versiyon 3

Versiyon 3, Versiyon 2'ye ek olarak her dosya için ayrı çalışan threadler kullanır. Ancak bu optimize edilmiş versiyon, daha fazla iş parçacığı kullanarak bazı işlemlerde beklenmedik yavaşlamalara neden olabilir.

### Versiyon 4

Versiyon 4, const ve constexpr kullanarak optimizasyon sağlar ve versiyon 3 ile kıyaslandığında 30 saniyelik hızlandırma elde eder.

### Versiyon 5

Versiyon 5, recursive fonksiyon kullanarak çalışır ve versiyon 4'e göre 3 saniyelik bir yavaşlama yaşar. Bu yavaşlama, rekürsif fonksiyonun derleme zamanında çözülemiyor olması, her çağrıda veri erişimi istemesi ve rekürsif mantığının karmaşık olmasından kaynaklanır.

### Versiyon 6

Versiyon 6, en çok zaman harcanan yerleri belirlemek için gprof çıktısını kullanır ve bottleneck'i bulur. Bu versiyonda map veri yapısını unordered map ve vector ile değiştirerek 2 saniyelik iyileşme sağlar.

### Versiyon 7

Versiyon 7, vektörizasyon işlemi için bazı değişiklikler yapar ve malloc kullanarak iyileştirmeler sağlar. Bu versiyon, 3 saniyelik iyileşme elde eder.

### Versiyon 8

Versiyon 8, daha fazla iş parçacığı kullanarak hızlandırmayı amaçlar.



## Katkıda Bulunma
Bu proje her türlü katkıya açıktır. Katkıda bulunmak için şu adımları takip edebilirsiniz:

1. "Star" butonuna tıklayarak projeye star verebilirsiniz.
2. Bu depoyu (`repository`) çatallayın (fork).
3. Yaptığınız değişiklikleri içeren yeni bir dal (branch) oluşturun.
4. Değişikliklerinizi bu yeni dalda yapın ve düzenleyin.
5. Değişikliklerinizi başka bir dalda test edin.
6. Değişikliklerinizi orijinal depoya (upstream repository) geri göndermek için bir birleştirme isteği (pull request) açın.
