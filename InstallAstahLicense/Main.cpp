#include <Windows.h>
#include <stdio.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nCmdShow)
{

	int argc;
	LPTSTR *argv;
	argv = CommandLineToArgvW(GetCommandLine(), &argc);

	// assuming this is invoked like: InstallAstahLicense.exe "c:\stuff\source-license-file" "C:\Program Files\astah-professional\license-file"
	// exits with 0 on success, nonzero on failure

	if (argc < 3)
	{
		wprintf(L"Usage: %s [source license file] [target license file]\n", argv[0]);
		return 1;
	}

	auto sourceFileName = argv[1];
	auto targetFileName = argv[2];

	wprintf(L"Copying %s to %s...\n", sourceFileName, targetFileName);
	if (CopyFile(sourceFileName, targetFileName, false))
	{
		wprintf(L"License installed!\n");
		return 0;
	}
	else
	{
		auto errorCode = GetLastError();
		wchar_t buffer[16384];
		if (FormatMessageW(0, nullptr, errorCode, 0, buffer, sizeof(buffer), nullptr))
			fwprintf(stderr, L"Copy failed: %s\n", buffer);
		else
			fwprintf(stderr, L"Copy failed: (error code %d)\n", errorCode);

		return -1;
	}
}