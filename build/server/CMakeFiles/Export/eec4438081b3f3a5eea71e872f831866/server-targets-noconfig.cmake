#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "server::server_lib" for configuration ""
set_property(TARGET server::server_lib APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(server::server_lib PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libserver_lib.a"
  )

list(APPEND _cmake_import_check_targets server::server_lib )
list(APPEND _cmake_import_check_files_for_server::server_lib "${_IMPORT_PREFIX}/lib/libserver_lib.a" )

# Import target "server::TCPChatServer" for configuration ""
set_property(TARGET server::TCPChatServer APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(server::TCPChatServer PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/Applications/TCPChatServer.app/Contents/MacOS/TCPChatServer"
  )

list(APPEND _cmake_import_check_targets server::TCPChatServer )
list(APPEND _cmake_import_check_files_for_server::TCPChatServer "${_IMPORT_PREFIX}/Applications/TCPChatServer.app/Contents/MacOS/TCPChatServer" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
