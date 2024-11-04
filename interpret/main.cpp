#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Dir;

class File {
private:
    string name; // имя файла
    //string format; // формат файла
    string content; // контент файла
public:
    //explicit File(const string& n, const string& f, const string& c) : name{ n }, format{ f }, content{ c } {};
    //explicit File(const string& n, const string& f): name{ n }, format{ f }, content{ "" } {};
    explicit File(const string& n, const string& c) : name{ n }, content{ c } {};
    explicit File(const string& n) : name{ n }, content{ "" } {};
    //File() : name{ "null" }, format{ "txt" }, content{ "" } {};
    File() : name{ "null.txt" }, content{ "" } {};
    ~File() {};
    void reName(const string& n) { // изменения значения строки name типа File
        if (this) {
            this->name = n;
        }
        else cerr << "Error..." << endl;
    }
    /*void change_format(const string& f) { // изменения значения строки format типа File
        if (this) {
            this->format = f;
        }
        else cerr << "Error..." << endl;
    } */
    const string& getName() { // возврат строки name типа File
        if (this) return this->name;
        return nullptr;
    }
    void changeContent(const string& c) { // изменение значения строки content
        if (this) {
            this->content = c;
        }
        else cerr << "Error..." << endl;
    }
};

class Dir {
private:
    string name;
    Dir* parent; // родитель директории
    vector<Dir*> childs; // директории-дети
    vector<File*> files; // файлы в директории
public:
    explicit Dir(const string& n) : name{ n }, parent{ nullptr } {};
    Dir(const string& n, Dir* p) : name{ n }, parent{ p } {};
    void addFile(const string& n) { // добавление объекта типа File в вектор files
        if (this) {
            File* f = new File{ n };// тут возможна утечка памяти, но это решалось бы функцией deleteFile(const string& n)
                                    // но она не нужна по условию. может сделаю по-своему желанию позже.
            this->files.push_back(f);
        }
        else cerr << "Error..." << endl;
    }
    void addChild(const string& n) { // добавить директорию-ребёнка(вектор childs)
        if (this) {
            Dir* newchild = new Dir{ n, this }; // тут возможна утечка памяти, но это решалось бы функцией deleteChild(const string& n)
                                                // но она не нужна по условию. может сделаю по-своему желанию позже.
            this->childs.push_back(newchild);
        }
        else cerr << "Error..." << endl;
    }
    void printFiles() { // вывод всех объектов типа File в векторе files
        if (this) {
            cout << "(";
            for (int i = 0; i < this->files.size(); i++) {
                cout << this->files[i]->getName();
                if (i < this->files.size() - 1) cout << ", ";
            }
            cout << ")" << endl;
        }
        else cerr << "Error..." << endl;
    }
    void printDirs() { // вывод всех директорий-детей(вектор childs)
        if (this) {
            cout << "(";
            for (int i = 0; i < this->childs.size(); i++) {
                cout << this->childs[i]->name;
                if (i < this->childs.size() - 1) cout << ", ";
            }
            cout << ")" << endl;
        }
        else cerr << "Error..." << endl;
    }
    void printAll() { // вывод всех элементов векторов childs и files
        if (this) {
            cout << "Dirs: ";
            this->printDirs();
            cout << "Files: ";
            this->printFiles();
        }
        else cerr << "Error..." << endl;
    }
    void changeContent(const string& n) {
        if (this) {
            for (int i = 0; i < this->files.size(); i++) {
                if (this->files[i]->getName() == n) {
                    this->files[i]->changeContent(n); // тут вызывается функция changeContent из класса File, а не из класса Dir(никакой рекурсии нету)
                }
            }
        }
        else cerr << "Error..." << endl;
    }
    Dir* changeDir(const string& s) { // возврат указателя на директорию с именем s
        if (this) {
            if (s == "..") return this->parent;
            for (int i = 0; i < this->childs.size(); i++) { // поиск директории в векторе childs с именем = s
                if (this->childs[i]->name == s) {
                    return this->childs[i]; // возврат указателя на эту директорию с именем s
                }
            }
        }
        cout << "No such directory";
        return this; // возврат указателя на директорию, для которой выполняется функция в случае, если не найдена нужна директория с именем s
    }
};

int main() {
    string input_line;
    Dir* home = new Dir{ "root" };
    while (true) {
        cout << "> ";
        getline(cin, input_line);
        istringstream iss(input_line);
        string command, arg;
        iss >> command;
        if (command == "exit") {
            break;
        }
        else if (command == "ls") {
            home->printAll();
        }
        else if (command == "cd") {
            if (iss >> arg) {
                home = home->changeDir("arg");
            }
            else {
                cout << "Error: 'cd' command requires an argument." << endl;
            }
        }
        else if (command == "mkdir") {
            if (iss >> arg) {
                home->addChild(arg);
            }
            else {
                cout << "Error: 'mkdir' command requires an argument." << endl;
            }
        } 
        else if (command == "touch") {
            if(iss >> arg) {
                home->addFile(arg);
            }
            else {
                cout << "Error: 'touch' commands requires an argument.";
            }
        } 
        else if (command == "write") {
            if (iss >> arg) {
                home->changeContent(arg);
            }
            else {
                cout << "Error: 'touch' commands requires an argument.";
            }
        }
        else if (command == "cat") {
            if (iss >> arg) {
                home->addFile(arg);
            }
            else {
                cout << "Error: 'touch' commands requires an argument.";
            }
        }
        else {
            cout << "Unknown command: " << command << endl;
        }
    }
    delete home;
    return 0;
}