#include "editor.h"
#include "colours.h"
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

vector<string> add_line(vector<string> &st, stack<Action> &undoStack, stack<Action> &redoStack)
{
    string data;
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.ignore();
    while (true)
    {
        getline(cin, data);
        if (data == ">>")
            break;

        st.push_back(data);

        Action act;
        act.type = "add";
        act.content = data;
        act.index = st.size();
        undoStack.push(act);
        while (!redoStack.empty())
        {
            redoStack.pop();
        }
    }

    cout << GREEN << "[+] lines added" << RESET << endl;

    modified = true;

    return st;
}
vector<string> delete_line(vector<string> &st, stack<Action> &undoStack, stack<Action> &redoStack)
{
    int d;
    if (st.empty())
    {
        cout << YELLOW << "[WARNING] Document is empty." << RESET << endl;
        return st;
    }
    if (!(cin >> d))
    {
        cout << RED << "[ERROR] Invalid input. Expected a line number." << RESET << endl;
        cin.clear();                                         // reset stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard bad input
        return st;
    }

    if (d < 1 || d > st.size())
    {
        cout << RED << "[ERROR] Invalid memory access!!" << RESET << endl;
        return st;
    }
    string deletetd_line = st[d - 1];
    st.erase(st.begin() + (d - 1));

    Action act;
    act.type = "delete";
    act.content = deletetd_line;
    act.index = d;
    undoStack.push(act);

    while (!redoStack.empty())
    {
        redoStack.pop();
    }

    cout << RED << "[-]Line " << d << " deleted." << RESET << endl;

    modified = true;

    return st;
}

void insert_line(vector<string> &st, int i, stack<Action> &undoStack, stack<Action> &redoStack)
{
    if (i <= 0 || i > st.size() + 1)
    {
        cout << RED << "[ERROR] Invalid index." << RESET;
        return;
    }
    cin.ignore();
    string text;
    getline(cin, text);

    while (!redoStack.empty())
        redoStack.pop();

    st.insert(st.begin() + (i - 1), text);
    Action act;
    act.type = "insert";
    act.content = text;
    act.index = i;

    undoStack.push(act);
    modified = true;
    cout << GREEN << "[+] Line inserted at " << i << RESET << endl;
}


void edit_line(vector<string> &st, int n, stack<Action> &undoStack, stack<Action> &redoStack)
{
    if (n < 1 || n > st.size())
    {
        cout << RED << "[ERROR] Invalid index." << RESET << endl;
        return;
    }

    cin.ignore();
    string oldLine = st[n - 1];
    string newLine;

    cout << "Current line: " << oldLine << endl;
    cout << "New line: ";
    getline(cin, newLine);

   
    st[n - 1] = newLine;

    // clear redo stack
    while (!redoStack.empty())
        redoStack.pop();

    
    Action act;
    act.type = "edit";
    act.content = oldLine + "\n" + newLine; 
    act.index = n;
    undoStack.push(act);

    modified = true;

    cout << GREEN << "[+] Line " << n << " updated." << RESET << endl;
}
