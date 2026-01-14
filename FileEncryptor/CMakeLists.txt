# CMakeList.txt: CMake-Projekt für "FileEncryptor". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (FileEncryptor "Main.cpp" "Main.h" "Encryptor/Encryptor.h" "Encryptor/Encryptor.cpp")

find_package(unofficial-sodium CONFIG REQUIRED)
target_link_libraries(FileEncryptor PRIVATE unofficial-sodium::sodium)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FileEncryptor PROPERTY CXX_STANDARD 20)
endif()

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
