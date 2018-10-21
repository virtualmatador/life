#include "file-dialog.h"
#include <cstring>

std::string GetOpenFileName(bool bSave)
{
    std::string sName;
#ifdef __linux__
    char file[1024];
	FILE *f = popen("zenity --file-selection  2> /dev/null", "r");
 	fgets(file, 1024, f);
	pclose(f);
	file[strlen(file) - 1] = 0;
    sName = std::string(file);
#endif
#ifdef __APPLE__
#endif
#ifdef __WINDOWS__
#endif
    return sName;
}
