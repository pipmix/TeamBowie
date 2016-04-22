#include "Game.h"

Game::Game(HWND hWnd) {
		
	int width = 920;
	int height = 680;





		//SWAPCHAIN
		DXGI_SWAP_CHAIN_DESC scd;
		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
		scd.BufferCount = 1;
		scd.BufferDesc.Width = width;
		scd.BufferDesc.Height = height;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferDesc.RefreshRate.Numerator = 60;
		scd.BufferDesc.RefreshRate.Denominator = 1;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.OutputWindow = hWnd;
		scd.SampleDesc.Count = 1;
		scd.SampleDesc.Quality = 0;
		scd.Windowed = TRUE;
		D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, 0, 0, D3D11_SDK_VERSION, &scd, &swapchain, &device, NULL, &context);

		//DEPTH STENCIL
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
		ZeroMemory(&dsvd, sizeof(dsvd));
		dsvd.Format = DXGI_FORMAT_D32_FLOAT;
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
		device->CreateDepthStencilView(pDepthBuffer, &dsvd, &zbuffer);

		//BACKBUFFER

		swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		device->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
		pBackBuffer->Release();
		context->OMSetRenderTargets(1, &backbuffer, zbuffer);


		//VIEWPORT
		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = width;
		viewport.Height = height;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		context->RSSetViewports(1, &viewport);

		//DEPTH BUFFER
		D3D11_TEXTURE2D_DESC texd;
		ZeroMemory(&texd, sizeof(texd));
		texd.Width = width;
		texd.Height = height;
		texd.ArraySize = 1;
		texd.MipLevels = 1;
		texd.SampleDesc.Count = 4;
		texd.Format = DXGI_FORMAT_D32_FLOAT;
		texd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		device->CreateTexture2D(&texd, NULL, &pDepthBuffer);


		sb = new SpriteBatch(context);

		sf = new SpriteFont(device,L"BerlienSans12.spritefont");


		CreateDDSTextureFromFile(device, L"cont.dds", NULL, &c1, NULL);
		CreateDDSTextureFromFile(device, L"circle.dds", NULL, &b_circle, NULL);
		CreateDDSTextureFromFile(device, L"dpad.dds", NULL, &b_dpad, NULL);
		CreateDDSTextureFromFile(device, L"l_larger.dds", NULL, &b_l_larger, NULL);
		CreateDDSTextureFromFile(device, L"lsmall.dds", NULL, &b_lsmall, NULL);
		CreateDDSTextureFromFile(device, L"smallcircle.dds", NULL, &b_smallecircle, NULL);
		CreateDDSTextureFromFile(device, L"square.dds", NULL, &b_square, NULL);

		
		
		
		stringList[0] = L"test";
		stringList[1] = L"test";
		



		slen = sizeof(si_other);

		
		AddString(L"Initialising Winsock...");
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0){
			AddString(L"Failed. Error Code :");
			exit(EXIT_FAILURE);
		}
		AddString(L"Initialised.");


		if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
			AddString(L"Could not create socket");
		
		AddString(L"Socket created");

		//Prepare the sockaddr_in structure
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons(PORT);

		bind(s, (struct sockaddr *)&server, sizeof(server));
		//Bind
		//if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
		//{
		//	AddString(L"Bind failed with error code");
		//	exit(EXIT_FAILURE);
		//}
		AddString(L"Bind done");


		//keyboard = (new Keyboard);









}

void Game::AddString(wstring s) {

	stringList[currentItem] = s;
	
	currentItem++;
	if (currentItem > 240) {
		currentItem = 0;
		filled = 1;
	}



}


Game::~Game() {

	closesocket(s);
	WSACleanup();



	swapchain->Release();
	backbuffer->Release();
	device->Release();
	context->Release();


}


void Game::Update() {


	
		//AddString(L"Waiting for data...");

		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);

		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
		{

			AddString(L"recvfrom() failed with error code" + to_wstring(count++));
			//exit(EXIT_FAILURE);
		}

		//print details of the client/peer and the data received
		//printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		//printf("Data: %s\n", buf);

		//now reply the client with the same data
		if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR)
		{
			//AddString(L"sendto() failed with error code");
			//exit(EXIT_FAILURE);
		}
	


}

void Game::Draw(){

	float fill[4] = { 0.0f, 0.0f, 0.25f, 1.0f };
	context->ClearRenderTargetView(backbuffer, fill);

	context->OMSetRenderTargets(1, &backbuffer, zbuffer );

	sb->Begin();
	sb->Draw(c1, XMFLOAT2(0.0f, 0.0f));
	sb->Draw(b_circle, XMFLOAT2(710.0f, 235.0f));
	sb->Draw(b_dpad, XMFLOAT2(400.0f, 240.0f));
	sb->Draw(b_l_larger, XMFLOAT2(400.0f, 0.0f));
	sb->Draw(b_lsmall, XMFLOAT2(0.0f, 0.0f));
	sb->Draw(b_smallecircle, XMFLOAT2(0.0f, 0.0f));
	sb->Draw(b_square, XMFLOAT2(0.0f, 0.0f));




	sf->DrawString(sb, L"GAME ANAYLTICS TOOL", XMFLOAT2(100, 100));

	int tW = 30;
	int tH = 460;

	int tCurrent = currentItem;

	for (int i = 0; i < numberOfItems; i++) {
		
		int y = tCurrent;
		if(y <= 9 && filled == 0)sf->DrawString(sb, stringList[i].c_str(), XMFLOAT2(tW, tH));
		if (y <= 9 && filled == 1) {

			int tt = (tCurrent - 10) + i;
			if (tt < 0)tt += 240;

			sf->DrawString(sb, stringList[tt].c_str(), XMFLOAT2(tW, tH));
		}
		else if ( y >=10 && y <= 240 )sf->DrawString(sb, stringList[(tCurrent - 10) + i].c_str(), XMFLOAT2(tW, tH));
		
		
		
		

		tH += 20;

	}



	sb->End();


	swapchain->Present(0, 0);
}

ID3D11Device * Game::ReturnDevice()
{
	return device;
}

ID3D11DeviceContext * Game::ReturnContext()
{
	return context;
}

