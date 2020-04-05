#!/bin/sh

git clone https://gitlab.com/ericsonj/pymaketool.git pymaketool
cp -r pymaketool/pybuild .
cp pymaketool/testing.py .
cp pymaketool/__init__.py .
cp -Rn pymaketool/Test .
cp -n pymaketool/Makefile .
cp -n pymaketool/makefile.mk .
cp -n pymaketool/Makefile.py .
cp -n pymaketool/.cproject .
cp -n pymaketool/.cproject_template .
cp -n pymaketool/.project .
rm -rf pymaketool