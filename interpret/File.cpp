#include "File.h"
using namespace std;
using F = File;
    F::File(const string& n, const string& c) : name{ n }, content{ c } {};
    F::File(const string& n) : name{ n }, content{ "" } {};
    F::File() : name{ "null.txt" }, content{ "" } {};
    F::~File() {};
    void F::reName(const string& n) { // ��������� �������� ������ name ���� File
        if (this) {
            this->name = n;
        }
        else cerr << "Error..." << endl;
    }
    const string& F::getName() const { // ������� ������ name ���� File
        return this->name;
    }
    void F::addContent(const string& c) { // ��������� �������� ������ content ���� File
        if (this) {
            this->content += c;
        }
        else cerr << "Error..." << endl;
    }
    const string& F::returnFileContent() const { // ����� � ����� cout ������ content ���� File
        if (this) {
            return this->content;
        }
        else cerr << "Error..." << endl;
        return "";
    }