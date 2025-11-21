#include "compiler.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void build_file(string f_name)
{
    if (f_name.empty())
    {
        cout << "Enter file name" << endl;
        return;
    }
    ifstream file(f_name);
    if (!file.is_open())
    {
        cout << "[ERROR] File not found : " << f_name << endl;
        return;
    }
    file.close();

    size_t pos = f_name.find_last_of('.');
    string base = (pos == string::npos) ? f_name : f_name.substr(0, pos);
    string exefile = base + ".exe";
    string command = "g++ " + f_name + " -o " + exefile;
    cout << "Compiling " << f_name << "...." << endl;

    int result = system(command.c_str());
    if (result == 0)
    {
        cout << "[SUCCESS] Build complete... " << exefile << endl;
    }
    else
        cout << "[FAILED] Could not build file." << endl;
}

void run_file(const string &f_name)
{
    size_t pos = f_name.find_last_of('.');
    string base = (pos == string::npos) ? f_name : f_name.substr(0, pos);
    string exefile = base + ".exe";
    ifstream check(exefile);
    if (!check.is_open())
    {
        cout << "[ERROR] Executable not found. Build first. " << endl;
        return;
    }
    check.close();
    cout << "Running file..." << exefile << "..." << endl;
    string command = ".\\" + exefile;
    system(command.c_str());
}
