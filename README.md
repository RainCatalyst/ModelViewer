# Model Viewer
![Example](https://i.imgur.com/l6xurCk.png)
## Run
* Download the release build
* Unpack the contents of the folder
* Run ModelViewer.exe (or SSAA version) and provide the path to the 3d model file
```
Model path:
./samples/alliance.obj
Mesh count: 1
BBox size: vec3(0.447438, 1.085979, 0.513685) (max = 1.08598)
BBox center: vec3(-0.000049, 0.538849, 0.000777)
Computing mesh colors...
Vertex count: 18273
Index count: 18273
Done.
```
## Build
* Clone the repo
* Configure and build using CMake
* If you run into issues with assimp, download the MSYS2 MinGW version

## Credits
Heavily based on this tutorial: https://shot511.github.io/2018-05-29-how-to-setup-opengl-project-with-cmake/