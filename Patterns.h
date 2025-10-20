#ifndef PATTERNS_H
#define PATTERNS_H

namespace SegmentPatterns {
// 1=Segment pixel, 0=Background pixel

const bool HORIZONTAL_LINE[3][3] = {
    {false, false, false},
    {true,  true,  true},
    {false, false, false}
};

const bool VERTICAL_LINE[3][3] = {
    {false, true, false},
    {false, true, false},
    {false, true, false}
};

const bool CORNER_90[3][3] = {
    {true, true,  false},
    {true, true,  false},
    {false, false, false}
};

const bool T_JUNCTION[3][3] = {
    {true, true,  true},
    {false, true,  false},
    {false, true, false}
};



}

#endif // PATTERNS_H
