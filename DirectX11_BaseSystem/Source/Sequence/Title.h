#pragma once

#include "Sequence.h"
#include "../Object/Base/Surface.h"
#include "../System/Base/Shader.h"

class Title : public Sequence
{
private:
	std::unordered_map<std::string, DX11::ShaderSet> _shaderSet;
	DX11::Surface _surface;
	int _oldTime=0 ,_time = 0;
public:
	Title();
	void Init(const std::string& beforeSequenceName);
	bool Update(std::unordered_map<std::string, std::shared_ptr<Sequence>>* sequenceContainer);
	void Draw(DX11::Canvas* canvas);

};
