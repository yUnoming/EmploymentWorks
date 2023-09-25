#pragma once
// ������������������������������������ //
// �@�@   �t�@�C���̃C���N���[�h        //
// ������������������������������������ //
#include "Vector3.h"
#include "Transform.h"

namespace PublicSystem
{
	/// <summary>
	/// �ΏۂƑΏۂ��������Ă��邩�ǂ������v�Z����@�\����������N���X
	/// </summary>
	class CalculationHit
	{
		public:
			// ----- functions / �֐� ----- //
			// **  �傪�����̓����蔻��  ** //
			/// <summary>
			/// �����Ɛ������������Ă��邩���v�Z����
			/// </summary>
			/// <param name = "�����P�F_mySegment_Start">
			/// �^���g�Ƃ��Ĉ��������̎n�_
			/// </param>
			/// <param name = "�����Q�F_mySegment_End">
			/// �^���g�Ƃ��Ĉ��������̏I�_
			/// </param>
			/// <param name = "�����R�F_otherSegment_End">
			/// �^����Ƃ��Ĉ��������̎n�_
			/// </param>
			/// <param name = "�����S�F_otherSegment_End">
			/// �^����Ƃ��Ĉ��������̏I�_
			/// </param>
			/// <returns>
			/// �������Ă�����true�A�������Ă��Ȃ����false��Ԃ�
			/// </returns>
			static bool SegmentToSegment(Vector3 _mySegment_Start, Vector3 _mySegment_End, Vector3 _otherSegment_Start, Vector3 _otherSegment_End);
			/// <summary>
			/// �����Ǝl�p�`���������Ă��邩���v�Z����
			/// </summary>
			/// <param name = "�����P�F_mySegment_Start">
			/// �^���g�Ƃ��Ĉ��������̎n�_
			/// </param>
			/// <param name = "�����Q�F_mySegment_End">
			/// �^���g�Ƃ��Ĉ��������̏I�_
			/// </param>
			/// <param name = "�����R�F_otherRightTop">
			/// �^����Ƃ��Ĉ����l�p�`�̉E�㒸�_
			/// </param>
			/// <param name = "�����S�F_otherLeftBottom">
			/// �^����Ƃ��Ĉ��������̍������_
			/// </param>
			/// <returns>
			/// �������Ă�����true�A�������Ă��Ȃ����false��Ԃ�
			/// </returns>
			static bool SegmentToQuadrangle(Vector3 _mySegment_Start, Vector3 _mySegment_End, Vector3 _otherRightTop, Vector3 _otherLeftBottom);
			/// <summary>
			/// �����ƘZ�ʑ̂��������Ă��邩���v�Z����
			/// </summary>
			/// <param name = "�����P�F_mySegment_Start">
			/// �^���g�Ƃ��Ĉ��������̎n�_
			/// </param>
			/// <param name = "�����Q�F_mySegment_End">
			/// �^���g�Ƃ��Ĉ��������̏I�_
			/// </param>
			/// <param name = "�����R�F_otherHexahedron">
			/// �^����Ƃ��Ĉ����Z�ʑ̂�Transform���
			/// </param>
			/// <returns>
			/// �������Ă�����true�A�������Ă��Ȃ����false��Ԃ�
			/// </returns>
			static bool SegmentToHexahedron(Vector3 _mySegment_Start, Vector3 _mySegment_End, const Transform* _otherHexahedron);

			// **  �傪�_�̓����蔻��  ** //
			/// <summary>
			/// �_�Ǝl�p�`���������Ă��邩���v�Z����
			/// </summary>
			/// <param name = "�����P�F_myPoint">
			/// �^���g�Ƃ��Ĉ����_�̍��W�l
			/// </param>
			/// <param name = "�����R�F_otherRightTop">
			/// �^����Ƃ��Ĉ����l�p�`�̉E�㒸�_
			/// </param>
			/// <param name = "�����S�F_otherLeftBottom">
			/// �^����Ƃ��Ĉ��������̍������_
			/// </param>
			/// <returns>
			/// �������Ă�����true�A�������Ă��Ȃ����false��Ԃ�
			/// </returns>
			static bool PointToQuadrangle(Vector3 _myPoint, Vector3 _otherRightTop, Vector3 _otherLeftBottom);
	};
}

