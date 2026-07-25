#include <cstdio>
#include <cstddef> 

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len)
{
    for(size_t i = 0; i < len; i++){
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void show_int(int x)
{
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x)
{
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) 
{
    show_bytes((byte_pointer) &x, sizeof(void *));
}

int main(){
    int64_t x = 5;
    int64_t* p = &x;
    show_int(x);
    show_float(5.0);
    show_pointer(p);
}
