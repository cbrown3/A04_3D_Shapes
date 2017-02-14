
/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/08
----------------------------------------------*/
#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include "RE\ReEngAppClass.h"
#include "WiiYourself\wiimote.h"
#include <SFML\Graphics.hpp>
//#include <chrono>

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

enum Controller
{
	C_360,
	C_XBONE,
	C_PS4,
};

class AppClass : public ReEngAppClass
{
	static const int m_nWiimotes = 1;
	wiimote m_Wiimote[m_nWiimotes]; //For holding the wiimote controller
	Controller m_eController = Controller::C_360;
	uint m_uPad = 0;
	
public:
	//Axis options
	sf::Joystick::Axis m_eLeftTrigger = sf::Joystick::Axis::V;
	sf::Joystick::Axis m_eRightTrigger = sf::Joystick::Axis::U;

	sf::Joystick::Axis m_eLeftThumbH = sf::Joystick::Axis::X;
	sf::Joystick::Axis m_eLeftThumbV = sf::Joystick::Axis::Y;
	
	sf::Joystick::Axis m_eRightThumbH = sf::Joystick::Axis::Z;
	sf::Joystick::Axis m_eRightThumbV = sf::Joystick::Axis::R;

	typedef ReEngAppClass super;
	/*
	USAGE: Constructor
	ARGUMENTS:
	- HINSTANCE hInstance -> Instance of the window
	- LPWSTR lpCmdLine -> Command line
	- int nCmdShow -> Number or arguments
	- bool a_bConsole = false -> create command window flag
	OUTPUT: ---
	*/
	AppClass(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow, bool a_bUsingConsole = false) : super(hInstance, lpCmdLine, nCmdShow, a_bUsingConsole) {}
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~AppClass(void) { Release(); }
	/*
	USAGE: Reads the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ReadConfig(void) final {}
	/*
	USAGE: Writes the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void WriteConfig(void) final {}
	/*
	USAGE: Initialize ReEng variables necessary to create the window
	ARGUMENTS: String a_sWindowName -> Name of the window
	OUTPUT: ---
	*/
	virtual void InitWindow(String a_sWindowName) final;
	/*
	USAGE: Initializes user specific variables, this is executed right after InitApplicationVariables,
	the purpose of this member function is to initialize member variables specific for this lesson
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void InitVariables(void) final;
	/*
	USAGE: Updates the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Update(void) final;
	/*
	USAGE: Displays the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Display(void) final;
	/*
	USAGE: Manage the response of key presses
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ProcessKeyboard(void) final;
	/*
	USAGE: Manage the response of key presses and mouse position
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ProcessMouse(void) final;
	/*
	USAGE: Manage the response of gamepad controllers
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ProcessJoystick(void) final;
	/*
	USAGE: Manage the type gamepad connected
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void UpdateJoystickType(void) final;
};

#endif //__APPLICATION_H_