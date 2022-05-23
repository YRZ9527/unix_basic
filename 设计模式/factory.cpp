#include "iostream"
using namespace std;

class Product
{
public:
    virtual ~Product() = 0;

protected:
    Product() {}

private:
};
class ConcreteProduct : public Product
{
public:
    ~ConcreteProduct(){};
    ConcreteProduct()
    {
        cout << "ConcraateProduct" << endl;
    }

protected:
private:
};

class Factory
{
public:
    virtual ~Factory() = 0;
    virtual Product *CreateProduct() = 0;

protected:
    Factory();
};

class ConcreteFactory : public Factory
{
public:
    ~ConcreteFactory() override;
    ConcreteFactory()
    {
        cout<<"ConcreteFactory..."<<endl;
    }
    Product *CreateProuct()
    {
        return new ConcreteProduct();
    }

protected:
};

int main(int argc, char **argv)
{
    Factory* fac = new ConcreteFactory();
    Product* p = fac->CreateProduct();


    return 0;
}