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

#include <lauxlib.h>
#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_script_s.h"
/* -- */
#include "lua/def.h"
#include "lua/setfield.h"

static GSList *_match_util_script(_quvi_t q, const gchar *w)
{
  _quvi_script_t qs;
  GSList *curr;
  gboolean r;
  gchar *s;

  curr = q->scripts.util;
  while (curr != NULL)
    {
      qs = (_quvi_script_t) curr->data;
      s = g_path_get_basename(qs->fpath->str);
      r = (g_strcmp0(s, w) == 0) ? TRUE:FALSE;

      g_free(s);
      s = NULL;

      if (r == TRUE)
        break;

      curr = g_slist_next(curr);
    }
  return (curr);
}

QuviError l_load_util_script(_quvi_t q, const gchar *script_fname,
                             const gchar *script_func)
{
  _quvi_script_t qs;
  lua_State *l;
  GSList *s;

  s = _match_util_script(q, script_fname);
  l = q->handle.lua;

  if (s == NULL)
    luaL_error(l, "Could not find utility script %s in path", script_fname);

  lua_pushnil(l);
  lua_getglobal(l, script_func);

  qs = (_quvi_script_t) s->data;

  if (luaL_dofile(l, qs->fpath->str))
    luaL_error(l, "%s", lua_tostring(l, -1));

  lua_getglobal(l, script_func);

  if (!lua_isfunction(l, -1))
    luaL_error(l, "%s: %s: function not found", qs->fpath->str, script_func);

  lua_newtable(l);
  l_set_reg_userdata(l, USERDATA_QUVI_T, (gpointer) q);
  l_setfield_b(l, GS_VERBOSE, q->opt.scripts.verbose);

  return (QUVI_OK);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
