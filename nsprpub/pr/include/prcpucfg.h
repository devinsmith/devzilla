
#ifdef WIN32
#ifndef XP_PC
#define XP_PC
#endif
#else
#ifndef XP_UNIX
#define XP_UNIX
#endif 
#endif /* !WIN32 */
