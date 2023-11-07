#pragma once
/**
* @file		CalculationHit.h
* @brief	CalculationHit�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.02
*/
// ������������������������������������ //
// �@�@   �t�@�C���̃C���N���[�h        //
// ������������������������������������ //
#include "Vector3.h"
#include "Transform.h"

namespace PublicSystem
{
	/// <summary>
	/// �ΏۂƑΏۂ��������Ă��邩�ǂ������v�Z����@�\����������N���X	</summary>
	class CalculationHit
	{
		public:
			// ----- functions / �֐� ----- //
			// **  ���g�������̓����蔻��  ** //
			/// <summary>
			/// �����Ɛ������������Ă��邩���v�Z����	</summary>
			/// <param name = "mySegmentStart">
			/// ���g�Ƃ��Ĉ��������̎n�_	</param>
			/// <param name = "mySegmentEnd">
			/// ���g�Ƃ��Ĉ��������̏I�_	</param>
			/// <param name = "otherSegmentEnd">
			/// ����Ƃ��Ĉ��������̎n�_	</param>
			/// <param name = "otherSegmentEnd">
			/// ����Ƃ��Ĉ��������̏I�_	</param>
			/// <returns>
			/// �������Ă�����true�A�������Ă��Ȃ����false��Ԃ�	</returns>
			static bool SegmentToSegment(Vector3 mySegmentStart, Vector3 mySegmentEnd, Vector3 otherSegmentStart, Vector3 otherSegmentEnd);
			/// <summary>
			/// �����Ǝl�p�`���������Ă��邩���v�Z����
			/// </summary>
			/// <param name = "mySegmentStart">
			/// ���g�Ƃ��Ĉ��������̎n�_	</param>
			/// <param name = "mySegmentEnd">
			/// ���g�Ƃ��Ĉ��������̏I�_	</param>
			/// <param name = "otherRightTop">
			/// ����Ƃ��Ĉ����l�p�`�̉E�㒸�_	</param>
			/// <param name = "otherLeftBottom">
			/// ����Ƃ��Ĉ��������̍������_	</param>
			/// <returns>
			/// �������Ă�����true�A�������Ă��Ȃ����false��Ԃ�	</returns>
			static bool SegmentToQuadrangle(Vector3 mySegmentStart, Vector3 mySegmentEnd, Vector3 otherRightTop, Vector3 otherLeftBottom);
			/// <summary>
			/// �����ƘZ�ʑ̂��������Ă��邩���v�Z����	</summary>
			/// <param name = "mySegmentStart">
			/// ���g�Ƃ��Ĉ��������̎n�_	</param>
			/// <param name = "mySegmentEnd">
			/// ���g�Ƃ��Ĉ��������̏I�_	</param>
			/// <param name = "otherHexahedron">
			/// ����Ƃ��Ĉ����Z�ʑ̂�Transform���	</param>
			/// <returns>
			/// �������Ă�����true�A�������Ă��Ȃ����false��Ԃ�	</returns>
			static bool SegmentToHexahedron(Vector3 mySegment_Start, Vector3 mySegmentEnd, const Transform* otherHexahedron);

			// **  ���g���_�̓����蔻��  ** //
			/// <summary>
			/// �_�Ǝl�p�`���������Ă��邩���v�Z����	</summary>
			/// <param name = "myPoint">
			/// ���g�Ƃ��Ĉ����_�̍��W�l	</param>
			/// <param name = "otherRightTop">
			/// ����Ƃ��Ĉ����l�p�`�̉E�㒸�_	</param>
			/// <param name = "otherLeftBottom">
			/// ����Ƃ��Ĉ��������̍������_	</param>
			/// <returns>
			/// �������Ă�����true�A�������Ă��Ȃ����false��Ԃ�	</returns>
			static bool PointToQuadrangle(Vector3 myPoint, Vector3 otherRightTop, Vector3 otherLeftBottom);
	};
}

