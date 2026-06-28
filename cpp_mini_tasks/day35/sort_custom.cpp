#include <bits/stdc++.h>
using namespace std;

struct Product
{
    string name;
    double price;
};

bool compareByPriceDescending(const Product& a, const Product& b)
{
    return a.price > b.price;
}

int main()
{
    vector<Product> market = {{"Laptop", 999.99}, {"Mobile", 99.9}};

    sort(market.begin(), market.end(), compareByPriceDescending);

    for (const auto& prod : market) {
        std::cout << prod.name << ": $" << prod.price << "\n";
    }

    return 0;
}