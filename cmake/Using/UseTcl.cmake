MACRO(USE_TCL)
  FIND_PACKAGE(TCL)
  IF ((NOT TCL_FOUND) AND (${ARGC} LESS 1))
    USING_MESSAGE("Skipping because of missing TCL")
    RETURN()
  ENDIF((NOT TCL_FOUND) AND (${ARGC} LESS 1))
  IF(NOT TCL_USED AND TCL_FOUND)
    SET(TCL_USED TRUE)
    INCLUDE_DIRECTORIES(SYSTEM ${TCL_INCLUDE_PATH})
    SET(EXTRA_LIBS ${EXTRA_LIBS} ${TCL_LIBRARIES})
  ENDIF()
ENDMACRO(USE_TCL)

