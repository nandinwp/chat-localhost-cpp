#pragma once
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;
using namespace System::Threading;
using namespace System::Collections::Generic;

public delegate void NewConnectionEventHandler(String^ address);
public delegate void NewMessage(String^ msg);

public ref class SystemNode
{
private:
    String^ nodeName;
    UdpClient^ udpClient;
    int port;
    Thread^ receiveThread;
    Action<String^>^ onMessageReceived;
    Dictionary<String^, IPEndPoint^>^ connectedNodes;

public:
    event NewConnectionEventHandler^ OnNewConnection;
    event NewMessage^ OnNewMessage;

    SystemNode(String^ name, int portNumber, Action<String^>^ messageCallback)
    {
        nodeName = name;
        port = portNumber;
        udpClient = gcnew UdpClient(port);
        onMessageReceived = messageCallback;
        connectedNodes = gcnew Dictionary<String^, IPEndPoint^>();
    }

    int GetConnectedNodeCount()
    {
        return connectedNodes->Count;
    }

    void Start()
    {
        receiveThread = gcnew Thread(gcnew ThreadStart(this, &SystemNode::ReceiveData));
        receiveThread->ApartmentState = ApartmentState::MTA;
        receiveThread->Priority = ThreadPriority::Highest;
        receiveThread->IsBackground = true;
        receiveThread->Start();
    }

    void SendMessageTo(String^ message, String^ address, int port)
    {
        try
        {
            array<Byte>^ sendBytes = Encoding::ASCII->GetBytes(message);
            IPEndPoint^ endPoint = gcnew IPEndPoint(IPAddress::Parse(address), port);
            udpClient->Send(sendBytes, sendBytes->Length, endPoint);
            Console::WriteLine("Message sent to {0}:{1} - {2}", address, port, message);
        }
        catch (Exception^ e)
        {
            Console::WriteLine("Exception: {0}", e->Message);
        }
    }

    void BroadcastMessage(String^ message)
    {
        for each (KeyValuePair<String^, IPEndPoint^> ^ kvp in connectedNodes)
        {
            String^ ip = kvp->Value->Address->ToString();
            MessageBox::Show(ip, "IP");
            SendMessageTo(message, ip, kvp->Value->Port);
        }
    }

    void SendDiscoveryRequest()
    {
        String^ discoveryMessage = String::Format("{0} está à procura de outros nós", nodeName);
        IPEndPoint^ broadcastEndPoint = gcnew IPEndPoint(IPAddress::Broadcast, port);
        SendMessageTo(discoveryMessage, broadcastEndPoint->Address->ToString(), broadcastEndPoint->Port);
    }

    void ReceiveData()
    {
        IPEndPoint^ receiveEndPoint = gcnew IPEndPoint(IPAddress::Any, port);
        while (true)
        {
            try
            {
                array<Byte>^ receiveBytes = udpClient->Receive(receiveEndPoint);
                String^ receiveString = Encoding::ASCII->GetString(receiveBytes);

                String^ senderAddress = receiveEndPoint->Address->ToString();
                if (!connectedNodes->ContainsKey(senderAddress))
                {
                    connectedNodes->Add(senderAddress, gcnew IPEndPoint(IPAddress::Parse(senderAddress), receiveEndPoint->Port));
                    OnNewConnection(senderAddress);
                }
                OnNewMessage(receiveString);
                onMessageReceived(receiveString);
            }
            catch (Exception^ e)
            {
                Console::WriteLine("Exception: {0}", e->Message);
                break;
            }
        }
    }

    ~SystemNode()
    {
        if (receiveThread != nullptr && receiveThread->IsAlive)
        {
            receiveThread->Abort();
        }
        udpClient->Close();
    }
};
