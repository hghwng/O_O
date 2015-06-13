#include "stdio.h"
#define plus +
#define shift <<
#define br_l (
#define br_r )
#define one 1
#define two br_l one shift one br_r
#define four br_l two shift one br_r
#define print(x) fputc(x, stdout)
#define cond_print(cond, val, go) if (cond == argc) print(val), main(go, 0);
#define stub int main(int argc, char **argv) {
#define ret if (argc == -1) return 0; }

stub
cond_print(one, 'a' plus two, -1)
ret
