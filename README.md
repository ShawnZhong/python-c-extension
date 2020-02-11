# Subprocess
Simply call an executable and get the output from stdout. 
It might sounds pretty broutforce, but it should handle workloads like formatting csv lines pretty well. 

```py
>>> import subprocess
>>>
>>> date = "2017-05-10 13:40:01"
>>> in_format = "%Y-%m-%d %H:%M:%S"
>>> out_format = "%d %B of %Y at %H:%M and %S seconds"
>>> 
>>> subprocess.check_output(["date", "-jf", in_format, date, "+" + out_format])
b'10 May of 2017 at 13:40 and 01 seconds\n'
```

# Python.h
[`<Python.h>`](https://docs.python.org/3/extending/extending.html) is the official way to extend Python with C/C++, but it requires some amount of wrapper code to interactive with Python.

Here is an example of calling the `add` function in C from Python

**module.c**
```c
#include <Python.h>

int add(int a) { return a + 1; }

static PyObject *_add(PyObject *self, PyObject *args) {
  int _a;
  int res;
  if (!PyArg_ParseTuple(args, "i", &_a)) return NULL;
  res = add(_a);
  return PyLong_FromLong(res);
}

static PyMethodDef ModuleMethods[] = {{"add", _add, METH_VARARGS, ""},
                                      {NULL, NULL, 0, NULL}};

static struct PyModuleDef module = {PyModuleDef_HEAD_INIT, "module", NULL, -1,
                                    ModuleMethods};

PyMODINIT_FUNC PyInit_module(void) { return PyModule_Create(&module); }
```

**build.py** 
```python
from setuptools import setup, Extension

setup(ext_modules=[
    Extension('module', sources=["module.c"])
])
```

**main.py**
```python
import module

print(module.add(1))
```

**Comile & Run**
```sh
> python build.py build_ext --inplace
running build_ext
copying build/lib.macosx-10.7-x86_64-3.7/module.cpython-37m-darwin.so -> 
> python python main.py                     
2
```

# Swig

[Swig](http://www.swig.org/Doc1.3/Python.html) is a C/C++ wrapper for various languages including Python. It allows us to write less template code compared to using pure `Python.h`

**module.i**
```c
%module module
%{
int add(int a) { return a + 1; }
%}
int add(int a);
```

**build.py** 
```python
from setuptools import setup, Extension

setup(ext_modules=[
    Extension('_module', sources=["module_wrap.c"])
])
```

**main.py**
```py
import module

print(module.add(1))
```

**Compile & Run**
```sh
> swig -python module.i
> python build.py build_ext --inplace
running build_ext
building '_module' extension
creating build
creating build/temp.macosx-10.7-x86_64-3.7
gcc -Wno-unused-result -Wsign-compare -Wunreachable-code -DNDEBUG -g -fwrapv -O3 -Wall -Wstrict-prototypes -I/Users/Shawn/SDKs/anaconda3/include -arch x86_64 -I/Users/Shawn/SDKs/anaconda3/include -arch x86_64 -I/Users/Shawn/SDKs/anaconda3/include/python3.7m -c module_wrap.c -o build/temp.macosx-10.7-x86_64-3.7/module_wrap.o
creating build/lib.macosx-10.7-x86_64-3.7
gcc -bundle -undefined dynamic_lookup -L/Users/Shawn/SDKs/anaconda3/lib -arch x86_64 -L/Users/Shawn/SDKs/anaconda3/lib -arch x86_64 -arch x86_64 build/temp.macosx-10.7-x86_64-3.7/module_wrap.o -o build/lib.macosx-10.7-x86_64-3.7/_module.cpython-37m-darwin.so
copying build/lib.macosx-10.7-x86_64-3.7/_module.cpython-37m-darwin.so -> 
> swig python main.py
2
```
