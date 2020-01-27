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