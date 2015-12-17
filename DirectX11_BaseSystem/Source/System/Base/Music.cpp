#include "Music.h"

/**
*@brief	XACT�̏��������s��
*@return	S_OK or E_FAILED
*/
HRESULT Music::Init()
{
	MusicStop = false;
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	CreateXACTEngine();
	CreateSoundBank();
	CreateWaveBank();
	CreateCue();
	return S_OK;
}

void Music::Destroy()
{

}

/**
*@brief	XACTEngine�̍쐬
*@return	S_OK or E_FAILED
*/
HRESULT Music::CreateXACTEngine()
{
	//xgs�t�@�C����ǂ݂���
	HANDLE hFile;
	void* xgsBuf = NULL;
	DWORD xgsFileSize;
	bool isSuccess = false;//��������

	IXACT3Engine* engine;

	if(FAILED(XACT3CreateEngine(NULL, &engine)))
		throw;

	Engine = std::shared_ptr<IXACT3Engine>(engine, [](IXACT3Engine* p)
	{
			p->ShutDown();
			p->Release();
	});
	//�t�@�C������
	hFile = CreateFile("SOUND/WIN/SOUND.xgs", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile)
	{
		//�t�@�C���T�C�Y���擾
		xgsFileSize = GetFileSize(hFile, NULL);

		//�t�@�C���T�C�Y�擾����
		if (xgsFileSize != INVALID_FILE_SIZE)
		{
			xgsBuf = CoTaskMemAlloc(xgsFileSize);
			if (xgsBuf)
			{
				DWORD byteRead;
				//�t�@�C����ǂݍ���
				if (NULL != ReadFile(hFile, xgsBuf, xgsFileSize, &byteRead, NULL))
					isSuccess = true;
			}
		}
		//�t�@�C���n���h�������
		CloseHandle(hFile);
	}

	//�ǂݍ���xgs�t�@�C������G���W��������
	XACT_RUNTIME_PARAMETERS xrParams = { 0 };
	xrParams.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
	xrParams.pGlobalSettingsBuffer = xgsBuf;
	xrParams.globalSettingsBufferSize = xgsFileSize;
	xrParams.globalSettingsFlags = XACT_FLAG_GLOBAL_SETTINGS_MANAGEDATA;
	if(FAILED(Engine->Initialize(&xrParams)))
		throw;

	return S_OK;
}

/**
*@brief	WaveBank�̍쐬
*@return	S_OK or E_FAILED
*/
HRESULT Music::CreateWaveBank()
{
	std::array<std::string, 2> WBName = {
		"SOUND/WIN/BGM.xwb",
		"SOUND/WIN/SE.xwb",
	};
	for (int i = 0; i < 2; i++)
	{
		IXACT3WaveBank* wavebank = nullptr;
		void* wbbuffer = nullptr;
		HANDLE hFile = CreateFile(WBName[i].c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		DWORD dwFileSize = GetFileSize(hFile, NULL);
		HANDLE hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, dwFileSize, NULL);
		wbbuffer = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);
		if (wbbuffer)
		{
			if(FAILED(Engine->CreateInMemoryWaveBank(wbbuffer, dwFileSize, 0, 0, &wavebank)))
				throw;
		}
		CloseHandle(hMapFile);
		CloseHandle(hFile);
		WB.insert(um_WB::value_type(SoundKey[i], std::shared_ptr<IXACT3WaveBank>(wavebank, [](IXACT3WaveBank* p)
		{
			p->Destroy();
		})));
		WBBuffer.insert(um_void::value_type(SoundKey[i], std::shared_ptr<void>(wbbuffer, [](void* p)
		{
			UnmapViewOfFile(p);
		})));
	}

	return S_OK;
}

/**
*@brief	SoundBank�̍쐬
*@return	S_OK or E_FAILED
*/
HRESULT Music::CreateSoundBank()
{
	std::array<std::string, 2> SBName = {
		"SOUND/WIN/BGM.xsb",
		"SOUND/WIN/SE.xsb",
	};
	
	for (int i = 0; i < 2; i++)
	{
		IXACT3SoundBank* soundbank = nullptr;
		void* sbbuffer = nullptr;
		HANDLE hFile = CreateFile(SBName[i].c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		DWORD dwFileSize = GetFileSize(hFile, NULL);
		sbbuffer = new BYTE[dwFileSize];
		if (sbbuffer)
		{
			DWORD dwByteRead = 0;
			ReadFile(hFile, sbbuffer, dwFileSize, &dwByteRead, NULL);
			if(FAILED(Engine->CreateSoundBank(sbbuffer, dwFileSize, 0, 0, &soundbank)))
				throw;
		}
		CloseHandle(hFile);
		SB.insert(um_SB::value_type(SoundKey[i], std::shared_ptr<IXACT3SoundBank>(soundbank, [](IXACT3SoundBank* p)
		{
			p->Destroy();
		})));
		SBBuffer.insert(um_void::value_type(SoundKey[i], std::shared_ptr<void>(sbbuffer, [](void* p)
		{
			delete[] p;
		})));
	}

	return S_OK;
}

/**
*@brief	Cue�̍쐬
*@return	S_OK
*/
HRESULT Music::CreateCue()
{
	std::array<std::string, 2> SBKey = {
		"BGM",
		"SE",
	};

	XACTINDEX CueNum;
	SB["BGM"]->GetNumCues(&CueNum);

	
	for (int i = 0; i < CueNum; i++){
		IXACT3Cue* cue = nullptr;
		if(FAILED(SB["BGM"]->Prepare(i, 0, 0, &cue)))
			throw;
		Cue["BGM"].push_back(std::shared_ptr<IXACT3Cue>(cue, [](IXACT3Cue* p)
		{
			if (p)
			{
				p->Destroy();
				p = NULL;
			}
		}));
	}
	SB["SE"]->GetNumCues(&CueNum);
	for (int i = 0; i < CueNum; i++){
		IXACT3Cue* cue = nullptr;
		SB["SE"]->Prepare(i, 0, 0, &cue);
		Cue["SE"].push_back(std::shared_ptr<IXACT3Cue>(cue, [](IXACT3Cue* p)
		{
			if (p)
			{
				p->Destroy();
				p = NULL;
			}
		}));
	}
	return S_OK;
}

/**
*@brief	���̉����̐ݒ�(���ݒ�~��)
*@return	S_OK or E_FAILED
*/
/*HRESULT Music::Create3DSound()
{
	CHECKHRESULT(XACT3DInitialize(Engine.get(), xact3dInstance));
	DSPSettings = { 0 };
	CHECKHRESULT(Engine->GetFinalMixFormat(&format));

	DSPSettings.SrcChannelCount = 1;
	DSPSettings.DstChannelCount = format.Format.nChannels;
	DSPSettings.pMatrixCoefficients = new FLOAT32[DSPSettings.SrcChannelCount * DSPSettings.DstChannelCount];

	m_Listener.OrientFront = XMFLOAT3(0.f,0.f,1.0f);
	m_Listener.OrientTop = XMFLOAT3(0.f, 1.f, 0.0f);
	m_Listener.Position = XMFLOAT3(0.f,0.f,0.0f);
	m_Listener.Velocity = XMFLOAT3(0.f, 0.f, 0.0f);


	// the following need to be orthonormal
	m_Emitter.OrientFront = XMFLOAT3(0.f, 0.f, 1.0f);
	m_Emitter.OrientTop = XMFLOAT3(0.f, 1.f, 0.0f);

	m_Emitter.Position = XMFLOAT3(0.f, 0.f, 0.0f);
	m_Emitter.Velocity = XMFLOAT3(0.f, 0.f, 0.0f); // needs to not be zero if you want to hear Doppler effect

	// m_Emitter ChannelCount and DSP Setting's SrcChannelCount must match
	m_Emitter.ChannelCount = 1;

	// this will be set by XACT3DCalculate if ChannelCount > 1.
	m_Emitter.ChannelRadius = 0.0f;

	// will be set by XACT3DCalculate
	m_Emitter.pChannelAzimuths = NULL;

	// will be set by XACT3DCalculate
	m_Emitter.pVolumeCurve = m_Emitter.pLFECurve
		= m_Emitter.pLPFDirectCurve
		= m_Emitter.pLPFReverbCurve
		= m_Emitter.pReverbCurve
		= NULL;

	m_Emitter.CurveDistanceScaler = 1.0;
	m_Emitter.DopplerScaler = 1.0f;

	return S_OK;
}*/

/**
*@brief	���̉����̌v�Z���s��
*/
/*void Music::Calculate3DSound()
{
	XACT3DCalculate(xact3dInstance,&m_Listener,&m_Emitter,&DSPSettings);
}*/

/**
*@brief	���̉�����Cue�ɕۑ�����
*@param CueName �L���[�̖��O(XACT�Őݒ肵������)
*/
/*void Music::Apply3DSound(const std::string& CueName)
{
	XACTINDEX index = 0;
	for (auto key : SoundKey)
	{
		index = SB[key]->GetCueIndex(CueName.c_str());
		if (index != XACTINDEX_INVALID)
		{
			XACT3DApply(&DSPSettings, Cue[key][index].get());
			break;
		}
	}
}*/

/**
*@brief	���X�i�[�̈ʒu��ݒ�
*@param pos ���X�i�[�̎O�����ʒu
*/
/*void Music::SetListenPos(XMFLOAT3 pos)
{
	m_Listener.Position = pos;
}

/**
*@brief	�G�~�b�^�[�̈ʒu��ݒ�
*@param pos �G�~�b�^�[�̎O�����ʒu
*/
/*void Music::SetEmitPos(XMFLOAT3 pos)
{
	m_Emitter.Position = pos;
}*/

/**
*@brief	���y���Đ�����
*@param CueName �L���[�̖��O(XACT�Őݒ肵������)
*/
void Music::Play(const std::string& CueName)
{
	if (!MusicStop){
		XACTINDEX index = 0;
		DWORD State;
		for (auto key : SoundKey)
		{
			index = SB[key]->GetCueIndex(CueName.c_str());
			if (index != XACTINDEX_INVALID)
			{
				IXACT3Cue* cue = Cue[key][index].get();
				cue->GetState(&State);
				if ((key == "SE") && ((State == XACT_CUESTATE_PLAYING) || (State == XACT_CUESTATE_STOPPED) || (State & XACT_CUESTATE_STOPPED) == XACT_CUESTATE_STOPPED))
				{
					SB[key]->Prepare(index, 0, 0, &cue);
					cue->Play();
				}
				else if ((((State & XACT_CUESTATE_PREPARED) == XACT_CUESTATE_PREPARED) || ((State & XACT_CUESTATE_STOPPED) == XACT_CUESTATE_STOPPED)) && ((State & XACT_CUESTATE_PLAYING) != XACT_CUESTATE_PLAYING))
				{
					//SB[key]->Prepare(index, 0, 0, &cue);
					//cue->Play();
					SB[key]->Play(index, 0, 0, &cue);
				}
				else if ((State & XACT_CUESTATE_PAUSED) == XACT_CUESTATE_PAUSED)
				{
					cue->Pause(FALSE);
				}
				break;
			}
		}
	}
}

/**
*@brief	���y���~����
*@param CueName �L���[�̖��O(XACT�Őݒ肵������)
*/
void Music::Stop(const std::string& CueName)
{
	if (!MusicStop)
	{
		XACTINDEX index = 0;
		for (auto key : SoundKey)
		{
			index = SB[key]->GetCueIndex(CueName.c_str());
			if (index != XACTINDEX_INVALID)
			{
				IXACT3Cue* cue = Cue[key][index].get();
				DWORD State;
				cue->GetState(&State);
				if (((State & XACT_CUESTATE_PREPARED) == XACT_CUESTATE_PREPARED) || ((State & XACT_CUESTATE_STOPPED) == XACT_CUESTATE_STOPPED))
				{
					SB[key]->Stop(index,0);
				}
				break;
			}
		}
	}
}

/**
*@brief	���y���ꎞ��~����
*@param CueName �L���[�̖��O(XACT�Őݒ肵������)
*/
void Music::Pause(const std::string& CueName)
{
	if (!MusicStop)
	{
		XACTINDEX index = 0;
		for (auto key : SoundKey)
		{
			index = SB[key]->GetCueIndex(CueName.c_str());
			if (index != XACTINDEX_INVALID)
			{
				IXACT3Cue* cue = Cue[key][index].get();
				DWORD State;
				cue->GetState(&State);
				if ((State & XACT_CUESTATE_PLAYING) == XACT_CUESTATE_PLAYING)
				{
					cue->Pause(TRUE);
				}
				break;
			}
		}
	}
}

/**
*@brief	���y�̏�Ԃ��擾����
*@param CueName �L���[�̖��O(XACT�Őݒ肵������)
*@return State : ���y�̏��
*/
DWORD Music::GetState(const std::string& CueName)
{
	if (!MusicStop)
	{
		XACTINDEX index = 0;
		for (auto key : SoundKey)
		{
			index = SB[key]->GetCueIndex(CueName.c_str());
			if (index != XACTINDEX_INVALID)
			{
				IXACT3Cue* cue = Cue[key][index].get();
				DWORD State;
				cue->GetState(&State);
				return State;
			}
		}
	}
	return 0;
}

/**
*@brief	�L���[�ϐ��ɒl���Z�b�g����
*@param CueName �L���[�̖��O(XACT�Őݒ肵������)
*@param VariableName �L���[�ϐ��̖��O(XACT�Őݒ肵������)
*@param Value �l
*/
void Music::SetCueVariable(const std::string& CueName, const std::string& VariableName, float Value)
{
	if (!MusicStop)
	{
		XACTINDEX index = 0;
		for (auto key : SoundKey)
		{
			index = SB[key]->GetCueIndex(CueName.c_str());
			if (index != XACTINDEX_INVALID)
			{
				IXACT3Cue* cue = Cue[key][index].get();
				DWORD State;
				Cue[key][index]->GetState(&State);
				if ((State == XACT_CUESTATE_PREPARED) || (State == XACT_CUESTATE_PLAYING))
				{
					XACTVARIABLEINDEX v_index = cue->GetVariableIndex(VariableName.c_str());
					cue->SetVariable(v_index, Value);//�����Ń{�����[��or�s�b�`�ύX
				}
				break;
			}
		}
	}
}

/**
*@brief	�O���[�o���ϐ��ɒl���Z�b�g����
*@param VariableName �O���[�o���ϐ��̖��O(XACT�Őݒ肵������)
*@param Value �l
*/
void Music::SetGlobalVariable(const std::string& VariableName, float Value)
{
	if (!MusicStop)
	{
		XACTVARIABLEINDEX v_index = Engine->GetGlobalVariableIndex(VariableName.c_str());
		Engine->SetGlobalVariable(v_index, Value);//�����Ń{�����[��or�s�b�`�ύX
	}
}