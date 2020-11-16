// a program which contains possible operations can be made on matrices
// 231112


// Girilen bir matris sabit bir sayiya boluneceginden float deger �retebilir.Ama butun tan�mlamar int,
// o y�zden matrisi sabit bir sayiya bolme islemi eklenmedi!

#include <stdio.h>
#include <stdlib.h>

// Global Variables
 // firstMatris ~ matrix[0] , secondMatris ~ matrix[1], resultMatris ~ matris[2]
 // determinant hesaplan�rken derinlik 5x5 iken 3'e kadar gidiyor.5 se�memiz simdilik yeterli.
int** matrix[5]; // Matrisleri point eden pointerlar� tutacaz. 

// program menusu, baslang�cta kullan�c�y� kars�l�yor.
int printMenu();

// her matrisin row ve col say�s�n� bir art�yorum.Her matris beraberinde sat�r ve sutun say�s�n� da tas�s�n diye
// sadece tek row eklemek yeterl� olabilirdi.Ancak matrisler aras�ndaki islemlerin uygulanabilirli�i i�in
// satir ve sutun sayilarini 1 den baslatmam�z daha uygun
// art�r�mdan sonra bellek ay�r�yor
// sonra da row ve col bilgilerini [0][0] ve [0][1] sakliyor.
int** allocateMatrix(int, int);

// Yap�lacak her islem sonras�nda ya da hata durumlar�nda ayr�lan memory i serbest b�rak.
void freeAll();

// baslang�c adresi parametre olarak verilen matrisi, matris yap�s�nda ekrana yaz�yor.
void printMatrix(int**);

// Ba�lang�c noktas� verilen matrisin elemanlar�n� kullan�c�dan al�yor
// boyutlar� zaten matrisin icinde.for dongusunun s�n�rlar�na dikkat!
void getMatrixElement(int**);

// Yap�lacak i�lem icin gereken matris sayisi parametre olarak akt�r�l�yor
// fonksiyon i�erisinde matris icin yer ay�r�m� ve matris degerlerini almak 
// icin di�er fonksiyonlar da cagiriliyor
void getMatrixSize(int);

// yapacag�m�z isleme g�re sonuc matrisimizin boyutlar� bellidir
// Bunun i�in degisik durumlara gore row ve  col hesaplan�p allocateMatris ile yer ayr�l�yor.
void calSizesOfResultMatrix(int);

// kullan�c�dan ald�g�m�z matrisler global matrix dizisini kullanarak ula�abilece�imiz
// i�in aktarmaya genel olarak gerek yok.
void add();

void sub();

void transpose();

void mulWithConstant();

void multiple();

int determinant(int** , int );

int main(){
	int operation;
	char devam='e';
	
	while( devam == 'e' || devam == 'E' ){
		freeAll();
		printf("\n");
		operation = printMenu();
		
		switch( operation ){
			case 1: // toplama islemi
				getMatrixSize(2); // iki matris gerekiyor
				if( matrix[0][0][0] != matrix[1][0][0]  || matrix[0][0][1] != matrix[1][0][1] ){
					printf("HATA : toplama ve cikarma icin iki matrisin satir ve sutun sayilar� esit olmal�!\n");
					continue;
				}
				add();
				printf("Verilen iki matrisin toplam� : \n");
			break;
			case 2: // cikarma islemi
				printf("\n BILGILENDIRME : Birinci matristen ikinci matris cikartilacaktir.\n");
				getMatrixSize(2);  // 2 matris gerekiyor
				if( matrix[0][0][0] != matrix[1][0][0]  || matrix[0][0][1] != matrix[1][0][1] ){
					printf("HATA : toplama ve cikarma icin iki matrisin satir ve sutun sayilar� esit olmal�!\n");
					continue;
				}
				sub();
				printf("1.Matristen 2.matrisin cikarilmasiyla olusan matris :\n");
			break;
			case 3: // Sabit ile carpma
				getMatrixSize(1);
				// Herhangi bir kontrole gerek yok
				mulWithConstant();
				printf("\nMatrisin sabit ile carpilmis hali : \n");
			break;
			case 4:// determinant, bir matris lazim.
				getMatrixSize(1);				
				if( matrix[0][0][0] != matrix[0][0][1] ){
					printf("HATA : determinant�n�n alinmas� icin kare matris olmal�! \n");
					continue;
				}
				printf("Determinant : |A| : %d \n", determinant(matrix[0],0));
				// BU KISIMDA SORUN VAR!
			break;
			case 5:// Carpma islemi
				getMatrixSize(2);
				if( matrix[0][0][1] != matrix[1][0][0] ){
				printf("HATA : Carpma islemi icin 1.matrisin sutun sayisi \n        2.matrisin satir sayisina esit olmal�! \n");
				continue;
				}
				multiple();
				printf("Iki matrisin carpiminin sonucu : \n");
			break;
			case 6: // Transpoze islemi
				getMatrixSize(1);
				// Herhangi bir kontrole gerek yok.
				transpose();
				printf("Verilen matrisin transpozesi : \n");			
			break;
			case 0:
				return 0;
			break;
			
		} // the end of switch
		
		// Determinanta say�sal bir sonuc olustugu �c�n durumu farkl� digerlerinde sonuc matrisi ekrana yazdiriliyor
		if( operation != 4 ){
			//hesaplama isleminin sonucu hep matrix[2] nin gosterdi�i yerde saklanacak.
			printMatrix(matrix[2]);
		}		
		
		getchar();
		printf("\nNew operation e/h? > ");		
		devam = getchar();
	} // the end of while
	
	return 0;
}// the end of main


int printMenu(){
		int op;
	
		printf("=== Matrix operations ===\n");
		printf("[1] - Toplama\n");
		printf("[2] - Cikarma\n");
		printf("[3] - Sabit ile Carpma\n");
		printf("[4] - Determinant\n");
		printf("[5] - �ki matrisin carpimi\n");
		printf("[6] - Transpoze\n");
		printf("[0] - Exit\n");
		
		do{
			printf("\nHangi islemi yapmak istiyorsan�z basindaki sayiyi giriniz > ");
			scanf("%d", &op);
		}while( op<0 || op>6 );
		
		return op;
}

int** allocateMatrix(int row, int col){
	int i;
	int **matrixPointer;
	
	// ilk satirda matrislerin boyutlar�n� sakl�yor
	row++;
	col++;
	
	// Matris icin memory allocation.
	
	matrixPointer = (int**)malloc( row * sizeof(int*) );
	//Kontrol		
	if( matrixPointer == NULL){ printf("HATA : Gerekli alan ayr�lamadi!."); exit(0); }
	
	for( i=0; i<row; i++ ){
		matrixPointer[i] = (int*)malloc( col * sizeof(int) );
		// Kontrol
		if( matrixPointer[i] == NULL){ printf("HATA : Gerekli alan ayr�lamadi!."); exit(0); }
	}
	
	// Store matrix row and col info in its first row
	matrixPointer[0][0] = row;
	matrixPointer[0][1] = col;
	
	return matrixPointer;
}

void printMatrix(int** theMatrix){
	int i,j;
	
	for( i=1; i<theMatrix[0][0]; i++ ){
		printf("\n");
		for( j=1; j<theMatrix[0][1]; j++ ){
			printf(" %2d", theMatrix[i][j]);
		}
	}
	printf("\n\n");
}

void getMatrixElement(int** theMatrix){
	int i,j;
	
	printf("\n");
	for( i=1; i<theMatrix[0][0]; i++ ){
		for( j=1; j<theMatrix[0][1]; j++ ){
			srand(time(NULL));
		theMatrix[i][j]=5+rand()%3495;
		printf("[%d][%d] element : %d %d", i,j,theMatrix[i][j]);
	
	for(i=0;i<theMatrix[0][0];i++){
		for(j=0;j<theMatrix[0][1];j++){
			printf("%4d",theMatrix[i][j]);
			printf("\t\t\t");
		}
		printf("\n\n");
	}
		

		}
		
	}
	
}

void getMatrixSize(int numberOfMatrix){
	int i;
	int row,col;
	
	for( i=0; i<numberOfMatrix; i++ ){
		// Get size of the matrix 
		
		printf("\n%d.Matrisin Satir Sayisi > ", i+1);
		scanf("%d", &row);
		printf("\n%d.Matrisin Sutun Sayisi > ", i+1);
		scanf("%d", &col);
		// Allocate memory for the maxtrix
		matrix[i] = allocateMatrix(row, col);
		// Get value of the elements of matrix
		getMatrixElement(matrix[i]);
		
		printf("\n%d.Matris : \n", i+1);
		printMatrix(matrix[i]);
	}
}

void calSizesOfResultMatrix(int op){
	int row, col;
	switch( op ){
		case 1: // toplama
		case 2: // cikarma
		case 3: // sabit ile carpma
			row = matrix[0][0][0] - 1; // -1 because it will add 1 in the allocate function.
			col = matrix[0][0][1] - 1; 
		break;
		case 5:
			row = matrix[0][0][0] -1; // Birincinin satir sayisi
			col = matrix[1][0][1] -1; // ikinci matrisin sutun sayisi
		break;
		case 6:
			row = matrix[0][0][1] - 1;
			col = matrix[0][0][0] - 1;
		break;
	}
	
	matrix[2] = allocateMatrix(row, col);
}

void add(){
	int i,j;
	
	
	// buraya geldi�imde toplanacak matrislerin degerlerinin bilinmesi
	// ve sonuc matrisi i�in yer ayr�lm�s olmas� laz�m
	
	calSizesOfResultMatrix(1); // toplama 
	
	for( i=1; i<matrix[0][0][0]; i++ ){
		for( j=1; j<matrix[0][0][1]; j++ ){
			matrix[2][i][j] = matrix[0][i][j] + matrix[1][i][j];
		}
	}
}

void sub(){
	int i,j;
	
	// hesapla ve yer ayir.
	calSizesOfResultMatrix(2); // cikarma 
	
	for( i=1; i<matrix[0][0][0]; i++ ){
		for( j=1; j<matrix[0][0][1]; j++ ){
			matrix[2][i][j] = matrix[0][i][j] - matrix[1][i][j];
		}
	}	
}

void transpose(){
	// sunuc matrisinin boyutu : transpoze al�n�rken row ve col say�s� deg�s�r.
	int i,j;
	
	calSizesOfResultMatrix(6);
	
	for( i=1; i<matrix[0][0][0]; i++ ){
		for( j=1; j<matrix[0][0][1]; j++ ){
			matrix[2][j][i] = matrix[0][i][j];
			printf("matrix[2][%d][%d] : %d\n", j,i,matrix[2][j][i]);
		}
	}
}

void mulWithConstant(){
	int i,j,con;
	
	calSizesOfResultMatrix(3);
	
	printf("\nEnter constant > ");
	scanf("%d", &con);
	
	for( i=1; i<matrix[0][0][0]; i++ ){
		for( j=1; j<matrix[0][0][1]; j++ ){
			matrix[2][i][j] = matrix[0][i][j] * con;
		}
	}
}

void multiple(){
	int i,j,k;
	
	calSizesOfResultMatrix(5);
	
	for( i=1; i<matrix[0][0][0]; i++ ){
		for( j=1; j<matrix[1][0][1]; j++ ){
			for( k=1; k<matrix[0][0][1]; k++ ){
				matrix[2][i][j] = matrix[2][i][j] + ( matrix[0][i][k] * matrix[1][k][j] );
			}
		}
	}
}

int determinant(int** theMatrix, int derinlik){
	int det=0,isaret= -1;
	int newSat,newSut=1;
	int sut,sat,i,j;
	
	// base case
	if( theMatrix[0][0] == 3 ){
		// 2x2 l�k matrisin determinant�
		det = theMatrix[1][1] * theMatrix[2][2] - theMatrix[2][1] * theMatrix[1][2]; // det = a*d - c*b
		return det;
	}else{ // recursive case		
		
		// Determinant� birinci satira g�re alalim	
		sat = 1;
		
		// Alt matrislerin tutulacag� bolgelerin alikasyonu
		derinlik++; 
		// 3x3luk matriste 2x2l�k alt matrisler olusur, bir de allocateMatrix fonk. art�r�mdan dolay� -1 = -2
		matrix[derinlik] = allocateMatrix(theMatrix[0][0]-2,theMatrix[0][1]-2); 
		
		
		for( sut=1; sut<theMatrix[0][1]; sut++ ){ // ilk satirdaki elemanlar�n s�ras�yla islenmesi
			newSat=0; // Alt matrislerin satir sayisi			
			// Ana matristen alt matrislerin olusturulmas�
			for( i=2; i<theMatrix[0][0]; i++ ){ // Det. birinci satire g�re al�nd�g� �c�n 2 den basla			
				newSat++; 
				newSut = 1; // Ayn� alt matris icin bir sonraki satir
				for( j=1; j<theMatrix[0][1]; j++ ){
					if( sut == j ){
						continue; // det al�nan sat�rdaki elemanlar�n sutunlar�n �st� ciziliyor.Alt matrise katm�yoruz.
					}
					matrix[derinlik][newSat][newSut] = theMatrix[i][j]; // Ana matristen alt matrisine eleman aktar�m�
					newSut++;
				}
			}
			// Olusan her alt matrisi ekrana yazdirmak istersek :
			// Matris boyutuna g�re gidilecek derinli�i g�rmek istiyorsak
			// alta yorumlanm�s iki satirdan // kaldirilabilir. 
			//printf("Derinlik : %d \n", derinlik);
			//printMatrix(matrix[derinlik]);
			
			det = det + theMatrix[sat][sut] * isaret * determinant(matrix[derinlik], derinlik);	// recursive call		
			isaret = isaret * (-1); // bir art� bir eksi olacak.
					
		} // Determinant aldi�imiz satirin elemanlar�n� donderen for un sonu
		return det;	
	} // matris boyutunu kontrol eden if in sonu
}

void freeAll(){
	int i;
	
	for(i=0; i<5; i++){
		free(matrix[i]);
	}
}
