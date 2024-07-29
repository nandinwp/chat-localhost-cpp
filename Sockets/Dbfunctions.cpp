#include "Dbfunctions.h"

int callback(void* data, int argc, char** argv, char** azColName) {
	int i;
	std::string result;

	fprintf(stderr, "%s: ", (const char*)data);
	for (i = 0; i < argc; i++) {
		result += azColName[i] + std::string(" = ") + (argv[i] ? argv[i] : "NULL") + "\n";
	}

	return 0;
}

int createDatabase()
{
	db_path = (char*)malloc(255);
	int sizePath = strlen("Sockets.db");
	memcpy(db_path, "Sockets.db", sizePath);
	*(db_path + sizePath) = '\0';

	char* query = (char*)malloc(4096);
	strcpy(query, "PRAGMA foreign_keys = off;");
	strcat(query, "BEGIN TRANSACTION;");
	strcat(query, "CREATE TABLE IF NOT EXISTS mensagem (id VARCHAR (255) PRIMARY KEY, fase VARCHAR (255), status INTEGER, dateCreated DATETIME DEFAULT (CURRENT_TIMESTAMP), message TEXT, userId VARCHAR (255), fromId VARCHAR (255));");
	strcat(query, "COMMIT TRANSACTION;");
	strcat(query, "PRAGMA foreign_keys = on;");

	char* error = (char*)malloc(255);

	sqlite3* db;
	int result = sqlite3_open(db_path, &db);
	if (result == SQLITE_OK)
	{
		result = sqlite3_exec(db, query, callback, NULL, &error);
		if (result != SQLITE_OK)
		{
			sqlite3_close(db);
			free(error);

			return EXIT_FAILURE;
		}
	}
		free(query);
		free(error);
		sqlite3_close(db);

	return 0;
}

int getAllMessageFromUser(char* user)
{
	char* query = (char*)malloc(4096);

	strcpy(query, "SELECT * FROM mensagem");

	char* error = (char*)malloc(255);

	sqlite3* db;
	int result = sqlite3_open(db_path, &db);
	if (result == SQLITE_OK)
	{
		result = sqlite3_exec(db, query, callback, NULL, &error);
		if (result != SQLITE_OK)
		{
			sqlite3_close(db);
			free(error);

			return EXIT_FAILURE;
		}

	}
	free(query);
	free(error);
	sqlite3_close(db);

	return 0;
}
