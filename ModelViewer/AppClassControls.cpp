#include "AppClass.h"
void AppClass::ProcessKeyboard(void)
{
	bool bModifier = false;
	float fSpeed = 0.01f;

	int nMesh = m_pMeshMngr->IdentifyInstance(m_sSelectedObject);

#pragma region ON PRESS/RELEASE DEFINITION
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false, bLastF = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

#pragma region Modifiers
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		bModifier = true;
#pragma endregion

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		m_qArcBall = m_qOrientation = quaternion();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		if (!bModifier)
			m_qOrientation = m_qOrientation * quaternion(vector3(glm::radians(1.0f), 0.0f, 0.0f));
		else
			m_qOrientation = m_qOrientation * quaternion(vector3(glm::radians(-1.0f), 0.0f, 0.0f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		if (!bModifier)
			m_qOrientation = m_qOrientation * quaternion(vector3(0.0f, glm::radians(1.0f), 0.0f));
		else
			m_qOrientation = m_qOrientation * quaternion(vector3(0.0f, glm::radians(-1.0f), 0.0f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		if (!bModifier)
			m_qOrientation = m_qOrientation * quaternion(vector3(0.0f, 0.0f, glm::radians(1.0f)));
		else
			m_qOrientation = m_qOrientation * quaternion(vector3(0.0f, 0.0f, glm::radians(-1.0f)));
	}

	//Model States
#pragma region Model States
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState(m_sSelectedObject, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState(m_sSelectedObject, 1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState(m_sSelectedObject, 2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState(m_sSelectedObject, 3);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState(m_sSelectedObject, 4);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState(m_sSelectedObject, 5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState(m_sSelectedObject, 6);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState(m_sSelectedObject, 7);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState(m_sSelectedObject, 8);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState(m_sSelectedObject, 9);
	}
#pragma endregion

#pragma region Model Loading
	//Model Loading
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
	{
		FileReaderClass pFile;
#ifdef FBXSDK_SHARED
		String sFileName = pFile.RetriveFileNameFromExplorer(L"FBX Files (*.fbx)\0*.fbx\0BTO Files (*.bto)\0*.bto\0ATO Files (*.ato)\0*.ato\0OBJ Files (*.obj)\0*.obj\0", L"fbx");
#else
		String sFileName = pFile.RetriveFileNameFromExplorer(L"BTO Files (*.bto)\0*.bto\0ATO Files (*.ato)\0*.ato\0OBJ Files (*.obj)\0*.obj\0", L"bto");
#endif

		if (sFileName != "")
		{
			bool bThreaded = m_pSystem->GetThreaded();
			m_pSystem->SetThreaded(false);

			m_pMeshMngr->m_pModelMngr->DeleteInstance();
			m_sSelectedObject = pFile.GetFileName(sFileName);
			m_pMeshMngr->LoadModel(sFileName, m_sSelectedObject, true);

			bool bTest = m_pMeshMngr->IsInstanceCreated(m_sSelectedObject);
			if (bTest)
			{
				//BoundingObjectClass* pBO = m_pMeshMngr->GetBoundingObject(m_sSelectedObject);
				//vector3 v3Centroid = pBO->GetCentroidGlobal();
				//vector3 v3HalfWidth = pBO->GetHalfWidth();
				//float fSize = v3HalfWidth.x;
				//if (fSize < v3HalfWidth.y)
				//	fSize = v3HalfWidth.y;
				//if (fSize < v3HalfWidth.z)
				//	fSize = v3HalfWidth.z;
				//m_pCameraMngr->SetPositionTargetAndView(v3Centroid + REAXISZ * fSize * 3.5f, v3Centroid, REAXISY);
				//m_qArcBall = quaternion();
			}

			m_pSystem->SetThreaded(bThreaded);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F6))
	{
		if (m_sSelectedObject != "")
		{
			bool bThreaded = m_pSystem->GetThreaded();
			m_pSystem->SetThreaded(false);
			FileReaderClass pFile;
			String sFileName = pFile.IndicateFileNameOnExplorer(L"BTO Files (*.bto)\0*.bto\0ATO Files (*.ato)\0*.ato\0All Files (*.*)\0*.*\0", L"bto");
			String sExtension = FileReaderClass::GetExtension(sFileName);
			if (sFileName != "")
			{
				if(sExtension == "bto")
					m_pMeshMngr->SaveModel(sFileName, BTO, m_sSelectedObject, true);
				else
					m_pMeshMngr->SaveModel(sFileName, ATO, m_sSelectedObject, true);
			}

			m_pSystem->SetThreaded(bThreaded);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F9))
	{
		m_pMeshMngr->m_pModelMngr->DeleteInstance(m_sSelectedObject);
		m_sSelectedObject = "";
	}
#pragma endregion

#pragma region Camera Positioning
	if(bModifier)
		fSpeed *= 10.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_pCameraMngr->MoveForward(fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_pCameraMngr->MoveForward(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_pCameraMngr->MoveSideways(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_pCameraMngr->MoveSideways(fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		m_pCameraMngr->MoveVertical(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		m_pCameraMngr->MoveVertical(fSpeed);
#pragma endregion

#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL));
	ON_KEY_PRESS_RELEASE(F1, NULL, m_pCameraMngr->SetCameraMode(CAMPERSP));
	ON_KEY_PRESS_RELEASE(F2, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOZ));
	ON_KEY_PRESS_RELEASE(F3, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOY));
	ON_KEY_PRESS_RELEASE(F4, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOX));
	if (bModifier)
		ON_KEY_PRESS_RELEASE(F, NULL, m_pCameraMngr->SetFPS(false))
	else
		ON_KEY_PRESS_RELEASE(F, NULL, m_pCameraMngr->SetFPS(true))
#pragma endregion
}
void AppClass::ProcessMouse(void)
{
	m_bArcBall = false;
	m_bFPC = false;
#pragma region ON_MOUSE_PRESS_RELEASE
	static bool	bLastLeft = false, bLastMiddle = false, bLastRight = false;
#define ON_MOUSE_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion
	bool bLeft = false;
	ON_MOUSE_PRESS_RELEASE(Left, NULL, bLeft = true)
	if (bLeft)
	{
		//Turn off the visibility of all BOs for all instances
		m_pMeshMngr->SetVisibleBO(BD_NONE, "ALL", -1);
		//Get the Position and direction of the click on the screen
		std::pair<vector3, vector3> pair =
			m_pCameraMngr->GetClickAndDirectionOnWorldSpace(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
		float fDistance = 0;//Stores the distance to the first colliding object
		m_selection = m_pMeshMngr->IsColliding(pair.first, pair.second, fDistance);

		//If there is a collision
		if (m_selection.first >= 0)
		{
			//Turn on the BO of the group
			m_pMeshMngr->SetVisibleBO(BD_OB, m_selection.first, m_selection.second);

			//Turn of the BO of the instance but not the group
			m_pMeshMngr->SetVisibleBO(BD_NONE, m_selection.first, -2);
		}
	}
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
		m_bArcBall = true;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		m_bFPC = true;
}
