from  pybuild.Module import ModuleHandle


def getSrcs(mh: ModuleHandle):
    return mh.getAllSrcsC()


def getIncs(mh: ModuleHandle):
    return mh.getAllIncsC()