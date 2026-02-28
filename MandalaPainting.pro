QT += core gui widgets

CONFIG += c++17 warn_on 

QMAKE_CXXFLAGS += -Wall -Wextra -Wpedantic 

SOURCES += \
    main.cpp \
    $$files(model/*.cpp) \
    $$files(view/*.cpp) \
    $$files(controller/*.cpp)
   
HEADERS += \
    $$files(model/*.h) \
    $$files(view/*.h) \
    $$files(controller/*.h)

FORMS += \
    view/MandalaPaiting.ui

ui