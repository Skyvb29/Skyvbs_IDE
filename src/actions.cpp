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
    else if (last_action.type == "edit")
    {
        size_t splitPos = last_action.content.find('\n');
        string oldLine = last_action.content.substr(0, splitPos);
        string newLine = last_action.content.substr(splitPos + 1);

        // restore OLD line
        st[last_action.index - 1] = oldLine;

        // push REDO for edit
        Action redoAct;
        redoAct.type = "edit";
        redoAct.index = last_action.index;
        redoAct.content = oldLine + "\n" + newLine;
        redoStack.push(redoAct);

        cout << BLUE << "[UNDO] Reverted edit on line " << last_action.index << RESET << endl;
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
    else if (last_action.type == "edit")
    {
        size_t pos = last_action.content.find('\n');
        string oldLine = last_action.content.substr(0, pos);
        string newLine = last_action.content.substr(pos + 1);

        st[last_action.index - 1] = newLine;

        undoStack.push(last_action);

        cout << CYAN << "[REDO] Re-applied edit on line " << last_action.index << RESET << endl;
    }

    modified = true;
}
