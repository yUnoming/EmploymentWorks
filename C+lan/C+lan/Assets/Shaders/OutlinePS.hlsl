cbuffer outLiniColor : register(b0)
{
    float4 color;
}

// ���ŕ`�恨�֊s�̐F�ɂȂ�
float4 main() : SV_Target
{
    return color;
}