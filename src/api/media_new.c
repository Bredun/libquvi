/* libquvi
 * Copyright (C) 2012,2013  Toni Gundogdu <legatvs@gmail.com>
 *
 * This file is part of libquvi <http://quvi.sourceforge.net/>.
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General
 * Public License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/** @file media_new.c */

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_media_s.h"
/* -- */
#include "misc/match_media_script.h"

/** @brief Parse media properties for URL
@return New handle, @ref quvi_media_free it when done using it
@note
  - Calling this function restores the current @ref sess_handle to its
    initial state (cookies cleared, custom headers cleared, default
    user-agent string restored, ...)
  - Use @ref quvi_ok for checking if an error occurred
@sa @ref parse_media
@ingroup mediaprop
*/
quvi_media_t quvi_media_new(quvi_t handle, const char *url)
{
  _quvi_media_t qm;
  _quvi_t q;

  /* If G_DISABLE_CHECKS is defined then the check is not performed. */
  g_return_val_if_fail(handle != NULL, NULL);
  g_return_val_if_fail(url != NULL, NULL);

  q = (_quvi_t) handle;
  qm = NULL;

  q->status.rc = m_match_media_script(q, &qm, url, QM_MATCH_MS_PARSE);
  return (qm);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
