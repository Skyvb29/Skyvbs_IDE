#include "compiler.h"
#include "colours.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void build_file(string f_name)
{
    if (f_name.empty())
    {
        cout << RED << "[ERROR] Enter file name" << RESET << endl;
        return;
    }

    string fullpath = "user/" + f_name;

    ifstream file(fullpath);
    if (!file.is_open())
    {
        cout << RED << "[ERROR] File not found: " << f_name << RESET << endl;
        return;
    }
    file.close();

    size_t pos = f_name.find_last_of('.');
    string base = (pos == string::npos) ? f_name : f_name.substr(0, pos);

    string exepath = "user/" + base + ".exe";

    string command = "g++ \"" + fullpath + "\" -o \"" + exepath + "\"";

    cout << CYAN << "Compiling " << f_name << "..." << RESET << endl;

    int result = system(command.c_str());
    if (result == 0)
        cout << GREEN << "[SUCCESS] Build complete: " << exepath << RESET << endl;
    else
        cout << RED << "[FAILED] Could not build file." << RESET << endl;
}

void run_file(const string &f_name)
{
    size_t pos = f_name.find_last_of('.');
    string base = (pos == string::npos) ? f_name : f_name.substr(0, pos);

    string exepath = "user/" + base + ".exe";

    ifstream check(exepath);
    if (!check.is_open())
    {
        cout << RED << "[ERROR] Executable not found. Build first." << RESET << endl;
        return;
    }
    check.close();

    cout << CYAN << "Running " << exepath << "..." << RESET << endl;

    string command = "\"user\\" + base + ".exe\"";
    system(command.c_str());
}
