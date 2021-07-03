const int LOP_TC = 10000 ;


struct SinhVien{

	char	MASV[15];
	char 	HO[50];
	char  	TEN[50];
	bool 	PHAI;
	char 	SDT[13];
	char 	MALOP[50];
};

struct nodesv{
	SinhVien 		data;
	struct nodesv 	*next;
};
typedef nodesv* LinkedSV;

struct DangKy{
	char 		MASV[15];
	float 	DIEM;
};

struct nodedk{
	DangKy 					data;
	struct nodedk 	*next;
};
typedef nodedk *LinkedDK;

struct MonHoc{
	char  		MAMH[10];
	char  		TENMH[50];
	int 		STCLT;
	int 		STCTH;
};
struct nodemh{
	MonHoc data;
	struct nodemh *left;
	struct nodemh *right;
};
typedef nodemh *TreeBinarySearch;


struct LopTinChi{
	int 			MALOPTC; //tang dan
	char  			MAMH[10];
	int 			NienKhoa;
	char 			HocKy[10];
	char 			Nhom[10];
	int 			MinSV;
	int 			MaxSV;
	bool 			HuyLop;
	LinkedSV 	DSSV;
};

struct DSLopTinChi {
	int n;
	LopTinChi *nodes[LOP_TC];
};
