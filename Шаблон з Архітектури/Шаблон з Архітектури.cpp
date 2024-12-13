#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
using namespace std;

// --------- MODEL ---------
class TaskModel {
private:
    vector<string> tasks;

public:
    void addTask(const string& task) {
        tasks.push_back(task);
    }

    void deleteTask(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
        }
        else {
            cout << "Невірний номер завдання!\n";
        }
    }

    vector<string> getTasks() const {
        return tasks;
    }
};

// --------- VIEW ---------
class TaskView {
public:
    void displayTasks(const vector<string>& tasks) {
        cout << "Ваші завдання:\n";
        for (int i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << tasks[i] << endl;
        }
    }

    void displayMessage(const string& message) {
        cout << message << endl;
    }
};

// --------- CONTROLLER ---------
class TaskController {
private:
    TaskModel model;
    TaskView view;

public:
    TaskController(TaskModel model, TaskView view) : model(model), view(view) {}

    void addTask(const string& task) {
        model.addTask(task);
        view.displayMessage("Завдання успішно додано.");
    }

    void deleteTask(int index) {
        model.deleteTask(index - 1); // Зсув для 0-індекса
        view.displayMessage("Завдання успішно видалено.");
    }

    void showTasks() {
        vector<string> tasks = model.getTasks();
        if (tasks.empty()) {
            view.displayMessage("Список завдань порожній.");
        }
        else {
            view.displayTasks(tasks);
        }
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    TaskModel model;
    TaskView view;
    TaskController controller(model, view);

    int choice;
    do {
        cout << "\nМенеджер завдань\n";
        cout << "1. Показати завдання\n";
        cout << "2. Додати завдання\n";
        cout << "3. Видалити завдання\n";
        cout << "4. Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            controller.showTasks();
            break;
        }
        case 2: {
            cin.ignore(); // Очистити буфер введення
            string task;
            cout << "Введіть нове завдання: ";
            getline(cin, task);
            controller.addTask(task);
            break;
        }
        case 3: {
            int index;
            cout << "Введіть номер завдання для видалення: ";
            cin >> index;
            controller.deleteTask(index);
            break;
        }
        case 4: {
            cout << "Програма завершена.\n";
            break;
        }
        default: {
            cout << "Невірний вибір. Спробуйте ще раз.\n";
            break;
        }
        }
    } while (choice != 4);

    return 0;
}
