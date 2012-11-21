/* libquvi
 * Copyright (C) 2012  Toni Gundogdu <legatvs@gmail.com>
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

#ifndef _quvi_net_s_h
#define _quvi_net_s_h

struct _quvi_net_s
{
  GSList *options;
  struct
  {
    GString *addr;
  } url;
  struct
  {
    GString *errmsg;
    glong resp_code;
  } status;
  struct
  {
    GString *content;
  } fetch;
  struct
  {
    gdouble content_length;
    GString *content_type;
  } http_metainfo;
  struct
  {
    _quvi_t quvi;
  } handle;
};

typedef struct _quvi_net_s *_quvi_net_t;

#endif /* _quvi_net_s_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
