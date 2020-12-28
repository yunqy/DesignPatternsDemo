#include <iostream>

class Weapon {
public:
    Weapon() : _atk(0), _range(0) {}
    Weapon(int atk, int range) : _atk(atk), _range(range) {}
    virtual void display() {
        std::cout << "This is " << typeid(*this).name() <<  " with atk: " << _atk << ", range: " << _range << std::endl;
    }
protected:
    int _atk;
    int _range;
};

class LongSword : public Weapon {
public:
    LongSword() : Weapon() {}
    LongSword(int atk, int range) : Weapon(atk, range) {}
};

class Bow : public Weapon {
public:
    Bow() : Weapon() {}
    Bow(int atk, int range) : Weapon(atk, range) {}
};

class Cloths {
public:
    Cloths() : _def(0) {}
    Cloths(int def) : _def(def) {}
    virtual void display() {
        std::cout << "This is " << typeid(*this).name() <<  " with def: " << _def << std::endl;
    }
protected:
    int _def;
};

class Armor : public Cloths {
public:
    Armor() : Cloths() {}
    Armor(int def) : Cloths(def) {}
};

class Leather : public Cloths {
public:
    Leather() : Cloths() {}
    Leather(int def) : Cloths(def) {}
};

class EquipmentFactory {
public:
    virtual Weapon* productWeapon() const = 0;
    virtual Cloths* productCloths() const = 0;
};

class WarriorEquipmentFactory : public EquipmentFactory {
public:
    Weapon* productWeapon() const override {
        LongSword* weapon = new LongSword(10, 1);
        return weapon;
    }
    Cloths* productCloths() const override {
        Armor* cloths = new Armor(10);
        return cloths;
    }
};

class ArcherEquipmentFactory : public EquipmentFactory {
public:
    Weapon* productWeapon() const override {
        Bow* weapon = new Bow(10, 10);
        return weapon;
    }
    Cloths* productCloths() const override {
        Leather* cloths = new Leather(5);
        return cloths;
    }
};

class Advanturer {
public:
    virtual void printAdvantureInfo() const = 0;
    void setWeapon(Weapon* weapon) {
        _weapon = weapon;
    }
    void setCloths(Cloths* cloths) {
        _cloths = cloths;
    }
protected:
    Weapon* _weapon;
    Cloths* _cloths;
};

class Warrior : public Advanturer {
public:
    void printAdvantureInfo() const override {
        std::cout << "This is a Warrior." << std::endl;
        std::cout << "[Weapon]" << std::endl;
        _weapon->display();
        std::cout << "[Cloths]" << std::endl;
        _cloths->display();
    }
};

class Archer : public Advanturer {
public:
    void printAdvantureInfo() const override {
        std::cout << "This is an Archer." << std::endl;
        std::cout << "[Weapon]" << std::endl;
        _weapon->display();
        std::cout << "[Cloths]" << std::endl;
        _cloths->display();
    }
};

class TrainingCamp {
public:
    virtual Advanturer* trainAdvanturer() const = 0;
};

class WarriorTrainingCamp : public TrainingCamp {
public:
    Advanturer* trainAdvanturer() const override {
        Warrior* advanturer = new Warrior();
        advanturer->setWeapon(getEqpFactory()->productWeapon());
        advanturer->setCloths(getEqpFactory()->productCloths());
        return advanturer;
    }
private:
    EquipmentFactory* getEqpFactory() const {
        static EquipmentFactory* eqpFactory = new WarriorEquipmentFactory();
        return eqpFactory;
    }
};

class ArcherTrainingCamp : public TrainingCamp {
public:
    Advanturer* trainAdvanturer() const override {
        Archer* advanturer = new Archer();
        advanturer->setWeapon(getEqpFactory()->productWeapon());
        advanturer->setCloths(getEqpFactory()->productCloths());
        return advanturer;
    }
private:
    EquipmentFactory* getEqpFactory() const {
        static EquipmentFactory* eqpFactory = new ArcherEquipmentFactory();
        return eqpFactory;
    }
};

int main() {
    TrainingCamp* trainingCamp;
    Advanturer* advanturer;
    std::cout << "=====Create a Warrior=====" << std::endl;
    trainingCamp = new WarriorTrainingCamp();
    advanturer = trainingCamp->trainAdvanturer();
    advanturer->printAdvantureInfo();
    delete trainingCamp;
    delete advanturer;
    std::cout << "=====Create a Archer=====" << std::endl;
    trainingCamp = new ArcherTrainingCamp();
    advanturer = trainingCamp->trainAdvanturer();
    advanturer->printAdvantureInfo();
}