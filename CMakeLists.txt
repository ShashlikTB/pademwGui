project(pademiddleWare)
cmake_minimum_required(VERSION 2.6)

FIND_PACKAGE(Qt4)
INCLUDE(${QT_USE_FILE})


set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -m64 -Wall ${ROOTCFLAGS} -DQT_NO_KEYWORDS")
execute_process(COMMAND root-config --cflags OUTPUT_VARIABLE ROOTCFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND root-config --libdir OUTPUT_VARIABLE ROOTLDIR OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND root-config --libs OUTPUT_VARIABLE ROOTLIBS OUTPUT_STRIP_TRAILING_WHITESPACE)
include_directories(${include_directories} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} "${PROJECT_SOURCE_DIR}/include" )
link_directories(${ROOTLDIR} )
add_definitions(-std=c++0x -ggdb)

set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -m64 -Wall ${ROOTCFLAGS} -DQT_NO_KEYWORDS")

QT4_WRAP_UI(UISrcs src/form.ui)
QT4_WRAP_CPP(MOCSrcs include/form.h)

set(uitestsources
	src/uitest.cpp
	src/form.cpp)



add_executable(uitest ${uitestsources} ${MOCSrcs} ${UISrcs} )
target_link_libraries(uitest ${QT_LIBRARIES})
target_link_libraries(uitest pthread)
target_link_libraries(uitest event)
target_link_libraries(uitest boost_system)
target_link_libraries(uitest boost_thread)			   
target_link_libraries(uitest boost_regex)			   
target_link_libraries(uitest ${ROOTLIBS})
target_link_libraries(uitest ${TB_LIBRARY})
