#pragma once
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Threading::Tasks;
using namespace System::Net;
using namespace System::Net::NetworkInformation;


public ref class StaticData
{
private:
	static String^ user;
	static Int16 port=8080;
    static String^ userSend;

public:
	static property String^ Usuario 
	{
		void set(String^ val) { user = val; }
		String^ get() { return user;}
	}
    static property String^ Destinatario
    {
        void set(String^ val) { userSend = val; }
        String^ get() { return userSend; }
    }
	static property Int16 Porta
	{
		void set(Int16 val) { port = val; }
		Int16 get() { return port; }
	}

    static String^ GetLocalIPAddress()
    {
        try
        {
            String^ hostName = Dns::GetHostName();

            cli::array<IPAddress^>^ ipAddresses = Dns::GetHostAddresses(hostName);

            for each (IPAddress ^ ipAddress in ipAddresses)
            {
                if (ipAddress->AddressFamily == AddressFamily::InterNetwork && !IPAddress::IsLoopback(ipAddress))
                {
                    return ipAddress->ToString();
                }
            }
        }
        catch (Exception^ ex)
        {
            Console::WriteLine("Exception: {0}", ex->Message);
        }

        return nullptr;
    }
    static bool IsPortOpen(String^ ipAddress, int port)
    {
        try
        {
            TcpClient^ client = gcnew TcpClient();
            client->ReceiveTimeout = 1000;
            client->SendTimeout = 1000;

            client->Connect(ipAddress, port);
            client->Close();

            return true;
        }
        catch (SocketException^)
        {
            return false;
        }
    }
    static void GetLocalNetworkIPs(ComboBox^%comb)
    {
        comb->Items->Clear();
        comb->BeginUpdate();
        cli::array<NetworkInterface^>^ networkInterfaces = NetworkInterface::GetAllNetworkInterfaces();
        for each (NetworkInterface ^ ni in networkInterfaces)
        {
            IPInterfaceProperties^ ipProps = ni->GetIPProperties();
            for each (UnicastIPAddressInformation ^ ip in ipProps->UnicastAddresses)
            {
                if (ip->Address->AddressFamily == AddressFamily::InterNetwork)
                {
                    comb->Items->Add(ip->Address->ToString());
                }
            }
        }
        comb->EndUpdate();
    }
};

