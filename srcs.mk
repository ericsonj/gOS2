####################################################
#                  gOS2/gos_mk.py                  #
####################################################
CSRC += gOS2/g_cmsis_os.c
CSRC += gOS2/g_freertos.c

INCS += -IgOS2

Release/Objects/gOS2/g_cmsis_os.o : CFLAGS = -D_DEFAULT_SOURCE    -g3  -MP -MMD   -std=c99 `pkg-config --libs --cflags glib-2.0`   `pkg-config --libs glib-2.0` `pkg-config --libs --cflags gio-2.0` 
Release/Objects/gOS2/g_freertos.o : CFLAGS = -D_DEFAULT_SOURCE    -g3  -MP -MMD   -std=c99 `pkg-config --libs --cflags glib-2.0`   `pkg-config --libs glib-2.0` `pkg-config --libs --cflags gio-2.0` 

####################################################
#                  App/App_mk.py                   #
####################################################
CSRC += App/main.c


Release/Objects/App/main.o : CFLAGS = -D_DEFAULT_SOURCE    -g3  -MP -MMD   -std=c99 `pkg-config --libs --cflags glib-2.0`   `pkg-config --libs glib-2.0` `pkg-config --libs --cflags gio-2.0` 

