#include <stdio.h>
 
int main(){
    
    // Dizimiz iki boyutlu birinci sat�rda gelen zar yuzeyleri
    // ikinci sat�rda tekrar durumunu kontrol etmek i�in 0 ve 1 degerleri
    // �nce 2 sat�r� s�f�rl�yoruz. 0 tek sefer , say� tekrar ediyorsa tekrarlar�n� 1 yap�yoruz.
    
    int yuzler[2][100];
    int cikis,N,i,j,k,farkliyuz;
 
    printf("Zara kac kere atildi : ");
    scanf("%d", &N);
 
    for(i=0; i<N; i++){
        printf("\%d.Yuz : ", i+1);
        scanf("%d", &yuzler[0][i]);
        yuzler[1][i] = 0;
    }
 
    // E�er soruyu 2 for ile ��z�m�n� d���nd���n�z zaman
    // bu k�s�mda daha kolay anla��lacakt�r.
    // k d��ardaki for sayac�
    // i ise i�erdeki for un sayac�.
 
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
 
    // Gereksiz ve uzun k�s�mlar var elbette.
    // Fikir vermesi a��s�ndan b�yle b�rak�yorum.
    
    getchar();
    return 0;
 
}
