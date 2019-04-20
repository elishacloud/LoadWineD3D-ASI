# LoadWineD3D ASI

### Introduction

A simple ASI file that loads the WineD3D dll's from the ASI 'scripts' folder. This way you can load different DirectX dll files (or no DirectX dll files) from the game's EXE folder.

### Installation

How to install:

1. Download the LoadWineD3D ASI file from the [releases](https://github.com/elishacloud/LoadWineD3D-ASI/releases) page and unzip it into the ASI 'scripts' folder.
2. Copy the WineD3D dll's into the ASI 'scripts' folder.  Usually this will be the wine3d.dll, libwine.dll and one or more of the following: d3d8.dll, d3d9.dll, d3d10.dll, d3d11.dll, d3d11core.dll, dxgi.dll or ddraw.dll
3. (Optional) You can add other DirectX dll files into the games EXE folder.

### Unnstallation

How to uninstall:

1. Remove the LoadWineD3D ASI file and optionally the log file from the ASI 'scripts' folder.
2. Remove the WineD3D dll's from the ASI 'scripts' folder.

### License

Copyright (C) 2019 Elisha Riedlinger

This software is  provided 'as-is', without any express  or implied  warranty. In no event will the
authors be held liable for any damages arising from the use of this software.
Permission  is granted  to anyone  to use  this software  for  any  purpose,  including  commercial
applications, and to alter it and redistribute it freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not claim that you  wrote the
      original  software. If you use this  software  in a product, an  acknowledgment in the product
      documentation would be appreciated but is not required.
   2. Altered source versions must  be plainly  marked as such, and  must not be  misrepresented  as
      being the original software.
   3. This notice may not be removed or altered from any source distribution.

This LoadWineD3D ASI is taken primarily from code in [DxWrapper](https://github.com/elishacloud/dxwrapper).  But also includes code from the following:

 - [DxWnd](https://sourceforge.net/projects/dxwnd/): Includes the HotPatch and IATPatch code.
 - [Parsing PE export table](http://www.rohitab.com/discuss/topic/40594-parsing-pe-export-table/): Includes the full GetProcAddress.

### Development

This code was written in C++ using Microsoft Visual Studio Community 2017.
