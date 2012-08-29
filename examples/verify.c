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

#include <locale.h>
#include <stdlib.h>
#include <glib.h>
#include <quvi.h>

#include "examples.h"

static void usage()
{
  g_printerr("Usage: verify <URL>\n");
  exit(0);
}

typedef quvi_callback_status qcs;

gint main(gint argc, gchar **argv)
{
  gchar *url = NULL;
  gint i = 1;

  g_assert(qv == NULL);
  g_assert(q == NULL);

  setlocale(LC_ALL, "");

  if (argc < 2)
    usage();

  q = quvi_new();
  exit_if_error();

  for (; i<argc; ++i)
    {
      if (g_strcmp0("-v", argv[i]) == 0)
        enable_verbose();
      else if (g_strcmp0("-a", argv[i]) == 0)
        enable_autoproxy();
      else
        url = argv[i];
    }

  if (url == NULL)
    usage();

  quvi_set(q, QUVI_OPTION_CALLBACK_STATUS, (qcs) status);

  qv = quvi_verify_new(q, url);
  exit_if_error();
  {
    gchar *ct, *fe;
    gdouble cl;

    quvi_verify_get(qv, QUVI_VERIFY_PROPERTY_FILE_EXTENSION, &fe);
    quvi_verify_get(qv, QUVI_VERIFY_PROPERTY_CONTENT_TYPE, &ct);
    quvi_verify_get(qv, QUVI_VERIFY_PROPERTY_LENGTH_BYTES, &cl);

    g_print("content_type=%s\nlength_bytes=%.0f\nfile_ext=%s\n",
            ct, cl, fe);
  }
  cleanup();

  g_assert(qv == NULL);
  g_assert(q == NULL);

  return (0);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
