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

/* JE - compatibility layer to carry on supporting MSVC 2005 */

#include "je-compat.h"
#include <io.h>

/* We might be using tty emulators such as mintty, so try to detect it, if we passed in a valid FD
 * so we need to check the name of the pipe if _isatty (fd) == 0
 */

#if (defined(G_OS_WIN32) && defined(_MSC_VER) && _MSC_VER < 1500)

gboolean
win32_is_pipe_tty (int fd)
{
  gboolean result = FALSE;
  HANDLE h_fd;
  FILE_NAME_INFO *info = NULL;
  gint info_size = sizeof (FILE_NAME_INFO) + sizeof (WCHAR) * MAX_PATH;
  wchar_t *name = NULL;
  gint length;

  /* XXX: Remove once XP support really dropped */
  HANDLE h_kerneldll = NULL;
  fGetFileInformationByHandleEx *GetFileInformationByHandleEx;

  h_fd = (HANDLE) _get_osfhandle (fd);

  if (h_fd == INVALID_HANDLE_VALUE || GetFileType (h_fd) != FILE_TYPE_PIPE)
    goto done_query;

  /* The following check is available on Vista or later, so on XP, no color support */
  /* mintty uses a pipe, in the form of \{cygwin|msys}-xxxxxxxxxxxxxxxx-ptyN-{from|to}-master */

  /* XXX: Remove once XP support really dropped */
  h_kerneldll = LoadLibraryW (L"kernel32.dll");

  if (h_kerneldll == NULL)
    goto done_query;

  GetFileInformationByHandleEx =
    (fGetFileInformationByHandleEx *) GetProcAddress (h_kerneldll, "GetFileInformationByHandleEx");

  if (GetFileInformationByHandleEx == NULL)
    goto done_query;

  info = g_try_malloc (info_size);

  if (info == NULL ||
      !GetFileInformationByHandleEx (h_fd, FileNameInfo, info, info_size))
    goto done_query;

  info->FileName[info->FileNameLength / sizeof (WCHAR)] = L'\0';
  name = info->FileName;

  length = wcslen (L"\\cygwin-");
  if (wcsncmp (name, L"\\cygwin-", length))
    {
      length = wcslen (L"\\msys-");
      if (wcsncmp (name, L"\\msys-", length))
        goto done_query;
    }

  name += length;
  length = wcsspn (name, L"0123456789abcdefABCDEF");
  if (length != 16)
    goto done_query;

  name += length;
  length = wcslen (L"-pty");
  if (wcsncmp (name, L"-pty", length))
    goto done_query;

  name += length;
  length = wcsspn (name, L"0123456789");
  if (length != 1)
    goto done_query;

  name += length;
  length = wcslen (L"-to-master");
  if (wcsncmp (name, L"-to-master", length))
    {
      length = wcslen (L"-from-master");
      if (wcsncmp (name, L"-from-master", length))
        goto done_query;
    }

  result = TRUE;

done_query:
  if (info != NULL)
    g_free (info);

  /* XXX: Remove once XP support really dropped */
  if (h_kerneldll != NULL)
    FreeLibrary (h_kerneldll);

  return result;
}
#endif
