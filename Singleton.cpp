class Manager {
public:
    int id;
    static Manager* getInstance() {
        if (!_instance)
            _instance = new Manager();
        return _instance;
    }
    static void destroyInstance() {
        if (_instance)
            delete _instance;
        _instance = nullptr;
    }
private:
    Manager();
    // static Manager* setManager() {
    //     static Manager* manager = new Manager();
    //     return maganer;
    // }
    static Manager* _instance;
}

Manager* Manager::_instance = nullptr;

int main() {
    Manager* m = Manager::getManager();
    m->id = 123;
}