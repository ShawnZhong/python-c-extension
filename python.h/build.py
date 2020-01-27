from setuptools import setup, Extension

setup(ext_modules=[
    Extension('module', sources=["module.c"])
])

