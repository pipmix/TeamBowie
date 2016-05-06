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

		sf = new SpriteFont(device,L"Assets/BerlienSans12.spritefont");


		CreateDDSTextureFromFile(device, L"Assets/cont.dds", NULL, &c1, NULL);
		CreateDDSTextureFromFile(device, L"Assets/circle.dds", NULL, &b_circle, NULL);
		CreateDDSTextureFromFile(device, L"Assets/dpad.dds", NULL, &b_dpad, NULL);
		CreateDDSTextureFromFile(device, L"Assets/l_larger.dds", NULL, &b_l_larger, NULL);
		CreateDDSTextureFromFile(device, L"Assets/lsmall.dds", NULL, &b_lsmall, NULL);
		CreateDDSTextureFromFile(device, L"Assets/smallcircle.dds", NULL, &b_smallecircle, NULL);
		CreateDDSTextureFromFile(device, L"Assets/square.dds", NULL, &b_square, NULL);

		port2 = 9787;
		
		Socket.Bind(port2);
		AddString(L"Bind done");




		B_SET = B_UP = B_DOWN = B_LEFT = B_RIGHT = B_L1 = B_L2 = B_L3 = B_R1 = B_R2 = B_R3 = B_1 = B_2 = B_3 = B_4 = B_9 = B_10 = B_11 = B_12 = false;
		B_LX = B_LY = B_RX = B_RY = 0.0f;


		debug = false;


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





	swapchain->Release();
	backbuffer->Release();
	device->Release();
	context->Release();


}


void Game::Update() {







	sockaddr_in add = Socket.RecvFrom(bufff, sizeof(js_event));



	memcpy(&e, bufff, sizeof(js_event));

	if (e.type == 0x01) {

		if (e.value == 0)B_SET = 0;
		else B_SET = 1;


		switch (e.number) {
		case 0:
			if(debug)AddString(L"Button 1");
			B_1 = B_SET;
			break;
		case 1:
			if (debug)AddString(L"Button 2");
			B_2 = B_SET;
			break;
		case 2:
			if (debug)AddString(L"Button 3");
			B_3 = B_SET;
			break;
		case 3:
			if (debug)AddString(L"Button 4");
			B_4 = B_SET;
			break;
		case 4:
			if (debug)AddString(L"L1");
			B_L1 = B_SET;
			break;
		case 5:
			if (debug)AddString(L"R1");
			B_R1 = B_SET;
			break;
		case 6:
			if (debug)AddString(L"L2");
			B_L2 = B_SET;
			break;
		case 7:
			if (debug)AddString(L"R2");
			B_R2 = B_SET;
			break;
		case 8:
			if (debug)AddString(L"Select");
			B_9 = B_SET;
			break;
		case 9:
			if (debug)AddString(L"Start");
			B_10 = B_SET;
			break;
		case 10:
			if (debug)AddString(L"L3");
			B_L3 = B_SET;
			break;
		case 11:
			if (debug)AddString(L"R3");
			B_R3 = B_SET;
			break;
		}


	}
	else if (e.type == 0x02) {
		switch (e.number) {
		case 0:
			AddString(L"Left X-Axis:");
			break;
		case 1:
			AddString(L"Left Y-Axis:");
			break;
		case 2:
			AddString(L"Right X-Axis:");
			break;
		case 3:
			AddString(L"Right Y-Axis:");
			break;
		}
		if (e.value == 0)AddString(L"  ");


		AddString(L"at Time:");
	}
	else if (e.type == 0x80) {
	}




	


}

void Game::Draw(){

	float fill[4] = { 0.0f, 0.0f, 0.25f, 1.0f };
	context->ClearRenderTargetView(backbuffer, fill);

	context->OMSetRenderTargets(1, &backbuffer, zbuffer );

	sb->Begin();
	sb->Draw(c1, XMFLOAT2(0.0f, 0.0f));
		if(B_L1)sb->Draw(b_lsmall, XMFLOAT2(405.0f, 80.0f));
		if (B_L2)sb->Draw(b_l_larger, XMFLOAT2(405.0f, 37.0f));
		if (B_L3);
		if (B_R1)sb->Draw(b_lsmall, XMFLOAT2(731.0f, 80.0f));
		if (B_R2)sb->Draw(b_l_larger, XMFLOAT2(733.0f, 37.0f));
		if (B_R3);
		if (B_1)sb->Draw(b_circle, XMFLOAT2(740.0f, 176.0f));
		if (B_2)sb->Draw(b_circle, XMFLOAT2(702.0f, 216.0f));
		if (B_3)sb->Draw(b_circle, XMFLOAT2(740.0f, 255.0f));
		if (B_4)sb->Draw(b_circle, XMFLOAT2(783.0f, 216.0f));
		if (B_9)sb->Draw(b_square, XMFLOAT2(537.0f, 237.0f));
		if (B_10)sb->Draw(b_square, XMFLOAT2(634.0f, 237.0f));
		if (B_11)sb->Draw(b_square, XMFLOAT2(0.0f, 0.0f));
		if (B_12)sb->Draw(b_square, XMFLOAT2(0.0f, 0.0f));
		if (B_UP)sb->Draw(b_dpad, XMFLOAT2(424.0f, 195.0f));
		if (B_DOWN)sb->Draw(b_dpad, XMFLOAT2(424.0f, 255.0f));
		if (B_LEFT)sb->Draw(b_dpad, XMFLOAT2(395.0f, 224.0f));
		if (B_RIGHT)sb->Draw(b_dpad, XMFLOAT2(457.0f, 224.0f));


	//float B_LX, B_LY, B_RX, B_LY; sb->Draw(b_smallecircle, XMFLOAT2(0.0f, 0.0f));


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

