// part 1 
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

typedef struct { int ngay , thang ,nam ;  float sotien ;  char ghichu[250] ;  } Chitieu ;
typedef struct { int thang , nam ; float sotien  ; }Thunhap ;
//part 2
void savefilechitieu(Chitieu ct) {
	FILE *f = fopen("chitieu.txt" , "a" );
	if (f== NULL) {
		printf ("\n ko the mo file\n") ;
		return ; } 
    fprintf(f , "%02d/%02d/%d %.0f %s\n" , ct.ngay , ct.thang , ct.nam , ct.sotien , ct.ghichu );
    fclose(f); }

void savefilethunhap(Thunhap tn ) {
	FILE *f = fopen("thunhap.txt" , "a") ;
		if (f== NULL) {
		printf ("\n ko the mo file\n") ;
		return ; } 
    fprintf(f , "%02d %d %.0f\n" , tn.thang , tn.nam , tn.sotien  );
    fclose(f); } 
    
float laythunhapthang( int thangxem , int namxem ) {
	FILE *f = fopen("thunhap.txt", "r");
	if (f == NULL) return 0; 
	
	Thunhap tn ;
	
	while (fscanf(f, "%02d %d %f\n", &tn.thang, &tn.nam, &tn.sotien) ==3) {
        if (tn.thang == thangxem && tn.nam == namxem) {
            return tn.sotien;
        }
    }
    fclose(f);
    return 0; }
    
void themthunhap() {
	Thunhap tn ;
	printf("\n=== Thiet lap thu nhap thang===\n");
	printf("Nhap thang va nam : " ) ; scanf("%02d %d" , &tn.thang , &tn.nam ) ;
	printf(" Nhap tong thu nhap thang (VND):") ;
	scanf ("%f" , &tn.sotien) ;
	savefilethunhap(tn) ;
	printf("=> Ðã luu thu nhap tháng %02d/%d thanh cong!\n", tn.thang, tn.nam);
}

void themchitieu() { 
    int chontiep ;
    do { 
        Chitieu ct ;
        printf("\n=== NHAP KHOAN CHI TIEU MOI ===\n");
        printf("Nhap ngay, thang, nam (Vi du: 23 7 2026): ");
        scanf("%d %d %d", &ct.ngay, &ct.thang, &ct.nam);
        
        printf("Nhap so tien chi (VND): ");
        scanf("%f", &ct.sotien);
        
        printf("Nhap ghi chu : ");
        scanf(" %[^\n]", ct.ghichu);

        savefilechitieu(ct);
        printf(" Ða luu khoan chi ngay %02d/%02d/%d thanh cong!\n", ct.ngay, ct.thang, ct.nam);
  
      
	    printf("\n Nhap tiep an 1 ko nhan 0: ");
        scanf(" %d", &chontiep ); } 
           while ( chontiep == 1) ; }

void xembaocao() { 
int thangxem , namxem ;
    printf("\n=== XEM BAO CAO TAI CHINH ===\n");
    printf("Nhap thang và nam muon xem (Vi du: 7 2026): ");
    scanf("%d %d", &thangxem, &namxem);

    float tongthu = laythunhapthang(thangxem, namxem);
    
    FILE *f = fopen("chitieu.txt", "r");

    printf("\n+-----------------------------------------------------------------------+\n");
    printf("| THANG %02d/%d  | Tong tien thu : %.0f VND  |\n", thangxem, namxem, tongthu);
    printf("+-----------------------------------------------------------------------+\n");
    printf("|                          DANH MUC CHI TIEU                            |\n");
    printf("+------------------+-----------------------+----------------------------+\n");
    printf("| Ngay             | So Tien Chi (VND)     | Ghi Chu                    |\n");
    printf("+------------------+-----------------------+----------------------------+\n");

    float tongchi = 0;

    if (f != NULL) {
        Chitieu ct;
        while (fscanf(f, "%d/%d/%d %f %[^\n]\n", &ct.ngay, &ct.thang, &ct.nam, &ct.sotien, ct.ghichu) == 5) {
            if (ct.thang == thangxem && ct.nam == namxem) {
                printf("| %02d/%02d/%-10d | %-21.0f | %-26s |\n", 
                       ct.ngay, ct.thang, ct.nam, ct.sotien, ct.ghichu);
                tongchi += ct.sotien; 
            }
        }
        fclose(f);
    }

    float sodu = tongthu - tongchi;
    
    printf("+-----------------------------------------------------------------------+\n");
    printf("| Tong tieu thang %02d: %-12.0f | So du con lai: %-18.0f VND|\n",thangxem, tongchi, sodu);
    printf("+-----------------------------------------------------------------------+\n");
}


void chinhsua() {
	int chonso ;
    do {
        printf("\n==========================================\n");
        printf("            BAN MUON SUA GI          \n");
        printf("==========================================\n");
        printf("1. SUA KHOAN THU THANG\n");
        printf("2. SUA SO TIEN CHI TIEU THEO NGAY\n");
        printf("3. SUA GHI CHU THEO NGAY\n");
        printf("0. Thoat\n");
        printf("------------------------------------------\n");
        printf("LUA CHON:") ;
        scanf ("%d" , &chonso ); 
    

		switch (chonso) {
        case 1: {
            int thangSua, namSua;
            int timThay = 0;
            
            printf("Nhap thang/nam muon sua (VD: 7 2026): ");
            scanf("%d %d", &thangSua, &namSua);

            FILE *f = fopen("thunhap.txt", "r");
            if (f == NULL) {
                printf("Loi: Khong mo duoc file thunhap.txt hoac file chua ton tai!\n");
                break;
            }

            Thunhap tn[100]; 
            int n = 0;

            while ( n < 100 && fscanf(f, "%02d %d %f", &tn[n].thang, &tn[n].nam, &tn[n].sotien) == 3) {
                if (tn[n].thang == thangSua && tn[n].nam == namSua) {
                    printf("Tim thay! So tien hien tai: %.2f\n", tn[n].sotien);
                    printf("Nhap so tien thu nhap moi: ");
                    scanf("%f", &tn[n].sotien);
                    timThay = 1;
                }
                n++;
            }
            fclose(f);

            if (timThay) {
                f = fopen("thunhap.txt", "w"); 
                for (int i = 0; i < n; i++) {
                    fprintf(f, "%02d %d %.2f\n", tn[i].thang, tn[i].nam, tn[i].sotien);
                }
                fclose(f);
                printf("=> Cap nhat khoan thu thanh cong!\n");
            } else {
                printf("=> Khong tim thay du lieu thu nhap cho thang %d/%d!\n", thangSua, namSua);
            }
            break;
        }
		 
		 
		case 2 : {
			int thangsua , namsua , ngaysua ; 
			int timthay = 0 ;
			
			printf ("Nhap  ngay/thang/nam muon sua :") ;
		    scanf ("%d %d %d" , &ngaysua, &thangsua , &namsua );
		    FILE *f = fopen("chitieu.txt" , "r") ;
		    if (f==NULL) {
			     printf("Loi: Khong mo duoc file chitieu.txt hoac file chua ton tai!\n");
                break;
            } 
			Chitieu ct[1000] ;
			int n = 0 ;
			while (n < 1000 && fscanf(f, "%d/%d/%d %f %[^\n]\n" , &ct[n].ngay , &ct[n].thang , &ct[n].nam , &ct[n].sotien , ct[n].ghichu ) == 5 ) {
			     if ( ct[n].ngay == ngaysua && ct[n].thang == thangsua && ct[n].nam==namsua ) {
			     	printf("Tim thay so tien chi hien tai : %.0f\n" , ct[n].sotien) ;
			     	printf("Nhap so tien chi moi: ");
                    scanf("%f", &ct[n].sotien);
                    timthay = 1;
                }
                n++;
            }
            fclose(f);
            
            if(timthay) { 
			   f = fopen("chitieu.txt", "w") ;
			    if (f == NULL) {
                    printf("Loi: Khong ghi duoc file chitieu.txt!\n");
                    break;
                }
			   for(int i = 0 ; i < n ; i++) { 
			       fprintf(f ,"%02d/%02d/%d %.0f %s\n" , ct[i].ngay , ct[i].thang , ct[i].nam , ct[i].sotien , ct[i].ghichu ) ;  
			    }
            fclose(f) ;
            printf("=> Cap nhat khoan thu thanh cong!\n");
            } else {
                printf("=> Khong tim thay du lieu thu nhap cho ngay %02d/%02d/%d!\n", ngaysua, thangsua , namsua );
            }
            break; }
            
            
        case 3 : {
            int thangsua , namsua , ngaysua ; 
			int timthay = 0 ;
			
			printf ("Nhap ngay/thang/nam muon sua :") ;
		    scanf (" %d %d %d" , &ngaysua, &thangsua , &namsua );
		    FILE *f = fopen("chitieu.txt" , "r") ;
		    if (f== NULL) {
			     printf("Loi: Khong mo duoc file chitieu.txt hoac file chua ton tai!\n");
                break;
            } 
			Chitieu ct[1000] ;
			int n = 0 ;
			while (n < 1000 && fscanf(f, "%d/%d/%d %f %249[^\n]", &ct[n].ngay , &ct[n].thang , &ct[n].nam , &ct[n].sotien , ct[n].ghichu ) == 5 ) {
				
				 if ( ct[n].ngay == ngaysua && ct[n].thang == thangsua && ct[n].nam== namsua ) {
			     	printf("Tim thay ghi chu hien tai : %s\n" , ct[n].ghichu) ;
			     	printf("Nhap ghi chu moi: ");
                    scanf(" %[^\n]", ct[n].ghichu);
                    timthay = 1;
                }
                n++;
            }
            fclose(f);
            
            if(timthay) { 
			   f = fopen("chitieu.txt", "w") ;
			     if (f == NULL) {
                    printf("Loi: Khong ghi duoc file chitieu.txt!\n");
                    break;
                }
			   for(int i = 0 ; i < n ; i++) { 
			       fprintf(f,"%02d/%02d/%d %.0f %s\n", ct[i].ngay, ct[i].thang, ct[i].nam, ct[i].sotien, ct[i].ghichu);
			    }
            fclose(f) ;
            printf("=> Cap nhat ghi chu thanh cong!\n");
            } else {
                printf("=> Khong tim thay du lieu khoan chi cho thang %02d/%02d/%d!\n", ngaysua, thangsua , namsua );
            }
            break; }
		
        case 0 :
            printf("\nCam on ban da su dung chuong trinh!\n");
            break;

        default:
            printf("\nLua chon khong hop le! Vui long chon lai.\n");
            break ; }
            } while (chonso != 0) ; 
       }
        
	

    int main() {
	int chon;
	do {
        printf("\n==========================================\n");
        printf("            BANG QUAN LY CHI TIEU          \n");
        printf("==========================================\n");
        printf("1. Nhap bang quan ly chi tieu\n");
        printf("2. Nhap so tien dau thang\n");
        printf("3. Xem bao cao va so du\n");
        printf("4. Chinh sua thong tin\n");
        printf("0. Thoat\n");
        printf("------------------------------------------\n");
        printf("LUA CHON:") ;
        scanf ("%d" , &chon ); 
    
    switch (chon) { 
        case 1 : 
			themchitieu() ; 
			break ;
		case 2 :
			themthunhap() ; 
			break ;
		case 3 :
            xembaocao() ;
        	break ;
        case 4 :
        	chinhsua() ;
                break;
        case 0 :
            printf("\nCam on ban da su dung chuong trinh!\n");
            break;

        default:
            printf("\nLua chon khong hop le! Vui long chon lai.\n");
        }
            } while (chon != 0);

    return 0;
    }

   	    	
