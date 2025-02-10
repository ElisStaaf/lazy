#ifndef __LAZY__
#define __LAZY__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iso646.h>

/* DISCLAIMER: Some of these are shamelessly stolen from "Pretty C", which
 *             is licensed under the "WTFPL", keep that in mind. Because
 *             it is licensed under the WTFPL, I'm exercising my legal
 *             right to "DO WHAT THE FUCK I WANT TO". Thankyou. Just
 *             keep in mind that if you see a section with the
 *             "<pretty>" tag it was either blatanly stolen or 
 *             derives from the "Pretty C" module for C. Check
 *             Pretty C out at <github.com/aartaka/pretty.c>. */

/* Debug <pre> */
#define DEBUG(msg)
#ifndef LAZY_DEBUG
# undef  DEBUG
# define DEBUG(msg) printf("%s\n", msg);
#endif

/* Checks <pre> */
#ifndef LAZY_NO_WARN
# ifdef __cplusplus
#  warning "You are running lazy on C++."
#  warning "Therefore, some functions will not work."
#  warning "Define ``LAZY_NO_WARN`` to hide this message"
# endif
#endif

/* "Predicates" <...> <impl> <pretty> */

#define even     0 == 1 &
#define odd      1 == 1 &
#define positive 0 <
#define negative 0 >
#define neutral  0 ==
#define empty    NULL ==
#define null     NULL ==

/* Comparison-Definitions <...> <impl> <pretty> */

#define eq ==
#define ne !=
#define gt >
#define lt <
#define ge >=
#define le <=

/* Ternaries & Conditionals <...> <impl> <pretty> */

#define ifnt(...)   if(!(__VA_ARGS__))
#define ifnot(...)  if(!(__VA_ARGS__))
#define elif        else if
#define elifnt(...) else if(!(__VA_ARGS__))
#define elifnot(...) else if(!(__VA_ARGS__))
#define when
#define unless      !
#define then        ?
#define other       :
#define otherwise   :
#define otherwhen   :
#define only        : NULL

/* Loops & Blocks <...> <impl> <pretty> */

#define until(...)   while(!(__VA_ARGS__))
#define always       while(1)
#define forever      while(1)
#define loop         while(1)
#define indefinitely while(1)
#define never        while(0)
#define comment      while(0)
#define repeat       do
#define done         break
#define finish       break
#define pass         continue

/* Dynamically-Typed Declarations <...> <wrapper> <pretty> */

#if defined(__GNUC__) || defined(__GNUG__)
#define var   __auto_type
#define let   __auto_type
#define local __auto_type
#elif __STDC_VERSION__ > 201710L || defined(__cplusplus)
#define var   auto
#define let   auto
#define local auto
#endif

/* Tracking & Freeing Resources <...> <impl> <pretty> */

#if (__STDC_VERSION__ > 201710L || defined(__GNUC__) || defined(__GNUG__))
#define with(var, close, ...)					\
        for (typeof((__VA_ARGS__)) var = (__VA_ARGS__),         \
                     *pretty_with_flag = (void*) 1;             \
             pretty_with_flag;                                  \
             (close)(var), pretty_with_flag = (void*) 0)
#else
#define with(var, close, ...)					\
        for (void *var = (void*) (__VA_ARGS__),                 \
                     *pretty_with_flag = (void*) 1;             \
             pretty_with_flag;                                  \
             (close)(var), pretty_with_flag = (void*) 0)
#endif

/* Python "range()" <...> <impl> <pretty> */

#define forrangeby(var, type, init, target, by) \
        for (type var = (type)(init);           \
             (((init) >= ((type) target))       \
              ? (var > ((type) target))         \
              : (var < ((type) target)));       \
             (((init) >= ((type) target))       \
              ? (var -= (by))                   \
              : (var += (by))))

#if (__STDC_VERSION__ > 201710L || defined(__GNUC__) || defined(__GNUG__)) && !defined(__clang_major__)
#define forrange(var, init, ...)                                \
        for (typeof((init)+(__VA_ARGS__)) pretty_init = (init), \
                     var = pretty_init,                         \
                     pretty_target = (__VA_ARGS__);             \
             ((pretty_init >= pretty_target)                    \
              ? (var > pretty_target)                           \
              : (var < pretty_target));                         \
             var += ((pretty_init >= pretty_target) ? -1 : +1))
#else
#define forrange(var, init, ...)                                \
        for (int pretty_init = (init),                          \
                     var = pretty_init,                         \
                     pretty_target = (__VA_ARGS__);             \
             var != pretty_target;                              \
             var += ((pretty_init >= pretty_target) ? -1 : +1))
#endif

/* Repeat X Times <...> <impl> <pretty> */

#if  (__STDC_VERSION__ > 201710L || defined(__GNUC__) || defined(__GNUG__)) && !defined(__clang_major__)
#define fortimes(var, ...)                                              \
        for (typeof((__VA_ARGS__)) pretty_result = (__VA_ARGS__),       \
                     var = (typeof((__VA_ARGS__))) 0;                   \
             var < pretty_result;                                       \
             ++var)
#else
#define fortimes(var, ...)                                              \
        for (size_t var = 0, pretty_result = (size_t)(__VA_ARGS__);     \
             var < pretty_result;                                       \
             ++var)
#endif

/* Finally, FOREACH!!! <...> <impl> <pretty> */

#define foreach(var, type, length, ...)                                 \
        for (type *pretty_init = (__VA_ARGS__),                         \
                     *pretty_foreach_flag = (void*) 1;                  \
             pretty_foreach_flag;                                       \
             pretty_foreach_flag = (void*) 0)                           \
                for (size_t pretty_offset = 0;                          \
                     pretty_offset < length;                            \
                     pretty_offset += 1)                                \
                        for (type *var = (pretty_init + pretty_offset), \
                                     *pretty_foreach_flag2 = (void*) 1; \
                             pretty_foreach_flag2;                      \
                             pretty_foreach_flag2 = (void*) 0)

/* Loops over provided args <...> <impl> <pretty> */

#define forthese(var, type, ...)                                        \
        for (type *pretty_init = (type[]){__VA_ARGS__},                 \
                     *pretty_forthese_flag = (void*) 1;                 \
             pretty_forthese_flag;                                      \
             pretty_forthese_flag = (void*) 0)                          \
                for (size_t pretty_offset = 0;                          \
                     pretty_offset < (sizeof((type[]){__VA_ARGS__})     \
                                      / sizeof(type));                  \
                     pretty_offset += 1)                                \
                        for (type var = pretty_init [pretty_offset],    \
                                     *pretty_forthese_flag2 = (void*) 1; \
                             pretty_forthese_flag2;                     \
                             pretty_forthese_flag2 = (void*) 0)

/* Easy Resource & Array Allocation <...> <impl> <pretty> */


static void *pretty_allocpy(size_t size, void *contents) {
	char *allocated = (char *)malloc(size);
	memcpy(allocated, contents, size);
	return allocated;
}

#define new(type, ...)                                                  \
        (type *) pretty_allocpy(sizeof(type), &((type) {__VA_ARGS__}))

/* Btw there is a better implementation, down below,
 * keeping this in for historical purposes. */
#define vector(length, type, ...)                               \
        (type*) pretty_allocpy(sizeof(type) * length,           \
                               (type[length]){__VA_ARGS__})

#define delete free

/* "Defer" From the Best Programming Language 
 * Made This century; Go! <...> <impl> <pretty> */

#define defer(...)                              \
        for (bool pretty_flag = 1;              \
             pretty_flag;                       \
             pretty_flag = 0, (__VA_ARGS__))

/* Try/Catch Blocks <...> <impl> <pretty> */

#define try                                     \
        errno = 0;                              \
        for (bool pretty_flag = 1;              \
             pretty_flag;                       \
             pretty_flag = 0)

static int pretty_err_part_of(int err, size_t length, int *errs) {
	for (size_t i = 0; i < length; ++i)
		if (err == errs[i])
			return 1;
	return 0;
}

#define catch(...)                                              \
        if (pretty_err_part_of                                  \
            (errno,                                             \
             sizeof ((int[]){__VA_ARGS__}) / sizeof(int),       \
             (int[]){__VA_ARGS__}))

/* Print++ (Better Print) <...> <impl> <pretty> */

#define print(...)                                                      \
        _Generic((__VA_ARGS__),                                         \
                 bool: fputs((bool)(__VA_ARGS__) ? "true" : "false", stdout), \
                 default: printf(                                       \
                         _Generic((__VA_ARGS__),                        \
                                  char*:              "%s",		\
                                  char:               "%c",		\
                                  short:              "%hi",		\
                                  int:                "%i",		\
                                  long:               "%li",		\
                                  float:              "%g",		\
                                  double:             "%g",		\
                                  default:            "%p"),		\
                         (__VA_ARGS__)))
#define println(...)				\
	print(__VA_ARGS__), print("\n")

/* Type-Definitions <...> <impl> <pretty> */

typedef char*          string;
typedef char           byte;
typedef char*          bytes;
typedef void*          any;
typedef unsigned char  uchar;
typedef unsigned char  ubyte;
typedef unsigned char* ubytes;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned long  ulong;

/* Boolean <...> <impl> <pretty> */

#if !defined(__cplusplus)

typedef unsigned int bool;

#define true  (bool)1
#define false (bool)0

#endif

/* Len-Macro <...> <impl> <pretty> */

#if __STDC_VERSION__ >= 201112L
#define len(...)                                                        \
        (__VA_ARGS__ == NULL) ? 0                                       \
        : _Generic((__VA_ARGS__),                                       \
                   char*: strlen((char*)(__VA_ARGS__)),                 \
                   default: (sizeof(__VA_ARGS__) / sizeof(__VA_ARGS__[0])))
#else
#define len(...)                                                \
        (__VA_ARGS__ == NULL) ? 0                               \
        : (sizeof(__VA_ARGS__) / sizeof(__VA_ARGS__[0]))
#endif

/* Miscellanous math <math.h,...> <impl> */

#define min(a, b) ((a) > (b) ? (b) : (a))
#define max(a, b) ((a) < (b) ? (b) : (a))

#define square(x) (x * x)
#define cube(x)   (x * x * x)

/* Vector/Dynamic array <...> <impl> */

#define vec_unpack_(v) \
  (char**)&(v)->data, &(v)->length, &(v)->capacity, sizeof(*(v)->data)


#define vec_t(T) \
  struct { T *data; int length, capacity; }


#define vec_init(v) \
  memset((v), 0, sizeof(*(v)))


#define vec_deinit(v) \
  ( free((v)->data),  \
    vec_init(v) ) 


#define vec_push(v, val)               \
  ( vec_expand_(vec_unpack_(v)) ? -1 : \
    ((v)->data[(v)->length++] = (val), 0), 0 )


#define vec_pop(v) \
  (v)->data[--(v)->length]


#define vec_splice(v, start, count)            \
  ( vec_splice_(vec_unpack_(v), start, count), \
    (v)->length -= (count) )


#define vec_swapsplice(v, start, count)            \
  ( vec_swapsplice_(vec_unpack_(v), start, count), \
    (v)->length -= (count) )


#define vec_insert(v, idx, val)             \
  ( vec_insert_(vec_unpack_(v), idx) ? -1 : \
    ((v)->data[idx] = (val), 0), (v)->length++, 0 )
    

#define vec_sort(v, fn) \
  qsort((v)->data, (v)->length, sizeof(*(v)->data), fn)


#define vec_swap(v, idx1, idx2) \
  vec_swap_(vec_unpack_(v), idx1, idx2)


#define vec_truncate(v, len) \
  ((v)->length = (len) < (v)->length ? (len) : (v)->length)


#define vec_clear(v) \
  ((v)->length = 0)


#define vec_first(v) \
  (v)->data[0]


#define vec_last(v) \
  (v)->data[(v)->length - 1]


#define vec_reserve(v, n) \
  vec_reserve_(vec_unpack_(v), n)

 
#define vec_compact(v) \
  vec_compact_(vec_unpack_(v))


#define vec_pusharr(v, arr, count)                                       \
  do {                                                                   \
    int i__, n__ = (count);                                              \
    if (vec_reserve_po2_(vec_unpack_(v), (v)->length + n__) != 0) break; \
    for (i__ = 0; i__ < n__; i__++) {                                    \
      (v)->data[(v)->length++] = (arr)[i__];                             \
    }\
  } while (0)


#define vec_extend(v, v2) \
  vec_pusharr((v), (v2)->data, (v2)->length)


#define vec_find(v, val, idx)                       \
  do {                                              \
    for ((idx) = 0; (idx) < (v)->length; (idx)++) { \
      if ((v)->data[(idx)] == (val)) break;         \
    }                                               \
    if ((idx) == (v)->length) (idx) = -1;           \
  } while (0)


#define vec_remove(v, val)                    \
  do {                                        \
    int idx__;                                \
    vec_find(v, val, idx__);                  \
    if (idx__ != -1) vec_splice(v, idx__, 1); \
  } while (0)


#define vec_reverse(v)                             \
  do {                                             \
    int i__ = (v)->length / 2;                     \
    while (i__--) {                                \
      vec_swap((v), i__, (v)->length - (i__ + 1)); \
    }                                              \
  } while (0)


#define vec_foreach(v, var, iter)                                 \
  if  ( (v)->length > 0 )                                         \
  for ( (iter) = 0;                                               \
        (iter) < (v)->length && (((var) = (v)->data[(iter)]), 1); \
        ++(iter))


#define vec_foreach_rev(v, var, iter)                    \
  if  ( (v)->length > 0 )                                \
  for ( (iter) = (v)->length - 1;                        \
        (iter) >= 0 && (((var) = (v)->data[(iter)]), 1); \
        --(iter))


#define vec_foreach_ptr(v, var, iter)                              \
  if  ( (v)->length > 0 )                                          \
  for ( (iter) = 0;                                                \
        (iter) < (v)->length && (((var) = &(v)->data[(iter)]), 1); \
        ++(iter))


#define vec_foreach_ptr_rev(v, var, iter)                 \
  if  ( (v)->length > 0 )                                 \
  for ( (iter) = (v)->length - 1;                         \
        (iter) >= 0 && (((var) = &(v)->data[(iter)]), 1); \
        --(iter))

/* Functions <...> <impl> */
#define fn       int
#define fun      int
#define func     int
#define def      int
#define defun    int
#define define   int

#define begin {
#define end   }

/* Classic python-esques <...> <impl> */
#ifndef __cplusplus
#define or  ||
#define and &&
#define not !
#endif

/* Classic lua-esques <...> <impl> */
#define function(...) \
        int __LAZY_FUNCTION__(int __VA_ARGS__)


/* Enum <Elixir::Enum, ~Cpp::std> <impl> */ 
typedef struct {
    char* key;
    int value;
} KeyValue;

typedef struct {
    KeyValue* pairs;
    int size;
    int capacity;
} Map;

Map* makeMap() {
    Map* m = (Map*)malloc(sizeof(Map));
    m->pairs = NULL;
    m->size = 0;
    m->capacity = 0;
    return m;
}

void setKeyValue(Map* m, const char* key, int value) {
    for (int i = 0; i < m->size; i++) {
        if (strcmp(m->pairs[i].key, key) == 0) {
            m->pairs[i].value = value;
            return;
        }
    }
    
    if (m->size == m->capacity) {
        m->capacity = m->capacity == 0 ? 1 : m->capacity * 2;
        m->pairs = (KeyValue*)realloc(m->pairs, m->capacity * sizeof(KeyValue));
    }
    
    m->pairs[m->size].key = strdup(key);
    m->pairs[m->size].value = value;
    m->size++;
}

int getValue(Map* m, const char* key, int* found) {
    for (int i = 0; i < m->size; i++) {
        if (strcmp(m->pairs[i].key, key) == 0) {
            *found = 1;
            return m->pairs[i].value;
        }
    }
    *found = 0;
    return 0;
}

void deleteKeyValue(Map* m, const char* key) {
    for (int i = 0; i < m->size; i++) {
        if (strcmp(m->pairs[i].key, key) == 0) {
            free(m->pairs[i].key);
            for (int j = i; j < m->size - 1; j++) {
                m->pairs[j] = m->pairs[j + 1];
            }
            m->size--;
            return;
        }
    }
}

void clearMap(Map* m) {
    for (int i = 0; i < m->size; i++) {
        free(m->pairs[i].key);
    }
    free(m->pairs);
    m->pairs = NULL;
    m->size = 0;
    m->capacity = 0;
}

void printMap(Map* m) {
    printf("map: {");
    for (int i = 0; i < m->size; i++) {
        printf("%s:%d", m->pairs[i].key, m->pairs[i].value);
        if (i < m->size - 1) {
            printf(" ");
        }
    }
    printf("}\n");
}

typedef struct node {
  int data;
  struct node* next;
} Node;

#define at(start, index)                \
        Node now = start;               \
        for (int i = 0; i < index; i++) \
             now = now->next;           \
        now;

/* Misc-macros <impl> <...> */
#define jmp  goto
#define jump goto

#define nl (uchar)0x0a /* \n */
#define cr (uchar)0x0d /* \r */

/* Minimal flag parser <impl> <...> */
#define flagzone for (int i = 0; i < argc; i++)
#define flagargs int argc, char **argv
#define flag(arr)                               \
        for (int j = 0; j < len(arr); j++)      \
            if (i == arr[j]) if (true)          \

/* Flag parser example:
 *
 *     int main(flagargs) {
 *         flagzone {
 *             flag({"--debug", "-d"}) {
 *                 // ...
 *             }
 *             flag({"--hello"}) {
 *                 // ...
 *             }
 *             flag({"--oi", "--koi", "--moi"}) {
 *                 // ...
 *             }
 *             // ...
 *         }
 *         // ...
 *     }
 */

#endif
