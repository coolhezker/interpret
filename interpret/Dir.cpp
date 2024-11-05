#include "Dir.h"

using namespace std;
using D = Dir;
    D::Dir(const string& n) : name{ n }, parent{ nullptr } {};
    D::Dir(const string& n, Dir* p) : name{ n }, parent{ p } {};
    D::~Dir() {
        for (File* file : files) {
            delete file; // освобождение всех файлов
        }
        for (Dir* child : childs) {
            delete child; // рекурсивное освобождение всех дочерних директорий
        }
    }
    void D::addFile(const string& n) { // добавление объекта типа File в вектор files
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
    void D::addChild(const string& n) { // добавить директорию-ребёнка(вектор childs)
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
    void D::printFiles() { // вывод всех объектов типа File в векторе files
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
    void D::printDirs() { // вывод всех директорий-детей(вектор childs)
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
    void D::printAll() { // вывод всех элементов векторов childs и files
        if (this) {
            cout << "Dirs: ";
            this->printDirs();
            cout << "Files: ";
            this->printFiles();
        }
        else cerr << "Error..." << endl;
    }
    void D::changeContent(const string& n, const string& c) {
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
    const string& D::returnFileContent(const string& n) const { // вывод строки content типа File с name == n
        if (this) {
            bool isFind = false;
            for (int i = 0; i < this->files.size(); i++) {
                if (this->files[i]->getName() == n) {
                    return this->files[i]->returnFileContent(); // эта функция вызывается из класса File(никакой рекурсии нету)
                    isFind = true;
                    break;
                }
            }
            if (!isFind) cout << "No such file." << endl;
        }
        else cerr << "Error..." << endl;
        return "";
    }
    void D::printPath() {
        if (this) {
            vector<Dir*> v;
            Dir* d = this;
            while (d) {
                v.push_back(d);
                d = d->parent;
            }
            for (int i = v.size() - 1; i >= 0; i--) {
                cout << "/" << v[i]->name;
            }
            cout << endl;
        }
    }
    void D::removeDir(const string& s) {
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
    void D::removeFile(const string& s) {
        if (this) {
            bool isFind = false;
            for (int i = 0; i < this->files.size(); i++) {
                if (this->files[i]->getName() == s) {
                    delete this->files[i];
                    this->files.erase(this->files.begin() + i);
                    isFind = true;
                    break;
                }
            }
            if (!isFind) cout << "No such file." << endl;
        }
        else cerr << "Error..." << endl;
    }
    Dir* D::changeDir(const string& s) { // возврат указателя на директорию с именем s
        if (this) {
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