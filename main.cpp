#include <iomanip>
#include <windows.h>
#include "mylib.h"
#include "KhaiBao.h"

// ham chung
char* trim(char *str);
void BaoLoi (char *s);
bool isStringEmpty(char data[]);
bool isNumEmpty(int data);
char* intToChars(int num)

// danh sach sinh vien
void AddLinkedSV(LinkedSV &First, SinhVien &data);
bool kiemTraMaSV(LinkedSV &First, char input[]);
void Delete_LinkedSV(LinkedSV &First,SinhVien &sv);
char scanner(char source[]);
int  ChonGioiTinh();
void reInputSV(int chon, char td[][100]);
void reDrawSV(int chon, char td[][100], SinhVien data);
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

// danh sach mon hoc
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


// danh sach lop tin chi
void HienThiLTC(LopTinChi &lopTC);
int HuyLop();
void reInputLTC(int index, char td[][100]);
void reDrawLTC(int index, char td[][100], LopTinChi lopTC);
bool InsertLTC(DSLopTinChi dsLopTinChi, LopTinChi &lopTC, int key);
int maxMaLTC (DSLopTinChi dsLopTinChi);
void AddLTC(DSLopTinChi &dsLopTinChi, LopTinChi lopTC);
void UpdateLTC(int index, DSLopTinChi &dsLopTinChi, int key);
void DeleteLTC(int index, DSLopTinChi &dsLopTinChi);
bool HienThiDSLTC(DSLopTinChi &dsLopTinChi);

// danh sach dang ky
int LengthLinkedDK(LinkedDK &linkedDK);
void reInputSearchField(char td[][100], int index);
void reDrawSearchFields(char td[][100], int index, LopTinChi lopTC);
bool check4params(LopTinChi lopTC1, LopTinChi lopTC2);
int searchIndexDSLTC4params(DSLopTinChi dsLopTinChi, LopTinChi lopTCSample);
bool FindIndexLTC(DSLopTinChi dsLopTinChi, LopTinChi &lopTC, int &index);
SinhVien findSVByMaSV(LinkedSV First, char maSV[]);
void LinkedDKToArray(SinhVien des[], LinkedDK linkedDK, LinkedSV linkedSV);
void inSV(SinhVien sinhVien[], int index);
bool HienThiDSDK(LinkedDK linkedDK, LinkedSV linkedSV);
bool QuanLyDSDK(DSLopTinChi &dsLopTinChi, LinkedSV linkedSV);


//---------------------------HAM CHUNG------------------------------
char scanner(char source[]){
	char ketqua[100];
	bool loop = true;
	int i = strlen(source);
	if (i != 0) {
		strcpy(ketqua,source);
		cout << source;
	}
	int x0 = wherex(); int y0 = wherey();
	int x,y;
	while(loop){
		x = wherex(); y = wherey();
		char kytu = getch();
		if(kytu == ESC){
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
		else if( kytu == 13 || i >= 98){
			ketqua[i] = '\0';
			strcpy(source,ketqua);
			return 13;
		}
		if(kytu == 8){
			if(i <= 0){
				i = 0;
			}
			else {
				i--;
				x = wherex(); y = wherey();
				gotoxy(x-1,y);
				cout<<" ";
				gotoxy(x-1,y);
			}
		}
		else {
			cout << kytu;
			ketqua[i] = kytu;
			i++;
		}
	}
}

bool isStringEmpty(char data[]) {
	int length = strlen(data);
	if (length == 0) return 1;
	int spaces = 0;
	for(int i=0; i<length; i++) {
		if(data[i] == ' ') spaces++;
	}
	if(spaces == length) return 1;
	return 0;
}

bool isNumEmpty(int data) {
	if (data == 0) return 1;
	return 0;
}

char* intToChars(int num) {
	char temp[100]="";
	return itoa(num, temp, 10); // decimal - base10
}


//----------------------------------LOP TIN CHI-------------------------------------
void HienThiLTC(LopTinChi &lopTC){
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

void reInputLTC(int index, char td[][100]) {
	gotoxy(cot, dong+index);
	cout << td[index];
	gotoxy(cot+11, dong+index);
}

void reDrawLTC(int index, char td[][100], LopTinChi lopTC) {
	reInputLTC(index, td);
	if(index == 0) cout << lopTC.MALOPTC;
	if(index == 1) cout << lopTC.MAMH;
	if(index == 2) {
		if (!(isNumEmpty(lopTC.NienKhoa))) cout << lopTC.NienKhoa;
	}
	if(index == 3) cout << lopTC.HocKy;
	if(index == 4) cout << lopTC.Nhom;
	if(index == 5) {
		if (!(isNumEmpty(lopTC.MinSV))) cout << lopTC.MinSV;
	}

	if(index == 6) {
		if (!(isNumEmpty(lopTC.MaxSV))) cout << lopTC.MaxSV;
	}
}

bool InsertLTC(DSLopTinChi dsLopTinChi, LopTinChi &lopTC, int key){
	int so_item = 8;
	char td [so_item][100] = {"MALOPTC  :                                                       ",
							  						"MA MH    :                                                       ",
							  						"NIEN KHOA:                                                       ",
							  						"HOC KY   :                                                       ",
							  						"NHOM     :                                                       ",
							  						"SO SV MIN:                                                       ",
							  						"SO SV MAX:                                                       ",
														"LUU THONG TIN"};
	Normal();
	system("cls");
	int chon = 1;
	if (key == Insert) lopTC.MALOPTC = maxMaLTC(dsLopTinChi);
	for (int i=0; i< so_item ; i++) {
		if (key == Home) reDrawLTC(i, td, lopTC);
		else {
			reInputLTC(i, td);
			if(i == 0) cout << lopTC.MALOPTC;
		}
	}
	HighLight();
	reInputLTC(chon, td);
	char kytu;
	do {
		char temp[100]="";
		if(chon == 1) strcpy(temp, lopTC.MAMH);
		if(chon == 2) strcpy(temp, intToChars(lopTC.NienKhoa));
		if(chon == 3) strcpy(temp, lopTC.HocKy);
		if(chon == 4) strcpy(temp, lopTC.Nhom);
		if(chon == 5) strcpy(temp, intToChars(lopTC.MinSV));
		if(chon == 6) strcpy(temp, intToChars(lopTC.MaxSV));
		kytu = scanner(temp);
		switch (kytu) {
			case Left: {
				HighLight();
				reDrawLTC(chon, td, lopTC);
			}

			case Right: {
				HighLight();
				reDrawLTC(chon, td, lopTC);
			}

			case Up :if (chon >1) {
				Normal();
				reDrawLTC(chon, td, lopTC);
				chon --;
			}
			HighLight();
			reInputLTC(chon, td);
			break;

			case Down :if (chon+1 < so_item) {
				Normal();
				reDrawLTC(chon, td, lopTC);
				chon ++;
			}
			HighLight();
			reInputLTC(chon, td);
			break;

			case Enter: if (chon+1 <= so_item) {
				if(chon == 1) strcpy(lopTC.MAMH, temp);
				if(chon == 2) lopTC.NienKhoa = atoi(temp);
				if(chon == 3) strcpy(lopTC.HocKy, temp);
				if(chon == 4) strcpy(lopTC.Nhom, temp);
				if(chon == 5) lopTC.MinSV = atoi(temp);
				if(chon == 6) lopTC.MaxSV = atoi(temp);
				if(chon == 7) return 1;
				Normal();
				reDrawLTC(chon, td, lopTC);
				chon ++;
				HighLight();
				reInputLTC(chon, td);
			}
			break;

			case ESC: return 0;
		}  // end switch
	} while (true);
}

int maxMaLTC (DSLopTinChi dsLopTinChi) {
	LopTinChi lopTC;
	int max = 0;
	int n = dsLopTinChi.n;
	if (n == 0) return max+1;
	for (int i = 0; i < n; i++) {
		lopTC = *dsLopTinChi.nodes[i];
		if (lopTC.MALOPTC > max) max = lopTC.MALOPTC;
	}
	return max+1;
}

void AddLTC(DSLopTinChi &dsLopTinChi, LopTinChi lopTC) {
	int n = dsLopTinChi.n;
	dsLopTinChi.nodes[n] = new LopTinChi;
	*dsLopTinChi.nodes[n] = lopTC;
	dsLopTinChi.n++;
}

void UpdateLTC(int index, DSLopTinChi &dsLopTinChi, int key) {
	LopTinChi lopTC = *dsLopTinChi.nodes[index];
	if (InsertLTC(dsLopTinChi, lopTC, key)) {
		*dsLopTinChi.nodes[index] = lopTC;
	}
}

void DeleteLTC(int index, DSLopTinChi &dsLopTinChi) {
	delete dsLopTinChi.nodes[index];
	for(int i=index; i < dsLopTinChi.n-1; i++) {
		dsLopTinChi.nodes[i] = dsLopTinChi.nodes[i+1];
	}
	dsLopTinChi.n--;
}

bool HienThiDSLTC(DSLopTinChi &dsLopTinChi){
  int x = 0; int y = 0;
  int chon = 0;
  char kytu;
  bool isTrue = true;

	do {
		LopTinChi lopTC = {};	// init = 0;
		if(isTrue) {
			Normal();
			system("cls");
			gotoxy(x,y);

			cout << setw(70) << left << " " << "DANH SACH LOP TIN CHI" << endl;
			cout << setw(20) << left << "MALOPTC";
			cout << setw(20) << left << "MAMH";
			cout << setw(20) << left << "NIEN KHOA";
			cout << setw(20) << left << "HOC KY";
			cout << setw(20) << left << "NHOM";
			cout << setw(20) << left << "SO SV MIN";
			cout << setw(20) << left << "SO SV MAX" <<endl;

			cout << setfill('-');
			cout << setw(150) << "-" << endl;
			cout << setfill(' ');

			if(dsLopTinChi.n != 0){
				for (int i = 0; i < dsLopTinChi.n; i++){
					gotoxy(x,y+3+i);
					HienThiLTC(*dsLopTinChi.nodes[i]);
				}

				HighLight();
				gotoxy(x,y+chon+3);
				HienThiLTC(*dsLopTinChi.nodes[chon]);
			}
		}
		isTrue = false;

		kytu = getch();
		if (kytu==-32) kytu = getch();
		switch (kytu) {
			case Up :if (chon >0) {
				Normal();
				gotoxy(x,y+chon+3);
				HienThiLTC(*dsLopTinChi.nodes[chon]);
				chon --;
				HighLight();
				gotoxy(x,y+chon+3);
				HienThiLTC(*dsLopTinChi.nodes[chon]);
				}
				break;

			case Down :if (chon+1 < dsLopTinChi.n) {
				Normal();
				gotoxy(x,y+chon+3);
				HienThiLTC(*dsLopTinChi.nodes[chon]);
				chon ++;
				HighLight();
				gotoxy(x,y+chon+3);
				HienThiLTC(*dsLopTinChi.nodes[chon]);
				}
				break;

			case Insert: {
				if (InsertLTC(dsLopTinChi, lopTC, Insert)) AddLTC(dsLopTinChi, lopTC);
				chon = dsLopTinChi.n - 1;
				isTrue = true;
				}
				break;

			case Home: if (dsLopTinChi.n > 0) {
				UpdateLTC(chon, dsLopTinChi, Home);
				isTrue = true;
				}
				break;

			case DEL: if (dsLopTinChi.n > 0) {
				DeleteLTC(chon, dsLopTinChi);
				chon = dsLopTinChi.n - 1;
				isTrue = true;
				}
				break;

			case ESC: return 0;

		} // end switch
	} while (true);
}


//--------------------------------DANH SACH SINH VIEN DANG KY--------------------------------
int LengthLinkedDK(LinkedDK &linkedDK){
	int count = 0;
	for(LinkedDK p = linkedDK; p != NULL; p=p->next){
		count++;
	}
	return count;
}

void reInputSearchField(char td[][100], int index) {
	gotoxy(cot, dong+index);
	cout<<td[index];
	gotoxy(cot+11, dong+index);
}

void reDrawSearchFields(char td[][100], int index, LopTinChi lopTC) {
	reInputSearchField(td, index);
	if (index == 1) {
		if (!(isNumEmpty(lopTC.NienKhoa))) cout<<lopTC.NienKhoa;
	}
	if (index == 2) cout<<lopTC.HocKy;
	if (index == 3) cout<<lopTC.Nhom;
	if (index == 4) cout<<lopTC.MAMH;
}

bool check4params(LopTinChi lopTC1, LopTinChi lopTC2) {
	if (!strcmp(lopTC1.MAMH, lopTC2.MAMH)) {
		if (lopTC1.NienKhoa == lopTC2.NienKhoa) {
			if (!strcmp(lopTC1.HocKy, lopTC2.HocKy)) {
				if (!strcmp(lopTC1.Nhom, lopTC2.Nhom)) {
					return 1;
				}
			}
		}
	}
	return 0;
}

int searchIndexDSLTC4params(DSLopTinChi dsLopTinChi, LopTinChi lopTCSample) {
	int n = dsLopTinChi.n;
	LopTinChi lopTC = {};		// init = 0
	for (int i = 0; i < n; i++) {
		lopTC = *dsLopTinChi.nodes[i];
		if (check4params(lopTC, lopTCSample)) return i;
	}
	return -2;
}

bool FindIndexLTC(DSLopTinChi dsLopTinChi, LopTinChi &lopTC, int &index) {
	int chon = 1;
	int so_item = 6;
	char td [so_item][100] = {"		NHAP THONG TIN LOP TIN CHI																		",
														"NIEN KHOA:                                                      	",
							  						"HOC KY   :                                                       ",
							  						"NHOM     :                                                       ",
														"MA MH    :                                                       ",
														"IN DANH SACH SINH VIEN DA DANG KY"};
	Normal();
	system("cls");
	for(int i=0; i<so_item; i++) {
		gotoxy(cot, dong+i);
		cout << td[i];
	}
	HighLight();
	reInputSearchField(td, chon);
	char kytu;
	do {
		char temp[100] = "";
		kytu = scanner(temp);
		if(chon == 1) strcpy(temp, intToChars(lopTC.NienKhoa));
		if(chon == 2) strcpy(temp, lopTC.HocKy);
		if(chon == 3) strcpy(temp, lopTC.Nhom);
		if(chon == 4) strcpy(temp, lopTC.MAMH);
		switch(kytu) {
			case Left:
				HighLight();
				reDrawSearchFields(td, chon, lopTC);
				break;

			case Right:
				HighLight();
				reDrawSearchFields(td, chon, lopTC);
				break;

			case Up :if (chon >1) {
				Normal();
				reDrawSearchFields(td, chon, lopTC);
				chon --;
			}
				HighLight();
				reInputSearchField(td, chon);
				break;

			case Down :if (chon+1 < so_item) {
				Normal();
				reDrawSearchFields(td, chon, lopTC);
				chon ++;
				}
				HighLight();
				reInputSearchField(td, chon);
				break;

			case Enter : {
				if(chon==1) lopTC.NienKhoa = atoi(temp);
				if(chon==2) strcpy(lopTC.HocKy, temp);
				if(chon==3) strcpy(lopTC.Nhom, temp);
				if(chon==4) strcpy(lopTC.MAMH, temp);
				if(chon==5) {
					if(isNumEmpty(lopTC.NienKhoa)) {
						MessageBox(NULL, "Chua nhap nien khoa", "Error", MB_OK);
						break;
					}
					if(isStringEmpty(lopTC.HocKy)) {
						MessageBox(NULL, "Chua nhap hoc ky", "Error", MB_OK);
						break;
					}
					if(isStringEmpty(lopTC.Nhom)) {
						MessageBox(NULL, "Chua nhap nhom", "Error", MB_OK);
						break;
					}
					if(isStringEmpty(lopTC.MAMH)) {
						MessageBox(NULL, "Chua nhap ma mon hoc", "Error", MB_OK);
						break;
					}

					// check tim thay lop tin chi khong
					index = searchIndexDSLTC4params(dsLopTinChi, lopTC);
					if (index == -2) {
						MessageBox(NULL, "Khong tim thay lop tin chi!", "Error", MB_OK);
						break;
					}
					return 1;
					}
				Normal();
				reDrawSearchFields(td, chon, lopTC);
				chon++;
				HighLight();
				reInputSearchField(td, chon);
				}
				break;

			case ESC: return 0;
		} // end switch
	} while(true);
}

// tim sinh vien theo maSV
SinhVien findSVByMaSV(LinkedSV First, char maSV[]) {
	while(First != NULL) {
		if(!strcmp(First->data.MASV, maSV)) {
			return First->data;
		}

		First = First->next;
	}
}

void LinkedDKToArray(SinhVien des[], LinkedDK linkedDK, LinkedSV linkedSV){
	if(linkedDK != NULL){
		int index = 0;
		char maSV[15];
		SinhVien sv;
		for(LinkedDK p = linkedDK; p!=NULL; p=p->next){
			strcpy(maSV, p->data.MASV);
			sv = findSVByMaSV(linkedSV, maSV);
			des[index] = sv;
			index++;
		}
	}
}

void inSV(SinhVien sinhVien[], int index) {
	gotoxy(0,0+3+index);
	hienThiSinhVien(sinhVien[index]);
}

bool HienThiDSDK(LinkedDK linkedDK, LinkedSV linkedSV) {
	int so_item = LengthLinkedDK(linkedDK);
	SinhVien *sinhVienDK = new SinhVien[so_item];
	LinkedDKToArray(sinhVienDK, linkedDK, linkedSV);

	int x = 0 ; int y = 0;
	int chon = 0;
	char kytu;
	Normal();
	system("cls");
	gotoxy(x,y);

	cout << setw(30) << left << " " << "DANH SACH SINH VIEN DANG KY LOP TIN CHI" << endl;
	cout << setw(20) << left << "MASV";
	cout << setw(50) << left << "HO";
	cout << setw(20) << left << "TEN";
	cout << setw(20) << left << "Phai";
	cout << setw(20) << left << "SDT";
	cout << setw(20) << left << "MALOP"<<endl;

	cout << setfill('-');
	cout << setw(150) << "-" << endl;
	cout << setfill(' ');

	if(linkedDK != NULL) {
		for(int i=0; i< so_item ; i++) {
			inSV(sinhVienDK, i);
		}
	}

	HighLight();
	inSV(sinhVienDK, chon);
	do
	{
		kytu = getch();
		if (kytu==-32) kytu = getch();
		switch (kytu) {
			case Up: if (chon >0) {
				Normal();
				inSV(sinhVienDK, chon);
				chon --;
				HighLight();
				inSV(sinhVienDK, chon);
			}
			break;

			case Down: if (chon+1 <so_item) {
				Normal();
				inSV(sinhVienDK, chon);
				chon ++;
				HighLight();
				inSV(sinhVienDK, chon);
				}
				break;

			case ESC: return 0;
		}
	} while (true);
}

float getDiem(int index, LinkedDK linkedDK) {
	for(int i=0; i<index; i++) linkedDK = linkedDK->next;
	DangKy dk = linkedDK->data;
	return dk.DIEM;
}

void HienThiNhapDiem(SinhVien sv, int i, LinkedDK linkedDK) {
	cout << setw(20) << left << i+1;
	cout << setw(20) << left << sv.MASV;
	cout << setw(50) << left << sv.HO;
	cout << setw(20) << left << sv.TEN;
	cout << setw(20) << left << getDiem(i, linkedDK);
}

bool HienThiDSNhapDiem(LinkedDK linkedDK, LinkedSV linkedSV) {
	int so_item = LengthLinkedDK(linkedDK);
	SinhVien *sinhVienDK = new SinhVien[so_item];
	LinkedDKToArray(sinhVienDK, linkedDK, linkedSV);

	int x = 0; int y = 0;
	int chon = 0;
	Normal();
	system("cls");
	gotoxy(x,y);

	cout << setw(30) << left << " " << "DANH SACH SINH VIEN DANG KY LOP TIN CHI" << endl;
	cout << setw(20) << left << "STT";
	cout << setw(20) << left << "MASV";
	cout << setw(50) << left << "HO";
	cout << setw(20) << left << "TEN";
	cout << setw(20) << left << "DIEM" << endl;

	cout << setfill('-');
	cout << setw(150) << "-" << endl;
	cout << setfill(' ');

	if(linkedDK != NULL) {
		for(int i=0; i< so_item ; i++) {
			gotoxy(x,y+3+i);
			HienThiNhapDiem(sinhVienDK[i], i, linkedDK);
		}
	}

	char kytu;
	do
	{
		gotoxy(110, y+3+chon);
		char input[1]="";
		kytu = scanner(input);
		switch (kytu)
		{
		case Up: if(chon > 0) {
				Normal();
				gotoxy(x,y+3+chon);
				HienThiNhapDiem(sinhVienDK[chon], chon, linkedDK);
				chon--;
				HighLight();
				gotoxy(x,y+3+chon);
				HienThiNhapDiem(sinhVienDK[chon], chon, linkedDK);
			}
			break;

		case Down :if (chon+1 <so_item) {
				Normal();
				gotoxy(x,y+3+chon);
				HienThiNhapDiem(sinhVienDK[chon], chon, linkedDK);
				chon++;
				HighLight();
				gotoxy(x,y+3+chon);
				HienThiNhapDiem(sinhVienDK[chon], chon, linkedDK);
			}
			break;

		case Enter:
			Normal();
			gotoxy(x,y+3+chon);
			// HienThiNhapDiem(sinhVienDK[chon], chon, linkedDK);
			cout << input;
			chon++;
			HighLight();
			gotoxy(x,y+3+chon);
			HienThiNhapDiem(sinhVienDK[chon], chon, linkedDK);
			break;

		case ESC: return 0;
		} // end switch

	} while (true);

}

bool QuanLyDSDK(DSLopTinChi &dsLopTinChi, LinkedSV linkedSV){
	LopTinChi lopTC = {};
	int index = -2;	// init = 0
	bool check = FindIndexLTC(dsLopTinChi, lopTC, index); // nhap thong tin va tim index lopTC

	// tim thay lopTC
	if (check) {
		lopTC = *dsLopTinChi.nodes[index];
		int so_item = 2;
		char td[so_item][100] =	 {"1. Xem danh sach sinh vien dang ky          ",
															"2. Nhap diem                                "};

		do
		{
			int chon = MenuDong(td, so_item);
			switch (chon)
			{
				case 1:
					HienThiDSDK(lopTC.linkedDK, linkedSV);
					break;

				case 2:
					HienThiDSNhapDiem(lopTC.linkedDK, linkedSV);
					break;

				case -1: return 0;
			} // end switch

		} while (true);
	}

	// thoat nhap thong tin lop tin chi
	else return 0;
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
  if (First==NULL ) return;

	// Del phan tu dau
	if (!strcmp(First->data.MASV,sv.MASV)){
		LinkedSV temp = First;
		First = temp->next;
		delete temp;
	}

	for (LinkedSV p = First; p->next != NULL;){
		if (!strcmp(p->next->data.MASV, sv.MASV) ) {
				LinkedSV q = p->next;
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

void reInputSV(int chon, char td[][100]) {
	gotoxy(cot,dong+chon);
	cout << td[chon];
	gotoxy(cot+6,dong+chon);
}

void reDrawSV(int chon, char td[][100], SinhVien data) {
	reInputSV(chon, td);
	if(chon == 0) cout<<data.MASV;
	if(chon == 1) cout<<data.HO;
	if(chon == 2) cout<<data.TEN;
	if(chon == 3){
		if(data.PHAI) cout<<"Nam";
		else cout<<"Nu";
	}
	if(chon == 4) cout<<data.SDT;
	if(chon == 5) cout<<data.MALOP;
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
		reDrawSV(i, td, data);
	}
	if(key == Home) chon++; //tang chon bo qua ma sinh vien
	HighLight();
	reInputSV(chon, td);
	char kytu;
	do {
		char temp[100]="";
		if(chon == 0) strcpy(temp, data.MASV);
		if(chon == 1) strcpy(temp, data.HO);
		if(chon == 2) strcpy(temp, data.TEN);
		if(chon == 4) strcpy(temp, data.SDT);
		if(chon == 5) strcpy(temp, data.MALOP);
		kytu = scanner(temp);
		switch (kytu) {
			case Left:
				HighLight();
				reInputSV(chon, td);
				break;

			case Right:
				HighLight();
				reInputSV(chon, td);
				break;

			case Up : {
				int limit = 0;
				if (key == Home) limit = 1;
				if (chon > limit) {
					Normal();
					reDrawSV(chon, td, data);
					chon --;
				}
				HighLight();
				reInputSV(chon, td);
			}
				break;

			case Down :if (chon+1 <so_item) {
				Normal();
				reDrawSV(chon, td, data);
				chon ++;
				}
				HighLight();
				reInputSV(chon, td);
				break;

			case Enter: {
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
				Normal();
				reDrawSV(chon, td, data);
				chon ++;
				HighLight();
				reInputSV(chon, td);
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
		if(isTrue){
			Normal();
			system("cls");
			gotoxy(x,y);

			cout << setw(50) << left << " " << "DANH SACH SINH VIEN" << endl;
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
					inSV(sinhVien,i);
				}

				HighLight();
				inSV(sinhVien, chon);
			}
		}
		isTrue = false;

		kytu = getch();
		if (kytu==-32) kytu = getch();
		switch (kytu) {
			case Up :if (chon >0) {
				Normal();
				inSV(sinhVien, chon);
				chon --;
				HighLight();
				inSV(sinhVien, chon);
			}
			break;

			case Down :if (chon+1 <so_item) {
				Normal();
				inSV(sinhVien, chon);
				chon ++;
				HighLight();
				inSV(sinhVien, chon);
			}
			break;

			case Insert:{
				SinhVien sv;
				int check = NhapSinhVien(linkedSV, sv,Insert);
				if( check == 1){
					AddLinkedSV(linkedSV, sv);
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
						gotoxy(x,y+chon+3);
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


//---------------------DANH SACH MON HOC----------------------------
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
		// if(chon == 1) strcpy(temp, data.MAMH);
		// if(chon == 2) strcpy(temp, data.TENMH);
		// if(chon == 3) strcpy(temp, intToChars(data.STCLT));
		// if(chon == 4) strcpy(temp, intToChars(data.STCTH));
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

//----------------------------------XU LY FILE--------------------------------
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
			{"1. Danh sach lop tin chi                       ",
			 "2. Danh sach sinh vien dang ky tin chi         ",
			 "3. Danh sach sinh vien                         ",
			 "4. Danh sach mon hoc                           ",
			 "5. In DSSV tang dan ho ten                     ",
			 "6. In DSMH tang dan ten mon                    ",
			 "7. Dang ki lop tin chi                         ",
			 "8. Huy lop tin chi                             ",
			 "9. Thoat                                       "};

	OpenFileSinhVien(linkedSV,"DSSV.TXT");
	OpenFileMonHoc(root,"DSMH.TXT");
	BaoLoi ("Da load xong danh sach vao bo nho");

	while (1) {
		chon = MenuDong(thucdon, so_item);
		switch (chon) {
			case 1: HienThiDSLTC(dsLopTinChi);
			break;

			case 2: QuanLyDSDK(dsLopTinChi, linkedSV);
			break;

			case 3: HienThiDanhSachSinhVien(linkedSV);
			break;

			case 4: HienThiDanhSachMonHoc(root);
			break;

			case 5: HienThiDSSVTangDanTheoHoTen(linkedSV);
			break;

			case 6: HienThiDSMHTangDanTenMonHoc(root);
			break;

			case 7: gotoxy (10,20); cout << "Vua chon chuc nang " << chon;
			break;

			case 8: gotoxy (10,20); cout << "Vua chon chuc nang " << chon;
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
