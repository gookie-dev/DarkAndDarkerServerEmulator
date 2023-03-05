#include <winsock2.h>
#include "server.h"
#include "include/httplib.h"

#pragma comment (lib, "Ws2_32.lib")

httplib::Server web_server_instance;
int web_port = 0;
int tcp_port = 0;


void yeet(string msg)
{
	MessageBoxA(NULL, msg.c_str(), "Server Emulator Error", MB_ICONERROR);
	ExitProcess(0x1337);
}

void web_server_thread()
{
	web_server_instance.listen_after_bind();
}

void web_server_init()
{
	web_port = web_server_instance.bind_to_any_port("0.0.0.0");

	if (web_port == -1)
	{
		auto last_error = GetLastError();
		yeet(string("Failed to host local server.\nError code: ") + to_string(last_error));
	}
	else
	{
		web_server_instance.Get("/dc/helloWorld", [&](const httplib::Request& req, httplib::Response& res)
			{
				res.set_content(string("{\"ipAddress\": \"127.0.0.1\", \"port\": " + to_string(tcp_port) + "}"), "application/json");
			}
		);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)web_server_thread, NULL, NULL, NULL);
	}
}

void game_thread()
{
	string arg_str = " -server=127.0.0.1:" + to_string(web_port);
	int arg_size = MultiByteToWideChar(CP_UTF8, 0, arg_str.c_str(), -1, NULL, 0);
	LPWSTR arg_lpw = new WCHAR[arg_size];
	MultiByteToWideChar(CP_UTF8, 0, arg_str.c_str(), -1, arg_lpw, arg_size);

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	HANDLE job = CreateJobObject(NULL, NULL);
	JOBOBJECT_EXTENDED_LIMIT_INFORMATION jeli = { 0 };
	jeli.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
	SetInformationJobObject(job, JobObjectExtendedLimitInformation, &jeli, sizeof(jeli));

	if (!CreateProcessW(
		L".\\DungeonCrawler.exe",
		arg_lpw,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi)
		)
	{
		yeet(string("CreateProcess failed ") + to_string(GetLastError()) + string("."));
	}
	else
	{
		if (!AssignProcessToJobObject(job, pi.hProcess)) {
			TerminateProcess(pi.hProcess, 1);
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			CloseHandle(job);
			string msg = (string("Error assigning process to job object: ") + to_string(GetLastError()));
			MessageBoxA(NULL, msg.c_str(), "Server Emulator Error", MB_ICONERROR);
		}

		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		CloseHandle(job);
		ExitProcess(0x1337);
	}

}

void game_init()
{
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)game_thread, NULL, NULL, NULL);
}

void tcp_server_thread()
{
	WSADATA wsaData;
	SOCKET ListenSocket, ClientSocket;
	sockaddr_in addrServer;
	int port = 29122;
	int iSendResult;
	char buffer[4096];

	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
		yeet(string("WSAStartup failed with error: ") + to_string(iResult));

	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET)
		yeet(string("Socket failed with error: ") + to_string(WSAGetLastError()));

	while (true)
	{
		addrServer.sin_family = AF_INET;
		InetPton(AF_INET, L"127.0.0.1", &addrServer.sin_addr.s_addr);
		port = port++;
		addrServer.sin_port = htons(port);
		memset(&(addrServer.sin_zero), '\0', 8);

		if (::bind(ListenSocket, (SOCKADDR*)&addrServer, sizeof(addrServer)) != SOCKET_ERROR)
		{
			tcp_port = port;
			break;
		}
	}

	if (listen(ListenSocket, 5) == SOCKET_ERROR)
		yeet(string("Listen failed with error: ") + to_string(WSAGetLastError()));

	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET)
		yeet(string("Accept failed with error: ") + to_string(WSAGetLastError()));

	closesocket(ListenSocket);

	while (true)
	{
		iResult = recv(ClientSocket, buffer, 4096, 0);
		if (iResult <= 0)
		{
			break;
		}

		int response_length = server_response(buffer, iResult);

		iSendResult = send(ClientSocket, buffer, response_length, 0);
		if (iSendResult == SOCKET_ERROR)
			yeet(string("Send failed with error: ") + to_string(WSAGetLastError()));
	}

	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
		yeet(string("Send failed with error: ") + to_string(WSAGetLastError()));

	closesocket(ClientSocket);
	WSACleanup();
}

void tcp_server_init()
{
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)tcp_server_thread, NULL, NULL, NULL);
}

int main()
{
	cout << " _____             _                      _   _____             _               " << endl;
	cout << "|  __ \\           | |                    | | |  __ \\           | |              " << endl;
	cout << "| |  | | __ _ _ __| | __   __ _ _ __   __| | | |  | | __ _ _ __| | _____ _ __   " << endl;
	cout << "| |  | |/ _` | '__| |/ /  / _` | '_ \\ / _` | | |  | |/ _` | '__| |/ / _ \\ '__|  " << endl;
	cout << "| |__| | (_| | |  |   <  | (_| | | | | (_| | | |__| | (_| | |  |   <  __/ |     " << endl;
	cout << "|_____/ \\__,_|_|  |_|\\_\\  \\__,_|_| |_|\\__,_| |_____/ \\__,_|_|  |_|\\_\\___|_|     " << endl;
	cout << " / ____|                          |  ____|               | |     | |            " << endl;
	cout << "| (___   ___ _ ____   _____ _ __  | |__   _ __ ___  _   _| | __ _| |_ ___  _ __ " << endl;
	cout << " \\___ \\ / _ \\ '__\\ \\ / / _ \\ '__| |  __| | '_ ` _ \\| | | | |/ _` | __/ _ \\| '__|" << endl;
	cout << " ____) |  __/ |   \\ V /  __/ |    | |____| | | | | | |_| | | (_| | || (_) | |   " << endl;
	cout << "|_____/ \\___|_|    \\_/ \\___|_|    |______|_| |_| |_|\\__,_|_|\\__,_|\\__\\___/|_|   " << endl << endl;
	cout << "                                    by gookie" << endl << endl;
	tcp_server_init();
	web_server_init();
	game_init();
	this_thread::sleep_for(24h);
	cout << "go touch some grass" << std::endl;
}