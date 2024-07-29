#pragma once
#include "StaticData.h"
#include "Dbfunctions.h"

public ref class StaticFunctions
{
public:
	static int validation() {
		if (String::IsNullOrEmpty(StaticData::Usuario))
			return-1;

		if (String::IsNullOrEmpty(StaticData::Destinatario))
			return-1;

		String^ aux = StaticData::Porta.ToString();

		if (String::IsNullOrEmpty(aux) || aux->Equals("0") || aux->Length < 4)
			return-1;

		StaticData::Usuario = StaticData::Usuario->Replace(" ", "");
		StaticData::Usuario = StaticData::Usuario->ToLower();
		StaticData::Usuario = StaticData::Usuario->Trim();
		return 0;
	}
	static String^ StringToBase64(String^ base) {
		cli::array<Byte>^ bytes = Encoding::UTF8->GetBytes(base);
		String^ base64String = Convert::ToBase64String(bytes);
		return base64String;
	}
	static String^ Base64ToString(String^ base64) {
		cli::array<Byte>^ bytes = Convert::FromBase64String(base64);
		return Encoding::UTF8->GetString(bytes);
	}

	static int CreateDataBase() 
	{
		int resp = createDatabase();
		getAllMessageFromUser("");
		return resp;
	}
};

