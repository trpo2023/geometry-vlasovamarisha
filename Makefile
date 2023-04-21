APP_NAME = appgeo                    # переменные
LIB_STATIC = geometry
LIB_DIR = mylibgeometry
CC = gcc
 
CFLAGS = -Wall -Werror
CPPFLAGS = -Isrc -MP -MMD       # -Isrc ключ -I , путь к компиляции src, ищет geometry.h в папке src. ; -MP создает фиктивную цель для каждой зависимости, -MMD создает файлы зависимости
 
BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
 
APP_PATH = $(BIN_DIR)/$(APP_NAME)                  #путь к приложению
LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_DIR)/$(LIB_STATIC).a      #путь к статической библиотеке с расширением .a
 
APP_SOURCES = $(shell find $(SRC_DIR)/$(LIB_STATIC) -name '*.c')          #исходники, где хранятся файлы,
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/$(SRC_DIR)/%.o)        #создание объектных файлов с расширением .o (раскрывается как цель)
LIB_SOURCES = $(shell find $(SRC_DIR)/$(LIB_DIR) -name '*.c')           #ищет библиотеки, файлы с реализацией функций
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/$(SRC_DIR)/%.o)        #преобразует библиотечные файлы с расширением ".c"  в  ".o" (раскрывается как цель)
 
DEPS = $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d)  #создает файлы зависимости с расширением .d
 
.PHONY: all      #позволяет независимо от наличия файла с таким же названием как и данная цель выполнять определенные действия
all: $(APP_PATH)
 
-include $(DEPS) #подключить файлы зависимости, позволяет компилировать измененные зависящие файлы
$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)      # создает приложение с названием
      $(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ -lm        # -lm подключение math.h для использования константы M_PI
 
$(LIB_PATH): $(LIB_OBJECTS)   # переделывает main файл, создает статическую библиотеку с раширением .a
      ar rcs $@ $^           # $^ - берет все что указано в зависимости, $< - берет одно поочередно, $@ - подставляет имя цели, ac rcs - команда для статической библиотеки
 
$(OBJ_DIR)/%.o: %.c   # ищет .с и создает .o
      $(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
 
.PHONY: clean
clean:           # удаляет приложение и файлы с расширениями .o, .d, .a (удаляет артефакты сборки)
      $(RM) $(APP_PATH) $(LIB_PATH)
      find $(OBJ_DIR) -name '*.o' -exec $(RM) '{}' \;
      find $(OBJ_DIR) -name '*.d' -exec $(RM) '{}' \;
