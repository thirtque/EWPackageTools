//#ifdef _WIN32
//#include <locale>
//#include <codecvt>
//#endif

#include <vector>

#include "dialog.h"

namespace Dialog {
    void Initialize() {
        NFD_Init();
    }

    void Finalize() {
        NFD_Quit();
    }

    // @todo Add parameters to pass default directory
    FileResult OpenFile(std::vector<FileFilter> fileFilters) {
        nfdchar_t *nfdPath;
        const nfdchar_t *nfdDefaultPath = "~/.steam/steam/steamapps/common/Eastward/content/game";
        std::vector<nfdfilteritem_t> nfdFilterItems{};
        for (auto &fileFilter: fileFilters) {
            nfdfilteritem_t nfdFilterItem = {fileFilter.Name.data(), fileFilter.Filter.data()};
            nfdFilterItems.push_back(nfdFilterItem);
        }
        nfdresult_t nfdResult = NFD_OpenDialog(&nfdPath, nfdFilterItems.data(), 1, nfdDefaultPath);
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

    // @todo Add parameters to pass default directory
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

    DirectoryResult SaveDirectory() {
        nfdchar_t *nfdPath;
        const nfdchar_t *nfdDefaultPath = "~/.steam/steam/steamapps/common/Eastward/content/game";
        nfdresult_t nfdResult = NFD_PickFolder(&nfdPath, nfdDefaultPath);
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
