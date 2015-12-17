/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2006-2013 CRI Middleware Co., Ltd.
 *
 * Library  : CRI File System
 * Module   : Library User's Header
 * File     : cri_le_file_system.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_le_file_system.h
 */

/* ���d��`�h�~					*/
/* Prevention of redefinition	*/
#ifndef	CRI_INCL_CRI_LE_FILE_SYSTEM_H
#define	CRI_INCL_CRI_LE_FILE_SYSTEM_H

/***************************************************************************
 *      �C���N���[�h�t�@�C��
 *      Include files
 ***************************************************************************/
#include <cri_le_xpt.h>
#include <cri_le_error.h>

/***************************************************************************
 *      �萔�}�N��
 *      Macro Constants
 ***************************************************************************/
/* �o�[�W������� */
/* Version Number */
#define CRI_FS_VERSION		(0x02660200)
#define CRI_FS_VER_NUM		"2.66.02"
#define CRI_FS_VER_NAME		"CRI File System(LE)"


#define	CRIFS_CONFIG_DEFAULT_THREAD_MODEL		CRIFS_THREAD_MODEL_MULTI
#define	CRIFS_CONFIG_DEFAULT_NUM_BINDERS		(16)
#define	CRIFS_CONFIG_DEFAULT_NUM_LOADERS		(16)
#define	CRIFS_CONFIG_DEFAULT_NUM_GROUP_LOADERS	(2)
#define	CRIFS_CONFIG_DEFAULT_NUM_STDIO_HANDLES	(16)
#define	CRIFS_CONFIG_DEFAULT_NUM_INSTALLERS		(0)
#define	CRIFS_CONFIG_DEFAULT_MAX_BINDS			(16)
#define	CRIFS_CONFIG_DEFAULT_MAX_FILES			(16)
#define	CRIFS_CONFIG_DEFAULT_MAX_PATH			(256)

/***************************************************************************
 *      �����}�N��
 *      Macro Functions
 ***************************************************************************/
/*JP
 * \brief �f�t�H���g�R���t�B�M�����[�V�����̃Z�b�g
 * \ingroup FSLIB_CRIFS
 * \param[in]	config	�R���t�B�M�����[�V����
 * \par ����:
 * ::criFs_InitializeLibrary �֐��ɐݒ肷��R���t�B�M�����[�V�����i ::CriFsConfig �j�ɁA�f�t�H���g�̒l���Z�b�g���܂��B<br>
 * \par �⑫:
 * �R���t�B�M�����[�V�����ɐݒ肷��e�p�����[�^���A�A�v���P�[�V�����Ŏg�p����n���h���̐��ɉ����Ē��߂��邱�ƂŁA
 * ���C�u�������K�v�Ƃ��郁�����T�C�Y���������}���邱�Ƃ��\�ł��B<br>
 * �������A�A�v���P�[�V�������Ŏg�p����n���h���̐������m�łȂ��J�������i�K��A�������T�C�Y���^�C�g�ł͂Ȃ��P�[�X�ł́A
 * �{�}�N�����g�p���邱�Ƃɂ��ŁA�������������ȗ������邱�Ƃ��\�ł��B<br>
 * \attention:
 * �{�}�N���ł́A�قƂ�ǂ̃P�[�X�ŕK�v�[���Ȑ��̃n���h�����m�ۂł���悤�A�R���t�B�M�����[�V�����̊e�p�����[�^�ɑ傫�߂̒l���Z�b�g���܂��B<br>
 * ���̂��߁A�{�}�N�����g�p�����ꍇ�A���C�u�������K�v�Ƃ��郏�[�N�̈�̃T�C�Y�͑傫���Ȃ�܂��̂ŁA�����ӂ��������B<br>
 * �i�������T�C�Y���^�C�g�ȃP�[�X�ł́A�{�}�N���ŃR���t�B�M�����[�V������������������A�e�p�����[�^���ʂɒ��߂��邱�Ƃ��I�X�X���������܂��B�j<br>
 * \sa
 * CriFsConfig
*/
#define criFs_SetDefaultConfig(p_config)	\
{\
	(p_config)->thread_model		= CRIFS_CONFIG_DEFAULT_THREAD_MODEL;\
	(p_config)->num_binders			= CRIFS_CONFIG_DEFAULT_NUM_BINDERS;\
	(p_config)->num_loaders			= CRIFS_CONFIG_DEFAULT_NUM_LOADERS;\
	(p_config)->num_group_loaders	= CRIFS_CONFIG_DEFAULT_NUM_GROUP_LOADERS;\
	(p_config)->num_stdio_handles	= CRIFS_CONFIG_DEFAULT_NUM_STDIO_HANDLES;\
	(p_config)->num_installers		= CRIFS_CONFIG_DEFAULT_NUM_INSTALLERS;\
	(p_config)->max_binds			= CRIFS_CONFIG_DEFAULT_MAX_BINDS;\
	(p_config)->max_files			= CRIFS_CONFIG_DEFAULT_MAX_FILES;\
	(p_config)->max_path			= CRIFS_CONFIG_DEFAULT_MAX_PATH;\
	(p_config)->version				= CRI_FS_VERSION;\
}

/***************************************************************************
 *      �f�[�^�^�錾
 *      Data Type Declarations
 ***************************************************************************/
/*==========================================================================
 *      CRI File System API
 *=========================================================================*/
/*JP
 * \brief �X���b�h���f��
 * \ingroup FSLIB_CRIFS
 * \par ����:
 * CRI File System���C�u�������ǂ̂悤�ȃX���b�h���f���œ��삷�邩��\���܂��B<br>
 * ���C�u�������������i::criFs_InitializeLibrary�֐��j�ɁA::CriFsConfig�\���̂ɂĎw�肵�܂��B
 * \sa CriFsConfig
 * \sa criFs_InitializeLibrary
 */
typedef enum CriFsThreadModelTag {
	/*JP
	 * \brief �}���`�X���b�h
	 * \par ����:
	 * ���C�u�����͓����ŃX���b�h���쐬���A�}���`�X���b�h�ɂē��삵�܂��B<br>
	 * �X���b�h��::criFs_InitializeLibrary�֐��Ăяo�����ɍ쐬����܂��B
	 */
	/*EN Multi thread				*/
	CRIFS_THREAD_MODEL_MULTI = 0,

	/*JP
	 * \brief �}���`�X���b�h�i���[�U�쓮���j
	 * \par ����:
	 * ���C�u�����͓����ŃX���b�h���쐬���A�}���`�X���b�h�ɂē��삵�܂��B<br>
	 * �X���b�h�� ::criFs_InitializeLibrary �֐��Ăяo�����ɍ쐬����܂��B<br>
	 * �T�[�o�������͍̂쐬���ꂽ�X���b�h��Ŏ��s����܂����A
	 * CRIFS_THREAD_MODEL_MULTI �Ƃ͈قȂ�A�����I�ɂ͎��s����܂���B<br>
	 * ���[�U�� ::criFs_ExecuteMain �֐��Ŗ����I�ɃT�[�o�������쓮����K�v������܂��B<br>
	 * �i  ::criFs_ExecuteMain �֐������s����ƁA�X���b�h���N�����A�T�[�o���������s����܂��B�j<br>
	 */
	CRIFS_THREAD_MODEL_MULTI_USER_DRIVEN = 3,

	/*JP
	 * \brief ���[�U�}���`�X���b�h
	 * \par ����:
	 * ���C�u���������ł̓X���b�h���쐬���܂��񂪁A���[�U���Ǝ��ɍ쐬�����X���b�h����T�[�o�����֐��i::criFs_ExecuteFileAccess�֐��A::criFs_ExecuteDataDecompression�֐��j���Ăяo����悤�A�����̔r������͍s���܂��B
	 */
	/*EN User multi thread				*/
	CRIFS_THREAD_MODEL_USER_MULTI = 1,

	/*JP
	 * \brief �V���O���X���b�h
	 * \par ����:
	 * ���C�u���������ŃX���b�h���쐬���܂���B�܂��A�����̔r��������s���܂���B<br>
	 * ���̃��f����I�������ꍇ�A�eAPI�ƃT�[�o�����֐��i::criFs_ExecuteFileAccess�֐��A::criFs_ExecuteDataDecompression�֐��j�Ƃ𓯈�X���b�h����Ăяo���悤�ɂ��Ă��������B
	 */
	/*EN Single thread				*/
	CRIFS_THREAD_MODEL_SINGLE = 2,

	/* enum be 4bytes */
	CRIFS_THREAD_MODEL_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsThreadModel;

/*JP
 * \brief �R���t�B�M�����[�V����
 * \ingroup FSLIB_CRIFS
 * \par ����:
 * CRI File System���C�u�����̓���d�l���w�肷�邽�߂̍\���̂ł��B<br>
 * ���C�u�������������i::criFs_InitializeLibrary�֐��j�Ɉ����Ƃ��Ė{�\���̂��w�肵�܂��B<br>
 * \par
 * CRI File System���C�u�����́A���������Ɏw�肳�ꂽ�R���t�B�M�����[�V�����ɉ����āA�������\�[�X��K�v�Ȑ��������m�ۂ��܂��B<br>
 * ���̂��߁A�R���t�B�M�����[�V�����Ɏw�肷��l�����������邱�ƂŁA���C�u�������K�v�Ƃ��郁�����̃T�C�Y���������}���邱�Ƃ��\�ł��B<br>
 * �������A�R���t�B�M�����[�V�����Ɏw�肵�����ȏ�̃n���h�����m�ۂ��邱�Ƃ͂ł��Ȃ��Ȃ邽�߁A�l����������������ƁA�n���h���̊m�ۂɎ��s����\��������܂��B<br>
 * \par ���l:
 * �f�t�H���g�ݒ���g�p����ꍇ�A ::criFs_SetDefaultConfig �֐��Ńf�t�H���g�p�����[�^���Z�b�g���A ::criFs_InitializeLibrary �֐��Ɏw�肵�Ă��������B<br>
 * \attention
 * �����I�Ƀ����o��������\���ɔ����A�ݒ�O��::criFs_SetDefaultConfig �֐��ŏ��������Ă���g�p���Ă��������B<br>
 * \sa criFs_InitializeLibrary, criFs_SetDefaultConfig
 */
typedef struct CriFsConfigTag {
	/*JP
		\brief �X���b�h���f��
		\par ����:
		CRI File System�̃X���b�h���f�����w�肵�܂��B<br>
		\sa CriFsThreadModel
	*/
	CriFsThreadModel thread_model;

	/*JP
		\brief �g�p����CriFsBinder�̐�
		\par ����:
		�A�v���P�[�V�������Ŏg�p����o�C���_�iCriFsBinder�j�̐����w�肵�܂��B<br>
		�A�v���P�[�V�������� ::criFsBinder_Create �֐����g�p���ăo�C���_���쐬����ꍇ�A
		�{�p�����[�^�Ɏg�p����o�C���_�̐����w�肷��K�v������܂��B<br>
		<br>
		num_binders�ɂ́u�����Ɏg�p����o�C���_�̍ő吔�v���w�肵�܂��B<br>
		�Ⴆ�΁A ::criFsBinder_Create �֐��� ::criFsBinder_Destroy �֐������݂ɑ����Ď��s����P�[�X�ɂ����ẮA
		�ő哯���ɂ�1�̃o�C���_�����g�p���Ȃ����߁A�֐��̌Ăяo���񐔂Ɋ֌W�Ȃ�num_binders��1���w�肷�邱�Ƃ��\�ł��B<br>
		�t�ɁA�����ʂŃo�C���_��10�g�p����ꍇ�ɂ́A���̑��̏�ʂŃo�C���_��S���g�p���Ȃ��ꍇ�ł����Ă��A
		num_binders��10���w�肷��K�v������܂��B<br>
		\par ���l:
		CRI File System���C�u�����́A�g�p����o�C���_�̐��������̃����������������ɗv�����܂��B<br>
		���̂��߁Anum_binders�ɕK�v�ŏ����̒l���Z�b�g���邱�ƂŁA���C�u�������K�v�Ƃ��郁�����̃T�C�Y��}���邱�Ƃ��\�ł��B<br>
		\sa criFsBinder_Create, criFsBinder_Destroy
	*/
	CriSint32 num_binders;

	/*JP
		\brief �g�p����CriFsLoader�̐�
		\par ����:
		�A�v���P�[�V�������Ŏg�p���郍�[�_�iCriFsLoader�j�̐����w�肵�܂��B<br>
		�A�v���P�[�V�������� ::criFsLoader_Create �֐����g�p���ă��[�_���쐬����ꍇ�A
		�{�p�����[�^�Ɏg�p���郍�[�_�̐����w�肷��K�v������܂��B<br>
		<br>
		num_loaders�ɂ́u�����Ɏg�p���郍�[�_�̍ő吔�v���w�肵�܂��B<br>
		�Ⴆ�΁A ::criFsLoader_Create �֐��� ::criFsLoader_Destroy �֐������݂ɑ����Ď��s����P�[�X�ɂ����ẮA
		�ő哯���ɂ�1�̃��[�_�����g�p���Ȃ����߁A�֐��̌Ăяo���񐔂Ɋ֌W�Ȃ�num_loaders��1���w�肷�邱�Ƃ��\�ł��B<br>
		�t�ɁA�����ʂŃ��[�_��10�g�p����ꍇ�ɂ́A���̑��̏�ʂŃ��[�_��S���g�p���Ȃ��ꍇ�ł����Ă��A
		num_loaders��10���w�肷��K�v������܂��B<br>
		\par ���l:
		CRI File System���C�u�����́A�g�p���郍�[�_�̐��������̃����������������ɗv�����܂��B<br>
		���̂��߁Anum_loaders�ɕK�v�ŏ����̒l���Z�b�g���邱�ƂŁA���C�u�������K�v�Ƃ��郁�����̃T�C�Y��}���邱�Ƃ��\�ł��B<br>
		\sa criFsLoader_Create, criFsLoader_Destroy
	*/
	CriSint32 num_loaders;

	/*JP
		\brief �g�p����CriFsGroupLoader�̐�
		\par ����:
		�A�v���P�[�V�������Ŏg�p����O���[�v���[�_�iCriFsGroupLoader�j�̐����w�肵�܂��B<br>
		�A�v���P�[�V�������� ::criFsGroupLoader_Create �֐����g�p���ăO���[�v���[�_���쐬����ꍇ�A
		�{�p�����[�^�Ɏg�p����O���[�v���[�_�̐����w�肷��K�v������܂��B<br>
		<br>
		num_group_loaders�ɂ́u�����Ɏg�p����O���[�v���[�_�̍ő吔�v���w�肵�܂��B<br>
		�Ⴆ�΁A ::criFsGoupLoader_Create �֐��� ::criFsGroupLoader_Destroy �֐������݂ɑ����Ď��s����P�[�X�ɂ����ẮA
		�ő哯���ɂ�1�̃O���[�v���[�_�����g�p���Ȃ����߁A�֐��̌Ăяo���񐔂Ɋ֌W�Ȃ�num_group_loaders��1���w�肷�邱�Ƃ��\�ł��B<br>
		�t�ɁA�����ʂŃO���[�v���[�_��10�g�p����ꍇ�ɂ́A���̑��̏�ʂŃO���[�v���[�_��S���g�p���Ȃ��ꍇ�ł����Ă��A
		num_group_loaders��10���w�肷��K�v������܂��B<br>
		\par ���l:
		CRI File System���C�u�����́A�g�p����O���[�v���[�_�̐��������̃����������������ɗv�����܂��B<br>
		���̂��߁Anum_group_loaders�ɕK�v�ŏ����̒l���Z�b�g���邱�ƂŁA���C�u�������K�v�Ƃ��郁�����̃T�C�Y��}���邱�Ƃ��\�ł��B<br>
		\sa criFsGroupLoader_Create, criFsGroupLoader_Destroy
	*/
	CriSint32 num_group_loaders;

	/*JP
		\brief �g�p����CriFsStdio�̐�
		\par ����:
		�A�v���P�[�V�������Ŏg�p����CriFsStdio�n���h���̐����w�肵�܂��B<br>
		�A�v���P�[�V�������� ::criFsStdio_OpenFile �֐����g�p����CriFsStdio�n���h�����쐬����ꍇ�A
		�{�p�����[�^�Ɏg�p����CriFsStdio�n���h���̐����w�肷��K�v������܂��B<br>
		<br>
		num_stdio_handles�ɂ́u�����Ɏg�p����CriFsStdio�n���h���̍ő吔�v���w�肵�܂��B<br>
		�Ⴆ�΁A ::criFsStdio_OpenFile �֐��� ::criFsStdio_CloseFile �֐������݂ɑ����Ď��s����P�[�X�ɂ����ẮA
		�ő哯���ɂ�1��CriFsStdio�n���h�������g�p���Ȃ����߁A�֐��̌Ăяo���񐔂Ɋ֌W�Ȃ�num_stdio_handles��1���w�肷�邱�Ƃ��\�ł��B<br>
		�t�ɁA�����ʂ�CriFsStdio�n���h����10�g�p����ꍇ�ɂ́A���̑��̏�ʂ�CriFsStdio�n���h����S���g�p���Ȃ��ꍇ�ł����Ă��A
		num_stdio_handles��10���w�肷��K�v������܂��B<br>
		\par ���l:
		CRI File System���C�u�����́A�g�p����CriFsStdio�n���h���̐��������̃����������������ɗv�����܂��B<br>
		���̂��߁Anum_stdio_handles�ɕK�v�ŏ����̒l���Z�b�g���邱�ƂŁA���C�u�������K�v�Ƃ��郁�����̃T�C�Y��}���邱�Ƃ��\�ł��B<br>
		\attention
		�u���b�W���C�u�������g�p����ADX���C�u������~���僉�C�u�����𕹗p����ꍇ�A
		ADXT�n���h����criSsPly�n���h���͓����I��CriFsStdio�n���h�����쐬���܂��B<br>
		���̂��߁A�u���b�W���C�u�������g�p����ꍇ�ɂ́ACRI File System���C�u��������������
		num_stdio_handles��ADXT�n���h����criSsPly�n���h���̐����������l���w�肵�Ă��������B<br>
		\sa criFsStdio_OpenFile, criFsStdio_CloseFile
	*/
	CriSint32 num_stdio_handles;

	/*JP
		\brief �g�p����CriFsInstaller�̐�
		\par ����:
		�A�v���P�[�V�������Ŏg�p����C���X�g�[���iCriFsInstaller�j�̐����w�肵�܂��B<br>
		�A�v���P�[�V�������� ::criFsInstaller_Create �֐����g�p���ăC���X�g�[�����쐬����ꍇ�A
		�{�p�����[�^�Ɏg�p����C���X�g�[���̐����w�肷��K�v������܂��B<br>
		<br>
		num_installers�ɂ́u�����Ɏg�p����C���X�g�[���̍ő吔�v���w�肵�܂��B<br>
		�Ⴆ�΁A ::criFsInstaller_Create �֐��� ::criFsInstaller_Destroy �֐������݂ɑ����Ď��s����P�[�X�ɂ����ẮA
		�ő哯���ɂ�1�̃C���X�g�[�������g�p���Ȃ����߁A�֐��̌Ăяo���񐔂Ɋ֌W�Ȃ�num_installers��1���w�肷�邱�Ƃ��\�ł��B<br>
		�t�ɁA�����ʂŃC���X�g�[����10�g�p����ꍇ�ɂ́A���̑��̏�ʂŃC���X�g�[����S���g�p���Ȃ��ꍇ�ł����Ă��A
		num_installers��10���w�肷��K�v������܂��B<br>
		\par ���l:
		CRI File System���C�u�����́A�g�p����C���X�g�[���̐��������̃����������������ɗv�����܂��B<br>
		���̂��߁Anum_installers�ɕK�v�ŏ����̒l���Z�b�g���邱�ƂŁA���C�u�������K�v�Ƃ��郁�����̃T�C�Y��}���邱�Ƃ��\�ł��B<br>
		\attention
		::criFs_SetDefaultConfig �}�N�����g�p���ăR���t�B�M�����[�V����������������ꍇ�Anum_installers�̐���0�ɐݒ肳��܂��B<br>
		���̂��߁A�C���X�g�[�����g�p����ꍇ�ɂ́A�A�v���P�[�V��������num_installers�𖾎��I�Ɏw�肷��K�v������܂��B<br>
		\sa criFsInstaller_Create, criFsInstaller_Destroy
	*/
	CriSint32 num_installers;

	/*JP
		\brief �ő哯���o�C���h��
		\par ����:
		�A�v���P�[�V�������Ńo�C���h�������s���A�ێ�����o�C���hID�iCriFsBindId�j�̐����w�肵�܂��B<br>
		�A�v���P�[�V�������� ::criBinder_BindCpk �֐������g�p���ăo�C���h�������s���ꍇ�A
		�{�p�����[�^�Ɏg�p����o�C���hID�̐����w�肷��K�v������܂��B<br>
		<br>
		max_binds�ɂ́u�����Ɏg�p����o�C���hID�̍ő吔�v���w�肵�܂��B<br>
		�Ⴆ�΁A ::criFsBinder_BindCpk �֐��� ::criFsBinder_Unbind �֐������݂ɑ����Ď��s����P�[�X�ɂ����ẮA
		�ő哯���ɂ�1�̃o�C���hID�����g�p���Ȃ����߁A�֐��̌Ăяo���񐔂Ɋ֌W�Ȃ�max_binds��1���w�肷�邱�Ƃ��\�ł��B<br>
		�t�ɁA�����ʂŃo�C���hID��10�g�p����ꍇ�ɂ́A���̑��̏�ʂŃo�C���h����؍s��Ȃ��ꍇ�ł����Ă��A
		max_binds��10���w�肷��K�v������܂��B<br>
		\par ���l:
		CRI File System���C�u�����́A�g�p����o�C���hID�̐��������̃����������������ɗv�����܂��B<br>
		���̂��߁Amax_binds�ɕK�v�ŏ����̒l���Z�b�g���邱�ƂŁA���C�u�������K�v�Ƃ��郁�����̃T�C�Y��}���邱�Ƃ��\�ł��B<br>
		\sa criFsBinder_BindCpk, criFsBinder_BindFile, criFsBinder_BindFiles, criFsBinder_BindDirectory, criFsBinder_Unbind
	*/
	CriSint32 max_binds;

	/*JP
		\brief �ő哯���I�[�v���t�@�C����
		\par ����:
		�A�v���P�[�V�������ŃI�[�v������t�@�C���̐����w�肵�܂��B<br>
		�A�v���P�[�V�������� ::criFsStdio_OpenFile �֐������g�p���ăt�@�C�����I�[�v������ꍇ�A
		�{�p�����[�^�ɃI�[�v������t�@�C���̐����w�肷��K�v������܂��B<br>
		<br>
		max_files�ɂ́u�����ɃI�[�v������t�@�C���̍ő吔�v���w�肵�܂��B<br>
		�Ⴆ�΁A ::criFsStdio_OpenFile �֐��� ::criFsStdio_CloseFile �֐������݂ɑ����Ď��s����P�[�X�ɂ����ẮA
		�ő哯���ɂ�1�̃t�@�C�������I�[�v�����Ȃ����߁A�֐��̌Ăяo���񐔂Ɋ֌W�Ȃ�max_files��1���w�肷�邱�Ƃ��\�ł��B<br>
		�t�ɁA�����ʂŃt�@�C����10�I�[�v������ꍇ�ɂ́A���̑��̏�ʂŃt�@�C����1�����I�[�v�����Ȃ��ꍇ�ł����Ă��A
		max_files��10���w�肷��K�v������܂��B<br>
		\par �⑫:
		CRI File System���C�u�����́A�ȉ��̊֐������s�����ꍇ�Ƀt�@�C�����I�[�v�����܂��B<br>
		\table "�t�@�C�����I�[�v���������" align=center border=1 cellspacing=0 cellpadding=4
		{�֐�					|���l	}
		[criFsBinder_BindCpk	|�I�[�v�������t�@�C���̐���1�B<br> criFsBinder_Unbind �֐������s�����܂ł̊ԃt�@�C���̓I�[�v�����ꑱ����B	]
		[criFsBinder_BindFile	|�I�[�v�������t�@�C���̐���1�B<br> criFsBinder_Unbind �֐������s�����܂ł̊ԃt�@�C���̓I�[�v�����ꑱ����B	]
		[criFsBinder_BindFiles	|���X�g�Ɋ܂܂�鐔���t�@�C�����I�[�v�������B<br> criFsBinder_Unbind �֐������s�����܂Ńt�@�C���̓I�[�v�����ꑱ����B	]
		[criFsLoader_Load		|�I�[�v�������t�@�C���̐���1�B<br> ���[�h����������܂ł̊ԃt�@�C���̓I�[�v�����ꑱ����B<br> �o�C���_���w�肵���ꍇ�A�t�@�C���̓I�[�v������Ȃ��i�o�C���_�����ɃI�[�v���ς݂̂��߁j�B	]
		[criFsStdio_OpenFile	|�I�[�v�������t�@�C���̐���1�B<br> criFsStdio_CloseFile �֐������s�����܂ł̊ԃt�@�C���̓I�[�v�����ꑱ����B<br> �o�C���_���w�肵���ꍇ�A�t�@�C���̓I�[�v������Ȃ��i�o�C���_�����ɃI�[�v���ς݂̂��߁j�B	]
		[criFsInstaller_Copy	|�I�[�v�������t�@�C���̐���2�B<br> �t�@�C���R�s�[����������܂ł̊ԃt�@�C���̓I�[�v�����ꑱ����B<br> �o�C���_���w�肵���ꍇ�A�I�[�v�������t�@�C����1�ɂȂ�i1���o�C���_�����ɃI�[�v���ς݂̂��߁j�B	]
		\endtable
		\attention
		�u���b�W���C�u�������g�p����ADX���C�u������~���僉�C�u�����𕹗p����ꍇ�A
		ADXT�n���h����criSsPly�n���h���͓����I��CriFsStdio�n���h�����쐬���܂��B<br>
		���̂��߁A�u���b�W���C�u�������g�p����ꍇ�ɂ́ACRI File System���C�u��������������
		max_files��ADXT�n���h����criSsPly�n���h���̐����������l���w�肵�Ă��������B<br>
	*/
	CriSint32 max_files;

	/*JP
		\brief �p�X�̍ő咷�i�o�C�g�P�ʁj
		\par ����:
		�A�v���P�[�V�������Ŏw�肷��t�@�C���p�X�̍ő咷���w�肵�܂��B<br>
		�A�v���P�[�V�������� ::criFsLoader_Load �֐������g�p���ăt�@�C���ɃA�N�Z�X����ꍇ�A
		�{�p�����[�^�ɃA�v���P�[�V�����Ŏg�p����p�X������̍ő咷���w�肷��K�v������܂��B<br>
		<br>
		max_path�ɂ́u�g�p����p�X������̍ő吔�v���w�肵�܂��B<br>
		�����ʂ�256�o�C�g�̃t�@�C���p�X���g�p����ꍇ�A���̑��̏�ʂ�32�o�C�g�̃t�@�C���p�X�����g��Ȃ��ꍇ�ł��A
		max_path�ɂ�256���w�肷��K�v������܂��B<br>
		\par ���l:
		�p�X�̍ő咷�ɂ́A�I�[��NULL�������܂񂾐����w�肷��K�v������܂��B<br>
		�i�u�������{�P�o�C�g�v�̒l���w�肷��K�v������܂��B�j<br>
		\attention
		PC���A���[�U���A�v���P�[�V���������R�ȏꏊ�ɃC���X�g�[���\�ȏꍇ�ɂ́A�z�肳���ő�T�C�Y�� max_path �Ɏw�肷��K�v������܂��̂ŁA�����ӂ��������B<br>
	*/
	CriSint32 max_path;

	/*JP
		\brief ���C�u�����o�[�W�����ԍ�
		\par ����:
		CRI File System���C�u�����̃o�[�W�����ԍ��ł��B<br>
		::criFs_SetDefaultConfig �֐��ɂ��A�{�w�b�_�ɒ�`����Ă���o�[�W�����ԍ����ݒ肳��܂��B<br>
		\attention
		�A�v���P�[�V�����ł́A���̒l��ύX���Ȃ��ł��������B<br>
	*/
	CriUint32 version;
} CriFsConfig;

/*==========================================================================
 *      CRI File System Binder
 *=========================================================================*/
struct CriFsBinderHnObjTag;
/*JP
 * \brief CriFsBinder�n���h��
 * \ingroup FSLIB_CRIFS
 * \par ����:
 * ADX2 LE �̏ꍇ�A�֐������ɓn���o�C���_�n���h����NULL���w�肵�Ă��������B
 */
typedef struct CriFsBinderHnObjTag *CriFsBinderHn;


#endif	/* CRI_INCL_CRI_LE_FILE_SYSTEM_H */

/* --- end of file --- */
