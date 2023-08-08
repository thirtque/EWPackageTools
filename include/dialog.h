#pragma once

#include <string>
#include <nfd.h>

namespace Dialog {
    struct FileFilter {
        std::string Name;
        std::string Filter;
    };
    struct FileResult {
        bool Status;
        std::string Path;
    };
    struct DirectoryResult {
        bool Status;
        std::string Path;
    };

    void Initialize();
    void Finalize();

    FileResult OpenFile(std::vector<FileFilter> fileFilters);
    FileResult SaveFile(const std::string &defaultFileName);

    DirectoryResult SaveDirectory();
}