#include "EditScene.h"
#include "SceneManager.h"
#include "Text.h"
#include "KeyInput.h"

void Ctlan::EngineScene::EditScene::Init()
{
	// ===== 編集用カメラの生成 ===== //
	m_spectatorCamera = AddSceneObject<EngineObject::SpectatorCamera>(0, "SpectatorCamera");

	// ===== ロード処理 ===== //
	// シーンファイルを開く
	FILE* file;
	fopen_s(&file, "Assets\\SceneEditor.dat", "rb");

	// 開くことが出来た？
	if (file)
	{
		// データをロード
		fread(&m_sceneEditorData, sizeof(SceneEditorData), 1, file);
		// トランスフォーム情報を代入
		m_spectatorCamera->transform->position = m_sceneEditorData.transformComponent.position;
		m_spectatorCamera->transform->rotation = m_sceneEditorData.transformComponent.rotation;
		m_spectatorCamera->transform->scale = m_sceneEditorData.transformComponent.scale;
		// カメラ情報を代入
		Camera* cam = m_spectatorCamera->GetComponent<Camera>();
		cam->nearClip = m_sceneEditorData.cameraComponent.nearClip;
		cam->farClip = m_sceneEditorData.cameraComponent.farClip;
		cam->fieldOfView = m_sceneEditorData.cameraComponent.fieldOfView;
		fclose(file);
	}
	// 開くことが出来なかった
	else
	{
		// シーン編集に使うデータを作成
		m_sceneEditorData.transformComponent = *m_spectatorCamera->transform;
		m_sceneEditorData.cameraComponent = *m_spectatorCamera->GetComponent<Ctlan::PublicSystem::Camera>();
	}


	// ===== マニピュレーター用オブジェクトの生成 ===== //
	// ----- 移動 ----- //
	m_manipulator_MoveX = AddSceneObject<Ctlan::EngineObject::Manipulator::Manipulator_MoveX>(1, "Manipulator_MoveX");
	m_manipulator_MoveY = AddSceneObject<Ctlan::EngineObject::Manipulator::Manipulator_MoveY>(1, "Manipulator_MoveY");
	m_manipulator_MoveZ = AddSceneObject<Ctlan::EngineObject::Manipulator::Manipulator_MoveZ>(1, "Manipulator_MoveZ");
}

void Ctlan::EngineScene::EditScene::Uninit()
{
	// ===== セーブ処理 ===== //
	// シーン編集に使うデータを作成
	m_sceneEditorData.transformComponent = *m_spectatorCamera->transform;
	m_sceneEditorData.cameraComponent = *m_spectatorCamera->GetComponent<Camera>();

	// シーンファイルを開く
	FILE* file;
	fopen_s(&file, "Assets\\SceneEditor.dat", "wb");

	// 開くことが出来た？
	if (file)
	{
		fwrite(&m_sceneEditorData, sizeof(SceneEditorData), 1, file);
		fclose(file);
	}

	// シーンの基本的な終了処理を実行
	SceneBase::Uninit();
}

void Ctlan::EngineScene::EditScene::Update()
{
	// オブジェクトをクリックした？
	if (m_spectatorCamera->GetClickedObject() != nullptr)
	{
		// テキストではない？
		if (!m_spectatorCamera->GetClickedObject()->GetComponent<Ctlan::PublicSystem::Text>())
		{
			// ===== マニピュレーターの表示処理 ===== //
			// ----- 移動 ----- //
			// X軸方向
			m_manipulator_MoveX->isActive = true;
			m_manipulator_MoveX->transform->parent = m_spectatorCamera->GetClickedObject();
			// Y軸方向
			m_manipulator_MoveY->isActive = true;
			m_manipulator_MoveY->transform->parent = m_spectatorCamera->GetClickedObject();
			// Z軸方向
			m_manipulator_MoveZ->isActive = true;
			m_manipulator_MoveZ->transform->parent = m_spectatorCamera->GetClickedObject();
		}
		else
		{
			// ===== マニピュレーターの非表示処理 ===== //
			// ----- 移動 ----- //
			// X軸方向
			m_manipulator_MoveX->isActive = false;
			m_manipulator_MoveX->transform->parent = nullptr;
			// Y軸方向
			m_manipulator_MoveY->isActive = false;
			m_manipulator_MoveY->transform->parent = nullptr;
			// Z軸方向
			m_manipulator_MoveZ->isActive = false;
			m_manipulator_MoveZ->transform->parent = nullptr;
		}
	}
	else
	{
		// ===== マニピュレーターの非表示処理 ===== //
		// ----- 移動 ----- //
		// X軸方向
		m_manipulator_MoveX->isActive = false;
		m_manipulator_MoveX->transform->parent = nullptr;
		// Y軸方向
		m_manipulator_MoveY->isActive = false;
		m_manipulator_MoveY->transform->parent = nullptr;
		// Z軸方向
		m_manipulator_MoveZ->isActive = false;
		m_manipulator_MoveZ->transform->parent = nullptr;
	}

	// F1キーが押された？
	if (KeyInput::GetKeyDownTrigger(KeyName::F1))
	{
		isDemoPlay = isDemoPlay ? false : true;	// デモプレイ状態を切り替える
	}

	// 各スレッド内のオブジェクトリスト取得
	for (auto& objectList : m_sceneObjectList)
	{
		// リスト内のオブジェクト取得
		for (Ctlan::PrivateSystem::GameObject* object : objectList)
		{
			// アクティブ状態？
			if (object->isActive)
				object->UpdateBase();	// 更新処理
		}
	}
}

void Ctlan::EngineScene::EditScene::Draw()
{
	// 各スレッド内のオブジェクトリスト取得
	for (auto& objectList : m_sceneObjectList)
	{
		// リスト内のオブジェクト取得
		for (Ctlan::PrivateSystem::GameObject* object : objectList)
		{
			// アクティブ状態？
			if (object->isActive)
				object->DrawBase();	// 描画処理
		}
	}
}
