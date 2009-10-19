#ifndef COS_TESTS_TESTS_H
#define COS_TESTS_TESTS_H

/*
 o---------------------------------------------------------------------o
 |
 | COS testsuites - tests suite
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
 | $Id: tests.h,v 1.6 2009/10/19 19:38:10 ldeniau Exp $
 |
*/

void ut_slice(void);
void ut_range(void);
void ut_xrange(void);
void ut_string(void);
void ut_array_basics(void);
void ut_array_functor(void);

#endif // COS_TESTS_TESTS_H
