
#include "common.hlsl"

void main(VS_IN vin, out VS_OUT vout)
{   
    // ���[�J�����W���X�N���[�����W�֕ϊ�
    vout.pos = float4(vin.Position.xyz, vin.Position.w); // ���[�J�����W
    
    // �֊s���Ƃ��ĕ\�����邽�߂ɁA�@�������֒��_���ړ�
    //�i�P���Ɋg�k�ő傫������ƌ����ڂ����������Ȃ�j
    // ���K�����ꂽ�@���͂P�i���[�g���j�Ŋg�傪�傫���Ȃ肷���邽�ߕ␳������
    vout.pos.xyz += normalize(vin.Normal) * 0.0075f;
    
    vout.pos = mul(vout.pos, World);        // ���[���h���W
    vout.pos = mul(vout.pos, View);         // �r���[���W
    vout.pos = mul(vout.pos, Projection);   // �v���W�F�N�V�������W
    
    // �s�N�Z���V�F�[�_�[�ŗ��p����UV���W��n��
    vout.uv = vin.TexCoord;
    
    // �s�N�Z���V�F�[�_�[�ŗ��p����@����n��
    // �@���̓I�u�W�F�N�g�̉�]�ɕ����ĉ�]����Ȃ��Ƃ������Ȍ����ڂɂȂ�
    // ���[���h�s��ɂ͈ړ��������܂܂�邪�ړ���@���ɓK�p���Ă����������Ȃ�̂�
    // ��]�����݂̂̍s��ƂȂ�悤�ɏk�����Čv�Z����B
    vout.normal = mul(vin.Normal, (float3x3) World);
}