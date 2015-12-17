#ifndef __SEQUENCE__
#define __SEQUENCE__

#include "../System/Base/Camera.h"
#include "../Object/Base/Sprite.h"
#include "../System/Base/Canvas.h"
#include <unordered_map>

class Sequence{
protected:
	enum class State
	{
		wait = 0x01,
		drawable = 0x02,
		updatable = 0x04,
		active = 0x06,
	};
private:
	std::string _sequenceName;
protected:
	using um_Sprite = std::unordered_map<std::string, std::shared_ptr<DX11::Sprite>>;
	um_Sprite _imageMap;
	State _state = State::wait;
	std::string  nextSequenceName;
	std::string  beforeSequenceName;
	unsigned int _priority = 0;
protected:
	template<typename T>
	static void EmplaceSequence(std::unordered_map<std::string, std::shared_ptr<Sequence>>* sequenceContainer)
	{
		std::string sequenceName = typeid(T).name();
		for (auto& info : *sequenceContainer)
		{
			if (info.first == sequenceName)
				return;
		}
		auto sequence = std::make_shared<T>();
		sequenceContainer->emplace(sequence->GetSequenceName(),sequence);
	}
public:
	Sequence(const std::string& sequenceName)
	{
		//ÉNÉâÉXñºÇÃ" *"Çè¡ãéÇµÇƒìoò^
		_sequenceName = sequenceName;
		for (auto i : {0,1,2,3,4,5,6,7,8,9})
			_sequenceName.pop_back();
	}
	virtual ~Sequence(){}
	virtual void Init(const std::string& beforeSequenceName) = 0;
	virtual bool Update(std::unordered_map<std::string, std::shared_ptr<Sequence>>* sequenceContainer) = 0;
	virtual void Draw(DX11::Canvas* canvas) = 0;
public:
	const std::string GetSequenceName(){ 
		return _sequenceName;
	}
	virtual void SetVariable(double value){};
	unsigned int GetPriority(){ return _priority; }
	bool isUpdatable(){ return ((static_cast<int>(_state)& static_cast<int>(State::updatable)) == static_cast<int>(State::updatable)); }
	bool isDrawable(){ return ((static_cast<int>(_state)& static_cast<int>(State::drawable)) == static_cast<int>(State::drawable)); }
};

class SeqManager{
private:
	std::unordered_map<std::string, std::shared_ptr<Sequence>> _sequenceContainer;
	DX11::Canvas _canvas;
public:
	void Init();
	bool Update();
	void Draw();
};

#endif