#############################################################################
# Makefile for building: chess2
# Generated by qmake (3.1) (Qt 5.9.0)
# Project:  Thegianshoulder.pro
# Template: app
# Command: G:\QQT5.9\5.9\mingw53_32\bin\qmake.exe -o Makefile Thegianshoulder.pro -spec win32-g++ "CONFIG+=qml_debug" "CONFIG+=force_debug_info" "CONFIG+=separate_debug_info"
#############################################################################

MAKEFILE      = Makefile

first: release
install: release-install
uninstall: release-uninstall
QMAKE         = G:\QQT5.9\5.9\mingw53_32\bin\qmake.exe
DEL_FILE      = del
CHK_DIR_EXISTS= if not exist
MKDIR         = mkdir
COPY          = copy /y
COPY_FILE     = copy /y
COPY_DIR      = xcopy /s /q /y /i
INSTALL_FILE  = copy /y
INSTALL_PROGRAM = copy /y
INSTALL_DIR   = xcopy /s /q /y /i
QINSTALL_FILE = G:\QQT5.9\5.9\mingw53_32\bin\qmake.exe -install qinstall file
QINSTALL_PROGRAM = G:\QQT5.9\5.9\mingw53_32\bin\qmake.exe -install qinstall program
QINSTALL_DIR  = G:\QQT5.9\5.9\mingw53_32\bin\qmake.exe -install qinstall directory
DEL_FILE      = del
SYMLINK       = $(QMAKE) -install ln -f -s
DEL_DIR       = rmdir
MOVE          = move
SUBTARGETS    =  \
		release \
		debug


release: FORCE
	$(MAKE) -f $(MAKEFILE).Release
release-make_first: FORCE
	$(MAKE) -f $(MAKEFILE).Release 
release-all: FORCE
	$(MAKE) -f $(MAKEFILE).Release all
release-clean: FORCE
	$(MAKE) -f $(MAKEFILE).Release clean
release-distclean: FORCE
	$(MAKE) -f $(MAKEFILE).Release distclean
release-install: FORCE
	$(MAKE) -f $(MAKEFILE).Release install
release-uninstall: FORCE
	$(MAKE) -f $(MAKEFILE).Release uninstall
debug: FORCE
	$(MAKE) -f $(MAKEFILE).Debug
debug-make_first: FORCE
	$(MAKE) -f $(MAKEFILE).Debug 
debug-all: FORCE
	$(MAKE) -f $(MAKEFILE).Debug all
debug-clean: FORCE
	$(MAKE) -f $(MAKEFILE).Debug clean
debug-distclean: FORCE
	$(MAKE) -f $(MAKEFILE).Debug distclean
debug-install: FORCE
	$(MAKE) -f $(MAKEFILE).Debug install
debug-uninstall: FORCE
	$(MAKE) -f $(MAKEFILE).Debug uninstall

Makefile: Thegianshoulder.pro ../../QQT5.9/5.9/mingw53_32/mkspecs/win32-g++/qmake.conf ../../QQT5.9/5.9/mingw53_32/mkspecs/features/spec_pre.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/qdevice.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/device_config.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/common/g++-base.conf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/common/angle.conf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/common/sanitize.conf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/common/gcc-base.conf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/qconfig.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3danimation.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3danimation_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dcore.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dcore_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dextras.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dextras_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dinput.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dinput_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dlogic.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dlogic_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquick.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquick_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquickanimation.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquickanimation_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquickextras.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquickextras_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquickinput.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquickinput_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquickrender.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquickrender_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquickscene2d.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquickscene2d_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3drender.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3drender_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_accessibility_support_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_axbase.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_axbase_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_axcontainer.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_axcontainer_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_axserver.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_axserver_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_bluetooth.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_bluetooth_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_bootstrap_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_charts.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_charts_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_concurrent.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_concurrent_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_core.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_core_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_datavisualization.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_datavisualization_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_dbus.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_dbus_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_designer.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_designer_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_designercomponents_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_devicediscovery_support_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_egl_support_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_fb_support_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_fontdatabase_support_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_gamepad.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_gamepad_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_gui.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_gui_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_help.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_help_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_location.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_location_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_multimedia.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_multimedia_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_multimediawidgets.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_multimediawidgets_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_network.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_network_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_networkauth.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_networkauth_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_nfc.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_nfc_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_opengl.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_opengl_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_openglextensions.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_openglextensions_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_packetprotocol_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_platformcompositor_support_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_positioning.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_positioning_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_printsupport.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_printsupport_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_purchasing.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_purchasing_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_qml.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_qml_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_qmldebug_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_qmldevtools_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_qmltest.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_qmltest_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_quick.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_quick_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_quickcontrols2.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_quickcontrols2_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_quickparticles_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_quicktemplates2_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_quickwidgets.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_quickwidgets_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_remoteobjects.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_remoteobjects_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_repparser.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_repparser_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_script.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_script_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_scripttools.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_scripttools_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_scxml.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_scxml_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_sensors.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_sensors_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_serialbus.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_serialbus_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_serialport.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_serialport_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_sql.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_sql_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_svg.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_svg_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_testlib.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_testlib_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_texttospeech.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_texttospeech_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_theme_support_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_uiplugin.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_uitools.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_uitools_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_webchannel.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_webchannel_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_websockets.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_websockets_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_widgets.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_widgets_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_winextras.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_winextras_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_xml.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_xml_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_xmlpatterns.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_xmlpatterns_private.pri \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/qt_functions.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/qt_config.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/win32-g++/qmake.conf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/spec_post.prf \
		.qmake.stash \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/exclusive_builds.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/toolchain.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/default_pre.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/win32/default_pre.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/resolve_config.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/exclusive_builds_post.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/default_post.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/resolve_target.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/win32/separate_debug_info.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/qml_debug.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/precompile_header.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/warn_on.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/qt.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/resources.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/moc.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/win32/opengl.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/uic.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/qmake_use.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/file_copies.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/win32/windows.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/testcase_targets.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/exceptions.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/yacc.prf \
		../../QQT5.9/5.9/mingw53_32/mkspecs/features/lex.prf \
		Thegianshoulder.pro \
		../../QQT5.9/5.9/mingw53_32/lib/qtmain.prl \
		../../QQT5.9/5.9/mingw53_32/lib/Qt5Widgets.prl \
		../../QQT5.9/5.9/mingw53_32/lib/Qt5Gui.prl \
		../../QQT5.9/5.9/mingw53_32/lib/Qt5Network.prl \
		../../QQT5.9/5.9/mingw53_32/lib/Qt5Core.prl
	$(QMAKE) -o Makefile Thegianshoulder.pro -spec win32-g++ "CONFIG+=qml_debug" "CONFIG+=force_debug_info" "CONFIG+=separate_debug_info"
../../QQT5.9/5.9/mingw53_32/mkspecs/features/spec_pre.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/qdevice.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/device_config.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/common/g++-base.conf:
../../QQT5.9/5.9/mingw53_32/mkspecs/common/angle.conf:
../../QQT5.9/5.9/mingw53_32/mkspecs/common/sanitize.conf:
../../QQT5.9/5.9/mingw53_32/mkspecs/common/gcc-base.conf:
../../QQT5.9/5.9/mingw53_32/mkspecs/qconfig.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3danimation.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3danimation_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dcore.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dcore_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dextras.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dextras_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dinput.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dinput_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dlogic.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dlogic_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquick.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquick_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquickanimation.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquickanimation_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquickextras.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquickextras_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquickinput.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquickinput_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquickrender.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquickrender_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquickscene2d.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3dquickscene2d_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3drender.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_3drender_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_accessibility_support_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_axbase.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_axbase_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_axcontainer.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_axcontainer_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_axserver.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_axserver_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_bluetooth.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_bluetooth_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_bootstrap_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_charts.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_charts_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_concurrent.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_concurrent_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_core.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_core_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_datavisualization.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_datavisualization_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_dbus.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_dbus_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_designer.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_designer_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_designercomponents_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_devicediscovery_support_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_egl_support_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_fb_support_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_fontdatabase_support_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_gamepad.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_gamepad_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_gui.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_gui_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_help.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_help_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_location.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_location_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_multimedia.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_multimedia_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_multimediawidgets.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_multimediawidgets_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_network.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_network_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_networkauth.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_networkauth_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_nfc.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_nfc_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_opengl.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_opengl_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_openglextensions.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_openglextensions_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_packetprotocol_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_platformcompositor_support_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_positioning.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_positioning_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_printsupport.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_printsupport_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_purchasing.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_purchasing_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_qml.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_qml_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_qmldebug_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_qmldevtools_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_qmltest.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_qmltest_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_quick.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_quick_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_quickcontrols2.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_quickcontrols2_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_quickparticles_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_quicktemplates2_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_quickwidgets.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_quickwidgets_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_remoteobjects.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_remoteobjects_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_repparser.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_repparser_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_script.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_script_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_scripttools.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_scripttools_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_scxml.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_scxml_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_sensors.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_sensors_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_serialbus.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_serialbus_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_serialport.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_serialport_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_sql.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_sql_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_svg.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_svg_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_testlib.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_testlib_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_texttospeech.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_texttospeech_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_theme_support_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_uiplugin.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_uitools.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_uitools_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_webchannel.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_webchannel_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_websockets.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_websockets_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_widgets.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_widgets_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_winextras.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_winextras_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_xml.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_xml_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_xmlpatterns.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/modules/qt_lib_xmlpatterns_private.pri:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/qt_functions.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/qt_config.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/win32-g++/qmake.conf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/spec_post.prf:
.qmake.stash:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/exclusive_builds.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/toolchain.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/default_pre.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/win32/default_pre.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/resolve_config.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/exclusive_builds_post.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/default_post.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/resolve_target.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/win32/separate_debug_info.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/qml_debug.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/precompile_header.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/warn_on.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/qt.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/resources.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/moc.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/win32/opengl.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/uic.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/qmake_use.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/file_copies.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/win32/windows.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/testcase_targets.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/exceptions.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/yacc.prf:
../../QQT5.9/5.9/mingw53_32/mkspecs/features/lex.prf:
Thegianshoulder.pro:
../../QQT5.9/5.9/mingw53_32/lib/qtmain.prl:
../../QQT5.9/5.9/mingw53_32/lib/Qt5Widgets.prl:
../../QQT5.9/5.9/mingw53_32/lib/Qt5Gui.prl:
../../QQT5.9/5.9/mingw53_32/lib/Qt5Network.prl:
../../QQT5.9/5.9/mingw53_32/lib/Qt5Core.prl:
qmake: FORCE
	@$(QMAKE) -o Makefile Thegianshoulder.pro -spec win32-g++ "CONFIG+=qml_debug" "CONFIG+=force_debug_info" "CONFIG+=separate_debug_info"

qmake_all: FORCE

make_first: release-make_first debug-make_first  FORCE
all: release-all debug-all  FORCE
clean: release-clean debug-clean  FORCE
distclean: release-distclean debug-distclean  FORCE
	-$(DEL_FILE) Makefile
	-$(DEL_FILE) G:\tsttt\Thegianshoulder\chess2.exe.debug .qmake.stash

release-mocclean:
	$(MAKE) -f $(MAKEFILE).Release mocclean
debug-mocclean:
	$(MAKE) -f $(MAKEFILE).Debug mocclean
mocclean: release-mocclean debug-mocclean

release-mocables:
	$(MAKE) -f $(MAKEFILE).Release mocables
debug-mocables:
	$(MAKE) -f $(MAKEFILE).Debug mocables
mocables: release-mocables debug-mocables

check: first

benchmark: first
FORCE:

$(MAKEFILE).Release: Makefile
$(MAKEFILE).Debug: Makefile