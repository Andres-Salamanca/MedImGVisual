# MedImGVisual

## how to build

### Basic build
> `-DCMAKE_EXPORT_COMPILE_COMMANDS=1` used for exporting compile_commands.json for the clangd lsp

```
mkdir build
cmake ../source  -DCMAKE_EXPORT_COMPILE_COMMANDS=1
```

### build using vcpkg
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
        "opengl"
      ]
    }
  ]
}
```
