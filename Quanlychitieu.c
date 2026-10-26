// part 1 
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

typedef struct { int ngay , thang ,nam ;  double sotien ;  char ghichu[250] ;  } Chitieu ;
typedef struct { int thang , nam ; double sotien  ; }Thunhap ;
//part 2

void xoabodem() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int songaytrongthang(int thang, int nam) {
    if (thang == 2) {
        if ((nam % 4 == 0 && nam % 100 != 0) || nam % 400 == 0) return 29;
        return 28;
    }
    if (thang == 4 || thang == 6 || thang == 9 || thang == 11) return 30;
    return 31;
}

void nhapngay(int *ngay, int *thang, int *nam) {
    while (1) {
        int kq = scanf("%d %d %d", ngay, thang, nam);
        if (kq == EOF) exit(1);
        xoabodem();
        if (kq == 3 && *nam >= 2000 && *nam <= 2100
            && *thang >= 1 && *thang <= 12
            && *ngay >= 1 && *ngay <= songaytrongthang(*thang, *nam)) {
            return;
        }
        printf("  ! Ngay khong hop le. Nhap lai (VD: 23 7 2026): ");
    }
}

void nhapso (int *so) {
	while (1) {
	    int kq = scanf("%d", so);
	    if (kq == EOF) exit(1);
        xoabodem();
        if (kq == 1) {                      
            return;
        }
        printf("  ! Nhap so ko hop le. Nhap lai: ");
	    }
    }

void nhapsotien(double *money) {
    while (1) {
    	int kq = scanf("%lf", money);
    	if (kq == EOF) exit(1);
        xoabodem();
        if (kq == 1 && *money >= 0 ) { return ;}
        printf("  ! So tien khong hop le. Nhap lai: ");
	    }
    }

void nhapthangnam(int *thang, int *nam) {
    while (1) {
        int kq = scanf("%d %d", thang, nam);
        if (kq == EOF) exit(1);
        xoabodem();
        if (kq == 2 && *nam >= 2000 && *nam <= 2100
            && *thang >= 1 && *thang <= 12) {
            return;
        }
        printf("  ! Thang/nam khong hop le. Nhap lai (VD: 7 2026): ");
    }
}

void savefilechitieu(Chitieu ct) {
	FILE *f = fopen("chitieu.txt" , "a" );
	if (f== NULL) {
		printf ("\n ko the mo file\n") ;
		return ; } 
    fprintf(f , "%02d/%02d/%d %.0f %s\n" , ct.ngay , ct.thang , ct.nam , ct.sotien , ct.ghichu );
    fclose(f); }


double laythunhapthang( int thangxem , int namxem ) {
	FILE *f = fopen("thunhap.txt", "r");
	if (f == NULL) return 0; 
	
	Thunhap tn ;
	
	while (fscanf(f, "%d %d %lf", &tn.thang, &tn.nam, &tn.sotien) ==3) {
        if (tn.thang == thangxem && tn.nam == namxem) {
        	fclose(f);
            return tn.sotien;
        } 
    }
    fclose(f);
    return 0; }
    
void themthunhap() {
	Thunhap tn ;
	printf("\n=== Thiet lap thu nhap thang===\n");
	printf("Nhap thang va nam : " ) ; 
	nhapthangnam(&tn.thang, &tn.nam);
	printf(" Nhap thu nhap thang (VND):") ;
	nhapsotien(&tn.sotien);
    int n = 0, cap = 10;
    Thunhap *ds = (Thunhap*) malloc(cap * sizeof(Thunhap));
    if (ds == NULL) { printf("Loi: khong du bo nho\n"); return; }

    FILE *f = fopen("thunhap.txt", "r");
    if (f != NULL) {
        while (1) {
            if (n == cap) {
                cap *= 2;
                Thunhap *mr = (Thunhap*) realloc(ds, cap * sizeof(Thunhap));
                if (mr == NULL) { printf("Loi: khong du bo nho\n"); free(ds); fclose(f); return; }
                ds = mr;
            }
            if (fscanf(f, "%d %d %lf", &ds[n].thang, &ds[n].nam, &ds[n].sotien) != 3) break;
            n++;
        }
        fclose(f);
    }

    int vitri = -1;
    for (int i = 0; i < n; i++) {
        if (ds[i].thang == tn.thang && ds[i].nam == tn.nam) {
            vitri = i;
            break;
        }
    }

    if (vitri == -1) {
        ds[n] = tn;
        n++;
    } else {
        int chon;
        printf("Thang %02d/%d da co thu nhap: %.0f VND\n", tn.thang, tn.nam, ds[vitri].sotien);
        do {
            printf("  1 = Cong them %.0f VND\n  2 = Ghi de thanh %.0f VND\nChon (1 hoac 2): ", tn.sotien, tn.sotien);
            nhapso(&chon);
        } while (chon != 1 && chon != 2);

        if (chon == 1) ds[vitri].sotien += tn.sotien;
        else           ds[vitri].sotien  = tn.sotien;
    }

    f = fopen("thunhap.txt", "w");
    if (f == NULL) { printf("Loi: khong ghi duoc file thunhap.txt\n"); free(ds); return; }
    for (int i = 0; i < n; i++)
        fprintf(f, "%02d %d %.0f\n", ds[i].thang, ds[i].nam, ds[i].sotien);
    fclose(f);
    printf("=> Da luu thu nhap thang %02d/%d thanh cong!\n", tn.thang, tn.nam);
    free(ds);
}

void themchitieu() { 
    int chontiep ;
    do { 
        Chitieu ct ;
        printf("\n=== NHAP KHOAN CHI TIEU MOI ===\n");
        printf("Nhap ngay, thang, nam (Vi du: 23 7 2026): ");
        nhapngay(&ct.ngay, &ct.thang, &ct.nam);
        
        printf("Nhap so tien chi (VND): ");
        nhapsotien(&ct.sotien);
        
        printf("Nhap ghi chu : ");
        scanf(" %249[^\n]", ct.ghichu);

        savefilechitieu(ct);
        printf(" Ða luu khoan chi ngay %02d/%02d/%d thanh cong!\n", ct.ngay, ct.thang, ct.nam);
  
      
	    printf("\n Nhap tiep an 1 ko nhan 0: ");
        nhapso(&chontiep); } 
           while ( chontiep == 1) ; }
           
double tongchithang(int m, int y) {
    FILE *f = fopen("chitieu.txt", "r");
    if (f == NULL) return 0;
    Chitieu ct;
    double tong = 0;
    while (fscanf(f, "%d/%d/%d %lf %249[^\n]", &ct.ngay, &ct.thang, &ct.nam, &ct.sotien, ct.ghichu) == 5) {
        if (ct.thang == m && ct.nam == y) tong += ct.sotien;
    }
    fclose(f);
    return tong;
}

int namdautien() {
    int min = 0;

    FILE *f = fopen("thunhap.txt", "r");
    if (f != NULL) {
        Thunhap tn;
        while (fscanf(f, "%d %d %lf", &tn.thang, &tn.nam, &tn.sotien) == 3) {
            if (min == 0 || tn.nam < min) min = tn.nam;
        }
        fclose(f);
    }

    f = fopen("chitieu.txt", "r");
    if (f != NULL) {
        Chitieu ct;
        while (fscanf(f, "%d/%d/%d %lf %249[^\n]", &ct.ngay, &ct.thang, &ct.nam, &ct.sotien, ct.ghichu) == 5) {
            if (min == 0 || ct.nam < min) min = ct.nam;
        }
        fclose(f);
    }

    return min;  
}

double dutruoc(int m, int y) {
    int namdau = namdautien();
    if (namdau == 0 || namdau > y) return 0;     

    double du = 0;
    for (int nam = namdau; nam <= y; nam++) {
        int thangcuoi = (nam == y) ? m - 1 : 12; 
        for (int t = 1; t <= thangcuoi; t++) {
            du += laythunhapthang(t, nam) - tongchithang(t, nam);
        }
    }
    return du;
}

void xembaocao() { 
int thangxem , namxem ;
    printf("\n=== XEM BAO CAO TAI CHINH ===\n");
    printf("Nhap thang và nam muon xem (Vi du: 7 2026): ");
    nhapthangnam(&thangxem, &namxem);

    double tongthu = laythunhapthang(thangxem, namxem);
    
    FILE *f = fopen("chitieu.txt", "r");

    printf("\n+-----------------------------------------------------------------------+\n");
    printf("| THANG %02d/%d  | Tong tien thu : %.0f VND  |\n", thangxem, namxem, tongthu);
    printf("+-----------------------------------------------------------------------+\n");
    printf("|                          DANH MUC CHI TIEU                            |\n");
    printf("+------------------+-----------------------+----------------------------+\n");
    printf("| Ngay             | So Tien Chi (VND)     | Ghi Chu                    |\n");
    printf("+------------------+-----------------------+----------------------------+\n");

    double tongchi = 0;

    if (f != NULL) {
        Chitieu ct;
        while (fscanf(f, "%d/%d/%d %lf %249[^\n]", &ct.ngay, &ct.thang, &ct.nam, &ct.sotien, ct.ghichu) == 5) {
            if (ct.thang == thangxem && ct.nam == namxem) {
                printf("| %02d/%02d/%-10d | %-21.0f | %-26s |\n", 
                       ct.ngay, ct.thang, ct.nam, ct.sotien, ct.ghichu);
                tongchi += ct.sotien; 
            }
        }
        fclose(f);
    }

    double dutruocthang = dutruoc(thangxem, namxem);
    double sodu = dutruocthang + tongthu - tongchi;
    printf("| Du tu cac thang truoc: %.0f VND\n                                     |\n", dutruocthang);
    
    printf("+-----------------------------------------------------------------------+\n");
    printf("| Tong tieu thang %02d: %-12.lf | So du con lai: %-18.lf VND|\n",thangxem, tongchi, sodu);
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
        nhapso(&chonso); 
    

		switch (chonso) {
        case 1: {
            int thangSua, namSua;
            int timThay = 0;
            
            printf("Nhap thang/nam muon sua (VD: 7 2026): ");
            nhapthangnam(&thangSua, &namSua);

            FILE *f = fopen("thunhap.txt", "r");
            if (f == NULL) {
                printf("Loi: Khong mo duoc file thunhap.txt hoac file chua ton tai!\n");
                break;
            }
            int n = 0, cap = 10, loi = 0 ;
            Thunhap *tn = (Thunhap*) malloc (cap * sizeof(Thunhap)) ;
            if (tn == NULL) {printf("Loi: khong du bo nho\n") ;
			                fclose(f);
							break ;}
            
            while (1) {
			    if(n==cap){
				    cap *= 2;
					Thunhap *mr = (Thunhap*) realloc(tn, cap*sizeof(Thunhap));
					if (mr == NULL){loi=1; break;}
					tn=mr ;}
				if (fscanf(f, "%d %d %lf", &tn[n].thang, &tn[n].nam, &tn[n].sotien) != 3)
                    break;                           

                if (tn[n].thang == thangSua && tn[n].nam == namSua) {
                    printf("Tim thay! So tien hien tai: %.0f\n", tn[n].sotien);
                    printf("Nhap so tien thu nhap moi: ");
                    nhapsotien(&tn[n].sotien);
                    timThay = 1;
                }
                n++;
            }
            fclose(f);
	
            if (loi) {
                printf("Loi: Khong du bo nho, khong luu thay doi!\n");
            }
            else if (timThay) {
                f = fopen("thunhap.txt", "w"); 
                if (f==NULL) {printf("Loi: khong ghi duoc file thunhap.txt\n"); }
                else {
                for (int i = 0; i < n; i++) {
                    fprintf(f, "%02d %d %.0f\n", tn[i].thang, tn[i].nam, tn[i].sotien);
                }
                fclose(f);
                printf("=> Cap nhat khoan thu thanh cong!\n");
                      } 
			   } 
			    else {
                printf("=> Khong tim thay du lieu thu nhap cho thang %d/%d!\n", thangSua, namSua);
            }
            free(tn) ;
			break;
        }
		 
		 
		case 2 : {
			int thangsua , namsua , ngaysua ; 
			int timthay = 0 ;
			
			printf ("Nhap  ngay/thang/nam muon sua :") ;
		    nhapngay(&ngaysua, &thangsua, &namsua);
		    FILE *f = fopen("chitieu.txt" , "r") ;
		    if (f==NULL) {
			     printf("Loi: Khong mo duoc file chitieu.txt hoac file chua ton tai!\n");
                break;
            } 
            
            int n = 0, cap = 10, loi = 0 ;
			Chitieu *ct = (Chitieu*) malloc (cap * sizeof(Chitieu));
			if (ct == NULL) {printf("Loi: khong du bo nho") ;
			                fclose(f);
							break ;}
										
			while (1) {
			    if(n==cap){
				    cap *= 2;
					Chitieu *mr2 = (Chitieu*) realloc(ct, cap*sizeof(Chitieu));
					if (mr2 == NULL){loi=1; break;}
					ct=mr2 ;}
				if (fscanf(f, "%d/%d/%d %lf %249[^\n]" , &ct[n].ngay , &ct[n].thang , &ct[n].nam , &ct[n].sotien , ct[n].ghichu ) != 5 )
                    break;                           

                if ( ct[n].ngay == ngaysua && ct[n].thang == thangsua && ct[n].nam==namsua ) {
			     	printf("Tim thay so tien chi hien tai : %.0f\n" , ct[n].sotien) ;
			     	printf("Nhap so tien chi moi: ");
                    nhapsotien(&ct[n].sotien);
                    timthay = 1;
                }
                n++;
            }
            fclose(f);
							
			
			if (loi) {
                printf("Loi: Khong du bo nho, khong luu thay doi!\n");
            }
            else if(timthay) { 
			   f = fopen("chitieu.txt", "w") ;
			    if (f == NULL) {
                    printf("Loi: Khong ghi duoc file chitieu.txt!\n");
                    free(ct);
                    break;
                }
			   else {for(int i = 0 ; i < n ; i++) { 
			       fprintf(f ,"%02d/%02d/%d %.0f %s\n" , ct[i].ngay , ct[i].thang , ct[i].nam , ct[i].sotien , ct[i].ghichu ) ;  
			    }
            fclose(f) ;
            printf("=> Cap nhat khoan chi thanh cong!\n"); }
            } else {
                printf("=> Khong tim thay du lieu chi tieu cho ngay %02d/%02d/%d!\n", ngaysua, thangsua , namsua );
            }
            free(ct);
            break; }
            
            
        case 3 : {
            int thangsua , namsua , ngaysua ; 
			int timthay = 0 ;
			
			printf ("Nhap ngay/thang/nam muon sua :") ;
		    nhapngay(&ngaysua, &thangsua, &namsua);
		    FILE *f = fopen("chitieu.txt" , "r") ;
		    if (f== NULL) {
			     printf("Loi: Khong mo duoc file chitieu.txt hoac file chua ton tai!\n");
                break;
            } 
			int n = 0, cap = 10, loi = 0 ;
			Chitieu *ct = (Chitieu*) malloc (cap * sizeof(Chitieu));
			if (ct == NULL) {printf("Loi: khong du bo nho") ;
			                fclose(f);
							break ;}	
			while (1) {
			    if(n==cap){
				    cap *= 2;
					Chitieu *mr3 = (Chitieu*) realloc(ct, cap*sizeof(Chitieu));
					if (mr3 == NULL){loi=1; break;}
					ct=mr3 ;}
				if (fscanf(f, "%d/%d/%d %lf %249[^\n]" , &ct[n].ngay , &ct[n].thang , &ct[n].nam , &ct[n].sotien , ct[n].ghichu ) != 5 )
                    break;  				
				
				if ( ct[n].ngay == ngaysua && ct[n].thang == thangsua && ct[n].nam== namsua ) {
			     	printf("Tim thay ghi chu hien tai : %s\n" , ct[n].ghichu) ;
			     	printf("Nhap ghi chu moi: ");
                    scanf(" %249[^\n]", ct[n].ghichu);
                    timthay = 1;
                }
                n++;
            }
            fclose(f);
            
            if (loi) {
                printf("Loi: Khong du bo nho, khong luu thay doi!\n");
            }
            else if(timthay) { 
			   f = fopen("chitieu.txt", "w") ;
			     if (f == NULL) {
                    printf("Loi: Khong ghi duoc file chitieu.txt!\n");
                    free(ct);
                    break;
                }
			     else { for(int i = 0 ; i < n ; i++) { 
			       fprintf(f,"%02d/%02d/%d %.0f %s\n", ct[i].ngay, ct[i].thang, ct[i].nam, ct[i].sotien, ct[i].ghichu);
			    }
            fclose(f) ;
            printf("=> Cap nhat ghi chu thanh cong!\n"); }
            } 
			else {
                printf("=> Khong tim thay du lieu khoan chi cho ngay %02d/%02d/%d!\n", ngaysua, thangsua , namsua );
            }
            free(ct) ;
            break; }
		
        case 0 :
            printf("\nQuay lai menu chinh!\n");
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
        printf("2. Nhap so thu nhap thang\n");
        printf("3. Xem bao cao va so du\n");
        printf("4. Chinh sua thong tin\n");
        printf("0. Thoat\n");
        printf("------------------------------------------\n");
        printf("LUA CHON:") ;
        nhapso(&chon); 
    
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

   	    	
