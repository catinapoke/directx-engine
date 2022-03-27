#pragma once
#include <DirectXTex.h>

class TextureLoader {
public:
	static HRESULT LoadWic(const wchar_t* path, DirectX::ScratchImage* image) {
		return LoadFromWICFile(
			path,
			DirectX::WIC_FLAGS_NONE,
			nullptr,
			*image);
	}
};