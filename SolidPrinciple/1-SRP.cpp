/*
Single Responsibility Principle(SRP)
A class should have only one reason to change
Means a class should have only those methods which only change for a single reason or are impacted by only one source.
Simply put, if in future you want to modify the code of a class, then you should only touch that class code every time because of a single source.

One class can have mutiple method. But all of them must change for the same reason
*/

#include <bits/stdc++.h>
using namespace std;

class Product
{
public:
    string name;
    double price;

    Product(string name, double price)
    {
        this->name = name;
        this->price = price;
    }
};

class ShoppingCart
{
private:
    vector<Product *> products;

public:
    void addProduct(Product *p)
    {
        products.push_back(p);
    }

    const vector<Product *> &getProduct()
    {
        return products;
    }

    double calculateTotal()
    {
        double total = 0;
        for (auto p : products)
        {
            total += p->price;
        }

        return total;
    }
};

class ShoppingCartPrinter
{
private:
    ShoppingCart *cart;

public:
    ShoppingCartPrinter(ShoppingCart *cart)
    {
        this->cart = cart;
    }

    void printInvoice()
    {
        cout << "Shopping Cart Invoice:\n";
        for (auto p : cart->getProduct())
        {
            cout << p->name << "------>" << p->price << endl;
        }
        cout << "________________________" << endl;
        cout << "Total" << "------>" << cart->calculateTotal() << endl;
    }
};

class SaveCartToDb
{
private:
    ShoppingCart *cart;

public:
    SaveCartToDb(ShoppingCart *cart)
    {
        this->cart = cart;
    }
    void savetoMongoDb()
    {
        cout << "Saving cart to mongoDb" << endl;
    }
};

int main()
{
    cout << "............starts................" << endl;
    ShoppingCart *cart = new ShoppingCart();
    cart->addProduct(new Product("headphone", 1200.50));
    cart->addProduct(new Product("watch", 600.50));
    cart->addProduct(new Product("tv", 6000.00));

    ShoppingCartPrinter *printer = new ShoppingCartPrinter(cart);
    printer->printInvoice();

    SaveCartToDb *saveDb = new SaveCartToDb(cart);
    saveDb->savetoMongoDb();

    cout << "............end................";
}
