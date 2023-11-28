
#include "common.hlsl"

void main(VS_IN vin, out VS_OUT vout)
{   
    // ローカル座標をスクリーン座標へ変換
    vout.pos = float4(vin.Position.xyz, vin.Position.w); // ローカル座標
    
    // 輪郭線として表示するために、法線方向へ頂点を移動
    //（単純に拡縮で大きくすると見た目がおかしくなる）
    // 正規化された法線は１（メートル）で拡大が大きくなりすぎるため補正を入れる
    vout.pos.xyz += normalize(vin.Normal) * 0.0075f;
    
    vout.pos = mul(vout.pos, World);        // ワールド座標
    vout.pos = mul(vout.pos, View);         // ビュー座標
    vout.pos = mul(vout.pos, Projection);   // プロジェクション座標
    
    // ピクセルシェーダーで利用するUV座標を渡す
    vout.uv = vin.TexCoord;
    
    // ピクセルシェーダーで利用する法線を渡す
    // 法線はオブジェクトの回転に併せて回転されないとおかしな見た目になる
    // ワールド行列には移動成分も含まれるが移動を法線に適用してもおかしくなるので
    // 回転成分のみの行列となるように縮小して計算する。
    vout.normal = mul(vin.Normal, (float3x3) World);
}