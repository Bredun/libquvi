/* libquvi
 * Copyright (C) 2013  Toni Gundogdu <legatvs@gmail.com>
 *
 * This file is part of libquvi <http://quvi.sourceforge.net/>.
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General
 * Public License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef l_quvi_crypto_err_h
#define l_quvi_crypto_err_h

void l_quvi_object_crypto_invalid_hexstr(lua_State*, _quvi_t, const gboolean);

QuviError
l_quvi_object_crypto_chk_if_failed(lua_State*, const crypto_t,
                                   const gboolean, _quvi_t);

#endif /* l_quvi_crypto_err_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
