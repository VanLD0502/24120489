#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// struct Product
// {
//     char ten[26];
//     float quantity;
//     float price;
// };
// struct Category
// {
//     char ten[26];
//     int quantity;
//     Product products[100];
// };

class Vector
{
private:
    struct Node
    {
        int data;
        Node *_next;
    };

public:
    class Iterator;

    
};

class Iterator
{
private:
    int a = 5;

public:
    int b = 7;
};
int main()
{
    return 0;
}

void Duyen()
{
    // ifstream fin("input.txt");

    // if (!fin.is_open())
    // {
    //     cout << "LOI";
    //     return 0;
    // }

    // Category cat[100];
    // int cnt = 0;
    // char buffer[1024];
    // while (fin.getline(buffer, sizeof(buffer)))
    // {
    //     char *context = nullptr;
    //     const char *delimiter = ">";
    //     char *token = strtok_s(buffer, delimiter, &context);
    //     strcpy_s(cat[cnt].ten, sizeof(cat[cnt].ten), token);
    //     int productCnt = 0;
    //     while (token != nullptr)
    //     {
    //         token = strtok_s(nullptr, "/", &context);
    //         if (token == nullptr)
    //             break;

    //         char *productContext = nullptr;
    //         char *productToken = strtok_s(token, ",", &productContext);

    //         Product newProduct;

    //         if (productToken)
    //             strcpy_s(newProduct.ten, sizeof(newProduct.ten), productToken);

    //         productToken = strtok_s(nullptr, ",", &productContext);
    //         newProduct.quantity = atoi(productToken);

    //         productToken = strtok_s(nullptr, ",", &productContext);
    //         newProduct.price = atof(productToken);

    //         cat[cnt].products[productCnt] = newProduct;

    //         productCnt++;
    //     }

    //     cat[cnt].quantity = productCnt;
    //     cnt++;
    // }

    // for (int i = 0; i < cnt; i++)
    // {
    //     cout << i << " " << cat[i].ten << " " << cat[i].quantity << '\n';
    //     for (int j = 0; j < cat[i].quantity; j++)
    //     {
    //         cout << cat[i].products[j].ten << " " << cat[i].products[j].quantity << " " << cat[i].products[j].price << '\n';
    //     }
    // }

    // ifstream fin("input2.txt");
    // int a, b;
    // char c[3];

    // fin >> a;
    // fin.ignore();
    // fin.getline(c, sizeof(c));
    // // fin >> b;

    // cout << a << endl;
    // // cout << b << endl;
    // cout << c << endl;
}