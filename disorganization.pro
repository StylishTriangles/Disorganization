TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/imgui/imgui-SFML.cpp \
    src/imgui/imgui.cpp \
    src/imgui/imgui_demo.cpp \
    src/imgui/imgui_draw.cpp \
    src/Collision.cpp \
    src/Utils.cpp \
    Cat.cpp \
    game.cpp \
    item.cpp \
    Prank.cpp \
    pranks/prankBookThrow.cpp

INCLUDEPATH += C:/SFML/include
INCLUDEPATH += ./include
DEPENDPATH += C:/SFML/include
LIBS += -LC:/SFML/lib
LIBS += -LC:\Qt\Tools\mingw530_32\i686-w64-mingw32\lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system -llibopengl32
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d -llibopengl32

HEADERS += \
    include/imgui/imconfig-SFML.h \
    include/imgui/imconfig.h \
    include/imgui/imgui-SFML.h \
    include/imgui/imgui.h \
    include/imgui/imgui_internal.h \
    include/imgui/stb_rect_pack.h \
    include/imgui/stb_textedit.h \
    include/imgui/stb_truetype.h \
    include/AnimatedSprite.hpp \
    include/Collision.hpp \
    include/Common.hpp \
    include/Utils.hpp \
    cat.hpp \
    game.hpp \
    item.hpp \
    prank.hpp \
    texture_container.hpp \
    items/itemPot.hpp \
    pranks/prankBookThrow.hpp

DISTFILES += \
    imgui.ini
