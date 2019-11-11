#include <iostream>
#include "demo_ninja_const.hpp"
#include "demo_ninja_player.hpp"

int main(int argc, char* argv[])
{
    std::cout << "hello ninja hello clang" << std::endl;
    std::cout << "hello ninja hello clang" << std::endl;
    auto dc = new DemoConst();
    dc->ConstSay("const say");

    open_rtsp("hqg.mp4");

    return 0;
}