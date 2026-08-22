keymaps = [
  ['atset1', 'linux'],
  ['linux', 'qcode'],
  ['linux', 'atset1'],
  ['linux', 'atset2'],
  ['linux', 'atset3'],
  ['qcode', 'linux'],
  ['linux', 'qnum'],
  ['linux', 'sun'],
  ['qnum', 'linux'],
  ['usb', 'linux'],
  ['win32', 'linux'],
  ['x11', 'linux'],
  ['xorgkbd', 'linux'],
  ['xorgxquartz', 'linux'],
  ['xorgxwin', 'linux'],
  ['osx', 'linux'],
]

if have_system
  keycodemapdb_proj = subproject('keycodemapdb', required: true)
  foreach e : keymaps
    output = 'input-keymap-@0@-to-@1@.c.inc'.format(e[0], e[1])
    genh += custom_target(output,
                  output: output,
                  capture: true,
                  input: keycodemapdb_proj.get_variable('keymaps_csv'),
                  command: [python, keycodemapdb_proj.get_variable('keymap_gen').full_path(),
                            'code-map', '--lang', 'glib2',
                            '--varname', 'qemu_input_map_@0@_to_@1@'.format(e[0], e[1]),
                            '@INPUT0@', e[0], e[1]])
  endforeach
endif

libui_sources = files(
    'clipboard.c',
    'console.c',
    'cursor.c',
    'dmabuf.c',
    'display-surface.c',
    'input-keymap.c',
    'kbd-state.c',
    'keymaps.c',
    'spice-module.c',
    'vgafont.c',
  )

system_ss.add(png)
system_ss.add(files(
  'input-barrier.c',
  'input.c',
  'ui-hmp-cmds.c',
  'ui-qmp-cmds.c',
  'util.c',
))
system_ss.add(ui)
if dbus_display
  system_ss.add(files('dbus-module.c'))
endif
system_ss.add(when: spice_protocol, if_true: files('vdagent.c'))

if host_os == 'linux'
  system_ss.add(files('input-linux.c', 'udmabuf.c'))
endif

ui_modules = {}

dbus_display1 = files()
if dbus_display
  dbus_ss = ss.source_set()
  env = environment()
  env.set('HOST_OS', host_os)
  xml = custom_target('dbus-display preprocess',
                      input: 'dbus-display1.xml',
                      output: 'dbus-display1.xml',
                      env: env,
                      command: [xml_pp, '@INPUT@', '@OUTPUT@'])
  dbus_display1 = custom_target('dbus-display gdbus-codegen',
                                output: ['dbus-display1.h', 'dbus-display1.c'],
                                input: xml,
                                command: [gdbus_codegen, '@INPUT@',
                                          '--glib-min-required', '2.64',
                                          '--output-directory', meson.current_build_dir(),
                                          '--interface-prefix', 'org.qemu.',
                                          '--c-namespace', 'QemuDBus',
                                          '--generate-c-code', '@BASENAME@'])
  dbus_display1_h = declare_dependency(dependencies: [gio],
                                       sources: dbus_display1[0])
  ui_modules += {'dbus' : dbus_ss}
endif

subdir('shader')

if have_system
  subdir('icons')

  install_data('qemu.desktop', install_dir: qemu_desktopdir)
endif

modules += {'ui': ui_modules}
