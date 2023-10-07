# Multithread Huffman Coding 
Bu proje, Huffman algoritmasının farklı versiyonlarını kullanarak daha optimize hale getirme çabalarını içerir. Toplamda 8 farklı versiyon üzerinde çalışıldı.

## Versiyonlar

### Versiyon 1

Bu versiyon, en temel ve ilkel Huffman algoritmasıdır. İçinde 5 adet dosya ve pointerlar bulunur.

### Versiyon 2

Versiyon 2, Versiyon 1'deki while döngülerini optimize etmek için for döngülerine dönüşüm yapar. Ayrıca, gereksiz dosya açma işlemlerini kaldırarak iyileştirmeler sağlar.

### Versiyon 3

Versiyon 3, Versiyon 2'ye ek olarak her dosya için ayrı çalışan threadler kullanır. Ancak bu optimize edilmiş versiyon, daha fazla iş parçacığı kullanarak bazı işlemlerde beklenmedik yavaşlamalara neden olabilir.







## Katkıda Bulunma
Bu proje her türlü katkıya açıktır. Katkıda bulunmak için şu adımları takip edebilirsiniz:

1. "Star" butonuna tıklayarak projeye star verebilirsiniz.
2. Bu depoyu (`repository`) çatallayın (fork).
3. Yaptığınız değişiklikleri içeren yeni bir dal (branch) oluşturun.
4. Değişikliklerinizi bu yeni dalda yapın ve düzenleyin.
5. Değişikliklerinizi başka bir dalda test edin.
6. Değişikliklerinizi orijinal depoya (upstream repository) geri göndermek için bir birleştirme isteği (pull request) açın.
