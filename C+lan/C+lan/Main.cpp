// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "Application.h"
#include <time.h>

int main()
{
    srand((unsigned int)time(NULL));    // �����p

    //**  �A�v���P�[�V�������s  **//
    Ctlan::PrivateSystem::Application app;
    app.Run();

    return 0;
}
