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

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_script_s.h"
/* -- */
#include "misc/script_free.h"

void m_script_free(gpointer p, gpointer userdata)
{
  _quvi_script_t qs = (_quvi_script_t) p;

  if (p == NULL)
    return;

  /* Media, playlist. */

  g_string_free(qs->domains, TRUE);
  qs->domains = NULL;

  /* Any */

  g_string_free(qs->fpath, TRUE);
  qs->fpath = NULL;

  g_string_free(qs->fname, TRUE);
  qs->fname = NULL;

  g_string_free(qs->sha1, TRUE);
  qs->sha1 = NULL;

  g_free(p);
  p = NULL;
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
