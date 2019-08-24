CONFIG += qt debug
SOURCES += main.cpp

!exists( main.cpp ) {
    error( "No main.cpp file found" )
}
