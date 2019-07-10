/* Copyright (c) 2000, 2011, Oracle and/or its affiliates. All rights reserved.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License, version 2.0,
   as published by the Free Software Foundation.

   This program is also distributed with certain software (including
   but not limited to OpenSSL) that is licensed under separate terms,
   as designated in a particular file or component or in included license
   documentation.  The authors of MySQL hereby grant you an additional
   permission to link the program and your derivative works with the
   separately licensed software that they have included with MySQL.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License, version 2.0, for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA */

/* Returns info about database status */

#include "heapdef.h"


uchar *heap_position(HP_INFO *info)
{
  return ((info->update & HA_STATE_AKTIV) ? info->current_ptr :
	  (HEAP_PTR) 0);
}


#ifdef WANT_OLD_HEAP_VERSION

/*
  The following should NOT be used anymore as this can't be used together with
   heap_rkey()
*/

ulong heap_position_old(HP_INFO *info)
{
  return ((info->update & HA_STATE_AKTIV) ? info->current_record :
	  (ulong) ~0L);
}

#endif /* WANT_OLD_HEAP_CODE */

/* Note that heap_info does NOT return information about the
   current position anymore;  Use heap_position instead */

int heap_info(reg1 HP_INFO *info,reg2 HEAPINFO *x, int flag )
{
  DBUG_ENTER("heap_info");
  x->records         = info->s->records;
  x->deleted         = info->s->deleted;
  x->reclength       = info->s->reclength;
  x->data_length     = info->s->data_length;
  x->index_length    = info->s->index_length;
  x->max_records     = info->s->max_records;
  x->errkey          = info->errkey;
  x->create_time     = info->s->create_time;
  if (flag & HA_STATUS_AUTO)
    x->auto_increment= info->s->auto_increment + 1;
  DBUG_RETURN(0);
} /* heap_info */
