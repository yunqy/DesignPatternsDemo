#include <iostream>
#include <string>
class Product {
public:
    virtual void describe() = 0;
};
class Factory {
public:
    virtual Product* getProduct() = 0;
};

class FrenchFries : public Product {
public:
    void describe() {
        std::cout << "This is " << _state << " French Fries." << std::endl;
    }
    void setState(std::string state){
        _state = state;
    }
private:
    std::string _state;
};

class FrenchFriesFactory : public Factory {
public:
    Product* getProduct() {
        return new FrenchFries();
    }
};

int main() {
    FrenchFriesFactory frenchFriesFactory;
    FrenchFries* frenchFries = (FrenchFries*)frenchFriesFactory.getProduct();
    frenchFries->setState("salty");
    frenchFries->describe();
}

