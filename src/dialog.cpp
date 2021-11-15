#include "dialog.h"

#ifdef _WIN32
#include <locale>
#include <codecvt>
#endif

void InitializeDialog() {
    NFD_Init();
}

void FinalizeDialog() {
    NFD_Quit();
}

// @todo Add parameters to pass default directory and filter list
OpenFileDialogResult OpenFileDialog() {
    nfdchar_t *nfdPath;
    const nfdchar_t *nfdDefaultPath = "~/.steam/steam/steamapps/common/Eastward/content/game";
    nfdfilteritem_t nfdFilterItem[] = {{"Eastward Package", "g"}};
    nfdresult_t nfdResult = NFD_OpenDialog(&nfdPath, nfdFilterItem, 1, nfdDefaultPath);
    if (nfdResult == NFD_OKAY) {
#ifdef _WIN32
        std::string path = std::wstring_convert<std::codecvt_utf8_utf16<nfdchar_t>, nfdchar_t>{}.to_bytes(nfdPath);
#else
        std::string path = nfdPath;
#endif
        NFD_FreePath(nfdPath);

        return {true, path};
    }

    return {false, ""};
}
