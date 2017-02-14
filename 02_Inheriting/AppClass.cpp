#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	//Using Base InitWindow method
	super::InitWindow("Inheriting (No keyboard control, close with Alt + F4)");
	//Changing the clear color
	m_v4ClearColor = vector4(0.0f);
}

void AppClass::InitVariables(void)
{
	//Enable ArcBall
	m_bArcBall = true;
	//Enable FPC
	//m_bFPC = true;
}