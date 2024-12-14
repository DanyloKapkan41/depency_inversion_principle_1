#include <iostream>
#include <memory>
using namespace std;
// Абстракція для робітника
class IWorker {
public:
    virtual void doWork() = 0;
    virtual ~IWorker() = default;
};

// Реалізація звичайного працівника
class Worker : public IWorker {
public:
    void doWork() override {
        cout << "Worker is doing work." << endl;
    }
};

// Реалізація фрілансера
class Freelancer : public IWorker {
public:
    void doWork() override {
        cout << "Freelancer is doing work remotely." << endl;
    }
};

// Менеджер тепер залежить від абстракції
class Manager {
private:
    shared_ptr<IWorker> worker;
public:
    Manager(shared_ptr<IWorker> w) : worker(w) {}

    void manage() {
        worker->doWork();
    }
};

int main() {
    auto worker = make_shared<Worker>();
    auto freelancer = make_shared<Freelancer>();

    Manager manager1(worker);
    Manager manager2(freelancer);

    manager1.manage();  // Worker is doing work.
    manager2.manage();  // Freelancer is doing work remotely.

    return 0;
}

/*
Порушення принципу DIP
Розглянемо простий приклад: клас Worker, який використовується менеджером Manager для виконання роботи.

#include <iostream>

class Worker {
public:
    void doWork() {
        std::cout << "Worker is doing work." << std::endl;
    }
};

class Manager {
private:
    Worker worker;
public:
    void manage() {
        worker.doWork();
    }
};

int main() {
    Manager manager;
    manager.manage();
    return 0;
}
Проблеми:
Клас Manager напряму залежить від конкретного класу Worker.
Якщо ми захочемо замінити Worker на іншу реалізацію (наприклад, Freelancer), доведеться змінювати код Manager, порушуючи принцип відкритості/закритості (OCP).
*/