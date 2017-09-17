/* GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1997  Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _JE_COMPAT_GLIB_H__
#define _JE_COMPAT_GLIB_H__

/* JE - compatibility layer to carry on supporting MSVC 2005 */

#ifdef G_OS_WIN32
#include <windows.h>
#endif

#include <config.h>

#include <glib.h>

#if (_WIN32_WINNT < 0x0600 || (defined(_MSC_VER) && _MSC_VER < 1500))
typedef enum _FILE_INFO_BY_HANDLE_CLASS
{
  FileBasicInfo                   = 0,
  FileStandardInfo                = 1,
  FileNameInfo                    = 2,
  FileRenameInfo                  = 3,
  FileDispositionInfo             = 4,
  FileAllocationInfo              = 5,
  FileEndOfFileInfo               = 6,
  FileStreamInfo                  = 7,
  FileCompressionInfo             = 8,
  FileAttributeTagInfo            = 9,
  FileIdBothDirectoryInfo         = 10,
  FileIdBothDirectoryRestartInfo  = 11,
  FileIoPriorityHintInfo          = 12,
  FileRemoteProtocolInfo          = 13,
  FileFullDirectoryInfo           = 14,
  FileFullDirectoryRestartInfo    = 15,
  FileStorageInfo                 = 16,
  FileAlignmentInfo               = 17,
  FileIdInfo                      = 18,
  FileIdExtdDirectoryInfo         = 19,
  FileIdExtdDirectoryRestartInfo  = 20,
  MaximumFileInfoByHandlesClass
} FILE_INFO_BY_HANDLE_CLASS;

typedef struct _FILE_NAME_INFO
{
  DWORD FileNameLength;
  WCHAR FileName[1];
} FILE_NAME_INFO;

typedef BOOL (WINAPI fGetFileInformationByHandleEx) (HANDLE,
                                                     FILE_INFO_BY_HANDLE_CLASS,
                                                     LPVOID,
                                                     DWORD);
#endif

gboolean win32_is_pipe_tty (int fd);

#endif // _JE_COMPAT_GLIB_H__
