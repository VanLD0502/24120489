#include <iostream>
#include <string>
#include <functional>
#include <algorithm>
#include <stack>
#include <fstream>
using namespace std;
//Cấu trúc dữ liệu cho số nguyên lớn. 
struct Number
{
    bool _negative = false; // Đánh dấu có phải là số âm. 1 : am , 0: duong.
    std::string _number;// Phần số dạng chuổi trong số nguyên lớn.
    int len = 0; // Độ dài chuỗi, cũng không cần thiết.
    Number() { _number = "0";  _negative = false; }; // Khởi tạo số 0;
    void TrimLeadingZeros();// Xóa số 0 đầu chuỗi.
    Number(std::string num, bool negative) {  // Tạo số nguyên lớn với phần số là num, âm dương phụ thuộc negative.
        len = num.size(); _negative = negative;
        
        _number = (num == "") ? "0" : num; //Chuoi rong mac dinh la so 0.
    };
    //Nap chong cac phep so sanh va tinh toan.
    //các phép so sánh cho số dương. Vì tính toán trên số dương. Việc xét dấu xét riêng nên so sánh số âm không cần thiết trong bài này.
    bool operator<(const Number& other);
    bool operator>(const Number& other);
    bool operator==(const Number& other);
    bool operator<=(const Number& other);
    bool operator>=(const Number& other);
    Number operator+(Number other);
    Number operator-(Number other);
    Number operator*(Number other);
    Number operator/(Number other);
    //Lấy trị tuyệt đối thuận tiện tính +, -, *, /
    Number Abs(Number a);
};

std::ostream& operator<<(std::ostream& os, const Number& num); // Nạp chồng phép in ra cho tiện debug, với Không cần viết dài.
//So sánh thì == thì 2 chuỗi giống nhau là được, còn bé hơn thì so sánh về độ dài chuỗi ,nếu chuỗi độ dài 2 chuỗi bằng nhau thì so sánh từng kí tự, lớn hơn tương tự.
// <=, >= là kết hợp các phép toán lại.
bool Number::operator<(const Number& other)
{
    int n = _number.length();
    int m = other._number.length();
    return ((n < m) || (n == m && _number < other._number));
}
bool Number::operator>(const Number& other)
{
    int n = _number.length();
    int m = other._number.length();
    return ((n > m) || (n == m && _number > other._number));
}
bool Number::operator==(const Number& other)
{
    return _number == other._number;
}
bool Number::operator<=(const Number& other)
{
    return _number < other._number || _number == other._number;
}
bool Number::operator>=(const Number& other)
{
    return _number > other._number || _number == other._number;
}

// Thực hiện phép toán cộng.
Number Number::operator+(Number other)
{
    bool is_Negative = false;
    //Lấy a + b; a là struct hiện tại, b là struct bên ngoài.
    //Nếu 2 số cùng âm thì ta chỉ cần cộng phần _number của 2 Number, rồi xét âm là true cho kết quả.
    if ((*this)._negative == true && other._negative == true) {
        is_Negative = true;
    }
    //123 + -200;
    //Nếu chỉ có a âm thì lấy b - |a| là được
    else if ((*this)._negative == true) {
        return other - Abs((*this));
    }
    //Nếu b âm thì a - |b|
    else if ((other)._negative == true) {
        return (*this) - Abs(other);
    }
    std::string a = _number;
    std::string b = other._number;
    int n1 = a.length(), n2 = b.length();
    //Để 2 chuỗi có độ dài bằng nhau cho dễ tính.
    if (n1 < n2) a = std::string(n2 - n1, '0') + a;
    if (n2 < n1) b = std::string(n1 - n2, '0') + b;
    std::string result = "";
    //Nhớ 
    int carry = 0;
    //Duyệt ngược từ cuối.
    for (int i = std::max(n1,n2) - 1; i >= 0; i--) {
        int sum = ((a[i] - '0') + (b[i] - '0') + carry);
        //Lấy tổng bỏ vào kết quả.
        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }
    //Nếu vẫn còn carry = 1 thì push vào kết quả/
    if (carry > 0) {
        result.push_back('1');
    }
    //Lật ngược sẽ ra đáp án.
    std::reverse(result.begin(), result.end());
    return Number(result, is_Negative);
}

    Number Number::operator-(Number other)
    {
        
        //Lấy a - b;
        //a - b = -|a| - -|b| = |b| - |a|
        if ((*this)._negative == true && other._negative == true) {
            Number res = Abs(other) - Abs(*this);
            return res;
        }
        //a - b = - |a| - b = -(|a| + b)
        else if ((*this)._negative == true) {
            Number res = Abs(*this) + other;
            res._negative = true;
            return res;
        }
        //a - b = a - -|b| = a + |b|
        else if (other._negative == true) {
            Number res = (*this) + Abs(other);
            return res;
        }

        std::string a = _number;
        std::string b = other._number;

        bool is_negative = false;
        int n1 = a.length(), n2 = b.length();
        //Phép trừ đang thực hiện lấy số lớn trừ số bé nếu a < b thì cập nhật kết quả là âm.
        if (n1 < n2 || (n1 == n2 && a < b)){
            is_negative = true; // Cập nhật âm nếu số a bé hơn số b.
            std::swap(a, b);
            std::swap(n1, n2);
        }
        // Thêm các số 0 ở đầu b nếu b ngắn hơn a để dễ trừ từng chữ số
        //Mình swap rồi nên đoạn này khỏi if cũng được.
        if (n2 < n1) b = std::string(n1 - n2, '0') + b;
        int carry = 0;
        std::string result = "";
        for (int i = n1 - 1; i >= 0; i--) {
            int sum = ((a[i] - '0') - (b[i] - '0') + carry);
            result.push_back((sum + 10) % 10 + '0');
            if (sum < 0) carry = -1;
            else carry = 0;
        }

        //reverse chuỗi được đáp án.
        std::reverse(result.begin(), result.end());
        //Xóa số 0 ở đàu.
        result.erase(0, result.find_first_not_of('0'));
        return Number(result, is_negative); // trả về kết quả với dấu âm nếu cần
    }
/*

*/
//Xóa số 0 ở đầu.
void Number::TrimLeadingZeros() {
    int i = 0;
    while (i < _number.length() - 1 && _number[i] == '0') ++i;
    _number = _number.substr(i);
}

Number Number::operator*(Number other)
{
    // Hàm phụ: Thêm các chữ số 0 vào cuối chuỗi (tương đương với nhân 10^lenZero)
    std::function<Number(Number,int)> Fill_Zero = [&](Number a, int lenZero) -> Number {
        a._number += std::string(lenZero, '0');
        return a;
    };

     // Thuật toán nhân Karatsuba: Chia để trị, tối ưu hơn nhân thường với số lớn
    std::function<Number(Number, Number)>Karatsuba = [&](Number x, Number y) -> Number {
        //bool is_negative = x._negative ^ y._negative;
        // Trường hợp cơ sở: y có 1 chữ số → nhân đơn giản bằng cách cộng nhiều lần
        if (y._number.length() == 1) {
            Number res;
            for (int i = 0; i < y._number[0] - '0'; i++) {
                res = res + x;
            }
            //res._negative = is_negative;
            return res;
        }
        // Trường hợp cơ sở: x có 1 chữ số
        else if (x._number.length() == 1) {
            Number res;
            for (int i = 0; i < x._number[0] - '0'; i++) {
                res = res + y;
            }
            //res._negative = is_negative;
            return res;
        }

        int n = std::max(x._number.length(), y._number.length());

        int m = n / 2;

        int lenx = (int)x._number.length();
        int leny = (int)y._number.length();
        // Chia số x thành a và b: x = a * 10^m + b 
        Number a(x._number.substr(0, std::max(0, lenx - m)), false);
        Number b(x._number.substr(std::max(0, lenx - m)), false);

        // Chia số y thành c và d: y = c * 10^m + d
        Number c(y._number.substr(0, std::max(0, leny - m)), false);
        Number d(y._number.substr(std::max(0, leny - m)), false);
        // Tính ac, bd, (a + b)(c + d)
        Number ac = Karatsuba(a, c);
        Number bd = Karatsuba(b, d);
        Number ab_cd(Karatsuba(a + b, c + d));
        // x * y = ac * 10^(2*m) + ((a+b)(c+d) - ac - bd) * 10^m + bd
        Number result = Fill_Zero(ac, 2 * m) + Fill_Zero(ab_cd - ac - bd, m) + bd;
        result.TrimLeadingZeros();
        return result;

        };

    Number res = Karatsuba(Abs(*this), Abs(other));
    // Đặt dấu của kết quả: âm nếu một trong hai số âm (nhưng không phải cả hai)
    res._negative = (other._negative ^ (*this)._negative);
    return res;
}

Number Number::operator/(Number other)
{
    // Bước 1: Lấy trị tuyệt đối để xử lý phần giá trị, dấu xử lý sau
    Number dividend = Abs(*this);      // Số bị chia
    Number divisor = Abs(other);       // Số chia

    std::string cur = "";              // Phần đang xét của số bị chia (giống như lấy từng chữ số xuống)
    std::string res = "";              // Kết quả cuối cùng

    // Hàm phụ: chia current cho divisor, trả về thương nguyên
    std::function<int(Number&, Number)> Divide1Number = [&](Number& current, Number divisor) -> int
    {
        int cnt = 0;
        int n = current._number.length(); // Độ dài current
        int m = divisor._number.length(); // Độ dài divisor

        // Lặp cho đến khi current < divisor
        while ((n > m) || (n == m && current._number >= divisor._number)) {
            current = current - divisor;  // Trừ divisor khỏi current
            cnt++;                        // Đếm số lần trừ được → thương
            n = current._number.length(); // Cập nhật độ dài mới
        }

        return cnt;
    };

    // Bước 2: Duyệt từng chữ số trong dividend
    for (int i = 0; i < dividend._number.length(); i++) {
        cur += dividend._number[i];   // Lấy từng chữ số một để chia

        // Loại bỏ các chữ số 0 không cần thiết ở đầu
        while (cur.length() > 1 && cur[0] == '0') cur.erase(0, 1);

        Number current(cur, false);   // Biến tạm để chia
        int cnt = Divide1Number(current, divisor); // Chia và lấy thương
        res += cnt + '0';             // Lưu thương vào kết quả
        cur = current._number;        // Cập nhật current để dùng cho lần sau
    }

    // Bước 3: Loại bỏ các chữ số 0 ở đầu kết quả
    int i = 0;
    while (i < res.length() - 1 && res[i] == '0') i++;
    res = res.substr(i);

    // Bước 4: Trả về kết quả với đúng dấu (âm nếu một trong hai là âm)
    return Number(res, (*this)._negative ^ other._negative);
}



Number Number::Abs(Number a)
{
    Number res = a;
    a._negative = false;
    return a;
}
std::ostream& operator<<(std::ostream& os, const Number& num)
{
    if (num._number == "0") {
        os << num._number;
        return os;
    }
    if (num._negative) {
        os << '-';
    }
    os << num._number;
    return os;
}



// Process ExpressionExpression
void Input(string fileIn, string fileOut);
int priority(char c);
bool isSign(char c);
Number Compute(Number a, Number b, char c);
void Processing(std::string expression, ofstream & out);

void Input(string fileIn, string fileOut)
{
    ifstream in("tests.txt");
    ofstream out("output_24120489.txt");
    int t;
    string s;
    while (getline(in, s))
    {
        Processing(s, out);
    }

    // s = "5 +   7 + 2 - 3";
    // Processing(s, out);
    in.close();
    out.close();
}

int priority(char c)
{
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;

    return 0;
}

bool isSign(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

Number Compute(Number a, Number b, char c)
{
    if (c == '+') return a + b;
    else if (c == '-') return a - b;
    else if (c == '*') return a * b;
    else if (c == '/') return a / b;
    return Number();
}

string removeSpaces(const std::string& input) {
    std::string result;
    for (char c : input) {
        if (c != ' ') {
            result += c;
        }
    }
    return result;
}

void Processing(std::string expression, ofstream& out)
{
    // Hai stack: 
    // - Operator: chứa các toán tử +, -, *, /, (, )
    // - Operand: chứa các số (Number) đã được đọc từ biểu thức
    stack<char> Operator;
    stack<Number> Operand;

    expression = removeSpaces(expression); // Loại bỏ khoảng trắng
    int n = expression.size();

    // Duyệt từng ký tự trong biểu thức
    for (int i = 0; i < n; i++)
    {
        char c = expression[i];
        if (c == ' ') continue;

        // Kiểm tra lỗi: không được có toán tử liên tiếp hoặc toán tử trước dấu ')'
        if (isSign(expression[i])) {
            int j = i + 1;
            if (j < n && (isSign(expression[j]) || expression[j] == ')')) {
                out << "Error" << '\n';
                return;
            }
        }

        // Nếu gặp dấu mở ngoặc '('
        if (c == '(')
        {
            int j = i + 1;

            // Kiểm tra lỗi: không được có "()", "(*)", "(/)"
            if (j < n && expression[j] == ')') {
                out << "Error" << '\n';
                return;
            }

            if (j < n && (expression[j] == '*' || expression[j] == '/')) {
                out << "Error" << '\n';
                return;
            }

            // Nếu sau '(' là một số âm/dương đơn giản, ví dụ "(-123)"
            if (j < n && (expression[j] == '-' || expression[j] == '+')) {
                bool isNegative = (expression[j] == '-') ? 1 : 0;
                int k = j + 1;
                std::string sum = "";

                // Lấy toàn bộ phần số
                while (k < n && isdigit(expression[k])) {
                    sum.push_back(expression[k]);
                    k++;
                }

                // Đẩy số âm/dương vào stack
                i = k - 1;
                Operand.push(Number(sum, isNegative));
            }

            Operator.push(c); // Đẩy '(' vào stack
        }

        // Nếu gặp dấu đóng ngoặc ')'
        else if (c == ')')
        {
            bool findOpenParenthisis = true;

            // Tính toán cho đến khi gặp '(' hoặc lỗi
            while (!Operator.empty() && Operator.top() != '(') {
                //Nếu có toán tử mà không có đủ 2 toán hạng thì lỗi 
                if (Operand.size() < 2) {
                    out << "Error" << '\n';
                    return;
                }

                Number o2 = Operand.top(); Operand.pop();
                Number o1 = Operand.top(); Operand.pop();

                // Kiểm tra chia cho 0
                if (Operator.top() == '/' && o2 == Number("0", false)) {
                    out << "Error" << endl;
                    return;
                }

                Operand.push(Compute(o1, o2, Operator.top()));
                Operator.pop();

                if (Operator.empty()) {
                    findOpenParenthisis = false;
                    break;
                }
            }

            if (!findOpenParenthisis) {
                out << "Error" << '\n';
                return;
            }

            Operator.pop(); // Pop dấu '(' tương ứng
        }

        // Nếu là toán tử: + - * /
        else if (isSign(c)) {
            // Ưu tiên toán tử trong stack trước nếu có độ ưu tiên cao hơn hoặc bằng
            while (!Operator.empty() && priority(Operator.top()) >= priority(c)) {
                if (Operand.size() < 2) {
                    out << "Error" << '\n';
                    return;
                }

                Number o2 = Operand.top(); Operand.pop();
                Number o1 = Operand.top(); Operand.pop();

                if (Operator.top() == '/' && o2 == Number("0", false)) {
                    out << "Error" << endl;
                    return;
                }

                Operand.push(Compute(o1, o2, Operator.top()));
                Operator.pop();
            }
            Operator.push(c); // Đẩy toán tử hiện tại vào stack
        }

        // Nếu là chữ số: đọc cả chuỗi số liên tiếp
        else if (isdigit(c))
        {
            int j = i;
            std::string sum = "";

            // Đọc hết chuỗi số liên tiếp
            while (j < n && isdigit(expression[j])) {
                sum.push_back(expression[j]);
                j++;
            }

            i = j - 1; // Lùi lại 1 ký tự để tiếp tục đọc đúng
            Operand.push(Number(sum, false)); // Đẩy số vào stack
        }
    }

    // Xử lý phần còn lại trong stack
    while (!Operator.empty() && Operator.top() != '(')
    {
        if (Operand.size() < 2) {
            out << "Error" << '\n';
            return;
        }

        Number o2 = Operand.top(); Operand.pop();
        Number o1 = Operand.top(); Operand.pop();

        if (Operator.top() == '/' && o2 == Number("0", false)) {
            out << "Error" << endl;
            return;
        }

        Operand.push(Compute(o1, o2, Operator.top()));
        Operator.pop();
    }

    // In kết quả cuối cùng ra file
    out << Operand.top() << '\n';
}







int main(int argc, char* argv[]) {
    if (argc == 3) {
        Input(argv[1], argv[2]);
    }
    else {
        cout << "Press Terminal: ./24120489 tests.txt output_24120489.txt , with tests.txt: input file, output_24120489.txt: output file";
    }
	return 0;
}