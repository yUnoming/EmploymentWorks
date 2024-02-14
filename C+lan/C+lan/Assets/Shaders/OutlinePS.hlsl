cbuffer outLiniColor : register(b0)
{
    float4 color;
}

// •‚Å•`‰æ¨—ÖŠs‚ÌF‚É‚È‚é
float4 main() : SV_Target
{
    return color;
}