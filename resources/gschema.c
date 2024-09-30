#include <gio/gio.h>

#if defined (__ELF__) && ( __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 6))
# define SECTION __attribute__ ((section (".gresource.gschema"), aligned (sizeof(void *) > 8 ? sizeof(void *) : 8)))
#else
# define SECTION
#endif

static const SECTION union { const guint8 data[1774]; const double alignment; void * const ptr;}  gschema_resource_data = {
  "\107\126\141\162\151\141\156\164\000\000\000\000\000\000\000\000"
  "\030\000\000\000\310\000\000\000\000\000\000\050\006\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\003\000\000\000"
  "\005\000\000\000\005\000\000\000\324\265\002\000\377\377\377\377"
  "\310\000\000\000\001\000\114\000\314\000\000\000\320\000\000\000"
  "\256\021\036\234\002\000\000\000\320\000\000\000\011\000\166\000"
  "\340\000\000\000\062\004\000\000\336\276\201\304\000\000\000\000"
  "\062\004\000\000\012\000\114\000\074\004\000\000\104\004\000\000"
  "\253\105\335\160\004\000\000\000\104\004\000\000\006\000\166\000"
  "\120\004\000\000\074\005\000\000\025\150\071\015\002\000\000\000"
  "\074\005\000\000\010\000\114\000\104\005\000\000\114\005\000\000"
  "\253\142\103\107\004\000\000\000\114\005\000\000\010\000\166\000"
  "\130\005\000\000\355\006\000\000\057\000\000\000\002\000\000\000"
  "\147\165\151\056\147\154\141\144\145\000\000\000\000\000\000\000"
  "\027\037\000\000\001\000\000\000\170\332\355\131\301\162\332\060"
  "\024\274\347\053\124\135\073\016\041\264\063\071\000\231\111\247"
  "\344\320\103\073\155\072\235\351\205\021\322\003\124\144\311\225"
  "\236\001\377\175\237\201\064\020\014\301\046\315\064\211\117\200"
  "\255\225\364\126\373\326\013\264\057\347\261\141\123\360\101\073"
  "\333\341\315\323\063\316\300\112\247\264\035\165\370\367\233\136"
  "\164\301\057\273\047\355\067\121\304\256\301\202\027\010\212\315"
  "\064\216\331\310\010\005\254\165\332\272\070\155\262\050\242\101"
  "\332\042\370\241\220\320\075\141\254\355\341\167\252\075\004\146"
  "\364\240\303\107\070\171\313\357\026\152\235\236\277\343\215\305"
  "\070\067\370\005\022\231\064\042\204\016\277\306\311\017\155\225"
  "\233\161\246\125\207\317\226\357\363\201\064\064\361\056\001\217"
  "\031\263\042\206\016\227\302\106\103\047\323\300\273\075\141\002"
  "\264\033\267\003\212\307\243\106\003\234\241\027\066\030\201\142"
  "\140\350\142\006\004\277\062\116\176\322\270\065\101\320\043\053"
  "\314\012\256\300\000\102\004\123\260\310\331\130\130\145\300\167"
  "\370\130\053\350\007\100\044\312\002\147\141\046\222\004\150\353"
  "\326\055\013\244\151\344\130\033\265\174\137\124\360\225\233\363"
  "\333\273\333\273\236\352\240\151\247\274\173\343\323\255\022\253"
  "\320\122\204\031\013\103\245\362\256\204\374\014\017\101\114\113"
  "\043\142\341\107\332\106\001\205\107\336\075\077\053\201\001\253"
  "\112\042\320\045\045\021\003\207\350\342\103\101\316\153\052\134"
  "\040\251\231\167\111\326\250\245\060\207\000\103\042\044\051\145"
  "\347\072\033\132\051\326\313\067\352\077\071\136\066\010\330\134"
  "\306\212\257\043\052\150\350\001\035\225\201\241\163\006\165\022"
  "\041\314\261\260\331\076\056\266\334\120\072\344\257\154\107\357"
  "\125\127\152\065\265\026\241\204\104\075\335\313\132\273\261\074"
  "\235\215\153\164\302\023\072\342\375\163\303\074\021\271\252\167"
  "\266\150\021\150\250\215\051\167\032\211\013\172\051\322\263\135"
  "\025\154\155\267\335\270\047\302\103\104\171\225\122\373\330\115"
  "\053\373\027\122\054\305\327\301\135\272\267\123\337\037\212\060"
  "\042\163\051\222\303\145\171\201\013\243\333\011\335\242\164\037"
  "\255\374\376\300\242\265\007\140\012\373\355\247\110\030\075\272"
  "\142\142\142\327\156\052\037\324\021\276\121\004\365\040\201\072"
  "\056\104\012\206\042\065\130\176\206\007\335\347\006\342\304\171"
  "\341\265\311\230\207\330\115\341\040\162\066\222\200\064\132\116"
  "\310\164\357\102\100\102\027\372\371\074\205\001\140\277\137\354"
  "\366\214\312\276\121\315\073\052\371\307\016\017\051\364\221\047"
  "\026\176\376\144\231\324\322\377\313\307\027\360\261\260\304\305"
  "\243\112\177\220\263\374\264\332\057\313\314\261\322\157\076\206"
  "\364\237\121\124\150\326\121\341\165\106\205\236\066\024\217\351"
  "\033\173\300\120\033\146\367\163\002\226\015\327\070\311\077\300"
  "\061\146\011\112\143\177\061\325\213\065\313\347\227\023\076\244"
  "\201\276\371\257\016\272\326\375\112\367\162\203\225\307\121\376"
  "\152\262\072\050\274\220\240\160\136\007\205\327\031\024\276\202"
  "\161\102\061\260\043\155\241\166\314\115\076\030\171\233\311\350"
  "\230\231\260\031\223\144\201\043\010\054\316\377\056\101\307\160"
  "\014\114\072\073\324\243\324\057\124\164\214\253\372\305\272\375"
  "\000\236\224\130\377\366\360\377\144\212\236\363\022\130\232\050"
  "\201\165\177\254\350\030\246\306\144\053\116\030\220\140\263\365"
  "\160\115\315\242\230\077\330\127\036\150\214\141\276\140\177\271"
  "\126\035\067\136\110\334\150\125\215\033\233\065\256\335\274\273"
  "\321\156\254\375\175\375\007\150\320\072\124\000\050\165\165\141"
  "\171\051\162\145\163\157\165\162\143\145\163\057\001\000\000\000"
  "\004\000\000\000\172\141\160\056\152\163\000\000\000\000\000\000"
  "\343\001\000\000\001\000\000\000\170\332\165\220\315\016\202\060"
  "\020\204\317\364\051\066\361\200\136\032\023\217\004\157\372\036"
  "\265\054\206\270\164\111\177\120\142\174\167\133\042\112\104\173"
  "\152\073\335\157\146\332\053\013\244\234\057\204\250\203\321\276"
  "\141\003\232\120\331\365\006\356\042\253\130\207\026\215\227\154"
  "\132\016\016\271\107\013\045\230\100\124\374\120\203\377\051\152"
  "\152\364\345\243\044\077\351\374\100\050\117\154\253\221\230\347"
  "\205\170\010\061\033\272\340\020\272\250\040\224\373\024\245\251"
  "\141\215\062\336\102\031\237\037\234\126\035\346\143\310\354\025"
  "\070\242\037\137\220\171\350\011\224\354\323\121\172\145\317\030"
  "\233\147\323\166\021\152\327\335\300\061\065\025\254\216\161\155"
  "\267\213\224\263\336\023\377\057\155\061\074\375\313\142\322\142"
  "\033\103\217\215\076\335\336\203\047\256\206\027\074\125\253\211"
  "\257\011\257\202\347\150\221\131\364\301\032\250\025\071\114\216"
  "\117\202\032\234\143\000\050\165\165\141\171\051\163\143\162\151"
  "\160\164\163\057\005\000\000\000\003\000\000\000\142\154\157\143"
  "\153\056\152\163\000\000\000\000\133\003\000\000\001\000\000\000"
  "\170\332\175\222\317\156\203\060\014\306\317\360\024\231\172\000"
  "\124\015\155\332\155\250\275\114\355\151\332\145\117\020\202\241"
  "\121\103\202\102\350\037\115\175\367\331\201\264\235\332\216\123"
  "\022\177\266\177\376\160\075\150\341\244\321\254\007\225\202\202"
  "\066\143\077\161\044\153\226\076\235\157\221\005\067\130\315\222"
  "\244\210\243\123\074\206\051\232\313\352\257\140\226\260\071\233"
  "\042\244\305\163\017\136\261\343\226\111\135\301\201\055\330\153"
  "\061\075\200\302\233\227\167\026\166\322\014\375\012\057\240\335"
  "\267\054\225\324\015\351\366\033\251\200\332\215\235\042\137\144"
  "\076\247\120\064\345\377\223\175\272\300\205\001\363\216\133\024"
  "\115\332\014\201\023\266\144\147\160\307\233\057\336\102\356\314"
  "\247\331\203\375\340\075\244\136\364\256\335\346\131\040\115\225"
  "\222\170\034\006\337\263\321\025\364\205\106\122\274\167\105\034"
  "\327\301\126\241\200\333\324\263\127\106\014\324\062\067\272\105"
  "\130\060\073\260\310\257\007\245\212\073\321\301\335\015\012\045"
  "\305\366\022\241\176\171\357\216\012\362\322\330\312\127\244\377"
  "\204\070\127\111\133\070\016\035\171\305\026\313\360\177\041\307"
  "\127\266\100\371\252\027\274\203\144\064\170\002\016\063\075\200"
  "\016\205\250\075\135\321\066\333\000\116\036\205\343\015\324\133"
  "\167\140\275\121\262\142\263\365\372\005\277\033\312\253\271\103"
  "\375\207\325\156\222\203\057\041\123\030\215\335\040\127\246\111"
  "\223\122\031\261\225\216\315\374\202\372\115\230\012\147\331\065"
  "\263\205\026\007\364\323\137\174\070\067\051\115\165\234\100\310"
  "\206\132\231\075\241\360\301\031\332\201\151\317\152\216\073\117"
  "\164\277\012\154\014\320\000\050\165\165\141\171\051" };

static GStaticResource static_resource = { gschema_resource_data.data, sizeof (gschema_resource_data.data) - 1 /* nul terminator */, NULL, NULL, NULL };

G_MODULE_EXPORT
GResource *gschema_get_resource (void);
GResource *gschema_get_resource (void)
{
  return g_static_resource_get_resource (&static_resource);
}
/* GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1997  Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Modified by the GLib Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GLib Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GLib at ftp://ftp.gtk.org/pub/gtk/.
 */

#ifndef __G_CONSTRUCTOR_H__
#define __G_CONSTRUCTOR_H__

/*
  If G_HAS_CONSTRUCTORS is true then the compiler support *both* constructors and
  destructors, in a usable way, including e.g. on library unload. If not you're on
  your own.

  Some compilers need #pragma to handle this, which does not work with macros,
  so the way you need to use this is (for constructors):

  #ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
  #pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(my_constructor)
  #endif
  G_DEFINE_CONSTRUCTOR(my_constructor)
  static void my_constructor(void) {
   ...
  }

*/

#ifndef __GTK_DOC_IGNORE__

#if  __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR(_func) static void __attribute__((constructor)) _func (void);
#define G_DEFINE_DESTRUCTOR(_func) static void __attribute__((destructor)) _func (void);

#elif defined (_MSC_VER)

/*
 * Only try to include gslist.h if not already included via glib.h,
 * so that items using gconstructor.h outside of GLib (such as
 * GResources) continue to build properly.
 */
#ifndef __G_LIB_H__
#include "gslist.h"
#endif

#include <stdlib.h>

#define G_HAS_CONSTRUCTORS 1

/* We do some weird things to avoid the constructors being optimized
 * away on VS2015 if WholeProgramOptimization is enabled. First we
 * make a reference to the array from the wrapper to make sure its
 * references. Then we use a pragma to make sure the wrapper function
 * symbol is always included at the link stage. Also, the symbols
 * need to be extern (but not dllexport), even though they are not
 * really used from another object file.
 */

/* We need to account for differences between the mangling of symbols
 * for x86 and x64/ARM/ARM64 programs, as symbols on x86 are prefixed
 * with an underscore but symbols on x64/ARM/ARM64 are not.
 */
#ifdef _M_IX86
#define G_MSVC_SYMBOL_PREFIX "_"
#else
#define G_MSVC_SYMBOL_PREFIX ""
#endif

#define G_DEFINE_CONSTRUCTOR(_func) G_MSVC_CTOR (_func, G_MSVC_SYMBOL_PREFIX)
#define G_DEFINE_DESTRUCTOR(_func) G_MSVC_DTOR (_func, G_MSVC_SYMBOL_PREFIX)

#define G_MSVC_CTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _wrapper(void);              \
  int _func ## _wrapper(void) { _func(); g_slist_find (NULL,  _array ## _func); return 0; } \
  __pragma(comment(linker,"/include:" _sym_prefix # _func "_wrapper")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _wrapper;

#define G_MSVC_DTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _constructor(void);              \
  int _func ## _constructor(void) { atexit (_func); g_slist_find (NULL,  _array ## _func); return 0; } \
   __pragma(comment(linker,"/include:" _sym_prefix # _func "_constructor")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _constructor;

#elif defined(__SUNPRO_C)

/* This is not tested, but i believe it should work, based on:
 * http://opensource.apple.com/source/OpenSSL098/OpenSSL098-35/src/fips/fips_premain.c
 */

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  init(_func)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void);

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  fini(_func)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void);

#else

/* constructors not supported for this compiler */

#endif

#endif /* __GTK_DOC_IGNORE__ */
#endif /* __G_CONSTRUCTOR_H__ */

#ifdef G_HAS_CONSTRUCTORS

#ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(gschemaresource_constructor)
#endif
G_DEFINE_CONSTRUCTOR(gschemaresource_constructor)
#ifdef G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(gschemaresource_destructor)
#endif
G_DEFINE_DESTRUCTOR(gschemaresource_destructor)

#else
#warning "Constructor not supported on this compiler, linking in resources will not work"
#endif

static void gschemaresource_constructor (void)
{
  g_static_resource_init (&static_resource);
}

static void gschemaresource_destructor (void)
{
  g_static_resource_fini (&static_resource);
}
