<<<<<<< HEAD
# Install script for directory: C:/Users/maria/OneDrive/Documentos/GitHub/Paper-Please
=======
# Install script for directory: C:/Users/thiag/OneDrive/Escritorio/REPOSITORIO 3/Paper-Please
>>>>>>> main

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/PaperPlease")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/Users/maria/OneDrive/Desktop/Nuevacarpeta/Tools/mingw1120_64/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
<<<<<<< HEAD
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/maria/OneDrive/Documentos/GitHub/Paper-Please/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/PaperPlease.exe")
=======
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/thiag/OneDrive/Escritorio/REPOSITORIO 3/Paper-Please/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/PaperPlease.exe")
>>>>>>> main
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/PaperPlease.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/PaperPlease.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/Users/maria/OneDrive/Desktop/Nuevacarpeta/Tools/mingw1120_64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/PaperPlease.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
<<<<<<< HEAD
file(WRITE "C:/Users/maria/OneDrive/Documentos/GitHub/Paper-Please/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/${CMAKE_INSTALL_MANIFEST}"
=======
file(WRITE "C:/Users/thiag/OneDrive/Escritorio/REPOSITORIO 3/Paper-Please/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/${CMAKE_INSTALL_MANIFEST}"
>>>>>>> main
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
