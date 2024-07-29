#pragma once

#include <iostream>
#include <vector>
#include <sqlite3.h>

static char* db_path;

int callback(void* data, int argc, char** argv, char** azColName);
int createDatabase();
int getAllMessageFromUser(char* user);
