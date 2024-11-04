#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Dir;

const string root = "root";

class File {
private:
    string name; // им€ файла
    string content; // контент файла
public:
    explicit File(const string& n, const string& c) : name{ n }, content{ c } {};
    explicit File(const string& n) : name{ n }, content{ "" } {};
    File() : name{ "null.txt" }, content{ "" } {};
    ~File() {};
    void reName(const string& n) { // изменени€ значени€ строки name типа File
        if (this) {
            this->name = n;
        }
        else cerr << "Error..." << endl;
    }
    const string& getName() const { // возврат строки name типа File
        return this->name;
    }
    void changeContent(const string& c) { // изменение значени€ строки content типа File
        if (this) {
            this->content += c;
        }
        else cerr << "Error..." << endl;
    }
    void seeFileContent() const{ // ¬ывод в поток cout строки content типа File
        if (this) {
            cout << this->content << endl;
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
    ~Dir() {
        for (File* file : files) {
            delete file; // освобождение всех файлов
        }
        for (Dir* child : childs) {
            delete child; // рекурсивное освобождение всех дочерних директорий
        }
    }
    void addFile(const string& n) { // добавление объекта типа File в вектор files
        if (this) {
            for (int i = 0; i < this->files.size(); i++) {
                if (this->files[i]->getName() == n) {
                    cout << "This file already exists." << endl;
                    return;
                }
            }
            File* f = new File{ n };
            this->files.push_back(f);
        }
        else cerr << "Error..." << endl;
    }
    void addChild(const string& n) { // добавить директорию-ребЄнка(вектор childs)
        if (this) {
            for (int i = 0; i < this->childs.size(); i++) {
                if (this->childs[i]->name == n) {
                    cout << "This directory already exists." << endl;
                    return;
                }
            }
            Dir* newchild = new Dir{ n, this };
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
                    this->files[i]->changeContent(c); // тут вызываетс€ функци€ changeContent из класса File, а не из класса Dir(никакой рекурсии нету)
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
                    this->files[i]->seeFileContent(); // эта функци€ вызываетс€ из класса File(никакой рекурсии нету)
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
    void removeDir(const string& s) {
        if (this) {
            bool isFind = false;
            for (int i = 0; i < this->childs.size(); i++) { // поиск директории в векторе childs с именем = s
                if (this->childs[i]->name == s) {
                    delete this->childs[i];
                    this->childs.erase(this->childs.begin() + i);
                    isFind = true;
                }
            }
            if (!isFind) cout << "No such directory" << endl;
        }
        else cerr << "Error..." << endl;
    }
    Dir* changeDir(const string& s) { // возврат указател€ на директорию с именем s
        if (this) {
            if (s == ".." && this->parent) return this->parent;
            for (int i = 0; i < this->childs.size(); i++) { // поиск директории в векторе childs с именем = s
                if (this->childs[i]->name == s) {
                    return this->childs[i]; // возврат указател€ на эту директорию с именем s
                }
            }
            cout << "No such directory." << endl;
        } 
        else cerr << "Error..." << endl;
        return this; // возврат указател€ на директорию, дл€ которой выполн€етс€ функци€ в случае, если не найдена нужна директори€ с именем s
    }
};

int main() {
    string input_line;
    Dir* currentDir = new Dir{ root };
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
            currentDir->printAll();
        }
        else if (command == "pwd") {
            currentDir->printPath();
        }
        else if (command == "cd") {
            if (iss >> arg) {
                currentDir = currentDir->changeDir(arg);
            }
            else {
                cout << "Error: 'cd' command requires an argument." << endl;
            }
        }
        else if (command == "mkdir") {
            if (iss >> arg) {
                currentDir->addChild(arg);
            }
            else {
                cout << "Error: 'mkdir' command requires an argument." << endl;
            }
        } 
        else if (command == "touch") {
            if(iss >> arg) {
                currentDir->addFile(arg);
            }
            else {
                cout << "Error: 'touch' commands requires an argument." << endl;
            }
        } 
        else if (command == "write") {
            if (iss >> arg) {
                if (getline(iss, arg2)) {
                    arg2[0] = '\0'; // думаю можно сделать как-то более адекватно(это нужно чтобы пробел после arg стал пустым символом
                    currentDir->changeContent(arg, arg2);
                }
                else cout << "Error: content is invalid." << endl;
            }
            else cout << "Error: 'write' commands requires an argument." << endl;
        }
        else if (command == "cat") {
            if (iss >> arg) {
                currentDir->seeFileContent(arg);
            }
            else cout << "Error: 'cat' commands requires an argument." << endl;
        }
        else if (command == "rmdir") {
            if (iss >> arg) {
                currentDir->removeDir(arg);
            }
        }
        else cout << "Unknown command: " << command << endl;
    }
    delete currentDir;
    return 0;
}