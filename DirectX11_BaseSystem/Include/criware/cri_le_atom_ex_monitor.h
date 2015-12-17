/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2010-2013 CRI Middleware Co., Ltd.
 *
 * Library  : CRI AtomEx Monitor Library
 * Module   : Monitor Library C Interface Header
 * File     : cri_le_atom_ex_monitor.h
 *
 ****************************************************************************/
/*!
 *	\file	cri_le_atom_ex_monitor.h
 */

#ifndef CRI_INCL_CRI_LE_ATOM_EX_MONITOR_H
#define CRI_INCL_CRI_LE_ATOM_EX_MONITOR_H

/***************************************************************************
 *      �C���N���[�h�t�@�C��
 *      Include files
 ***************************************************************************/

#include <cri_le_xpt.h>

/***************************************************************************
 *      �萔�}�N��
 *      Macro Constants
 ***************************************************************************/
/* �o�[�W������� */
/* Version Number */
#define CRIATOMEX_MONITOR_VERSION				(0x01070000)
#define CRIATOMEX_MONITOR_VER_NUM				"1.07.00"
#define CRIATOMEX_MONITOR_VER_NAME				"CRI AtomEx Monitor(LE)"
#define CRIATOMEX_MONITOR_VER_OPTION


/*JP
 * \brief �f�t�H���g�v���r���[�I�u�W�F�N�g
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \par ����:
 * �f�t�H���g�̃v���r���[�I�u�W�F�N�g���ł��B<br>
 * \sa criAtomExMonitor_SetDefaultConfig
 */
#define CRIATOMX_MONITOR_DEFAULT_NUM_PUREVIEW_OBJECTS		(200)
/*JP
 * \brief �f�t�H���g�ʐM�o�b�t�@�T�C�Y
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \par ����:
 * �f�t�H���g�̒ʐM�o�b�t�@�T�C�Y�ł��B<br>
 * \sa criAtomExMonitor_SetDefaultConfig
 */
#define CRIATOMX_MONITOR_DEFAULT_COMMUNICATION_BUFFER_SIZE	(2*1024*1024)
/*JP
 * \brief �f�t�H���g�Đ��ʒu���X�V�Ԋu
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \par ����:
 * �f�t�H���g�̍Đ��ʒu���X�V�Ԋu�ł��B<br>
 * \sa criAtomExMonitor_SetDefaultConfig
 */
#define CRIATOMX_MONITOR_DEFAULT_PLAYBACK_POSITION_UPDATE_INTERVAL	(8)

/*JP
 * \brief ���O�擾���[�h
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \par ����:
 * ���O�擾�̃��[�h�ł��B<br>
 * \sa criAtomExMonitor_SetLogMode
 */
#define CRIATOMEX_MONITOR_LOG_MODE_OFF					(0)
#define CRIATOMEX_MONITOR_LOG_MODE_PLAYBACK				(1)			/* �Đ�����֘A */
#define CRIATOMEX_MONITOR_LOG_MODE_ERROR				(1 << 1)	/* �G���[�֘A */
#define CRIATOMEX_MONITOR_LOG_MODE_LOW_LEVEL_PLAYBACK	(1 << 2)	/* �჌�x���Đ�����֘A */
#define CRIATOMEX_MONITOR_LOG_MODE_SYSTEM_INFORMATION	(1 << 3)	/* �V�X�e�����֘A */
#define CRIATOMEX_MONITOR_LOG_MODE_HANDLE_INFORMATION	(1 << 4)	/* �V�X�e�����֘A */
#define CRIATOMEX_MONITOR_LOG_MODE_CUE_LIMIT			(1 << 5)	/* �L���[���~�b�g�����֘A */
#define CRIATOMEX_MONITOR_LOG_MODE_PROBABILITY			(1 << 6)	/* �v���o�r���e�B�����֘A */
#define CRIATOMEX_MONITOR_LOG_MODE_CATEGORY				(1 << 7)	/* �J�e�S�������֘A */

#define CRIATOMEX_MONITOR_LOG_MODE_ALL					(0xFFFFFFFF)


/***************************************************************************
 *      �����}�N��
 *      Macro Functions
 ***************************************************************************/

#define criAtomExMonitor_SetDefaultConfig(p_config)	\
{\
	(p_config)->max_preivew_object = CRIATOMX_MONITOR_DEFAULT_NUM_PUREVIEW_OBJECTS;\
	(p_config)->communication_buffer_size = CRIATOMX_MONITOR_DEFAULT_COMMUNICATION_BUFFER_SIZE;\
	(p_config)->additional_buffer = 0;\
	(p_config)->additional_buffer_size = 0;\
	(p_config)->playback_position_update_interval = CRIATOMX_MONITOR_DEFAULT_PLAYBACK_POSITION_UPDATE_INTERVAL;\
}
 
/***************************************************************************
 *      �f�[�^�^�錾
 *      Data Type Declarations
 ***************************************************************************/
typedef struct CriAtomExMonitorConfigTag {
	CriUint32	max_preivew_object;
	CriUint32	communication_buffer_size;
	CriUintPtr	additional_buffer;
	CriUint32	additional_buffer_size;
	/*JP
		\brief �Đ��ʒu���X�V�Ԋu
		\par ����:
		�T�[�o�������s���ɍĐ��ʒu���̑��M�������s���Ԋu���w�肵�܂��B<br>
		playback_position_update_interval �̒l��ύX���邱�ƂŁA
		�T�[�o�����̎��s�񐔂�ς��邱�ƂȂ��Đ��ʒu���̑��M�p�x�������邱�Ƃ��\�ł��B<br>
		<br>
		playback_position_update_interval �ɂ́A�Đ��ʒu���̑��M���������T�[�o���Ƃɍs�������w�肵�܂��B<br>
		�Ⴆ�΁A playback_position_update_interval �� 2 �ɐݒ肷��ƁA
		�T�[�o���� 2 ��ɑ΂��A 1 �񂾂��Đ��ʒu���̑��M���s���܂��B<br>
		�i�Đ��ʒu���̑��M�p�x�� 1/2 �ɂȂ�܂��B�j<br>
	*/
	CriSint32	playback_position_update_interval;
} CriAtomExMonitorConfig;

/*	Log Callback Function type	*/
typedef void (*CriAtomExMonitorLogCbFunc)(void* obj, const CriChar8 *log_string);

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

/*JP
 * \brief ���j�^�[�@�\�������p���[�N�̈�T�C�Y�̌v�Z
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \param[in]	config		�������p�R���t�B�O�\����
 * \return		CriSint32	���[�N�̈�T�C�Y
 * \par ����:
 * ���j�^�[�@�\���g�p���邽�߂ɕK�v�ȁA���[�N�̈�̃T�C�Y���擾���܂��B<br>
 * <br>
 * ���[�N�̈�T�C�Y�̌v�Z�Ɏ��s����ƁA�{�֐��� -1 ��Ԃ��܂��B<br>
 * ���[�N�̈�T�C�Y�̌v�Z�Ɏ��s�������R�ɂ��ẮA�G���[�R�[���o�b�N�̃��b�Z�[�W�Ŋm�F�\�ł��B<br>
 * \par ���l:
 * ���j�^�[�@�\���K�v�Ƃ��郏�[�N�̈�̃T�C�Y�́A���j�^�[�@�\�������p�R���t�B�O
 * �\���́i ::CriAtomExMonitorConfig �j�̓��e�ɂ���ĕω����܂��B<br>
 * <br>
 * ������NULL���w�肵���ꍇ�A�f�t�H���g�ݒ�
 * �i ::criAtomExMonitor_SetDefaultConfig �K�p���Ɠ����p�����[�^�j��
 * ���[�N�̈�T�C�Y���v�Z���܂��B
 * <br>
 * ���� config �̏��́A�֐����ł̂ݎQ�Ƃ���܂��B<br>
 * �֐��𔲂�����͎Q�Ƃ���܂���̂ŁA�֐����s��� config �̗̈��������Ă�
 * ��肠��܂���B
 * \sa criAtomExMonitor_SetDefaultConfig, criAtomExMonitor_Initialize, CriAtomExMonitorConfig
 */
CriSint32 CRIAPI criAtomExMonitor_CalculateWorkSize(const CriAtomExMonitorConfig* config);

/*JP
 * \brief ���j�^�[�@�\�̏�����
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \param[in]	config		�������p�R���t�B�O�\����
 * \param[in]	work		���[�N�̈�
 * \param[in]	work_size	���[�N�̈�T�C�Y
 * \par ����:
 * ���j�^�[�@�\�����������܂��B<br>
 * ���j�^�[�@�\�𗘗p����ɂ́A�K�����̊֐������s����K�v������܂��B<br>
 * �i���j�^�[�@�\�́A�{�֐������s��A ::criAtomExMonitor_Finalize �֐������s����܂ł̊ԁA
 * ���p�\�ł��B�j<br>
 * �{�֐��̌Ăяo���́AcriAtomEx_Initialize �֐����s�� ::criAtomEx_Finalize �֐������s����܂ł̊Ԃ�
 * �s���悤�ɂ��Ă��������B<br>
 * \sa criAtomExMonitor_Finalize, CriAtomExMonitorConfig
 */
void CRIAPI criAtomExMonitor_Initialize(
	const CriAtomExMonitorConfig *config, void *work, CriSint32 work_size);

/*JP
 * \brief ���j�^�[�@�\�̏I��
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \par ����:
 * ���j�^�[�@�\���I�����܂��B<br>
 * \attention
 * ::criAtomExMonitor_Initialize �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * \sa criAtomExMonitor_Initialize
 */
void CRIAPI criAtomExMonitor_Finalize(void);

/*JP
 * \brief �T�[�o�[IP�A�h���X������̎擾
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \par ����:
 * �T�[�o�[IP�A�h���X��������擾���܂��B<br>
 * \attention
 * ::criAtomExMonitor_Initialize �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * \sa criAtomExMonitor_Initialize, criAtomExMonitor_GetClientIpString
 */
const CriChar8* CRIAPI criAtomExMonitor_GetServerIpString(void);

/*JP
 * \brief �N���C�A���gIP�A�h���X������̎擾
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \par ����:
 * �N���C�A���gIP�A�h���X��������擾���܂��B<br>
 * \attention
 * ::criAtomExMonitor_Initialize �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * \sa criAtomExMonitor_Initialize, criAtomExMonitor_GetServerIpString
 */
const CriChar8* CRIAPI criAtomExMonitor_GetClientIpString(void);

/*JP
 * \brief �c�[���ڑ���Ԃ̎擾
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \return		CriBool	�ڑ���ԁiCRI_TRUE:�ڑ��ACRI_FALSE:���ڑ��j
 * \par ����:
 * �c�[���ڑ���Ԃ��擾���܂��B<br>
 * \attention
 * ::criAtomExMonitor_Initialize �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * \sa criAtomExMonitor_Initialize
 */
CriBool CRIAPI criAtomExMonitor_IsConnected(void);

/*JP
 * \brief ���O�擾�R�[���o�b�N�̓o�^
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \par ����:
 * \param		cbf			�R�[���o�b�N�֐�
 * \param		obj			���[�U�w��I�u�W�F�N�g
 * ���O�擾�p�R�[���o�b�N�֐���o�^���܂��B<br>
 * �֐���o�^����ƃ��O�擾���J�n���ANULL��ݒ肷�邱�ƂŃ��O�擾���~���܂��B<br>
 * �擾���郍�O�̃��[�h�ؑւ� ::criAtomExMonito_SetLogMode �֐��Őݒ�w�肭�������B<br>
 * \attention
 * ::criAtomExMonitor_Initialize �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * \sa criAtomExMonitor_Initialize, criAtomExMonito_SetLogMode
 */
void CRIAPI criAtomExMonitor_SetLogCallback(CriAtomExMonitorLogCbFunc cbf, void* obj);

/*JP
 * \brief ���O���[�h�̐ݒ�
 * \ingroup ATOMEXMONITORLIB_GLOBAL
 * \par ����:
 * ���O�擾�̃��[�h��ݒ肵�܂��B<br>
 * �{�֐��Őݒ肵�����[�h�ɂ��������� ::criAtomExMonitor_SetLogCallback �֐���
 * �o�^�������O�擾�p�R�[���o�b�N�֐����Ăяo����܂��B<br>
 * \sa criAtomExMonitor_SetLogCallback
 */
void CRIAPI criAtomExMonitor_SetLogMode(CriUint32 mode);

#ifdef __cplusplus
}
#endif

#endif // CRI_INCL_CRI_LE_ATOM_EX_MONITOR_H
