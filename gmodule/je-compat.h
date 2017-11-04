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

#ifndef _JE_COMPAT_GMODULE_H__
#define _JE_COMPAT_GMODULE_H__

/* JE - compatibility layer to carry on supporting MSVC 2005 */

#ifdef G_OS_WIN32
#include <windows.h>
#endif

#include <config.h>

#include <glib.h>

#if (_WIN32_WINNT < 0x0600 || (defined(_MSC_VER) && _MSC_VER < 1500))

typedef BOOL (fSetThreadErrorMode) (DWORD,
                                    LPDWORD);

#endif

#endif // _JE_COMPAT_GMODULE_H__
