
#include <stdio.h>

__attribute__((noinline));
void putfunc (int a) {
    asm volatile ("xc.gpr2xcr c0, %0;"
                  :
                  : "r" (a)
                   );
}

__attribute__((noinline));
int getfunc () {
    int tr;
    asm volatile ("xc.xcr2gpr %0, c0;"
                  : "=r" (tr)
                        );
    return tr;
}

int main(int argv, char ** argc) {

    printf("Hello World!\n");

    for(int i =0 ; i < 10; i ++) {
        putfunc(i);

        int x  = getfunc();

        if(x == i) {
            printf("%d - Pass\n", i);
        } else {
            printf("%d - Fail: got %d, expected %d\n", i,x,i);
        }
    }

    return 0;
}
