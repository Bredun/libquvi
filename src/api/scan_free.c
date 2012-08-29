/* libquvi
 * Copyright (C) 2012  Toni Gundogdu <legatvs@gmail.com>
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
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301  USA
 */

/** @file scan_free.c */

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_scan_s.h"

static void _url_free(gpointer p, gpointer userdata)
{
  if (p == NULL)
    return;

  g_free(p);
  p = NULL;
}

/** @brief Free all of memory used by a scan handle
@note If handle is NULL the function simply returns
@sa @ref scan_media
@ingroup scan
*/
void quvi_scan_free(quvi_scan_t handle)
{
  _quvi_scan_t qs = (_quvi_scan_t) handle;

  if (handle == NULL)
    return;

  /* URLs */

#ifdef HAVE_GLIB_2_28
  g_slist_free_full(qs->url.media, _url_free);
#else
  g_slist_foreach(qs->url.media, _url_free, NULL);
  g_slist_free(qs->url.media);
#endif
  qs->url.media = NULL;

  g_string_free(qs->url.input, TRUE);
  qs->url.input = NULL;

  g_free(qs);
  qs = NULL;
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
