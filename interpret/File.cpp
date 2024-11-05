#include "File.h"
using namespace std;
using F = File;
    F::File(const string& n, const string& c) : name{ n }, content{ c } {};
    F::File(const string& n) : name{ n }, content{ "" } {};
    F::File() : name{ "null.txt" }, content{ "" } {};
    F::~File() {};
    void F::reName(const string& n) { // изменения значения строки name типа File
        if (this) {
            this->name = n;
        }
        else cerr << "Error..." << endl;
    }
    const string& F::getName() const { // возврат строки name типа File
        return this->name;
    }
    void F::addContent(const string& c) { // изменение значения строки content типа File
        if (this) {
            this->content += c;
        }
        else cerr << "Error..." << endl;
    }
    const string& F::returnFileContent() const { // Вывод в поток cout строки content типа File
        if (this) {
            return this->content;
        }
        else cerr << "Error..." << endl;
        return "";
    }