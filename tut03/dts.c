int A[10];

void __attribute__((annotate("my annotation"))) func(){
    A[10] = A[9] + 1;
}
