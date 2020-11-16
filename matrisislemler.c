// a program which contains possible operations can be made on matrices
// 231112


// Girilen bir matris sabit bir sayiya boluneceginden float deger üretebilir.Ama butun tanýmlamar int,
// o yüzden matrisi sabit bir sayiya bolme islemi eklenmedi!

#include <stdio.h>
#include <stdlib.h>

// Global Variables
 // firstMatris ~ matrix[0] , secondMatris ~ matrix[1], resultMatris ~ matris[2]
 // determinant hesaplanýrken derinlik 5x5 iken 3'e kadar gidiyor.5 seçmemiz simdilik yeterli.
int** matrix[5]; // Matrisleri point eden pointerlarý tutacaz. 

// program menusu, baslangýcta kullanýcýyý karsýlýyor.
int printMenu();

// her matrisin row ve col sayýsýný bir artýyorum.Her matris beraberinde satýr ve sutun sayýsýný da tasýsýn diye
// sadece tek row eklemek yeterlý olabilirdi.Ancak matrisler arasýndaki islemlerin uygulanabilirliði için
// satir ve sutun sayilarini 1 den baslatmamýz daha uygun
// artýrýmdan sonra bellek ayýrýyor
// sonra da row ve col bilgilerini [0][0] ve [0][1] sakliyor.
int** allocateMatrix(int, int);

// Yapýlacak her islem sonrasýnda ya da hata durumlarýnda ayrýlan memory i serbest býrak.
void freeAll();

// baslangýc adresi parametre olarak verilen matrisi, matris yapýsýnda ekrana yazýyor.
void printMatrix(int**);

// Baþlangýc noktasý verilen matrisin elemanlarýný kullanýcýdan alýyor
// boyutlarý zaten matrisin icinde.for dongusunun sýnýrlarýna dikkat!
void getMatrixElement(int**);

// Yapýlacak iþlem icin gereken matris sayisi parametre olarak aktýrýlýyor
// fonksiyon içerisinde matris icin yer ayýrýmý ve matris degerlerini almak 
// icin diðer fonksiyonlar da cagiriliyor
void getMatrixSize(int);

// yapacagýmýz isleme göre sonuc matrisimizin boyutlarý bellidir
// Bunun için degisik durumlara gore row ve  col hesaplanýp allocateMatris ile yer ayrýlýyor.
void calSizesOfResultMatrix(int);

// kullanýcýdan aldýgýmýz matrisler global matrix dizisini kullanarak ulaþabileceðimiz
// için aktarmaya genel olarak gerek yok.
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
					printf("HATA : toplama ve cikarma icin iki matrisin satir ve sutun sayilarý esit olmalý!\n");
					continue;
				}
				add();
				printf("Verilen iki matrisin toplamý : \n");
			break;
			case 2: // cikarma islemi
				printf("\n BILGILENDIRME : Birinci matristen ikinci matris cikartilacaktir.\n");
				getMatrixSize(2);  // 2 matris gerekiyor
				if( matrix[0][0][0] != matrix[1][0][0]  || matrix[0][0][1] != matrix[1][0][1] ){
					printf("HATA : toplama ve cikarma icin iki matrisin satir ve sutun sayilarý esit olmalý!\n");
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
					printf("HATA : determinantýnýn alinmasý icin kare matris olmalý! \n");
					continue;
				}
				printf("Determinant : |A| : %d \n", determinant(matrix[0],0));
				// BU KISIMDA SORUN VAR!
			break;
			case 5:// Carpma islemi
				getMatrixSize(2);
				if( matrix[0][0][1] != matrix[1][0][0] ){
				printf("HATA : Carpma islemi icin 1.matrisin sutun sayisi \n        2.matrisin satir sayisina esit olmalý! \n");
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
		
		// Determinanta sayýsal bir sonuc olustugu ýcýn durumu farklý digerlerinde sonuc matrisi ekrana yazdiriliyor
		if( operation != 4 ){
			//hesaplama isleminin sonucu hep matrix[2] nin gosterdiði yerde saklanacak.
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
		printf("[5] - Ýki matrisin carpimi\n");
		printf("[6] - Transpoze\n");
		printf("[0] - Exit\n");
		
		do{
			printf("\nHangi islemi yapmak istiyorsanýz basindaki sayiyi giriniz > ");
			scanf("%d", &op);
		}while( op<0 || op>6 );
		
		return op;
}

int** allocateMatrix(int row, int col){
	int i;
	int **matrixPointer;
	
	// ilk satirda matrislerin boyutlarýný saklýyor
	row++;
	col++;
	
	// Matris icin memory allocation.
	
	matrixPointer = (int**)malloc( row * sizeof(int*) );
	//Kontrol		
	if( matrixPointer == NULL){ printf("HATA : Gerekli alan ayrýlamadi!."); exit(0); }
	
	for( i=0; i<row; i++ ){
		matrixPointer[i] = (int*)malloc( col * sizeof(int) );
		// Kontrol
		if( matrixPointer[i] == NULL){ printf("HATA : Gerekli alan ayrýlamadi!."); exit(0); }
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
	
	
	// buraya geldiðimde toplanacak matrislerin degerlerinin bilinmesi
	// ve sonuc matrisi için yer ayrýlmýs olmasý lazým
	
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
	// sunuc matrisinin boyutu : transpoze alýnýrken row ve col sayýsý degýsýr.
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
		// 2x2 lýk matrisin determinantý
		det = theMatrix[1][1] * theMatrix[2][2] - theMatrix[2][1] * theMatrix[1][2]; // det = a*d - c*b
		return det;
	}else{ // recursive case		
		
		// Determinantý birinci satira göre alalim	
		sat = 1;
		
		// Alt matrislerin tutulacagý bolgelerin alikasyonu
		derinlik++; 
		// 3x3luk matriste 2x2lýk alt matrisler olusur, bir de allocateMatrix fonk. artýrýmdan dolayý -1 = -2
		matrix[derinlik] = allocateMatrix(theMatrix[0][0]-2,theMatrix[0][1]-2); 
		
		
		for( sut=1; sut<theMatrix[0][1]; sut++ ){ // ilk satirdaki elemanlarýn sýrasýyla islenmesi
			newSat=0; // Alt matrislerin satir sayisi			
			// Ana matristen alt matrislerin olusturulmasý
			for( i=2; i<theMatrix[0][0]; i++ ){ // Det. birinci satire göre alýndýgý ýcýn 2 den basla			
				newSat++; 
				newSut = 1; // Ayný alt matris icin bir sonraki satir
				for( j=1; j<theMatrix[0][1]; j++ ){
					if( sut == j ){
						continue; // det alýnan satýrdaki elemanlarýn sutunlarýn üstü ciziliyor.Alt matrise katmýyoruz.
					}
					matrix[derinlik][newSat][newSut] = theMatrix[i][j]; // Ana matristen alt matrisine eleman aktarýmý
					newSut++;
				}
			}
			// Olusan her alt matrisi ekrana yazdirmak istersek :
			// Matris boyutuna göre gidilecek derinliði görmek istiyorsak
			// alta yorumlanmýs iki satirdan // kaldirilabilir. 
			//printf("Derinlik : %d \n", derinlik);
			//printMatrix(matrix[derinlik]);
			
			det = det + theMatrix[sat][sut] * isaret * determinant(matrix[derinlik], derinlik);	// recursive call		
			isaret = isaret * (-1); // bir artý bir eksi olacak.
					
		} // Determinant aldiðimiz satirin elemanlarýný donderen for un sonu
		return det;	
	} // matris boyutunu kontrol eden if in sonu
}

void freeAll(){
	int i;
	
	for(i=0; i<5; i++){
		free(matrix[i]);
	}
}
