#pragma once
#include <iostream>
#include <string>

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Security::Cryptography;
using namespace System::Runtime::InteropServices;

public ref class Secure
{
public:
    static array<Byte>^ EncryptMessage(String^ plainText)
    {
        String^ key = "cHV0YXF1ZW9wYXJpdU1ldVBhdU1ldU92";
        String^ iv = "cHV0YXF1ZW9wYXJp";

        array<Byte>^ keyBytes = Encoding::UTF8->GetBytes(key);
        array<Byte>^ ivBytes = Encoding::UTF8->GetBytes(iv);

        if (keyBytes->Length != 32 || ivBytes->Length != 16)
        {
            throw gcnew ArgumentException("Key or IV size is incorrect.");
        }

        Aes^ aes = Aes::Create();
        aes->Key = keyBytes;
        aes->IV = ivBytes;

        ICryptoTransform^ encryptor = aes->CreateEncryptor();
        array<Byte>^ plainTextBytes = Encoding::UTF8->GetBytes(plainText);
        array<Byte>^ cipherTextBytes;

        try
        {
           MemoryStream^ ms = gcnew MemoryStream();
            
           CryptoStream^ cs = gcnew CryptoStream(ms, encryptor, CryptoStreamMode::Write);
               
           cs->Write(plainTextBytes, 0, plainTextBytes->Length);
           cs->FlushFinalBlock();
           cipherTextBytes = ms->ToArray();      
           
        }
        catch (CryptographicException^ e)
        {
            Console::WriteLine("Error during encryption: {0}", e->Message);
            return nullptr;
        }

        return cipherTextBytes;
    }

    static String^ DecryptMessage(array<Byte>^ cipherTextBytes)
    {
        String^ key = "cHV0YXF1ZW9wYXJpdU1ldVBhdU1ldU92";
        String^ iv = "cHV0YXF1ZW9wYXJp";

        array<Byte>^ keyBytes = Encoding::UTF8->GetBytes(key);
        array<Byte>^ ivBytes = Encoding::UTF8->GetBytes(iv);

        if (keyBytes->Length != 32 || ivBytes->Length != 16)
        {
            throw gcnew ArgumentException("Key or IV size is incorrect.");
        }

        Aes^ aes = Aes::Create();
        aes->Key = keyBytes;
        aes->IV = ivBytes;

        ICryptoTransform^ decryptor = aes->CreateDecryptor();
        array<Byte>^ plainTextBytes;

        try
        {
            MemoryStream^ ms = gcnew MemoryStream(cipherTextBytes);

            CryptoStream^ cs = gcnew CryptoStream(ms, decryptor, CryptoStreamMode::Read);
            plainTextBytes = gcnew array<Byte>(cipherTextBytes->Length);
            int decryptedByteCount = cs->Read(plainTextBytes, 0, plainTextBytes->Length);
            Array::Resize(plainTextBytes, decryptedByteCount);

        }
        catch (CryptographicException^ e)
        {
            Console::WriteLine("Error during decryption: {0}", e->Message);
            return nullptr;
        }

        return Encoding::UTF8->GetString(plainTextBytes);
    }
};

