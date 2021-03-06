#pragma once

#include <nanovg.h>
#include <nanocanvas/NanoCanvas.h>
#include <cstdlib>
#include <fmt/format.h>

namespace drawing {
using namespace NanoCanvas;

const uint WIDTH = 320;
const uint HEIGHT = 240;

const auto COLOR_BLACK = Color(0,0,0);
const auto COLOR_WHITE = Color(255, 255, 255);
const auto COLOR_WHITE_DIMMED = Color(100, 100, 100);
const auto COLOR_RED = Color(255, 42, 42);
const auto COLOR_RED_DIMMED = Color(110, 12, 12);
const auto COLOR_BLUE = Color(10, 124, 255);
const auto COLOR_BLUE_DIMMED = Color(12, 12, 110);
const auto COLOR_GREEN = Color(94, 207, 62);
const auto COLOR_GREEN_DIMMED = Color(12, 110, 12);

const auto COLOR_GRAY60 = Color(60, 60, 71);
const auto COLOR_GRAY70 = Color(0.7f, 0.7f, 0.7f);

const auto COLOR_CURRENT_TRACK = Color(255, 74, 74);
const auto COLOR_CURRENT_SLICE = Color(74, 74, 255);
const auto COLOR_OTHER_TRACK = Color(80, 80, 80);
const auto COLOR_LOOP_MARKER = COLOR_GREEN;
const auto COLOR_BAR_MARKER = Color(204, 204, 204);

extern Font FONT_LIGHT;
extern Font FONT_NORM;
extern Font FONT_BOLD;

void initUtils(Canvas &canvas);

}
