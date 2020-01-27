from setuptools import setup, Extension

setup(ext_modules=[
    Extension('_module', sources=["module_wrap.c"])
])