#include "ui.h"

int main() {
    Ui::State state{};
    Ui::Initialize(state);
    while (Ui::Loop(state)) {
        Ui::FrameStart(state);
        Ui::RenderFrame();
        Ui::FrameEnd(state);
    }
    Ui::Finalize();

    return 0;
}
