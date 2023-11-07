// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "ScreenInput.h"
#include "Vector2.h"
#include "Application.h"
#include <SimpleMath.h>
#include <Windows.h>


PublicSystem::Vector2 PublicSystem::ScreenInput::GetScreenPosition(Vector2 _paramPosition)
{
    // �X�N���[�����W��������ϐ��i�����̒l�������l�Ƃ��đ���j
    POINT ScreenPosition = {_paramPosition.x, _paramPosition.y};

    // �X�N���[�����W���擾
    ScreenToClient(Application::GetWindow(), &ScreenPosition);
    // ** ��L�֐��̕⑫ **
    // Screen��PC�̉�ʂȂǂ̎����w���A
    // Client�̓A�v���̉�ʁiScreenInput��Screen�ɒl������́j���w���Ă���B

    // �l��Vector2�ɕϊ����ĕԂ�
    return Vector2(ScreenPosition.x, ScreenPosition.y);
}
