# 使用CMake控制的项目

## 编译
```
cd build
cmake ..
# make
mingw32-make
```
可执行文件就在build文件夹下

## 调试
配置.vscode/launch.json
```
// "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
"program": "${workspaceFolder}\\build\\my_cmake_swap.exe",
```




## from GitHub 创建完工程的提示
Quick setup — if you’ve done this kind of thing before
or	
git@github.com:xconfigurator/test_cpp_cmake_quickstart.git
Get started by creating a new file or uploading an existing file. We recommend every repository include a README, LICENSE, and .gitignore.

…or create a new repository on the command line
```
echo "# test_cpp_cmake_quickstart" >> README.md
git init
git add README.md
git commit -m "first commit"
git branch -M main
git remote add origin git@github.com:xconfigurator/test_cpp_cmake_quickstart.git
git push -u origin main
```
…or push an existing repository from the command line
```
git remote add origin git@github.com:xconfigurator/test_cpp_cmake_quickstart.git
git branch -M main
git push -u origin main
```

…or import code from another repository
You can initialize this repository with code from a Subversion, Mercurial, or TFS project.