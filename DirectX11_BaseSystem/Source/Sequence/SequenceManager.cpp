#include "Sequence.h"
#include "Title.h"
#include "../System/Base/Joypad.h"
#include <future>

void SeqManager::Init(){
	auto sequence = std::make_shared<Title>();
	_sequenceContainer.emplace(sequence->GetSequenceName(), sequence);
	sequence->Init("");
	std::vector<XMFLOAT4> viewport;
	viewport.emplace_back(XMFLOAT4(1200.f, 900.f, 0.f, 0.f));
	_canvas.Init(viewport);
}

bool SeqManager::Update(){
	for (int i = 0; i < 4;++i)
		JoypadUpdate(i);
	bool continueFlag = true;
	std::vector<std::shared_ptr<Sequence>> updatableSequence;
	for (auto& sequence : _sequenceContainer)
	{
		if (sequence.second->isUpdatable())
			updatableSequence.emplace_back(sequence.second);
	}
	for (auto& sequence : updatableSequence)
	{
		continueFlag &= sequence->Update(&_sequenceContainer);
	}
	return continueFlag;
}

void SeqManager::Draw(){
	int drawableSequenceNum = 0;
	for (auto& sequence : _sequenceContainer)
	{
		drawableSequenceNum += static_cast<int>(sequence.second->isDrawable());
	}
	std::vector<std::shared_ptr<Sequence>*> drawableSequence;
	drawableSequence.resize(drawableSequenceNum);
	for (auto& sequence : _sequenceContainer)
	{
		if (sequence.second->isDrawable())
		{
			auto priority = sequence.second->GetPriority();
			priority = (priority >= drawableSequence.size() - 1) ? drawableSequence.size() - 1 : priority;
			while (drawableSequence[priority] != nullptr && priority != drawableSequence.size() - 1)
				priority++;
			if (drawableSequence[priority] != nullptr)
			{
				while (drawableSequence[priority] != nullptr && priority != 0)
					priority--;
			}
			if (drawableSequence[priority] == nullptr)
				drawableSequence[priority] = &sequence.second;
		}
	}
	_canvas.Begin();
	for (auto& sequence : drawableSequence)
	{
		if (sequence != nullptr)
			(*sequence)->Draw(&_canvas);
	}
	_canvas.End();
}