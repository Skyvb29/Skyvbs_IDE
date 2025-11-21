#include "actions.h"
#include "colours.h"
#include <iostream>
using namespace std;

bool modified = false; // same global as before

void undo_line(vector<string> &st, stack<Action> &undoStack, stack<Action> &redoStack)
{
    if (undoStack.empty())
    {
        cout << CYAN << "[INFO] nothing to undo" << RESET << endl;
        return;
    }

    Action last_action = undoStack.top();
    undoStack.pop();

    if (last_action.type == "add" || last_action.type == "insert")
    {
        // undo = remove the line
        if (last_action.index >= 1 && last_action.index <= st.size())
        {
            st.erase(st.begin() + (last_action.index - 1));
            cout << BLUE << "[UNDO] Removed line: " << last_action.content << RESET << endl;
        }
        else
        {
            cout << YELLOW << "[WARNING] Undo failed: index out of range." << RESET << endl;
        }

        redoStack.push(last_action);
    }
    else if (last_action.type == "delete")
    {
        // undo delete = restore at same index
        int pos = last_action.index - 1;
        if (pos < 0)
            pos = 0;
        if (pos > st.size())
            pos = st.size();

        st.insert(st.begin() + pos, last_action.content);
        cout << BLUE << "[UNDO] Restored deleted line: " << last_action.content << RESET << endl;

        redoStack.push(last_action);
    }

    modified = true;
}

void redo_line(vector<string> &st, stack<Action> &undoStack, stack<Action> &redoStack)
{
    if (redoStack.empty())
    {
        cout << CYAN << "[INFO] Nothing to redo." << RESET << endl;
        return;
    }

    Action last_action = redoStack.top();
    redoStack.pop();

    if (last_action.type == "add" || last_action.type == "insert")
    {
        int pos = last_action.index - 1;
        if (pos < 0)
            pos = 0;
        if (pos > st.size())
            pos = st.size();

        st.insert(st.begin() + pos, last_action.content);
        cout << CYAN << "[REDO] Re-inserted line: " << last_action.content << RESET << endl;

        undoStack.push(last_action);
    }
    else if (last_action.type == "delete")
    {
        if (last_action.index >= 1 && last_action.index <= st.size())
        {
            st.erase(st.begin() + (last_action.index - 1));
            cout << CYAN << "[REDO] Re-deleted line: " << last_action.content << RESET << endl;
        }
        else
        {
            cout << YELLOW << "[WARNING] Redo delete failed: index out of range." << RESET << endl;
        }

        undoStack.push(last_action);
    }

    modified = true;
}
