/*
 o---------------------------------------------------------------------o
 |
 | COS Object (root class)
 |
 o---------------------------------------------------------------------o
 |
 | C Object System
 |
 | Copyright (c) 2006+ Laurent Deniau, laurent.deniau@cern.ch
 |
 | For more information, see:
 | http://cern.ch/laurent.deniau/cos.html
 |
 o---------------------------------------------------------------------o
 |
 | This file is part of the C Object System framework.
 |
 | The C Object System is free software; you can redistribute it and/or
 | modify it under the terms of the GNU Lesser General Public License
 | as published by the Free Software Foundation; either version 3 of
 | the License, or (at your option) any later version.
 |
 | The C Object System is distributed in the hope that it will be
 | useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 | of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 |
 | See <http://www.gnu.org/licenses> for more details.
 |
 o---------------------------------------------------------------------o
 |
 | $Id: Object.c,v 1.5 2008/08/21 15:54:36 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Number.h>
#include <cos/gen/object.h>

#include <stdlib.h>

// -----

makclass(Object,Any);

// ----- allocator, deallocator

static void*
object_alloc(OBJ _cls, U32 extra_size)
{
  useclass(ExBadAlloc);
  struct Class *cls = STATIC_CAST(struct Class*, _cls);
  struct Object *obj = malloc(cls->isz + extra_size);

  if (!obj) THROW(ExBadAlloc); // throw the class -> no allocation!

  obj->Any.id = cls->Behavior.id;
  obj->Any.rc = COS_RC_UNIT;

  return obj;
}

defmethod(OBJ, galloc, mObject)
  retmethod( object_alloc(_1, 0) );
endmethod

defmethod(OBJ, gallocWith, mObject, Int) // alloc with extra size (max 2GB)
  test_assert( self2->value >= 0 );
  retmethod( object_alloc(_1, self2->value) );
endmethod

