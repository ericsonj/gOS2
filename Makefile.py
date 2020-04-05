import os
from os.path import basename
from pybuild import git
from pybuild import MKVARS


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
    return {
        'CC':       'gcc',
        'CXX':      'g++',
        'LD':       'gcc',
        'AR':       'ar',
        'AS':       'as',
        'OBJCOPY':  'objcopy',
        'SIZE':     'size',
        'OBJDUMP':  'objdump',
        'INCLUDES': [
            '/usr/lib/gcc/x86_64-linux-gnu/5/include',
            '/usr/local/include',
            "/usr/lib/gcc/x86_64-linux-gnu/5/include-fixed",
            '/usr/include/x86_64-linux-gnu',
            "/usr/include",
            '/var/lib/gems/2.3.0/gems/ceedling-0.29.1/vendor/unity/src/',
            '/usr/include/glib-2.0',
            '/usr/lib/x86_64-linux-gnu/glib-2.0/include',
        ]
    }


LIBRARIES = ['`pkg-config --libs --cflags glib-2.0`']

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
