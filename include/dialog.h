#pragma once

#include <string>
#include <nfd.h>

namespace Dialog {
    struct FileResult {
        bool Status;
        std::string Path;
    };

    void Initialize();
    void Finalize();

    FileResult OpenFile();
    FileResult SaveFile(const std::string &defaultFileName);
}