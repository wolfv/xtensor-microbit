/***************************************************************************
* Copyright (c) 2018, Wolf Vollprecht, Johan Mabille and Sylvain Corlay    *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include "MicroBit.h"

#undef PI
#include <xtensor/xtensor.hpp>

MicroBit uBit;

// Init for a stable brick for debug purposes
// xt::xtensor<uint8_t, 2> init = {{0,0,0,0,0},
//                                 {0,0,1,0,0},
//                                 {0,0,1,0,0},
//                                 {0,0,1,0,0},
//                                 {0,0,0,0,0}};

void display_xtensor(const xt::xtensor<uint8_t, 2>& dx)
{
    auto img = MicroBitImage(dx.shape()[0], dx.shape()[1], dx.raw_data());
    uBit.display.print(img);
}

void game_of_life_step(xt::xtensor<uint8_t, 2>& state)
{
    auto cnt = xt::xtensor<uint8_t, 2>::from_shape({state.shape()[0], state.shape()[1]});

    auto idx = [&state](int i)
    {
        if (i < 0)
            return (int)state.shape()[0] - 1;
        if (i == state.shape()[0])
            return 0;
        return i;
    };

    for (int i = 0; i < state.shape()[0]; ++i)
    {
        for (int j = 0; j < state.shape()[1]; ++j)
        {
            cnt(i, j) = state(idx(i - 1), idx(j - 1)) + state(i, idx(j - 1)) + state(idx(i + 1), idx(j - 1)) +
                        state(idx(i - 1), j)                                 + state(idx(i + 1), j)          +
                        state(idx(i - 1), idx(j + 1)) + state(i, idx(j + 1)) + state(idx(i + 1), idx(j + 1));
        }
    }

    // Any cell with fewer than 2 dies, any cell with more than 3 neighbours dies
    state = (state && (cnt >= 2 && cnt < 4)) || (equal(state, 0) && equal(cnt, 3));
}

int main()
{
    uBit.init();
    xt::xtensor<uint8_t, 2> init = {{0,0,0,0,0},
                                    {0,1,0,1,0},
                                    {1,1,1,0,0},
                                    {0,1,0,0,1},
                                    {1,1,1,0,0}};
    while (true)
    {
        game_of_life_step(init);
        display_xtensor(init);
        uBit.sleep(300);
    }
    return 1;
}