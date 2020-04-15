from  pymakelib.Module import ModuleHandle, GCC_CompilerOpts


def getSrcs(mh: ModuleHandle):
    return ['App/main.c']


def getIncs(mh: ModuleHandle):
    return mh.getAllIncsC()


def getCompilerOpts(mh: ModuleHandle):
    opts = GCC_CompilerOpts(mh.getGeneralCompilerOpts())
    opts.setControlCOpts(['-std=c99'])
    return opts