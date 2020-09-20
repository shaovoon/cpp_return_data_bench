# Benchmark of Retrieve Data By Reference Parameter or Returning a Reference

In C++, there are two options to retrieve data from a object: either passing a reference parameter to be filled up or returning a reference. The former is making a copy of data while the latter is returning a memory address of the data.

```Cpp
void PassByReference(std::vector<int>& vec)
{
    vec = m_vec; // make a copy
}
std::vector<int>& ReturnReference()
{
    return m_vec; // return memory address
}
```

Since reference in C++ is a syntactic sugar for pointer, the pointer equivalent of the 2 above functions are presented below. By right, they should have the same performance characteristic.

```Cpp
void PassByPointer(std::vector<int>* vec)
{
    *vec = m_vec; // make a copy
}
std::vector<int>* ReturnPointer()
{
    return &m_vec; // return memory address
}
```

###Benchmark Code

The code used for benchmark is below.

```Cpp
const int MAX_LOOP = 100000;
timer stopwatch;

{
    stopwatch.start("PassByReference");
    Foo foo;
    std::vector<int> vec;
    for (int i = 0; i < MAX_LOOP; ++i)
    {
        foo.Add(i);
        foo.PassByReference(vec);
    }
    stopwatch.stop();
}
{
    stopwatch.start("ReturnReference");
    Foo foo;
    std::vector<int>* p = nullptr;
    for (int i = 0; i < MAX_LOOP; ++i)
    {
        foo.Add(i);
        p = &foo.ReturnReference();
    }
    stopwatch.stop();
}
{
    stopwatch.start("PassByPointer");
    Foo foo;
    std::vector<int> vec;
    for (int i = 0; i < MAX_LOOP; ++i)
    {
        foo.Add(i);
        foo.PassByPointer(&vec);
    }
    stopwatch.stop();
}
{
    stopwatch.start("ReturnPointer");
    Foo foo;
    std::vector<int>* p;
    for (int i = 0; i < MAX_LOOP; ++i)
    {
        foo.Add(i);
        p = foo.ReturnPointer();
    }
    stopwatch.stop();
}
```

###Benchmark Result

The benchmark result for different C++ compilers are presented below.

__Visual C++ 2019 16.7 Update on Windows 10 20.04 Update__

```
     PassByReference timing:  565ms
     ReturnReference timing:    0ms
       PassByPointer timing:  572ms
       ReturnPointer timing:    0ms
```

__G++ 9.3.0 Ubuntu 20.04 WSL2__

G++ build command is as follows.

```
g++ -std=c++11 -O3 TestReference.cpp
```

```
     PassByReference timing: 8945ms
     ReturnReference timing:    0ms
       PassByPointer timing:  598ms
       ReturnPointer timing:    1ms
```

__Clang++ 10.0.0 Ubuntu 20.04 WSL2__

Clang++ build command is as follows.

```
clang++ -std=c++11 -O3 TestReference.cpp
```

```
     PassByReference timing: 8824ms
     ReturnReference timing:    0ms
       PassByPointer timing:  617ms
       ReturnPointer timing:    0ms
```


