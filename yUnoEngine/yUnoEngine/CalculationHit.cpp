#include "CalculationHit.h"

bool PublicSystem::CalculationHit::SegmentToSegment(Vector3 mySegmentStart, Vector3 mySegmentEnd, Vector3 _otherSegment_Start, Vector3 _otherSegment_End)
{
    // ===== 判定に必要なベクトルを作成 ===== //
    // ** 自身の線分用 ** //
    Vector3 MyStart_To_MyEnd      = mySegmentEnd - mySegmentStart;         // 自身の線分のベクトル
    Vector3 MyStart_To_OtherStart = _otherSegment_Start - mySegmentStart;    // 自身の始点から相手の始点へのベクトル
    Vector3 MyStart_To_OtherEnd   = _otherSegment_End - mySegmentStart;      // 自身の始点から相手の終点へのベクトル

    // ** 相手の線分用 ** //
    Vector3 OtherStart_To_OtherEnd = _otherSegment_End - _otherSegment_Start;   // 相手の線分のベクトル
    Vector3 OtherStart_To_MyStart  = mySegmentStart - _otherSegment_Start;    // 相手の始点から自身の始点へのベクトル
    Vector3 OtherStart_To_MyEnd    = mySegmentEnd - _otherSegment_Start;      // 相手の始点から自身の終点へのベクトル


    // ===== 外積計算を実行 ===== //
    // ** 自身の線分用 ** //
    float CrossA_For_Me = (MyStart_To_MyEnd.x * MyStart_To_OtherStart.y) - (MyStart_To_OtherStart.x * MyStart_To_MyEnd.y);
    float CrossB_For_Me = (MyStart_To_MyEnd.x * MyStart_To_OtherEnd.y) - (MyStart_To_OtherEnd.x * MyStart_To_MyEnd.y);
    
    // ** 相手の線分用 ** //
    float CrossA_For_Other = (OtherStart_To_OtherEnd.x * OtherStart_To_MyStart.y) - (OtherStart_To_MyStart.x * OtherStart_To_OtherEnd.y);
    float CrossB_For_Other = (OtherStart_To_OtherEnd.x * OtherStart_To_MyEnd.y) - (OtherStart_To_MyEnd.x * OtherStart_To_OtherEnd.y);


    // 外積結果を乗算し、結果が負の値であれば””線分と線分は当たっている””
    if (CrossA_For_Me * CrossB_For_Me < 0.0f && CrossA_For_Other * CrossB_For_Other < 0.0f)
    {
        return true;
    }

    // ここまで来たなら””線分と線分は当たっていない””
    return false;
}

bool PublicSystem::CalculationHit::SegmentToQuadrangle(Vector3 mySegmentStart, Vector3 mySegmentEnd, Vector3 _otherRightTop, Vector3 _otherLeftBottom)
{
    // ===== 線分の始点と終点が四角形の内側にあるかどうかを判定し、===== //
    // =====     内側にあれば””線分と四角形は当たっている””    ===== //
    if (PointToQuadrangle(mySegmentStart, _otherRightTop, _otherLeftBottom) &&
        PointToQuadrangle(mySegmentEnd, _otherRightTop, _otherLeftBottom))
    {
        return true;
    };


    // 右上、左下頂点は分かっているので、残りの２頂点を取得
    Vector3 OtherRightBottom = Vector3(_otherRightTop.x, _otherLeftBottom.y);   // 右下頂点
    Vector3 OtherLeftTop = Vector3(_otherLeftBottom.x, _otherRightTop.y);       // 左下頂点


    // ===== 四角形は「４つの辺（線分）」から出来ているので、各辺と自身の線分との当たり判定を行う ===== //
    // =====   　　        1つでも当たっていれば、””線分と四角形は当たっている””   　　　　   ===== //
    if (
        SegmentToSegment(mySegmentStart, mySegmentEnd, OtherLeftTop, _otherRightTop) ||         // 上辺
        SegmentToSegment(mySegmentStart, mySegmentEnd, _otherLeftBottom, OtherRightBottom) ||   // 下辺
        SegmentToSegment(mySegmentStart, mySegmentEnd, OtherLeftTop, _otherLeftBottom) ||       // 左辺
        SegmentToSegment(mySegmentStart, mySegmentEnd, _otherRightTop, OtherRightBottom)        // 右辺
        )
    {
        return true;
    }

    // ここまで来たなら””線分と四角形は当たっていない””
    return false;
}

bool PublicSystem::CalculationHit::SegmentToHexahedron(Vector3 mySegmentStart, Vector3 mySegmentEnd, const Transform* otherHexahedron)
{
    // ===== 六面体を各座標平面から見た際に出来る「四角形」を求める ===== //
    // ----- XY平面の四角形 ----- //
    Vector3 XY_Plane_Quad[2] =
    {
        // 右上頂点
        Vector3(otherHexahedron->position.x + otherHexahedron->scale.x / 2, 
                otherHexahedron->position.y + otherHexahedron->scale.y / 2, 0.0f),
        // 左下頂点
        Vector3(otherHexahedron->position.x - otherHexahedron->scale.x / 2, 
                otherHexahedron->position.y - otherHexahedron->scale.y / 2, 0.0f),
    };

    // ----- ZY平面の四角形 ----- //
    Vector3 ZY_Plane_Quad[2] =
    {
        // 右上頂点
        Vector3(otherHexahedron->position.z + otherHexahedron->scale.z / 2,
                otherHexahedron->position.y + otherHexahedron->scale.y / 2, 0.0f),
        // 左下頂点
        Vector3(otherHexahedron->position.z - otherHexahedron->scale.z / 2,
                otherHexahedron->position.y - otherHexahedron->scale.y / 2, 0.0f),
    };

    // ----- XZ平面の四角形 ----- //
    Vector3 XZ_Plane_Quad[2] =
    {
        // 右上頂点
        Vector3(otherHexahedron->position.x + otherHexahedron->scale.x / 2,
                otherHexahedron->position.z + otherHexahedron->scale.z / 2, 0.0f),
        // 左下頂点
        Vector3(otherHexahedron->position.x - otherHexahedron->scale.x / 2,
                otherHexahedron->position.z - otherHexahedron->scale.z / 2, 0.0f),
    };


    // ===== 各座標平面から見た場合の線分を求める ===== //
    // ----- XY平面の線分 ----- //
    Vector3 XY_Plane_Segment[2] =
    {
        // 始点
        Vector3(mySegmentStart.x, mySegmentStart.y, 0.0f),
        // 終点
        Vector3(mySegmentEnd.x, mySegmentEnd.y, 0.0f),
    };

    // ----- ZY平面の線分 ----- //
    Vector3 ZY_Plane_Segment[2] =
    {
        // 始点
        Vector3(mySegmentStart.z, mySegmentStart.y, 0.0f),
        // 終点
        Vector3(mySegmentEnd.z, mySegmentEnd.y, 0.0f),
    };

    // ----- XZ平面の線分 ----- //
    Vector3 XZ_Plane_Segment[2] = 
    {
        // 始点
        Vector3(mySegmentStart.x, mySegmentStart.z, 0.0f),
        // 終点
        Vector3(mySegmentEnd.x, mySegmentEnd.z, 0.0f),
    };


    // =====     求めた四角形と求めた線分との当たり判定を行う      ===== //
    // ===== 全て当たっていれば、””線分と六面体は当たっている””===== //
    if (
        SegmentToQuadrangle(XY_Plane_Segment[0], XY_Plane_Segment[1], XY_Plane_Quad[0], XY_Plane_Quad[1]) &&
        SegmentToQuadrangle(ZY_Plane_Segment[0], ZY_Plane_Segment[1], ZY_Plane_Quad[0], ZY_Plane_Quad[1]) &&
        SegmentToQuadrangle(XZ_Plane_Segment[0], XZ_Plane_Segment[1], XZ_Plane_Quad[0], XZ_Plane_Quad[1]))
    {
        return true;
    }

    // ===== ここまで来たなら、””線分と六面体は当たっていない””===== //
    return false;
}

bool PublicSystem::CalculationHit::SegmentToHexahedron(Vector3 mySegmentStart, Vector3 mySegmentEnd, DirectX::BoundingBox otherBoundingBox, const Transform* otherHexahedron)
{
    // Transformの回転値を元に境界ボックスを回転
    Vector3 center, extents;
    center = otherBoundingBox.Center;
    extents = otherBoundingBox.Extents;

    //// 回転行列取得
    //DirectX::SimpleMath::Matrix rot = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(
    //    DirectX::XMConvertToRadians(otherHexahedron->rotation.y),
    //    DirectX::XMConvertToRadians(otherHexahedron->rotation.x),
    //    DirectX::XMConvertToRadians(otherHexahedron->rotation.z));

    //// 回転行列の分解
    //DirectX::SimpleMath::Vector3 scale, translation;
    //DirectX::SimpleMath::Quaternion rotation;
    //rot.Decompose(scale, rotation, translation);

    //// 境界ボックスを回転
    //otherBoundingBox.Transform(otherBoundingBox, DirectX::SimpleMath::Matrix::CreateFromQuaternion(rotation));


    // 境界ボックスをTransfrom情報を元に修正
    // 中心
    center = Vector3(
        otherBoundingBox.Center.x + otherHexahedron->position.x,
        otherBoundingBox.Center.y + otherHexahedron->position.y,
        otherBoundingBox.Center.z + otherHexahedron->position.z);
    // 幅
    extents = Vector3(
        otherBoundingBox.Extents.x * otherHexahedron->scale.x,
        otherBoundingBox.Extents.y * otherHexahedron->scale.y,
        otherBoundingBox.Extents.z * otherHexahedron->scale.z);

    // ===== 六面体を各座標平面から見た際に出来る「四角形」を求める ===== //
    // ----- XY平面の四角形 ----- //
    Vector3 XY_Plane_Quad[2] =
    {
        // 右上頂点
        Vector3(center.x + extents.x, center.y + extents.y),
        // 左下頂点
        Vector3(center.x - extents.x, center.y - extents.y),
    };

    // ----- ZY平面の四角形 ----- //
    Vector3 ZY_Plane_Quad[2] =
    {
        // 右上頂点
        Vector3(center.z + extents.z, center.y + extents.y),
        // 左下頂点
        Vector3(center.z - extents.z, center.y - extents.y),
    };

    // ----- XZ平面の四角形 ----- //
    Vector3 XZ_Plane_Quad[2] =
    {
        // 右上頂点
        Vector3(center.x + extents.x, center.z + extents.z),
        // 左下頂点
        Vector3(center.x - extents.x, center.z - extents.z),
    };


    // ===== 各座標平面から見た場合の線分を求める ===== //
    // ----- XY平面の線分 ----- //
    Vector3 XY_Plane_Segment[2] =
    {
        // 始点
        Vector3(mySegmentStart.x, mySegmentStart.y, 0.0f),
        // 終点
        Vector3(mySegmentEnd.x, mySegmentEnd.y, 0.0f),
    };

    // ----- ZY平面の線分 ----- //
    Vector3 ZY_Plane_Segment[2] =
    {
        // 始点
        Vector3(mySegmentStart.z, mySegmentStart.y, 0.0f),
        // 終点
        Vector3(mySegmentEnd.z, mySegmentEnd.y, 0.0f),
    };

    // ----- XZ平面の線分 ----- //
    Vector3 XZ_Plane_Segment[2] =
    {
        // 始点
        Vector3(mySegmentStart.x, mySegmentStart.z, 0.0f),
        // 終点
        Vector3(mySegmentEnd.x, mySegmentEnd.z, 0.0f),
    };


    // =====     求めた四角形と求めた線分との当たり判定を行う      ===== //
    // ===== 全て当たっていれば、””線分と六面体は当たっている””===== //
    if (
        SegmentToQuadrangle(XY_Plane_Segment[0], XY_Plane_Segment[1], XY_Plane_Quad[0], XY_Plane_Quad[1]) &&
        SegmentToQuadrangle(ZY_Plane_Segment[0], ZY_Plane_Segment[1], ZY_Plane_Quad[0], ZY_Plane_Quad[1]) &&
        SegmentToQuadrangle(XZ_Plane_Segment[0], XZ_Plane_Segment[1], XZ_Plane_Quad[0], XZ_Plane_Quad[1]))
    {
        return true;
    }

    // ===== ここまで来たなら、””線分と六面体は当たっていない””===== //
    return false;
}

bool PublicSystem::CalculationHit::PointToQuadrangle(Vector3 _myPoint, Vector3 _otherRightTop, Vector3 _otherLeftBottom)
{
    // ===== 点が四角形の内側にあれば””点と四角形は当たっている”” ===== //
    if (_myPoint.x >= _otherLeftBottom.x &&     // 点が四角形の左辺より右側にあるか
        _myPoint.x <= _otherRightTop.x   &&     // 点が四角形の右辺より左側にあるか
        _myPoint.y <= _otherRightTop.y   &&     // 点が四角形の上辺より下側にあるか
        _myPoint.y >= _otherLeftBottom.y)       // 点が四角形の下辺より上側にあるか
    {
        return true;
    }

    // ===== ここまで来たなら、””線分と六面体は当たっていない””===== //
    return false;
}
