/* GIO - GLib Input, Output and Streaming Library
 *
 * Copyright (C) 2008 Christian Kellner, Samuel Cormier-Iijima
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, see <http://www.gnu.org/licenses/>.
 *
 * Authors: Christian Kellner <gicmo@gnome.org>
 *          Samuel Cormier-Iijima <sciyoshi@gmail.com>
 */

#ifndef _JE_COMPAT_GIO_H__
#define _JE_COMPAT_GIO_H__

/* JE - compatibility layer to carry on supporting MSVC 2005 */

#include <config.h>

#include <glib.h>

#include "ginetaddress.h"
#include "gnetworkingprivate.h"

/* These are provided so that we can use inet_pton() and inet_ntop() on Windows
 * if they are available (i.e. Vista and later), and use the existing code path
 * on Windows XP/Server 2003.
 */
#if ((defined(G_OS_WIN32) && _WIN32_WINNT < 0x0600) || (defined(_MSC_VER) && _MSC_VER < 1500))
gint inet_pton (gint family,
           const gchar *addr_string,
           gpointer addr);

const gchar* inet_ntop (gint family,
           const gpointer addr,
           gchar *addr_str,
           socklen_t size);
#endif

#endif  // _JE_COMPAT_GIO_H__
