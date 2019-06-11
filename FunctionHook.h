// FunctionHook: MIT licensed.

#include <substrate.h>

#define FHConcat_(a, b) a ## b
#define FHConcat(a, b) FHConcat_(a, b)
#define FHConstructor __attribute__((constructor)) static void FHConcat($FHConstructor, __LINE__)()
#define FHDestructor __attribute__((destructor)) static void FHConcat($FHDestructor, __LINE__)()
#define FHInline __attribute__((always_inline)) inline

#define FHOriginal(name) $ ## name ## _original
#define FHReplaced(name) $ ## name ## _replaced
#define FHOriginalPrototype(type, name) static type (*FHOriginal(name))
#define FHReplacedPrototype(type, name) static type FHReplaced(name)
#define FHHook(name) MSHookFunction((void *)MSFindSymbol(NULL, "_" # name), (void *)FHReplaced(name), (void **)&FHOriginal(name))

#define FHFunction(type, name, args...) \
    FHOriginalPrototype(type, name)(args); \
    FHReplacedPrototype(type, name)(args)
