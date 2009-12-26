/*
 o---------------------------------------------------------------------o
 |
 | COS Array - Array view
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
 | $Id: Array_vw.c,v 1.4 2009/09/30 21:52:59 ldeniau Exp $
 |
*/

#include <cos/Array.h>
#include <cos/Number.h>
#include <cos/Slice.h>
#include <cos/View.h>

#include <cos/gen/object.h>

// -----

makclass(ArrayView, Array);
makclass(ArraySubView, ArrayView);

// -----

useclass(ArrayView, ArraySubView);

// ----- initializer

struct Array*
ArrayView_init(struct ArrayView *vecv, struct Array *vec, struct Slice *slc, BOOL isSub)
{
  test_assert( Slice_first(slc) < vec->size &&
               Slice_last (slc) < vec->size, "slice out of range" );

  struct Array* vw = &vecv->Array;

  vw->object = Slice_start (slc)*vec->stride + vec->object;
  vw->size   = Slice_size  (slc);
  vw->stride = isSub ? Slice_stride(slc) : Slice_stride(slc)*vec->stride;
  vecv->ref  = vec;

  return vw;
}

// ----- view constructors

defalias (OBJ, (ginitWith2)gnewWith2, mView, Array, Slice);
defmethod(OBJ,  ginitWith2          , mView, Array, Slice) // vector view
  retmethod(ginitWith3(galloc(ArrayView),_2,_3,aInt(NO)));
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, mView, Array, Range);
defmethod(OBJ,  ginitWith2          , mView, Array, Range) // vector view
  struct Range range = Range_normalize(self3,self2->size);
  struct Slice slice = Slice_fromRange(&range);
  
  retmethod(ginitWith3(galloc(ArrayView),_2,(OBJ)&slice,aInt(NO)));
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, mSubView, Array, Slice);
defmethod(OBJ,  ginitWith2          , mSubView, Array, Slice) // vector view
  retmethod(ginitWith3(galloc(ArraySubView),_2,_3,aInt(YES)));
endmethod

defalias (OBJ, (ginitWith2)gnewWith2, mSubView, Array, Range);
defmethod(OBJ,  ginitWith2          , mSubView, Array, Range) // vector view
  struct Range range = Range_normalize(self3,self2->size);
  struct Slice slice = Slice_fromRange(&range);

  retmethod(ginitWith3(galloc(ArraySubView),_2,(OBJ)&slice,aInt(YES)));
endmethod

defmethod(OBJ, ginitWith3, ArrayView, Array, Slice, Int) // vector view
  PRE POST BODY
    PRT(_1);
    test_assert( !cos_object_isKindOf(_2, classref(ArrayDyn)),
                 "array views accept only non-dynamic array" );

    OBJ ref = gretain(_2); PRT(ref);
    
    ArrayView_init(self, STATIC_CAST(struct Array*, ref), self3, self4->value);

    UNPRT(_1);
    retmethod(_1);
endmethod

// ----- destructor

defmethod(OBJ, gdeinit, ArrayView)
  if (self->ref)              // take care of protection cases
    grelease( (OBJ)self->ref );
  retmethod(_1);
endmethod

// ----- invariant

defmethod(void, ginvariant, ArrayView, (STR)func, (STR)file, (int)line)
  test_assert( cos_object_isKindOf((OBJ)self->ref, classref(Array)),
               "array view points to something not an array", func, file, line);

  test_assert( !cos_object_isKindOf((OBJ)self->ref, classref(ArrayDyn)),
               "array view points to a dynamic an array", func, file, line);

  struct Array *vec = self->ref;

  I32 start  = (vec->object - self->Array.object)/vec->stride;
  U32 size   = self->Array.size;
  I32 stride = self->Array.stride/vec->stride;

  struct Slice *slc = atSlice(start, size, stride);

  U32 first = Slice_first(slc);
  U32 last  = Slice_last (slc);

  test_assert( first < self->ref->size && last < self->ref->size,
               "array view is out of range", func, file, line);

  if (next_method_p)
    next_method(self, func, file, line);
endmethod
