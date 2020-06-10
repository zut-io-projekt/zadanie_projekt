#pragma once
#include <iostream>
#include <windows.h>
#include <vector>



class IPC
{
public:
	IPC()
	{

	}
	static std::string getStockfishMove()
	{
        HANDLE g_hChildStd_IN_Rd = NULL;
        HANDLE g_hChildStd_IN_Wr = NULL;
        HANDLE g_hChildStd_OUT_Rd = NULL;
        HANDLE g_hChildStd_OUT_Wr = NULL;

        std::string result;
        SECURITY_ATTRIBUTES saAttr;
        saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
        saAttr.bInheritHandle = TRUE;
        saAttr.lpSecurityDescriptor = NULL;

        STARTUPINFOA lpStartupInfo = { sizeof(STARTUPINFOA),NULL, };
        lpStartupInfo.dwFlags = STARTF_USESTDHANDLES;
        ZeroMemory(&lpStartupInfo, sizeof(lpStartupInfo));
        lpStartupInfo.cb = sizeof(lpStartupInfo);

        if (CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &saAttr, 0))
            if (CreatePipe(&g_hChildStd_IN_Rd, &g_hChildStd_IN_Wr, &saAttr, 0))

                ZeroMemory(&lpStartupInfo, sizeof(STARTUPINFO));
        lpStartupInfo.cb = sizeof(STARTUPINFO);
        //lpStartupInfo.hStdError = g_hChildStd_OUT_Wr;
        lpStartupInfo.hStdOutput = g_hChildStd_OUT_Wr;
        lpStartupInfo.hStdInput = g_hChildStd_IN_Rd;
        lpStartupInfo.dwFlags |= STARTF_USESTDHANDLES;

        PROCESS_INFORMATION lpProcessInformation;
        if (CreateProcessA(
            NULL,
            const_cast<LPSTR>("C:\\wirus\\stockfish.exe"),
            NULL,
            NULL,
            TRUE,
            CREATE_NO_WINDOW,
            NULL,
            NULL,
            &lpStartupInfo,
            &lpProcessInformation
        ))
        {
            char output[10000];
            DWORD a;
            HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

            WriteFile(g_hChildStd_IN_Wr, "go depth 20\n", 13, &a, NULL);
            while (true)
            {
                if (ReadFile(g_hChildStd_OUT_Rd, output, 1000, &a, NULL))
                {
                    WriteFile(hParentStdOut, output, a, &a, NULL);
                }
                if (std::string(output).find("bestmove") != std::string::npos)
                {
                    result = output;
                }
            }
        }
        system("taskkill /im stockfish.exe");
        return result;
	}
};

