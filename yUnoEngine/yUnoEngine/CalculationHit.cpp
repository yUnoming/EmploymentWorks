#include "CalculationHit.h"

bool PublicSystem::CalculationHit::SegmentToSegment(Vector3 mySegmentStart, Vector3 mySegmentEnd, Vector3 _otherSegment_Start, Vector3 _otherSegment_End)
{
    // ===== ����ɕK�v�ȃx�N�g�����쐬 ===== //
    // ** ���g�̐����p ** //
    Vector3 MyStart_To_MyEnd      = mySegmentEnd - mySegmentStart;         // ���g�̐����̃x�N�g��
    Vector3 MyStart_To_OtherStart = _otherSegment_Start - mySegmentStart;    // ���g�̎n�_���瑊��̎n�_�ւ̃x�N�g��
    Vector3 MyStart_To_OtherEnd   = _otherSegment_End - mySegmentStart;      // ���g�̎n�_���瑊��̏I�_�ւ̃x�N�g��

    // ** ����̐����p ** //
    Vector3 OtherStart_To_OtherEnd = _otherSegment_End - _otherSegment_Start;   // ����̐����̃x�N�g��
    Vector3 OtherStart_To_MyStart  = mySegmentStart - _otherSegment_Start;    // ����̎n�_���玩�g�̎n�_�ւ̃x�N�g��
    Vector3 OtherStart_To_MyEnd    = mySegmentEnd - _otherSegment_Start;      // ����̎n�_���玩�g�̏I�_�ւ̃x�N�g��


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

bool PublicSystem::CalculationHit::SegmentToQuadrangle(Vector3 mySegmentStart, Vector3 mySegmentEnd, Vector3 _otherRightTop, Vector3 _otherLeftBottom)
{
    // ===== �����̎n�_�ƏI�_���l�p�`�̓����ɂ��邩�ǂ����𔻒肵�A===== //
    // =====     �����ɂ���΁h�h�����Ǝl�p�`�͓������Ă���h�h    ===== //
    if (PointToQuadrangle(mySegmentStart, _otherRightTop, _otherLeftBottom) &&
        PointToQuadrangle(mySegmentEnd, _otherRightTop, _otherLeftBottom))
    {
        return true;
    };


    // �E��A�������_�͕������Ă���̂ŁA�c��̂Q���_���擾
    Vector3 OtherRightBottom = Vector3(_otherRightTop.x, _otherLeftBottom.y);   // �E�����_
    Vector3 OtherLeftTop = Vector3(_otherLeftBottom.x, _otherRightTop.y);       // �������_


    // ===== �l�p�`�́u�S�̕Ӂi�����j�v����o���Ă���̂ŁA�e�ӂƎ��g�̐����Ƃ̓����蔻����s�� ===== //
    // =====   �@�@        1�ł��������Ă���΁A�h�h�����Ǝl�p�`�͓������Ă���h�h   �@�@�@�@   ===== //
    if (
        SegmentToSegment(mySegmentStart, mySegmentEnd, OtherLeftTop, _otherRightTop) ||         // ���
        SegmentToSegment(mySegmentStart, mySegmentEnd, _otherLeftBottom, OtherRightBottom) ||   // ����
        SegmentToSegment(mySegmentStart, mySegmentEnd, OtherLeftTop, _otherLeftBottom) ||       // ����
        SegmentToSegment(mySegmentStart, mySegmentEnd, _otherRightTop, OtherRightBottom)        // �E��
        )
    {
        return true;
    }

    // �����܂ŗ����Ȃ�h�h�����Ǝl�p�`�͓������Ă��Ȃ��h�h
    return false;
}

bool PublicSystem::CalculationHit::SegmentToHexahedron(Vector3 mySegmentStart, Vector3 mySegmentEnd, const Transform* otherHexahedron)
{
    // ===== �Z�ʑ̂��e���W���ʂ��猩���ۂɏo����u�l�p�`�v�����߂� ===== //
    // ----- XY���ʂ̎l�p�` ----- //
    Vector3 XY_Plane_Quad[2] =
    {
        // �E�㒸�_
        Vector3(otherHexahedron->position.x + otherHexahedron->scale.x / 2, 
                otherHexahedron->position.y + otherHexahedron->scale.y / 2, 0.0f),
        // �������_
        Vector3(otherHexahedron->position.x - otherHexahedron->scale.x / 2, 
                otherHexahedron->position.y - otherHexahedron->scale.y / 2, 0.0f),
    };

    // ----- ZY���ʂ̎l�p�` ----- //
    Vector3 ZY_Plane_Quad[2] =
    {
        // �E�㒸�_
        Vector3(otherHexahedron->position.z + otherHexahedron->scale.z / 2,
                otherHexahedron->position.y + otherHexahedron->scale.y / 2, 0.0f),
        // �������_
        Vector3(otherHexahedron->position.z - otherHexahedron->scale.z / 2,
                otherHexahedron->position.y - otherHexahedron->scale.y / 2, 0.0f),
    };

    // ----- XZ���ʂ̎l�p�` ----- //
    Vector3 XZ_Plane_Quad[2] =
    {
        // �E�㒸�_
        Vector3(otherHexahedron->position.x + otherHexahedron->scale.x / 2,
                otherHexahedron->position.z + otherHexahedron->scale.z / 2, 0.0f),
        // �������_
        Vector3(otherHexahedron->position.x - otherHexahedron->scale.x / 2,
                otherHexahedron->position.z - otherHexahedron->scale.z / 2, 0.0f),
    };


    // ===== �e���W���ʂ��猩���ꍇ�̐��������߂� ===== //
    // ----- XY���ʂ̐��� ----- //
    Vector3 XY_Plane_Segment[2] =
    {
        // �n�_
        Vector3(mySegmentStart.x, mySegmentStart.y, 0.0f),
        // �I�_
        Vector3(mySegmentEnd.x, mySegmentEnd.y, 0.0f),
    };

    // ----- ZY���ʂ̐��� ----- //
    Vector3 ZY_Plane_Segment[2] =
    {
        // �n�_
        Vector3(mySegmentStart.z, mySegmentStart.y, 0.0f),
        // �I�_
        Vector3(mySegmentEnd.z, mySegmentEnd.y, 0.0f),
    };

    // ----- XZ���ʂ̐��� ----- //
    Vector3 XZ_Plane_Segment[2] = 
    {
        // �n�_
        Vector3(mySegmentStart.x, mySegmentStart.z, 0.0f),
        // �I�_
        Vector3(mySegmentEnd.x, mySegmentEnd.z, 0.0f),
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

bool PublicSystem::CalculationHit::SegmentToHexahedron(Vector3 mySegmentStart, Vector3 mySegmentEnd, DirectX::BoundingBox otherBoundingBox, const Transform* otherHexahedron)
{
    // Transform�̉�]�l�����ɋ��E�{�b�N�X����]
    Vector3 center, extents;
    center = otherBoundingBox.Center;
    extents = otherBoundingBox.Extents;

    //// ��]�s��擾
    //DirectX::SimpleMath::Matrix rot = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(
    //    DirectX::XMConvertToRadians(otherHexahedron->rotation.y),
    //    DirectX::XMConvertToRadians(otherHexahedron->rotation.x),
    //    DirectX::XMConvertToRadians(otherHexahedron->rotation.z));

    //// ��]�s��̕���
    //DirectX::SimpleMath::Vector3 scale, translation;
    //DirectX::SimpleMath::Quaternion rotation;
    //rot.Decompose(scale, rotation, translation);

    //// ���E�{�b�N�X����]
    //otherBoundingBox.Transform(otherBoundingBox, DirectX::SimpleMath::Matrix::CreateFromQuaternion(rotation));


    // ���E�{�b�N�X��Transfrom�������ɏC��
    // ���S
    center = Vector3(
        otherBoundingBox.Center.x + otherHexahedron->position.x,
        otherBoundingBox.Center.y + otherHexahedron->position.y,
        otherBoundingBox.Center.z + otherHexahedron->position.z);
    // ��
    extents = Vector3(
        otherBoundingBox.Extents.x * otherHexahedron->scale.x,
        otherBoundingBox.Extents.y * otherHexahedron->scale.y,
        otherBoundingBox.Extents.z * otherHexahedron->scale.z);

    // ===== �Z�ʑ̂��e���W���ʂ��猩���ۂɏo����u�l�p�`�v�����߂� ===== //
    // ----- XY���ʂ̎l�p�` ----- //
    Vector3 XY_Plane_Quad[2] =
    {
        // �E�㒸�_
        Vector3(center.x + extents.x, center.y + extents.y),
        // �������_
        Vector3(center.x - extents.x, center.y - extents.y),
    };

    // ----- ZY���ʂ̎l�p�` ----- //
    Vector3 ZY_Plane_Quad[2] =
    {
        // �E�㒸�_
        Vector3(center.z + extents.z, center.y + extents.y),
        // �������_
        Vector3(center.z - extents.z, center.y - extents.y),
    };

    // ----- XZ���ʂ̎l�p�` ----- //
    Vector3 XZ_Plane_Quad[2] =
    {
        // �E�㒸�_
        Vector3(center.x + extents.x, center.z + extents.z),
        // �������_
        Vector3(center.x - extents.x, center.z - extents.z),
    };


    // ===== �e���W���ʂ��猩���ꍇ�̐��������߂� ===== //
    // ----- XY���ʂ̐��� ----- //
    Vector3 XY_Plane_Segment[2] =
    {
        // �n�_
        Vector3(mySegmentStart.x, mySegmentStart.y, 0.0f),
        // �I�_
        Vector3(mySegmentEnd.x, mySegmentEnd.y, 0.0f),
    };

    // ----- ZY���ʂ̐��� ----- //
    Vector3 ZY_Plane_Segment[2] =
    {
        // �n�_
        Vector3(mySegmentStart.z, mySegmentStart.y, 0.0f),
        // �I�_
        Vector3(mySegmentEnd.z, mySegmentEnd.y, 0.0f),
    };

    // ----- XZ���ʂ̐��� ----- //
    Vector3 XZ_Plane_Segment[2] =
    {
        // �n�_
        Vector3(mySegmentStart.x, mySegmentStart.z, 0.0f),
        // �I�_
        Vector3(mySegmentEnd.x, mySegmentEnd.z, 0.0f),
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
