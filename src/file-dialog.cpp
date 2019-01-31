#include "file-dialog.h"
#include <cstring>

#ifdef __MINGW32__
#include <windows.h>
#endif
std::string ShowFileDialog(bool bSave)
{
	char szFile[1024] = "";
#ifdef __linux__
	const char* szCommand;
	if (bSave)
		szCommand = "zenity --file-selection --save 2> /dev/null";
	else
		szCommand = "zenity --file-selection 2> /dev/null";
	FILE *fPipe;
	fPipe = popen(szCommand, "r");
	if (fPipe)
	{
		fgets(szFile, sizeof(szFile), fPipe);
		pclose(fPipe);
	}
	int iLength = strlen(szFile);
	if (iLength > 0)
		szFile[iLength - 1] = 0;
#endif
#ifdef __APPLE__
	if (bSave)
		szCommand = "";
	else
		szCommand = "";
#endif
#ifdef __MINGW32__
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize  = sizeof(ofn);
	ofn.hwndOwner    = NULL;
	ofn.lpstrFilter  = "Image Files\0*.pbm\0All Files\0*.*\0\0";
	ofn.lpstrFile    = szFile;
	ofn.nMaxFile     = sizeof(szFile);
	ofn.lpstrTitle   = "Select an image";
	if (bSave)
		ofn.Flags    = OFN_HIDEREADONLY;
	else
		ofn.Flags    = OFN_FILEMUSTEXIST;

	if (!GetOpenFileNameA(&ofn))
		szFile[0] = '\0';
#endif

	return szFile;
}
