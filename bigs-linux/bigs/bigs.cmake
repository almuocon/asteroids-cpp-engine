# Este fichero es para su inclusión desde proyectos externos
#
# En CMakeLists.txt del nuevo proyecto se debe poner:
#  include(<path>/bigs.cmake)
#  indicando la ruta completa (relativa o absoluta) al directorio en donde está BiGS

# Obtener PATH absoluto 
get_filename_component(BIGS_DIR_ABS ${CMAKE_CURRENT_LIST_DIR} ABSOLUTE)

set(BIGS_LIB ${BIGS_DIR_ABS}/lib)
set(BIGS_IMPLIB ${BIGS_DIR_ABS}/lib/libbigs.a)
set(BIGS_INC ${BIGS_DIR_ABS}/include)
set(BIGS_LOCATION ${BIGS_DIR_ABS}/lib/libbigs.a)

# Localizar biblioteca Allegro
find_package(Allegro)
include(${Allegro_DIR}/AllegroTargets.cmake)
#set(LIBALLEGRO Allegro::allegro Allegro::allegro_main Allegro::allegro_primitives Allegro::allegro_ttf Allegro::allegro_image)
set(LIBALLEGRO Allegro::allegro Allegro::allegro_main Allegro::allegro_primitives Allegro::allegro_image Allegro::allegro_ttf Allegro::allegro_audio  Allegro::allegro_acodec)

# Añadir biblioteca BiGS
add_library(bigs STATIC IMPORTED)

set_target_properties(bigs PROPERTIES 
    IMPORTED_IMPLIB "${BIGS_IMPLIB}"
    INTERFACE_INCLUDE_DIRECTORIES "${BIGS_INC}"
    IMPORTED_LOCATION "${BIGS_LOCATION}"
)

include_directories(${BIGS_INC})
link_directories(${BIGS_LIB})

# Añadir dependencia para que al incluir BiGS se incluya también Allegro
target_link_libraries(bigs INTERFACE ${LIBALLEGRO})
