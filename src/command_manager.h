#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <string>
#include <vector>
#include <stack>
#include "actions.h"
#include "file_ops.h"

using namespace std;

void handle_command(
    const string &command,
    vector<string> &storage,
    stack<Action> &undoStack,
    stack<Action> &redoStack,
    vector<string> &command_logs);

#endif
