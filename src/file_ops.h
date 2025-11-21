#ifndef FILE_OPS_H
#define FILE_OPS_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>

#include "actions.h"

using namespace std;

void save_file(vector<string> &st, string f_name);
void load_function(vector<string> &st, string f_name);
void rename_file(vector<string> &st, string old_name, string new_name);
void delete_file(vector<string> &st, string f_name);

void view_logs(vector<string> &logs);
void save_logs(vector<string> &logs, const string &original_file);

#endif
