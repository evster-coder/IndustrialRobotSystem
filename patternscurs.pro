QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialogaddrobot.cpp \
    main.cpp \
    mainwindowapp.cpp \
    src/ActivateExecutiveUnit.cpp \
    src/ControlSystem.cpp \
    src/DeactivateExecutiveUnit.cpp \
    src/DecSensorLight.cpp \
    src/DecSensorRadiation.cpp \
    src/DecSensorTemperature.cpp \
    src/DecSensorWet.cpp \
    src/DecoratorSensorUnit.cpp \
    src/Detail.cpp \
    src/EUnitHandCreator.cpp \
    src/EUnitSprayCreator.cpp \
    src/ExecutiveUnitHand.cpp \
    src/ExecutiveUnitSpray.cpp \
    src/FacadeSystem.cpp \
    src/MoveMovingUnit.cpp \
    src/MovingUnit.cpp \
    src/Robot.cpp \
    src/RobotSystem.cpp \
    src/ScanSensorUnit.cpp \
    src/SensorUnit.cpp \
    src/SetPressureSensor.cpp

HEADERS += \
    dialogaddrobot.h \
    mainwindowapp.h \
    src/ActivateExecutiveUnit.h \
    src/ControlSystem.h \
    src/DeactivateExecutiveUnit.h \
    src/DecSensorLight.h \
    src/DecSensorRadiation.h \
    src/DecSensorTemperature.h \
    src/DecSensorWet.h \
    src/DecoratorSensorUnit.h \
    src/Detail.h \
    src/EUnitCreator.h \
    src/EUnitHandCreator.h \
    src/EUnitSprayCreator.h \
    src/ExecutiveUnit.h \
    src/ExecutiveUnitHand.h \
    src/ExecutiveUnitSpray.h \
    src/FacadeSystem.h \
    src/IRobot.h \
    src/ISensorUnit.h \
    src/MoveMovingUnit.h \
    src/MovingUnit.h \
    src/ProgramUnit.h \
    src/Robot.h \
    src/RobotSystem.h \
    src/ScanSensorUnit.h \
    src/SensorUnit.h \
    src/SetPressureSensor.h

FORMS += \
    dialogaddrobot.ui \
    mainwindowapp.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
