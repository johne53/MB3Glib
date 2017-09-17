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

/* JE - compatibility layer to carry on supporting MSVC 2005 */

#include "je-compat.h"
#include <gwin32networking.h>


/* These are provided so that we can use inet_pton() and inet_ntop() on Windows
 * if they are available (i.e. Vista and later), and use the existing code path
 * on Windows XP/Server 2003.
 */
#if ((defined(G_OS_WIN32) && _WIN32_WINNT < 0x0600) || (defined(_MSC_VER) && _MSC_VER < 1500))
gint
inet_pton (gint family,
           const gchar *addr_string,
           gpointer addr)
{
  /* For Vista/Server 2008 and later, there is native inet_pton() in Winsock2 */
  if (ws2funcs.pInetPton != NULL)
    return ws2funcs.pInetPton (family, addr_string, addr);
  else
    {
      /* Fallback codepath for XP/Server 2003 */
      struct sockaddr_storage sa;
      struct sockaddr_in *sin = (struct sockaddr_in *)&sa;
      struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)&sa;
      gint len = sizeof (sa);

      if (family != AF_INET && family != AF_INET6)
        {
          WSASetLastError (WSAEAFNOSUPPORT);
          return -1;
        }

      /* WSAStringToAddress() will accept various not-an-IP-address
       * strings like "127.0.0.1:80", "[1234::5678]:80", "127.1", etc.
       */
      if (!g_hostname_is_ip_address (addr_string))
        return 0;

      if (WSAStringToAddress ((LPTSTR) addr_string, family, NULL, (LPSOCKADDR) &sa, &len) != 0)
        return 0;

      if (family == AF_INET)
        *(IN_ADDR *)addr = sin->sin_addr;
      else
        *(IN6_ADDR *)addr = sin6->sin6_addr;

      return 1;
    }
}

const gchar *
inet_ntop (gint family,
           const gpointer addr,
           gchar *addr_str,
           socklen_t size)
{
  /* On Vista/Server 2008 and later, there is native inet_ntop() in Winsock2 */
  if (ws2funcs.pInetNtop != NULL)
    return ws2funcs.pInetNtop (family, addr, addr_str, size);
  else
    {
      /* Fallback codepath for XP/Server 2003 */
      DWORD buflen = size, addrlen;
      struct sockaddr_storage sa;
      struct sockaddr_in *sin = (struct sockaddr_in *)&sa;
      struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)&sa;

      memset (&sa, 0, sizeof (sa));
      sa.ss_family = family;
      if (sa.ss_family == AF_INET)
        {
          struct in_addr *addrv4 = (struct in_addr *) addr;

          addrlen = sizeof (*sin);
          memcpy (&sin->sin_addr, addrv4, sizeof (sin->sin_addr));
        }
      else if (sa.ss_family == AF_INET6)
        {
          struct in6_addr *addrv6 = (struct in6_addr *) addr;

          addrlen = sizeof (*sin6);
          memcpy (&sin6->sin6_addr, addrv6, sizeof (sin6->sin6_addr));
        }
      else
        {
          WSASetLastError (WSAEAFNOSUPPORT);
          return NULL;
        }
      if (WSAAddressToString ((LPSOCKADDR) &sa, addrlen, NULL, addr_str, &buflen) == 0)
        return addr_str;
      else
        return NULL;
    }
}
#endif
