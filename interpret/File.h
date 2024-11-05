#ifndef FILE_H
#define FILE_H

#include <vector>
#include <string>
#include <iostream>
class File {
private:
    std::string name; // имя файла
    std::string content; // контент файла
public:
    explicit File(const std::string& n, const std::string& c);
    explicit File(const std::string& n);
    File();
    ~File();
    void reName(const std::string& n);
    const std::string& getName() const;
    void changeContent(const std::string& c);
    const std::string& returnFileContent() const;
};
#endif