from pymakelib.Module import ModuleHandle, GCC_CompilerOpts


def getSrcs(mh: ModuleHandle):
    return mh.getAllSrcsC()


def getIncs(mh: ModuleHandle):
    return mh.modDir


def getCompilerOpts(mh: ModuleHandle):
    opts = GCC_CompilerOpts(mh.getGeneralCompilerOpts())
    opts.setControlCOpts(['-std=c99', 
                          '`pkg-config --libs --cflags glib-2.0`', 
                          '`pkg-config --libs --cflags gstreamer-1.0`'])
    return opts