
float a = 1.0f;
float b = 1.11f;

void __sync_cu();
void func() {
float c = 0;
float d = 1;
if(a > b) {
  if(a - b > 10.0f) {
    c = a + b;
    __sync_cu();
    d = a - b;
  } else {
    c = a - b;
    __sync_cu();
    d = a + b;
  }
}
}
