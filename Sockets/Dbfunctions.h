#pragma once

#include <iostream>
#include <vector>
#include <sqlite3.h>
using namespace System::Windows::Forms;
using namespace System;
using namespace System::Runtime::InteropServices;

static char* db_path;

int callback(void* data, int argc, char** argv, char** azColName);
int createDatabase();
int getAllMessageFromUser(const char* user, System::Object^ formObject);
int insertMessage(const char* id, const char* fase, int status, const char* message, const char* userId, const char* fromId);
System::String^ getNameByUserId(const char* userId);
int findUserInConfig();
int insertIntoConfig(const std::string& id, const std::string& fase, int status, const std::string& dateCreated, const std::string& name, const std::string& userId, const std::string& pass);
int LoadDataToListView(ListView^% list);
int LoadFriends(ListView^% list);
int InsertAmigo(String^ fase, int status, String^ name, String^ userId, String^ conectionContex);
