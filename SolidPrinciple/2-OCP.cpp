/*
OPEN-CLOSED PRINCIPLE(OCP)
A class should be open for extension but closed for modification.
*/

#include <bits/stdc++.h>

using namespace std;

class PaymentProcessor
{
protected:
    int price;

public:
    PaymentProcessor() : price(0) {};
    virtual void processPayment(int price) = 0; // pure virtual
};

class UpiPaymentProcessor : public PaymentProcessor
{
public:
    void processPayment(int price) override
    {
        cout << "Process the upi payment: " << price << endl;
    }
};

class CreditPaymentProcessor : public PaymentProcessor
{
public:
    void processPayment(int price) override
    {
        cout << "Process the credit card payment: " << price << endl;
    }
};

class CryptoPaymentProcessor : public PaymentProcessor
{
public:
    void processPayment(int price) override
    {
        cout << "Process the crypto payment: " << price << endl;
    }
};

int main()
{

    PaymentProcessor *upi = new UpiPaymentProcessor();
    PaymentProcessor *credit = new CreditPaymentProcessor();
    PaymentProcessor *crypto = new CryptoPaymentProcessor();

    upi->processPayment(100);
    credit->processPayment(200);
    crypto->processPayment(300);

    delete upi;
    delete credit;
    delete crypto;
}