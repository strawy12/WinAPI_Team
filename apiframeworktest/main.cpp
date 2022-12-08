

#include "pch.h"
#include "framework.h"
#include "apiframeworktest.h"
#include <vector>
#include "BWindow.h"
#include "Core.h"
#include <iostream>
//#include <crtdbg.h>
using namespace std;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    BWindow game;
    game.Run(hInstance, lpCmdLine, nCmdShow);
    return 0;
}