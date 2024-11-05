#ifndef DIR_H
#define DIR_H

#include <iostream>
#include <vector>
#include <string>
#include "File.h"

class Dir {
private:
    std::string name;
    Dir* parent; // родитель директории
    std::vector<Dir*> childs; // директории-дети
    std::vector<File*> files; // файлы в директории
public:
    explicit Dir(const std::string& n);
    Dir(const std::string& n, Dir* p);
    ~Dir();
    void addFile(const std::string& n);
    void addChild(const std::string& n);
    void printFiles();
    void printDirs();
    void printAll();
    void changeContent(const std::string& n, const std::string& c);
    const std::string& returnFileContent(const std::string& n) const;
    void printPath();
    void removeDir(const std::string& s);
    void removeFile(const std::string& s);
    Dir* changeDir(const std::string& s);
};

#endif