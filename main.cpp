#include <iostream>
#include <vector>
#include <stack>
#include "actions.h"
#include "colours.h"
#include "command_manager.h"
#include "file_ops.h"

using namespace std;

int main()
{
    vector<string> storage;
    stack<Action> undoStack, redoStack;
    vector<string> command_logs;
    string command;

    cout << endl
         << BOLD << BLUE << "\t\t\t---- SKYVB'S IDE ----" << RESET << endl;
    cout << YELLOW << "Commands: add, delete [i], view, save, load, clear, undo, redo, "
         << "insert [i], logs, rename, remove, help, exit" << RESET << endl
         << "--------------------------------------------------------------" << endl;

    while (true)
    {
        cout << GREY << ">> " << RESET;
        

        cin >> command;
        command_logs.push_back(command);

        if (command == "exit" || command == "EXIT")
        {
            if (modified)
            {
                cout << YELLOW << "[WARNING] Unsaved changes. Save before exit? (y/n): " << RESET;
                char choice;
                cin >> choice;

                if (choice == 'y' || choice == 'Y')
                {
                    string file_name;
                    cout << "Enter file name: ";
                    cin >> file_name;
                    save_file(storage, file_name);
                }
            }
            break;
        }

        handle_command(command, storage, undoStack, redoStack, command_logs);
    }

    return 0;
}
