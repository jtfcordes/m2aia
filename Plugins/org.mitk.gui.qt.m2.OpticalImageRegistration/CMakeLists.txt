project(org_mitk_gui_qt_m2_OpticalImageRegistration)

mitk_create_plugin(
  EXPORT_DIRECTIVE M2OPTICALIMAGEREGISTRATION_EXPORT
  EXPORTED_INCLUDE_SUFFIXES src
  MODULE_DEPENDS MitkQtWidgetsExt M2aiaCore
)
