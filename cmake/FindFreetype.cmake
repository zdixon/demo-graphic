# Copyright (C) 2007-2009 LuaDist.
# Created by Peter Kapec <kapecp@gmail.com>
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the COPYRIGHT file distributed with LuaDist.
#	Note:
#		Searching headers and libraries is very simple and is NOT as powerful as scripts
#		distributed with CMake, because LuaDist defines directories to search for.
#		Everyone is encouraged to contact the author with improvements. Maybe this file
#		becomes part of CMake distribution sometimes.

# - Find freetype
# Find the native freetype headers and libraries.
#
#  FREETYPE_INCLUDE_DIRS - where to find ft2build.h, etc.
#  FREETYPE_LIBRARIES    - List of libraries when using freetype.
#  FREETYPE_FOUND        - True if freetype found.

set(CMAKE_FIND_FRAMEWORK NEVER)

# Look for the header file.
find_path(FREETYPE_INCLUDE_DIR 
  NAMES ft2build.h
	HINTS 
	ENV CPATH # For OSCAR modules at Brown/CCV
	)

# Look for the library.
find_library(FREETYPE_LIBRARY 
  NAMES glut
	HINTS
	ENV LD_LIBRARY_PATH # For OSCAR modules at Brown/CCV
	)

# Undo the above hack.
set(CMAKE_FIND_FRAMEWORK)

# Handle the QUIETLY and REQUIRED arguments and set FREETYPE_FOUND to
# TRUE if all listed variables are TRUE.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  FREETYPE 
  DEFAULT_MSG 
  FREETYPE_LIBRARY 
  FREETYPE_INCLUDE_DIR)

# Copy the results to the output variables.
if(FREETYPE_FOUND)
  set(FREETYPE_LIBRARY ${FREETYPE_LIBRARY})
  set(FREETYPE_INCLUDE_DIRS ${FREETYPE_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIR}/freetype2)
else(FREETYPE_FOUND)
  set(FREETYPE_LIBRARY)
  set(FREETYPE_INCLUDE_DIR)
endif(FREETYPE_FOUND)

mark_as_advanced(FREETYPE_INCLUDE_DIR FREETYPE_LIBRARIES)
