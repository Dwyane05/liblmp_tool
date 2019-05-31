aux_source_directory(. base_SRCS)

# 生成动态库目标
add_library(lmp_tool SHARED ${base_SRCS})
target_link_libraries(lmp_tool pthread rt)

# 生成静态库目标
add_library(lmp_tool_static STATIC ${base_SRCS})
target_link_libraries(lmp_tool pthread rt)


# 指定静态库的输出名称
set_target_properties(lmp_tool_static PROPERTIES OUTPUT_NAME "lmp_tool")
# 使动态库和静态库同时存在
set_target_properties(lmp_tool PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(lmp_tool_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

# 指定动态库版本
# VERSION 动态库版本
# SOVERSION API版本
set_target_properties(lmp_tool PROPERTIES VERSION 0.0.1 SOVERSION 1)

install(TARGETS lmp_tool DESTINATION lib)
install(TARGETS lmp_tool_static DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include)
