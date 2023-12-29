#pragma once
/**
* @file		EditScene.h
* @brief	EditSceneNXÌwb_[t@C
* @author	Kojima, Kosei
* @date		2023.12.25
*/
//  //
// @@t@CÌCN[h@@ //
//  //
#include "SceneBase.h"

#include "SpectatorCamera.h"
#include "Manipulator_MoveX.h"


namespace yUnoEngine
{
	/// <summary>
	///	GfBbgV[	</summary>
	class EditScene : public SceneBase
	{
		public:
			// ----- functions / Ö ----- //
			void Init()
			{
				// ===== GfBbgpJÌ¶¬ ===== //
				AddSceneObject<SpectatorCamera>(0, "SpectatorCamera");
				
				// ===== }js[^[pIuWFNgÌ¶¬ ===== //
				// ----- Ú®n ----- //
				AddSceneObject<Manipulator::Manipulator_MoveX>(1, "Manipulator_MoveX");	// XûüÖÌÚ®
				//AddSceneObject<Manipulator::Manipulator_MoveX>(1, "Manipulator_MoveY");	// YûüÖÌÚ®
				//AddSceneObject<Manipulator::Manipulator_MoveX>(1, "Manipulator_MoveZ");	// ZûüÖÌÚ®
			}
	};
};

