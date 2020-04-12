from  pymakelib.Module import ModuleHandle, GCC_CompilerOpts


def getSrcs(mh: ModuleHandle):
    return ['App/async-op.c']


def getIncs(mh: ModuleHandle):
    return mh.getAllIncsC()


def getCompilerOpts(mh: ModuleHandle):
    opts = GCC_CompilerOpts(mh.getGeneralCompilerOpts())
    opts.setControlCOpts(['-std=c99', '`pkg-config --libs --cflags glib-2.0`'])
    return opts