PROJECT(randomwordlistgenerator)

cmake_minimum_required(VERSION 2.4)
  
SET(GUI "randomwordlistgenerator")  

ADD_DEFINITIONS( ${OPTIMIZATION_FLAGS} )
  
SET(randomwordlistgenerator_UIS  
    ui/mainwindow.ui
    ui/dialoginfo.ui
)  
  
SET(randomwordlistgenerator_SRCS  
    src/main.cpp
    src/mainwindow.cpp
    src/wordgenerator.cpp
    src/randomize.cpp
    src/dialoginfo.cpp
)  
  
SET(randomwordlistgenerator_MOC_HDRS  
    src/mainwindow.h
    src/wordgenerator.h
    src/randomize.h
    src/dialoginfo.h
)
  
SET(randomwordlistgenerator_RESOURCES  
    res.qrc
)


FIND_PACKAGE(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
QT5_WRAP_UI(randomwordlistgenerator_UIS_H ${randomwordlistgenerator_UIS})  
QT5_ADD_RESOURCES(randomwordlistgenerator_RESOURCES ${randomwordlistgenerator_RESOURCES})

ADD_DEFINITIONS(
	-Wall
	-W
	${QT_DEFINITIONS}
)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
  
ADD_EXECUTABLE(${GUI}  
    ${randomwordlistgenerator_SRCS}  
    ${randomwordlistgenerator_UIS_H}  
    ${randomwordlistgenerator_MOC_SRCS}  
    ${randomwordlistgenerator_RESOURCES}  
    ${randomwordlistgenerator_RCS} 
)  
  
TARGET_LINK_LIBRARIES(${GUI} ${QT_LIBRARIES} ${ImageMagick_LIBRARIES} ${ImageMagick_Magick++_LIBRARIES})

qt5_use_modules(${GUI} Widgets Gui)

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/randomwordlistgenerator DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(FILES res/randomwordlistgenerator.desktop DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications)
install(FILES res/randomwordlistgenerator.png DESTINATION ${CMAKE_INSTALL_PREFIX}/share/pixmaps)
