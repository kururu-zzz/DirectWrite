/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2010-2013 CRI Middleware Co., Ltd.
 *
 * Library  : CRI Atom
 * Module   : Library User's Header for PC
 * File     : cri_le_atom_pc.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_le_atom_pc.h
 */

/* ���d��`�h�~					*/
/* Prevention of redefinition	*/
#ifndef	CRI_INCL_CRI_LE_ATOM_PC_H
#define	CRI_INCL_CRI_LE_ATOM_PC_H

/***************************************************************************
 *      �C���N���[�h�t�@�C��
 *      Include files
 ***************************************************************************/
#include <windows.h>
#include <cri_le_xpt.h>
#include <cri_le_error.h>
#include <cri_le_atom.h>
#include <cri_le_atom_ex.h>
#include <cri_le_atom_asr.h>

/***************************************************************************
 *      �萔�}�N��
 *      Macro Constants
 ***************************************************************************/

/***************************************************************************
 *      �����}�N��
 *      Macro Functions
 ***************************************************************************/
/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*JP
 * \brief ���C�u�����������p�R���t�B�O�\���̂Ƀf�t�H���g�l���Z�b�g
 * \ingroup ATOMLIB_PC
 * \param[out]	p_config	�������p�R���t�B�O�\���̂ւ̃|�C���^
 * \par ����:
 * ::criAtomEx_Initialize_PC �֐��ɐݒ肷��R���t�B�O�\����
 * �i ::CriAtomExConfig_PC �j�ɁA�f�t�H���g�̒l���Z�b�g���܂��B<br>
 * \sa CriAtomExConfig_PC
 */
#define criAtomEx_SetDefaultConfig_PC(p_config)				\
{															\
	criAtomEx_SetDefaultConfig(&(p_config)->atom_ex);		\
	criAtomExAsr_SetDefaultConfig(&(p_config)->asr);		\
	criAtomExHcaMx_SetDefaultConfig(&(p_config)->hca_mx);	\
}

/***************************************************************************
 *      �f�[�^�^�錾
 *      Data Type Declarations
 ***************************************************************************/
/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*JP
 * \brief Atom���C�u�����������p�R���t�B�O�\����
 * \ingroup ATOMLIB_PC
 * CRI Atom���C�u�����̓���d�l���w�肷�邽�߂̍\���̂ł��B<br>
 * ::criAtomEx_Initialize_PC �֐��̈����Ɏw�肵�܂��B<br>
 * \sa criAtomEx_Initialize_PC, criAtomEx_SetDefaultConfig_PC
 */
typedef struct CriAtomExConfigTag_PC{
	CriAtomExConfig			atom_ex;	/*JP< AtomEx�������p�R���t�B�O�\����	*/
	CriAtomExAsrConfig		asr;		/*JP< ASR�������p�R���t�B�O			*/
	CriAtomExHcaMxConfig	hca_mx;		/*JP< HCA-MX�������p�R���t�B�O�\����	*/
} CriAtomExConfig_PC;

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
void CRIAPI criAtom_SetThreadPriority_PC(int prio);
int CRIAPI criAtom_GetThreadPriority_PC(void);
void CRIAPI criAtom_SetThreadAffinityMask_PC(DWORD_PTR mask);
DWORD_PTR CRIAPI criAtom_GetThreadAffinityMask_PC(void);

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*JP
 * \brief ���C�u�����������p���[�N�̈�T�C�Y�̌v�Z
 * \ingroup ATOMLIB_PC
 * \param[in]	config		�������p�R���t�B�O�\����
 * \return		CriSint32	���[�N�̈�T�C�Y
 * \retval		0�ȏ�		����ɏ���������
 * \retval		-1			�G���[������
 * \par ����:
 * ���C�u�������g�p���邽�߂ɕK�v�ȁA���[�N�̈�̃T�C�Y���擾���܂��B<br>
 * <br>
 * ���[�N�̈�T�C�Y�̌v�Z�Ɏ��s����ƁA�{�֐��� -1 ��Ԃ��܂��B<br>
 * ���[�N�̈�T�C�Y�̌v�Z�Ɏ��s�������R�ɂ��ẮA�G���[�R�[���o�b�N�̃��b�Z�[�W�Ŋm�F�\�ł��B<br>
 * \par ���l:
 * ���C�u�������K�v�Ƃ��郏�[�N�̈�̃T�C�Y�́A���C�u�����������p�R���t�B�O
 * �\���́i ::CriAtomExConfig_PC �j�̓��e�ɂ���ĕω����܂��B<br>
 * <br>
 * ������NULL���w�肵���ꍇ�A�f�t�H���g�ݒ�
 * �i ::criAtomEx_SetDefaultConfig_PC �K�p���Ɠ����p�����[�^�j��
 * ���[�N�̈�T�C�Y���v�Z���܂��B
 * <br>
 * ���� config �̏��́A�֐����ł̂ݎQ�Ƃ���܂��B<br>
 * �֐��𔲂�����͎Q�Ƃ���܂���̂ŁA�֐����s��� config �̗̈��������Ă�
 * ��肠��܂���B
 * \sa CriAtomExConfig_PC, criAtomEx_Initialize_PC
 */
CriSint32 CRIAPI criAtomEx_CalculateWorkSize_PC(const CriAtomExConfig_PC *config);

/*JP
 * \brief ���C�u�����̏�����
 * \ingroup ATOMLIB_PC
 * \param[in]	config		�������p�R���t�B�O�\����
 * \param[in]	work		���[�N�̈�
 * \param[in]	work_size	���[�N�̈�T�C�Y
 * \par ����:
 * ���C�u���������������܂��B<br>
 * ���C�u�����̋@�\�𗘗p����ɂ́A�K�����̊֐������s����K�v������܂��B<br>
 * �i���C�u�����̋@�\�́A�{�֐������s��A ::criAtomEx_Finalize_PC �֐������s����܂ł̊ԁA
 * ���p�\�ł��B�j<br>
 * <br>
 * ���C�u����������������ۂɂ́A���C�u�����������ŗ��p���邽�߂̃������̈�i���[�N�̈�j
 * ���m�ۂ���K�v������܂��B<br>
 * ���[�N�̈���m�ۂ�����@�ɂ́A�ȉ���2�ʂ�̕��@������܂��B<br>
 * <b>(a) User Allocator����</b>�F�������̊m�ہ^����ɁA���[�U���p�ӂ����֐����g�p������@�B<br>
 * <b>(b) Fixed Memory����</b>�F�K�v�ȃ������̈�𒼐ڃ��C�u�����ɓn�����@�B<br>
 * <br>
 * User Allocator������p����ꍇ�A���[�U�̓��C�u�����Ƀ������m�ۊ֐���o�^���Ă����܂��B<br>
 * work��NULL�Awork_size��0���w�肵�Ė{�֐����Ăяo�����ƂŁA
 * ���C�u�����͓o�^�ς݂̃������m�ۊ֐����g�p���ĕK�v�ȃ������������I�Ɋm�ۂ��܂��B<br>
 * ���[�U�����[�N�̈��p�ӂ���K�v�͂���܂���B<br>
 * ���������Ɋm�ۂ��ꂽ�������́A�I���������i ::criAtomEx_Finalize_PC �֐����s���j�ɉ������܂��B<br>
 * <br>
 * Fixed Memory������p����ꍇ�A���[�N�̈�Ƃ��ĕʓr�m�ۍς݂̃������̈��{�֐���
 * �ݒ肷��K�v������܂��B<br>
 * ���[�N�̈�̃T�C�Y�� ::criAtomEx_CalculateWorkSize_PC �֐��Ŏ擾�\�ł��B<br>
 * �����������̑O�� ::criAtomEx_CalculateWorkSize_PC �֐��Ŏ擾�����T�C�Y���̃�������\��
 * �m�ۂ��Ă����A�{�֐��ɐݒ肵�Ă��������B<br>
 * ���AFixed Memory������p�����ꍇ�A���[�N�̈�̓��C�u�����̏I�������i ::criAtomEx_Finalize_PC �֐��j
 * ���s�Ȃ��܂ł̊ԁA���C�u�������ŗ��p���ꑱ���܂��B<br>
 * ���C�u�����̏I���������s�Ȃ��O�ɁA���[�N�̈�̃�������������Ȃ��ł��������B<br>
 * \par ��:
 * �yUser Allocator�����ɂ�郉�C�u�����̏������z<br>
 * User Allocator������p����ꍇ�A���C�u�����̏������^�I���̎菇�͈ȉ��̈ȉ��̒ʂ�ł��B<br>
 * 	-# �������������s�O�ɁA ::criAtomEx_SetUserAllocator �֐���p���ă������m�ہ^����֐���o�^����B<br>
 * 	-# �������p�R���t�B�O�\���̂Ƀp�����[�^���Z�b�g����B<br>
 * 	-# ::criAtomEx_Initialize_PC �֐��ŏ������������s���B<br>
 * �iwork�ɂ�NULL�Awork_size�ɂ�0���w�肷��B�j<br>
 * 	-# �A�v���P�[�V�����I������ ::criAtomEx_Finalize_PC �֐��ŏI���������s�Ȃ��B<br>
 * 	.
 * <br>��̓I�ȃR�[�h�͈ȉ��̂Ƃ���ł��B<br>
 * \code
 * // �Ǝ��̃������m�ۊ֐�
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
 * 	CriAtomExConfig_PC config;	// ���C�u�����������p�R���t�B�O�\����
 * 		:
 * 	// �Ǝ��̃������A���P�[�^��o�^
 * 	criAtomEx_SetUserAllocator(user_malloc, user_free, NULL);
 * 	
 * 	// ���C�u�����������p�R���t�B�O�\���̂Ƀf�t�H���g�l���Z�b�g
 * 	criAtomEx_SetDefaultConfig_PC(&config);
 * 	
 * 	// ���C�u�����̏�����
 * 	// ���[�N�̈�ɂ�NULL��0���w�肷��B
 * 	// ���K�v�ȃ������́A�o�^�����������m�ۊ֐����g���Ċm�ۂ����B
 * 	criAtomEx_Initialize_PC(&config, NULL, 0);
 * 		:
 * 	// �A�v���P�[�V�����̃��C������
 * 		:
 * 	// �A�v���P�[�V�������I������ۂɏI���������s��
 * 	// �����������Ɋm�ۂ��ꂽ�������́A�o�^��������������֐����g���ĉ�������B
 * 	criAtomEx_Finalize_PC();
 * 		:
 * }
 * \endcode
 * <br>
 * �yFixed Memory�����ɂ�郉�C�u�����̏������z<br>
 * Fixed Memory������p����ꍇ�A���C�u�����̏������^�I���̎菇�͈ȉ��̈ȉ��̒ʂ�ł��B<br>
 * 	-# �������p�R���t�B�O�\���̂Ƀp�����[�^���Z�b�g����B<br>
 * 	-# ���C�u�����̏������ɕK�v�ȃ��[�N�̈�̃T�C�Y���A ::criAtomEx_CalculateWorkSize_PC 
 * �֐����g���Čv�Z����B<br>
 * 	-# ���[�N�̈�T�C�Y���̃��������m�ۂ���B<br>
 * 	-# ::criAtomEx_Initialize_PC �֐��ŏ������������s���B<br>
 * �iwork�ɂ͊m�ۂ����������̃A�h���X���Awork_size�ɂ̓��[�N�̈�̃T�C�Y���w�肷��B�j<br>
 * 	-# �A�v���P�[�V�����I������ ::criAtomEx_Finalize_PC �֐��ŏI���������s�Ȃ��B<br>
 * 	-# ���[�N�̈�̃��������������B<br>
 * 	.
 * <br>��̓I�ȃR�[�h�͈ȉ��̂Ƃ���ł��B<br>
 * \code
 * main()
 * {
 * 	CriAtomExConfig_PC config;	// ���C�u�����������p�R���t�B�O�\����
 * 	void *work;					// ���[�N�̈�A�h���X
 * 	CriSint32 work_size;		// ���[�N�̈�T�C�Y
 * 		:
 * 	// ���C�u�����������p�R���t�B�O�\���̂Ƀf�t�H���g�l���Z�b�g
 * 	criAtomEx_SetDefaultConfig_PC(&config);
 * 	
 * 	// ���C�u�����̏������ɕK�v�ȃ��[�N�̈�̃T�C�Y���v�Z
 * 	work_size = criAtomEx_CalculateWorkSize_PC(&config);
 * 	
 * 	// ���[�N�̈�p�Ƀ��������m��
 * 	work = malloc((size_t)work_size);
 * 	
 * 	// ���C�u�����̏�����
 * 	// ���m�ۍς݂̃��[�N�̈���w�肷��B
 * 	criAtomEx_Initialize_PC(&config, NULL, 0);
 * 		:
 * 	// �A�v���P�[�V�����̃��C������
 * 	// �����̊ԁA�m�ۂ����������͕ێ���������B
 * 		:
 * 	// �A�v���P�[�V�������I������ۂɏI���������s��
 * 	criAtomEx_Finalize_PC();
 * 	
 * 	// �K�v�Ȃ��Ȃ������[�N�̈���������
 * 	free(work);
 * 		:
 * }
 * \endcode
 * \par ���l:
 * ���C�u�������K�v�Ƃ��郏�[�N�̈�̃T�C�Y�́A�������p�R���t�B�O�\���̂̓��e�ɉ�����
 * �ω����܂��B<br>
 * �܂��A�K�v�ȃ��[�N�̈�̃T�C�Y�́A�v���b�g�t�H�[���ɂ���Ă��قȂ�܂��B
 * <br>
 * ���� config �̏��́A�֐����ł̂ݎQ�Ƃ���܂��B<br>
 * �֐��𔲂�����͎Q�Ƃ���܂���̂ŁA�֐����s��� config �̗̈��������Ă�
 * ��肠��܂���B
 * \attention
 * ����A�X�g���[���Đ����s�����ǂ����Ɋ֌W�Ȃ��A Atom ���C�u�����͕K�� 
 * CRI File System ���C�u�����̋@�\���g�p���܂��B<br>
 * ���̂��߁ACRI File System���C�u�����̏��������s���Ă��Ȃ��ꍇ�A
 * Atom ���C�u�����͏������������ɓ����� CRI File System ���C�u�����̏��������s���܂��B<br>
 * <br>
 * Atom ���C�u������������ CRI File System ���C�u����������������ꍇ�A
 * CRI File System �̏������p�����[�^�Ƃ��āA ::CriAtomExConfig �\���̂�
 * fs_config �p�����[�^���g�p���܂��B<br>
 * fs_config �� NULL �̏ꍇ�A Atom ���C�u�����̓f�t�H���g�p�����[�^�i 
 * ::criFs_SetDefaultConfig �}�N���̐ݒ�l�j�� CRI File System ���C�u���������������܂��B<br>
 * <br>
 * ���A�{�֐������s���鎞�_�ŁA���� CRI File System ���C�u�������������ς݂ł���ꍇ�A
 * �{�֐����ł� CRI File System ���C�u�����̏������͍s���܂���B<br>
 * <br>
 * �{�֐��͊������A�^�̊֐��ł��B<br>
 * �{�֐������s����ƁA���΂炭�̊�Atom���C�u�����̃T�[�o�������u���b�N����܂��B<br>
 * �����Đ����ɖ{�֐������s����ƁA���r�؂ꓙ�̕s�����������\�������邽�߁A
 * �{�֐��̌Ăяo���̓V�[���̐؂�ւ�蓙�A���וϓ������e�ł���^�C�~���O�ōs���Ă��������B
 * <br>
 * �{�֐������s��A�K���΂ɂȂ� ::criAtomEx_Finalize_PC �֐������s���Ă��������B<br>
 * �܂��A ::criAtomEx_Finalize_PC �֐������s����܂ł́A�{�֐����ēx���s���Ȃ��ł��������B<br>
 * \sa CriAtomExConfig_PC, criAtomEx_Finalize_PC,
 * criAtomEx_SetUserAllocator, criAtomEx_CalculateWorkSize_PC
 */
void CRIAPI criAtomEx_Initialize_PC(
	const CriAtomExConfig_PC *config, void *work, CriSint32 work_size);

/*JP
 * \brief ���C�u�����̏I��
 * \ingroup ATOMLIB_PC
 * \par ����:
 * ���C�u�������I�����܂��B<br>
 * \attention
 * �{�֐��͊������A�^�̊֐��ł��B<br>
 * �{�֐������s����ƁA���΂炭�̊�Atom���C�u�����̃T�[�o�������u���b�N����܂��B<br>
 * �����Đ����ɖ{�֐������s����ƁA���r�؂ꓙ�̕s�����������\�������邽�߁A
 * �{�֐��̌Ăяo���̓V�[���̐؂�ւ�蓙�A���וϓ������e�ł���^�C�~���O�ōs���Ă��������B
 * <br>
 * ::criAtomEx_Initialize_PC �֐����s�O�ɖ{�֐������s���邱�Ƃ͂ł��܂���B<br>
 * \sa criAtomEx_Initialize_PC
 */
void CRIAPI criAtomEx_Finalize_PC(void);

/*JP
 * \brief �T�[�o�����X���b�h�̃v���C�I���e�B�ύX
 * \ingroup ATOMLIB_PC
 * \param[in]	prio	�X���b�h�v���C�I���e�B
 * \par ����:
 * �T�[�o�����i���C�u�����̓��������j���s���X���b�h�̃v���C�I���e�B��ύX���܂��B<br>
 * �f�t�H���g��ԁi�{�֐������s���Ȃ��ꍇ�j�ł́A�T�[�o�����X���b�h�̃v���C�I���e�B��
 * THREAD_PRIORITY_HIGHEST �ɐݒ肳��܂��B<br>
 * \attention:
 * �{�֐��́A���C�u�������������ɃX���b�h���f�����}���`�X���b�h���f��
 * �i ::CRIATOM_THREAD_MODEL_MULTI �j�ɐݒ肵���ꍇ�ɂ̂݌��ʂ𔭊����܂��B<br>
 * ���̃X���b�h���f����I�������ꍇ�A�{�֐��͉����������s���܂���B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 * <br>
 * �{�֐��͏�������`�I�������O�̊ԂɎ��s����K�v������܂��B<br>
 * �������O��I��������ɖ{�֐������s���Ă��A���ʂ͂���܂���B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 * <br>
 * �T�[�o�����X���b�h�́ACRI File System���C�u�����ł����p����Ă��܂��B<br>
 * ���ł�CRI File System���C�u������API�ŃT�[�o�����X���b�h�̐ݒ��ύX���Ă���ꍇ
 * �{�֐��ɂ��ݒ肪�㏑������܂��̂ł����ӂ��������B<br>
 * \sa criAtomEx_Initialize_PC, criAtomEx_GetThreadPriority_PC
 */
#define criAtomEx_SetThreadPriority_PC(prio)	\
	criAtom_SetThreadPriority_PC(prio)

/*JP
 * \brief �T�[�o�����X���b�h�̃v���C�I���e�B�擾
 * \ingroup ATOMLIB_PC
 * \return	int		�X���b�h�v���C�I���e�B
 * \par ����:
 * �T�[�o�����i���C�u�����̓��������j���s���X���b�h�̃v���C�I���e�B���擾���܂��B<br>
 * �擾�ɐ�������ƁA�{�֐��̓T�[�o�������s���X���b�h�̃v���C�I���e�B��Ԃ��܂��B<br>
 * �擾�Ɏ��s�����ꍇ�A�{�֐��� THREAD_PRIORITY_ERROR_RETURN ��Ԃ��܂��B<br>
 * \attention:
 * �{�֐��́A���C�u�������������ɃX���b�h���f�����}���`�X���b�h���f��
 * �i ::CRIATOM_THREAD_MODEL_MULTI �j�ɐݒ肵���ꍇ�ɂ̂݌��ʂ𔭊����܂��B<br>
 * ���̃X���b�h���f����I�������ꍇ�A�{�֐��̓G���[�l��Ԃ��܂��B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 * <br>
 * �{�֐��͏�������`�I�������O�̊ԂɎ��s����K�v������܂��B<br>
 * �������O��I��������ɖ{�֐������s�����ꍇ�A�{�֐��̓G���[�l��Ԃ��܂��B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 * \sa criAtomEx_Initialize_PC, criAtomEx_SetThreadPriority_PC
 */
#define criAtomEx_GetThreadPriority_PC()	\
	criAtom_GetThreadPriority_PC()

/*JP
 * \brief �T�[�o�����X���b�h�̃A�t�B�j�e�B�}�X�N�ύX
 * \ingroup ATOMLIB_PC
 * \param[in]	mask	�X���b�h�A�t�B�j�e�B�}�X�N
 * \par ����:
 * �T�[�o�����i���C�u�����̓��������j���s���X���b�h�̃A�t�B�j�e�B�}�X�N��ύX���܂��B<br>
 * �f�t�H���g��ԁi�{�֐������s���Ȃ��ꍇ�j�ł́A�T�[�o���������삷��v���Z�b�T��
 * ��ؐ�������܂���B<br>
 * \attention:
 * �{�֐��́A���C�u�������������ɃX���b�h���f�����}���`�X���b�h���f��
 * �i ::CRIATOM_THREAD_MODEL_MULTI �j�ɐݒ肵���ꍇ�ɂ̂݌��ʂ𔭊����܂��B<br>
 * ���̃X���b�h���f����I�������ꍇ�A�{�֐��͉����������s���܂���B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 * <br>
 * �{�֐��͏�������`�I�������O�̊ԂɎ��s����K�v������܂��B<br>
 * �������O��I��������ɖ{�֐������s���Ă��A���ʂ͂���܂���B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 * <br>
 * �T�[�o�����X���b�h�́ACRI File System���C�u�����ł����p����Ă��܂��B<br>
 * ���ł�CRI File System���C�u������API�ŃT�[�o�����X���b�h�̐ݒ��ύX���Ă���ꍇ
 * �{�֐��ɂ��ݒ肪�㏑������܂��̂ł����ӂ��������B<br>
 * \sa criAtomEx_Initialize_PC, criAtomEx_GetThreadAffinityMask_PC
 */
#define criAtomEx_SetThreadAffinityMask_PC(mask)	\
	criAtom_SetThreadAffinityMask_PC(mask)

/*JP
 * \brief �T�[�o�����X���b�h�̃A�t�B�j�e�B�}�X�N�̎擾
 * \ingroup ATOMLIB_PC
 * \return	DWORD_PTR	�X���b�h�A�t�B�j�e�B�}�X�N
 * \par ����:
 * �T�[�o�����i���C�u�����̓��������j���s���X���b�h�̃A�t�B�j�e�B�}�X�N���擾���܂��B<br>
 * �擾�ɐ�������ƁA�{�֐��̓T�[�o�������s���X���b�h�̃A�t�B�j�e�B�}�X�N��Ԃ��܂��B<br>
 * �擾�Ɏ��s�����ꍇ�A�{�֐��� 0 ��Ԃ��܂��B<br>
 * \attention:
 * �{�֐��́A���C�u�������������ɃX���b�h���f�����}���`�X���b�h���f��
 * �i ::CRIATOM_THREAD_MODEL_MULTI �j�ɐݒ肵���ꍇ�ɂ̂݌��ʂ𔭊����܂��B<br>
 * ���̃X���b�h���f����I�������ꍇ�A�{�֐��̓G���[�l��Ԃ��܂��B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 * <br>
 * �{�֐��͏�������`�I�������O�̊ԂɎ��s����K�v������܂��B<br>
 * �������O��I��������ɖ{�֐������s�����ꍇ�A�{�֐��̓G���[�l��Ԃ��܂��B<br>
 * �i�G���[�R�[���o�b�N���������܂��B�j<br>
 * \sa criAtomEx_Initialize_PC, criAtomEx_SetThreadAffinityMask_PC
 */
#define criAtomEx_GetThreadAffinityMask_PC()	\
	criAtom_GetThreadAffinityMask_PC()

#ifdef __cplusplus
}
#endif

#endif	/* CRI_INCL_CRI_LE_ATOM_PC_H */

/* --- end of file --- */
