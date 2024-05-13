#pragma once
#include <raylib.h>
#include <vector>


extern const Color darkgray;
extern const Color green;
extern const Color red;
extern const Color orange;
extern const Color yellow;
extern const Color purple;
extern const Color cyan;
extern const Color blue;

// for the user interface
extern const Color lightblue;
extern const Color darkblue;

//////////////
/// \brief creates and returns a vector of pre-defined colors
/// \return a vector of 8 colors (the 0 index is representing a dark-gray value for the empty cells, 1-7 indices are reserved for blocks
//////////////
std::vector<Color> CreatCellColors();