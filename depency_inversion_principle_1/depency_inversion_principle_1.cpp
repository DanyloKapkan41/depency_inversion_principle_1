#include <iostream>
#include <memory>
using namespace std;
// ���������� ��� ��������
class IWorker {
public:
    virtual void doWork() = 0;
    virtual ~IWorker() = default;
};

// ��������� ���������� ����������
class Worker : public IWorker {
public:
    void doWork() override {
        cout << "Worker is doing work." << endl;
    }
};

// ��������� ���������
class Freelancer : public IWorker {
public:
    void doWork() override {
        cout << "Freelancer is doing work remotely." << endl;
    }
};

// �������� ����� �������� �� ����������
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
��������� �������� DIP
���������� ������� �������: ���� Worker, ���� ��������������� ���������� Manager ��� ��������� ������.

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
��������:
���� Manager ������� �������� �� ����������� ����� Worker.
���� �� �������� ������� Worker �� ���� ��������� (���������, Freelancer), ���������� �������� ��� Manager, ��������� ������� ���������/��������� (OCP).
*/