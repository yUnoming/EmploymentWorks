#pragma once
/**
* @file		SpectatorCamera.h
* @brief	SpectatorCameraNXΜwb_[t@C
* @author	Kojima, Kosei
* @date		2023.11.01
*/
//  //
// @@t@CΜCN[h@@ //
//  //
#include "GameObject.h"


/// <summary>
///	GWΰΕg€JIuWFNg	</summary>
class SpectatorCamera : public GameObject
{
	private:
		// ----- variables / Ο ----- //
		///<summary>
		///NbN³κ½IuWFNgπγό·ιΟ	</summary>
		GameObject* m_clickedObject = nullptr;

	public:
		void Init();
		void Update();
};

