#include <iostream>
#include <vector>

class Weapon {
public:
    Weapon() : _atk(0), _range(0) {}
    Weapon(int atk, int range) : _atk(atk), _range(range) {}
    virtual void display() {
        std::cout << "[" << typeid(*this).name() <<  "] with atk: " << _atk << ", range: " << _range << std::endl;
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
        std::cout << "[" << typeid(*this).name() <<  "] with def: " << _def << std::endl;
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

class FightStrategy {
public:
    FightStrategy() {}
    FightStrategy(std::string strategyName) : _strategyName(strategyName) {}
    virtual void execute() const = 0;
    std::string getName() {
        return _strategyName;
    }
private:
    std::string _strategyName;
};

class NormalAttack : public FightStrategy {
public:
    NormalAttack() : FightStrategy("Nornal Attack") {}
    void execute() const override {
        std::cout << "Normal attack!" << std::endl;
    }
};

class UseSkill : public FightStrategy {
public:
    UseSkill() : FightStrategy("Use Skill") {}
    void execute() const override {
        std::cout << "Attack with skill!" << std::endl;
    }
};

class UseItem : public FightStrategy {
public:
    UseItem() : FightStrategy("Use Item") {}
    void execute() const override {
        std::cout << "Attack with item!" << std::endl;
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
    void setStrategy() {
        int idx = 0;
        std::cin >> idx;
        if (idx < _fightStategyList.size()) {
            chooseStategy(idx);
        } else {
            std::cout << "Wrong input, please choose again!" << std::endl;
            showStategies();
            setStrategy();
        }
    }
    void chooseStategy(int index) {
        _fightStrategy = _fightStategyList[index];
    }
    void showStategies() {
        for(int i = 0; i < _fightStategyList.size(); ++i) {
            std::cout << "[" << i << "] " << _fightStategyList[i]->getName() << std::endl;
        }
    }
    void addStategy(FightStrategy* fightStrategy) {
        _fightStategyList.push_back(fightStrategy);
    }
    void attack() {
        if (_fightStrategy) {
            _fightStrategy->execute();
        } else {
            std::cout << "Plese choose one strategy first!" << std::endl;
            showStategies();
            setStrategy();
            attack();
        }
    };
protected:
    Weapon* _weapon;
    Cloths* _cloths;
    FightStrategy* _fightStrategy;
    std::vector<FightStrategy*> _fightStategyList;
};

class Warrior : public Advanturer {
public:
    void printAdvantureInfo() const override {
        std::cout << "This is a Warrior." << std::endl;
        std::cout << "[Weapon] ";
        _weapon->display();
        std::cout << "[Cloths] ";
        _cloths->display();
    }
};

class Archer : public Advanturer {
public:
    void printAdvantureInfo() const override {
        std::cout << "This is an Archer." << std::endl;
        std::cout << "[Weapon] ";
        _weapon->display();
        std::cout << "[Cloths] ";
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
        advanturer->addStategy(new NormalAttack());
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
        advanturer->addStategy(new NormalAttack());
        return advanturer;
    }
private:
    EquipmentFactory* getEqpFactory() const {
        static EquipmentFactory* eqpFactory = new ArcherEquipmentFactory();
        return eqpFactory;
    }
};

TrainingCamp* chooseCharactor() {
    std::cout << "Please choose a charactor:" << std::endl;
    std::cout << "[0]: Warrior" << std::endl;
    std::cout << "[1]: Archer" << std::endl;
    int idx = 0;
    std::cin >> idx;
    if (idx == 0) {
        std::cout << "=====Create a Warrior=====" << std::endl;
        return new WarriorTrainingCamp();
    } else if (idx == 1) {
        std::cout << "=====Create a Archer=====" << std::endl;
        return new ArcherTrainingCamp();
    } else {
        return chooseCharactor();
    }
}

bool chooseAction(Advanturer* advanturer) {
    std::cout << "Please choose an action:" << std::endl;
    std::cout << "[0]: Show advanturer info" << std::endl;
    std::cout << "[1]: Attack" << std::endl;
    std::cout << "[2]: Exit" << std::endl;
    int idx = 0;
    std::cin >> idx;
    if (idx == 0) {
        advanturer->printAdvantureInfo();
    } else if (idx == 1) {
        advanturer->attack();
    } else if (idx == 2) {
        return false;
    }
    return true;
}

int main() {
    TrainingCamp* trainingCamp;
    Advanturer* advanturer;
    trainingCamp = chooseCharactor();
    advanturer = trainingCamp->trainAdvanturer();
    bool continueGame = true;
    while (continueGame) {
        continueGame = chooseAction(advanturer);
    }
    delete trainingCamp;
    delete advanturer;
}