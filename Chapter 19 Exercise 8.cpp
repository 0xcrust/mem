//8. Implement an allocator (19.3.7) using the basic allocation functions malloc() and free() (B.11.4).
// Get vector as defined by the end of 19.4 to work for a few simple test cases.
// Hint: Look up "placement new" and "explicit call of destructor" in a complete C++ reference.

//p = malloc(s) Allocate s uninitialized bytes on the free store;
//p = 0 if s bytes could not be allocated.

//free(p) Deallocate the memory pointed to by p;
//p must be a pointer returned by malloc(), calloc(), or realloc().


//9. Re - implement vector::operator=() (§19.2.5) using an allocator(§19.3.7)
//for memory management.



template<typename T> class allocator {
    int size;
public:
    // . . .
    allocator() { size = sizeof(T); }
    T* allocate(int n); 
    void deallocate(T* p, int n); 
    void construct(T* p, const T& v); 
    void destroy(T* p); 
};



template<typename T> T* allocator<T>::allocate(int n) // allocate space for n objects of type T
{
    s = size * n;
    p = malloc(s);
    return p;
}


template<typename T> void allocator<T>::deallocate(T* p, int n) // deallocate n objects of type T starting at p
{
    int a = 0;
    while (a < n) { 
        free(p);
        p += size;
        a++;
    }
}


template <typename T> void allocator<T>::construct(T* p, const T& v) //construct a T with the value v in p
{
    void∗ buf = reinterpret_cast<void∗>(*p); 
    p = new(buf) T;
}


template<typename T> void allocator<T>::destroy(T* p) // destroy the T in p 
{
    p->~T();        // explicit call to destroy a T object in p
}


template<typename T> class vector {
    int sz; // number of elements
    T* elem; // address of first element
    int space; // number of elements plus “free space”/“slots” for new elements (“the current allocation”)
    allocator<T> alloc;
public:
    // . .
    vector& operator=(const vector& a);
};


template<typename T> vector<T>& vector<T>::operator=(const vector& a)
{
    if (this == &a) return *this; // self-assignment, no work needed

    if (a.sz <= space) { // enough space, no need for new allocation
        for (int i = 0; i < a.sz; ++i) alloc.construct(elem[i], a.elem[i]);
        sz = a.sz;
        return *this;
    }

    double* p = alloc.allocate(a.sz); // allocate new space
    for (int i = 0; i < a.sz; ++i) alloc.construct(&p[i], a.elem[i]); // copy elements
    for (int i = 0; i < sz; ++i) alloc.destroy(&p[i]);
    alloc.deallocate(elem, space);
    elem = p; // set new elements
    sz = a.sz;
    return *this; // return a self-reference
}



int main()
{


}
