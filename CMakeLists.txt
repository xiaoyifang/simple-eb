# set minimum cmake version
cmake_minimum_required(VERSION 3.22)

# project name and language
project(eb VERSION 1.0.0 LANGUAGES C)

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
    eb.def
    )


if(WIN32)
  add_definitions(-DDOS_FILE_PATH)
  add_definitions(-DHAVE__GETDCWD)
  set(SOURCES
      ${SOURCES}
      dirent.h
      )
endif()

add_library(eb
  STATIC
  ${SOURCES}
  )

add_definitions(-DEB_BUILD_LIBRARY)

add_definitions(-DHAVE_DIRECT_H)

if(UNIX)
    find_package(ZLIB REQUIRED)
    target_link_libraries(eb ZLIB::ZLIB)
endif()

if(WIN32)
  find_package(ZLIB REQUIRED)
  target_link_libraries(eb PRIVATE ZLIB::ZLIB)
endif()
include(GNUInstallDirs)
install(TARGETS eb
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
    
INSTALL (
    DIRECTORY ${CMAKE_SOURCE_DIR}/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*")    
