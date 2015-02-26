# -*- coding: utf-8 -*-
# Deployment settings for SlidingHomeC.
# This file is autogenerated by the mkb system and used by the s3e deployment
# tool during the build process.

config = {}
cmdline = ['C:/Marmalade/7.3/s3e/makefile_builder/mkb.py', 'c:/Users/b1002814/Desktop/slidinghome/SlidingHomeC.mkb', '--buildenv=VC12X', '--debug', '--x86', '--no-ide', '--make', '--deploy-only']
mkb = 'c:/Users/b1002814/Desktop/slidinghome/SlidingHomeC.mkb'
mkf = ['c:\\marmalade\\7.3\\modules\\iw2d\\iw2d.mkf', 'c:\\marmalade\\7.3\\modules\\iwgx\\iwgx.mkf', 'c:\\marmalade\\7.3\\modules\\iwgl\\iwgl.mkf', 'c:\\marmalade\\7.3\\modules\\iwutil\\iwutil.mkf', 'c:\\marmalade\\7.3\\modules\\third_party\\libjpeg\\libjpeg.mkf', 'c:\\marmalade\\7.3\\modules\\third_party\\libpng\\libpng.mkf', 'c:\\marmalade\\7.3\\modules\\third_party\\zlib\\zlib.mkf', 'c:\\marmalade\\7.3\\modules\\iwgeom\\iwgeom.mkf', 'c:\\marmalade\\7.3\\modules\\iwresmanager\\iwresmanager.mkf', 'c:\\marmalade\\7.3\\extensions\\pvrtextool\\pvrtextool.mkf', 'c:\\marmalade\\7.3\\modules\\iwgxfont\\iwgxfont.mkf', 'c:\\marmalade\\7.3\\modules\\third_party\\tiniconv\\tiniconv.mkf', 'c:\\marmalade\\7.3\\modules\\iw2dscenegraph\\iw2dscenegraph.mkf', 'c:\\marmalade\\7.3\\modules\\iw2dscenegraphcore\\iw2dscenegraphcore.mkf', 'c:\\marmalade\\7.3\\modules\\iwtween\\iwtween.mkf', 'c:\\users\\b1002814\\desktop\\slidinghome\\modules\\soundengine\\soundengine.mkf']

class DeployConfig(object):
    pass

######### ASSET GROUPS #############

assets = {}

assets['Default'] = [
    ('c:/Users/b1002814/Desktop/slidinghome/data', '.', 0),
    ('c:/Users/b1002814/Desktop/slidinghome/data/audio', 'audio', 0),
    ('c:/Users/b1002814/Desktop/slidinghome/data/textures', 'textures', 0),
    ('c:/Users/b1002814/Desktop/slidinghome/data/maps', 'maps', 0),
    ('c:/Users/b1002814/Desktop/slidinghome/data/fonts', 'fonts', 0),
    ('c:/Users/b1002814/Desktop/slidinghome/data-ram/data-gles1', '.', 0),
    ('c:/Users/b1002814/Desktop/slidinghome/data-ram/data-gles1/fonts/arial8.gxfont.bin', 'fonts/arial8.gxfont.bin', 0),
]

######### DEFAULT CONFIG #############

class DefaultConfig(DeployConfig):
    embed_icf = -1
    name = 'SlidingHomeC'
    pub_sign_key = 0
    priv_sign_key = 0
    caption = 'SlidingHomeC'
    long_caption = 'SlidingHomeC'
    version = [0, 0, 0]
    config = ['c:/Users/b1002814/Desktop/slidinghome/data/app.icf']
    data_dir = 'c:/Users/b1002814/Desktop/slidinghome/data'
    iphone_link_lib = []
    osx_ext_dll = ['c:/marmalade/7.3/extensions/pvrtextool/lib/osx/libPVRTexTool.dylib']
    ws8_ext_capabilities = []
    android_external_res = []
    win32_ext_dll = ['c:/marmalade/7.3/extensions/pvrtextool/lib/win32/PVRTexTool.dll']
    wp8_ext_capabilities = []
    ws81_ext_managed_dll = []
    iphone_link_libdir = []
    android_extra_application_manifest = []
    ws8_ext_native_dll = []
    android_extra_manifest = []
    iphone_link_libdirs = []
    linux_ext_lib = []
    ws8_ext_managed_dll = []
    ws81_ext_sdk_ref_file = []
    ws8_ext_sdk_manifest_part = []
    ws8_ext_device_capabilities = []
    android_external_jars = []
    android_supports_gl_texture = []
    ws81_ext_sdk_manifest_part = []
    ws81_ext_device_capabilities = []
    ws8_ext_sdk_ref = []
    iphone_extra_string = []
    tizen_so = []
    wp8_ext_native_dll = []
    ws81_ext_sdk_ref = []
    iphone_link_opts = []
    ws81_ext_native_dll = []
    wp8_ext_managed_dll = []
    android_so = []
    osx_extra_res = []
    ws81_ext_capabilities = []
    iphone_link_libs = []
    target = {
         'gcc_x86' : {
                   'debug'   : r'c:/Users/b1002814/Desktop/slidinghome/build_slidinghomec_vc12x/Debug_SlidingHomeC_VC12X_gcc_x86/SlidingHomeC.so',
                   'release' : r'c:/Users/b1002814/Desktop/slidinghome/build_slidinghomec_vc12x/Release_SlidingHomeC_VC12X_gcc_x86/SlidingHomeC.so',
                 },
         'gcc_x86_tizen' : {
                   'debug'   : r'c:/Users/b1002814/Desktop/slidinghome/build_slidinghomec_vc12x/Debug_SlidingHomeC_VC12X_gcc_x86_tizen/SlidingHomeC.s86',
                   'release' : r'c:/Users/b1002814/Desktop/slidinghome/build_slidinghomec_vc12x/Release_SlidingHomeC_VC12X_gcc_x86_tizen/SlidingHomeC.s86',
                 },
         'mips_gcc' : {
                   'debug'   : r'c:/Users/b1002814/Desktop/slidinghome/build_slidinghomec_vc12x/Debug_SlidingHomeC_VC12X_gcc_mips/SlidingHomeC.so',
                   'release' : r'c:/Users/b1002814/Desktop/slidinghome/build_slidinghomec_vc12x/Release_SlidingHomeC_VC12X_gcc_mips/SlidingHomeC.so',
                 },
         'arm_gcc' : {
                   'debug'   : r'c:/Users/b1002814/Desktop/slidinghome/build_slidinghomec_vc12x/Debug_SlidingHomeC_VC12X_gcc_arm/SlidingHomeC.s3e',
                   'release' : r'c:/Users/b1002814/Desktop/slidinghome/build_slidinghomec_vc12x/Release_SlidingHomeC_VC12X_gcc_arm/SlidingHomeC.s3e',
                 },
         'mips' : {
                   'debug'   : r'c:/Users/b1002814/Desktop/slidinghome/build_slidinghomec_vc12x/Debug_SlidingHomeC_VC12X_gcc_mips/SlidingHomeC.so',
                   'release' : r'c:/Users/b1002814/Desktop/slidinghome/build_slidinghomec_vc12x/Release_SlidingHomeC_VC12X_gcc_mips/SlidingHomeC.so',
                 },
         'gcc_x86_android' : {
                   'debug'   : r'c:/Users/b1002814/Desktop/slidinghome/build_slidinghomec_vc12x/Debug_SlidingHomeC_VC12X_gcc_x86_android/SlidingHomeC.so',
                   'release' : r'c:/Users/b1002814/Desktop/slidinghome/build_slidinghomec_vc12x/Release_SlidingHomeC_VC12X_gcc_x86_android/SlidingHomeC.so',
                 },
         'arm' : {
                   'debug'   : r'c:/Users/b1002814/Desktop/slidinghome/build_slidinghomec_vc12x/Debug_SlidingHomeC_VC12X_arm/SlidingHomeC.s3e',
                   'release' : r'c:/Users/b1002814/Desktop/slidinghome/build_slidinghomec_vc12x/Release_SlidingHomeC_VC12X_arm/SlidingHomeC.s3e',
                 },
         'x86' : {
                   'debug'   : r'c:/Users/b1002814/Desktop/slidinghome/build_slidinghomec_vc12x/Debug_SlidingHomeC_VC12X_x86/SlidingHomeC.s86',
                   'release' : r'c:/Users/b1002814/Desktop/slidinghome/build_slidinghomec_vc12x/Release_SlidingHomeC_VC12X_x86/SlidingHomeC.s86',
                 },
        }
    arm_arch = ''
    assets_original = assets
    assets = assets['Default']

default = DefaultConfig()
