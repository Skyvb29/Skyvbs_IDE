#include "display.h"
#include "colours.h"
#include <iostream>

using namespace std;
void display(const vector<string> &st)
{
    if (st.empty())
    {
        cout << RED << "[INFO] No content to view\n"
             << RESET;
        return;
    }

    for (int i = 0; i < st.size(); i++)
        cout << BLUE << i + 1 << RESET << ". " << st[i] << "\n";
}

void view_logs(const vector<string> &logs)
{
    for (int i = 0; i < logs.size(); i++)
        cout << BLUE << i + 1 << RESET << ". " << logs[i] << "\n";
}
