macro (goscpp_get_properties)
  get_target_property(goscpp_include_directories gosc
    INTERFACE_INCLUDE_DIRECTORIES)
  get_target_property(goscpp_compile_definitions gosc
    INTERFACE_COMPILE_DEFINITIONS)
  set(goscpp_target gosc)
  if (GOS_CPP_EMSCRIPTEN_BUILD)
    get_target_property(goscpp_wasm_library gosc RESOURCE)
  endif ()
  get_target_property(goscpp_source gosc SOURCES)
  get_target_property(goscpp_source_dir gosc SOURCE_DIR)
  list(TRANSFORM goscpp_source PREPEND "${goscpp_source_dir}/")
endmacro (goscpp_get_properties)
