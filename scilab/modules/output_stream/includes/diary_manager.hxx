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

extern "C"
{
#include "dynlib_output_stream.h"
}

OUTPUT_STREAM_IMPEXP wchar_t *getDiaryFilename(int _Id);
OUTPUT_STREAM_IMPEXP wchar_t **getDiaryFilenames(int *array_size);
OUTPUT_STREAM_IMPEXP int *getDiaryIDs(int *array_size);
OUTPUT_STREAM_IMPEXP double *getDiaryIDsAsDouble(int *array_size);
OUTPUT_STREAM_IMPEXP int diaryCloseAll(void);
OUTPUT_STREAM_IMPEXP int diaryClose(int _iId);
OUTPUT_STREAM_IMPEXP int diaryClose(wchar_t *filename);
OUTPUT_STREAM_IMPEXP int diaryPauseAll(void);
OUTPUT_STREAM_IMPEXP int diaryPause(int _iId);
OUTPUT_STREAM_IMPEXP int diaryPause(wchar_t *filename);
OUTPUT_STREAM_IMPEXP int diaryResumeAll(void);
OUTPUT_STREAM_IMPEXP int diaryResume(int _iId);
OUTPUT_STREAM_IMPEXP int diaryResume(wchar_t *filename);
OUTPUT_STREAM_IMPEXP int diaryExists(int _iId);
OUTPUT_STREAM_IMPEXP int diaryExists(wchar_t *filename);
OUTPUT_STREAM_IMPEXP int diaryNew(wchar_t *filename, bool autorename);
OUTPUT_STREAM_IMPEXP int diaryAppend(wchar_t *filename);
OUTPUT_STREAM_IMPEXP int diarySetFilterMode(int _iId, diary_filter mode);
OUTPUT_STREAM_IMPEXP int diarySetPrefixMode(int ID_diary, diary_prefix_time_format iPrefixMode);
OUTPUT_STREAM_IMPEXP int diarySetPrefixIoModeFilter(int ID_diary, diary_prefix_time_filter mode);

#endif /* __DIARY_MANAGER_HXX__ */
/*--------------------------------------------------------------------------*/
