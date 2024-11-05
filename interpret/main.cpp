#include "File.h"
#include "Dir.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

const string root = "root";

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
                cout << currentDir->returnFileContent(arg) << endl;
            }
            else cout << "Error: 'cat' commands requires an argument." << endl;
        }
        else if (command == "rmdir") {
            if (iss >> arg) {
                currentDir->removeDir(arg);
            }
            else cout << "Error: 'rmdir' commands requires an argument." << endl;
        }
        else if (command == "rmfile") {
            if (iss >> arg) {
                currentDir->removeFile(arg);
            }
            else cout << "Error: 'rmfile' commands requires an argument." << endl;
        }
        else cout << "Unknown command: " << command << endl;
    }
    delete currentDir;
    return 0;
}