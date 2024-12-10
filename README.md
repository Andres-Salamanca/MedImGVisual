# MedImGVisual

## Description  
MedImGVisual is a visualization tool for exploring MRI, CT, and digitized pathology images in 3D. It supports files with extensions such as:  
- **DICOM series** (`.DCM`)  
- **MHA**  
- **VTI**  

The tool has been tested with datasets from **[The Cancer Imaging Archive (TCIA)](https://www.cancerimagingarchive.net/)**.  

### Key Features  
1. **3D Visualization**:  
   - Render volumetric images in 3D with real-time interaction.  

2. **Multi-Planar Views**:  
   - Explore axial, coronal, and sagittal views.  

3. **Interactive Widgets**:  
   - Interact with 2D images and customize segmentation of body parts using your preferred colors, based on the [Hounsfield scale](https://en.wikipedia.org/wiki/Hounsfield_scale).  

### Technology Stack  
- **Programming Language**: C++  
- **Libraries**:  
  - **ITK** for image processing.  
  - **VTK** for rendering, with **Qt** integration for GUI development.  
  - **QT** for GUI development.
- **Rendering**: Uses VTK built with Qt integration to manage different OpenGL views seamlessly.  

![MedImGVisual Tool in Action](Images/MedImGVisual.gif)  
---

## How to Build

### Basic Build
> `-DCMAKE_EXPORT_COMPILE_COMMANDS=1` is used for exporting `compile_commands.json` for the `clangd` LSP.

```
mkdir build
cmake ../source -DCMAKE_EXPORT_COMPILE_COMMANDS=1
```

### Build Using vcpkg
```
mkdir build
cmake ../source -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1
```
**vcpkg.json**
```
{
  "dependencies": [
    {
      "name": "itk",
      "features": [
        "vtk"
      ]
    },
    {
      "name": "vtk",
      "features": [
        "opengl",
        "qt"
      ]
    }
  ]
}
```

> **Problem with vcpkg and Qt usage**:
>
>> Use the command  
>> ```'/vcpkg/installed/x64-windows/tools/Qt6/bin/windeployqt.exe ./{executable}'```  
>> for importing appropriate libraries.  

> **Important**: Compile in release mode because it won't work in debug mode.  
>> ```cmake --build . --config Release```

---


