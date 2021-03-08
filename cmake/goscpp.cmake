macro (goscpp_get_properties)
  get_target_property(goscpp_include_directories goscpp
    INTERFACE_INCLUDE_DIRECTORIES)
  get_target_property(goscpp_compile_definitions goscpp
    INTERFACE_COMPILE_DEFINITIONS)
  set(goscpp_target goscpp)
  if (GOS_CPP_EMSCRIPTEN_BUILD)
    get_target_property(goscpp_wasm_library goscpp RESOURCE)
  endif ()
  get_target_property(goscpp_source goscpp SOURCES)
  get_target_property(goscpp_source_dir goscpp SOURCE_DIR)
  list(TRANSFORM goscpp_source PREPEND "${goscpp_source_dir}/")
endmacro (goscpp_get_properties)
