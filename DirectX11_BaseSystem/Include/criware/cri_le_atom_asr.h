/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2010-2013 CRI Middleware Co., Ltd.
 *
 * Library  : CRI Atom
 * Module   : Library User's Header
 * File     : cri_le_atom_asr.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_le_atom_asr.h
 */

/* ���d��`�h�~					*/
/* Prevention of redefinition	*/
#ifndef CRI_INCL_CRI_LE_ATOM_ASR_H
#define CRI_INCL_CRI_LE_ATOM_ASR_H

/***************************************************************************
 *      �C���N���[�h�t�@�C��
 *      Include files
 ***************************************************************************/
#include <cri_le_xpt.h>
#include <cri_le_atom.h>
#include <cri_le_atom_ex.h>

/***************************************************************************
 *      �萔�}�N��
 *      Macro Constants
 ***************************************************************************/
/*JP
 * \brief �ő�`�����l����
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * ASR�������\�ȍő�`�����l�����ł��B
 */
#define CRIATOMEXASR_MAX_CHANNELS		(8)

/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "GENERIC"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_GENERIC \
	{ -1000,  -100, 1.49f, 0.83f,  -2602, 0.007f,    200, 0.011f, 100.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "PADED CELL"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_PADDEDCELL \
	{ -1000, -6000, 0.17f, 0.10f,  -1204, 0.001f,    207, 0.002f, 100.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "ROOM"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_ROOM \
	{ -1000,  -454, 0.40f, 0.83f,  -1646, 0.002f,     53, 0.003f, 100.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "BATH ROOM"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_BATHROOM \
	{ -1000, -1200, 1.49f, 0.54f,   -370, 0.007f,   1030, 0.011f, 100.0f,  60.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "LIVING ROOM"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_LIVINGROOM \
	{ -1000, -6000, 0.50f, 0.10f,  -1376, 0.003f,  -1104, 0.004f, 100.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "STONE ROOM"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_STONEROOM \
	{ -1000,  -300, 2.31f, 0.64f,   -711, 0.012f,     83, 0.017f, 100.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "AUDITORIUM"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_AUDITORIUM \
	{ -1000,  -476, 4.32f, 0.59f,   -789, 0.020f,   -289, 0.030f, 100.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "CONCERT HALL"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_CONCERTHALL \
	{ -1000,  -500, 3.92f, 0.70f,  -1230, 0.020f,     -2, 0.029f, 100.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "CAVE"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_CAVE \
	{ -1000,     0, 2.91f, 1.30f,   -602, 0.015f,   -302, 0.022f, 100.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "ARENA"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_ARENA \
	{ -1000,  -698, 7.24f, 0.33f,  -1166, 0.020f,     16, 0.030f, 100.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "HANGER"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_HANGAR \
	{ -1000, -1000, 10.05f, 0.23f,   -602, 0.020f,    198, 0.030f, 100.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "CARPETED HALLWAY"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_CARPETEDHALLWAY \
	{ -1000, -4000, 0.30f, 0.10f,  -1831, 0.002f,  -1630, 0.030f, 100.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "HALLWAY"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_HALLWAY \
	{ -1000,  -300, 1.49f, 0.59f,  -1219, 0.007f,    441, 0.011f, 100.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "STONE CORRIDOR"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_STONECORRIDOR \
	{ -1000,  -237, 2.70f, 0.79f,  -1214, 0.013f,    395, 0.020f, 100.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "ALLEY"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_ALLEY \
	{ -1000,  -270, 1.49f, 0.86f,  -1204, 0.007f,     -4, 0.011f, 100.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "FOREST"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_FOREST \
	{ -1000, -3300, 1.49f, 0.54f,  -2560, 0.162f,   -613, 0.088f,  79.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "CITY"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_CITY \
	{ -1000,  -800, 1.49f, 0.67f,  -2273, 0.007f,  -2217, 0.011f,  50.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "MOUNTAINS"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_MOUNTAINS \
	{ -1000, -2500, 1.49f, 0.21f,  -2780, 0.300f,  -2014, 0.100f,  27.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "QUARRY"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_QUARRY \
	{ -1000, -1000, 1.49f, 0.83f, -10000, 0.061f,    500, 0.025f, 100.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "PLAIN"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_PLAIN \
	{ -1000, -2000, 1.49f, 0.50f,  -2466, 0.179f,  -2514, 0.100f,  21.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "PARKINGLOT"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_PARKINGLOT \
	{ -1000,     0, 1.65f, 1.50f,  -1363, 0.008f,  -1153, 0.012f, 100.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "SEWER PIPE"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_SEWERPIPE \
	{ -1000, -1000, 2.81f, 0.14f,    429, 0.014f,    648, 0.021f,  80.0f,  60.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "UNDER WATER"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_UNDERWATER \
	{ -1000, -4000, 1.49f, 0.10f,   -449, 0.007f,   1700, 0.011f, 100.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "SMALL ROOM"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_SMALLROOM \
	{ -1000,  -600, 1.10f, 0.83f,   -400, 0.005f,    500, 0.010f, 100.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "MEDIUM ROOM"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_MEDIUMROOM \
	{ -1000,  -600, 1.30f, 0.83f,  -1000, 0.010f,   -200, 0.020f, 100.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "LARGE ROOM"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_LARGEROOM \
	{ -1000,  -600, 1.50f, 0.83f,  -1600, 0.020f,  -1000, 0.040f, 100.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "MEDIUM HALL"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_MEDIUMHALL \
	{ -1000,  -600, 1.80f, 0.70f,  -1300, 0.015f,   -800, 0.030f, 100.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "LARGE HALL"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_LARGEHALL \
	{ -1000,  -600, 1.80f, 0.70f,  -2000, 0.030f,  -1400, 0.060f, 100.0f, 100.0f, 5000.0f}
/*JP
 * \brief I3DL2���o�[�u�v���Z�b�g "PLATE"
 * \ingroup ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_PLATE \
	{ -1000,  -200, 1.30f, 0.90f,      0, 0.002f,      0, 0.010f, 100.0f,  75.0f, 5000.0f}

/***************************************************************************
 *      �����}�N��
 *      Macro Functions
 ***************************************************************************/
/*==========================================================================
 *      CRI AtomEx ASR API
 *=========================================================================*/
/*JP
 * \brief ASR�̏������R���t�B�O�\���̂Ƀf�t�H���g�l���Z�b�g
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * �R���t�B�O�\���́i ::CriAtomExAsrConfig �j�ɁA�f�t�H���g�l���Z�b�g���܂��B<br>
 * \sa CriAtomExAsrConfig
 */
#define criAtomExAsr_SetDefaultConfig(p_config)	\
{\
	(p_config)->server_frequency = 60.0f;\
	(p_config)->output_channels = CRIATOM_DEFAULT_OUTPUT_CHANNELS;\
	(p_config)->output_sampling_rate = CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE;\
	(p_config)->sound_renderer_type	= CRIATOM_SOUND_RENDERER_NATIVE;\
}

/*JP
 * \brief ���x������@�\�R���t�B�O�\���̂Ƀf�t�H���g�l���Z�b�g
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * ::criAtomExAsr_AttachBusAnalyzer �֐��ɐݒ肷��R���t�B�O�\����
 * �i ::CriAtomExAsrBusAnalyzerConfig �j�ɁA�f�t�H���g�l���Z�b�g���܂��B<br>
 * \sa criAtomExAsr_AttachBusAnalyzer, CriAtomExAsrBusAnalyzerConfig
 */
#define criAtomExAsr_SetDefaultConfigForBusAnalyzer(p_config) \
{\
	(p_config)->interval = 50;\
	(p_config)->peak_hold_time = 1000;\
}

/***************************************************************************
 *      �f�[�^�^�錾
 *      Data Type Declarations
 ***************************************************************************/
/*==========================================================================
 *      CRI AtomEx ASR API
 *=========================================================================*/
/*JP
 * \brief ASR�������p�R���t�B�O�\����
 * \ingroup ATOMEXLIB_ASR
 * ASR�iAtom Sound Renderer�j�̓���d�l���w�肷�邽�߂̍\���̂ł��B<br>
 * \attention
 * �����I�Ƀ����o��������\�������邽�߁A ::criAtomExAsr_SetDefaultConfig 
 * �}�N�����g�p���Ȃ��ꍇ�ɂ́A�g�p�O�ɕK���\���̂��[���N���A���Ă��������B<br>
 * �i�\���̂̃����o�ɕs��l������Ȃ��悤�����ӂ��������B�j
 * \sa criAtomExAsr_SetDefaultConfig
 */
typedef struct CriAtomExAsrConfigTag {
	/*JP
		\brief �T�[�o�����̎��s�p�x
		\par ����:
		�T�[�o���������s����p�x���w�肵�܂��B<br>
		\attention
		Atom���C�u�������������Ɏw�肵���l�i ::CriAtomExConfig �\���̂�
		server_frequency �j�ƁA�����l���Z�b�g����K�v������܂��B<br>
		\sa CriAtomExConfig
	*/
	CriFloat32 server_frequency;

	/*JP
		\brief �o�̓`�����l����
		\par ����:
		ASR�̏o�̓`�����l�������w�肵�܂��B<br>
		�p��3D��������3D�|�W�V���j���O�@�\���g�p����ꍇ��6ch�ȏ���w�肵�܂��B<br>
	*/
	CriSint32 output_channels;
	
	/*JP
		\brief �o�̓T���v�����O���[�g
		\par ����:
		�o�͂���я����ߒ��̃T���v�����O���[�g���w�肵�܂��B<br>
		�ʏ�A�^�[�Q�b�g�@�̃T�E���h�f�o�C�X�̃T���v�����O���[�g���w�肵�܂��B<br>
		\par ���l:
		�Ⴍ����Ə������ׂ������邱�Ƃ��ł��܂��������������܂��B<br>
	*/
	CriSint32 output_sampling_rate;
	
	/*JP
		\brief �T�E���h�����_���^�C�v
		\par ����:
		ASR�̏o�͐�T�E���h�����_���̎�ʂ��w�肵�܂��B<br>
		sound_renderer_type �� CRIATOM_SOUND_RENDERER_NATIVE ���w�肵���ꍇ�A
		�����f�[�^�̓f�t�H���g�ݒ�̊e�v���b�g�t�H�[���̃T�E���h�o�͂ɓ]������܂��B<br>
		\attention
		CRIATOM_SOUND_RENDERER_ASR�����CRIATOM_SOUND_RENDERER_DEFAULT�͎w�肵�Ȃ��ł��������B
	*/
	CriAtomSoundRendererType sound_renderer_type;
} CriAtomExAsrConfig;

/*JP
 * \brief ���x������@�\�A�^�b�`�p�R���t�B�O�\����
 * \ingroup ATOMEXLIB_ASR
 * ���x������@�\��DSP�o�X�ɃA�^�b�`���邽�߂̍\���̂ł��B<br>
 * ::criAtomExAsr_AttachBusAnalyzer �֐��̈����Ɏw�肵�܂��B<br>
 * \par ���l:
 * �f�t�H���g�ݒ���g�p����ꍇ�A ::criAtomExAsr_SetDefaultConfigForBusAnalyzer �}�N����
 * �\���̂Ƀf�t�H���g�p�����[�^���Z�b�g������A ::criAtomExAsr_AttachBusAnalyzer �֐�
 * �ɍ\���̂��w�肵�Ă��������B<br>
 * \attention
 * �����I�Ƀ����o��������\�������邽�߁A ::criAtomExAsr_SetDefaultConfigForBusAnalyzer
 * �}�N�����g�p���Ȃ��ꍇ�ɂ́A�g�p�O�ɕK���\���̂��[���N���A���Ă��������B<br>
 * �i�\���̂̃����o�ɕs��l������Ȃ��悤�����ӂ��������B�j
 * \sa criAtomExAsr_AttachBusAnalyzer
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
	CriSint32 peak_hold_time;
} CriAtomExAsrBusAnalyzerConfig;

/*JP
 * \brief ���x��������
 * \par ����:
 * DSP�o�X�̃��x����������擾���邽�߂̍\���̂ł��B<br>
 * ::criAtomExAsr_GetBusAnalyzerInfo �֐��ŗ��p���܂��B
 * \par ���l:
 * �e���x���l�͉����f�[�^�̐U���ɑ΂���{���ł��i�P�ʂ̓f�V�x���ł͂���܂���j�B<br>
 * �ȉ��̃R�[�h�Ńf�V�x���\�L�ɕϊ����邱�Ƃ��ł��܂��B<br>
 * dB = 10.0f * log10f(level);
 * \sa criAtomExAsr_GetBusAnalyzerInfo
 */
typedef struct CriAtomExAsrBusAnalyzerInfoTag {
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
	CriFloat32 rms_levels[CRIATOMEXASR_MAX_CHANNELS];
	
	/*JP
		\brief �s�[�N���x��
		\par ����:
		����Ԋu�Ԃ̉����U���̍ő�l�ł��B<br>
	*/
	CriFloat32 peak_levels[CRIATOMEXASR_MAX_CHANNELS];
	
	/*JP
		\brief �s�[�N�z�[���h���x��
		\par ����:
		�z�[���h���Ă���s�[�N���x���l�ł��B<br>
	*/
	CriFloat32 peak_hold_levels[CRIATOMEXASR_MAX_CHANNELS];
} CriAtomExAsrBusAnalyzerInfo;

/*JP
 * \brief �g�`�t�B���^�R�[���o�b�N�֐�
 * \ingroup ATOMEXLIB_PLAYER
 * \par ����:
 * \param[in]		obj				���[�U�w��I�u�W�F�N�g
 * \param[in]		format			PCM�̌`��
 * \param[in]		num_channels	�`�����l����
 * \param[in]		num_samples		�T���v����
 * \param[in,out]	data			PCM�f�[�^�̃`�����l���z��
 * \return							�Ȃ�
 * \par ����:
 * DSP�o�X�ɓo�^���邱�Ƃ��ł��� PCM �f�[�^���󂯎��R�[���o�b�N�֐��ł��B<br>
 * <br>
 * �R�[���o�b�N�֐��̓o�^�ɂ� ::criAtomExAsr_SetBusFilterCallback �֐����g�p���܂��B<br>
 * �R�[���o�b�N�֐���o�^����ƁA�T�E���h�����_���������������s���x�ɁA
 * �R�[���o�b�N�֐������s�����悤�ɂȂ�܂��B<br>
 * <br>
 * �t�B���^�R�[���o�b�N�֐��ɂ́A PCM �f�[�^�̃t�H�[�}�b�g��`�����l�����A
 * �Q�Ɖ\�ȃT���v�����A PCM �f�[�^���i�[�����̈�̃A�h���X���Ԃ���܂��B<br>
 * �R�[���o�b�N���ł� PCM �f�[�^�̒l�𒼐ڎQ�Ɖ\�ɂȂ�̂ŁA
 * �Đ����̉����̐U�����`�F�b�N����Ƃ������p�r�ɗ��p�\�ł��B<br>
 * <br>
 * �܂��A�R�[���o�b�N�֐����� PCM �f�[�^�����H����ƁA�Đ����ɔ��f����邽�߁A
 * PCM �f�[�^�ɑ΂��ă��[�U�Ǝ��̃G�t�F�N�g�������邱�Ƃ��\�ł��B<br>
 * �i�������A�^�C���X�g���b�`�����̂悤�ȃf�[�^�ʂ�����������H���s�����Ƃ͂ł��܂���B�j<br>
 * \par ���l:
 * PCM �f�[�^�̓`�����l���P�ʂŕ�������Ă��܂��B<br>
 * �i�C���^�[���[�u����Ă��܂���B�j<br>
 * �� 6 �����i data �z��j�ɂ́A�e�`�����l���� PCM �f�[�^�z��̐擪�A�h���X���i�[����Ă��܂��B<br>
 * �i�񎟌��z��̐擪�A�h���X�ł͂Ȃ��A�`�����l�����Ƃ� PCM �f�[�^�z��̐擪�A�h���X���i�[����
 * �ꎟ���̃|�C���^�z��ł��B�j<br>
 * �i�[����Ă��� PCM �f�[�^��DSP�o�X�ɐݒ肳��Ă���DSP�̏�����̉����ł��B<br>
 * <br>
 * �v���b�g�t�H�[���ɂ���āA PCM �f�[�^�̃t�H�[�}�b�g�͈قȂ�܂��B<br>
 * ���s���̃f�[�^�t�H�[�}�b�g�ɂ��ẮA�� 3 �����i format �j�Ŕ��ʉ\�ł��B<br>
 * PCM �f�[�^�̃t�H�[�}�b�g�� 16 bit �����^�̏ꍇ�A format �� CRIATOM_PCM_FORMAT_SINT16 �ƂȂ�A
 * PCM �f�[�^�̃t�H�[�}�b�g�� 32 bit ���������_���^�̏ꍇ�A format �� CRIATOM_PCM_FORMAT_FLOAT32 �ƂȂ�܂��B<br>
 * ���ꂼ��̃P�[�X�� PCM �f�[�^�̒l��͈قȂ�܂��̂ł����ӂ��������B<br>
 * - CRIATOM_PCM_FORMAT_SINT16 ���� -32768 �` +32767
 * - CRIATOM_PCM_FORMAT_FLOAT32 ���� -1.0f �` +1.0f
 * .
 * �i���d�����̃~�L�V���O��O�i�̃G�t�F�N�g�ɂ���Ă͏�L�͈͂𒴂����l���o��\��������܂��B�j<br>
 * \attention
 * <br>
 * �{�R�[���o�b�N�֐����ŁAAtom���C�u������API�����s���Ȃ��ł��������B<br>
 * �R�[���o�b�N�֐���Atom���C�u�������̃T�[�o����������s����܂��B<br>
 * ���̂��߁A�T�[�o�����ւ̊��荞�݂��l�����Ȃ�API�����s�����ꍇ�A
 * �G���[������������A�f�b�h���b�N����������\��������܂��B<br>
 * <br>
 * �R�[���o�b�N�֐����Œ����ԏ������u���b�N����ƁA���؂ꓙ�̖�肪��������\��������܂��B<br>
 * \sa criAtomExAsr_SetBusFilterCallback
 */
typedef void (*CriAtomExAsrBusFilterCbFunc)(void *obj, CriAtomPcmFormat format,
	CriSint32 num_channels, CriSint32 num_samples, void *data[]);

/*JP
 * \brief DSP ID
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * ASR�iAtom Sound Renderer�j��DSP���w�肷�邽�߂̒l�ł��B<br>
 * \sa criAtomExAsr_SetDspParameter
 */
typedef enum {
	CRIATOMEXASR_DSP_ID_INVALID = 0,		/*JP< ����ID				*/
	CRIATOMEXASR_DSP_ID_BANDPASS_FILTER,	/*JP< �o���h�p�X�t�B���^	*/
	CRIATOMEXASR_DSP_ID_BIQUAD_FILTER,		/*JP< �o�C�N�A�b�h�t�B���^	*/
	CRIATOMEXASR_DSP_ID_DELAY,				/*JP< �f�B���C				*/
	CRIATOMEXASR_DSP_ID_ECHO,				/*JP< �G�R�[				*/
	CRIATOMEXASR_DSP_ID_REVERB,				/*JP< ���o�[�u				*/
	CRIATOMEXASR_DSP_ID_PITCH_SHIFTER,		/*JP< �s�b�`�V�t�^			*/
	CRIATOMEXASR_DSP_ID_3BAND_EQ,			/*JP< 3�o���h�C�R���C�U		*/
	CRIATOMEXASR_DSP_ID_COMPRESSOR,			/*JP< �R���v���b�T			*/
	CRIATOMEXASR_DSP_ID_CHORUS,				/*JP< �R�[���X				*/
	CRIATOMEXASR_DSP_ID_FLANGER,			/*JP< �t�����W���[			*/
	CRIATOMEXASR_DSP_ID_DISTORTION,			/*JP< �f�B�X�g�[�V����		*/
	CRIATOMEXASR_DSP_ID_AMPLITUDE_ANALYZER,	/*JP< �U����͊�			*/
	CRIATOMEXASR_DSP_ID_SURROUNDER,			/*JP< �T���E���_			*/
	CRIATOMEXASR_DSP_ID_I3DL2_REVERB,		/*JP< I3DL2���o�[�u			*/
	CRIATOMEXASR_DSP_ID_MULTI_TAP_DELAY,	/*JP< �}���`�^�b�v�f�B���C	*/
	CRIATOMEXASR_DSP_ID_LIMITER,			/*JP< ���~�b�^				*/
	CRIATOMEXASR_DSP_ID_MATRIX,				/*JP< �}�g���N�X			*/
	CRIATOMEXASR_DSP_ID_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExAsrDspId;

/*JP
 * \brief �o���h�p�X�t�B���^�̃p�����[�^
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * �o���h�p�X�t�B���^DSP�̃p�����[�^��ݒ肷�邽�߂̍\���̂ł��B<br>
 * �e�l�̈����ɂ��ẮA::criAtomExPlayer_SetBandpassFilterParameters �֐��Ɠ��l�ł��B<br>
 * \sa criAtomExAsr_SetDspParameter,criAtomExPlayer_SetBandpassFilterParameters
 */
typedef struct CriAtomExAsrBandpassFilterParameterTag {
	/*JP ���K������J�b�g�I�t���g�� */
	CriFloat32 cof_high;
	/*JP ���K�����J�b�g�I�t���g�� */
	CriFloat32 cof_low;
} CriAtomExAsrBandpassFilterParameter;

/*JP
 * \brief �o���h�p�X�t�B���^�̃p�����[�^
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * �o���h�p�X�t�B���^DSP�̃p�����[�^��ݒ肷�邽�߂̍\���̂ł��B<br>
 * �e�l�̈����ɂ��ẮA::criAtomExPlayer_SetBiquadFilterParameters �֐��Ɠ��l�ł��B<br>
 * \sa criAtomExAsr_SetDspParameter,criAtomExPlayer_SetBiquadFilterParameters
 */
typedef struct CriAtomExAsrBiquadFilterParameterTag {
	/*JP �t�B���^�^�C�v */
	CriAtomExBiquadFilterType type;
	/*JP ���K�����g�� */
	CriFloat32 frequency;
	/*JP Q�l */
	CriFloat32 q_value;
	/*JP �Q�C�� */
	CriFloat32 gain;
} CriAtomExAsrBiquadFilterParameter;

/*JP
 * \brief �f�B���C�̃p�����[�^
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * �f�B���CDSP�̃p�����[�^��ݒ肷�邽�߂̍\���̂ł��B<br>
 * max_delay_time_ms�����o�� ::criAtomExAcf_GetDspFxParameters �֐�
 * �Ńp�����[�^���擾����Ƃ��ɂ����g�p���܂��B<br>
 * ���̃����o�� ::criAtomExAsr_SetDspParameter �֐��ł̃p�����[�^�ύX���ɂɂ͖�������܂��B
 * \sa criAtomExAcf_GetDspFxParameters, criAtomExAsr_SetDspParameter
 */
typedef struct CriAtomExAsrDelayParameterTag {
	/* �������p�����[�^ */
	/*JP �ő�f�B���C���ԁi�~���b�P�ʁj */
	CriFloat32 max_delay_time_ms;
	/* ���쎞�p�����[�^ */
	/*JP �f�B���C���ԁi�~���b�P�ʁj */
	CriFloat32 delay_time_ms;
} CriAtomExAsrDelayParameter;

/*JP
 * \brief �G�R�[�̃p�����[�^
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * �G�R�[DSP�̃p�����[�^��ݒ肷�邽�߂̍\���̂ł��B<br>
 * \sa criAtomExAsr_SetDspParameter
 */
typedef struct CriAtomExAsrEchoParameterTag {
	/* �������p�����[�^ */
	/*JP �ő�f�B���C���ԁi�~���b�P�ʁj */
	CriFloat32 max_delay_time_ms;
	/*JP �f�B���C���ԁi�~���b�P�ʁj */
	CriFloat32 delay_time_ms;
	/*JP �t�B�[�h�o�b�N�Q�C���i0.0f�`1.0f�j */
	CriFloat32 gain;
} CriAtomExAsrEchoParameter;

/*JP
 * \brief ���o�[�u�̓��샂�[�h
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * ���o�[�u�̓��샂�[�h���擾���邽�߂̃f�[�^�^�ł��B<br>
 * ::criAtomExAcf_GetDspFxParameters �֐��ŗ��p���܂��B
 * \sa criAtomExAcf_GetDspFxParameters
 */
typedef enum {
	CRIATOMEXASR_REVERB_MODE_SURROUND = 0,
	CRIATOMEXASR_REVERB_MODE_STEREO,
	CRIATOMEXASR_REVERB_MODE_REAR_ONLY,
	CRIATOMEXASR_REVERB_MODE_CENTER_ONLY,
	/* enum size is 4bytes */
	CRIATOMEXASR_REVERB_MODE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExAsrReverbMode;

/*JP
 * \brief ���o�[�u�̃p�����[�^
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * ���o�[�uDSP�̃p�����[�^��ݒ肷�邽�߂̍\���̂ł��B<br>
 * max_predelay_time_ms�����o��max_room_size�����o�� ::criAtomExAcf_GetDspFxParameters �֐�
 * �Ńp�����[�^���擾����Ƃ��ɂ����g�p���܂��B<br>
 * �����̃����o�� ::criAtomExAsr_SetDspParameter �֐��ł̃p�����[�^�ύX���ɂɂ͖�������܂��B
 * \sa criAtomExAcf_GetDspFxParameters, criAtomExAsr_SetDspParameter
 */
typedef struct CriAtomExAsrReverbParameterTag {
	/* ���o�[�u�̏������p�����[�^ */
	/*JP �ő�v���f�B���C���ԁi�~���b�P�ʁj */
	CriFloat32 max_predelay_time_ms;
	/*JP �ő僋�[���T�C�Y�i���[�g���b�P�ʁj */
	CriFloat32 max_room_size;
	/*JP ���o�[�u�̓��샂�[�h */
	CriAtomExAsrReverbMode mode;
	/* ���o�[�u�̓��쎞�p�����[�^ */
	/*JP �c�����ԁi�~���b�P�ʁj */
	CriFloat32 reverb_time_ms;
	/*JP �����̑傫���i���[�g���P�ʁj */
	CriFloat32 room_size;
	/*JP �v���f�B���C���ԁi�~���b�P�ʁj */
	CriFloat32 predelay_time_ms;
	/*JP ���J�b�g�I�t���g���iHz�P�ʁj */
	CriFloat32 cof_low;
	/*JP ����J�b�g�I�t���g���iHz�P�ʁj */
	CriFloat32 cof_high;
} CriAtomExAsrReverbParameter;

/*JP
 * \brief �s�b�`�V�t�^�̃E�B���h�E��
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * �s�b�`�V�t�^�̃E�B���h�E�����擾���邽�߂̃f�[�^�^�ł��B<br>
 * ::criAtomExAcf_GetDspFxParameters �֐��ŗ��p���܂��B
 * \sa criAtomExAcf_GetDspFxParameters
 */
typedef enum {
	CRIATOMEXASR_PITCHSHIFTER_WINDOW_WIDTH_128 = 0,
	CRIATOMEXASR_PITCHSHIFTER_WINDOW_WIDTH_256,
	CRIATOMEXASR_PITCHSHIFTER_WINDOW_WIDTH_512,
	CRIATOMEXASR_PITCHSHIFTER_WINDOW_WIDTH_1024,
	CRIATOMEXASR_PITCHSHIFTER_WINDOW_WIDTH_2048,
	/* enum size is 4bytes */
	CRIATOMEXASR_PITCHSHIFTER_WINDOW_WIDTH_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExAsrPitchShifterWindowWidthType;

/*JP
 * \brief �s�b�`�V�t�^�̃I�[�o�[���b�v��
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * �s�b�`�V�t�^�̃I�[�o�[���b�v�ʂ��擾���邽�߂̃f�[�^�^�ł��B<br>
 * ::criAtomExAcf_GetDspFxParameters �֐��ŗ��p���܂��B
 * \sa criAtomExAcf_GetDspFxParameters
 */
typedef enum {
	CRIATOMEXASR_PITCHSHIFTER_OVERLAP_1 = 0,
	CRIATOMEXASR_PITCHSHIFTER_OVERLAP_2,
	CRIATOMEXASR_PITCHSHIFTER_OVERLAP_4,
	CRIATOMEXASR_PITCHSHIFTER_OVERLAP_8,
	/* enum size is 4bytes */
	CRIATOMEXASR_PITCHSHIFTER_OVERLAP_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExAsrPitchShifterOverlapType;

/*JP
 * \brief �s�b�`�V�t�^�̃p�����[�^
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * �s�b�`�V�t�^DSP�̃p�����[�^��ݒ肷�邽�߂̍\���̂ł��B<br>
 * window_width�����o��overlap�����o�� ::criAtomExAcf_GetDspFxParameters �֐�
 * �Ńp�����[�^���擾����Ƃ��ɂ����g�p���܂��B<br>
 * �����̃����o�� ::criAtomExAsr_SetDspParameter �֐��ł̃p�����[�^�ύX���ɂɂ͖�������܂��B
 * \sa criAtomExAcf_GetDspFxParameters, criAtomExAsr_SetDspParameter
 */
typedef struct CriAtomExAsrPitchShifterParameterTag {
	/* �s�b�`�V�t�^�̓��쎞�p�����[�^ */
	/*JP �s�b�`�V�t�g�l�i�Z���g�P�ʁj */
	CriFloat32 pitch_cent;
	/*JP �t�H���}���g�V�t�g�l�i�Z���g�P�ʁj */
	CriFloat32 formant_cent;
	/*JP �s�b�`�V�t�g���[�h */
	CriSint32 mode;
	/* �s�b�`�V�t�^�̏������p�����[�^ */
	/*JP �E�C���h�E�� */
    CriAtomExAsrPitchShifterWindowWidthType window_width;
	/*JP �I�[�o�[���b�v�� */
    CriAtomExAsrPitchShifterOverlapType overlap;
} CriAtomExAsrPitchShifterParameter;

/*JP
 * \brief �C�R���C�U�̃o���h�^�C�v
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * �C�R���C�U�̃o���h�^�C�v���w�肷�邽�߂̃f�[�^�^�ł��B<br>
 * ::CriAtomExAsr3BandsEqParameter �֐��ŗ��p���܂��B
 */
typedef enum {
	CRIATOMEX_EQ_BAND_TYPE_LOWSHELF = 0,	/*JP<���[�V�F���t�^�C�v	*/
	CRIATOMEX_EQ_BAND_TYPE_HIGHSHELF = 1,	/*JP<�n�C�V�F���t�^�C�v	*/
	CRIATOMEX_EQ_BAND_TYPE_PEAKING = 2,		/*JP<�s�[�L���O�t�^�C�v	*/

	/* enum size is 4bytes */
	CRIATOMEX_EQ_BAND_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExAsrEqBandType;

/*JP
 * \brief 3�o���h�C�R���C�U�̃p�����[�^
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * 3�o���h�C�R���C�UDSP�̃p�����[�^��ݒ肷�邽�߂̍\���̂ł��B<br>
 * \sa criAtomExAsr_SetDspParameter
 */
typedef struct CriAtomExAsr3BandsEqParameterTag {
	struct {
		/*JP �o���h�^�C�v */
		CriAtomExAsrEqBandType type;
		/*JP ���K�����g�� */
		CriFloat32 frequency;
		/*JP Q�l */
		CriFloat32 q_value;
		/*JP �Q�C�� */
		CriFloat32 gain;
	} bands[3];
} CriAtomExAsr3BandsEqParameter;

/*JP
 * \brief �R���v���b�T�̃p�����[�^
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * �R���v���b�TDSP�̃p�����[�^��ݒ肷�邽�߂̍\���̂ł��B<br>
 * side_chain_input_bus_no�����o�� ::criAtomExAcf_GetDspFxParameters �֐�
 * �Ńp�����[�^���擾����Ƃ��ɂ����g�p���܂��B<br>
 * ���̃����o�� ::criAtomExAsr_SetDspParameter �֐��ł̃p�����[�^�ύX���ɂɂ͖�������܂��B
 * \sa criAtomExAcf_GetDspFxParameters, criAtomExAsr_SetDspParameter
 */
typedef struct CriAtomExAsrCompressorParameterTag {
	/*JP �X���b�V�����h�idB�P�ʁj */
	CriFloat32 threshold;
	/*JP ���k���[�g�i0.0f�`�B���l�Ŗ������k�j */
	CriFloat32 ratio;
	/*JP �A�^�b�N���ԁi�~���b�P�ʁj */
	CriFloat32 attack_time;
	/*JP �����[�X���ԁi�~���b�P�ʁj */
	CriFloat32 release_time;
	/*JP �o�̓Q�C���idB�P�ʁj */
	CriFloat32 output_gain; 
	/*JP �T���E���h�����N�i0.0f�`1.0f�j */
	CriFloat32 surround_link;
	/*JP �T�C�h�`�F�C�����̓o�X�ԍ��i0�̏ꍇ�̓T�C�h�`�F�C���Ȃ��j */
	CriSint32 side_chain_input_bus_no;
} CriAtomExAsrCompressorParameter;

/*JP
 * \brief �R�[���X�̃p�����[�^
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * �R�[���XDSP�̃p�����[�^��ݒ肷�邽�߂̍\���̂ł��B<br>
 * max_delay_time_ms�����o�� ::criAtomExAcf_GetDspFxParameters �֐�
 * �Ńp�����[�^���擾����Ƃ��ɂ����g�p���܂��B<br>
 * ���̃����o�� ::criAtomExAsr_SetDspParameter �֐��ł̃p�����[�^�ύX���ɂɂ͖�������܂��B
 * \sa criAtomExAcf_GetDspFxParameters, criAtomExAsr_SetDspParameter
 */
typedef struct CriAtomExAsrChorusParameterTag {
	/* �R�[���X�̏������p�����[�^ */
	/*JP �ő�v���f�B���C���ԁi�~���b�P�ʁj */
	CriFloat32 max_delay_time_ms;
	/* �R�[���X�̓��쎞�p�����[�^ */
	/*JP �f�B���C���ԁi�~���b�j */
	CriFloat32 delay_time_ms;
	/*JP LFO���g���iHz�j */
	CriFloat32 rate;
	/*JP LFO�U���i0.0f�`1.0f�j */
	CriFloat32 depth;
	/*JP �t�B�[�h�o�b�N�ʁi0.0f�`1.0f�j */
	CriFloat32 feedback;
	/*JP ���������̊����i0.0f�`1.0f�j */
	CriFloat32 dry_mix; 
	/*JP �G�t�F�N�g�^�b�v1�̊����i0.0f�`1.0f�j */
	CriFloat32 wet_mix1;
	/*JP �G�t�F�N�g�^�b�v2�̊����i0.0f�`1.0f�j */
	CriFloat32 wet_mix2;
	/*JP �G�t�F�N�g�^�b�v3�̊����i0.0f�`1.0f�j */
	CriFloat32 wet_mix3;
} CriAtomExAsrChorusParameter;

/*JP
 * \brief �t�����W���[�̃p�����[�^
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * �t�����W���[DSP�̃p�����[�^��ݒ肷�邽�߂̍\���̂ł��B<br>
 * \sa criAtomExAsr_SetDspParameter
 */
typedef struct CriAtomExAsrFlangerParameterTag {
	/*JP �f�B���C���ԁi�~���b�j */
	CriFloat32 delay_time_ms;
	/*JP LFO���g���iHz�j */
	CriFloat32 rate;
	/*JP LFO�U���i0.0f�`1.0f�j */
	CriFloat32 depth;
	/*JP �t�B�[�h�o�b�N�ʁi0.0f�`1.0f�j */
	CriFloat32 feedback;
	/*JP ���������̊����i0.0f�`1.0f�j */
	CriFloat32 dry_mix; 
	/*JP �G�t�F�N�g�����̊����i0.0f�`1.0f�j */
	CriFloat32 wet_mix;
} CriAtomExAsrFlangerParameter;

/*JP
 * \brief �f�B�X�g�[�V�����̃p�����[�^
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * �f�B�X�g�[�V����DSP�̃p�����[�^��ݒ肷�邽�߂̍\���̂ł��B<br>
 * \sa criAtomExAsr_SetDspParameter
 */
typedef struct CriAtomExAsrDistortionParameterTag {
	/*JP �c�݁idB�P�ʁj */
	CriFloat32 drive;
	/*JP ���������̊����i0.0f�`1.0f�j */
	CriFloat32 dry_mix; 
	/*JP �G�t�F�N�g�����̊����i0.0f�`1.0f�j */
	CriFloat32 wet_mix;
	/*JP �o�̓Q�C���idB�P�ʁj */
	CriFloat32 output_gain; 
} CriAtomExAsrDistortionParameter;

/*JP
 * \brief �T���E���_�̃��[�h
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * �T���E���_DSP�̏������[�h���w�肷�邽�߂̃f�[�^�^�ł��B<br>
 * \sa criAtomExAsr_SetDspParameter
 */
typedef enum {
	CRIATOMEX_SURROUNDER_MODE_STRAIGHT = 0,
	CRIATOMEX_SURROUNDER_MODE_CROSS = 1,
	CRIATOMEX_SURROUNDER_MODE_MATRIX = 2,
	/* enum size is 4bytes */
	CRIATOMEX_SURROUNDER_MODE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExAsrSurrounderMode;

/*JP
 * \brief �T���E���_�̃p�����[�^
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * �T���E���_DSP�̃p�����[�^��ݒ肷�邽�߂̍\���̂ł��B<br>
 * \sa criAtomExAsr_SetDspParameter
 */
typedef struct CriAtomExAsrSurrounderParameterTag {
	/* �T���E���_�̏������p�����[�^ */
	/*JP �ő�v���f�B���C���ԁi�~���b�P�ʁj */
	CriFloat32 max_delay_time_ms;
	/* �T���E���_�̓��쎞�p�����[�^ */
	/*JP �f�B���C���ԁi�~���b�j */
	CriFloat32 delay_time_ms;
	/*JP �o�̓Q�C���idB�P�ʁj */
	CriFloat32 gain;
	/*JP �T���E���h�������[�h */
	CriAtomExAsrSurrounderMode mode;
} CriAtomExAsrSurrounderParameter;

/*JP
 * \brief I3DL2���o�[�u�̃p�����[�^
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * I3DL2���o�[�uDSP�̃p�����[�^��ݒ肷�邽�߂̍\���̂ł��B<br>
 * \sa criAtomExAsr_SetDspParameter
 */
typedef struct CriAtomExAsrI3DL2ReverbParameterTag {
	/*JP �f�B���C���ԁi�~���b�j */
	CriFloat32 room;
	/*JP �Q�Ǝ��g����荂��̃��x���i�~���x���j */
	CriFloat32 room_hf;
	/*JP ����c�����ԁi�b�j */
	CriFloat32 decay_time;
	/*JP ����c�����̎Q�Ǝ��g����荂��̌����� */
	CriFloat32 decay_hf_ratio;
	/*JP �������ˉ��̃��x���i�~���x���j */
	CriFloat32 reflections;
	/*JP �������ˉ��̃f�B���C�i�b�j */
	CriFloat32 reflections_delay;
	/*JP ����c�����̃��x���i�~���x���j */
	CriFloat32 reverb;
	/*JP ����c�����̃f�B���C�i�b�j */
	CriFloat32 reverb_delay;
	/*JP ����c�����̃G�R�[���x */
	CriFloat32 diffusion;
	/*JP ����c�����̃��f�����x */
	CriFloat32 density;
	/*JP �Q�Ǝ��g���iHz�j */
	CriFloat32 hf_reference;
	/*JP �t�����gCH���̓��x�� */
	CriFloat32 front_input;
	/*JP ���ACH���̓��x�� */
	CriFloat32 rear_input;
	/*JP �Z���^�[CH���̓��x�� */
	CriFloat32 center_input;
	/*JP �t�����gCH�o�̓��x�� */
	CriFloat32 front_output;
	/*JP ���ACH�o�̓��x�� */
	CriFloat32 rear_output;
	/*JP �Z���^�[CH�o�̓��x�� */
	CriFloat32 center_output;
} CriAtomExAsrI3DL2ReverbParameter;

/*JP
 * \brief Multi tap delay�̃p�����[�^
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * Multi tap delayDSP�̃p�����[�^��ݒ肷�邽�߂̍\���̂ł��B<br>
 * \sa criAtomExAsr_SetDspParameter
 */
typedef struct CriAtomExAsrMultiTapDelayParameterTag {
	/*JP �ő�f�B���C���ԁi50�`1000ms�j */
	CriFloat32 max_delay_time_ms;
	struct {
		/*JP �f�B���C���ԁi0�`�ő�j */
		CriFloat32 delay_time_ms;
		/*JP ���x���i0.0�`1.0�j */
		CriFloat32 level;
		/*JP �p���p�x�i-180 �` 180�j */
		CriFloat32 pan;
		/*JP �t�B�[�h�o�b�N�ʁi0.0 �` 1.0�j */
		CriFloat32 feedback;
	} taps[4];
} CriAtomExAsrMultiTapDelayParameter;

/*JP
 * \brief ���~�b�^�̃^�C�v
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * ���~�b�^DSP�̏����^�C�v���w�肷�邽�߂̃f�[�^�^�ł��B<br>
 * \sa criAtomExAsr_SetDspParameter
 */
typedef enum {
	CRIATOMEX_LIMITER_TYPE_PEAK = 0,
	CRIATOMEX_LIMITER_TYPE_RMS = 1,
	/* enum size is 4bytes */
	CRIATOMEX_LIMITER_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExAsrLimiterType;

/*JP
 * \brief ���~�b�^�̃p�����[�^
 * \ingroup ATOMEXLIB_ASR
 * \par ����:
 * ���~�b�^DSP�̃p�����[�^��ݒ肷�邽�߂̍\���̂ł��B<br>
 * side_chain_input_bus_no�����o�� ::criAtomExAcf_GetDspFxParameters �֐�
 * �Ńp�����[�^���擾����Ƃ��ɂ����g�p���܂��B<br>
 * ���̃����o�� ::criAtomExAsr_SetDspParameter �֐��ł̃p�����[�^�ύX���ɂɂ͖�������܂��B
 * \sa criAtomExAcf_GetDspFxParameters, criAtomExAsr_SetDspParameter
 */
typedef struct CriAtomExAsrLimiterParameterTag {
	/*JP �^�C�v */
	CriAtomExAsrLimiterType type;
	/*JP �X���b�V�����h�idB�P�ʁj */
	CriFloat32 threshold;
	/*JP �A�^�b�N���ԁi�~���b�P�ʁj */
	CriFloat32 attack_time;
	/*JP �����[�X���ԁi�~���b�P�ʁj */
	CriFloat32 release_time;
	/*JP �o�̓Q�C���idB�P�ʁj */
	CriFloat32 output_gain; 
	/*JP �T���E���h�����N�i0.0f�`1.0f�j */
	CriFloat32 surround_link;
	/*JP �T�C�h�`�F�C�����̓o�X�ԍ��i0�̏ꍇ�̓T�C�h�`�F�C���Ȃ��j */
	CriSint32 side_chain_input_bus_no;
} CriAtomExAsrLimiterParameter;

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
 *      CRI AtomEx ASR API
 *=========================================================================*/

/*JP
 * \brief DSP�o�X�̃{�����[���̐ݒ�
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	bus_no		DSP�o�X�ԍ�
 * \param[in]	volume		�{�����[���l
 * \par ����:
 * DSP�o�X�̃{�����[����ݒ肵�܂��B<br>
 * �Z���h�^�C�v���|�X�g�{�����[���A�|�X�g�p���̃Z���h��ɗL���ł��B<br>
 * <br>
 * �{�����[���l�ɂ́A0.0f�`1.0f�͈̔͂Ŏ����l���w�肵�܂��B<br>
 * �{�����[���l�͉����f�[�^�̐U���ɑ΂���{���ł��i�P�ʂ̓f�V�x���ł͂���܂���j�B<br>
 * �Ⴆ�΁A1.0f���w�肵���ꍇ�A�����͂��̂܂܂̃{�����[���ŏo�͂���܂��B<br>
 * 0.5f���w�肵���ꍇ�A�����g�`�̐U���𔼕��ɂ����f�[�^�Ɠ������ʁi-6dB�j��
 * �������o�͂���܂��B<br>
 * 0.0f���w�肵���ꍇ�A�����̓~���[�g����܂��i�����ɂȂ�܂��j�B<br>
 * �{�����[���̃f�t�H���g�l��CRI Atom Craft�Őݒ肵���l�ł��B<br>
 */
void CRIAPI criAtomExAsr_SetBusVolume(CriSint32 bus_no, CriFloat32 volume);

/*JP
 * \brief DSP�o�X�̃p���j���O3D�̐ݒ�
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	bus_no				DSP�o�X�ԍ�
 * \param[in]	pan3d_angle			Pan3D �p�x
 * \param[in]	pan3d_distance		Pan3D �C���e���A����
 * \param[in]	pan3d_volume		Pan3D ����
 * \par ����:
 * DSP�o�X�̃p���j���O3D�̃p�����[�^��ݒ肵�܂��B<br>
 * �Z���h�^�C�v���|�X�g�p���̃Z���h��ɗL���ł��B<br>
 * <br>
 * Pan3D�p�x�́A-180.0f �` 180.0f�͈̔͂Őݒ肵�܂��B<br>
 * <br>
 * Pan3D�C���e���A�����́A0.0f �` 1.0f�͈̔͂Őݒ肵�܂��B<br>
 * <br>
 * Pan3D�{�����[���́A0.0f �` 1.0f�͈̔͂Őݒ肵�܂��B<br>
 * �ʏ�̃{�����[���Ɗ|�����킳��܂��B
 * <br>
 * �p��3D�̃f�t�H���g�l��CRI Atom Craft�Őݒ肵���l�ł��B<br>
 */
void CRIAPI criAtomExAsr_SetBusPan3d(CriSint32 bus_no, 
	CriFloat32 pan3d_angle, CriFloat32 pan3d_distance, CriFloat32 pan3d_volume);

/*JP
 * \brief DSP�o�X�̃��x���s��̐ݒ�
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	bus_no			DSP�o�X�ԍ�
 * \param[in]	input_channels	���̓`�����l����
 * \param[in]	output_channels	�o�̓`�����l����
 * \param[in]	matrix			���x���s���1�����ɕ\�������x���l�̔z��
 * \par ����:
 * DSP�o�X�̃��x���s���ݒ肵�܂��B<br>
 * �Z���h�^�C�v���|�X�g�p���̃Z���h��ɗL���ł��B<br>
 * <br>
 * ���x���}�g���b�N�X�́A�����f�[�^�̊e�`�����l���̉������A�ǂ̃X�s�[�J�[����
 * �ǂ̒��x�̉��ʂŏo�͂��邩���w�肷�邽�߂̎d�g�݂ł��B<br>
 * matrix��[input_channels * output_channels]�̔z��ł��B<br>
 * ���̓`�����l��ch_in����o�̓`�����l��ch_out�ɃZ���h����郌�x����
 * matrix[ch_in * output_channels + ch_out]�ɃZ�b�g���܂��B<br>
 * ���x���s��̃f�t�H���g�l�͒P�ʍs��ł��B<br>
 * <br>
 * ���x���l�ɂ́A0.0f�`1.0f�͈̔͂Ŏ����l���w�肵�܂��B<br>
 * ���x���l�͉����f�[�^�̐U���ɑ΂���{���ł��i�P�ʂ̓f�V�x���ł͂���܂���j�B<br>
 * �Ⴆ�΁A1.0f���w�肵���ꍇ�A�����͂��̂܂܂̃��x���ŏo�͂���܂��B<br>
 * 0.5f���w�肵���ꍇ�A�����g�`�̐U���𔼕��ɂ����f�[�^�Ɠ������ʁi-6dB�j��
 * �������o�͂���܂��B<br>
 * 0.0f���w�肵���ꍇ�A�����̓~���[�g����܂��i�����ɂȂ�܂��j�B<br>
 */
void CRIAPI criAtomExAsr_SetBusMatrix(CriSint32 bus_no, 
	CriSint32 input_channels, CriSint32 output_channels, const CriFloat32 matrix[]);

/*JP
 * \brief DSP�o�X�̃Z���h���x���̐ݒ�
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	bus_no		DSP�o�X�ԍ�
 * \param[in]	sendto_no	�Z���h���DSP�o�X�ԍ�
 * \param[in]	level		���x���l
 * \par ����:
 * �Z���h��DSP�o�X�ɉ����f�[�^�𑗂�ۂ̃��x����ݒ肵�܂��B<br>
 * <br>
 * ���x���l�ɂ́A0.0f�`1.0f�͈̔͂Ŏ����l���w�肵�܂��B<br>
 * ���x���l�͉����f�[�^�̐U���ɑ΂���{���ł��i�P�ʂ̓f�V�x���ł͂���܂���j�B<br>
 * �Ⴆ�΁A1.0f���w�肵���ꍇ�A�����͂��̂܂܂̃��x���ŏo�͂���܂��B<br>
 * 0.5f���w�肵���ꍇ�A�����g�`�̐U���𔼕��ɂ����f�[�^�Ɠ������ʁi-6dB�j��
 * �������o�͂���܂��B<br>
 * 0.0f���w�肵���ꍇ�A�����̓~���[�g����܂��i�����ɂȂ�܂��j�B<br>
 * ���x���̃f�t�H���g�l��CRI Atom Craft�Őݒ肵���l�ł��B<br>
 */
void CRIAPI criAtomExAsr_SetBusSendLevel(
	CriSint32 bus_no, CriSint32 sendto_no, CriFloat32 level);

/*JP
 * \brief DSP�p�����[�^�̐ݒ�
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	bus_no		DSP�o�X�ԍ�
 * \param[in]	dsp_id		DSP ID
 * \param[in]	parameter	DSP�p�����[�^
 * \par ����:
 * DSP�p�����[�^��ݒ肵�܂��B<br>
 * DSP�p�����[�^��ݒ肷��ۂ́A�{�֐��Ăяo���O�ɂ��炩����
 * ::criAtomExAsr_AttachDspBusSetting �֐���DSP�o�X���\�z����Ă���K�v������܂��B<br>
 * �ǂ�DSP�o�X�ɂǂ�DSP�����݂��邩�́A�A�^�b�`����DSP�o�X�ݒ�Ɉˑ����܂��B�w�肵��DSP�o�X�Ɏw�肵��ID��DSP�����݂��Ȃ��ꍇ�A�֐��͎��s���܂��B<br>
 * DSP�p�����[�^�ɂ́A�eDSP�̃p�����[�^�\���̂��w�肵�Ă��������B
 * \sa criAtomExAsr_AttachDspBusSetting
 */
void CRIAPI criAtomExAsr_SetDspParameter(
	CriSint32 bus_no, CriAtomExAsrDspId dsp_id, const void* parameter);

/*JP
 * \brief DSP�̃o�C�p�X�ݒ�
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	bus_no		DSP�o�X�ԍ�
 * \param[in]	dsp_id		DSP ID
 * \param[in]	bypass		�o�C�p�X�ݒ�
 * \par ����:
 * DSP�̃o�C�p�X�ݒ���s���܂��B<br>
 * �o�C�p�X�ݒ肳�ꂽDSP�͉��������̍ہA�X���[�����悤�ɂȂ�܂��B<br>
 * DSP�̃o�C�p�X�ݒ������ۂ́A�{�֐��Ăяo���O�ɂ��炩����
 * ::criAtomExAsr_AttachDspBusSetting �֐���DSP�o�X���\�z����Ă���K�v������܂��B<br>
 * �ǂ�DSP�o�X�ɂǂ�DSP�����݂��邩�́A�A�^�b�`����DSP�o�X�ݒ�Ɉˑ����܂��B�w�肵��DSP�o�X�Ɏw�肵��ID��DSP�����݂��Ȃ��ꍇ�A�֐��͎��s���܂��B<br>
 * DSP�p�����[�^�ɂ́A�eDSP�̃p�����[�^�\���̂��w�肵�Ă��������B
 * \attention
 * �����Đ����Ƀo�C�p�X�ݒ���s���ƃm�C�Y���������邱�Ƃ�����܂��B<br>
 * \sa criAtomExAsr_AttachDspBusSetting
 */
void CRIAPI criAtomExAsr_SetDspBypass(
	CriSint32 bus_no, CriAtomExAsrDspId dsp_id, CriBool bypass);

/*JP
 * \brief ���x������@�\�̒ǉ�
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	bus_no		DSP�o�X�ԍ�
 * \param[in]	config		���x������@�\�̃R���t�B�O�\����
 * \par ����:
 * DSP�o�X�Ƀ��x������@�\��ǉ����A���x�����菈�����J�n���܂��B<br>
 * �{�֐������s��A ::criAtomExAsr_GetBusAnalyzerInfo �֐������s���邱�ƂŁA
 * RMS���x���i�����j�A�s�[�N���x���i�ő�U���j�A�s�[�N�z�[���h���x����
 * �擾���邱�Ƃ��\�ł��B
 * ����DSP�o�X�̃��x�����v������ɂ́ADSP�o�X���Ƃɖ{�֐����Ăяo���K�v������܂��B
 * \par ��:
 * \code
 * 	// ���x��������擾�p�\����
 * 	CriAtomExAsrBusAnalyzerInfo info;
 * 	
 * 	// 0�ԃo�X�i�}�X�^�[�o�X�j�Ƀ��x������@�\�̒ǉ�
 * 	criAtomExAsr_AttachBusAnalyzer(0, NULL);
 * 	
 * 	�@�@�F
 * 	
 * 	// ���x��������̎擾
 * 	criAtomExAsr_GetBusAnalyzerInfo(0, &info);
 * 	
 * 	// �v�����ʂ̕\��
 *  for (i = 0; i < CRIATOMEXASR_MAX_CHANNELS; i++) {
 * 	    printf("[%d] RMS: %1.6f, Peak: %1.6f, Hold: %1.6f", 
 * 	        i, info.rms_levels[i], info.peak_levels[i], info.peak_hold_levels[i]);
 *  }
 * \endcode
 * \attention
 * �{�֐��� ::criAtomExAsr_AttachDspBusSetting �֐��Ɠ���̃��\�[�X�𑀍삵�܂��B<br>
 * ���̂��߁A����� ::criAtomExAsr_AttachDspBusSetting �֐������s����ƁA
 * ::criAtomExAsr_GetBusAnalyzerInfo �֐��ɂ����擾���ł��Ȃ��Ȃ�܂��B<br>
 * �{�֐��� ::criAtomExAsr_AttachDspBusSetting �֐��𕹗p����ۂɂ́A
 * ::criAtomExAsr_AttachDspBusSetting �֐������s����O�Ɉ�U
 * ::criAtomExAsr_DetachBusAnalyzer �֐��Ń��x������@�\�𖳌������A
 * ::criAtomExAsr_AttachDspBusSetting �֐����s��ɍēx�{�֐������s���Ă��������B<br>
 * \code
 * 		�F
 * 	// DSP�o�X�ݒ�̕ύX�O�Ɉ�U���x������@�𖳌���
 * 	criAtomExAsr_DetachBusAnalyzer(0);
 * 	
 * 	// DSP�o�X�ݒ�̍X�V
 * 	criAtomExAsr_AttachDspBusSetting("DspBusSetting_0", NULL, 0);
 * 	
 * 	// ���x������@�̍ăA�^�b�`
 * 	criAtomExAsr_AttachBusAnalyzer(0, NULL);
 * 		�F
 * \endcode
 * \sa criAtomExAsr_GetBusAnalyzerInfo, criAtomExAsr_DetachBusAnalyzer
 */
void CRIAPI criAtomExAsr_AttachBusAnalyzer(
	CriSint32 bus_no, const CriAtomExAsrBusAnalyzerConfig* config);

/*JP
 * \brief ���x������@�\�̍폜
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	bus_no		DSP�o�X�ԍ�
 * \par ����:
 * DSP�o�X���烌�x������@�\���폜���܂��B
 * \sa criAtomExAsr_AttachBusAnalyzer
 */
void CRIAPI criAtomExAsr_DetachBusAnalyzer(CriSint32 bus_no);

/*JP
 * \brief ���x�����茋�ʂ̎擾
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	bus_no		DSP�o�X�ԍ�
 * \param[out]	info		���x�����茋�ʂ̍\����
 * \par ����:
 * DSP�o�X���烌�x������@�\�̌��ʂ��擾���܂��B
 * \sa criAtomExAsr_AttachBusAnalyzer
 */
void CRIAPI criAtomExAsr_GetBusAnalyzerInfo(
	CriSint32 bus_no, CriAtomExAsrBusAnalyzerInfo *info);

/*JP
 * \brief �g�`�t�B���^�R�[���o�b�N�֐��̓o�^
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	bus_no		DSP�o�X�ԍ�
 * \param[in]	pre_func	DSP�����O�̃t�B���^�R�[���o�b�N�֐�
 * \param[in]	post_func	DSP������̃t�B���^�R�[���o�b�N�֐�
 * \param[in]	obj			���[�U�w��I�u�W�F�N�g
 * \par ����:
 * DSP�o�X�ɗ���Ă��� PCM �f�[�^���󂯎��R�[���o�b�N�֐���o�^���܂��B<br>
 * �o�^���ꂽ�R�[���o�b�N�֐��́A�T�E���h�����_���������������s�����^�C�~���O�ŌĂяo����܂��B<br>
 * DSP�����O��DSP�������2��ނ̎g�p���Ȃ��ق���NULL�w�肪�\�ł��B<br>
 * \attention
 * �R�[���o�b�N�֐����ŁAAtom���C�u������API�����s���Ȃ��ł��������B<br>
 * �R�[���o�b�N�֐���Atom���C�u�������̃T�[�o����������s����܂��B<br>
 * ���̂��߁A�T�[�o�����ւ̊��荞�݂��l�����Ȃ�API�����s�����ꍇ�A
 * �G���[������������A�f�b�h���b�N����������\��������܂��B<br>
 * <br>
 * �g�`�t�B���^�R�[���o�b�N�֐����Œ����ԏ������u���b�N����ƁA���؂ꓙ�̖��
 * ���������܂��̂ŁA�����ӂ��������B<br>
 * \sa CriAtomExPlayerFilterCbFunc
 */
void CRIAPI criAtomExAsr_SetBusFilterCallback(CriSint32 bus_no, 
	CriAtomExAsrBusFilterCbFunc pre_func, CriAtomExAsrBusFilterCbFunc post_func, void *obj);

#ifdef __cplusplus
}
#endif

#endif	/* CRI_INCL_CRI_LE_ATOM_ASR_H */

/* --- end of file --- */
