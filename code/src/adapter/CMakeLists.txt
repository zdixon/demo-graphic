project(adapter)

include_directories(
      ${GLM_INCLUDE_DIR}
      ${MYSQL_INCLUDE_DIR}
      ${MYSQL_INCLUDE_CPPCONN_DIR}
      ${MYSQL_LIBRARY}
  )

set(adapter_headers DataAdapter.h) 
set(adapter_sources DataAdapter.cpp)
set(adapter_files ${adapter_headers} ${adapter_sources})

add_library(adapter ${adapter_files})

install(TARGETS adapter
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
	ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(FILES ${adapter_headers}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

