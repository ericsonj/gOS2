from pymakelib import module
from pymakelib import project

@module.ModuleClass
class GOS(module.AbstractModule):

    def getSrcs(self):
        return self.getAllSrcsC()
    
    
    def getIncs(self):
        return self.path
    
    
    def getCompilerOpts(self):
        gos_opts = module.GCC_CompilerOpts(project.getCompilerOpts())
        gos_opts.setControlCOpts(['-std=c99', 
                              '`pkg-config --libs --cflags glib-2.0`', 
                              '`pkg-config --libs --cflags gstreamer-1.0`'])
        return gos_opts.opts