#include "Game.h"


void strConvert(std::wstring &ws, const std::string &s){
	wstring wsTmp(s.begin(), s.end());
	ws = wsTmp;
}

Game::Game(HWND hWnd) {
		
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


		sb = new SpriteBatch(context);
		sf = new SpriteFont(device,L"Assets/BerlienSans14.spritefont");

		CreateDDSTextureFromFile(device, L"Assets/cont.dds", NULL, &c1, NULL);
		CreateDDSTextureFromFile(device, L"Assets/circle.dds", NULL, &b_circle, NULL);
		CreateDDSTextureFromFile(device, L"Assets/dpad.dds", NULL, &b_dpad, NULL);
		CreateDDSTextureFromFile(device, L"Assets/l_larger.dds", NULL, &b_l_larger, NULL);
		CreateDDSTextureFromFile(device, L"Assets/lsmall.dds", NULL, &b_lsmall, NULL);
		CreateDDSTextureFromFile(device, L"Assets/smallcircle.dds", NULL, &b_smallecircle, NULL);
		CreateDDSTextureFromFile(device, L"Assets/square.dds", NULL, &b_square, NULL);

		states = new CommonStates(device);


		wstring tempWs = L"Binding to port " + to_wstring(port) ;
		AddString(tempWs);


		int iResult = Socket.Bind(port);
		if (iResult != 0) {
			AddString(L"Bind failed");
		}
		else AddString(L"bind Success");

		//AddString(L"Bind done");

		B_SET = B_UP = B_DOWN = B_LEFT = B_RIGHT = B_L1 = B_L2 = B_L3 = B_R1 = B_R2 = B_R3 = B_1 = B_2 = B_3 = B_4 = B_9 = B_10 = B_11 = B_12 = false;
		B_LX = B_LY = B_RX = B_RY = 0.0f;
		countA = countB = countX = countY = countL = countR = 0;
		debug = false;
		flagA = flagB = flagX = flagY = flagL = flagR = flagSelect = 0;


		time_t t = time(0);   // get time now

		struct tm * now = localtime(&t);


		string dateStr = to_string(now->tm_year + 1900) + "-" + to_string(now->tm_mon + 1) + "-" + to_string(now->tm_mday);
			
		


		time_t  timev;
		time(&timev);
		out.open("output_" + dateStr + ".txt");
}

void Game::AddString(wstring s) {

	stringList[currentItem] = s;
	currentItem++;
	if (currentItem > 240) {
		currentItem = 0;
		filled = 1;
	}
}

void Game::SaveString(string s) {


	out << s << endl;



}

Game::~Game() {
	out.close();
	swapchain->Release();
	backbuffer->Release();
	device->Release();
	context->Release();
}


void Game::Update() {

	while (1) {

		int receivedBytes = Socket.RecvFrom(bufff, sizeof(js_event));


		if (receivedBytes == -1)return;


		memcpy(&e, bufff, sizeof(js_event));


	

		string save;
		//wstring wsave = to_wstring(e.number) + L"  " + to_wstring(e.time) + L"  " + to_wstring(e.type) + L"  " + to_wstring(e.value);
		//string save = to_string(e.number) + "  " + to_string(e.time) + "  " + to_string(e.type) + "  " + to_string(e.value);



		if (e.type == 0x01) {

			if (e.value == 0)B_SET = 0;
			else B_SET = 1;


			switch (e.number) {
			case 0:
				save += "X,";
				if (debug)AddString(L"Button 1");
				if (flagX == 1)
					if (B_SET == 0) {
						countX++;
						flagX = 0;
					}
				B_2 = B_SET;
				if (B_SET == 1)flagX = 1;

				break;
			case 1:
				save += "A,";
				if (debug)AddString(L"Button 2");
				if (flagA == 1)
					if (B_SET == 0) {
						countA++;
						flagA = 0;
					}
				B_3 = B_SET;
				if (B_SET == 1)flagA = 1;
				break;
			case 2:
				save += "B,";
				if (debug)AddString(L"Button 3");
				if (flagB == 1)
					if (B_SET == 0) {
						countB++;
						flagB = 0;
					}
				B_4 = B_SET;
				if (B_SET == 1)flagB = 1;
				break;
			case 3:
				save += "Y,";
				if (debug)AddString(L"Button 4");
				if (flagY == 1)
					if (B_SET == 0) {
						countY++;
						flagY = 0;
					}
				B_1 = B_SET;
				if (B_SET == 1)flagY = 1;
				break;
			case 4:
				save += "L1,";
				if (flagL == 1)
					if (B_SET == 0) {
						countL++;
						flagL = 0;
					}
				if (debug)AddString(L"L1");
				B_L1 = B_SET;
				if (B_SET == 1)flagL = 1;
				break;
			case 5:
				save += "R1,";
				if (flagR == 1)
					if (B_SET == 0) {
						countR++;
						flagR = 0;
					}
				if (debug)AddString(L"R1");
				B_R1 = B_SET;
				if (B_SET == 1)flagR = 1;
				break;
			case 6:
				save += "L2,";
				if (debug)AddString(L"L2");
				B_L2 = B_SET;
				break;
			case 7:
				save += "R2,";
				if (debug)AddString(L"R2");
				B_R2 = B_SET;
				break;
			case 8:
				save += "Select,";
				if (debug)AddString(L"Select");





				if (flagSelect == 1)
					if (B_SET == 0) {
						NextSection();
						flagSelect = 0;
					}
				B_9 = B_SET;
				if (B_SET == 1)flagSelect = 1;



				break;
			case 9:
				save += "Start,";
				if (debug)AddString(L"Start");
				B_10 = B_SET;
				break;
			case 10:
				save += "L3,";
				if (debug)AddString(L"L3");
				B_L3 = B_SET;
				break;
			case 11:
				save += "R3,";
				if (debug)AddString(L"R3");
				B_R3 = B_SET;
				break;
			}

			if (e.value == 0)save += "released,";
			else save += "pressed,";


		}
		else if (e.type == 0x02) {
			switch (e.number) {
			case 0:
				save += "LX,";
				save += to_string(e.value) + ",";
				if (strDebug)AddString(L"Left X-Axis:");
				B_LX = e.value;
				if (e.value == 0) {
					B_LEFT = 0;
					B_RIGHT = 0;
				}
				if (e.value == -32767)B_LEFT = 1;
				if (e.value == 32767)B_RIGHT = 1;
				break;
			case 1:
				save += "LY,";
				save += to_string(e.value) + ",";
				if (strDebug)AddString(L"Left Y-Axis:");
				B_LY = e.value;
				if (e.value == 0) {
					B_UP = 0;
					B_DOWN = 0;
				}
				if (e.value == -32767)B_UP = 1;
				if (e.value == 32767)B_DOWN = 1;
				break;
			case 2:
				save += "RX,";
				save += to_string(e.value) + ",";
				if (strDebug)AddString(L"Right X-Axis:");
				B_RX = e.value;
				break;
			case 3:
				save += "RY,";
				save += to_string(e.value) + ",";
				if (strDebug)AddString(L"Right Y-Axis:");
				B_RY = e.value;
				break;
			}
			if (e.value == 0)if (strDebug);
			if (strDebug)AddString(L"at Time:");
		}
		else if (e.type == 0x80) {
		}

		save += to_string(e.time);

		wstring wsave;
		strConvert(wsave, save);


		if (prevStr != save) {
			SaveString(save);
			AddString(wsave);
		}

		prevStr = save;
	}
	
}

void Game::Draw(){

	float fill[4] = { 0.0f, 0.0f, 0.25f, 1.0f };
	context->ClearRenderTargetView(backbuffer, fill);

	context->OMSetRenderTargets(1, &backbuffer, 0 );
	float oX = 14.0f;
	float oY = -12.0f;


	sb->Begin(SpriteSortMode_Deferred, states->NonPremultiplied());

	sb->Draw(c1, XMFLOAT2(0.0f, 0.0f));

	float rxLoc = 655 + (B_RX * 0.001);
	float ryLoc = 300 + (B_RY * 0.001);	
	float lxLoc = 492 + (B_LX * 0.001);
	float lyLoc = 300 + (B_LY * 0.001);

		sb->Draw(b_circle, XMFLOAT2(rxLoc + oX, ryLoc + oY));
		sb->Draw(b_circle, XMFLOAT2(lxLoc + oX, lyLoc + oY));

		if (B_L1) {
			sb->Draw(b_lsmall, XMFLOAT2(395.0f + oX, 68.0f + oY));

		}
		if (B_L2) {
			sb->Draw(b_l_larger, XMFLOAT2(395.0f + oX, 10.0f + oY));
		}
		if (B_L3) {

		}

		if (B_R1) {
			sb->Draw(b_lsmall, XMFLOAT2(731.0f + oX, 68.0f + oY));
		}
		if (B_R2) {
			sb->Draw(b_l_larger, XMFLOAT2(731.0f + oX, 10.0f + oY));
		}
		if (B_R3){

		}
		if (B_1) {
			sb->Draw(b_circle, XMFLOAT2(740.0f + oX, 176.0f + oY));
			//AddString(L"Y");
			//countY++;
		}
		if (B_2) {
			sb->Draw(b_circle, XMFLOAT2(702.0f + oX, 216.0f + oY));
			//AddString(L"X");
			//countX++;
		}
		if (B_3) {
			sb->Draw(b_circle, XMFLOAT2(740.0f + oX, 255.0f + oY));
			//AddString(L"A");
			//countA++;
		}
		if (B_4) {
			sb->Draw(b_circle, XMFLOAT2(783.0f + oX, 216.0f + oY));
			//AddString(L"B");
			//countB++;
		}
		if (B_9) {
			sb->Draw(b_square, XMFLOAT2(537.0f + oX, 237.0f + oY));
		}
		if (B_10) {
			sb->Draw(b_square, XMFLOAT2(634.0f + oX, 237.0f + oY));
		}
		if (B_11) {
			sb->Draw(b_square, XMFLOAT2(0.0f + oX, 0.0f + oY));
		}
		if (B_12) {
			sb->Draw(b_square, XMFLOAT2(0.0f + oX, 0.0f + oY));
		}
		if (B_UP) {
			sb->Draw(b_dpad, XMFLOAT2(419.0f + oX, 190.0f + oY));
		}
		if (B_DOWN) {
			sb->Draw(b_dpad, XMFLOAT2(419.0f + oX, 255.0f + oY));
		}
		if (B_LEFT) { 
			sb->Draw(b_dpad, XMFLOAT2(390.0f + oX, 222.0f + oY));
		}
		if (B_RIGHT) {
			sb->Draw(b_dpad, XMFLOAT2(452.0f + oX, 222.0f + oY));
		}

	//float B_LX, B_LY, B_RX, B_LY; sb->Draw(b_smallecircle, XMFLOAT2(0.0f, 0.0f));

		wstring tempS;
	sf->DrawString(sb, L"GAME ANAYLTICS TOOL", XMFLOAT2(50, 100));
	tempS = L"Current Section:" + to_wstring(section);
	sf->DrawString(sb, tempS.c_str(), XMFLOAT2(50, 120));
	tempS = L"Num of times A pressed:" + to_wstring(countA);
	sf->DrawString(sb, tempS.c_str(), XMFLOAT2(50, 140));
	tempS = L"Num of times B pressed:" + to_wstring(countB);
	sf->DrawString(sb, tempS.c_str(), XMFLOAT2(50, 160));
	tempS = L"Num of times X pressed:" + to_wstring(countX);
	sf->DrawString(sb, tempS.c_str(), XMFLOAT2(50, 180));
	tempS = L"Num of times Y pressed:" + to_wstring(countY);
	sf->DrawString(sb, tempS.c_str(), XMFLOAT2(50, 200));
	tempS = L"Num of times L1 pressed:" + to_wstring(countL);
	sf->DrawString(sb, tempS.c_str(), XMFLOAT2(50, 220));
	tempS = L"Num of times R1 pressed:" + to_wstring(countR);
	sf->DrawString(sb, tempS.c_str(), XMFLOAT2(50, 240));


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

	//sf->DrawString(sb, stringList[numberOfItems].c_str(), XMFLOAT2(tW+300, tH));



	sb->End();


	swapchain->Present(1, 0);
}

ID3D11Device * Game::ReturnDevice()
{
	return device;
}

ID3D11DeviceContext * Game::ReturnContext()
{
	return context;
}

void Game::NextSection() {

	countA = countB = countX = countY = countL = countR = 0;
	section++;
	AddString(L"Next Section reseting count");
	string str = "SECTION,A," + to_string(countA) + ",B," + to_string(countB) + ",C," + to_string(countX) + ",X," + to_string(countX) + ",Y," + to_string(countY) + ",L," + to_string(countL) + ",R," + to_string(countR);
	SaveString(str);
}