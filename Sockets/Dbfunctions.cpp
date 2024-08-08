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
	strcat(query, "CREATE TABLE IF NOT EXISTS mensagem (id VARCHAR (255) PRIMARY KEY, fase VARCHAR (255), status INTEGER, dateCreated DATETIME DEFAULT (CURRENT_TIMESTAMP), message TEXT, userId VARCHAR (255), fromId VARCHAR (255), chatId VARCHAR (255));");
	strcat(query, "CREATE TABLE IF NOT EXISTS amigos (id VARCHAR (255) PRIMARY KEY, fase VARCHAR (255), status INTEGER, dateCreated DATETIME DEFAULT (CURRENT_TIMESTAMP), name VARCHAR(50),conectionContex VARCHAR(255),userId VARCHAR (255));");
	strcat(query, "CREATE TABLE IF NOT EXISTS config (id VARCHAR (255) PRIMARY KEY, fase VARCHAR (255), status INTEGER, dateCreated DATETIME DEFAULT (CURRENT_TIMESTAMP), name VARCHAR(50), userId VARCHAR (255), pass VARCHAR(255));");
	strcat(query, "CREATE TABLE IF NOT EXISTS chat (id VARCHAR (255) PRIMARY KEY, fase VARCHAR (255), status INTEGER, dateCreated DATETIME DEFAULT (CURRENT_TIMESTAMP), chatName VARCHAR(50), userId VARCHAR (255), fromId VARCHAR(255));");
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
			free(query);
			free(error);

			return EXIT_FAILURE;
		}
	}
		free(query);
		free(error);
		sqlite3_close(db);

	return 0;
}

int getAllMessageFromUser(const char* user, System::Object^ formObject) {

	System::Windows::Forms::Form^ main = (System::Windows::Forms::Form^)formObject;

	System::Windows::Forms::ListBox^ mensagens = (System::Windows::Forms::ListBox^)main->Controls->Find("messageListBox", true)[0];

	char* query = (char*)malloc(4096);
	if (!query) {
		perror("Failed to allocate memory");
		return EXIT_FAILURE;
	}

	snprintf(query, 4096,
		"SELECT "
		"m.dateCreated, "
		"m.message, "
		"m.userId AS senderId, "
		"CASE "
		"WHEN m.userId = c.userId THEN c.name "
		"ELSE am.name "
		"END AS senderName, "
		"m.fromId AS receiverId, "
		"am.name AS receiverName, "
		"m.chatId, "
		"ch.chatName "
		"FROM mensagem m "
		"JOIN config c ON c.userId = m.userId "
		"LEFT JOIN amigos am ON am.userId = m.fromId "
		"LEFT JOIN chat ch ON ch.id = m.chatId "
		"WHERE m.userId = ? OR m.fromId = ? "
		"ORDER BY m.dateCreated ASC;",
		user, user);

	char* error = (char*)malloc(255);
	if (!error) {
		perror("Failed to allocate memory");
		free(query);
		return EXIT_FAILURE;
	}

	sqlite3* db;
	sqlite3_stmt* stmt;
	int result = sqlite3_open(db_path, &db);
	if (result == SQLITE_OK) {
		result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
		if (result != SQLITE_OK) {
			fprintf(stderr, "Failed to fetch statement: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			free(query);
			free(error);
			return EXIT_FAILURE;
		}

		// Bind parameters to the query
		sqlite3_bind_text(stmt, 1, user, -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, user, -1, SQLITE_STATIC);

		while ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
			const unsigned char* date = sqlite3_column_text(stmt, 0);
			const unsigned char* message = sqlite3_column_text(stmt, 1);
			const unsigned char* senderName = sqlite3_column_text(stmt, 3);
			const unsigned char* receiverName = sqlite3_column_text(stmt, 5);
			//const unsigned char* chatName = sqlite3_column_text(stmt, 6);

			System::String^ messageStr = nullptr;

			if (strcmp((const char*)receiverName, (const char*)senderName) == 0) 
			{
				strcpy((char*)senderName, "Você");
			}
			else {
				strcpy((char*)senderName,(char*)receiverName);
			}
			if (date && message) {
				messageStr = System::String::Format("{0} - {1}: {2}",
					gcnew System::String(reinterpret_cast<const char*>(date)),
					gcnew System::String(reinterpret_cast<const char*>(senderName)),
					gcnew System::String(reinterpret_cast<const char*>(message)));
				mensagens->Items->Add(messageStr);
			}
		}

		if (result != SQLITE_DONE) {
			fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			free(query);
			free(error);
			return EXIT_FAILURE;
		}

		sqlite3_finalize(stmt);
	}
	else {
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
		free(query);
		free(error);
		return EXIT_FAILURE;
	}

	free(query);
	free(error);
	sqlite3_close(db);

	return 0;
}

int insertMessage(const char* id, const char* fase, int status, const char* message, const char* userId, const char* fromId)
{
	sqlite3* db;
	sqlite3_stmt* stmt;
	char* sql = "INSERT INTO mensagem (id, fase, status, message, userId, fromId) VALUES (?, ?, ?, ?, ?, ?);";

	int result = sqlite3_open(db_path, &db);
	if (result != SQLITE_OK)
	{
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
		return EXIT_FAILURE;
	}

	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK)
	{
		fprintf(stderr, "Failed to fetch SQLite statement: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return EXIT_FAILURE;
	}

	sqlite3_bind_text(stmt, 1, id, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, fase, -1, SQLITE_STATIC);
	sqlite3_bind_int(stmt, 3, status);
	sqlite3_bind_text(stmt, 4, message, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 5, userId, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 6, fromId, -1, SQLITE_STATIC);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE)
	{
		fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return EXIT_FAILURE;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}

System::String^ getNameByUserId(const char* userId) {
	sqlite3* db;
	sqlite3_stmt* stmt;
	char* query = "SELECT name FROM amigos WHERE userId = ?;";
	char* error = nullptr;
	System::String^ name = nullptr;

	int result = sqlite3_open(db_path, &db);
	if (result != SQLITE_OK) {
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
		return nullptr;
	}

	result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		fprintf(stderr, "Failed to fetch statement: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return nullptr;
	}

	sqlite3_bind_text(stmt, 1, userId, -1, SQLITE_STATIC);

	if (sqlite3_step(stmt) == SQLITE_ROW) {
		const unsigned char* nameText = sqlite3_column_text(stmt, 0);
		if (nameText) {
			name = gcnew System::String(reinterpret_cast<const char*>(nameText));
		}
	}

	if (sqlite3_errmsg(db)) {
		fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return name;
}

int findUserInConfig() {
	sqlite3* db;
	sqlite3_stmt* stmt;
	int result;

	const char* query = "SELECT * FROM config";

	result = sqlite3_open(db_path, &db);
	if (result != SQLITE_OK) {
		std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
		return EXIT_FAILURE;
	}

	result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		std::cerr << "Failed to fetch statement: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return EXIT_FAILURE;
	}

	if (sqlite3_step(stmt) == SQLITE_ROW) {
		std::cout << "User found in config table." << std::endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return EXIT_SUCCESS;
	}
	else {
		std::cout << "User not found in config table." << std::endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return EXIT_FAILURE;
	}
}

int insertIntoConfig(const std::string& id, const std::string& fase, int status, const std::string& dateCreated, const std::string& name, const std::string& userId, const std::string& pass) {
	sqlite3* db;
	sqlite3_stmt* stmt;
	int result;

	const char* query = "INSERT INTO config (id, fase, status, dateCreated, name, userId, pass) VALUES (?, ?, ?, ?, ?, ?, ?)";

	result = sqlite3_open(db_path, &db);
	if (result != SQLITE_OK) {
		std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
		return EXIT_FAILURE;
	}

	result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return EXIT_FAILURE;
	}

	sqlite3_bind_text(stmt, 1, id.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, fase.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 3, status);
	sqlite3_bind_text(stmt, 4, dateCreated.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 5, name.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 6, userId.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 7, pass.c_str(), -1, SQLITE_TRANSIENT);

	result = sqlite3_step(stmt);
	if (result == SQLITE_DONE) {
		std::cout << "Data inserted successfully into config table." << std::endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return EXIT_SUCCESS;
	}
	else {
		std::cerr << "Failed to insert data: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return EXIT_FAILURE;
	}
}

int LoadDataToListView(ListView^% list) 
{
	sqlite3* db;
	sqlite3_stmt* stmt;
	int result;

	const char* query = "SELECT * FROM config";

	result = sqlite3_open(db_path, &db);
	if (result != SQLITE_OK) {
		MessageBox::Show("Cannot open database: " + gcnew String(sqlite3_errmsg(db)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return EXIT_FAILURE;
	}

	result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		MessageBox::Show("Failed to fetch statement: " + gcnew String(sqlite3_errmsg(db)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		sqlite3_close(db);
		return EXIT_FAILURE;
	}

	list->Items->Clear();

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		ListViewItem^ item = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(1) { gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4))) }, -1));
		item->SubItems->Add(gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6))));
		item->SubItems->Add(gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5))));

		list->Items->Add(item);
	}

	if (sqlite3_finalize(stmt) != SQLITE_OK) {
		MessageBox::Show("Failed to finalize statement: " + gcnew String(sqlite3_errmsg(db)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}

	sqlite3_close(db);
	return EXIT_SUCCESS;
}

int LoadFriends(ListView^% list)
{
	sqlite3* db;
	sqlite3_stmt* stmt;
	int result;

	const char* query = "SELECT * FROM amigos";

	result = sqlite3_open(db_path, &db);
	if (result != SQLITE_OK) {
		MessageBox::Show("Cannot open database: " + gcnew String(sqlite3_errmsg(db)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return EXIT_FAILURE;
	}

	result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		MessageBox::Show("Failed to fetch statement: " + gcnew String(sqlite3_errmsg(db)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		sqlite3_close(db);
		return EXIT_FAILURE;
	}

	list->Items->Clear();

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		ListViewItem^ item = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(1) { gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4))) }, -1));
		item->SubItems->Add(gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6))));
		item->SubItems->Add(gcnew String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5))));

		list->Items->Add(item);
	}

	if (sqlite3_finalize(stmt) != SQLITE_OK) {
		MessageBox::Show("Failed to finalize statement: " + gcnew String(sqlite3_errmsg(db)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}

	sqlite3_close(db);
	return EXIT_SUCCESS;
}

int InsertAmigo(String^ fase, int status, String^ name, String^ userId, String^ conectionContex)
{
	String^ id = userId;
	sqlite3* db;
	sqlite3_stmt* stmt;
	int result;

	const char* query = "INSERT INTO amigos (id, fase, status, dateCreated, name, userId, conectionContex) VALUES (?, ?, ?, CURRENT_TIMESTAMP, ?, ?, ?)";

	result = sqlite3_open(db_path, &db);
	if (result != SQLITE_OK)
	{
		Console::WriteLine("Cannot open database: {0}", gcnew String(sqlite3_errmsg(db)));
		return EXIT_FAILURE;
	}

	result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
	if (result != SQLITE_OK)
	{
		Console::WriteLine("Failed to prepare statement: {0}", gcnew String(sqlite3_errmsg(db)));
		sqlite3_close(db);
		return EXIT_FAILURE;
	}

	// Bind the parameters to the SQL statement
	sqlite3_bind_text(stmt, 1, (char*)(void*)Marshal::StringToHGlobalAnsi(id), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, (char*)(void*)Marshal::StringToHGlobalAnsi(fase), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 3, status);
	sqlite3_bind_text(stmt, 4, (char*)(void*)Marshal::StringToHGlobalAnsi(name), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 5, (char*)(void*)Marshal::StringToHGlobalAnsi(userId), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 6, (char*)(void*)Marshal::StringToHGlobalAnsi(conectionContex), -1, SQLITE_TRANSIENT);

	result = sqlite3_step(stmt);
	if (result == SQLITE_DONE)
	{
		Console::WriteLine("Data inserted successfully into amigos table.");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return EXIT_SUCCESS;
	}
	else
	{
		Console::WriteLine("Failed to insert data: {0}", gcnew String(sqlite3_errmsg(db)));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return EXIT_FAILURE;
	}
}
