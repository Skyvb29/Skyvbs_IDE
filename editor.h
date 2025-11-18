#ifndef EDITOR_H
#define EDITOR_H

using namespace std;
#include <vector>
#include <string>
#include <stack>
#include "actions.h"

vector<string> add_line(vector<string> &st, stack<Action> &undoStack, stack<Action> &redoStack);
vector<string> delete_line(vector<string> &st, stack<Action> &undoStack, stack<Action> &redoStack);
void insert_line(vector<string> &st, int i, stack<Action> &undoStack, stack<Action> &redoStack);

#endif