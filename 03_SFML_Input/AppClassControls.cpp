#include "AppClass.h"
void AppClass::ProcessKeyboard(void)
{
	bool bModifier = false;
	float fSpeed = 0.01f;
	//m_m4SelectedObject = m_pMeshMngr->GetModelMatrix(m_sSelectedObject);

#pragma region ON PRESS/RELEASE DEFINITION
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false;
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

#pragma region Camera Positioning
	if(bModifier)
		fSpeed *= 10.0f;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_pCameraMngr->MoveForward(fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_pCameraMngr->MoveForward(-fSpeed);
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_pCameraMngr->MoveSideways(-fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_pCameraMngr->MoveSideways(fSpeed);
#pragma endregion

#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL));
	ON_KEY_PRESS_RELEASE(F1, NULL, m_pCameraMngr->SetCameraMode(CAMPERSP));
	ON_KEY_PRESS_RELEASE(F2, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOZ));
	ON_KEY_PRESS_RELEASE(F3, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOY));
	ON_KEY_PRESS_RELEASE(F4, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOX));
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
	}
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
		m_bArcBall = true;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		m_bFPC = true;
}
void AppClass::ProcessJoystick(void)
{
	static uint uClock = m_pSystem->GenClock();

	static float fPitchLast = 0.0f;
	static float fRollLast = 0.0f;

	int nWiimote = 0;
	float fDelta = 0.0f;
	float fSpeed = 0.10f;

	float fAngleX = 0.0f;
	float fAngleY = 0.0f;

	float fCalibration = 15.0f; //Percentage of ignored values of the controller

	if (m_Wiimote[nWiimote].IsConnected())
	{
		m_Wiimote[nWiimote].RefreshState();
		static bool bLastA = false, bLastB = false, bLastPlus = false, bLastMinus = false,
			bLastUp = false, bLastDown = false, bLastLeft = false, bLastRight = false,
			bLastOne = false, bLastTwo = false, bLastHome = false, bLast4 = false, bLast5 = false;
#define ON_WIIMOTE_PRESS_RELEASE(button, pressed_action, released_action){  \
		bool pressed = m_Wiimote[nWiimote].Button.button();			\
		if(pressed){											\
			if(!bLast##button) pressed_action;}/*Just pressed? */\
		else if(bLast##button) released_action;/*Just released?*/\
		bLast##button = pressed; } //remember the state

		if (m_Wiimote[nWiimote].Button.Minus() && m_Wiimote[nWiimote].Button.Plus())
			PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL);
		
		if (m_pSystem->LapClock(uClock) > 1 / 100.0)
		{
			float fPitch = m_Wiimote[nWiimote].Acceleration.Orientation.Pitch;
			fPitch = (fPitch + fPitchLast) / 2.0f;
			float fRoll = m_Wiimote[nWiimote].Acceleration.Orientation.Roll;
			fRoll = (fRoll + fRollLast) / 2.0f;
			m_qArcBall = quaternion(vector3(glm::radians(fPitch), 0.0f, glm::radians(-fRoll)));
			fPitchLast = fPitch;
			fRollLast = fRoll;
			//m_pMeshMngr->PrintLine("Pitch: " + std::to_string(fPitch));
		}
	}
	
	sf::Joystick::update();
	if (sf::Joystick::isConnected(m_uPad))
	{
		UpdateJoystickType(); //check what controller is connected

		//Debug info
		if (true)
		{
			m_pMeshMngr->PrintLine(" ");
			m_pMeshMngr->PrintLine("Controller: " + std::to_string(m_uPad));
			switch (m_eController)
			{
			default:
			case Controller::C_360:
				m_pMeshMngr->PrintLine("Type: 360");
				break;
			case Controller::C_XBONE:
				m_pMeshMngr->PrintLine("Type: XBONE");
				break;
			case Controller::C_PS4:
				m_pMeshMngr->PrintLine("Type: PS4");
				break;
			}
			float fValue;
			fValue = sf::Joystick::getAxisPosition(m_uPad, m_eLeftTrigger);
			m_pMeshMngr->PrintLine("Left Trigger: " + std::to_string(fValue));
			fValue = sf::Joystick::getAxisPosition(m_uPad, m_eRightTrigger);
			m_pMeshMngr->PrintLine("Right Trigger: " + std::to_string(fValue));

			fValue = sf::Joystick::getAxisPosition(m_uPad, m_eLeftThumbH);
			m_pMeshMngr->PrintLine("Left ThumbH: " + std::to_string(fValue));
			fValue = sf::Joystick::getAxisPosition(m_uPad, m_eLeftThumbV);
			m_pMeshMngr->PrintLine("Left ThumbV: " + std::to_string(fValue));

			fValue = sf::Joystick::getAxisPosition(m_uPad, m_eRightThumbH);
			m_pMeshMngr->PrintLine("Right ThumbH: " + std::to_string(fValue));
			fValue = sf::Joystick::getAxisPosition(m_uPad, m_eRightThumbV);
			m_pMeshMngr->PrintLine("Right ThumbV: " + std::to_string(fValue));
		}
		static bool b4LastPressed = false, b5LastPressed = false;
#define ON_JOYSTICK_PRESS_RELEASE(button, pressed_action, released_action){  \
		bool pressed = sf::Joystick::isButtonPressed(nPad, button);			\
		if(pressed){											\
			if(!b##button##LastPressed) pressed_action;}/*Just pressed? */\
		else if(b##button##LastPressed) released_action;/*Just released?*/\
		b##button##LastPressed = pressed; } //remember the state

		//Exit the program by clicking both shoulders at the same time
		if (sf::Joystick::isButtonPressed(m_uPad, 4) && sf::Joystick::isButtonPressed(m_uPad, 5))
			exit(0);
		
		//reset camera by pressing both sticks at the same time
		if (sf::Joystick::isButtonPressed(m_uPad, 8) && sf::Joystick::isButtonPressed(m_uPad, 9))
		{
			m_pCameraMngr->SetPositionTargetAndView(
				vector3(0.0f, 2.5f, 15.0f),//Camera position
				vector3(0.0f, 2.5f, 0.0f),//What Im looking at
				REAXISY);//What is up
		}

		//Get the value of the Left thumb
		fDelta = sf::Joystick::getAxisPosition(m_uPad, m_eLeftThumbV);
		//Due to sensitivity, its is never 0, we do not want to accidentally move,
		//so we ignore values smaller than the calibration
		if (fDelta > -fCalibration && fDelta < fCalibration)
			fDelta = 0.0f;
		//The reported value goes from -100(up) to 100(down) but we need it between
		//fSpeed and -fSpeed, so we map the value to that range
		fDelta = MapValue(fDelta, -100.0f, 100.0f, fSpeed, -fSpeed);
		//Apply the delta to the camera
		m_pCameraMngr->MoveForward(fDelta);

		//Same method as for vertical but now horizontal
		fDelta = sf::Joystick::getAxisPosition(m_uPad, m_eLeftThumbH);
		if (fDelta > -fCalibration && fDelta < fCalibration)
			fDelta = 0.0f;
		fDelta = MapValue(fDelta, -100.0f, 100.0f, -fSpeed, fSpeed);
		m_pCameraMngr->MoveSideways(fDelta);
		m_pMeshMngr->PrintLine("fSpeed: " + std::to_string(fDelta));

		//Calculate orientation of the camera, same as above
		fDelta = -sf::Joystick::getAxisPosition(m_uPad, m_eRightThumbV);
		if (fDelta > -fCalibration && fDelta < fCalibration)
			fDelta = 0.0f;
		fAngleX = MapValue(fDelta, -100.0f, 100.0f, -fSpeed * 3.0f, fSpeed * 3.0f);
		m_pCameraMngr->ChangePitch(fAngleX);

		fDelta = sf::Joystick::getAxisPosition(m_uPad, m_eRightThumbH);
		if (fDelta > -fCalibration && fDelta < fCalibration)
			fDelta = 0.0f;
		fAngleY = MapValue(fDelta, -100.0f, 100.0f, fSpeed * 3.0f, -fSpeed * 3.0f);
		m_pCameraMngr->ChangeYaw(fAngleY);
				
		//UpdateView
		m_pCameraMngr->CalculateView();
	}
	
}
void AppClass::UpdateJoystickType(void)
{
	if (sf::Joystick::isConnected(m_uPad))
	{
		sf::Joystick::update();
		/*
		Check if PS4 Controller
		360 Controllers use a single axis for their trigger, which SFML reports as Z the native value of Z
		in 360 controllers starts at Z and grow till +100 on the left trigger and -100 on the right trigger
		thus not reporting a value for the V axis (will not return 0 either but it would be a really small value).
		Pressing both triggers will cause the Z value to go near 0 (not really 0 because rounding issues). On the
		other hand, XBONE and PS4 controllers have an extra axis to handle each trigger and they are responding
		with values that goes between -100 (when not pressed) and 100 (when fully pressed). If this is a PS4
		controller, without pressing anything V and U will have a native value of -100. Thumb sticks can go from
		-100 to a 100 extending both horizontally and vertically but diagonally they cant go further than
		-75,-75 to 75,75
		*/
		if (sf::Joystick::getAxisPosition(m_uPad, sf::Joystick::Axis::V) < -80 &&
			sf::Joystick::getAxisPosition(m_uPad, sf::Joystick::Axis::U) < -80)
		{
			m_eController = Controller::C_PS4;
		}

		/*
		Check if XBONE Controller
		XBONE controllers and PS4 controllers have their Right thumb and trigger analogs switched.
		tumbs will report V,U and triggers Z,R
		*/
		if (sf::Joystick::getAxisPosition(m_uPad, sf::Joystick::Axis::Z) < -80 &&
			sf::Joystick::getAxisPosition(m_uPad, sf::Joystick::Axis::R) < -80)
		{
			m_eController = Controller::C_XBONE;
		}
	}

	//Some enums because name are easier to remember than axis
	switch (m_eController)
	{
	case Controller::C_PS4:
		m_eLeftTrigger = sf::Joystick::Axis::V;
		m_eRightTrigger = sf::Joystick::Axis::U;

		m_eLeftThumbH = sf::Joystick::Axis::X;
		m_eLeftThumbV = sf::Joystick::Axis::Y;

		m_eRightThumbH = sf::Joystick::Axis::Z;
		m_eRightThumbV = sf::Joystick::Axis::R;
		break;
	case Controller::C_XBONE:
		m_eLeftTrigger = sf::Joystick::Axis::Z;
		m_eRightTrigger = sf::Joystick::Axis::R;

		m_eLeftThumbH = sf::Joystick::Axis::X;
		m_eLeftThumbV = sf::Joystick::Axis::Y;

		m_eRightThumbH = sf::Joystick::Axis::V;
		m_eRightThumbV = sf::Joystick::Axis::U;
		break;
	default:
	case Controller::C_360:
		m_eLeftTrigger = sf::Joystick::Axis::Z;
		m_eRightTrigger = sf::Joystick::Axis::Z;

		m_eLeftThumbH = sf::Joystick::Axis::X;
		m_eLeftThumbV = sf::Joystick::Axis::Y;

		m_eRightThumbH = sf::Joystick::Axis::U;
		m_eRightThumbV = sf::Joystick::Axis::R;
		break;
	}
}