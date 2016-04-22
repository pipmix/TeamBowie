#pragma once
#include "pch.h"



class Game {


public:

			Game(HWND hWnd);
			~Game();
	void	Update();
	void	Draw();

	void	AddString(wstring s);




private:

	ID3D11Device* ReturnDevice();
	ID3D11DeviceContext* ReturnContext();

private:
	IDXGISwapChain * swapchain = nullptr;
	ID3D11Device * device = nullptr;
	ID3D11DeviceContext * context = nullptr;
	ID3D11RenderTargetView *backbuffer = nullptr;
	ID3D11DepthStencilView *zbuffer = nullptr;
	ID3D11Texture2D *pDepthBuffer = nullptr;

	ID3D11Texture2D *pBackBuffer = nullptr;



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



	// SOCKET

	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;



	wstring stringList[256];

	int numberOfItems = 10;

	int currentItem = 0;

	int count = 0;

	bool filled = 0;


	// socket

	SOCKET s;
	struct sockaddr_in server, si_other;
	int slen, recv_len;
	char buf[BUFLEN];
	WSADATA wsa;


	std::unique_ptr<Keyboard> keyboard;








};
