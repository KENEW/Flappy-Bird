#include "resource.h"
#include "DXUT.h"

#include "MenuScene.h"
#include "Director.h"
#include "Renderer.h"
#include "Sound.h"

HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{
    srand(time(NULL));
    Sound::GetIns()->soundpreloads();
	Director::GetIns()->DirectorInit();
    return S_OK;
}

void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
	Time::deltaTime = fElapsedTime * Time::scaleTime;
	Director::GetIns()->DirectorUpdate();
}

void CALLBACK OnD3D9FrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    HRESULT hr;
    V( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 100, 255, 255, 170 ), 1.0f, 0 ) );
    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
		Renderer::GetIns()->Render();
        V( pd3dDevice->EndScene() );
    }
}

void CALLBACK OnD3D9DestroyDevice( void* pUserContext )
{
	exit(0);
}

void CALLBACK OnMouse(bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{
	if (bLeftButtonDown) Director::GetIns()->nClick = 1;
	else if (!bLeftButtonDown) Director::GetIns()->nClick = 3;
}

INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int )
{
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    DXUTSetCallbackD3D9DeviceCreated( OnD3D9CreateDevice );
    DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );
    DXUTSetCallbackD3D9DeviceDestroyed( OnD3D9DestroyDevice );
    DXUTSetCallbackFrameMove( OnFrameMove );
	DXUTSetCallbackMouse( OnMouse );

    DXUTInit( true, true ); 
    DXUTSetHotkeyHandling( true, true, true );
    DXUTSetCursorSettings( false, true );
    DXUTCreateWindow( L"Flappy bird" );
    DXUTCreateDevice( true, SCW, SCH );

	Director::GetIns()->ChangeScene(new MenuScene());

    DXUTMainLoop();

    return DXUTGetExitCode();
}