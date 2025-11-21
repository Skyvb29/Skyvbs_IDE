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
        cout << CYAN << "[INFO] Enter a file name." << RESET << endl;
        return;
    }

    string fullpath = "user/" + f_name;

    ifstream check(fullpath);
    if (check.is_open())
    {
        cout << YELLOW << "[WARNING] File '" << f_name << "' already exists. Overwrite? (y/n): " << RESET;
        char choice;
        cin >> choice;
        if (choice != 'y')
        {
            cout << CYAN << "[INFO] Save cancelled." << RESET << endl;
            return;
        }
    }
    check.close();

    ofstream file(fullpath);
    if (!file)
    {
        cout << RED << "[ERROR] Could not write file!" << RESET << endl;
        return;
    }

    for (auto &line : st)
        file << line << endl;

    file.close();
    cout << GREEN << "[INFO] Saved successfully as " << f_name << RESET << endl;

    modified = false;
}


void load_function(vector<string> &st, string f_name)
{
    if (f_name.empty())
    {
        cout << CYAN << "[INFO] Enter a file name." << RESET << endl;
        return;
    }

    string fullpath = "user/" + f_name;
    ifstream file(fullpath);

    if (!file.is_open())
    {
        cout << RED << "[ERROR] File not found in user/: " << f_name << RESET << endl;
        return;
    }

    st.clear();
    string line;

    while (getline(file, line))
        st.push_back(line);

    file.close();
    current_file = f_name;

    cout << GREEN << "[INFO] Loaded " << f_name << RESET << endl;
    modified = false;
}

void rename_file(vector<string> &st, string old_name, string new_name)
{
    if (old_name == new_name)
    {
        cout << CYAN << "[INFO] Old and new names are the same." << RESET << endl;
        return;
    }

    string oldpath = "user/" + old_name;
    string newpath = "user/" + new_name;

    ifstream check(oldpath);
    if (!check.is_open())
    {
        cout << RED << "[ERROR] File does not exist: " << old_name << RESET << endl;
        return;
    }
    check.close();

    ifstream check2(newpath);
    if (check2.is_open())
    {
        cout << YELLOW << "[WARNING] " << new_name << " already exists. Overwrite? (y/n): " << RESET;
        char ch;
        cin >> ch;
        if (ch != 'y')
        {
            cout << CYAN << "[INFO] Rename cancelled." << RESET << endl;
            return;
        }
    }
    check2.close();

    if (rename(oldpath.c_str(), newpath.c_str()) == 0)
        cout << GREEN << "[INFO] Rename successful." << RESET << endl;
    else
        cout << RED << "[ERROR] Rename failed!" << RESET << endl;
}

void delete_file(vector<string> &st, string f_name)
{
    if (f_name.empty())
    {
        cout << RED << "[ERROR] Enter a file name." << RESET << endl;
        return;
    }

    string fullpath = "user/" + f_name;

    if (remove(fullpath.c_str()) == 0)
        cout << GREEN << "[INFO] File removed: " << f_name << RESET << endl;
    else
        cout << RED << "[ERROR] Could not remove file." << RESET << endl;
}

void save_logs(vector<string> &logs, const string &file)
{
    string log_file = "user/log_" + file + ".log";

    ofstream out(log_file);
    if (!out)
    {
        cout << RED << "[ERROR] Failed to save logs!" << RESET << endl;
        return;
    }

    int i = 1;
    for (auto &l : logs)
        out << i++ << ". " << l << endl;

    out.close();
    cout << CYAN << "[INFO] Logs written to " << log_file << RESET << endl;
}

void view_logs(vector<string> &logs)
{
    int i = 1;
    for (auto &l : logs)
        cout << CYAN << i++ << ". " << l << RESET << endl;
}
