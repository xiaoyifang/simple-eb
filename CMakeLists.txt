# set minimum cmake version
cmake_minimum_required(VERSION 3.22)

# project name and language
project(eb VERSION 1.0.0 LANGUAGES C)

set(SOURCES
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
    eb_utf8.c
    widealt.c
    widefont.c
    word.c
    zio.c
    zio.h
    eb.def
    )


add_library(eb
  SHARED
  ${SOURCES}
  )


find_package(ZLIB REQUIRED)
if(WIN32)
  # <dirent.h> on Windows is provided by the vcpkg dirent port
  # (tronkko/dirent). On POSIX systems it is a libc header and needs no
  # find_package / link.
  find_package(dirent CONFIG REQUIRED)
  target_link_libraries(eb PRIVATE ZLIB::ZLIB dirent::dirent)
else()
  target_link_libraries(eb PRIVATE ZLIB::ZLIB)
endif()

if(WIN32)
  target_link_options(${PROJECT_NAME} PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/FS>)
endif()

include(GNUInstallDirs)
install(TARGETS eb
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
 
    if(WIN32)
    INSTALL (
        DIRECTORY ${CMAKE_SOURCE_DIR}/
        DESTINATION include
        FILES_MATCHING PATTERN "*.h*" 
        PATTERN "CMakeFiles" EXCLUDE)    
    else()
    INSTALL (
      DIRECTORY ${CMAKE_SOURCE_DIR}/
      DESTINATION include
      FILES_MATCHING PATTERN "*.h*"
      PATTERN ".git*" EXCLUDE
      PATTERN "winlibs" EXCLUDE
      PATTERN "CMakeFiles" EXCLUDE
      )  
    endif()