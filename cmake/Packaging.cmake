include(GNUInstallDirs)

# ----------------------------
# Make macOS build an .app bundle (only in packaging builds)
# ----------------------------
if(APPLE)
  set_target_properties(app PROPERTIES
    MACOSX_BUNDLE TRUE
  )
endif()

# ----------------------------
# Install the executable/bundle
# ----------------------------
install(TARGETS app
  RUNTIME DESTINATION .   # Windows/Linux: puts app(.exe) in install root
  BUNDLE  DESTINATION .   # macOS: installs Muharrik.app into install root
)

# ----------------------------
# Install content (platform-specific location)
# ----------------------------
if(APPLE)
  # Put assets inside the .app bundle:
  # Muharrik.app/Contents/Resources/content/...
  install(DIRECTORY "${CMAKE_SOURCE_DIR}/src/content/"
    DESTINATION "$<TARGET_BUNDLE_CONTENT_DIR:app>/Resources/content"
  )
else()
  # Put assets next to the executable:
  install(DIRECTORY "${CMAKE_SOURCE_DIR}/src/content/"
    DESTINATION "content"
  )
endif()

# ----------------------------
# Runtime dependencies
# (If you are fully static you may not need this, but it's good insurance.)
# ----------------------------
install(CODE [[
  message(STATUS "Collecting runtime dependencies for app...")

  file(GET_RUNTIME_DEPENDENCIES
    EXECUTABLES "$<TARGET_FILE:app>"
    RESOLVED_DEPENDENCIES_VAR deps
    UNRESOLVED_DEPENDENCIES_VAR udeps
  )

  if(udeps)
    message(WARNING "Unresolved deps: ${udeps}")
  endif()

  foreach(d IN LISTS deps)
    message(STATUS "  dep: ${d}")
  endforeach()

  # Copy deps next to executable (Windows/Linux) or into the .app Frameworks (macOS)
  if(APPLE)
    set(dest "$<TARGET_BUNDLE_CONTENT_DIR:app>/Frameworks")
  else()
    set(dest "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
  endif()

  file(MAKE_DIRECTORY "${dest}")

  foreach(d IN LISTS deps)
    file(INSTALL DESTINATION "${dest}" TYPE SHARED_LIBRARY FOLLOW_SYMLINK_CHAIN FILES "${d}")
  endforeach()
]])

# ----------------------------
# CPack config (choose generators per platform)
# ----------------------------
set(CPACK_PACKAGE_NAME "Muharrik")
set(CPACK_PACKAGE_VERSION "0.1.0")

if(WIN32)
  set(CPACK_GENERATOR "ZIP")            # add "NSIS" later if you want an installer
elseif(APPLE)
  set(CPACK_GENERATOR "ZIP;DragNDrop")  # DragNDrop makes a DMG
  set(CPACK_DMG_VOLUME_NAME "Muharrik")
else()
  set(CPACK_GENERATOR "TGZ")
endif()

# ----------------------------
# Put the final outputs into: <repo>/shippable/
# ----------------------------
set(CPACK_PACKAGE_DIRECTORY "${CMAKE_SOURCE_DIR}/shippable")
set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_SOURCE_DIR}/shippable")
file(MAKE_DIRECTORY "${CPACK_PACKAGE_DIRECTORY}")

include(CPack)
