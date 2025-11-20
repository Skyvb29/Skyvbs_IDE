#include "command_manager.h"
#include "editor.h"
#include "display.h"
#include "file_ops.h"
#include "colours.h"
#include "compiler.h"
#include <iostream>
using namespace std;

void handle_command(
    const string &command,
    vector<string> &storage,
    stack<Action> &undoStack,
    stack<Action> &redoStack,
    vector<string> &command_logs)
{
    if (command == "add")
    {
        add_line(storage, undoStack, redoStack);
    }
    else if (command == "view")
    {
        display(storage);
    }
    else if (command == "delete")
    {
        delete_line(storage, undoStack, redoStack);
    }
    else if (command == "help")
    {
        cout << BOLD << GREY << "try--> add, delete, view, save, load, clear, undo, redo, build, run, rename, remove, exit." << RESET << endl;
    }
    else if (command == "undo")
    {
        undo_line(storage, undoStack, redoStack);
    }
    else if (command == "redo")
    {
        redo_line(storage, undoStack, redoStack);
    }

    else if (command == "clear")
    {
        system("cls");
    }
    else if (command == "save")
    {
        string file_name;
        cin >> file_name;
        cin.ignore();

        save_file(storage, file_name);
        save_logs(command_logs, file_name);
        command_logs.clear();
    }
    else if (command == "load")
    {
        string file_name;
        cin >> file_name;
        load_function(storage, file_name);
        command_logs.clear();
    }
    else if (command == "logs")
    {
        view_logs(command_logs);
    }
    else if (command == "insert")
    {
        int in;
        cin >> in;
        insert_line(storage, in, undoStack, redoStack);
    }
    else if (command == "rename")
    {
        string old_name, new_name;
        cin >> old_name >> new_name;

        rename_file(storage, old_name, new_name);
    }
    else if (command == "remove")
    {
        string file_name;
        cin >> file_name;
        delete_file(storage, file_name);
    }
    else if (command == "build")
    {
        string file_name;
        cin >> file_name;
        build_file(file_name);
    }
    else if (command == "run")
    {
        string file_name;
        cin >> file_name;
        run_file(file_name);
    }

    else
    {
        cout << RED << "[ERROR] Invalid command: " << command << RESET << endl;
    }
}
