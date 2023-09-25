#include "CalculationHit.h"

bool PublicSystem::CalculationHit::SegmentToSegment(Vector3 _mySegment_Start, Vector3 _mySegment_End, Vector3 _otherSegment_Start, Vector3 _otherSegment_End)
{
    // ===== 判定に必要なベクトルを作成 ===== //
    // ** 自身の線分用 ** //
    Vector3 MyStart_To_MyEnd      = _mySegment_End - _mySegment_Start;         // 自身の線分のベクトル
    Vector3 MyStart_To_OtherStart = _otherSegment_Start - _mySegment_Start;    // 自身の始点から相手の始点へのベクトル
    Vector3 MyStart_To_OtherEnd   = _otherSegment_End - _mySegment_Start;      // 自身の始点から相手の終点へのベクトル

    // ** 相手の線分用 ** //
    Vector3 OtherStart_To_OtherEnd = _otherSegment_End - _otherSegment_Start;   // 相手の線分のベクトル
    Vector3 OtherStart_To_MyStart  = _mySegment_Start - _otherSegment_Start;    // 相手の始点から自身の始点へのベクトル
    Vector3 OtherStart_To_MyEnd    = _mySegment_End - _otherSegment_Start;      // 相手の始点から自身の終点へのベクトル


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

bool PublicSystem::CalculationHit::SegmentToQuadrangle(Vector3 _mySegment_Start, Vector3 _mySegment_End, Vector3 _otherRightTop, Vector3 _otherLeftBottom)
{
    // ===== 線分の始点と終点が四角形の内側にあるかどうかを判定し、===== //
    // =====     内側にあれば””線分と四角形は当たっている””    ===== //
    if (PointToQuadrangle(_mySegment_Start, _otherRightTop, _otherLeftBottom) &&
        PointToQuadrangle(_mySegment_End, _otherRightTop, _otherLeftBottom))
    {
        return true;
    };


    // 右上、左下頂点は分かっているので、残りの２頂点を取得
    Vector3 OtherRightBottom = Vector3(_otherRightTop.x, _otherLeftBottom.y);   // 右下頂点
    Vector3 OtherLeftTop = Vector3(_otherLeftBottom.x, _otherRightTop.y);       // 左下頂点


    // ===== 四角形は「４つの辺（線分）」から出来ているので、各辺と自身の線分との当たり判定を行う ===== //
    // =====   　　        1つでも当たっていれば、””線分と四角形は当たっている””   　　　　   ===== //
    if (
        SegmentToSegment(_mySegment_Start, _mySegment_End, OtherLeftTop, _otherRightTop) ||         // 上辺
        SegmentToSegment(_mySegment_Start, _mySegment_End, _otherLeftBottom, OtherRightBottom) ||   // 下辺
        SegmentToSegment(_mySegment_Start, _mySegment_End, OtherLeftTop, _otherLeftBottom) ||       // 左辺
        SegmentToSegment(_mySegment_Start, _mySegment_End, _otherRightTop, OtherRightBottom)        // 右辺
        )
    {
        return true;
    }

    // ここまで来たなら””線分と四角形は当たっていない””
    return false;
}

bool PublicSystem::CalculationHit::SegmentToHexahedron(Vector3 _mySegment_Start, Vector3 _mySegment_End, const Transform* _otherHexahedron)
{
    // ===== 六面体を各座標平面から見た際に出来る「四角形」を求める ===== //
    // ----- XY平面の四角形 ----- //
    Vector3 XY_Plane_Quad[2] =
    {
        // 右上頂点
        Vector3(_otherHexahedron->Position.x + _otherHexahedron->Scale.x / 2, 
                _otherHexahedron->Position.y + _otherHexahedron->Scale.y / 2, 0.0f),
        // 左下頂点
        Vector3(_otherHexahedron->Position.x - _otherHexahedron->Scale.x / 2, 
                _otherHexahedron->Position.y - _otherHexahedron->Scale.y / 2, 0.0f),
    };

    // ----- ZY平面の四角形 ----- //
    Vector3 ZY_Plane_Quad[2] =
    {
        // 右上頂点
        Vector3(_otherHexahedron->Position.z + _otherHexahedron->Scale.z / 2,
                _otherHexahedron->Position.y + _otherHexahedron->Scale.y / 2, 0.0f),
        // 左下頂点
        Vector3(_otherHexahedron->Position.z - _otherHexahedron->Scale.z / 2,
                _otherHexahedron->Position.y - _otherHexahedron->Scale.y / 2, 0.0f),
    };

    // ----- XZ平面の四角形 ----- //
    Vector3 XZ_Plane_Quad[2] =
    {
        // 右上頂点
        Vector3(_otherHexahedron->Position.x + _otherHexahedron->Scale.x / 2,
                _otherHexahedron->Position.z + _otherHexahedron->Scale.z / 2, 0.0f),
        // 左下頂点
        Vector3(_otherHexahedron->Position.x - _otherHexahedron->Scale.x / 2,
                _otherHexahedron->Position.z - _otherHexahedron->Scale.z / 2, 0.0f),
    };


    // ===== 各座標平面から見た場合の線分を求める ===== //
    // ----- XY平面の線分 ----- //
    Vector3 XY_Plane_Segment[2] =
    {
        // 始点
        Vector3(_mySegment_Start.x, _mySegment_Start.y, 0.0f),
        // 終点
        Vector3(_mySegment_End.x, _mySegment_End.y, 0.0f),
    };

    // ----- ZY平面の線分 ----- //
    Vector3 ZY_Plane_Segment[2] =
    {
        // 始点
        Vector3(_mySegment_Start.z, _mySegment_Start.y, 0.0f),
        // 終点
        Vector3(_mySegment_End.z, _mySegment_End.y, 0.0f),
    };

    // ----- XZ平面の線分 ----- //
    Vector3 XZ_Plane_Segment[2] = 
    {
        // 始点
        Vector3(_mySegment_Start.x, _mySegment_Start.z, 0.0f),
        // 終点
        Vector3(_mySegment_End.x, _mySegment_End.z, 0.0f),
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
