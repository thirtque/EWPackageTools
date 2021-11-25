//#ifdef _WIN32
//#include <locale>
//#include <codecvt>
//#endif

#include "dialog.h"

namespace Dialog {
    void Initialize() {
        NFD_Init();
    }

    void Finalize() {
        NFD_Quit();
    }

    // @todo Add parameters to pass default directory and filter list
    FileResult OpenFile() {
        nfdchar_t *nfdPath;
        const nfdchar_t *nfdDefaultPath = "~/.steam/steam/steamapps/common/Eastward/content/game";
        nfdfilteritem_t nfdFilterItem[] = {{"Eastward Package", "g"}};
        nfdresult_t nfdResult = NFD_OpenDialog(&nfdPath, nfdFilterItem, 1, nfdDefaultPath);
        if (nfdResult == NFD_OKAY) {
            // @todo Check if this helps with Windows build
//#ifdef _WIN32
//            std::string path = std::wstring_convert<std::codecvt_utf8_utf16<nfdchar_t>, nfdchar_t>{}.to_bytes(nfdPath);
//#else
            std::string path = nfdPath;
//#endif
            NFD_FreePath(nfdPath);

            return {true, path};
        }

        return {false, ""};
    }

    // @todo Add parameters to pass default directory and filter list
    FileResult SaveFile(const std::string &defaultFileName) {
        nfdchar_t *nfdPath;
        const nfdchar_t *nfdDefaultPath = "~/.steam/steam/steamapps/common/Eastward/content/game";
        const nfdchar_t *nfdDefaultFileName = defaultFileName.c_str();
        nfdresult_t nfdResult = NFD_SaveDialog(&nfdPath, nullptr, 0, nfdDefaultPath, nfdDefaultFileName);
        if (nfdResult == NFD_OKAY) {
            // @todo Check if this helps with Windows build
//#ifdef _WIN32
//            std::string path = std::wstring_convert<std::codecvt_utf8_utf16<nfdchar_t>, nfdchar_t>{}.to_bytes(nfdPath);
//#else
            std::string path = nfdPath;
//#endif
            NFD_FreePath(nfdPath);

            return {true, path};
        }

        return {false, ""};
    }
}
