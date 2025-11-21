#include "file_ops.h"
#include "actions.h"
#include "colours.h"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>

using namespace std;

string current_file = "";

void save_file(vector<string> &st, string f_name)
{
    if (f_name.empty())
    {
        cout << CYAN << "[INFO] add file name" << RESET << endl;
        return;
    }
    ifstream check(f_name);
    if (check.is_open())
    {
        cout << YELLOW << "[WARNING] file' " << f_name << " already  exists. Overwrite(y/n)? " << RESET;
        char choice;
        cin >> choice;
        if (choice != 'y')
        {
            cout << CYAN << "[INFO] save operation cancelled." << RESET << endl;
            return;
        }
    }
    check.close();

    ofstream file(f_name);
    if (!file)
    {
        cout << RED << "[ERROR] could not open file" << RESET << endl;
        return;
    }
    for (auto text : st)
    {
        file << text << endl;
    }
    file.close();
    cout << CYAN << "[INFO] file " << f_name << " saved." << RESET << endl;

    modified = false;
}

void load_function(vector<string> &st, string f_name)
{

    if (f_name.empty())
    {
        cout << CYAN << "[INFO] add file name ." << RESET << endl;
        return;
    }
    ifstream file(f_name);
    if (!file.is_open())
    {
        cout << RED << "[ERROR] File not found !." << RESET << endl;
        return;
    }
    st.clear();
    string line;
    while (getline(file, line))
    {
        st.push_back(line);
    }
    file.close();
    current_file = f_name;
    cout << CYAN << "[INFO] file " << f_name << " loaded." << RESET << endl;

    modified = false;
}

void rename_file(vector<string> &st, string old_name, string new_name)
{
    if (old_name == new_name)
    {
        cout << CYAN << "[INFO] File name are identical. No action taken." << RESET << endl;
        return;
    }

    ifstream check(old_name);
    if (!check)
    {
        char ch;
        cout << RED << "[ERROR] File " << old_name << " Missing : " << RESET << endl
             << "To create file (y/n) : ";
        cin >> ch;
        if (ch == 'y')
        {
            save_file(st, old_name);
        }
        else
        {
            cout << CYAN << "[INFO] Rename cancelled" << RESET << endl;
        }
        return;
    }
    check.close();

    ifstream check_new(new_name);
    if (check_new)
    {
        cout << YELLOW "[WARNING] File " << new_name << " already exists. Overwrite? (y/n): " << RESET;
        char ch;
        cin >> ch;
        if (ch != 'y')
        {
            check_new.close();
            cout << CYAN << "[INFO] Rename cancelled." << RESET << endl;
            return;
        }
    }

    check_new.close();

    int result = rename(old_name.c_str(), new_name.c_str());
    if (result == 0)
        cout << GREEN << "[MESSAGE] Rename successful " << RESET << endl;
    else
        cout << RED << "[ERROR] Rename failed." << RESET << endl;
}

void delete_file(vector<string> &st, string f_name)
{
    if (f_name.empty())
    {
        cout << RED << "[ERROR] No file name provided." << RESET << endl;
        return;
    }

    int result = remove(f_name.c_str());
    if (result == 0)
        cout << CYAN << "[INFO] File '" << f_name << "' removed successfully." << RESET << endl;
    else
        cout << RED << "[ERROR] Failed to remove file '" << f_name << "'. It may not exist." << RESET << endl;
}
void save_logs(vector<string> &logs, const string &orignal_file)
{
    string log_file = "log_" + orignal_file + ".log";

    ofstream file(log_file);
    if (!file)
    {
        cout << RED << "[ERROR] Could not save logs! " << RESET << endl;
        return;
    }
    file << "Command Log for file: " << orignal_file << endl
         << endl;
    int i = 1;
    for (const auto &l : logs)
    {
        file << i++ << ". " << l << endl;
    }
    file.close();
    cout << CYAN << "[INFO] Logs saved to: " << log_file << RESET << endl;
}
void view_logs(vector<string> &logs)
{
    int i = 1;
    for (auto &l : logs)
    {
        cout << i++ << ". " << l << endl;
    }
}
