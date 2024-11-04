#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Dir;

class File {
private:
    string name; // ��� �����
    //string format; // ������ �����
    string content; // ������� �����
public:
    //explicit File(const string& n, const string& f, const string& c) : name{ n }, format{ f }, content{ c } {};
    //explicit File(const string& n, const string& f): name{ n }, format{ f }, content{ "" } {};
    explicit File(const string& n, const string& c) : name{ n }, content{ c } {};
    explicit File(const string& n) : name{ n }, content{ "" } {};
    //File() : name{ "null" }, format{ "txt" }, content{ "" } {};
    File() : name{ "null.txt" }, content{ "" } {};
    ~File() {};
    void reName(const string& n) { // ��������� �������� ������ name ���� File
        if (this) {
            this->name = n;
        }
        else cerr << "Error..." << endl;
    }
    /*void change_format(const string& f) { // ��������� �������� ������ format ���� File
        if (this) {
            this->format = f;
        }
        else cerr << "Error..." << endl;
    } */
    const string& getName() { // ������� ������ name ���� File
        if (this) return this->name;
        return nullptr;
    }
    void changeContent(const string& c) { // ��������� �������� ������ content
        if (this) {
            this->content = c;
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
    void addFile(const string& n) { // ���������� ������� ���� File � ������ files
        if (this) {
            File* f = new File{ n };// ��� �������� ������ ������, �� ��� �������� �� �������� deleteFile(const string& n)
                                    // �� ��� �� ����� �� �������. ����� ������ ��-������ ������� �����.
            this->files.push_back(f);
        }
        else cerr << "Error..." << endl;
    }
    void addChild(const string& n) { // �������� ����������-������(������ childs)
        if (this) {
            Dir* newchild = new Dir{ n, this }; // ��� �������� ������ ������, �� ��� �������� �� �������� deleteChild(const string& n)
                                                // �� ��� �� ����� �� �������. ����� ������ ��-������ ������� �����.
            this->childs.push_back(newchild);
        }
        else cerr << "Error..." << endl;
    }
    void printFiles() { // ����� ���� �������� ���� File � ������� files
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
    void printDirs() { // ����� ���� ����������-�����(������ childs)
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
    void printAll() { // ����� ���� ��������� �������� childs � files
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
                    this->files[i]->changeContent(n); // ��� ���������� ������� changeContent �� ������ File, � �� �� ������ Dir(������� �������� ����)
                }
            }
        }
        else cerr << "Error..." << endl;
    }
    Dir* changeDir(const string& s) { // ������� ��������� �� ���������� � ������ s
        if (this) {
            if (s == "..") return this->parent;
            for (int i = 0; i < this->childs.size(); i++) { // ����� ���������� � ������� childs � ������ = s
                if (this->childs[i]->name == s) {
                    return this->childs[i]; // ������� ��������� �� ��� ���������� � ������ s
                }
            }
        }
        cout << "No such directory";
        return this; // ������� ��������� �� ����������, ��� ������� ����������� ������� � ������, ���� �� ������� ����� ���������� � ������ s
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