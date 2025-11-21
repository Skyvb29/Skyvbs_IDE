#ifndef ACTIONS_H
#define ACTIONS_H

#include <string>
#include <vector>
#include <stack>

using namespace std;

extern bool modified;
extern string current_file;


struct Action
{
    string type;
    string content;
    int index;
};

// Function declarations
void undo_line(vector<string> &st, stack<Action> &undoStack, stack<Action> &redoStack);

void redo_line(vector<string> &st, stack<Action> &undoStack, stack<Action> &redoStack);

#endif
