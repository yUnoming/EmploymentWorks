#include "CalculationHit.h"

bool PublicSystem::CalculationHit::SegmentToSegment(Vector3 _mySegment_Start, Vector3 _mySegment_End, Vector3 _otherSegment_Start, Vector3 _otherSegment_End)
{
    // ===== ����ɕK�v�ȃx�N�g�����쐬 ===== //
    // ** ���g�̐����p ** //
    Vector3 MyStart_To_MyEnd      = _mySegment_End - _mySegment_Start;         // ���g�̐����̃x�N�g��
    Vector3 MyStart_To_OtherStart = _otherSegment_Start - _mySegment_Start;    // ���g�̎n�_���瑊��̎n�_�ւ̃x�N�g��
    Vector3 MyStart_To_OtherEnd   = _otherSegment_End - _mySegment_Start;      // ���g�̎n�_���瑊��̏I�_�ւ̃x�N�g��

    // ** ����̐����p ** //
    Vector3 OtherStart_To_OtherEnd = _otherSegment_End - _otherSegment_Start;   // ����̐����̃x�N�g��
    Vector3 OtherStart_To_MyStart  = _mySegment_Start - _otherSegment_Start;    // ����̎n�_���玩�g�̎n�_�ւ̃x�N�g��
    Vector3 OtherStart_To_MyEnd    = _mySegment_End - _otherSegment_Start;      // ����̎n�_���玩�g�̏I�_�ւ̃x�N�g��


    // ===== �O�όv�Z�����s ===== //
    // ** ���g�̐����p ** //
    float CrossA_For_Me = (MyStart_To_MyEnd.x * MyStart_To_OtherStart.y) - (MyStart_To_OtherStart.x * MyStart_To_MyEnd.y);
    float CrossB_For_Me = (MyStart_To_MyEnd.x * MyStart_To_OtherEnd.y) - (MyStart_To_OtherEnd.x * MyStart_To_MyEnd.y);
    
    // ** ����̐����p ** //
    float CrossA_For_Other = (OtherStart_To_OtherEnd.x * OtherStart_To_MyStart.y) - (OtherStart_To_MyStart.x * OtherStart_To_OtherEnd.y);
    float CrossB_For_Other = (OtherStart_To_OtherEnd.x * OtherStart_To_MyEnd.y) - (OtherStart_To_MyEnd.x * OtherStart_To_OtherEnd.y);


    // �O�ό��ʂ���Z���A���ʂ����̒l�ł���΁h�h�����Ɛ����͓������Ă���h�h
    if (CrossA_For_Me * CrossB_For_Me < 0.0f && CrossA_For_Other * CrossB_For_Other < 0.0f)
    {
        return true;
    }

    // �����܂ŗ����Ȃ�h�h�����Ɛ����͓������Ă��Ȃ��h�h
    return false;
}

bool PublicSystem::CalculationHit::SegmentToQuadrangle(Vector3 _mySegment_Start, Vector3 _mySegment_End, Vector3 _otherRightTop, Vector3 _otherLeftBottom)
{
    // ===== �����̎n�_�ƏI�_���l�p�`�̓����ɂ��邩�ǂ����𔻒肵�A===== //
    // =====     �����ɂ���΁h�h�����Ǝl�p�`�͓������Ă���h�h    ===== //
    if (PointToQuadrangle(_mySegment_Start, _otherRightTop, _otherLeftBottom) &&
        PointToQuadrangle(_mySegment_End, _otherRightTop, _otherLeftBottom))
    {
        return true;
    };


    // �E��A�������_�͕������Ă���̂ŁA�c��̂Q���_���擾
    Vector3 OtherRightBottom = Vector3(_otherRightTop.x, _otherLeftBottom.y);   // �E�����_
    Vector3 OtherLeftTop = Vector3(_otherLeftBottom.x, _otherRightTop.y);       // �������_


    // ===== �l�p�`�́u�S�̕Ӂi�����j�v����o���Ă���̂ŁA�e�ӂƎ��g�̐����Ƃ̓����蔻����s�� ===== //
    // =====   �@�@        1�ł��������Ă���΁A�h�h�����Ǝl�p�`�͓������Ă���h�h   �@�@�@�@   ===== //
    if (
        SegmentToSegment(_mySegment_Start, _mySegment_End, OtherLeftTop, _otherRightTop) ||         // ���
        SegmentToSegment(_mySegment_Start, _mySegment_End, _otherLeftBottom, OtherRightBottom) ||   // ����
        SegmentToSegment(_mySegment_Start, _mySegment_End, OtherLeftTop, _otherLeftBottom) ||       // ����
        SegmentToSegment(_mySegment_Start, _mySegment_End, _otherRightTop, OtherRightBottom)        // �E��
        )
    {
        return true;
    }

    // �����܂ŗ����Ȃ�h�h�����Ǝl�p�`�͓������Ă��Ȃ��h�h
    return false;
}

bool PublicSystem::CalculationHit::SegmentToHexahedron(Vector3 _mySegment_Start, Vector3 _mySegment_End, const Transform* _otherHexahedron)
{
    // ===== �Z�ʑ̂��e���W���ʂ��猩���ۂɏo����u�l�p�`�v�����߂� ===== //
    // ----- XY���ʂ̎l�p�` ----- //
    Vector3 XY_Plane_Quad[2] =
    {
        // �E�㒸�_
        Vector3(_otherHexahedron->Position.x + _otherHexahedron->Scale.x / 2, 
                _otherHexahedron->Position.y + _otherHexahedron->Scale.y / 2, 0.0f),
        // �������_
        Vector3(_otherHexahedron->Position.x - _otherHexahedron->Scale.x / 2, 
                _otherHexahedron->Position.y - _otherHexahedron->Scale.y / 2, 0.0f),
    };

    // ----- ZY���ʂ̎l�p�` ----- //
    Vector3 ZY_Plane_Quad[2] =
    {
        // �E�㒸�_
        Vector3(_otherHexahedron->Position.z + _otherHexahedron->Scale.z / 2,
                _otherHexahedron->Position.y + _otherHexahedron->Scale.y / 2, 0.0f),
        // �������_
        Vector3(_otherHexahedron->Position.z - _otherHexahedron->Scale.z / 2,
                _otherHexahedron->Position.y - _otherHexahedron->Scale.y / 2, 0.0f),
    };

    // ----- XZ���ʂ̎l�p�` ----- //
    Vector3 XZ_Plane_Quad[2] =
    {
        // �E�㒸�_
        Vector3(_otherHexahedron->Position.x + _otherHexahedron->Scale.x / 2,
                _otherHexahedron->Position.z + _otherHexahedron->Scale.z / 2, 0.0f),
        // �������_
        Vector3(_otherHexahedron->Position.x - _otherHexahedron->Scale.x / 2,
                _otherHexahedron->Position.z - _otherHexahedron->Scale.z / 2, 0.0f),
    };


    // ===== �e���W���ʂ��猩���ꍇ�̐��������߂� ===== //
    // ----- XY���ʂ̐��� ----- //
    Vector3 XY_Plane_Segment[2] =
    {
        // �n�_
        Vector3(_mySegment_Start.x, _mySegment_Start.y, 0.0f),
        // �I�_
        Vector3(_mySegment_End.x, _mySegment_End.y, 0.0f),
    };

    // ----- ZY���ʂ̐��� ----- //
    Vector3 ZY_Plane_Segment[2] =
    {
        // �n�_
        Vector3(_mySegment_Start.z, _mySegment_Start.y, 0.0f),
        // �I�_
        Vector3(_mySegment_End.z, _mySegment_End.y, 0.0f),
    };

    // ----- XZ���ʂ̐��� ----- //
    Vector3 XZ_Plane_Segment[2] = 
    {
        // �n�_
        Vector3(_mySegment_Start.x, _mySegment_Start.z, 0.0f),
        // �I�_
        Vector3(_mySegment_End.x, _mySegment_End.z, 0.0f),
    };


    // =====     ���߂��l�p�`�Ƌ��߂������Ƃ̓����蔻����s��      ===== //
    // ===== �S�ē������Ă���΁A�h�h�����ƘZ�ʑ͓̂������Ă���h�h===== //
    if (
        SegmentToQuadrangle(XY_Plane_Segment[0], XY_Plane_Segment[1], XY_Plane_Quad[0], XY_Plane_Quad[1]) &&
        SegmentToQuadrangle(ZY_Plane_Segment[0], ZY_Plane_Segment[1], ZY_Plane_Quad[0], ZY_Plane_Quad[1]) &&
        SegmentToQuadrangle(XZ_Plane_Segment[0], XZ_Plane_Segment[1], XZ_Plane_Quad[0], XZ_Plane_Quad[1]))
    {
        return true;
    }

    // ===== �����܂ŗ����Ȃ�A�h�h�����ƘZ�ʑ͓̂������Ă��Ȃ��h�h===== //
    return false;
}

bool PublicSystem::CalculationHit::PointToQuadrangle(Vector3 _myPoint, Vector3 _otherRightTop, Vector3 _otherLeftBottom)
{
    // ===== �_���l�p�`�̓����ɂ���΁h�h�_�Ǝl�p�`�͓������Ă���h�h ===== //
    if (_myPoint.x >= _otherLeftBottom.x &&     // �_���l�p�`�̍��ӂ��E���ɂ��邩
        _myPoint.x <= _otherRightTop.x   &&     // �_���l�p�`�̉E�ӂ�荶���ɂ��邩
        _myPoint.y <= _otherRightTop.y   &&     // �_���l�p�`�̏�ӂ�艺���ɂ��邩
        _myPoint.y >= _otherLeftBottom.y)       // �_���l�p�`�̉��ӂ��㑤�ɂ��邩
    {
        return true;
    }

    // ===== �����܂ŗ����Ȃ�A�h�h�����ƘZ�ʑ͓̂������Ă��Ȃ��h�h===== //
    return false;
}
