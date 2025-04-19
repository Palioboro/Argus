vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO lucocozz/cargs
    REF v${VERSION}
    SHA512 981361ffe0f5d9848134f0f515210ff1533d4adc3e974e07ea6ad1eb0e22839318eadf23a13f8ecf6906b696548733a4e5375bc4c4af5790bad02163acbf1f4b
    HEAD_REF main
)

vcpkg_find_acquire_program(MESON)
message(STATUS "Using Meson: ${MESON}")

vcpkg_check_features(OUT_FEATURE_OPTIONS FEATURE_OPTIONS
    FEATURES
    regex WITH_REGEX
)

set(OPTIONS -Dtests=false -Dexamples=false -Dbenchmarks=false)
if(NOT "regex" IN_LIST FEATURES)
    list(APPEND OPTIONS -Ddisable_regex=true)
endif()

vcpkg_configure_meson(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS ${OPTIONS}
)

vcpkg_install_meson()
vcpkg_fixup_pkgconfig()

file(INSTALL "${SOURCE_PATH}/LICENSE" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}" RENAME copyright)
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/share")
