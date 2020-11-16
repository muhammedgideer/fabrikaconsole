#include <stdio.h>
 
int main(){
    
    // Dizimiz iki boyutlu birinci satırda gelen zar yuzeyleri
    // ikinci satırda tekrar durumunu kontrol etmek için 0 ve 1 degerleri
    // önce 2 satırı sıfırlıyoruz. 0 tek sefer , sayı tekrar ediyorsa tekrarlarını 1 yapıyoruz.
    
    int yuzler[2][100];
    int cikis,N,i,j,k,farkliyuz;
 
    printf("Zara kac kere atildi : ");
    scanf("%d", &N);
 
    for(i=0; i<N; i++){
        printf("\%d.Yuz : ", i+1);
        scanf("%d", &yuzler[0][i]);
        yuzler[1][i] = 0;
    }
 
    // Eğer soruyu 2 for ile çözümünü düşündüğünüz zaman
    // bu kısımda daha kolay anlaşılacaktır.
    // k dışardaki for sayacı
    // i ise içerdeki for un sayacı.
 
    cikis = 0;
    k = 0;
    i = 1;
 
    while( cikis == 0 ){
 
        if( yuzler[1][i] == 0 ){
            if( yuzler[0][k] == yuzler[0][i] ){
                yuzler[1][i] = 1;
            }
        }
        
        i++;
        
        if( i == N){
            k++;
            i = k+1;
        }
        
        if( k == N-1){
            cikis = 1;
        }
 
    }
 
    farkliyuz = 0;
 
    for(i=0; i<N; i++){
        
        if(yuzler[1][i] == 0){
            farkliyuz++;
        }
        
    }
 
    printf("\n%d tane farkli yuz gelmis : ", farkliyuz);
 
    // Gereksiz ve uzun kısımlar var elbette.
    // Fikir vermesi açısından böyle bırakıyorum.
    
    getchar();
    return 0;
 
}
