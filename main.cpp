

#include "CodeHunt.h"
#include "Model.h"
#include "View.h"

using namespace gj;

int main(int argc, char **argv) {

    CodeHunt codeHunt;
    Model model({
                        {"Mul3", {{0, 0}, {1, 3}, {5, 15}, {34, 102}}},
                        {"Div5Mul3", {{0, 0}, {5, 3}, {25, 15}, {45, 27}}},
                        {"SquarePlu1", {{0, 1}, {1, 2}, {5, 26}, {34, 1157}}}
                });

    codeHunt.addModel(&model);

    View view(800, 600, &model);
    view.setButtonClickListener("HUNT", [&]() { codeHunt.onHuntButtonClicked(); });
    codeHunt.addView(&view);

    codeHunt.start();

    return 0;
}