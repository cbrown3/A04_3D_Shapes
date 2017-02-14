/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/08
----------------------------------------------*/

#include "RE\ReEngAppClass.h"

#ifdef FBXSDK_SHARED
#undef FBXSDK_SHARED
#endif

//Initializing the main program using winappi
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
	//Creating a ReEngAppClass object providing the arguments and the window handler
	ReEngAppClass Application(hInstance, lpCmdLine, nCmdShow);
	//RE_RUNNING the Application's Main Loop
	Application.Run();
	//Finalizing the Application
	return 0;
}