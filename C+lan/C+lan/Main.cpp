//  //
// @@t@CΜCN[h@@ //
//  //
#include "Application.h"
#include <time.h>

#if _DEBUG
// DebugrhΜGg|Cg
int main()
{
    srand((unsigned int)time(NULL));    // p

    //**  AvP[Vΐs  **//
    Ctlan::PrivateSystem::Application app;
    app.Run();

    return 0;
}
#else
// ReleaserhΜGg|Cg
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    srand((unsigned int)time(NULL));    // p

    //**  AvP[Vΐs  **//
    Ctlan::PrivateSystem::Application app;
    app.Run();

    return 0;
}
#endif