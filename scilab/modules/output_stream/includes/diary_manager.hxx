/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009 - DIGITEO - Allan CORNET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyrigth (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */
/*--------------------------------------------------------------------------*/
#ifndef __DIARY_MANAGER_HXX__
#define __DIARY_MANAGER_HXX__

#include <wchar.h>
#include "DiaryModesEnum.hxx"

wchar_t *getDiaryFilename(int _Id);
wchar_t **getDiaryFilenames(int *array_size);
int *getDiaryIDs(int *array_size);
double *getDiaryIDsAsDouble(int *array_size);
int diaryCloseAll(void);
int diaryClose(int _iId);
int diaryClose(wchar_t *filename);
int diaryPauseAll(void);
int diaryPause(int _iId);
int diaryPause(wchar_t *filename);
int diaryResumeAll(void);
int diaryResume(int _iId);
int diaryResume(wchar_t *filename);
int diaryExists(int _iId);
int diaryExists(wchar_t *filename);
int diaryNew(wchar_t *filename, bool autorename);
int diaryAppend(wchar_t *filename);
int diarySetFilterMode(int _iId, diary_filter mode);
int diarySetPrefixMode(int ID_diary, diary_prefix_time_format iPrefixMode);
int diarySetPrefixIoModeFilter(int ID_diary, diary_prefix_time_filter mode);

#endif /* __DIARY_MANAGER_HXX__ */
/*--------------------------------------------------------------------------*/
