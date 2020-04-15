import os
import subprocess
from os.path import basename
from pymakelib import git
from pymakelib import MKVARS


def getProjectSettings():
    return {
        'PROJECT_NAME': basename(os.getcwd()),
        'FOLDER_OUT':   'Release/Objects/'
    }


def getTargetsScript():
    PROJECT_NAME = basename(os.getcwd())
    FOLDER_OUT = 'Release/'
    TARGET = FOLDER_OUT + PROJECT_NAME + '.bin'

    TARGETS = {
        'TARGET': {
            'LOGKEY':  'OUT',
            'FILE':    TARGET,
            'SCRIPT':  [MKVARS.LD, '-o', '$@', MKVARS.OBJECTS, MKVARS.LDFLAGS]
        },
        'TARGET_ZIP': {
            'LOGKEY':   'ZIP',
            'FILE':     TARGET + '.zip',
            'SCRIPT':   ['zip', TARGET + '.zip', MKVARS.TARGET]
        }
    }

    return TARGETS


def getCompilerSet():
    GCC_INCLUDES = []
    CEEDLING_INCLUDES = []
    try:
        res =  subprocess.check_output(["bash", "-c", "echo | gcc -Wp,-v -x c++ - -fsyntax-only &> /tmp/gccincs.tmp ; cat /tmp/gccincs.tmp |  grep '^[ ]*/usr.*'"])
        for line in res.splitlines():
            GCC_INCLUDES.append(line.decode('utf-8').strip())

        res = subprocess.check_output(['bash', '-c', "find /var/lib/gems $HOME/.gem/ -name 'unity.h' 2>&1 | grep '.*ceedling-[0-9\\.\\-]*/vendor/unity/src'"])
        for line in res.splitlines():
            CEEDLING_INCLUDES.append(os.path.dirname(line.decode('utf-8').strip()))

    except Exception as e:
        print(e)

    GLIB_INCLUDES = ['/usr/include/gstreamer-1.0', '/usr/include/glib-2.0', '/usr/lib/x86_64-linux-gnu/glib-2.0/include']

    return {
        'CC':       'gcc',
        'CXX':      'g++',
        'LD':       'gcc',
        'AR':       'ar',
        'AS':       'as',
        'OBJCOPY':  'objcopy',
        'SIZE':     'size',
        'OBJDUMP':  'objdump',
        'INCLUDES': GCC_INCLUDES + CEEDLING_INCLUDES + GLIB_INCLUDES

    }


LIBRARIES = [
    '`pkg-config --libs glib-2.0`',
    '`pkg-config --libs --cflags gio-2.0`',
    '`pkg-config --libs --cflags gstreamer-1.0`',
]

def getCompilerOpts():

    PROJECT_DEF = {
        '_DEFAULT_SOURCE': None
    }

    return {
        'MACROS': PROJECT_DEF,
        'MACHINE-OPTS': [
        ],
        'OPTIMIZE-OPTS': [
        ],
        'OPTIONS': [
        ],
        'DEBUGGING-OPTS': [
            '-g3'
        ],
        'PREPROCESSOR-OPTS': [
            '-MP',
            '-MMD'
        ],
        'WARNINGS-OPTS': [
        ],
        'CONTROL-C-OPTS': [
            '-std=c99'
        ],
        'GENERAL-OPTS': [
        ],
        'LIBRARIES': LIBRARIES
    }


def getLinkerOpts():
    return {
        'LINKER-SCRIPT': [
        ],
        'MACHINE-OPTS': [
        ],
        'GENERAL-OPTS': [
        ],
        'LINKER-OPTS': [
        ],
        'LIBRARIES': LIBRARIES
    }
