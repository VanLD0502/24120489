#include <iostream>
#include <cstring>
using namespace std;
class HocSinh
{
private:
    char *HoTen;
    float diemCSLT;
    float diemDSA;
    float diemOOP;
    float DTB;
    float static DTBLonNhat;
    long long MSSV;
    static HocSinh *_HSDiemTBCaoNhat;

    static long long MSSVIndex;

public:
    HocSinh();
    ~HocSinh();
    static HocSinh &HSDiemTBCaoNhat();
    void DatHoTen(const char *hoten);
    void GanDiem(const float &cslt, const float &dsa, const float &oop);
    HocSinh(const char *hoten, const float &cslt, const float &dsa, const float &oop);
    void In(ostream &os);

    void CapNhatHsDtbCaoNhat();

    void GanMSSV();

    void CapNhatSinhVien(const char *hoten, const float &cslt, const float &dsa, const float &oop);
};

long long HocSinh::MSSVIndex = 23120001;
HocSinh *HocSinh::_HSDiemTBCaoNhat = nullptr;
float HocSinh::DTBLonNhat = -1;
HocSinh::HocSinh()
{
    HoTen = nullptr;
    CapNhatSinhVien("Vo Danh", 0, 0, 0);
}

HocSinh::HocSinh(const char *hoten, const float &cslt, const float &dsa, const float &oop)
{
    HoTen = nullptr;
    CapNhatSinhVien(hoten, cslt, dsa, oop);
}

void HocSinh::CapNhatSinhVien(const char *hoten, const float &cslt, const float &dsa, const float &oop)
{
    // Thêm HoTen = nullptr ban đầu mang ý nghĩa là chưa từng đặt họ tên cho sinh viên, để dễ dàng check nullptr khi viết hàm DatHoTen;
    // Vì hàm DatHoTen có thể đặt lại nhiều lần;
    HoTen = nullptr;
    DatHoTen(hoten);
    GanDiem(cslt, dsa, oop);
    GanMSSV();
}
void HocSinh::DatHoTen(const char *hoten)
{
    if (HoTen)
    {
        delete[] HoTen;
        HoTen = nullptr;
    }
    int len = strlen(hoten) + 1;
    HoTen = new char[len];
    strcpy_s(HoTen, len, hoten);
}

void HocSinh::GanDiem(const float &cslt, const float &dsa, const float &oop)
{
    diemCSLT = (cslt > 10) ? 0 : abs(cslt);
    diemDSA = (dsa > 10) ? 0 : abs(dsa);
    diemOOP = (oop > 10) ? 0 : abs(oop);
    // Nếu đặt tên hàm là GanDiem thì em nghĩ chỉ nên làm công việc GanDiem, nếu để tên hàm là CapNhatDiem
    // thì có thể CapNhatHsDtbCaoNhat, nếu để GanDiem không thì mình có thể làm theo cách cứ một SinhVien được tạo ra sẽ lưu vào 1 mảng SV
    // Nếu dùng các này thì không hiệu quả cho sinh viên quá đông.
    // Do bt chỉ quan tâm đến static cũng như chủ yếu chạy được hàm main nên việc đặt tên không quan trọng.
    // Important: Nên đặt hàm này ở đây vì có thể GanDiem nhiều lần nếu mình để hàm này ở construtor thì nó sẽ chỉ dùng được 1 lần.
    CapNhatHsDtbCaoNhat();
}

void HocSinh::In(ostream &os)
{
    const char *hoten = (HoTen == nullptr) ? "Vo Danh" : HoTen; // Dù biết là HoTen luôn != nullptr nhưng mà vẫn phải kiểm tra cho chăc.
    os << "HS: " << hoten << ", Ms: " << MSSV << ", DTB: " << DTB;
}

HocSinh &HocSinh::HSDiemTBCaoNhat()
{
    return *_HSDiemTBCaoNhat;
}

HocSinh::~HocSinh()
{
    if (HoTen)
    {
        delete[] HoTen;
    }
}

void HocSinh::CapNhatHsDtbCaoNhat()
{
    DTB = (diemCSLT + diemDSA + diemOOP) / 3;

    if (DTB > DTBLonNhat)
    {
        DTBLonNhat = DTB;
        _HSDiemTBCaoNhat = this;
    }
}

void HocSinh::GanMSSV()
{
    MSSV = MSSVIndex;
    MSSVIndex++;
}

int main()
{
    HocSinh hs1;
    hs1.DatHoTen("Nguyen Van A");
    hs1.GanDiem(7, 8, 10);
    HocSinh hs2("Tran Thi B", 5, 8, 4.5);
    HocSinh hs3("Hoan Thi C", -9.5, 8.5, 4.5);
    HocSinh hs4("Le Van D", 7.5, 9, -10);
    hs1.In(cout);
    cout << endl;
    hs2.In(cout);
    cout << endl;
    hs3.In(cout);
    cout << endl;
    hs4.In(cout);
    cout << endl;
    cout << "Hoc Sinh co diem TB cao nhat: " << endl;
    HocSinh::HSDiemTBCaoNhat().In(cout);
    cout << endl;
    return 0;
}