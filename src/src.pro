TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt \
 exceptions \
 opengl
TARGET = ../bin/pzsculpt

QT += opengl

SOURCES += brush.cpp \
camera.cpp \
catmullclarksubd.cpp \
command.cpp \
commandstack.cpp \
cordinate.cpp \
drawcommand.cpp \
drawcommandelem.cpp \
edge.cpp \
face.cpp \
glwidget.cpp \
main.cpp \
mainwindow.cpp \
mesh.cpp \
meshexporter.cpp \
meshimporter.cpp \
multimesh.cpp \
objmeshexporter.cpp \
objmeshimporter.cpp \
position.cpp \
subdivider.cpp \
vertexdrawer.cpp \
vertexdrawerelem.cpp \
vertexpincher.cpp \
vertexpusher.cpp \
vertexsmoother.cpp
HEADERS += brush.h \
camera.h \
catmullclarksubd.h \
command.h \
commandstack.h \
config.h \
cordinate.h \
drawable.h \
drawcommandelem.h \
drawcommand.h \
edge.h \
face.h \
glwidget.h \
mainwindow.h \
meshexporter.h \
mesh.h \
meshimporter.h \
multimesh.h \
objmeshexporter.h \
objmeshimporter.h \
position.h \
subdivider.h \
vector3.h \
vertexdrawerelem.h \
vertexdrawer.h \
vertexpincher.h \
vertexpusher.h \
vertexsmoother.h
FORMS += mainwindow.ui

RESOURCES += images.qrc

