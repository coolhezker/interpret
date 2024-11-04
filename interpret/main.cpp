#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Dir;

const string root = "root";

class File {
private:
    string name; // имя файла
    string content; // контент файла
public:
    explicit File(const string& n, const string& c) : name{ n }, content{ c } {};
    explicit File(const string& n) : name{ n }, content{ "" } {};
    File() : name{ "null.txt" }, content{ "" } {};
    ~File() {};
    void reName(const string& n) { // изменения значения строки name типа File
        if (this) {
            this->name = n;
        }
        else cerr << "Error..." << endl;
    }
    const string& getName() const { // возврат строки name типа File
        return this->name;
    }
    void changeContent(const string& c) { // изменение значения строки content типа File
        if (this) {
            this->content += c;
        }
        else cerr << "Error..." << endl;
    }
    void seeFileContent() const{ // Вывод в поток cout строки content типа File
        if (this) {
            cout << this->content << endl;
        }
        else cerr << "Error..." << endl;
    }
    bool operator!=(const File& f1) {
        return name != f1.name;
    }
    bool operator==(const File& f1) {
        return name == f1.name;
    }
    void removeFile() {
        delete this;
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
    void printFiles() const { // вывод всех объектов типа File в векторе files
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
    void printDirs() const { // вывод всех директорий-детей(вектор childs)
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
    void printAll() const { // вывод всех элементов векторов childs и files
        if (this) {
            cout << "Dirs: ";
            this->printDirs();
            cout << "Files: ";
            this->printFiles();
        }
        else cerr << "Error..." << endl;
    }
    void changeContent(const string& n, const string& c) {
        if (this) {
            bool isFind = false;
            for (int i = 0; i < this->files.size(); i++) {
                if (this->files[i]->getName() == n) {
                    this->files[i]->changeContent(c); // тут вызывается функция changeContent из класса File, а не из класса Dir(никакой рекурсии нету)
                    isFind = true;
                    break;
                }
            }
            if (!isFind) cout << "No such file." << endl;
        }
        else cerr << "Error..." << endl;
    }
    void seeFileContent(const string& n) const { // вывод строки content типа File с name == n
        if (this) {
            bool isFind = false;
            for (int i = 0; i < this->files.size(); i++) {
                if (this->files[i]->getName() == n) {
                    this->files[i]->seeFileContent(); // эта функция вызывается из класса File(никакой рекурсии нету)
                    isFind = true;
                    break;
                }
            }
            if (!isFind) cout << "No such file." << endl;
        }
        else cerr << "Error..." << endl;
    }
    void printPath() {
        if (this) {
            vector<Dir*> v;
            Dir* d = this;
            while (d->parent != nullptr) {
                v.push_back(d);
                d = d->parent;
            }
            cout << "/" << root;
            for (int i = v.size() - 1; i >= 0; i--) {
                cout << "/" << v[i]->name;
            }
            cout << endl;
        }
    }
    bool operator!=(const Dir& d) const {
        return name != d.name;
    }
    bool operator==(const Dir& d) const {
        return name == d.name;
    }
    Dir* changeDir(const string& s) { // возврат указателя на директорию с именем s
        if (this != nullptr) {
            if (s == ".." && this->parent) return this->parent;
            for (int i = 0; i < this->childs.size(); i++) { // поиск директории в векторе childs с именем = s
                if (this->childs[i]->name == s) {
                    return this->childs[i]; // возврат указателя на эту директорию с именем s
                }
            }
            cout << "No such directory." << endl;
        } 
        else cerr << "Error..." << endl;
        return this; // возврат указателя на директорию, для которой выполняется функция в случае, если не найдена нужна директория с именем s
    }
};

int main() {
    string input_line;
    Dir* home = new Dir{ root };
    while (true) {
        cout << "> ";
        getline(cin, input_line);
        istringstream iss(input_line);
        string command, arg, arg2;
        iss >> command;
        if (command == "exit") {
            break;
        }
        else if (command == "ls") {
            home->printAll();
        }
        else if (command == "pwd") {
            home->printPath();
        }
        else if (command == "cd") {
            if (iss >> arg) {
                home = home->changeDir(arg);
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
                cout << "Error: 'touch' commands requires an argument." << endl;
            }
        } 
        else if (command == "write") {
            if (iss >> arg) {
                if (getline(iss, arg2)) {
                    arg2[0] = '\0'; // думаю можно сделать как-то более адекватно(это нужно чтобы пробел после arg стал пустым символом
                    home->changeContent(arg, arg2);
                }
                else cout << "Error: content is invalid." << endl;
            }
            else cout << "Error: 'write' commands requires an argument." << endl;
        }
        else if (command == "cat") {
            if (iss >> arg) {
                home->seeFileContent(arg);
            }
            else cout << "Error: 'cat' commands requires an argument." << endl;
        }
        else cout << "Unknown command: " << command << endl;
    }
    delete home;
    return 0;
}