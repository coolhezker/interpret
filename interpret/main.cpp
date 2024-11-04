#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Dir;

const string root = "root";

class File {
private:
    string name; // ��� �����
    string content; // ������� �����
public:
    explicit File(const string& n, const string& c) : name{ n }, content{ c } {};
    explicit File(const string& n) : name{ n }, content{ "" } {};
    File() : name{ "null.txt" }, content{ "" } {};
    ~File() {};
    void reName(const string& n) { // ��������� �������� ������ name ���� File
        if (this) {
            this->name = n;
        }
        else cerr << "Error..." << endl;
    }
    const string& getName() const { // ������� ������ name ���� File
        return this->name;
    }
    void changeContent(const string& c) { // ��������� �������� ������ content ���� File
        if (this) {
            this->content += c;
        }
        else cerr << "Error..." << endl;
    }
    void seeFileContent() const{ // ����� � ����� cout ������ content ���� File
        if (this) {
            cout << this->content << endl;
        }
        else cerr << "Error..." << endl;
    }
};

class Dir {
private:
    string name;
    Dir* parent; // �������� ����������
    vector<Dir*> childs; // ����������-����
    vector<File*> files; // ����� � ����������
public:
    explicit Dir(const string& n) : name{ n }, parent{ nullptr } {};
    Dir(const string& n, Dir* p) : name{ n }, parent{ p } {};
    ~Dir() {
        for (File* file : files) {
            delete file; // ������������ ���� ������
        }
        for (Dir* child : childs) {
            delete child; // ����������� ������������ ���� �������� ����������
        }
    }
    void addFile(const string& n) { // ���������� ������� ���� File � ������ files
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
    void addChild(const string& n) { // �������� ����������-������(������ childs)
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
    void printFiles() const { // ����� ���� �������� ���� File � ������� files
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
    void printDirs() const { // ����� ���� ����������-�����(������ childs)
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
    void printAll() const { // ����� ���� ��������� �������� childs � files
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
                    this->files[i]->changeContent(c); // ��� ���������� ������� changeContent �� ������ File, � �� �� ������ Dir(������� �������� ����)
                    isFind = true;
                    break;
                }
            }
            if (!isFind) cout << "No such file." << endl;
        }
        else cerr << "Error..." << endl;
    }
    void seeFileContent(const string& n) const { // ����� ������ content ���� File � name == n
        if (this) {
            bool isFind = false;
            for (int i = 0; i < this->files.size(); i++) {
                if (this->files[i]->getName() == n) {
                    this->files[i]->seeFileContent(); // ��� ������� ���������� �� ������ File(������� �������� ����)
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
            for (int i = 0; i < this->childs.size(); i++) { // ����� ���������� � ������� childs � ������ = s
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
    Dir* changeDir(const string& s) { // ������� ��������� �� ���������� � ������ s
        if (this) {
            if (s == ".." && this->parent) return this->parent;
            for (int i = 0; i < this->childs.size(); i++) { // ����� ���������� � ������� childs � ������ = s
                if (this->childs[i]->name == s) {
                    return this->childs[i]; // ������� ��������� �� ��� ���������� � ������ s
                }
            }
            cout << "No such directory." << endl;
        } 
        else cerr << "Error..." << endl;
        return this; // ������� ��������� �� ����������, ��� ������� ����������� ������� � ������, ���� �� ������� ����� ���������� � ������ s
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
                    arg2[0] = '\0'; // ����� ����� ������� ���-�� ����� ���������(��� ����� ����� ������ ����� arg ���� ������ ��������
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