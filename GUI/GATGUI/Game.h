#pragma once
#include "pch.h"
#include "Network.h"

extern int width;
extern int height;
extern int port;

class Game {

public:
			Game(HWND hWnd);
			~Game();
	void	Update();
	void	Draw();
	void	AddString(wstring s);
	void	SaveString(string s);
	void	NextSection();

private:

	// DIRECTX
	ID3D11Device* ReturnDevice();
	ID3D11DeviceContext* ReturnContext();
	IDXGISwapChain * swapchain = nullptr;
	ID3D11Device * device = nullptr;
	ID3D11DeviceContext * context = nullptr;
	ID3D11RenderTargetView *backbuffer = nullptr;
	ID3D11DepthStencilView *zbuffer = nullptr;
	ID3D11Texture2D *pDepthBuffer = nullptr;
	ID3D11Texture2D *pBackBuffer = nullptr;

	// DIRECTXTK
	SpriteBatch* sb;
	SpriteFont* sf;
	ID3D11ShaderResourceView* tex [10];
	ID3D11ShaderResourceView* c1;
	ID3D11ShaderResourceView* b_circle;
	ID3D11ShaderResourceView* b_dpad;
	ID3D11ShaderResourceView* b_l_larger;	
	ID3D11ShaderResourceView* b_lsmall;
	ID3D11ShaderResourceView* b_smallecircle;
	ID3D11ShaderResourceView* b_square;

	// CLASS
	wstring stringList[256];
	int numberOfItems = 10;
	int currentItem = 0;
	int count = 0;
	bool filled = 0;

	// NETWORKING
	Network Session;
	USocket Socket;
	char bufff[sizeof(js_event)];
	js_event e;

	//CONTROLLER
	bool B_L1, B_L2, B_L3, B_R1, B_R2, B_R3;
	bool B_1, B_2, B_3, B_4;
	bool B_9, B_10, B_11, B_12;
	bool B_UP, B_DOWN, B_LEFT, B_RIGHT;
	float B_LX, B_LY, B_RX, B_RY;
	bool B_SET;
	bool debug;
	bool strDebug = 0;
	int section = 0;
	int countA, countB, countX, countY, countL, countR;

	bool flagA, flagB, flagX, flagY, flagL, flagR, flagSelect;
	int tt = 0;

	ofstream out;

	string prevStr = "";
	CommonStates* states;
	

};