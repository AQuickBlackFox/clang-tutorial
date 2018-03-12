__declspec(property(get = __fetch_builtin_x)) unsigned int x;
static inline __attribute__((always_inline))
    __attribute__((device)) unsigned int __fetch_builtin_x(int x) {
        return __builtin_abs(x);
    }