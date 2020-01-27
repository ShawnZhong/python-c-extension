build:
	swig -python module.i
	python build.py build_ext --inplace

run:
	python main.py

clean:
	rm -rf build
	rm -rf __pycache__
	rm -f module.py
	rm -f module_wrap.c
	rm -f _module.*.so