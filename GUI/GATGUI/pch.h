#pragma once
#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <io.h>
#include <string>
#include <ctime>
#include <d3d11_1.h>
#include <DirectXMath.h>
#pragma comment (lib, "d3d11.lib")
#include "CommonStates.h"
#include "DDSTextureLoader.h"
#include "DirectXHelpers.h"
#include "Effects.h"
#include "Keyboard.h"
#include "Model.h"
#include "Mouse.h"
#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;
using namespace std;