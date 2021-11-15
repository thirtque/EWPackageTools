#ifndef UNTITLED3_DIALOG_H
#define UNTITLED3_DIALOG_H

#include <string>
#include <nfd.h>

struct OpenFileDialogResult {
    bool Status;
    std::string Path;
};

void InitializeDialog();

void FinalizeDialog();

OpenFileDialogResult OpenFileDialog();

#endif
