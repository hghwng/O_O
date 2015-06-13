#include "stdio.h"
#define plus +
#define shift <<
#define br_l (
#define br_r )
#define If if
#define Int int
#define Char char
#define Return return
#define one 1
#define two br_l one shift one br_r
#define four br_l two shift one br_r
#define cond_print(cond, val, go) If br_l cond == argc br_r fputc br_l val, stdout br_r , main br_l go , 0 br_r ;
#define stub Int main br_l Int argc, Char **argv br_r {
#define ret If (argc == -1) Return 0; }

stub
cond_print(one, 'a' plus two, -1)
ret
