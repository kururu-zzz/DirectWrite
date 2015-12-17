/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2009-2014 CRI Middleware Co., Ltd.
 *
 * Library  : CRI Atom
 * Module   : Library User's Header
 * File     : cri_le_atom.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_le_atom.h
 */

/* ���d��`�h�~					*/
/* Prevention of redefinition	*/
#ifndef CRI_INCL_CRI_LE_ATOM_H
#define CRI_INCL_CRI_LE_ATOM_H

/***************************************************************************
 *      �C���N���[�h�t�@�C��
 *      Include files
 ***************************************************************************/
#include <cri_le_xpt.h>
#include <cri_le_file_system.h>

/***************************************************************************
 *      �萔�}�N��
 *      Macro Constants
 ***************************************************************************/
/* �o�[�W������� */
/* Version Number */
#define CRI_ATOM_VERSION				(0x02060000)
#define CRI_ATOM_VER_NUM				"2.06.00"
#define CRI_ATOM_VER_NAME				"CRI Atom(LE)"

/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/
/* Windows�p�̃f�t�H���g�ݒ� */
#define CRIATOM_DEFAULT_OUTPUT_CHANNELS				(6)
#define CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE		(48000)
#define CRIATOM_DEFAULT_INPUT_MAX_CHANNELS			(2)
#define CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE		(48000)
#define CRIATOM_DEFAULT_DECODE_LATENCY				(0)
#define CRIATOM_DEFAULT_DBAS_MAX_STREAMS			(8)
#define CRIATOM_SOUND_RENDERER_DEFAULT				(CRIATOM_SOUND_RENDERER_ASR)

/*==========================================================================
 *      CRI Atom Player API
 *=========================================================================*/

/*==========================================================================
 *      CRI Atom AWB API
 *=========================================================================*/

/*==========================================================================
 *      CRI Atom D-BAS API
 *=========================================================================*/
/*JP
 * \brief Atom D-BAS ID
 * \ingroup ATOMLIB_DBAS
 * \par ����:
 * ::criAtomDbas_Create �֐��Ɏ��s�����ۂɕԂ�l�ł��B <br>
 * \sa criAtomDbas_Create, criAtomDbas_Destroy
 */
#define CRIATOMDBAS_ILLEGAL_ID	(-1)

/*JP
 * \brief D-BAS�쐬�p�̃f�t�H���g�������ő�r�b�g���[�g�l
 * \ingroup ATOMLIB_AWB
 * \par ����:
 * D-BAS�쐬�p�̃f�t�H���g�������p�����[�^�l��`�ł��B<br>
 * �e�v���b�g�t�H�[���Œ�`���Ă���f�t�H���g�̍ő�X�g���[���{�����A
 * �X�e���IADX�f�[�^���X�g���[�~���O�Đ�����O��Ōv�Z���Ă��܂��B <br>
 * \sa criAtomDbas_Create, criAtomDbas_CalculateWorkSize, criAtom_CalculateAdxBitrate
 */
#define CRIATOM_DEFAULT_DBAS_MAX_BPS \
	(criAtom_CalculateAdxBitrate(CRIATOM_DEFAULT_INPUT_MAX_CHANNELS,\
								 CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE)\
								 * CRIATOM_DEFAULT_DBAS_MAX_STREAMS)

/***************************************************************************
 *      �����}�N��
 *      Macro Functions
 ***************************************************************************/
/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/
#define criAtom_SetUserAllocator(p_malloc_func, p_free_func, p_obj)	\
{\
	criAtom_SetUserMallocFunction(p_malloc_func, p_obj);\
	criAtom_SetUserFreeFunction(p_free_func, p_obj);\
}

/*==========================================================================
 *      CRI Atom D-BAS API
 *=========================================================================*/
/*JP
 * \brief CriAtomDbasConfig �ւ̃f�t�H���g�p�����[�^�̃Z�b�g
 * \ingroup ATOMLIB_DBAS
 * \param[out]	p_config	D-BAS�쐬�p�R���t�B�O�\���̂ւ̃|�C���^
 * \par ����:
 * ::criAtomDbas_Create �֐��ɐݒ肷��R���t�B�O�\����
 * �i ::CriAtomDbasConfig �j�ɁA�f�t�H���g�̒l���Z�b�g���܂��B<br>
 * \sa CriAtomDbasConfig, criAtomDbas_Create, criAtomDbas_CalculateWorkSize
 */
#define criAtomDbas_SetDefaultConfig(p_config)	\
{\
	(p_config)->identifier	= 0;\
	(p_config)->max_streams	= CRIATOM_DEFAULT_DBAS_MAX_STREAMS;\
	(p_config)->max_bps		= CRIATOM_DEFAULT_DBAS_MAX_BPS;\
	(p_config)->max_mana_streams	= 0;\
	(p_config)->max_mana_bps		= 0;\
}

/* ========================================================================*/
/*       CRI Atom Meter API                                                */
/* ========================================================================*/

/*JP
 * \brief ���x�����[�^�@�\�R���t�B�O�\���̂Ƀf�t�H���g�l���Z�b�g
 * \ingroup ATOMLIB_METER
 * \par ����:
 * ::criAtomExAsr_AttachLevelMeter �֐��ɐݒ肷��R���t�B�O�\����
 * �i ::CriAtomLevelMeterConfig �j�ɁA�f�t�H���g�l���Z�b�g���܂��B<br>
 * \sa criAtomExAsr_AttachLevelMeter, CriAtomLevelMeterConfig
 */
#define criAtomMeter_SetDefaultConfigForLevelMeter(p_config) \
{\
	(p_config)->interval = 50;\
	(p_config)->hold_time = 1000;\
}

/***************************************************************************
 *      �f�[�^�^�錾
 *      Data Type Declarations
 ***************************************************************************/
/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/
/*JP
 * \brief �������m�ۊ֐�
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	obj		���[�U�w��I�u�W�F�N�g
 * \param[in]	size	�v���������T�C�Y�i�o�C�g�P�ʁj
 * \return		void*	�m�ۂ����������̃A�h���X�i���s����NULL�j
 * \par ����:
 * �������m�ۊ֐��o�^�p�̃C���^�[�t�F�[�X�ł��B<br>
 * CRI Atom���C�u���������C�u�������ōs���������m�ۏ������A
 * ���[�U�Ǝ��̃������m�ۏ����ɒu�����������ꍇ�Ɏg�p���܂��B<br>
 * \par ���l:
 * �R�[���o�b�N�֐������s�����ۂɂ́Asize�ɕK�v�Ƃ���郁�����̃T�C�Y���Z�b�g
 * ����Ă��܂��B<br>
 * �R�[���o�b�N�֐�����size���̃��������m�ۂ��A�m�ۂ����������̃A�h���X��
 * �߂�l�Ƃ��ĕԂ��Ă��������B<br>
 * ���A������ obj �ɂ́A::criAtom_SetUserMallocFunction �֐��œo�^�������[�U�w��
 * �I�u�W�F�N�g���n����܂��B<br>
 * �������m�ێ��Ƀ������}�l�[�W�������Q�Ƃ���K�v������ꍇ�ɂ́A
 * ���Y�I�u�W�F�N�g�� ::criAtom_SetUserMallocFunction �֐��̈����ɃZ�b�g���Ă����A
 * �{�R�[���o�b�N�֐��̈������o�R���ĎQ�Ƃ��Ă��������B<br>
 * \attention
 * �������̊m�ۂɎ��s�����ꍇ�A�G���[�R�[���o�b�N���Ԃ��ꂽ��A�Ăяo�����̊֐���
 * ���s����\��������܂��̂ł����ӂ��������B
 * \sa CriAtomFreeFunc, criAtom_SetUserMallocFunction
 */
typedef void *(CRIAPI *CriAtomMallocFunc)(void *obj, CriUint32 size);

/*JP
 * \brief ����������֐�
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	obj		���[�U�w��I�u�W�F�N�g
 * \param[in]	mem		������郁�����A�h���X
 * \return				�Ȃ�
 * \par ����:
 * ����������֐��o�^�p�̃C���^�[�t�F�[�X�ł��B<br>
 * CRI Atom���C�u�����������C�u�������ōs������������������A
 * ���[�U�Ǝ��̃�������������ɒu�����������ꍇ�Ɏg�p���܂��B<br>
 * \par ���l:
 * �R�[���o�b�N�֐������s�����ۂɂ́Amem�ɉ�����ׂ��������̃A�h���X���Z�b�g
 * ����Ă��܂��B<br>
 * �R�[���o�b�N�֐�����mem�̗̈�̃�������������Ă��������B
 * ���A������ obj �ɂ́A::criAtom_SetUserFreeFunction �֐��œo�^�������[�U�w��
 * �I�u�W�F�N�g���n����܂��B<br>
 * �������m�ێ��Ƀ������}�l�[�W�������Q�Ƃ���K�v������ꍇ�ɂ́A
 * ���Y�I�u�W�F�N�g�� ::criAtom_SetUserFreeFunction �֐��̈����ɃZ�b�g���Ă����A
 * �{�R�[���o�b�N�֐��̈������o�R���ĎQ�Ƃ��Ă��������B<br>
 * \sa CriAtomMallocFunc, criAtom_SetUserFreeFunction
 */
typedef void (CRIAPI *CriAtomFreeFunc)(void *obj, void *mem);

/*JP
 * \brief �T�E���h�����_���^�C�v
 * \ingroup ATOMLIB_GLOBAL
 * \par ����:
 * Atom�v���[���������ō쐬����T�E���h�����_���̎�ʂ��w�肷�邽�߂̃f�[�^�^�ł��B<br>
 * Atom�v���[���쐬���ɃR���t�B�O�\���̂̃p�����[�^�Ƃ��Ďw�肵�܂��B
 * \sa CriAtomStandardPlayerConfig
 */
typedef enum CriAtomSoundRendererTypeTag {
	CRIATOM_SOUND_RENDERER_NATIVE = 1,		/*JP<�v���b�g�t�H�[�����C�u�����֏o��	*/
	CRIATOM_SOUND_RENDERER_ASR = 2,			/*JP<Atom Sound Renderer�֏o��			*/
	
	/* enum size is 4bytes */
	CRIATOM_SOUND_RENDERER_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomSoundRendererType;

/*JP
 * \brief �X�s�[�J�[ID
 * \ingroup ATOMLIB_GLOBAL
 * \par ����:
 * �������o�͂���X�s�[�J�[���w�肷�邽�߂�ID�ł��B<br>
 * ::criAtomPlayer_SetSendLevel �֐��ŗ��p���܂��B
 * \sa criAtomPlayer_SetSendLevel
 */
typedef enum CriAtomSpeakerIdTag {
	CRIATOM_SPEAKER_FRONT_LEFT = 0,				/*JP<�t�����g���t�g�X�s�[�J�[			*/
	CRIATOM_SPEAKER_FRONT_RIGHT = 1,			/*JP<�t�����g���C�g�X�s�[�J�[			*/
	CRIATOM_SPEAKER_FRONT_CENTER = 2,			/*JP<�t�����g�Z���^�[�X�s�[�J�[			*/
	CRIATOM_SPEAKER_LOW_FREQUENCY = 3,			/*JP<LFE�i���T�u�E�[�n�[�j				*/
	CRIATOM_SPEAKER_SURROUND_LEFT = 4,			/*JP<�T���E���h���t�g�X�s�[�J�[			*/
	CRIATOM_SPEAKER_SURROUND_RIGHT = 5,			/*JP<�T���E���h���C�g�X�s�[�J�[			*/
	CRIATOM_SPEAKER_SURROUND_BACK_LEFT = 6,		/*JP<�T���E���h�o�b�N���t�g�X�s�[�J�[	*/
	CRIATOM_SPEAKER_SURROUND_BACK_RIGHT = 7,	/*JP<�T���E���h�o�b�N���C�g�X�s�[�J�[	*/

	/* enum size is 4bytes */
	CRIATOM_SPEAKER_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomSpeakerId;

/*JP
 * \brief �p�t�H�[�}���X���
 * \ingroup ATOMLIB_GLOBAL
 * \par ����:
 * �p�t�H�[�}���X�����擾���邽�߂̍\���̂ł��B<br>
 * ::criAtom_GetPerformanceInfo �֐��ŗ��p���܂��B
 * \sa criAtom_GetPerformanceInfo
 */
typedef struct CriAtomPerformanceInfoTag {
	CriUint32 server_process_count;		/*JP<�T�[�o�������s��									*/
	CriUint32 last_server_time;			/*JP<�T�[�o�������Ԃ̍ŏI�v���l�i�}�C�N���b�P�ʁj		*/
	CriUint32 max_server_time;			/*JP<�T�[�o�������Ԃ̍ő�l�i�}�C�N���b�P�ʁj			*/
	CriUint32 average_server_time;		/*JP<�T�[�o�������Ԃ̕��ϒl�i�}�C�N���b�P�ʁj			*/
	CriUint32 last_server_interval;		/*JP<�T�[�o�������s�Ԋu�̍ŏI�v���l�i�}�C�N���b�P�ʁj	*/
	CriUint32 max_server_interval;		/*JP<�T�[�o�������s�Ԋu�̍ő�l�i�}�C�N���b�P�ʁj		*/
	CriUint32 average_server_interval;	/*JP<�T�[�o�������s�Ԋu�̕��ϒl�i�}�C�N���b�P�ʁj		*/
} CriAtomPerformanceInfo;

/*JP
 * \brief �G���R�[�h�i��
 * \ingroup ATOMLIB_GLOBAL
 * \par ����:
 * CRI Atom Encoder, CRI Atom Craft�Őݒ肳���G���R�[�h�i���̃f�[�^�^�ł��B<br>
 * �����f�[�^�̃r�b�g���[�g���v�Z����Ƃ��Ɏg�p���܂��B
 * \sa criAtom_CalculateHcaBitrate, criAtom_CalculateHcaMxBitrate
 */
typedef enum CriAtomEncodeQualityTag {
	CRIATOM_ENCODE_QUALITY_LOWEST = 0,	/*JP<�Œ�i���ݒ�	*/
	CRIATOM_ENCODE_QUALITY_LOW,			/*JP<��i���ݒ�		*/
	CRIATOM_ENCODE_QUALITY_MIDDLE,		/*JP<���i���ݒ�		*/
	CRIATOM_ENCODE_QUALITY_HIGH,		/*JP<���i���ݒ�		*/
	CRIATOM_ENCODE_QUALITY_HIGHEST,		/*JP<�ō��i���ݒ�	*/

	/* enum size is 4bytes */
	CRIATOM_ENCODE_QUALITY_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomEncodeQuality;

/*JP
 * \brief �t�H�[�}�b�g���
 * \ingroup ATOMLIB_GLOBAL
 * \par ����:
 * �����f�[�^�̃t�H�[�}�b�g�������f�[�^�^�ł��B<br>
 * �ȉ��̂����ꂩ�̒l�����p�\�ł��B<br>
 * - ::CRIATOM_FORMAT_ADX
 * - ::CRIATOM_FORMAT_HCA
 * - ::CRIATOM_FORMAT_HCA_MX
 * .
 */
typedef CriUint32 CriAtomFormat;
#define CRIATOM_FORMAT_NONE			(0x00000000)		/*JP< �Ȃ�				*/
#define CRIATOM_FORMAT_ADX			(0x00000001)		/*JP< ADX				*/
#define CRIATOM_FORMAT_HCA			(0x00000003)		/*JP< HCA				*/
#define CRIATOM_FORMAT_HCA_MX		(0x00000004)		/*JP< HCA-MX			*/

/*JP
 * \brief PCM�t�H�[�}�b�g
 * \ingroup ATOMLIB_GLOBAL
 * \par ����:
 * PCM�f�[�^�̌^���ł��B
 * \sa criAtomPlayer_SetFilterCallback
 */
typedef enum CriAtomPcmFormatTag {
	CRIATOM_PCM_FORMAT_SINT16 = 0,
	CRIATOM_PCM_FORMAT_FLOAT32,

	/* enum size is 4bytes */
	CRIATOM_PCM_FORMAT_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomPcmFormat;

/*==========================================================================
 *      CRI Atom AWB API
 *=========================================================================*/
struct CriAtomAwbTag;
/*JP
 * \brief AWB�n���h��
 * \ingroup ATOMLIB_AWB
 * \par ����:
 * �Đ��f�[�^���܂܂�Ă���AWB�t�@�C����TOC���������n���h���ł��B<br>
 * ::criAtomAwb_LoadToc�֐��Ŏ擾���܂��B<br>
 * \sa criAtomAwb_LoadToc
 */
typedef struct CriAtomAwbTag *CriAtomAwbHn;

/*==========================================================================
 *      CRI Atom Player API
 *=========================================================================*/
/*JP
 * �W���v���[���쐬�p�R���t�B�O�\����
 * \ingroup ATOMLIB_PLAYER
 * \par ����:
 * �W���v���[���iADX��HCA���Đ��\�ȃv���[���j���쐬����ۂɁA
 * ����d�l���w�肷�邽�߂̍\���̂ł��B<br>
 * �{�C�X�v�[�����쐬����ہA�{�C�X�i��Atom�v���[���j�̎d�l���K�肷�邽�߂Ɏg�p���܂��B<br>
 * \sa CriAtomExStandardVoicePoolConfig
 */
typedef struct CriAtomStandardPlayerConfigTag {
	/*JP
		\brief �ő�o�̓`�����l����
		\par ����:
		Atom�v���[���ōĐ����鉹���̃`�����l�������w�肵�܂��B<br>
		::criAtomPlayer_CreateStandardPlayer �֐��ō쐬���ꂽAtom�v���[���́Amax_channels�Ŏw�肵��
		�`�����l����"�ȉ���"�����f�[�^���Đ��\�ł��B<br>
		�ő�o�̓`�����l�����Ƃ��Ďw�肷��l�ƁA�쐬���ꂽAtom�v���[���ōĐ��\�ȃf�[�^��
		�֌W���ȉ��Ɏ����܂��B<br>
		\table "�ő�o�̓`�����l�����ƍĐ��\�ȃf�[�^�̊֌W" align=center border=1 cellspacing=0 cellpadding=4
		[�ő�o�̓`�����l�����i�w�肷��l�j	| �쐬���ꂽAtom�v���[���ōĐ��\�ȃf�[�^	]
		[1									| ���m����									]
		[2									| ���m�����A�X�e���I						]
		[6									| ���m�����A�X�e���I�A5.1ch					]
		[8									| ���m�����A�X�e���I�A5.1ch�A7.1ch			]
		\endtable
		<br>
		\par ���l:
		�T�E���h�o�͎��Ƀn�[�h�E�F�A���\�[�X���g�p����v���b�g�t�H�[���ɂ����ẮA
		�o�̓`�����l���������������邱�ƂŁA�n�[�h�E�F�A���\�[�X�̏����}���邱�Ƃ�
		�\�ł��B<br>
		\attention
		�w�肳�ꂽ�ő�o�̓`�����l�����𒴂���f�[�^�́A�Đ����邱�Ƃ͂ł��܂���B<br>
		�Ⴆ�΁A�ő�o�̓`�����l������1�ɐݒ肵���ꍇ�A�쐬���ꂽAtom�v���[����
		�X�e���I�������Đ����邱�Ƃ͂ł��܂���B<br>
		�i���m�����Ƀ_�E���~�b�N�X����ďo�͂���邱�Ƃ͂���܂���B�j
	*/
	CriSint32 max_channels;

	/*JP
		\brief �ő�T���v�����O���[�g
		\par ����:
		Atom�v���[���ōĐ����鉹���̃T���v�����O���[�g���w�肵�܂��B<br>
		::criAtomPlayer_CreateStandardPlayer �֐��ō쐬���ꂽAtom�v���[���́Amax_sampling_rate�Ŏw�肵��
		�T���v�����O���[�g"�ȉ���"�����f�[�^���Đ��\�ł��B<br>
		<br>
		\par ���l:
		�ő�T���v�����O���[�g�������邱�ƂŁAAtom�v���[���쐬���ɕK�v�ƂȂ郏�[�N������
		�̃T�C�Y��}���邱�Ƃ��\�ł��B
		\attention
		�w�肳�ꂽ�ő�T���v�����O���[�g�𒴂���f�[�^�́A�Đ����邱�Ƃ͂ł��܂���B<br>
		�Ⴆ�΁A�ő�T���v�����O���[�g��24000�ɐݒ肵���ꍇ�A�쐬���ꂽAtom�v���[����
		48000Hz�̉������Đ����邱�Ƃ͂ł��܂���B<br>
		�i�_�E���T���v�����O����ďo�͂���邱�Ƃ͂���܂���B�j
	*/
	CriSint32 max_sampling_rate;

	/*JP
		\brief �X�g���[�~���O�Đ����s�����ǂ���
		\par ����:
		Atom�v���[���ŃX�g���[�~���O�Đ��i�t�@�C������̍Đ��j���s�����ǂ������w�肵�܂��B<br>
		streaming_flag��CRI_FALSE���w�肵���ꍇ�A�쐬���ꂽAtom�v���[���̓I���������̃f�[�^
		�Đ��i ::criAtomPlayer_SetData �֐��Ŏw�肵���������A�h���X�̍Đ��j�݂̂��T�|�[�g
		���܂��B�i�t�@�C������̍Đ��͂ł��܂���B�j<br>
		streaming_flag��CRI_TRUE���w�肵���ꍇ�A�쐬���ꂽAtom�v���[���̓I���������̃f�[�^
		�Đ��ɉ����A�t�@�C������̍Đ����T�|�[�g���܂��B<br>
		\par �⑫:
		streaming_flag��CRI_TRUE�ɂ����ꍇ�AAtom�v���[���쐬���Ƀt�@�C���ǂݍ��ݗp�̃��\�[�X
		���m�ۂ���܂��B<br>
		���̂��߁Astreaming_flag��CRI_FALSE�̏ꍇ�ɔ�ׁAAtom�v���[���̍쐬�ɕK�v�ȃ�������
		�T�C�Y���傫���Ȃ�܂��B
	*/
	CriBool streaming_flag;

	/*JP
		\brief �T�E���h�����_���^�C�v
		\par ����:
		Atom�v���[�����g�p����T�E���h�����_���̎�ʂ��w�肵�܂��B<br>
		LE�Ń��C�u�����ł͕K�� CRIATOM_SOUND_RENDERER_ASR ���w�肵�Ă��������B
	*/
	CriAtomSoundRendererType sound_renderer_type;

	/*JP
		\brief �f�R�[�h�����̃��C�e���V
		\par ����:
		�f�R�[�h�����̃��C�e���V���w�肵�܂��B<br>
		decode_latency �� 0 �ɐݒ肵���ꍇ�A�v���[���͉����Đ��J�n����
		�����f�[�^�̃f�R�[�h���\�Ȍ���x���Ȃ��s���܂��B<br>
		�i�I���������Đ����� ::criAtomPlayer_Start �֐������s��A
		�ŏ��̃T�[�o�������ōĐ��J�n�ɕK�v�ȗʂ̃f�[�^���f�R�[�h���A
		�����̏o�͂��J�n���܂��B�j<br>
		����ɑ΂� decode_latency �� 1 �ȏ�ɐݒ肵���ꍇ�A
		�Đ��J�n�ɕK�v�ȃf�[�^�̃f�R�[�h���A������̃T�[�o�����ɕ������čs���܂��B<br>
		�i�I���������Đ����ł����Ă� ::criAtomPlayer_Start �֐������s��A
		decode_latency �Ɏw�肵���񐔃T�[�o���������삷��܂ł͉����̏o�͂��J�n����܂���B�j<br>
		\par ���l:
		Atom�v���[���̓T�E���h�o�b�t�@���̃f�[�^�c�ʂ����ɁA
		�T�[�o����������̉����f�[�^�̃f�R�[�h�ʂ����肵�Ă��܂��B<br>
		�����Đ��J�n�O�̓T�E���h�o�b�t�@����̏�Ԃ̂��߁A
		�����Đ����ɔ�ׂđ����̃f�[�^�i�Đ����� 2 �` 4 �{���x�j���f�R�[�h����܂��B<br>
		�v���[��������̉����f�[�^�̃f�R�[�h�������ׂ͏��������߁A
		�ꉹ�ꉹ�̔����J�n���̏������ׂ����ɂȂ邱�Ƃ͂قƂ�ǂ���܂���B<br>
		�������A�A�v���P�[�V�������� 1V �ɑ�ʂ̔������N�G�X�g�𓯎��ɔ��s�����ꍇ�A
		�S�Ẵv���[���̏������ׂ̃s�[�N���������A���ׂ��ڂɌ����đ傫���Ȃ�ꍇ������܂��B<br>
		����������������s���P�[�X�ł́A decode_latency �̒l�𑝂₷���ƂŁA
		�Ǐ��I�ɏ������ׂ������Ȃ�Ǐ��������邱�Ƃ��\�ł��B<br>
		<br>
		decode_latency �̃f�t�H���g�l�́A�قƂ�ǂ̊��� 0 �ɐݒ肳��Ă��܂��B<br>
		�������A�g�уQ�[���@���A�킸���ȕ��וϓ��ł��A�v���P�[�V�����ɑ傫�ȉe�����y�ڂ����ł́A
		�f�t�H���g�l�� 1 �ȏ�ɐݒ肳��Ă���\��������܂��B<br>
		�i���ۂɃZ�b�g�����l�ɂ��Ă� ::criAtomPlayer_SetDefaultConfigForStandardPlayer
		�}�N���̓K�p���ʂ��m�F���Ă��������B�j<br>
		<br>
		���� decode_latency �̒l�� 4 �ȏ�̒l���w�肷�邱�Ƃ͂ł��܂���B<br>
		�i decode_latency �� 4 �ȏ�̒l���w�肵���ꍇ�ł��A���C�u�������� 3 �ɕύX����܂��B�j<br>
	*/
	CriSint32 decode_latency;
} CriAtomStandardPlayerConfig;

/*JP
 * \ingroup ATOMLIB_PLAYER
 * HCA-MX�v���[���쐬�p�R���t�B�O�\����
 * \par ����:
 * HCA-MX���Đ��\�ȃv���[�����쐬����ۂɁA����d�l���w�肷�邽�߂̍\���̂ł��B<br>
 * �{�C�X�v�[�����쐬����ہA�{�C�X�i��Atom�v���[���j�̎d�l���K�肷�邽�߂Ɏg�p���܂��B<br>
 * \sa CriAtomExHcaMxVoicePoolConfig
 */
typedef struct CriAtomHcaMxPlayerConfigTag {
	/*JP
		\brief �ő�o�̓`�����l����
		\par ����:
		Atom�v���[���ōĐ����鉹���̃`�����l�������w�肵�܂��B<br>
		::criAtomPlayer_CreateHcaMxPlayer �֐��ō쐬���ꂽAtom�v���[���́Amax_channels�Ŏw�肵��
		�`�����l����"�ȉ���"�����f�[�^���Đ��\�ł��B<br>
	*/
	CriSint32 max_channels;

	/*JP
		\brief �ő�T���v�����O���[�g
		\par ����:
		Atom�v���[���ōĐ����鉹���̃T���v�����O���[�g���w�肵�܂��B<br>
		::criAtomPlayer_CreateHcaMxPlayer �֐��ō쐬���ꂽAtom�v���[���́Amax_sampling_rate�Ŏw�肵��
		�T���v�����O���[�g"�ȉ���"�����f�[�^���Đ��\�ł��B<br>
		<br>
		\par ���l:
		�ő�T���v�����O���[�g�������邱�ƂŁAAtom�v���[���쐬���ɕK�v�ƂȂ郏�[�N������
		�̃T�C�Y��}���邱�Ƃ��\�ł��B
		\attention
		�w�肳�ꂽ�ő�T���v�����O���[�g�𒴂���f�[�^�́A�Đ����邱�Ƃ͂ł��܂���B<br>
		�Ⴆ�΁A�ő�T���v�����O���[�g��24000�ɐݒ肵���ꍇ�A�쐬���ꂽAtom�v���[����
		48000Hz�̉������Đ����邱�Ƃ͂ł��܂���B<br>
		�i�_�E���T���v�����O����ďo�͂���邱�Ƃ͂���܂���B�j
	*/
	CriSint32 max_sampling_rate;

	/*JP
		\brief �X�g���[�~���O�Đ����s�����ǂ���
		\par ����:
		Atom�v���[���ŃX�g���[�~���O�Đ��i�t�@�C������̍Đ��j���s�����ǂ������w�肵�܂��B<br>
		streaming_flag��CRI_FALSE���w�肵���ꍇ�A�쐬���ꂽAtom�v���[���̓I���������̃f�[�^
		�Đ��i ::criAtomPlayer_SetData �֐��Ŏw�肵���������A�h���X�̍Đ��j�݂̂��T�|�[�g
		���܂��B�i�t�@�C������̍Đ��͂ł��܂���B�j<br>
		streaming_flag��CRI_TRUE���w�肵���ꍇ�A�쐬���ꂽAtom�v���[���̓I���������̃f�[�^
		�Đ��ɉ����A�t�@�C������̍Đ����T�|�[�g���܂��B<br>
		\par �⑫:
		streaming_flag��CRI_TRUE�ɂ����ꍇ�AAtom�v���[���쐬���Ƀt�@�C���ǂݍ��ݗp�̃��\�[�X
		���m�ۂ���܂��B<br>
		���̂��߁Astreaming_flag��CRI_FALSE�̏ꍇ�ɔ�ׁAAtom�v���[���̍쐬�ɕK�v�ȃ�������
		�T�C�Y���傫���Ȃ�܂��B
	*/
	CriBool streaming_flag;
} CriAtomHcaMxPlayerConfig;

struct CriAtomPlayerTag;
/*JP
 * \brief Atom�v���[���n���h��
 * \ingroup ATOMLIB_PLAYER
 * \par ����:
 * Atom�v���[���́A�g�`�f�[�^���Đ����邽�߂̍ŏ����̃v���[���I�u�W�F�N�g�ł��B<br>
 * Atom�v���[���̍쐬���@�͗p�r�ɂ��قȂ�܂����A
 * �v���[���̃n���h���ɑ΂��Ă͋��ʂ�API�ő�����s�����Ƃ��\�ł��B<br>
 * \attention
 * Atom�v���[����AtomEx�v���[���͕ʕ��ł��B<br>
 * AtomEx�v���[����Atom Craft�ō쐬���ꂽ�V�[�P���X�f�[�^�̍Đ����s���܂����A
 * Atom�v���[���͒P�̂̔g�`�f�[�^���Đ�������̂ł��B<br>
 * \par �⑫:
 * LE�ł�Atom���C�u�����ł́A���[�U��Atom�v���[�����쐬������A
 * Atom�v���[��API���g�p���Ĕg�`�t�@�C�����Đ������邱�Ƃ͂ł��܂���B<br>
 * �i�{�C�X�v�[�����쐬�����ہA���C�u��������Atom�v���[�����쐬����܂����A
 * ���[�U��Atom�v���[���𒼐ڑ��삷��̂́A����V�[�����X�A���Đ����s���ꍇ�݂̂ł��B�j<br>
 * \sa criAtomPlayer_SetWaveId, criAtomPlayer_SetPreviousDataAgain
 */
typedef struct CriAtomPlayerTag *CriAtomPlayerHn;

/*==========================================================================
 *      CRI Atom D-BAS API
 *=========================================================================*/
/*JP
 * \brief Atom D-BAS ID
 * \ingroup ATOMLIB_DBAS
 * \par ����:
 * CriAtomDbasId �́AD-BAS�Ǘ��p��ID�ł��B<br>
 * ::criAtomDbas_Create �֐���D-BAS���쐬����Ǝ擾�ł��܂��B
 * <br>
 * �A�v���P�[�V����������D-BAS ID�𗘗p����̂́AD-BAS�̔j�����݂̂ł��B
 * \sa criAtomDbas_Create, criAtomDbas_Destroy
 */
typedef CriSint32 CriAtomDbasId;

/*JP
 * \brief D-BAS�쐬�p�����[�^�\����
 * \ingroup ATOMLIB_DBAS
 * \par ����:
 * ::criAtomDbas_Create �֐��̈����Ɏw�肷��AD-BAS�̍쐬�p�����[�^�\���̂ł��B<br>
 * <br>
 * \attention
 * �����I�Ƀ����o��������\�������邽�߁A ::criAtomDbas_SetDefaultConfig
 * �}�N�����g�p���Ȃ��ꍇ�ɂ́A�g�p�O�ɕK���\���̂��[���N���A���Ă��������B<br>
 * �i�\���̂̃����o�ɕs��l������Ȃ��悤�����ӂ��������B�j
 * \sa criAtomDbas_Create, criAtomDbas_CalculateWorkSize, criAtomDbas_SetDefaultConfig
 */
typedef struct CriAtomDbasConfigTag {
	/*JP
		\brief D-BAS ���ʎq
		\par ����:
		�A�v���P�[�V��������D-BAS���쐬����ۂɎw�肷�鎯�ʎq�ł��B<br>
		�A�v���P�[�V���������ǂ�D-BAS���g���������I�Ɏw�肷��ۂɎg�p���܂��B<br>
	*/
	CriUint32 identifier;				/*JP< D-BAS ���ʎq	*/
	/*JP
		\brief �ő�X�g���[�~���O��
		\par ����:
		D-BAS�ŊǗ�����u�ԍő�X�g���[�~���O�{�����w�肵�܂��B<br>
		�I�[�f�B�I�����łȂ��ASofdec2�ōĐ����郀�[�r�[�f�[�^�̃X�g���[�~���O�{������������K�v������܂��B<br>
		�Ⴆ�΁A�V�[��A�ł̓I�[�f�B�I�f�[�^���Q�{�A
		�V�[��B�ł̓I�[�f�B�I�f�[�^���P�{�ƃ��[�r�[�f�[�^���Q�{�A�X�g���[�~���O�Đ�����Ƃ��܂��B<br>
		���̏ꍇ�A�u�ԍő�X�g���[�~���O�{���̓V�[��B�̂R�{��ݒ肵�Ă��������B<br>
		�܂�A�A�v���P�[�V�����S�̂�ʂ��āA�ň���Ԃ̃X�g���[�~���O�{����z�肵���l��ݒ肵�Ă��������B
	*/
	CriSint32 max_streams;
	/*JP
		\brief �ő�r�b�g���[�g
		\par ����:
		�X�g���[�~���O�S�̂ɂ�����u�ԍő�r�b�g���[�g���w�肵�܂��B<br>
		���̒l�ɂ́A�A�v���P�[�V�����S�̂�ʂ��āA
		�X�g���[�~���O�Đ�����f�[�^�̏���r�b�g���[�g�̃s�[�N�l��ݒ肵�Ă��������B<br>
		�I�[�f�B�I�����łȂ��ASofdec2�ōĐ����郀�[�r�[�f�[�^�̏���r�b�g���[�g����������K�v������܂��B<br>
		�Ⴆ�΁A�V�[��A�ł̓I�[�f�B�I�f�[�^���S�{�A�V�[��B�ł̓��[�r�[�f�[�^���P�{�A�X�g���[�~���O�Đ�����Ƃ��܂��B<br>
		���̎��A�I�[�f�B�I�f�[�^�S�{���̏���r�b�g���[�g�������[�r�[�f�[�^�P�{�̏���r�b�g���[�g���傫���ꍇ�A<br>
		���[�r�[�f�[�^�̏���r�b�g���[�g��ݒ肵�Ă��������B<br>
		�܂�A�A�v���P�[�V�����S�̂�ʂ��āA�ň���Ԃ̏���r�b�g���[�g��z�肵���l��ݒ肵�Ă��������B
	*/
	CriSint32 max_bps;
	/*JP
		\brief CRI Mana���ōĐ�����ő�X�g���[�~���O��
		\par ����:
		CRI Mana���ōĐ�����u�ԍő�X�g���[�~���O�{�����w�肵�܂��B<br>
		D-BAS�̃������g�p�ʂ̌v�Z�ł́Amax_streams ���炱�̒l���������X�g���[�~���O�{�����A<br>
		CRI Atom�̍ő�X�g���[�~���O�{���Ƃ��Ĉ����܂��B<br>
		CRI Mana���ŃX�g���[�~���O�Đ����s��Ȃ��ꍇ�� 0 �ɐݒ肵�Ă��������B<br>
	*/
	CriSint32 max_mana_streams;
	/*JP
		\brief CRI Mana���ōĐ�����ő�r�b�g���[�g
		\par ����:
		CRI Mana���ōĐ�����u�ԍő�r�b�g���[�g���w�肵�܂��B<br>
		D-BAS�̃������g�p�ʂ̌v�Z�ł́Amax_bps ���炱�̒l���������r�b�g���[�g���A<br>
		CRI Atom�̍ő�r�b�g���[�g�Ƃ��Ĉ����܂��B<br>
		CRI Mana���ŃX�g���[�~���O�Đ����s��Ȃ��ꍇ�� 0 �ɐݒ肵�Ă��������B<br>
	*/
	CriSint32 max_mana_bps;
} CriAtomDbasConfig;

/* ========================================================================*/
/*       CRI Atom Meter API                                                */
/* ========================================================================*/

/*JP
 * \brief ���x�����[�^�@�\�ǉ��p�R���t�B�O�\����
 * \ingroup ATOMLIB_METER
 * \par ����:
 * ���x�����[�^�@�\��ǉ����邽�߂̍\���̂ł��B<br>
 * ::criAtomMeter_AttachLevelMeter �֐��̈����Ɏw�肵�܂��B<br>
 * \par ���l:
 * �f�t�H���g�ݒ���g�p����ꍇ�A ::criAtomMeter_SetDefaultConfigForLevelMeter �}�N����
 * �\���̂Ƀf�t�H���g�p�����[�^���Z�b�g������A ::criAtomMeter_AttachLevelMeter �֐�
 * �ɍ\���̂��w�肵�Ă��������B<br>
 * \attention
 * �����I�Ƀ����o��������\�������邽�߁A ::criAtomMeter_SetDefaultConfigForLevelMeter
 * �}�N�����g�p���Ȃ��ꍇ�ɂ́A�g�p�O�ɕK���\���̂��[���N���A���Ă��������B<br>
 * �i�\���̂̃����o�ɕs��l������Ȃ��悤�����ӂ��������B�j
 * \sa criAtomMeter_AttachLevelMeter
 */
typedef struct {
	/*JP
		\brief ����Ԋu�i�~���b�P�ʁj
		\par ����:
		���茋�ʂ��X�V����Ԋu�ł��B<br>
	*/
	CriSint32 interval;

	/*JP
		\brief �s�[�N�z�[���h���ԁi�~���b�P�ʁj
		\par ����:
		�s�[�N�l�����傫���l�ōX�V���ꂽ�Ƃ��A������Ȃ��悤�Ƀz�[���h���鎞�Ԃł��B<br>
	*/
	CriSint32 hold_time;
} CriAtomLevelMeterConfig;

/*JP
 * \brief ���x�����
 * \ingroup ATOMLIB_METER
 * \par ����:
 * ���x�������擾���邽�߂̍\���̂ł��B<br>
 * ::criAtomMeter_GetLevelInfo �֐��ŗ��p���܂��B
 * \par ���l:
 * �e���x���l�̒P�ʂ�dB�ł��B<br>
 * \sa criAtomMeter_GetLevelInfo
 */
typedef struct CriAtomLevelInfoTag {
	/*JP
		\brief �L���`�����l����
		\par ����:
		���茋�ʂ��L���ȃ`�����l�����ł��B<br>
	*/
	CriSint32 num_channels;
	
	/*JP
		\brief RMS���x��
		\par ����:
		����Ԋu�Ԃ̉����U����RMS�i��敽�ϕ������j���v�Z�����l�ł��B<br>
		�������x���Ƃ��Ĉ����܂��B
	*/
	CriFloat32 rms_levels[8];
	
	/*JP
		\brief �s�[�N���x��
		\par ����:
		����Ԋu�Ԃ̉����U���̍ő�l�ł��B<br>
	*/
	CriFloat32 peak_levels[8];
	
	/*JP
		\brief �s�[�N�z�[���h���x��
		\par ����:
		�z�[���h���Ă���s�[�N���x���l�ł��B<br>
	*/
	CriFloat32 peak_hold_levels[8];
} CriAtomLevelInfo;

/***************************************************************************
 *      �ϐ��錾
 *      Prototype Variables
 ***************************************************************************/

/***************************************************************************
 *      �֐��錾
 *      Prototype Functions
 ***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/
/*JP
 * \brief ���C�u�����o�[�W�����ԍ��̎擾
 * \ingroup ATOMLIB_GLOBAL
 * \return		CriUint32	�o�[�W�����ԍ�
 * \par ����:
 * ���C�u�����̃o�[�W�����ԍ����擾���܂��B<br>
 * �{�֐��Ŏ擾�����l�ƃw�b�_�t�@�C���i cri_atom.h �j�ɋL�ڂ��ꂽ
 * CRI_ATOM_VERSION �̒l���قȂ�ꍇ�A�C���N���[�h���Ă���w�b�_�ƁA
 * �����N���Ă��郉�C�u�����̃o�[�W��������v���Ă��Ȃ��\��������܂��B<br>
 * �i�r���h���ɐݒ肳�ꂽ�C���N���[�h�p�X�ƃ��C�u�����p�X���m�F���Ă��������B�j<br>
 * \par ���l:
 * �ȉ��̃R�[�h�ŁA�f�o�b�O���Ƀ��C�u�����ƃw�b�_�o�[�W�����̕s��v�����o�\�ł��B<br>
 * \code
 * 		�F
 * 	// ���C�u�����ƃw�b�_�̐��������`�F�b�N
 * 	assert(CRI_ATOM_VERSION == criAtom_GetVersionNumber());
 * 		�F
 * \endcode
 */
CriUint32 CRIAPI criAtom_GetVersionNumber(void);

/*JP
 * \brief �������m�ۊ֐��̓o�^
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	func		�������m�ۊ֐�
 * \param[in]	obj			���[�U�w��I�u�W�F�N�g
 * \par ����:
 * CRI Atom���C�u�����Ƀ������m�ۊ֐���o�^���܂��B<br>
 * CRI Atom���C�u�����������C�u�������ōs���������m�ۏ������A
 * ���[�U�Ǝ��̃������m�ۏ����ɒu�����������ꍇ�Ɏg�p���܂��B<br>
 * <br>
 * �{�֐��̎g�p�菇�͈ȉ��̂Ƃ���ł��B<br>
 * (1) ::CriAtomMallocFunc �C���^�[�t�F�[�X�ɕ������������m�ۊ֐���p�ӂ���B<br>
 * (2) ::criAtom_SetUserMallocFunction �֐����g�p���ACRI Atom���C�u�����ɑ΂���
 * �������m�ۊ֐���o�^����B<br>
 * <br>
 * ��̓I�ȃR�[�h�̗�͈ȉ��̂Ƃ���ł��B
 * \par ��:
 * \code
 * // �Ǝ��̃������m�ۊ֐���p��
 * void *user_malloc(void *obj, CriUint32 size)
 * {
 * 	void *mem;
 *
 * 	// �������̊m��
 * 	mem = malloc(size);
 *
 * 	return (mem);
 * }
 *
 * main()
 * {
 * 		:
 * 	// �������m�ۊ֐��̓o�^
 * 	criAtom_SetUserMallocFunction(user_malloc, NULL);
 * 		:
 * }
 * \endcode
 * \par ���l:
 * ������ obj �Ɏw�肵���l�́A ::CriAtomMallocFunc �Ɉ����Ƃ��ēn����܂��B<br>
 * �������m�ێ��Ƀ������}�l�[�W�������Q�Ƃ���K�v������ꍇ�ɂ́A
 * ���Y�I�u�W�F�N�g��{�֐��̈����ɃZ�b�g���Ă����A�R�[���o�b�N�֐��ň������o�R
 * ���ĎQ�Ƃ��Ă��������B<br>
 * \attention
 * �������m�ۊ֐���o�^����ۂɂ́A���킹�ă���������֐��i ::CriAtomFreeFunc �j��
 * �o�^����K�v������܂��B
 * \sa CriAtomMallocFunc, criAtom_SetUserFreeFunction
 */
void CRIAPI criAtom_SetUserMallocFunction(CriAtomMallocFunc func, void *obj);

/*JP
 * \brief ����������֐��̓o�^
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	func		����������֐�
 * \param[in]	obj			���[�U�w��I�u�W�F�N�g
 * \par ����:
 * CRI Atom���C�u�����Ƀ���������֐���o�^���܂��B<br>
 * CRI Atom���C�u�����������C�u�������ōs������������������A
 * ���[�U�Ǝ��̃�������������ɒu�����������ꍇ�Ɏg�p���܂��B<br>
 * <br>
 * �{�֐��̎g�p�菇�͈ȉ��̂Ƃ���ł��B<br>
 * (1) ::CriAtomFreeFunc �C���^�[�t�F�[�X�ɕ���������������֐���p�ӂ���B<br>
 * (2) ::criAtom_SetUserFreeFunction �֐����g�p���ACRI Atom���C�u�����ɑ΂���
 * ����������֐���o�^����B<br>
 * <br>
 * ��̓I�ȃR�[�h�̗�͈ȉ��̂Ƃ���ł��B
 * \par ��:
 * \code
 * // �Ǝ��̃���������֐���p��
 * void user_free(void *obj, void *mem)
 * {
 * 	// �������̉��
 * 	free(mem);
 *
 * 	return;
 * }
 *
 * main()
 * {
 * 		:
 * 	// ����������֐��̓o�^
 * 	criAtom_SetUserFreeFunction(user_free, NULL);
 * 		:
 * }
 * \endcode
 * \par ���l:
 * ������ obj �Ɏw�肵���l�́A ::CriAtomFreeFunc �Ɉ����Ƃ��ēn����܂��B<br>
 * �������m�ێ��Ƀ������}�l�[�W�������Q�Ƃ���K�v������ꍇ�ɂ́A
 * ���Y�I�u�W�F�N�g��{�֐��̈����ɃZ�b�g���Ă����A�R�[���o�b�N�֐��ň������o�R
 * ���ĎQ�Ƃ��Ă��������B<br>
 * \attention
 * ����������֐���o�^����ۂɂ́A���킹�ă������m�ۊ֐��i ::CriAtomMallocFunc �j��
 * �o�^����K�v������܂��B
 * \sa CriAtomFreeFunc, criAtom_SetUserMallocFunction
 */
void CRIAPI criAtom_SetUserFreeFunction(CriAtomFreeFunc func, void *obj);

/*JP
 * \brief �T�[�o�����̊��荞�݂�h�~
 * \ingroup ATOMLIB_GLOBAL
 * \par ����:
 * �T�[�o�����̊��荞�ݗ}�~���܂��B<br>
 * �{�֐����s��A::criAtom_Unlock�֐����s�܂ł̊ԁA�T�[�o�����̓��삪�}�~����܂��B<br>
 * ������API�𓯈�I�[�f�B�I�t���[�����Ŋm���Ɏ��s�������ꍇ�ɂ́A�{�֐��ŃT�[�o������
 * ���荞�݂�h�~���A�����̊֐������s���Ă��������B
 * \par ��:
 * \code
 * 	�F
 * // �T�[�o�����̊��荞�݂�h�~
 * criAtom_Lock();
 *
 * // �����̉����𓯎��ɍĐ��J�n
 * criAtomPlayer_Start(player1);
 * criAtomPlayer_Start(player2);
 * criAtomPlayer_Start(player3);
 * criAtomPlayer_Start(player4);
 *
 * // �T�[�o�����̊��荞�ݖh�~������
 * criAtom_Unlock();
 * 	�F
 * \endcode
 * \attention
 * ��L�̗�̂悤�ɁA�����̃v���[���œ����ɍĐ����X�^�[�g����ꍇ�ł��A
 * �X�g���[���Đ����͓����ɔ������J�n�����Ƃ͌���܂���B<br>
 * �i�o�b�t�@�����O�ɔ����Đ��x�������邽�߁B�j<br>
 * <br>
 * �{�֐����s��A������::criAtom_Unlock�֐����Ă΂Ȃ��ꍇ�A�����Đ����r�؂�鋰�ꂪ����܂��B<br>
 * �T�[�o�����̊��荞�݂�h�~�����Ԃ́A�ŏ����ɗ}����K�v������܂��B
 * \sa criAtom_Unlock
 */
void CRIAPI criAtom_Lock(void);

/*JP
 * \brief �T�[�o�����̊��荞�ݖh�~������
 * \ingroup ATOMLIB_GLOBAL
 * \par ����:
 * ::criAtom_Lock�֐��ɂ��A�T�[�o�����̊��荞�ݖh�~���������܂��B
 * \sa criAtom_Lock
 */
void CRIAPI criAtom_Unlock(void);

/*JP
 * \brief �p�t�H�[�}���X���j�^�@�\�̒ǉ�
 * \ingroup ATOMLIB_GLOBAL
 * \par ����:
 * �p�t�H�[�}���X�v���@�\��ǉ����A�p�t�H�[�}���X�v���������J�n���܂��B<br>
 * �{�֐������s��A ::criAtom_GetPerformanceInfo �֐������s���邱�ƂŁA
 * �T�[�o�����̕��ׂ�A�T�[�o�����̎��s�Ԋu���A���C�u�����̃p�t�H�[�}���X����
 * �擾���邱�Ƃ��\�ł��B
 * \sa criAtom_GetPerformanceInfo, criAtom_DetachPerformanceMonitor
 * \par ��:
 * \code
 * 	// �p�t�H�[�}���X���擾�p�\����
 * 	CriAtomPerformanceInfo info;
 *
 * 	// ���C�u�����̏�����
 * 	criAtom_Initialize(�c);
 *
 * 	// �p�t�H�[�}���X���j�^�@�\�̒ǉ�
 * 	criAtom_AttachPerformanceMonitor();
 *
 * 	// �p�t�H�[�}���X���j�^�̃��Z�b�g
 * 	criAtom_ResetPerformanceMonitor();
 *
 * 	// �p�t�H�[�}���X�v�����
 * 	�c
 *
 * 	// �p�t�H�[�}���X���̎擾
 * 	criAtom_GetPerformanceInfo(&info);
 *
 * 	// �v�����ʂ̕\��
 * 	printf(
 * 		"Max CPU Load            : %d (us)\n"	\
 * 		"Average CPU Load        : %d (us)\n"	\
 * 		"Max Server Interval     : %d (us)\n"	\
 * 		"Average Server Interval : %d (us)\n",
 * 		info.max_server_time, info.average_server_time,
 * 		info.max_server_interval, info.average_server_interval
 * 	);
 * \endcode
 */
void CRIAPI criAtom_AttachPerformanceMonitor(void);

/*JP
 * \brief �p�t�H�[�}���X���j�^�@�\�̍폜
 * \ingroup ATOMLIB_GLOBAL
 * \par ����:
 * �p�t�H�[�}���X�v���������I�����A�p�t�H�[�}���X�v���@�\���폜���܂��B
 * \attention
 * �{�֐��͊������A�^�̊֐��ł��B<br>
 * �{�֐������s����ƁA���΂炭�̊�Atom���C�u�����̃T�[�o�������u���b�N����܂��B<br>
 * �����Đ����ɖ{�֐������s����ƁA���r�؂ꓙ�̕s�����������\�������邽�߁A
 * �{�֐��̌Ăяo���̓V�[���̐؂�ւ�蓙�A���וϓ������e�ł���^�C�~���O�ōs���Ă��������B
 */
void CRIAPI criAtom_DetachPerformanceMonitor(void);

/*JP
 * \brief �p�t�H�[�}���X���j�^�̃��Z�b�g
 * \ingroup ATOMLIB_GLOBAL
 * \par ����:
 * ���݂܂ł̌v�����ʂ�j�����܂��B<br>
 * �p�t�H�[�}���X���j�^�́A ::criAtom_AttachPerformanceMonitor �֐����s����
 * ����p�t�H�[�}���X���̎擾���J�n���A�v�����ʂ�ݐς��܂��B<br>
 * ���ꂩ��v�������Ԃɑ΂��A�ȑO�̌v�����ʂ��ȍ~�̌v�����ʂɊ܂߂����Ȃ��ꍇ�ɂ́A
 * �{�֐������s���A�ݐς��ꂽ�v�����ʂ���U�j������K�v������܂��B
 */
void CRIAPI criAtom_ResetPerformanceMonitor(void);

/*JP
 * \brief �p�t�H�[�}���X���̎擾
 * \ingroup ATOMLIB_GLOBAL
 * \par ����:
 * �p�t�H�[�}���X�����擾���܂��B<br>
 * �{�֐��́A ::criAtom_AttachPerformanceMonitor �֐����s�ォ��
 * ::criAtom_DetachPerformanceMonitor �֐������s����܂ł̊ԁA���p�\�ł��B<br>
 * \sa criAtom_AttachPerformanceMonitor, criAtom_DetachPerformanceMonitor
 */
void CRIAPI criAtom_GetPerformanceInfo(CriAtomPerformanceInfo *info);

/*JP
 * \brief ADX�f�[�^�̃r�b�g���[�g�v�Z
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	num_channels	�f�[�^�̃`�����l����
 * \param[in]	sampling_rate	�f�[�^�̃T���v�����O���[�g
 * \return		CriSint32		�r�b�g���[�g[bps]
 * \par ����:
 * ADX�f�[�^�̃r�b�g���[�g���v�Z���܂��B<br>
 * �v�Z�Ɏ��s����Ɩ{�֐���-1��Ԃ��܂��B<br>
 * �v�Z�Ɏ��s�������R�ɂ��ẮA�G���[�R�[���o�b�N�̃��b�Z�[�W�Ŋm�F�\�ł��B<br>
 */
CriSint32 CRIAPI criAtom_CalculateAdxBitrate(
	CriSint32 num_channels, CriSint32 sampling_rate);

/*JP
 * \brief HCA�f�[�^�̃r�b�g���[�g�v�Z
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	num_channels	�f�[�^�̃`�����l����
 * \param[in]	sampling_rate	�f�[�^�̃T���v�����O���[�g
 * \param[in]	quality			�f�[�^�̃G���R�[�h�i��
 * \return		CriSint32		�r�b�g���[�g[bps]
 * \par ����:
 * HCA�f�[�^�̃r�b�g���[�g���v�Z���܂��B<br>
 * �v�Z�Ɏ��s����Ɩ{�֐���-1��Ԃ��܂��B<br>
 * �v�Z�Ɏ��s�������R�ɂ��ẮA�G���[�R�[���o�b�N�̃��b�Z�[�W�Ŋm�F�\�ł��B<br>
 * \par ���l:
 * quality�ɂ�CRI Atom Craft�܂���CRI Atom Encoder�Őݒ肵���G���R�[�h�i�����w�肵�܂��B
 */
CriSint32 CRIAPI criAtom_CalculateHcaBitrate(
	CriSint32 num_channels, CriSint32 sampling_rate, CriAtomEncodeQuality quality);

/*JP
 * \brief HCA-MX�f�[�^�̃r�b�g���[�g�v�Z
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	num_channels	�f�[�^�̃`�����l����
 * \param[in]	sampling_rate	�f�[�^�̃T���v�����O���[�g
 * \param[in]	quality			�f�[�^�̃G���R�[�h�i��
 * \return		CriSint32		�r�b�g���[�g[bps]
 * \par ����:
 * HCA-MX�f�[�^�̃r�b�g���[�g���v�Z���܂��B<br>
 * �v�Z�Ɏ��s����Ɩ{�֐���-1��Ԃ��܂��B<br>
 * �v�Z�Ɏ��s�������R�ɂ��ẮA�G���[�R�[���o�b�N�̃��b�Z�[�W�Ŋm�F�\�ł��B<br>
 * \par ���l:
 * quality�ɂ�CRI Atom Craft�܂���CRI Atom Encoder�Őݒ肵���G���R�[�h�i�����w�肵�܂��B
 */
CriSint32 CRIAPI criAtom_CalculateHcaMxBitrate(
	CriSint32 num_channels, CriSint32 sampling_rate, CriAtomEncodeQuality quality);

/*==========================================================================
 *      CRI Atom AWB API
 *=========================================================================*/

/*==========================================================================
 *      CRI Atom Player API
 *=========================================================================*/
/*JP
 * \brief �����f�[�^�̃Z�b�g�i�����f�[�^ID�̎w��j
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom�v���[���n���h��
 * \param[in]	awb			AWB�n���h��
 * \param[in]	id			�g�`�f�[�^ID
 * \par ����:
 * �Đ�����g�`�f�[�^��Atom�v���[���Ɋ֘A�t���܂��B<br>
 * �f�[�^�v���R�[���o�b�N�֐����� �{�֐������s���邱�ƂŁA
 * �����t�@�C����A�����čĐ�����
 * �i�Đ����̉����ƃZ�b�g�����������Ȃ��čĐ�����j���Ƃ��\�ł��B
 * \attention
 * �t�@�C������̍Đ����s���ꍇ�ɂ́A�X�g���[�~���O�Đ��ɑΉ�����
 * Atom�v���[�����g�p����K�v������܂��B<br>
 * �i ::CriAtomStandardPlayerConfig ��streaming_flag��CRI_TRUE��ݒ肵��
 * Atom�v���[�����쐬����K�v������܂��B�j<br>
 * \par ���l:
 * HCA-MX�f�[�^�ɑ΂��ăV�[�����X�A���Đ����s�����Ƃ͂ł��܂���B<br>
 * \sa criAtomExPlayer_SetDataRequestCallback
 */
void CRIAPI criAtomPlayer_SetWaveId(
	CriAtomPlayerHn player, CriAtomAwbHn awb, CriSint32 id);

/*JP
 * \brief ���ꉹ���f�[�^�̍ăZ�b�g
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom�v���[���n���h��
 * \par ����:
 * �O��Đ������f�[�^���A�ēx�Đ�����悤Atom�v���[���Ɏw�����܂��B<br>
 * \par ��:
 * �ȉ��̏����ɂ��A���ꉹ���f�[�^�𖳌��Ƀ��[�v�Đ��\�ł��B<br>
 * \code
 * // �f�[�^�v���R�[���o�b�N�֐�
 * void on_data_request(void *obj, CriAtomPlayerHn player)
 * {
 * 	// �O��Đ������f�[�^���ăZ�b�g
 * 	criAtomPlayer_SetPreviousDataAgain(player);
 * }
 *
 * main()
 * {
 * 		:
 * 	// �f�[�^�v���R�[���o�b�N�֐��̓o�^
 * 	criAtomExPlayer_SetDataRequestCallback(player, on_data_request, NULL);
 * 	
 * 	// �����f�[�^���Z�b�g
 * 	criAtomExPlayer_SetCueName(player, acb_hn, "MUSIC1");
 * 	
 * 	// �Z�b�g���ꂽ�����f�[�^���Đ�
 * 	criAtomExPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * \attention
 * �{�֐��̓f�[�^�v���R�[���o�b�N�֐����ł̂ݎg�p���܂��B<br>
 * �i�f�[�^�v���R�[���o�b�N�֐��O�ł����s�\�ł����A���̏ꍇ���̌��ʂ�����܂���B�j<br>
 * \sa criAtomExPlayer_SetDataRequestCallback
 */
void CRIAPI criAtomPlayer_SetPreviousDataAgain(CriAtomPlayerHn player);

/*JP
 * \brief �R�[���o�b�N�֐��̍Ď��s�v��
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom�v���[���n���h��
 * \par ����:
 * �f�[�^�v���R�[���o�b�N�֐��̏�����扄�΂����܂��B<br>
 * �f�[�^�v���R�[���o�b�N�֐������s���ꂽ���_�ŁA���ɍĐ����鉹���f�[�^��
 * �܂����܂��Ă��Ȃ��ꍇ�A�{�֐������s���邱�ƂŁA�R�[���o�b�N�֐������g���C
 * ���邱�Ƃ��\�ɂȂ�܂��B<br>
 * �i���~���b��ɍēx�f�[�^�v���R�[���o�b�N�֐����Ă΂�܂��B�j
 * \par ���l:
 * �f�[�^�v���R�[���o�b�N�֐����ŉ������Ȃ������ꍇ�AAtom�v���[���̃X�e�[�^�X��
 * CRIATOMPLAYER_STATUS_PLAYEND �ɑJ�ڂ��܂��B<br>
 * �������A�f�[�^�v���R�[���o�b�N�֐����Ŗ{�֐������s�����ꍇ�AAtom�v���[����
 * �X�e�[�^�X�� CRIATOMPLAYER_STATUS_PLAYING ���ێ��������܂��B
 * \attention
 * �{�֐������s�����ꍇ�AAtom�v���[���̃X�e�[�^�X�� CRIATOMPLAYER_STATUS_PLAYING
 * ���ێ��������܂����A�����o�͓͂r�؂��\��������܂��B<br>
 * �i�f�[�^�̓ǂݍ��݂��Ԃɍ���Ȃ��ꍇ�A�O��Đ����������ƁA���ɃZ�b�g���鉹��
 * �Ƃ̊ԂɁA����������\��������܂��B�j<br>
 * <br>
 * �{�֐��̓f�[�^�v���R�[���o�b�N�֐����ł̂ݎg�p�\�ł��B<br>
 * �i�f�[�^�v���R�[���o�b�N�֐��O�Ŏ��s�����ꍇ�A�G���[���������܂��B�j<br>
 * \sa criAtomExPlayer_SetDataRequestCallback
 */
void CRIAPI criAtomPlayer_DeferCallback(CriAtomPlayerHn player);

/*==========================================================================
 *      CRI Atom D-BAS API
 *=========================================================================*/
/*JP
 * \brief D-BAS�쐬�p���[�N�T�C�Y�̌v�Z
 * \ingroup ATOMLIB_DBAS
 * \param[in]	config		D-BAS�쐬�p�R���t�B�O�\���̂ւ̃|�C���^
 * \return		CriSint32	D-BAS�쐬�p���[�N�T�C�Y
 * \retval		0�ȏ�		����ɏ���������
 * \retval		-1			�G���[������
 * \par ����:
 * D-BAS�쐬�p�p�����[�^�Ɋ�Â��āAD-BAS�̍쐬�ɕK�v���[�N�T�C�Y���v�Z���܂��B<br>
 * <br>
 * ���[�N�̈�T�C�Y�̌v�Z�Ɏ��s����ƁA�{�֐��� -1 ��Ԃ��܂��B<br>
 * ���[�N�̈�T�C�Y�̌v�Z�Ɏ��s�������R�ɂ��ẮA�G���[�R�[���o�b�N�̃��b�Z�[�W�Ŋm�F�\�ł��B<br>
 * \attention
 * �{�֐������s����O�ɁA���C�u���������������Ă����K�v������܂��B<br>
 * <br>
 * �ݒ�ɂ���ẮAD-BAS��2GB�ȏ�̃��[�N�T�C�Y��K�v�Ƃ���ꍇ������A<br>
 * ���̍ۂ̓G���[�ɂȂ�A -1 ��Ԃ��܂��B<br>
 * �G���[�����������ꍇ�́Amax_streams��max_bps�̒l��Ⴍ�ݒ肵�Ă��������B<br>
 * \sa criAtomDbas_Create
 */
CriSint32 CRIAPI criAtomDbas_CalculateWorkSize(const CriAtomDbasConfig *config);

/*JP
 * \brief D-BAS�̍쐬
 * \ingroup ATOMLIB_DBAS
 * \param[in]	config			D-BAS�쐬�p�R���t�B�O�\���̂ւ̃|�C���^
 * \param[in]	work			D-BAS�쐬�p���[�N�̈�ւ̃|�C���^
 * \param[in]	work_size		D-BAS�쐬�p���[�N�T�C�Y
 * \return		CriAtomDbasId	D-BAS�Ǘ��pID
 * \par ����:
 * D-BAS�쐬�p�p�����[�^�Ɋ�Â��āAD-BAS���쐬���܂��B<br>
 * �쐬�ɐ�������ƁAD-BAS�����C�u�����ɓo�^���A�L���ȊǗ��pID��Ԃ��܂��B<br>
 * D-BAS�̍쐬�Ɏ��s�����ꍇ�A�{�֐��� ::CRIATOMDBAS_ILLEGAL_ID ��Ԃ��܂��B<br>
 * �i�G���[�̌����̓G���[�R�[���o�b�N�ɕԂ���܂��B�j<br>
 * <br>
 * �擾����ID��::criAtomDbas_Destroy �֐��Ŏg�p���܂��B<br>
 * \attention
 * �{�֐������s����O�ɁA���C�u���������������Ă����K�v������܂��B<br>
 * \sa criAtomDbas_CalculateWorkSize, criAtomDbas_Destroy
 */
CriAtomDbasId CRIAPI criAtomDbas_Create(
	const CriAtomDbasConfig *config, void *work, CriSint32 work_size);

/*JP
 * \brief D-BAS�̔j��
 * \ingroup ATOMLIB_DBAS
 * \param[in]	atom_dbas_id	D-BAS�Ǘ��pID
 * \par ����:
 * ::criAtomDbas_Create �֐��Ŏ擾�����Ǘ��pID���w�肵�āAD-BAS��j�����܂��B<br>
 * \sa criAtomDbas_Create
 */
void CRIAPI criAtomDbas_Destroy(CriAtomDbasId atom_dbas_id);

/* ========================================================================*/
/*       CRI Atom Meter API                                                */
/* ========================================================================*/
/*JP
 * \brief ���x�����[�^�@�\�p�̃��[�N�T�C�Y�̌v�Z
 * \ingroup ATOMLIB_METER
 * \param[in]	config			���x�����[�^�ǉ��p�̃R���t�B�O�\����
 * \return		CriSint32		�K�v�ȃ��[�N�̈�T�C�Y
 * \par ����:
 * ���x�����[�^�ǉ��ɕK�v�ȃ��[�N�̈�T�C�Y���v�Z���܂��B<br>
 * config ��NULL���w�肷��ƃf�t�H���g�ݒ�Ōv�Z����܂��B<br>
 * \sa criAtomMeter_AttachLevelMeter
 */
CriSint32 CRIAPI criAtomMeter_CalculateWorkSizeForLevelMeter(
	const CriAtomLevelMeterConfig *config);

/*JP
 * \brief ���x�����[�^�@�\�̒ǉ�
 * \ingroup ATOMLIB_METER
 * \param[in]	config			���x�����[�^�ǉ��p�̃R���t�B�O�\����
 * \param[in]	work			���[�N�̈�
 * \param[in]	work_size		���[�N�̈�T�C�Y
 * \par ����:
 * ���C�u�����Ƀ��x�����[�^�@�\��ǉ����܂��B<br>
 * config ��NULL���w�肷��ƃf�t�H���g�ݒ�Ń��x�����[�^���ǉ�����܂��B<br>
 * work ��NULL�Awork_size ��0���w�肷��ƁA�o�^���ꂽ���[�U�A���P�[�^�ɂ����
 * ���[�N�̈悪�m�ۂ���܂��B<br>
 * \sa criAtomMeter_GetLevelInfo
 */
void CRIAPI criAtomMeter_AttachLevelMeter(
	const CriAtomLevelMeterConfig *config, void *work, CriSint32 work_size);

/*JP
 * \brief ���x�����[�^�@�\�̉���
 * \ingroup ATOMLIB_METER
 * \param[in]	config			���x�����[�^�ǉ��p�̃R���t�B�O�\����
 * \param[in]	work			���[�N�̈�
 * \param[in]	work_size		���[�N�̈�T�C�Y
 * \par ����:
 * ���C�u�����̃��x�����[�^�@�\���������܂��B<br>
 * \sa criAtomMeter_AttachLevelMeter
 */
void CRIAPI criAtomMeter_DetachLevelMeter(void);

/*JP
 * \brief ���x�����̎擾
 * \ingroup ATOMLIB_METER
 * \param[out]	info			���x�����̍\����
 * \par ����:
 * ���x�����[�^�̌��ʂ��擾���܂��B<br>
 * �w�肷��o�X�ɂ� ::criAtomMeter_AttachLevelMeter �֐��ł��炩����
 * ���x�����[�^�@�\��ǉ����Ă����K�v������܂��B<br>
 * \sa criAtomMeter_AttachLevelMeter
 */
void CRIAPI criAtomMeter_GetLevelInfo(CriAtomLevelInfo *info);

#ifdef __cplusplus
}
#endif

#endif	/* CRI_INCL_CRI_LE_ATOM_H */

/* --- end of file --- */
