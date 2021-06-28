#include <iomanip>
#include "mylib.h"
#include "KhaiBao.h"

//define function
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

//---------------------------HAM CHUNG------------------------------
char scanner(char source[]){
	fflush(stdin);
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
			return 8;
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

void reDrawSV(int chon, char td[][100], SinhVien data) {
	gotoxy(cot,dong+chon); 	cout << td[chon];
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
			case Left:
				HighLight();
				reDrawSV(chon, td, data);
				break;

			case Right:
				HighLight();
				reDrawSV(chon, td, data);
				break;

			case Up :if (chon >0) {
				Normal();
				reDrawSV(chon, td, data);
				chon --;
				HighLight();
				reDrawSV(chon, td, data);
				}
				else {
					// rewdraw first line to not show UP ascii
					HighLight();
					reDrawSV(chon, td, data);
				}
				break;

			case Down :if (chon+1 <so_item) {
				Normal();
				reDrawSV(chon, td, data);
				chon ++;
				HighLight();
				reDrawSV(chon, td, data);
				}
				else {
					HighLight();
					reDrawSV(chon, td, data);
				}
				break;

			case Enter: if (chon+1 <=so_item) {
				Normal();
				gotoxy(cot,dong+chon);	cout << td[chon];
				gotoxy(cot+6,dong+chon); cout<< temp;
				if(chon == 0 && key == Insert) {     //truong hop cap nhat khong cho sua ma sinh vien kiem tra bao loi
					if(kiemTraMaSV(linkedSV, data.MASV)) return 2;
					else strcpy(data.MASV,temp);
				}
				if(chon == 1) strcpy(data.HO,temp);
				if(chon == 2) strcpy(data.TEN,temp);
				if(chon == 3) {
					ChonGioiTinh() == 1 ? data.PHAI = 1 : data.PHAI = 0;
				}
				if(chon == 4) strcpy(data.SDT,temp);
				if(chon == 5){
					//check du lieu cac truong roi save --> linkedSV
					strcpy(data.MALOP,temp);
					return 1;
				}
				chon ++;
				HighLight();
				reDrawSV(chon, td, data);
			  }
			  break;

			case 8:
				HighLight();
				gotoxy(cot,dong+chon); 	cout << td[chon];
				gotoxy(cot+6,dong+chon);
				// cout << "\b ";
				// gotoxy(current_x - 1, current_y);
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
	cout << setw(20) << left << sv.MALOP;
	cout << setw(20) << left << sv.SDT;
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
			cout << setw(20) << left << "MALOP";
			cout << setw(20) << left << "SDT"<<endl;
			cout << setfill('-');
			cout << setw(150) << "-" << endl;
			cout << setfill(' ');

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
					gotoxy(20,20);
					cout<<"Ma sinh vien bi trung";
					Sleep (1000);
				}
				isTrue = true;
			}
			break;

			case Home:{
				if(NhapSinhVien(linkedSV,sinhVien[chon],Home)){
					UpdateLinkedSV(linkedSV,sinhVien[chon]);
					length = LengthLinkedSV(linkedSV);
					delete [] sinhVien;
					sinhVien = new SinhVien[length];
					LinkedToArray(sinhVien,linkedSV);
					chon = length - 1;
					so_item = length;
				}
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

			case ESC: return 0;
		}
  } while (true);
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

void reDrawLopTC(int chon, char td[][100], LopTinChi lopTC) {
	gotoxy(cot, dong+chon);
	cout << td[chon];
	gotoxy(cot+11, dong+chon);
	if(chon == 0) cout << lopTC.MALOPTC;
	if(chon == 1) cout << lopTC.MAMH;
	if(chon == 2) cout << lopTC.NienKhoa;
	if(chon == 3) cout << lopTC.HocKy;
	if(chon == 4) cout << lopTC.Nhom;
	if(chon == 5) cout << lopTC.MinSV;
	if(chon == 6) cout << lopTC.MaxSV;
}

int NhapLopTinChi(LopTinChi &lopTC, int key){
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
	int i;
	for ( i=0; i< so_item ; i++) {
		if (key == Home) reDrawLopTC(i, td, lopTC);
		else {
			gotoxy(cot, dong+i);
			cout << td[i];
			gotoxy(cot+11, dong+i);
			if(i == 0) cout << lopTC.MALOPTC;
		}
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
			case Left: {
				HighLight();
				reDrawLopTC(chon, td, lopTC);
			}

			case Right: {
				HighLight();
				reDrawLopTC(chon, td, lopTC);
			}

			case Up :if (chon >1) {
				Normal();
				reDrawLopTC(chon, td, lopTC);
				chon --;
				HighLight();
				reDrawLopTC(chon, td, lopTC);
			}
			else {
				HighLight();
				reDrawLopTC(chon, td, lopTC);
			}
			break;

			case Down :if (chon+1 < so_item) {
				Normal();
				reDrawLopTC(chon, td, lopTC);
				chon ++;
				HighLight();
				reDrawLopTC(chon, td, lopTC);
			}
			else {
				HighLight();
				reDrawLopTC(chon, td, lopTC);
			}
			break;

			case Enter: if (chon+1 <= so_item) {
				Normal();
				gotoxy(cot, dong+chon);	cout << td[chon];
				gotoxy(cot+11, dong+chon); cout<< temp;
				if(chon == 1) strcpy(lopTC.MAMH, temp);
				if(chon == 2) {
					int nienKhoa		= atoi(temp);
					lopTC.NienKhoa		= nienKhoa;
				}
				if(chon == 3) strcpy(lopTC.HocKy, temp);
				if(chon == 4) strcpy(lopTC.Nhom, temp);
				if(chon == 5) {
					int minSV			= atoi(temp);
					lopTC.MinSV 		= minSV;
				}
				if(chon == 6) {
					int maxSV			= atoi(temp);
					lopTC.MaxSV 		= maxSV;
				}
				if(chon == 7) {
					return 1;
				}
				chon ++;
				HighLight();
				reDrawLopTC(chon, td, lopTC);
			}
			break;

			case 8:
				HighLight();
				gotoxy(cot, dong+chon);
				cout << td[chon];
				gotoxy(cot+11, dong+chon);
				// cout << "\b ";
				// gotoxy(current_x - 1, current_y);
				break;

			case ESC: return 0;
		}  // end switch
	} while (true);
}

int maxMaLopTC (DSLopTinChi dsLopTinChi) {
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

void AddLopTinChi(DSLopTinChi &dsLopTinChi, int key) {
	LopTinChi lopTC;
	lopTC.MALOPTC = maxMaLopTC(dsLopTinChi);
	int n = dsLopTinChi.n;
	if (NhapLopTinChi(lopTC, key)) {
		dsLopTinChi.nodes[n] = new LopTinChi;
		*dsLopTinChi.nodes[n] = lopTC;
		dsLopTinChi.n++;
	}
}

void UpdateLopTinChi(int chon, DSLopTinChi &dsLopTinChi, int key) {
	LopTinChi lopTC = *dsLopTinChi.nodes[chon];
	if (NhapLopTinChi(lopTC, key)) {
		*dsLopTinChi.nodes[chon] = lopTC;
	}
}

void DeleteLopTinChi(int chon, DSLopTinChi &dsLopTinChi) {
	LopTinChi lopTC = *dsLopTinChi.nodes[chon];
	for(int i=chon; i < dsLopTinChi.n-1; i++) {
		*dsLopTinChi.nodes[i] = *dsLopTinChi.nodes[i+1];
	}
	dsLopTinChi.n--;
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
				for (i = 0; i < dsLopTinChi.n; i++){
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

			case Down :if (chon+1 < dsLopTinChi.n) {
				Normal();
				gotoxy(x,y+chon+3);
				hienThiLopTinChi(*dsLopTinChi.nodes[chon]);
				chon ++;
				HighLight();
				gotoxy(x,y+chon+3);
				hienThiLopTinChi(*dsLopTinChi.nodes[chon]);
				}
				break;

			case Insert:
				AddLopTinChi(dsLopTinChi, Insert);
	//				length = LengthLinkedSV(linkedSV);
	//				delete [] sinhVien;
	// 				sinhVien = new SinhVien[length];
	//				LinkedToArray(sinhVien,linkedSV);
				chon = dsLopTinChi.n - 1;
				isTrue = true;
				break;

			case Home: if (dsLopTinChi.n > 0) {
				UpdateLopTinChi(chon, dsLopTinChi, Home);
	//				length = LengthLinkedSV(linkedSV);
	//				delete [] sinhVien;
	// 				sinhVien = new SinhVien[length];
	//				LinkedToArray(sinhVien,linkedSV);
				// chon = dsLopTinChi.n - 1;
				isTrue = true;
				}
				break;

			case DEL: if (dsLopTinChi.n > 0) {
				DeleteLopTinChi(chon, dsLopTinChi);
	//				length = LengthLinkedSV(linkedSV);
	//				delete [] sinhVien;
	// 				sinhVien = new SinhVien[length];
	//				LinkedToArray(sinhVien,linkedSV);
				chon = dsLopTinChi.n - 1;
				isTrue = true;
				}
				break;

			case ESC: return 0;

		} // end switch
	} while (true);
}

//-------------------------------------MAIN---------------------------------------
int main(int argc, char** argv) {
	DSLopTinChi					dsLopTinChi;
	dsLopTinChi.n = 0;
	LinkedSV 		 		 	linkedSV			=    NULL;
	LinkedDK 		 		 	linkedDK			=    NULL;
	TreeBinarySearch 			root     			=    NULL;

	int so_item = 7;
	int chon;
	char thucdon [so_item][100] =
			{"1. Lop tin chi            ",
			 "2. Sinh vien              ",
			 "3. Mon hoc                ",
			 "4. Dang ki lop tin chi    ",
			 "5. Huy lop tin chi        ",
			 "6. Nhap diem              ",
			 "7. Thoat                  "};
	while (1) {
		chon = MenuDong(thucdon, so_item);
		switch (chon) {
			case 1: HienThiDanhSachLopTinChi(dsLopTinChi);
			break;

			case 2: HienThiDanhSachSinhVien(linkedSV);
			break;

			case 3: gotoxy (10,20); cout << "Vua chon chuc nang " << chon;
			break;

			case 4: gotoxy (10,20); cout << "Vua chon chuc nang " << chon;
			break;

			case 5: gotoxy (10,20); cout << "Vua chon chuc nang " << chon;
			break;

			case 6: gotoxy (10,20); cout << "Vua chon chuc nang " << chon;
			break;

			case 7: return 0;
		} // end switch
//         Sleep (1000);
	}
}
