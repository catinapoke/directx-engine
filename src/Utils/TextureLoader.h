#pragma once
#include <DirectXTex.h>

class TextureLoader {
public:
	static HRESULT LoadWic(const wchar_t* path, DirectX::ScratchImage* image, bool sRGB = false) {
		DirectX::WIC_FLAGS flags = sRGB ? DirectX::WIC_FLAGS_FORCE_SRGB : DirectX::WIC_FLAGS_NONE;
		return LoadFromWICFile(
			path,
			flags,
			nullptr,
			*image);
	}
};