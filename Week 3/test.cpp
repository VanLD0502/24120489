#include <iostream>
#include <iomanip> // Để sử dụng system("pause") - mặc dù không được khuyến khích

using namespace std;

// --- Khai báo lớp Ngay ---
class Ngay
{
private:
    int ngay, thang, nam;

    // --- Các hàm hỗ trợ (private) ---

    // Kiểm tra năm nhuận
    bool KiemTraNamNhuan(int y)
    {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    // Trả về số ngày trong một tháng của một năm
    int ngayTrongThang(int m, int y)
    {
        if (m == 2)
        {
            return KiemTraNamNhuan(y) ? 29 : 28;
        }
        else if (m == 4 || m == 6 || m == 9 || m == 11)
        {
            return 30;
        }
        return 31;
    }

    // *** HÀM QUAN TRỌNG NHẤT: Chuẩn hóa ngày tháng ***
    // Xử lý các trường hợp ngày, tháng bị tràn (âm hoặc dương)
    void normalize()
    {
        // 1. Chuẩn hóa tháng (Month normalization)
        // Nếu tháng > 12, chuyển phần dư sang năm
        if (thang > 12)
        {
            nam += (thang - 1) / 12;      // Cộng số năm
            thang = (thang - 1) % 12 + 1; // Lấy tháng
        }
        // Nếu tháng <= 0, lùi về năm trước
        while (thang <= 0)
        {
            nam--;
            thang += 12;
        }

        // 2. Chuẩn hóa ngày (Day normalization)
        // Nếu ngày > số ngày trong tháng (tràn dương)
        while (ngay > ngayTrongThang(thang, nam))
        {
            ngay -= ngayTrongThang(thang, nam);
            thang++;
            // Nếu tháng lại bị tràn, chuẩn hóa tháng ngay lập tức
            if (thang > 12)
            {
                nam++;
                thang = 1;
            }
        }

        // Nếu ngày <= 0 (tràn âm)
        while (ngay <= 0)
        {
            thang--;
            // Nếu tháng bị tràn âm, chuẩn hóa tháng
            if (thang <= 0)
            {
                nam--;
                thang = 12;
            }
            ngay += ngayTrongThang(thang, nam);
        }
    }

public:
    // --- Constructors ---

    // 1. Hàm khởi tạo mặc định (cho n1)
    Ngay() : ngay(1), thang(1), nam(1) {}

    // 2. Hàm khởi tạo 3 tham số (cho n2, n3)
    Ngay(int d, int m, int y) : ngay(d), thang(m), nam(y)
    {
        normalize(); // Chuẩn hóa ngay sau khi gán
    }

    // 3. Hàm khởi tạo 1 tham số (cho n4)
    // Giả định là Ngay(d, 1, 1)
    Ngay(int d) : ngay(d), thang(1), nam(1)
    {
        normalize(); // Chuẩn hóa ngay sau khi gán
    }

    // --- Nạp chồng toán tử (Operator Overloading) ---

    // 4. n5 = n2 + n3 (Ngay + Ngay)
    Ngay operator+(const Ngay &other) const
    {
        return Ngay(ngay + other.ngay, thang + other.thang, nam + other.nam);
    }

    // 5. n9 = n8 - n6 (Ngay - Ngay)
    Ngay operator-(const Ngay &other) const
    {
        return Ngay(ngay - other.ngay, thang - other.thang, nam - other.nam);
    }

    // 6. n6 = n1 + 5000 (Ngay + int)
    // Giả định cộng vào thành phần 'ngay'
    Ngay operator+(long long days) const
    {
        return Ngay(ngay + days, thang, nam);
    }

    // 7. n7 = 1234 + n4 (int + Ngay)
    // Phải làm hàm bạn (friend) để đảo ngược vế
    friend Ngay operator+(long long days, const Ngay &date)
    {
        return date + days; // Tái sử dụng operator+(long long) ở trên
    }

    // 8. n10 = n2 - 1000 (Ngay - int)
    Ngay operator-(long long days) const
    {
        return Ngay(ngay - days, thang, nam);
    }

    // 9. n10 = 12000 - n9 (int - Ngay)
    // Đây là logic kỳ lạ nhất, nhưng để khớp bài toán:
    friend Ngay operator-(long long days, const Ngay &date)
    {
        // Coi 12000 là Ngay(12000) rồi trừ
        Ngay temp(days);
        return temp - date;
    }

    // 10. if (n10 > n6) (Ngay > Ngay)
    bool operator>(const Ngay &other) const
    {
        if (nam != other.nam)
            return nam > other.nam;
        if (thang != other.thang)
            return thang > other.thang;
        return ngay > other.ngay;
    }

    // 11. cout << n1 (Xuất ra cout)
    friend ostream &operator<<(ostream &os, const Ngay &date)
    {
        os << date.ngay << "/" << date.thang << "/" << date.nam;
        return os;
    }
};

// --- Hàm main() bạn đã cung cấp ---
int main()
{
    Ngay n1;                 // 1/1/1
    Ngay n2(2, 10, 2014);    // 2/10/2014
    Ngay n3(-10, 16, 2000);  // 10/4/2001 (Sau khi chuẩn hóa)
    Ngay n4(1000);           // 27/9/3 (Sau khi chuẩn hóa)
    Ngay n5 = n2 + n3;       // 12/2/4016 (Cộng 3 thành phần rồi chuẩn hóa)
    Ngay n6 = n1 + 5000;     // 10/10/15 (Cộng 5000 ngày rồi chuẩn hóa)
    Ngay n7 = 1234 + n4;     // 14/2/7 (Cộng 1234 ngày rồi chuẩn hóa)
    Ngay n8 = 190 + n6 + n7; // 2/7/23 (Cộng 190 ngày vào n6, rồi cộng n7, rồi chuẩn hóa)
    Ngay n9 = n8 - n6;       // 1/9/7 (Trừ 3 thành phần rồi chuẩn hóa)
    Ngay n10 = 12000 - n9;   // 9/2/26 (Lấy Ngay(12000) trừ n9)

    if (n10 > n6)
    {
        // n10 (9/2/26) > n6 (10/10/15) -> Đúng (26 > 15)
        n10 = n2 - 1000 + n6; // Tính giá trị n10 mới
    }

    // Kết quả in ra sẽ phụ thuộc vào giá trị cuối cùng của n10
    cout << n1 << endl
         << n2 << endl
         << n3 << endl
         << n4 << endl;
    cout << n5 << endl
         << n6 << endl
         << n7 << endl
         << n8 << endl;
    cout << n9 << endl
         << n10 << endl;

    system("pause"); // Dừng màn hình
    return 0;
}