#include "file-dialog.h"
#include <cstring>

std::string GetOpenFileName(bool bSave)
{
	const char* szCommand;
#ifdef __linux__
	if (bSave)
		szCommand = "zenity --file-selection --save 2> /dev/null";
	else
		szCommand = "zenity --file-selection 2> /dev/null";
#endif
#ifdef __APPLE__
	if (bSave)
		szCommand = "";
	else
		szCommand = "";
#endif
#ifdef __MINGW32__
	if (bSave)
		szCommand = "cmd.exe /V:ON /C \"set /p file= && echo !file!\"";
	else
		szCommand = "cmd.exe /V:ON /C \"set /p file= && echo !file!\"";
#endif
	char szFile[1024];
	szFile[0] = '\0';
	FILE *fPipe;
	fPipe = popen(szCommand, "r");
	if (fPipe)
	{
		fgets(szFile, 1024, fPipe);
		pclose(fPipe);
	}
	int iLength = strlen(szFile);
	if (iLength > 0)
		szFile[iLength - 1] = 0;
	return std::string(szFile);
}
