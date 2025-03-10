FUNCTION( GET_TARGET_CPU )
  IF( CMAKE_CXX_COMPILER MATCHES "aarch64" )
    # 处理arm64交叉编译的情况
    SET( TARGET_CPU aarch64 PARENT_SCOPE )
  ELSEIF( CMAKE_CXX_COMPILER MATCHES "arm-linux" )
    # arm32交叉编译的情况
    SET( TARGET_CPU arm32 PARENT_SCOPE )
  ELSEIF( CMAKE_CXX_COMPILER MATCHES "arm-rockchip830" )
    # arm32交叉编译的情况
    SET( TARGET_CPU arm-rockchip830 PARENT_SCOPE )
  ELSEIF( CMAKE_CXX_COMPILER MATCHES "arm-AX620E" )
    # arm32交叉编译的情况
    SET( TARGET_CPU arm-AX620E PARENT_SCOPE )
  ELSEIF( CMAKE_SYSTEM_PROCESSOR MATCHES "mips" OR CMAKE_CXX_COMPILER MATCHES "mips" )
    # mips编译的时候
    SET( TARGET_CPU mips_loongson PARENT_SCOPE )
  ELSEIF( CMAKE_SYSTEM_PROCESSOR MATCHES "loongarch64" OR CMAKE_CXX_COMPILER MATCHES "loongarch64" )
    # 5000编译的时候
    SET( TARGET_CPU loongarch64 PARENT_SCOPE )
  ELSE()
    SET( TARGET_CPU ${CMAKE_SYSTEM_PROCESSOR} PARENT_SCOPE )
  ENDIF()

  IF(CMAKE_SYSTEM_NAME MATCHES "^Windows" )
    IF(CMAKE_CL_64)
      # 64位
      SET( TARGET_CPU x86_64 PARENT_SCOPE)
    ELSE()
      # 32位
      SET( TARGET_CPU x86 PARENT_SCOPE)
    ENDIF()
  ELSEIF(CMAKE_SYSTEM_NAME MATCHES "^Android" )
    SET( TARGET_CPU ${ANDROID_ABI} PARENT_SCOPE)
  ENDIF()

ENDFUNCTION()

FUNCTION( SET_SUBMODULE_INFO LIB_NAME )
  #MESSAGE( ARGC:${ARGC} )
  #MESSAGE( ARGV:${ARGV} )
  INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_LIST_DIR}/include )

  GET_TARGET_CPU()

  SET( CURRENT_LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/${CMAKE_SYSTEM_NAME}_${TARGET_CPU} )

  IF(EXISTS ${CURRENT_LIB_DIR} )
    LINK_DIRECTORIES( ${CURRENT_LIB_DIR} )
    IF( ${ARGC} EQUAL 1 )
      SET( 3RD_LIBS ${3RD_LIBS};${LIB_NAME} PARENT_SCOPE )
      COPY_SHARED_LIB( ${CURRENT_LIB_DIR} ${LIB_NAME} )
    ELSEIF( ${ARGC} GREATER 1 )
      SET( 3RD_LIBS ${3RD_LIBS};${ARGV} PARENT_SCOPE )
      FOREACH(item IN LISTS my_list)
        COPY_SHARED_LIB( ${CURRENT_LIB_DIR} ${item} )
      ENDFOREACH()
    ENDIF()
  ELSE()
    MESSAGE( FATAL_ERROR "The path of library is not found! Maybe not support.\nPath:" ${CURRENT_LIB_DIR} )
  ENDIF()

ENDFUNCTION()

# 定义一个cmake开关，同时关联一个宏。如果cmake中开关打开，则在C++定义指定的宏
FUNCTION( OPTION_TO_DEFINE opt_name commnet switch macro_name )
  OPTION(${opt_name} ${commnet} ${switch} )
  IF(${opt_name})
    ADD_DEFINITIONS(-D${macro_name})
  ENDIF(${opt_name})
ENDFUNCTION()

#对生成目标做strip
FUNCTION( STRIP_TARGET target_name )
    IF(CMAKE_SYSTEM_NAME MATCHES "^Windows")
    ELSEIF(CMAKE_SYSTEM_NAME MATCHES "^Android")
        # 安卓上用这个命令可以节省近一半编译时间
        SET_TARGET_PROPERTIES( ${target_name} PROPERTIES LINK_FLAGS_RELEASE -s )
    ELSE()
        add_custom_command(TARGET ${target_name} POST_BUILD
            COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${target_name}>
        )
    ENDIF()

ENDFUNCTION()
