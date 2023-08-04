# 使用CMake控制的项目

## 环境准备
1. [VSCode](https://code.visualstudio.com/)
2. 编译链
    - gcc - 通过Qt、CodeBlocks、Dev-C++带的编译链安装
    - [clang](https://github.com/llvm/llvm-project/releases)
    - cl - 通过Visual Studio安装
2. [cmake](https://cmake.org/)
3. [vcpkg](https://vcpkg.io/en/index.html)
4. [powershell 7.2.x+ (这个是vcpkg的依赖项)](https://github.com/PowerShell/PowerShell/releases)

## 视频
[参考视频(10分钟) 首选](https://www.bilibili.com/video/BV1rR4y1E7n9?spm_id_from=333.337.search-card.all.click&vd_source=8bd7b24b38e3e12c558d839b352b32f4)  
[参考视频](https://www.bilibili.com/video/BV13K411M78v?p=2&spm_id_from=pageDriver)

## update 20230804 
> 本例中cmake到底替换了什么操作 —— 如果直接使用g++  

[来自参考视频](https://www.bilibili.com/video/BV13K411M78v?p=2&spm_id_from=pageDriver)
```shell
# 单文档
g++ main.cpp -o my_single_swap
# 单文档带调试
g++ -g main.cpp -o my_single_swap_debug

# 多文档
g++ -g main.cpp swap.cpp -o my_multi_swap_debug
```
> 如果使用cmaket 提要如下（视频27:39开始介绍cmake使用）  
- 编写最简单的CMakeLists.txt
```shell
project(MYSWAP)
add_executable(my_cmake_swap main.cpp swap.cpp)
```
- 进行多文件编译，并调试
```shell
mkdir build
cd build
# 如果电脑上已经安装了VS，可能会调用MSVC编译器，使用(cmake -G "MinGW Makefiles" ..)代替(cmake ..)即可
# 仅第一次使用cmake时使用cmake -G "MinGW Makefiles" ..， 后面可使用cmake ..。
cmake ..
mingw32-make.exe
```

## update 20220806  
[来自参考视频(10分钟) 首选](https://www.bilibili.com/video/BV1rR4y1E7n9?spm_id_from=333.337.search-card.all.click&vd_source=8bd7b24b38e3e12c558d839b352b32f4)  
1. 不需要做的
- 不需要.vscode  
- 如果使用msvc不需要使用Developer Command Prompt for VS 2022打开VSCode工程  
2. 配置ctrl + shift + p 输入 cmake configure
```shell
# 对应配置项目命令：
cmake -S . -B build
``` 
3. 构建ctrl + shift + p 输入 cmake build
```shell
# 对应构建项目命令
cmake --build build
```

4. C++第三方库, 推荐微软的vcpkg  
[vcpkg Github](https://github.com/Microsoft/vcpkg)  
摘要如下  
4.1. 命令行构建
```shell
# 构建的时候只需要额外置顶vcpkg工具链即可
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=C:/User/xconf/vcpkg/scripts/buildsystems/vcpkg.cmake
```
4.2. 使用vscode插件  
settings.json
```javascript
{
    "cmake.configureSettings" : {
        "CMAKE_TOOLCHAIN_FILE" : "C:/User/xconf/vcpkg/scripts/buildsystems/vcpkg.cmake"
    }
}
```


## archived before 20220806
测试从X13上提交

## 安装插件
C/C++
CMake
CMake Tools

## 完全配置json 适配VSCode "F5" (视频44:00左右开始讲解这两个配置文件)
- launch.json -- for debug
- tasks.json -- for build before debug
>launch.json
```json
{
    // 使用 IntelliSense 了解相关属性。 
    // 悬停以查看现有属性的描述。
    // 欲了解更多信息，请访问: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "g++.exe - 生成和调试活动文件",
            "type": "cppdbg",
            "request": "launch",
            // "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
            "program": "${workspaceFolder}\\build\\my_cmake_swap.exe", // liuyang modify
            "args": [],
            "stopAtEntry": false,
            "cwd": "C:\\CodeBlocks\\MinGW\\bin",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "C:\\CodeBlocks\\MinGW\\bin\\gdb.exe",
            "setupCommands": [
                {
                    "description": "为 gdb 启用整齐打印",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            // 编译：（手动编译）则注释掉"preLaunchTask"
            // "preLaunchTask": "C/C++: g++.exe build active file"  
            // 注1(直接调用g++)：g++ -g ./main.cpp ./swap.cpp -o my_cmake_swap.exe
            // 注2(调用cmake)：cd build; cmake ..; mingw32-make;
            // 编译：（利用VSCode调用）
            "preLaunchTask": "build" // liuyang modify // 配置tasks.json调用cmake"自动编译"
        }
    ]
}
```

>tasks.json
```shell
# 下面的task.json是为了完成一下的操作。
cd build
cmake ..
# make
mingw32-make
```
```json
{
    // liyang add "cd build"
    "options": {
        "cwd": "${workspaceFolder}/build"
    },
    "tasks": [
        // //////////////////////////////////////////////////////
        // liuyang add build
        {
            "label": "build", 
            "dependsOn":[
                "cmake",
                "make"
            ]
        },
        // liuyang add cmake
        {
            "label": "cmake",
            "type": "shell",
            "command": "cmake",
            "args": [
                ".."
            ]
        },
        // liuyang add make
        {
            "label": "make",
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "command": "mingw32-make", // on linux is make
            "args": [

            ]
        },
        // //////////////////////////////////////////////////////
        // VSCode自己利用g++编译（VSCode自己生成的）
        {
            "type": "cppbuild",
            "label": "C/C++: g++.exe build active file",
            "command": "C:\\CodeBlocks\\MinGW\\bin\\g++.exe",
            "args": [
                "-g",
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe"
            ],
            "options": {
                "cwd": "C:\\CodeBlocks\\MinGW\\bin"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "Task generated by Debugger."
        }
    ],
    "version": "2.0.0"
}
```
----

# 附GitHub相关
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

----

# 附 分步骤演示（在没有配置完整的launch.json和tasks.json时）

## 编译
先要ctrl + shift + p -> "CMake 配置" -> 选择gcc
```
cd build
cmake ..
# make
mingw32-make
```
可执行文件就在build文件夹下

## 调试
配置.vscode/launch.json
>launch.json
```
# 修改
// "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
"program": "${workspaceFolder}\\build\\my_cmake_swap.exe",
# 注释掉preLaunchTask
// "preLaunchTask": "C/C++: g++.exe build active file"
```