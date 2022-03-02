# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(qteb VERSION 1.0.0 LANGUAGES CXX)
# add_custom_target(test)

set(SOURCES
    unistd.h
    appendix.c
    appendix.h
    appsub.c
    bcd.c
    binary.c
    binary.h
    bitmap.c
    book.c
    booklist.c
    booklist.h
    build-post.h
    build-pre.h
    copyright.c
    cross.c
    defs.h
    eb.c
    eb.h
    endword.c
    error.c
    error.h
    exactword.c
    filename.c
    font.c
    font.h
    hook.c
    jacode.c
    keyword.c
    lock.c
    log.c
    match.c
    menu.c
    multi.c
    narwalt.c
    narwfont.c
    readtext.c
    search.c
    setword.c
    stopcode.c
    strcasecmp.c
    subbook.c
    sysdefs.h
    text.c
    text.h
    utf8.c
    widealt.c
    widefont.c
    word.c
    zio.c
    zio.h
    )


if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(SOURCES
        ${SOURCES}
        dirent.h
        dirent.cpp
        )
endif()

add_library(eb
  STATIC
  ${SOURCES}
  )


add_definitions(-DEB_BUILD_LIBRARY)
#target_link_libraries(eb libz)
  # add_dependencies(test eb)

