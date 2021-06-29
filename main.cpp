#include <iomanip>
#include "mylib.h"
#include "KhaiBao.h"

//define function
char* trim(char *str);
void BaoLoi (char *s);
void AddLinkedSV(LinkedSV &First, SinhVien &data);
bool kiemTraMaSV(LinkedSV &First, char input[]);
void Delete_LinkedSV(LinkedSV &First,SinhVien &sv);
char scanner(char source[]);
int  ChonGioiTinh();
int  NhapSinhVien(SinhVien &data);
void hienThiSinhVien(SinhVien &sv);
int  LengthLinkedSV(LinkedSV &first);
void LinkedToArray(SinhVien des[],LinkedSV &source);
bool HienThiDanhSachSinhVien(LinkedSV &linkedSV);
void OpenFileSinhVien(LinkedSV &First, char *filename);
void SaveFileSinhVien(LinkedSV &First,char *filename);

void TangDanHoTenSinhVien(SinhVien* arr,int length);
void findAllSVByMaLop(char *maLop,LinkedSV &linkedSV,SinhVien *arr,int length);
void HienThiDSSVTangDanTheoHoTen(LinkedSV &linkedSV);
int TimKiemSinhVienByMaSV(SinhVien *arr,int length);


void HienThiMonHoc(MonHoc monHoc);
void HienThiDanhSachMonHoc(TreeBinarySearch &root);
void TreeToArray(TreeBinarySearch root,int &count,MonHoc *monHoc);
void LengthTree(TreeBinarySearch root,int &count);
void UpdateTree(TreeBinarySearch &root,MonHoc monHoc);
void InsertTree(TreeBinarySearch &root,MonHoc monHoc);
int NhapMonHoc(TreeBinarySearch &root,MonHoc &data,int key);
TreeBinarySearch SearchTree(TreeBinarySearch root,char *maMH);
bool kiemTraMaMH(TreeBinarySearch &root,char *maMH);
void DeleteTree(TreeBinarySearch &root,char *maMH);
void TimNodeTheMang(TreeBinarySearch x,TreeBinarySearch y);
void SaveMonHoc(TreeBinarySearch root,FILE * f);
void SaveFileMonHoc(TreeBinarySearch root,char *filename);
void OpenFileMonHoc(TreeBinarySearch &root,char *filename);
void HienThiDSMHTangDanTenMonHoc(TreeBinarySearch root);
void TangDanTenMonHoc(MonHoc *arr,int length);

//---------------------------HAM CHUNG------------------------------
char scanner(char source[]){

	char ketqua[100];
	bool loop = true;
	int i = 0;
	int x0 = wherex(); int y0 = wherey();
	int x,y;
	while(loop){
		x = wherex(); y = wherey();
		char kytu = getch();
		if( x == x0 && y == y0 && kytu == 8 ){
			gotoxy(x0,y0);
		} else {
			cout<<kytu;
		}
		if( kytu == 13 || i >= 98){
			ketqua[i] = '\0';
			strcpy(source,ketqua);
			return 13;
		}
		else if(kytu == 27){
			return 27;
		}
		else if(kytu == Up){
			return 72;
		}
		else if(kytu == Down){
			return 80;
		}
		else if(kytu == Left){
			return 75;
		}
		else if(kytu == Right){
			return 77;
		}
		else if(kytu == 8){
			if(i <= 0){
				i = 0;
			}
			else i--;

			x = wherex(); y = wherey();
			gotoxy(x,y);
			cout<<" ";
			gotoxy(x,y);
		}
		else {
			ketqua[i] = kytu;
			i++;
		}
	}
}

//---------------------DANH SACH SINH VIEN------------------------
void AddLinkedSV(LinkedSV &First, SinhVien &data){
	LinkedSV p = new nodesv;
	p->data = data;
	p->next = First;
	First = p;
}

void UpdateLinkedSV(LinkedSV &First, SinhVien &data){
	LinkedSV p = First;
	while(p != NULL) {
		if(!strcmp(p->data.MASV, data.MASV)){
			p->data = data;
			break;
		}
		p = p->next;
	}
}

//Neu co trung thi return true else false
bool kiemTraMaSV(LinkedSV &First, char input[]) {
	LinkedSV p = First;
	while(p != NULL) {
		SinhVien sv = p->data;
		if (!strcmp(sv.MASV, input)) return true;
		p = p->next;
	}
	return false;
}


void Delete_LinkedSV(LinkedSV &First, SinhVien &sv){
	LinkedSV q;
  if (First==NULL ) return;

	// Del phan tu dau
	if (!strcmp(First->data.MASV,sv.MASV)){
		LinkedSV temp = First;
		First = temp->next;
		delete temp;
	}
	if (First==NULL ) return;


	for (LinkedSV p = First; p->next != NULL;){
		if (!strcmp(p->next->data.MASV, sv.MASV) ) {
				q = p->next;
				p->next = q->next;
				delete q;
			}
		else p = p->next;
	}
}

int ChonGioiTinh(){
  int so_item = 2;
  char td [so_item][50] = {"Nam", "Nu"};
  int chon = 0;
  int i;
  int cot = wherex(); int dong = wherey();
  HighLight();
  gotoxy(cot ,dong);
  cout << td[chon];
  char kytu;
  do {
		kytu = getch();
		if (kytu==-32) kytu = getch();
		switch (kytu) {
			case Up: if (chon > 0)
				{
					Normal();
					gotoxy(cot,dong);		cout << "   ";
					chon--;
					HighLight();
					gotoxy(cot,dong); 	cout << td[chon];
				}
				break;

			case Down: if (chon+1 <so_item)
				{
					Normal();
					gotoxy(cot,dong);		cout << "   ";
					chon++;
					HighLight();
					gotoxy(cot,dong); 	cout << td[chon];
				}
					break;

			case Enter:
				{
					Normal();
					gotoxy(cot,dong); 	cout << td[chon];
					return chon+1;
				}
	  }  // end switch
  } while (true);
}

int NhapSinhVien(LinkedSV &linkedSV,SinhVien &data,int key){
	int so_item = 6;
	char td [so_item][100] = {"MASV :                                                       ",
							"HO   :                                                       ",
							"TEN  :                                                       ",
							"PHAI :                                                       ",
							"SDT  :                                                       ",
							"MALOP:                                                       "};
	Normal();
	system("cls");   int chon =0;
	int i;
	for ( i=0; i< so_item ; i++){
		gotoxy(cot, dong +i);
		cout << td[i];
		if(key == Home){
			gotoxy(cot+6,dong+i);
			if(i == 0) cout<<data.MASV;
			if(i == 1) cout<<data.HO;
			if(i == 2) cout<<data.TEN;
			if(i == 3){
				if(data.PHAI) cout<<"Nam";
				else cout<<"Nu";
			}
			if(i == 4) cout<<data.SDT;
			if(i == 5) cout<<data.MALOP;
		}
	}
	if(key == Home) chon++; //tang chon bo qua ma sinh vien
	HighLight();
	gotoxy(cot,dong+chon);
	cout << td[chon];
	gotoxy(cot+6,dong+chon);
	char kytu;
	do {
		char temp[100]="";
		kytu = scanner(temp);
		switch (kytu) {
			case Up :if (chon >0) {
				Normal();
				gotoxy(cot,dong+chon);cout << td[chon];
				gotoxy(cot+6,dong+chon);

				if(chon == 0) cout<<data.MASV;
				if(chon == 1) cout<<data.HO;
				if(chon == 2) cout<<data.TEN;
				if(chon == 3){
					if(data.PHAI) cout<<"Nam";
					else cout<<"Nu";
				}
				if(chon == 4) cout<<data.SDT;
				if(chon == 5) cout<<data.MALOP;

				chon --;
				HighLight();
				gotoxy(cot,dong+chon); 	cout << td[chon];
				gotoxy(cot+6,dong+chon);
			}
			break;

			case Down :if (chon+1 <so_item) {
				Normal();
				gotoxy(cot,dong+chon);	cout << td[chon];
				gotoxy(cot+6,dong+chon);
				if(chon == 0) cout<<data.MASV;
				if(chon == 1) cout<<data.HO;
				if(chon == 2) cout<<data.TEN;
				if(chon == 3){
					if(data.PHAI) cout<<"Nam";
					else cout<<"Nu";
				}
				if(chon == 4) cout<<data.SDT;
				if(chon == 5) cout<<data.MALOP;
				chon ++;
				HighLight();
				gotoxy(cot,dong+chon); 	cout << td[chon];
				gotoxy(cot+6,dong+chon);
			}
			break;

			case Enter: if (chon+1 <=so_item) {
				Normal();
				gotoxy(cot,dong+chon);	cout << td[chon];
				gotoxy(cot+6,dong+chon); cout<< temp;

				//truong hop cap nhat khong cho sua ma sinh vien
				if(chon == 0 && key == Insert) {
					if(kiemTraMaSV(linkedSV, temp)) return 2;
					else strcpy(data.MASV,temp);
				}

				if(chon == 1) strcpy(data.HO,temp);
				if(chon == 2) strcpy(data.TEN,temp);
				if(chon == 3) {
					ChonGioiTinh() == 1 ? data.PHAI = 1 : data.PHAI = 0;
				}
				if(chon == 4) {strcpy(data.SDT,temp);data.SDT[12] = '\0';}
				if(chon == 5){
					//check du lieu cac truong roi save --> linkedSV
					strcpy(data.MALOP,temp);
					return 1;
				}
				chon ++;
				HighLight();
				gotoxy(cot,dong+chon); 	cout << td[chon];
				gotoxy(cot+6,dong+chon);
			  }
			  break;

			case ESC: return 0;
		}  // end switch
	} while (true);
}

void hienThiSinhVien(SinhVien &sv){
	cout << setw(20) << left << sv.MASV;
	cout << setw(50) << left << sv.HO;
	cout << setw(20) << left << sv.TEN;
	if(sv.PHAI == 1) cout << setw(20) << left << "Nam";
	else cout << setw(20) << left << "Nu";
	cout << setw(20) << left << sv.SDT;
	cout << setw(20) << left << sv.MALOP;
}

int LengthLinkedSV(LinkedSV &first){
	int count = 0;
	for(LinkedSV p = first;p != NULL;p=p->next){
		count++;
	}
	return count;
}

void LinkedToArray(SinhVien des[],LinkedSV &source){
	LinkedSV First = source;
	if(First != NULL){
		int index = 0;
		for(LinkedSV p = First;p!=NULL;p=p->next){
			des[index] = p->data;
			index++;
		}
	}
}


bool HienThiDanhSachSinhVien(LinkedSV &linkedSV){
  int searchKey = 0;
  int x = 0 ; int y = 0;
  int length = LengthLinkedSV(linkedSV);
  SinhVien *sinhVien = new SinhVien[length];
  LinkedToArray(sinhVien,linkedSV);

  int so_item = length;
  int chon = 0;
  int i;
  char kytu; bool isTrue = true;

	do {
		SinhVien temp;
		if(isTrue){
			Normal();
			system("cls");
			gotoxy(x,y);

			cout << setw(20) << left << "MASV";
			cout << setw(50) << left << "HO";
			cout << setw(20) << left << "TEN";
			cout << setw(20) << left << "Phai";
			cout << setw(20) << left << "SDT";
			cout << setw(20) << left << "MALOP"<<endl;
			cout << setfill('-');
			cout << setw(150) << "-" << endl;
			cout << setfill(' ');

//			gotoxy(190,1); cout<<"Insert : Them";
//			gotoxy(190,2); cout<<"Home: Cap Nhat";
//			gotoxy(190,3); cout<<"Delete : Xoa";



			if(linkedSV != NULL){
				for ( i=0; i< so_item ; i++){
					gotoxy(x,y+1+i);
					hienThiSinhVien(sinhVien[i]);
				}

				HighLight();
				gotoxy(x,y+chon+1);
				hienThiSinhVien(sinhVien[chon]);
			}
		}
		isTrue = false;

		kytu = getch();
		if (kytu==-32) kytu = getch();
		switch (kytu) {
			case Up :if (chon >0) {
				Normal();
				gotoxy(x,y+chon+1);
				hienThiSinhVien(sinhVien[chon]);
				chon --;
				HighLight();
				gotoxy(x,y+chon+1);
				hienThiSinhVien(sinhVien[chon]);
			}
			break;

			case Down :if (chon+1 <so_item) {
				Normal();
				gotoxy(x,y+chon+1);
				hienThiSinhVien(sinhVien[chon]);
				chon ++;
				HighLight();
				gotoxy(x,y+chon+1);
				hienThiSinhVien(sinhVien[chon]);
			}
			break;

			case Insert:{
				int check = NhapSinhVien(linkedSV,temp,Insert);
				if( check == 1){
					AddLinkedSV(linkedSV,temp);
					length = LengthLinkedSV(linkedSV);
					delete [] sinhVien;
					sinhVien = new SinhVien[length];
					LinkedToArray(sinhVien,linkedSV);
					chon = length - 1;
					so_item = length;
				}
				if(check == 2){
					BaoLoi("Ma sinh vien bi trung");
				}
				isTrue = true;
			}
			break;

			case Home:{
				NhapSinhVien(linkedSV,sinhVien[chon],Home);
				UpdateLinkedSV(linkedSV,sinhVien[chon]);
				length = LengthLinkedSV(linkedSV);
				delete [] sinhVien;
				sinhVien = new SinhVien[length];
				LinkedToArray(sinhVien,linkedSV);
				chon = length - 1;
				so_item = length;
				isTrue = true;
			}
			break;

			case DEL:{
				Delete_LinkedSV(linkedSV,sinhVien[chon]);
				length = LengthLinkedSV(linkedSV);
				delete [] sinhVien;
				sinhVien = new SinhVien[length];
				LinkedToArray(sinhVien,linkedSV);
				chon = length - 1;
				so_item = length;
				isTrue = true;
			}
			break;

			case End:{
					searchKey = TimKiemSinhVienByMaSV(sinhVien,so_item);
					if(searchKey != -1){
						Normal();
						gotoxy(x,y+chon+1);
						hienThiSinhVien(sinhVien[chon]);
						chon = searchKey;
						HighLight();
						gotoxy(x,y+chon+1);
						hienThiSinhVien(sinhVien[chon]);
					}

				}
				break;

			case ESC: return 0;
		}
  } while (true);
}


void TangDanHoTenSinhVien(SinhVien* arr,int length){
	for(int i=0;i<length;i++){
		for(int j=i+1;j<length;j++){
			int k = strcmp(arr[i].TEN,arr[j].TEN);
			if(k == 1){
				SinhVien temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			else if(k == 0){
				int p = strcmp(arr[i].HO,arr[j].HO);
				if(p == 1){
					SinhVien temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}
		}
	}
}

//notdone
//tim kiem tuyen tinh con yeu
int TimKiemSinhVienByMaSV(SinhVien *arr,int length){
	gotoxy(170,1);
	Normal();
	cout<<"                                     ";
	gotoxy(170,1);
	Normal();
	char maSV[100];
	cout<<"Ma sinh vien:";
	if(scanner(maSV) == ESC){
		gotoxy(170,1);
		Normal();
		cout<<"                                     ";
		return -1;
	}

	int i = 0;
	while(strcmp(arr[i].MASV,maSV) != 0 && i < length)
		i++;
	if(i == length) i = 0;
	return i;
}

void findAllSVByMaLop(char *maLop,LinkedSV &linkedSV,LinkedSV &results,int &lengthArrSV){
	SinhVien data; int count=0;
	for(LinkedSV p = linkedSV ; p != NULL ; p=p->next){
		if(!strcmp(maLop,p->data.MALOP)){
			count ++;
			data = p->data;
			AddLinkedSV(results,data);
		}
	}
	lengthArrSV = count;
}

void HienThiDSSVTangDanTheoHoTen(LinkedSV &linkedSV){
  	int x = 0 ; int y = 0;
  	SinhVien *arrSV; LinkedSV First = NULL;
  	int so_item = 0;
  	int chon = 0;
  	int i; char maLop[100];

	Normal();
	system("cls");
	gotoxy(x,y);
	cout << setw(20) << left << "Nhap Ma Lop:";
	gotoxy(x+12,y);

	scanner(maLop);
	findAllSVByMaLop(maLop,linkedSV,First,so_item);
	arrSV = new SinhVien[so_item];
	LinkedToArray(arrSV,First);

	TangDanHoTenSinhVien(arrSV,so_item);

	Normal();
	system("cls");
	gotoxy(x,y);
	cout << setw(20) << left << "MASV";
	cout << setw(50) << left << "HO";
	cout << setw(20) << left << "TEN";
	cout << setw(20) << left << "Phai";
	cout << setw(20) << left << "SDT";
	cout << setw(20) << left << "MALOP"<<endl;
	cout << setfill('-');
	cout << setw(150) << "-" << endl;
	cout << setfill(' ');

	if(linkedSV != NULL){
		for ( i=0; i< so_item ; i++){
			gotoxy(x,y+1+i);
			hienThiSinhVien(arrSV[i]);
		}
	}

	getch();
}


void HienThiDSMHTangDanTenMonHoc(TreeBinarySearch root){
  	int x = 0 ; int y = 0;
  	MonHoc *arr;
  	int so_item = 0;
  	int chon = 0;
  	int i;int lengthArr = 0; int count = 0;
  	LengthTree(root,lengthArr);
  	arr = new MonHoc[lengthArr];
  	TreeToArray(root,count,arr);
	so_item = lengthArr;

	TangDanTenMonHoc(arr,so_item);

	Normal();
    system("cls");
    gotoxy(x,y);

	cout << setw(10) << left << "MAMH";
	cout << setw(30) << left << "TENMH";
	cout << setw(20) << left << "STCLT";
	cout << setw(20) << left << "STCTH"<<endl;

	cout << setfill('-');
	cout << setw(80) << "-" << endl;
	cout << setfill(' ');

	if(root != NULL){
		for ( i=0; i< so_item ; i++){
			gotoxy(x,y+1+i);
			HienThiMonHoc(arr[i]);
		}
	}

	getch();
}


void TangDanTenMonHoc(MonHoc *arr,int length){
	for(int i=0;i<length;i++){
		for(int j=i+1;j<length;j++){
			if(strcmp(arr[i].TENMH,arr[j].TENMH) > 0){
				MonHoc temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

//----------------------------------LOP TIN CHI-------------------------------------
void hienThiLopTinChi(LopTinChi &lopTC){
	cout << setw(20) << left << lopTC.MALOPTC;
	cout << setw(20) << left << lopTC.MAMH;
	cout << setw(20) << left << lopTC.NienKhoa;
	cout << setw(20) << left << lopTC.HocKy;
	cout << setw(20) << left << lopTC.Nhom;
	cout << setw(20) << left << lopTC.MinSV;
	cout << setw(20) << left << lopTC.MaxSV;
}

int HuyLop(){
  int so_item = 2;
  char td [so_item][50] = {"false","true"};
  int chon = 0;
  int i;
  int cot = wherex(); int dong = wherey();
  HighLight();
  gotoxy(cot ,dong);
  cout << td[chon];
  char kytu;
  do {
		kytu = getch();
		if (kytu==-32) kytu = getch();
		switch (kytu) {
			case Up :if (chon > 0) {
				Normal();
				gotoxy(cot,dong);	cout << "   ";
				chon --;
				HighLight();
				gotoxy(cot,dong); 	cout << td[chon];
			}
			break;

			case Down :if (chon+1 <so_item) {
				Normal();
				gotoxy(cot,dong);	cout << "   ";
				chon ++;
				HighLight();
				gotoxy(cot,dong); 	cout << td[chon];
			}
			break;

			case Enter : {
				Normal();
				gotoxy(cot,dong); 	cout << td[chon];
				return chon;
			}
	  }  // end switch
  } while (true);
}

int maxMaLopTC (DSLopTinChi dsLopTinChi) {
	int max = 0;
	int n = dsLopTinChi.n;
	if (n == 0) return max+1;
	for (int i = 0; i < n; i++) {
		LopTinChi lopTC = *dsLopTinChi.nodes[i];
		if (lopTC.MALOPTC > max) max = lopTC.MALOPTC;
	}
	return max+1;
}

int NhapLopTinChi(DSLopTinChi dsLopTinChi, LopTinChi &lopTC){
	int so_item = 8;
	int maLopTC = maxMaLopTC(dsLopTinChi);
	char td [so_item][100] = {"MALOPTC  :                                                       ",
							  "MA MH    :                                                       ",
							  "NIEN KHOA:                                                       ",
							  "HOC KY   :                                                       ",
							  "NHOM     :                                                       ",
							  "SO SV MIN:                                                       ",
							  "SO SV MAX:                                                       ",
							  "HUY LOP	:                                                       "};
	Normal();
	system("cls");
	int chon = 1;
	int i;
	for ( i=0; i< so_item ; i++) {
		gotoxy(cot, dong +i);
		cout << td[i];
		if(i == 0) cout << maLopTC;
	}
	HighLight();
	gotoxy(cot, dong+chon);
	cout << td[chon];
	gotoxy(cot+11, dong+chon);
	char kytu;
	do {
		char temp[100]="";
		kytu = scanner(temp);
		switch (kytu) {
			case Up :if (chon >1) {
				Normal();
				gotoxy(cot, dong+chon);
				cout << td[chon];
				gotoxy(cot+11, dong+chon);
				if(chon == 1) cout << lopTC.MAMH;
				if(chon == 2) cout << lopTC.NienKhoa;
				if(chon == 3) cout << lopTC.HocKy;
				if(chon == 4) cout << lopTC.Nhom;
				if(chon == 5) cout << lopTC.MinSV;
				if(chon == 6) cout << lopTC.MaxSV;
				if(chon == 7) cout << lopTC.HuyLop;
				chon --;
				HighLight();
				gotoxy(cot, dong+chon); 	cout << td[chon];
				gotoxy(cot+11, dong+chon);

			}
			break;

			case Down :if (chon+1 < so_item) {
				Normal();
				gotoxy(cot, dong+chon);	cout << td[chon];
				gotoxy(cot+11, dong+chon);
				if(chon == 0) cout << maLopTC;
				if(chon == 1) cout << lopTC.MAMH;
				if(chon == 2) cout << lopTC.NienKhoa;
				if(chon == 3) cout << lopTC.HocKy;
				if(chon == 4) cout << lopTC.Nhom;
				if(chon == 5) cout << lopTC.MinSV;
				if(chon == 6) cout << lopTC.MaxSV;
				if(chon == 7) cout << lopTC.HuyLop;
				chon ++;
				HighLight();
				gotoxy(cot, dong+chon); 	cout << td[chon];
				gotoxy(cot+11, dong+chon);
			}
			break;

//			case Enter: if (chon+1 <= so_item) {
//				lopTC.MALOPTC = maLopTC;
//				Normal();
//				gotoxy(cot, dong+chon);	cout << td[chon];
//				gotoxy(cot+11, dong+chon); cout<< temp;
//				if(chon == 1) strcpy(lopTC.MAMH, temp);
//				if(chon == 2) {
//					int nienKhoa		= atoi(temp);
//					lopTC.NienKhoa		= nienKhoa;
//				}
//				if(chon == 3) strcpy(lopTC.HocKy, temp);
//				if(chon == 4) strcpy(lopTC.Nhom, temp);
//				if(chon == 5) {
//					int minSV			= atoi(temp);
//					lopTC.MinSV 		= minSV;
//				}
//				if(chon == 6) {
//					int maxSV			= atoi(temp);
//					lopTC.MaxSV 		= maxSV;
//				}
//				if(chon == 7){
//					HuyLop() == 1 ? lopTC.HuyLop = 1 : lopTC.HuyLop = 0;
//					return 1;
//				}
//				chon ++;
//				HighLight();
//				gotoxy(cot,dong+chon); 	cout << td[chon];
//				gotoxy(cot+11,dong+chon);
//			}
//			break;

			case ESC: return 0;
		}  // end switch
	} while (true);
}

void InsertLopTinChi(DSLopTinChi &dsLopTinChi, LopTinChi &lopTC) {
	int n = dsLopTinChi.n;
	NhapLopTinChi(dsLopTinChi, lopTC);
	dsLopTinChi.nodes[n] = new LopTinChi;
	*dsLopTinChi.nodes[n] = lopTC;
	dsLopTinChi.n++;
}

bool HienThiDanhSachLopTinChi(DSLopTinChi &dsLopTinChi){
  int searchKey = 0;
  int x = 0; int y = 0;
  int so_item = dsLopTinChi.n;
  int chon = 0;
  int i;
  char kytu;
  bool isTrue = true;

	do {
		LopTinChi lopTC;
		if(isTrue) {
			Normal();
			system("cls");
			gotoxy(x,y);

			cout << "DANH SACH LOP TIN CHI" << endl;
			cout << setw(20) << left << "MALOPTC";
			cout << setw(20) << left << "MAMH";
			cout << setw(20) << left << "NiEN KHOA";
			cout << setw(20) << left << "HOC KY";
			cout << setw(20) << left << "NHOM";
			cout << setw(20) << left << "SO SV MIN";
			cout << setw(20) << left << "SO SV MAX" <<endl;

			cout << setfill('-');
			cout << setw(150) << "-" << endl;
			cout << setfill(' ');

			if(dsLopTinChi.n != 0){
				for (i = 0; i < so_item; i++){
					gotoxy(x,y+3+i);
					hienThiLopTinChi(*dsLopTinChi.nodes[i]);
				}

				HighLight();
				gotoxy(x,y+chon+3);
				hienThiLopTinChi(*dsLopTinChi.nodes[chon]);
			}
		}
		isTrue = false;

		kytu = getch();
		if (kytu==-32) kytu = getch();
		switch (kytu) {
			case Up :if (chon >0) {
				Normal();
				gotoxy(x,y+chon+3);
				hienThiLopTinChi(*dsLopTinChi.nodes[chon]);
				chon --;
				HighLight();
				gotoxy(x,y+chon+3);
				hienThiLopTinChi(*dsLopTinChi.nodes[chon]);
			}
			break;

			case Down :if (chon+1 <so_item) {
				Normal();
				gotoxy(x,y+chon+3);
				hienThiLopTinChi(*dsLopTinChi.nodes[chon]);
				chon ++;
				HighLight();
				gotoxy(x,y+chon+3);
				hienThiLopTinChi(*dsLopTinChi.nodes[chon]);
			}
			break;

			case Insert: {
				InsertLopTinChi(dsLopTinChi, lopTC);
				so_item = dsLopTinChi.n;
				isTrue = true;
			}
			break;

	//	case Home:{
	////				UpdateSinhVien(sinhVien[chon],linkedSV);
	//				length = LengthLinkedSV(linkedSV);
	//				delete [] sinhVien;
	// 				sinhVien = new SinhVien[length];
	//				LinkedToArray(sinhVien,linkedSV);
	//				chon = length - 1;
	//				so_item = length;
	//				isTrue = true;
	//				}
	//				break;

	//	case DEL:
	//  				{
	//				Delete_LinkedSV(linkedSV,sinhVien[chon]);
	//				length = LengthLinkedSV(linkedSV);
	//				delete [] sinhVien;
	// 				sinhVien = new SinhVien[length];
	//				LinkedToArray(sinhVien,linkedSV);
	//				chon = length - 1;
	//				so_item = length;
	//				isTrue = true;
	//				}
	//				break;

		} // end switch
	} while (true);
}

void HienThiDanhSachMonHoc(TreeBinarySearch &root){
  int searchKey = 0;
  int x = 0 ; int y = 0;
  int lengthTree = 0;
  int count = 0;
  LengthTree(root,lengthTree);
  MonHoc *monHoc = new MonHoc[lengthTree];
  TreeToArray(root,count,monHoc);

  int so_item = lengthTree;
  int chon = 0;
  int i;
  char kytu; bool isTrue = true;


do {
	MonHoc temp;
    if(isTrue){
    Normal();
    system("cls");
    gotoxy(x,y);

	cout << setw(10) << left << "MAMH";
	cout << setw(30) << left << "TENMH";
	cout << setw(20) << left << "STCLT";
	cout << setw(20) << left << "STCTH"<<endl;





	cout << setfill('-');
	cout << setw(80) << "-" << endl;
	cout << setfill(' ');


  if(root != NULL){
  	for ( i=0; i< so_item ; i++){
	  	gotoxy(x,y+1+i);
	  	HienThiMonHoc(monHoc[i]);
  	}

  	HighLight();
  	gotoxy(x,y+chon+1);
  	HienThiMonHoc(monHoc[chon]);
  }




  }
  isTrue = false;


  kytu = getch();
  if (kytu==-32) kytu = getch();
  switch (kytu) {
    case Up :if (chon >0)
  			  {
  		        Normal();
              	gotoxy(x,y+chon+1);
				HienThiMonHoc(monHoc[chon]);
              	chon --;
              	HighLight();
              	gotoxy(x,y+chon+1);
				HienThiMonHoc(monHoc[chon]);
  			  }
  			  break;
  	case Down :if (chon+1 <so_item)
  			  {
  		        Normal();
              	gotoxy(x,y+chon+1);
              	HienThiMonHoc(monHoc[chon]);
              	chon ++;
              	HighLight();
              	gotoxy(x,y+chon+1);
              	HienThiMonHoc(monHoc[chon]);

  			  }
  			  break;

  	case DEL:
  				{
				DeleteTree(root,monHoc[chon].MAMH);
				lengthTree = 0;
				count = 0;
				LengthTree(root,lengthTree);
				delete [] monHoc;
 				monHoc = new MonHoc[lengthTree];
				TreeToArray(root,count,monHoc);
				chon = lengthTree - 1;
				so_item = lengthTree;
				isTrue = true;
				}
				break;
	case Insert:{
				int check = NhapMonHoc(root,temp,Insert);
				if(check == 1){
					InsertTree(root,temp);
					lengthTree = 0;
					count = 0;
					LengthTree(root,lengthTree);
					delete [] monHoc;
	 				monHoc = new MonHoc[lengthTree];
					TreeToArray(root,count,monHoc);
					chon = lengthTree - 1;
					so_item = lengthTree;
				}
				if(check == 2){
					BaoLoi("Ma mon hoc bi trung");
				}
				isTrue = true;
				}
				break;

	case Home:{
				NhapMonHoc(root,monHoc[chon],Home);
				UpdateTree(root,monHoc[chon]);
				lengthTree = 0;
				count = 0;
				LengthTree(root,lengthTree);
				delete [] monHoc;
 				monHoc = new MonHoc[lengthTree];
				TreeToArray(root,count,monHoc);
				chon = lengthTree - 1;
				so_item = lengthTree;
				isTrue = true;
				}
				break;

  	case ESC   : {
		  		delete [] monHoc;
		  		return;
	 			 }

//	case End   :{
//				searchKey = TimKiemDocGiaByMADG(docGia,so_item);
//				chon = searchKey;
//				isTrue = true;
//				break;
//				}


  }  // end switch
  } while (true);
}


void HienThiMonHoc(MonHoc monHoc){

	cout << setw(10) << left << monHoc.MAMH;
	cout << setw(30) << left << trim(monHoc.TENMH);
	cout << setw(20) << left << monHoc.STCLT;
	cout << setw(20) << left << monHoc.STCTH;
}


void TreeToArray(TreeBinarySearch root,int &count,MonHoc *monHoc){
	if(root == NULL){
		return;
	}
	else{
		TreeToArray(root->left,count,monHoc);
		monHoc[count] = root->data;
		count++;
		TreeToArray(root->right,count,monHoc);
	}
}


void LengthTree(TreeBinarySearch root,int &count){
	if(root == NULL){
		return;
	}
	else{
		LengthTree(root->left,count);
		count++;
		LengthTree(root->right,count);
	}
}

void UpdateTree(TreeBinarySearch &root,MonHoc monHoc){
	if(root == NULL){
		return;
	}else{
		UpdateTree(root->left,monHoc);
		if(!strcmp(monHoc.MAMH,root->data.MAMH)){
			root->data = monHoc;
		}
		UpdateTree(root->right,monHoc);
	}
}

void InsertTree(TreeBinarySearch &root,MonHoc monHoc){
	if(root == NULL){
		root = new nodemh;
		root->data = monHoc;
		root->left = NULL;
		root->right = NULL;
	}
	else {
		if(strcmp(root->data.MAMH,monHoc.MAMH) > 0){
			InsertTree(root->left,monHoc);
		}
		else if(strcmp(root->data.MAMH,monHoc.MAMH) < 0){
			InsertTree(root->right,monHoc);
		}
	}
}

int NhapMonHoc(TreeBinarySearch &root,MonHoc &data,int key){
	int so_item = 4;
	char td [so_item][100] = {
							"MAMH :                                                       ",
							"TENMH:                                                       ",
							"STCLT:                                                       ",
							"STCTH:                                                       "
							};
	Normal();
	system("cls");   int chon =0;
	int i;
	for ( i=0; i< so_item ; i++){
		gotoxy(cot, dong +i);
		cout << td[i];
		if(key == Home){
			gotoxy(cot+6,dong+i);
			if(i == 0) cout<<data.MAMH;
			if(i == 1) cout<<data.TENMH;
			if(i == 2) cout<<data.STCLT;
			if(i == 3) cout<<data.STCTH;
		}
	}
	if(key == Home) chon++;
	HighLight();
	gotoxy(cot,dong+chon);
	cout << td[chon];
	gotoxy(cot+6,dong+chon);
	char kytu;
	do {
		char temp[100]="";
		kytu = scanner(temp);
		switch (kytu) {
			case Up :if (chon >0) {
				Normal();
				gotoxy(cot,dong+chon);cout << td[chon];
				gotoxy(cot+6,dong+chon);

				if(chon == 0) cout<<data.MAMH;
				if(chon == 1) cout<<data.TENMH;
				if(chon == 2) cout<<data.STCLT;
				if(chon == 3) cout<<data.STCTH;

				chon --;
				HighLight();
				gotoxy(cot,dong+chon); 	cout << td[chon];
				gotoxy(cot+6,dong+chon);
			}
			break;

			case Down :if (chon+1 <so_item) {
				Normal();
				gotoxy(cot,dong+chon);	cout << td[chon];
				gotoxy(cot+6,dong+chon);
				if(chon == 0) cout<<data.MAMH;
				if(chon == 1) cout<<data.TENMH;
				if(chon == 2) cout<<data.STCLT;
				if(chon == 3) cout<<data.STCTH;
				chon ++;
				HighLight();
				gotoxy(cot,dong+chon); 	cout << td[chon];
				gotoxy(cot+6,dong+chon);
			}
			break;

			case Enter: if (chon+1 <=so_item) {
				Normal();
				gotoxy(cot,dong+chon);	cout << td[chon];
				gotoxy(cot+6,dong+chon); cout<< temp;

				//truong hop cap nhat khong cho sua ma sinh vien
				if(chon == 0 && key == Insert) {
					if(kiemTraMaMH(root, temp)) return 2;
					else strcpy(data.MAMH,temp);
				}

				if(chon == 1) strcpy(data.TENMH,temp);
				if(chon == 2) data.STCLT = atoi(temp);
				if(chon == 3){
					data.STCTH = atoi(temp);
					return 1;
				}

				chon ++;
				HighLight();
				gotoxy(cot,dong+chon); 	cout << td[chon];
				gotoxy(cot+6,dong+chon);
			  }
			  break;

			case ESC: return 0;
		}  // end switch
	} while (true);
}

bool kiemTraMaMH(TreeBinarySearch &root,char *maMH){
	TreeBinarySearch p = SearchTree(root,maMH);
	if(p == NULL) {
		return false;
	}
	else return true;

}

TreeBinarySearch SearchTree(TreeBinarySearch root,char *maMH){
	if(root == NULL){
		return NULL;
	}
	else{
		if(strcmp(maMH,root->data.MAMH) < 0){
			SearchTree(root->left,maMH);
		}
		else if(strcmp(maMH,root->data.MAMH) > 0){
			SearchTree(root->right,maMH);
		}
		else{
			return root;
		}
	}
}

void DeleteTree(TreeBinarySearch &root,char *maMH){
	if(root == NULL){
		return;
	}
	else{
		if(strcmp(maMH,root->data.MAMH) < 0){
			DeleteTree(root->left,maMH);
		}
		else if(strcmp(maMH,root->data.MAMH) > 0){
			DeleteTree(root->right,maMH);
		}
		else{
				TreeBinarySearch x = root;
				if(root->left == NULL){
					root = root->right;
				}
				else if(root->right == NULL){
					root = root->left;
				}else{
					TreeBinarySearch y = root->right;
					TimNodeTheMang(x,y);
				}
				delete x;
		}

	}
}


void TimNodeTheMang(TreeBinarySearch x,TreeBinarySearch y){
	if(y->left != NULL){
		TimNodeTheMang(x,y->left);
	}else{
		x->data = y->data;
		x = y;
		y = y->right;
	}
}

char* trim(char *str){
	int length = strlen(str);
	int x = 0;

	//xu ly khoang trang thu 0
	while(str[0] == ' '){
		for(int i =x ;i < length;i++ ){
			str[i] = str[i+1];
		}
	}

	//xu ly khoang trang o giua
	while(x < length){
		if(str[x] == ' ' && str[x+1] == ' '){
			for(int i =x ;i < length;i++ ){
				str[i] = str[i+1];
			}
		}
		else x++;
	}

	str[length] = '\0';
	return str;
}

void BaoLoi (char *s){
  int x=wherex() , y=wherey();
  gotoxy (20,25);
  cout <<s;
  Sleep(4000);
  gotoxy(10,24);
  clreol();
  gotoxy(x,y);
}

void SaveFileSinhVien(LinkedSV &First,char *filename) {
 FILE * f;
 if ((f=fopen(filename,"wb"))==NULL)
 {  BaoLoi ("Loi mo file de ghi"); return ;
 }
 for (LinkedSV p = First;p != NULL ; p=p->next)
   fwrite (&p->data, sizeof (SinhVien), 1, f);
 fclose(f);


}

void OpenFileSinhVien(LinkedSV &First, char *filename) {
 FILE * f; SinhVien sv;
 if ((f=fopen(filename,"rb"))==NULL)
 {  BaoLoi ("Loi mo file de doc"); return ;
 }
 while  (fread (&sv, sizeof (SinhVien), 1, f)!=0) {
	AddLinkedSV(First,sv);
 }

 fclose(f);


}

void SaveMonHoc(TreeBinarySearch root,FILE * f) {
 if(root == NULL) return;
 else
 {
 	SaveMonHoc(root->left,f);

	fwrite (&root->data, sizeof (MonHoc), 1, f);

 	SaveMonHoc(root->right,f);
 }
}

void SaveFileMonHoc(TreeBinarySearch root,char *filename){
	FILE * f;
	if ((f=fopen(filename,"wb"))==NULL)
	 {
	 	return ;
	 }
	 SaveMonHoc(root,f);
	 fclose(f);
}

void OpenFileMonHoc(TreeBinarySearch &root,char *filename) {
 FILE * f; MonHoc monHoc;
 if ((f=fopen(filename,"rb"))==NULL)
 {
 	 return ;
 }
 while  (fread (&monHoc, sizeof (MonHoc), 1, f)!=0) {
	InsertTree(root,monHoc);
 }
 fclose(f);


}





//-------------------------------------MAIN---------------------------------------
int main(int argc, char** argv) {
	DSLopTinChi					dsLopTinChi;
	dsLopTinChi.n = 0;
	LinkedSV 		 		 	linkedSV			=    NULL;
	LinkedDK 		 		 	linkedDK			=    NULL;
	TreeBinarySearch 			root     			=    NULL;

	int so_item = 9;
	int chon;
	char thucdon [so_item][100] =
			{"1. Lop tin chi            	",
			 "2. Sinh vien              	",
			 "3. Mon hoc                	",
			 "4. In DSSV tang dan ho ten 	",
			 "5. In DSMH tang dan ten mon 	",
			 "6. Dang ki lop tin chi    	",
			 "7. Huy lop tin chi        	",
			 "8. Nhap diem              	",
			 "9. Thoat                  	"};

	OpenFileSinhVien(linkedSV,"DSSV.TXT");
	OpenFileMonHoc(root,"DSMH.TXT");
	BaoLoi ("Da load xong danh sach vao bo nho");

	while (1) {
		chon = MenuDong(thucdon, so_item);
		switch (chon) {
			case 1: HienThiDanhSachLopTinChi(dsLopTinChi);
			break;

			case 2: HienThiDanhSachSinhVien(linkedSV);
			break;

			case 3: HienThiDanhSachMonHoc(root);
			break;

			case 4: HienThiDSSVTangDanTheoHoTen(linkedSV);
			break;

			case 5: HienThiDSMHTangDanTenMonHoc(root);
			break;

			case 6: gotoxy (10,20); cout << "Vua chon chuc nang " << chon;
			break;

			case 7: gotoxy (10,20); cout << "Vua chon chuc nang " << chon;
			break;

			case 9:{
				SaveFileSinhVien(linkedSV,"DSSV.TXT");
				SaveFileMonHoc(root,"DSMH.TXT");
				BaoLoi ("Da ghi xong danh sach vao file");
				return 0;
			}
		} // end switch
//         Sleep (1000);
	}
	return 1;
}
