/* libquvi
 * Copyright (C) 2012  Toni Gundogdu <legatvs@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_media_s.h"
#include "_quvi_net_s.h"
/* -- */
#include "misc/match_media_script.h"
#include "misc/resolve.h"
#include "misc/media.h"
#include "net/handle.h"
#include "lua/exec.h"

static gboolean _chk_goto_url(_quvi_media_t qm)
{
  if (qm->url.redirect_to->len >0)
    {
      g_string_assign(qm->url.input, qm->url.redirect_to->str);
      g_string_assign(qm->url.redirect_to, "");
      return (TRUE);
    }
  return (FALSE);
}

extern QuviError l_match_url_to_media_script(_quvi_media_t, GSList**);

typedef QuviMatchMediaScriptMode _qm_mode;

QuviError m_match_media_script(_quvi_t q, _quvi_media_t *qm,
                               const gchar *url, const _qm_mode mode,
                               gchar **result)
{
  gboolean resolve_flag;
  QuviError rc;
  GSList *s;

  resolve_flag = (mode != QM_MATCH_MS_SUPPORTED_OFFLINE)
                 ? TRUE
                 : FALSE;

  if (*qm == NULL)
    *qm = m_media_new(q, url);

  if (resolve_flag == TRUE) /* Resolve URL redirection. */
    {
      m_resolve(q, url, (*qm)->url.input);
      if (quvi_ok(q) == QUVI_FALSE)
        return (q->status.rc);
    }

  rc = l_match_url_to_media_script(*qm, &s);

  if (rc == QUVI_ERROR_NO_SUPPORT)
    {
      g_string_printf(q->status.errmsg, "no support: %s", url);
      return (rc);
    }
  else if (rc != QUVI_OK)
    return (rc);

  switch (mode)
    {
    case QM_MATCH_MS_PARSE:
      rc = l_exec_media_script_parse(*qm, s);
      if (rc == QUVI_OK)
        {
          /* Check if goto_url was set. */
          if (_chk_goto_url(*qm) == TRUE)
            return (m_match_media_script(q, qm, url, mode, result));
        }
      break;

    case QM_MATCH_MS_SUPPORTED_OFFLINE:
    case QM_MATCH_MS_SUPPORTED_ONLINE:
      break;
    }
  return (rc);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
