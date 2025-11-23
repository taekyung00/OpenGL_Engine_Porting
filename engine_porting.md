================================================
FILE: README.md
================================================

# CS200 Computer Graphics I

## How to Build and Run

First Setup your [Development Environment](docs/DevEnvironment.md)

### How to build and run

- open this folder(DragonicTactics) with visual studio code, and select configure preset with window (debug/developer release/ release). Now you can keep working with visual studio code , or you can move your ide with Visual Studio by open ./build/window*/*sln file.Then build with cmake(F7 shortkey may works) in VSCode or in VS(ctrl+shift+B) and run it!

### Project explanation

- You can check our base system works well by go Dragonic tactics in mainmenu. 
  
  Wheter all system is worked well is logged in console(VS) or debug console(VSCode).
  
  Keys to test:
  
  - F : eventbus check
  
  - E : dice manager
  
  - T : dragon and fighter status with fighter turn
  
  - Y : dragon and fighter status with dragon turn
  
  - D : dragon attack
  
  - H : fighter heal
  
  - S : grid
  
  - P : turn manager
  
  - J : test json
  
  - R: test json reload
  
  - L : test json log
  
  - Enter : test all combat system

- You can watch visualize demo in Test2 state. 
  
  - move character with arrow keys

- You can exit test states by press esc key

- You can also check how our engine works well by open demos provided in CS200 with Imgui panel, and also CS230 Final project in mainmenu. In final project, you should check particle(shining, ..), gamastate component(grid,..), gameobject component(ziggle,...), animation(passenger) working well.

### Command Line Build

**Windows**

```sh
# configure / generate build files
cmake --preset windows-debug
cmake --preset windows-developer-release
cmake --preset windows-release
cmake --preset web-debug-on-windows

# Build exe
cmake --build --preset windows-debug
cmake --build --preset windows-developer-release
cmake --build --preset windows-release
cmake --build --preset web-debug-on-windows
```

================================================
FILE: CMakeLists.txt
================================================

# author Rudy Castan

# date 2025 Fall

# CS200 Computer Graphics I

# copyright DigiPen Institute of Technology

cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# #  Helper to print out all environment variables

# get_cmake_property(_variableNames VARIABLES)

# list (SORT _variableNames)

# foreach (_variableName ${_variableNames})

# message(STATUS "${_variableName}=${${_variableName}}")

# endforeach()

project(engine_porting)

include(cmake/StandardProjectSettings.cmake)

include(cmake/CompilerWarnings.cmake)
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)
set_project_warnings(project_options)

include(cmake/Dependencies.cmake)

add_subdirectory(source)

================================================
FILE: CMakePresets.json
================================================
{
    "version": 3,
    "cmakeMinimumRequired": {
        "major": 3,
        "minor": 21,
        "patch": 0
    },
    "configurePresets": [
        {
            "name": "conf-common",
            "description": "General settings that apply to all configurations",
            "hidden": true,
            "binaryDir": "${sourceDir}/build/${presetName}",
            "installDir": "${sourceDir}/build/install/${presetName}"
        },
        {
            "name": "conf-windows-common",
            "description": "Windows settings for MSBuild toolchain that apply to msvc and clang",
            "hidden": true,
            "inherits": "conf-common",
            "condition": {
                "type": "equals",
                "lhs": "${hostSystemName}",
                "rhs": "Windows"
            },
            "architecture": {
                "value": "x64",
                "strategy": "external"
            },
            "toolset": {
                "value": "host=x64",
                "strategy": "external"
            },
            "cacheVariables": {
                "CMAKE_C_COMPILER": "cl",
                "CMAKE_CXX_COMPILER": "cl"
            }
        },
        {
            "name": "conf-unixlike-common",
            "description": "Unix-like OS settings for gcc and clang toolchains",
            "hidden": true,
            "inherits": "conf-common",
            "generator": "Ninja",
            "condition": {
                "type": "inList",
                "string": "${hostSystemName}",
                "list": [
                    "Linux",
                    "Darwin"
                ]
            },
            "cacheVariables": {
                "CMAKE_C_COMPILER": "gcc",
                "CMAKE_CXX_COMPILER": "g++"
            }
        },
        {
            "name": "conf-web-common",
            "description": "Common Web/Emscripten configuration",
            "hidden": true,
            "inherits": "conf-unixlike-common",
            "generator": "Ninja",
            "toolchainFile": "~/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake",
            "cacheVariables": {
                "CMAKE_C_COMPILER": "~/emsdk/upstream/emscripten/emcc",
                "CMAKE_CXX_COMPILER": "~/emsdk/upstream/emscripten/em++"
            }
        },
        {
            "name": "windows-debug",
            "displayName": "Windows Debug",
            "description": "Debug Build on Windows",
            "inherits": "conf-windows-common",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Debug",
                "IS_DEVELOPER_VERSION": "TRUE"
            }
        },
        {
            "name": "windows-developer-release",
            "displayName": "Windows Developer Release",
            "description": "Optimized Developer Build on Windows",
            "inherits": "conf-windows-common",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Release",
                "IS_DEVELOPER_VERSION": "TRUE"
            }
        },
        {
            "name": "windows-release",
            "displayName": "Windows Release",
            "description": "Optimized User Facing Build on Windows",
            "inherits": "conf-windows-common",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Release",
                "IS_DEVELOPER_VERSION": "FALSE"
            }
        },
        {
            "name": "web-debug-on-windows",
            "displayName": "Web Debug on Windows",
            "description": "Debug Build on Web for Windows",
            "inherits": "conf-common",
            "condition": {
                "type": "equals",
                "lhs": "${hostSystemName}",
                "rhs": "Windows"
            },
            "generator": "Ninja",
            "toolchainFile": "$env{USERPROFILE}/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake",
            "cacheVariables": {
                "CMAKE_C_COMPILER": "$env{USERPROFILE}/emsdk/upstream/emscripten/emcc",
                "CMAKE_CXX_COMPILER": "$env{USERPROFILE}/emsdk/upstream/emscripten/em++",
                "CMAKE_BUILD_TYPE": "Debug",
                "IS_DEVELOPER_VERSION": "TRUE"
            }
        },
        {
            "name": "linux-debug",
            "displayName": "Linux Debug",
            "description": "Debug Build on Linux",
            "inherits": "conf-unixlike-common",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Debug",
                "IS_DEVELOPER_VERSION": "TRUE"
            }
        },
        {
            "name": "linux-developer-release",
            "displayName": "Linux Developer Release",
            "description": "Optimized Developer Build on Linux",
            "inherits": "conf-unixlike-common",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Release",
                "IS_DEVELOPER_VERSION": "TRUE"
            }
        },
        {
            "name": "linux-release",
            "displayName": "Linux Release",
            "description": "Optimized User Facing Build on Linux",
            "inherits": "conf-unixlike-common",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Release",
                "IS_DEVELOPER_VERSION": "FALSE"
            }
        },
        {
            "name": "web-debug",
            "displayName": "Web Debug",
            "description": "Debug Build on Web",
            "inherits": "conf-web-common",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Debug",
                "IS_DEVELOPER_VERSION": "TRUE"
            }
        },
        {
            "name": "web-developer-release",
            "displayName": "Web Developer Release",
            "description": "Optimized Developer Build on Web",
            "inherits": "conf-web-common",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Release",
                "IS_DEVELOPER_VERSION": "TRUE"
            }
        },
        {
            "name": "web-release",
            "displayName": "Web Release",
            "description": "Optimized User Facing Build on Web",
            "inherits": "conf-web-common",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Release",
                "IS_DEVELOPER_VERSION": "FALSE"
            }
        }
    ],
    "buildPresets": [
        {
            "name": "build-windows-common",
            "description": "Windows build settings",
            "hidden": true,
            "condition": {
                "type": "equals",
                "lhs": "${hostSystemName}",
                "rhs": "Windows"
            }
        },
        {
            "name": "build-unixlike-common",
            "description": "Unix-like build settings",
            "hidden": true,
            "condition": {
                "type": "inList",
                "string": "${hostSystemName}",
                "list": [
                    "Linux",
                    "Darwin"
                ]
            }
        },
        {
            "name": "windows-debug",
            "configurePreset": "windows-debug",
            "inherits": "build-windows-common",
            "configuration": "Debug"
        },
        {
            "name": "windows-developer-release",
            "configurePreset": "windows-developer-release",
            "inherits": "build-windows-common",
            "configuration": "RelWithDebInfo"
        },
        {
            "name": "windows-release",
            "configurePreset": "windows-release",
            "inherits": "build-windows-common",
            "configuration": "Release"
        },
        {
            "name": "web-debug-on-windows",
            "configurePreset": "web-debug-on-windows",
            "inherits": "build-windows-common",
            "configuration": "Debug"
        },
        {
            "name": "linux-debug",
            "configurePreset": "linux-debug",
            "inherits": "build-unixlike-common",
            "configuration": "Debug"
        },
        {
            "name": "linux-developer-release",
            "configurePreset": "linux-developer-release",
            "inherits": "build-unixlike-common",
            "configuration": "RelWithDebInfo"
        },
        {
            "name": "linux-release",
            "configurePreset": "linux-release",
            "inherits": "build-unixlike-common",
            "configuration": "Release"
        },
        {
            "name": "web-debug",
            "configurePreset": "web-debug",
            "inherits": "build-unixlike-common",
            "configuration": "Debug"
        },
        {
            "name": "web-developer-release",
            "configurePreset": "web-developer-release",
            "inherits": "build-unixlike-common",
            "configuration": "RelWithDebInfo"
        },
        {
            "name": "web-release",
            "configurePreset": "web-release",
            "inherits": "build-unixlike-common",
            "configuration": "Release"
        }
    ]
}

================================================
FILE: .clang-format
================================================

# clang-format version 14

Language : Cpp
Standard : Latest

AccessModifierOffset: -4
AlignAfterOpenBracket: AlwaysBreak
AlignArrayOfStructures: Right
AlignConsecutiveAssignments: AcrossComments
AlignConsecutiveBitFields: AcrossEmptyLinesAndComments
AlignConsecutiveDeclarations: AcrossComments
AlignConsecutiveMacros: AcrossComments
AlignEscapedNewlines: Right
AlignOperands: Align
AlignTrailingComments: true
AllowAllArgumentsOnNextLine: true
AllowAllParametersOfDeclarationOnNextLine: true
AllowShortBlocksOnASingleLine: Never
AllowShortCaseLabelsOnASingleLine: true
AllowShortEnumsOnASingleLine: true
AllowShortFunctionsOnASingleLine: None
AllowShortIfStatementsOnASingleLine: Never
AllowShortLambdasOnASingleLine: Inline
AllowShortLoopsOnASingleLine: false
AlwaysBreakAfterReturnType: None
AlwaysBreakBeforeMultilineStrings: false
AlwaysBreakTemplateDeclarations: Yes
BinPackArguments: true
BinPackParameters: true
BitFieldColonSpacing: Both
BreakAfterJavaFieldAnnotations: true
BreakBeforeBinaryOperators: None
BreakBeforeBraces: Allman
BreakBeforeConceptDeclarations: true
BreakBeforeTernaryOperators: true
BreakConstructorInitializers: BeforeColon
BreakInheritanceList: BeforeColon
BreakStringLiterals: false
ColumnLimit: 200
CompactNamespaces: true
ContinuationIndentWidth: 4
Cpp11BracedListStyle: false
DeriveLineEnding: true
DerivePointerAlignment: false
EmptyLineAfterAccessModifier: Leave
EmptyLineBeforeAccessModifier: LogicalBlock
FixNamespaceComments: false
IncludeBlocks: Preserve
IndentAccessModifiers: false
IndentCaseBlocks: true
IndentCaseLabels: true
IndentExternBlock: NoIndent
IndentGotoLabels: false
IndentPPDirectives: AfterHash
IndentRequires: false
IndentWidth: 4
IndentWrappedFunctionNames: true
KeepEmptyLinesAtTheStartOfBlocks: false
LambdaBodyIndentation: Signature
MaxEmptyLinesToKeep: 2
NamespaceIndentation: All
PPIndentWidth: -1
PackConstructorInitializers: BinPack
PointerAlignment: Left

# QualifierOrder: ['static', 'constexpr', 'inline', 'const', 'type' ]

ReferenceAlignment: Left
ReflowComments: true
SeparateDefinitionBlocks: Always
SortIncludes: CaseSensitive
SortUsingDeclarations: true
SpaceAfterCStyleCast: false
SpaceAfterLogicalNot: false
SpaceAfterTemplateKeyword: true
SpaceBeforeAssignmentOperators: true
SpaceBeforeCaseColon: false
SpaceBeforeCpp11BracedList: false
SpaceBeforeCtorInitializerColon: true
SpaceBeforeInheritanceColon: true
SpaceBeforeParens: ControlStatements
SpaceBeforeRangeBasedForLoopColon: true
SpaceBeforeSquareBrackets: false
SpaceInEmptyBlock: true
SpaceInEmptyParentheses: false
SpacesInAngles: Never
SpacesInCStyleCastParentheses: false
SpacesInConditionalStatement: false
SpacesInContainerLiterals: false
SpacesInParentheses: false
SpacesInSquareBrackets: false
TabWidth: 4
UseCRLF: false
UseTab: true

================================================
FILE: app_resources/web/index_shell.html
================================================
<!doctype html>

<html lang="en-us">

<head>
    <meta charset="utf-8">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <link rel="icon" href="https://www.digipen.edu/themes/custom/digipen_future/favicon.ico"
        type="image/vnd.microsoft.icon" />
    <title>DigiPen Programming Fun</title>
    <meta name="description" content="Computer Programming Fun for DigiPen classes">

    <meta name="viewport"
        content="width=device-width, initial-scale=1, maximum-scale=1, minimum-scale=1, user-scalable=no" />
    <meta name="mobile-web-app-capable" content="yes" />
    
    <meta http-equiv="Cache-Control" content="no-cache, no-store, must-revalidate" />
    <meta http-equiv="Pragma" content="no-cache" />
    <meta http-equiv="Expires" content="0" />
    
    <style>
        body {
            overflow-y: hidden;
            overflow-x: hidden;
            margin: 0;
            background-color: #FFFFFF;
            -webkit-font-smoothing: subpixel-antialiased;
            font-smoothing: subpixel-antialiased;
        }
    
        #main-container {
            font-size: 12px;
            font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif, "Apple Color Emoji", "Segoe UI Emoji", "Segoe UI Symbol";
        }
    
        .emscripten {
            padding: 0;
            margin: 0;
            display: block;
            width: 100%;
            height: 100%;
            background: transparent;
            background-color: #00000000;
        }
    
        canvas.emscripten {
            border: 0px none;
            background: transparent;
            background-color: #00000000;
        }
    
        #description {
            margin: 10px;
            padding: 10px;
            color: #000000;
        }
    </style>

</head>

<body>
    <div id="main-container">
        <div id="description" align="center">
            <h2>DigiPen Korea Graphics I</h2>

            <div id="container_status" align="center">
                Loading - please wait ..
            </div>
        </div>
        <canvas class="emscripten" id="canvas" oncontextmenu="event.preventDefault()" tabindex=-1></canvas>
    </div>
    
    <script type='text/javascript'>
        // Set background image via JavaScript
        function setBackgroundImage() {
            document.body.style.backgroundImage = "url('data:image/svg+xml;base64,\

PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbDpzcGFjZT0icHJlc2VydmUiIGFyaWEtbGFiZWxsZWRieT0ibG9nb190aXRsZSIgcHJlc2VydmVBc3BlY3RSYXRpbz0ieE1pbllNaW4gbWVldCIgdmlld0JveD0iMCAyOTAuNSA2MTMuNSAyMTEiPgogIDx0aXRsZT5EaWdpUGVuIEluc3RpdHV0ZSBvZiBUZWNobm9sb2d5PC90aXRsZT4KICA8cGF0aCBkPSJNMTEzLjMgMzk2LjZhMzcgMzcgMCAwIDAgMzcuNC0zNi43YzAtMjAtMTcuMS0zNi43LTM4LjEtMzYuN0g4NS4zdjczLjFoMjcuOHYuM2guMnptLTc0IDczLjZhMzcgMzcgMCAwIDEtMzcuNC0zNi42QTM3LjYgMzcuNiAwIDAgMSAzOS44IDM5N2gyNy4zdjczLjFIMzkuM3YuMXptMzIuMi0xNDcuMWg5Ljd2MTQ3LjFoLTkuN3ptMzE3LjEgMTguOGMwIDIuNi0yLjYgNC42LTUuNiA0LjZoLTE1Yy0zLjEgMC01LjYtMi4xLTUuNi00LjZ2LTcuN2MwLTIuNiAyLjYtNC42IDUuNi00LjZoMTVjMy4xIDAgNS42IDIuMSA1LjYgNC42djcuN3ptLTI2LjUgOC45aDI2LjV2NjMuNmgtMjYuNXptLTgwLjItOC45YzAgMi42LTIuNiA0LjYtNS42IDQuNmgtMTVjLTMuMSAwLTUuOC0yLjEtNS44LTQuNnYtNy43YzAtMi42IDIuNi00LjYgNS44LTQuNmgxNWMzLjEgMCA1LjYgMi4xIDUuNiA0LjZ2Ny43em0tMjYuNiA4LjloMjYuNXY2My42aC0yNi41ek00NzEuOCAzMzljLTMuMS01LTcuNS04LjktMTIuOC0xMS42YTQxLjQgNDEuNCAwIDAgMC0xOC42LTQuMUgzOTh2OTEuMmgyNi4zVjM4N2gxOC4zYzQuOCAwIDkuMS0uOSAxMy4yLTIuNiAzLjktMS43IDcuNy0zLjkgMTAuOS02LjggMy4xLTIuOSA1LjYtNi4yIDcuMi0xMC40IDEuNy0zLjkgMi42LTcgMi42LTExLjRhMzYuNyAzNi43IDAgMCAwLTQuNy0xNi44bS0zNS40IDI3LjJoLTEydi0yMS40aDExLjhjNiAwIDEwLjkgNC44IDEwLjkgMTAuNi40IDYtNC42IDEwLjgtMTAuNyAxMC44bTE3Mi45LTguNmEyMS4xIDIxLjEgMCAwIDAtOS42LTcuOSAzOC4xIDM4LjEgMCAwIDAtMTQuNC0yLjdoLTM5LjV2NjcuNWgyNi41di0zNy42YzAtNC44IDIuMS02LjggNi43LTYuOCA0LjggMCA2LjcgMi4xIDYuNyA2Ljh2MzcuOWgyNi41di00NC45Yy41LTQuNy0uNS05LTIuOS0xMi4zbS02OSAyOS40Yy4zLTIuMS43LTQuMy43LTYuNWEzMy41IDMzLjUgMCAwIDAtMzMuMS0zMy43Yy0xOC41IDAtMzMuMSAxNS0zMy4xIDMzLjcgMCAxOC42IDE0LjkgMzQgMzMuMSAzNCAxMi41IDAgMjMuNC03IDI4LjktMTcuNGgtMjIuOWMtNS44IDAtMTAuNi0xLjQtMTAuNi03LjVWMzg3aDM3em0tMzcuMS0xMy44di0xLjdjMC00LjggMy44LTguNyA4LjItOC43IDQuOCAwIDguMiAzLjkgOC4yIDguNXYxLjdsLTE2LjQuMnptLTIwNSA2OS4yaDIzLjdjNy4yIDAgMTMuOC0yLjYgMTkuMy02LjcgNy4yLTUuOCAxMi0xNC45IDEyLTI0Ljl2LTYxLjNoLTMwLjhhNDMgNDMgMCAwIDAtMTMuMiAyLjIgMzYgMzYgMCAwIDAtMTAuNiA2LjcgMzEuOCAzMS44IDAgMCAwIDMuOCA0OC41YzEgLjcgMS45IDEuMiAyLjcgMS45IDQuMSAyLjYgOC45IDMuOSAxMy43IDQuMWg3djEuNWMwIDEuNy0uMyAyLjYtMSAzLjItMS43IDIuNi01IDMuMi05LjEgMy4yaC0xOC4xYy42LjYuNiAyMS42LjYgMjEuNnptMjUuMS03Mi41aDcuNXYyMGgtNy43Yy01LjYgMC0xMC4xLTQuNi0xMC4xLTkuOSAwLTUuNiA0LjUtMTAuMSAxMC4zLTEwLjFtLTgxLjUtMjMuNGMtNC4xLTctOS43LTEyLjYtMTcuMS0xNi43LTctNC4xLTE0LjktNi4yLTIyLjktNi4yaC0zNi4xdjkwLjdoMzcuNGM1LjMgMCAxMC45LTEuMiAxNi43LTMuOGE1NCA1NCAwIDAgMCAxNC45LTkuNyA0MSA0MSAwIDAgMCA5LjktMTQuNyA0NS41IDQ1LjUgMCAwIDAgMy4yLTE3LjFjLjUtNy44LTEuNi0xNS4zLTYtMjIuNW0tMjEuOSAyOC45Yy0xIDIuMS0yLjIgMy45LTMuOSA1LjZhMTcuMiAxNy4yIDAgMCAxLTUuOCAzLjhjLTIuMiAxLTQuMyAxLjQtNi41IDEuNGgtMTIuOHYtMzQuN0gyMDNjMy4xIDAgNi4yLjkgOC45IDIuNiAyLjcgMS43IDUgMy44IDYuNyA2LjVzMi42IDUuNiAyLjYgOC43Yy4zIDEuOC0uNCA0LjEtMS4zIDYuMW0tNTMuNSA3NC4zaDIuOVY0NzBoLTIuOXptMjguMiAwaC0yLjR2MTUuOGwtMTMuNi0xNS44aC0yLjR2MjAuMmgyLjV2LTE1LjRsMTMuNyAxNS40aDIuMnptMTcgMS4yYTcuNiA3LjYgMCAwIDAtNC42LTEuNGMtMy44IDAtNi4yIDIuMS02LjIgNS4zIDAgNS4zIDguNyA2IDguNyAxMC4xIDAgMS0xIDIuNi0zLjIgMi42LTEuOSAwLTMuOS0xLTUuMy0yLjl2My44YTkuNyA5LjcgMCAwIDAgNS42IDEuOWMzLjIgMCA1LjYtMi4yIDUuNi01LjMgMC02LjUtOC43LTYuNS04LjctMTAuNCAwLTEuNCAxLjItMi42IDMuMi0yLjYgMS4yIDAgMy4xLjMgNC44IDIuMWwuMS0zLjJ6bTIxLjMtMS4yaC0xNi43djIuNmg2Ljh2MTcuNmgyLjl2LTE3LjZoN3ptNS41IDBoMi45VjQ3MGgtMi45em0yNC45IDBoLTE2Ljl2Mi42aDd2MTcuNmgyLjl2LTE3LjZoN3ptMjIuMiAwaC0yLjl2MTEuOGMwIDEuOS0uMiAzLjItMS4yIDQuMy0xIDEtMi42IDEuNy00LjggMS43LTEuOSAwLTMuMi0uMy00LjMtMS45LTEtMS0xLjItMS45LTEuMi00LjF2LTEyaC0yLjl2MTIuNmMwIDUuMyA0LjEgNy45IDguMiA3LjkgNiAwIDkuMS0zLjIgOS4xLTguMnYtMTIuMXptMjEuNyAwaC0xNi45djIuNmg3djE3LjZoMi45di0xNy42aDd6bTE2LjYgMGgtMTEuNHYyMC4yaDExLjd2LTIuNmgtOC44VjQ2MWg4LjN2LTIuNmgtOC4zdi02LjFoOC41em0xOC42IDEwLjFjMC00LjYgMy4yLTcuNyA3LjktNy43IDQuNiAwIDcuOSAzLjIgNy45IDcuNyAwIDQuMy0zLjIgNy43LTcuOSA3LjdhNy42IDcuNiAwIDAgMS03LjktNy43bS0yLjkgMGMwIDUuMyA0LjEgMTAuNCAxMC44IDEwLjQgNi44IDAgMTAuOS01IDEwLjktMTAuNCAwLTUuNi00LjEtMTAuNC0xMC45LTEwLjQtNi41LjItMTAuOCA0LjgtMTAuOCAxMC40bTM4LjUtMTAuMWgtMTAuOHYyMC4yaDIuOXYtOS4yaDcuOXYtMi44aC03Ljl2LTUuNmg3Ljl6bTI3LjggMGgtMTYuOXYyLjZoN3YxNy42aDIuOXYtMTcuNmg3em0xNi42IDBoLTExLjN2MjAuMmgxMS44di0yLjZINDE0VjQ2MWg4LjR2LTIuNkg0MTR2LTYuMWg4LjR6bTIzLjQgMS40Yy0yLjctMS00LjgtMS43LTYuOC0xLjctNi41IDAtMTEuMSA0LjYtMTEuMSAxMC42IDAgNC4xIDMuMiAxMC4xIDEwLjkgMTAuMSAzLjIgMCA1LjMtLjkgNy41LTEuOVY0NjVhMTMuNyAxMy43IDAgMCAxLTcgMi4yYy00LjggMC04LjItMy4xLTguMi03LjdzMy4yLTcuNyA4LTcuN2MyLjYgMCA0LjYuNyA2LjggMi4xdi0yLjdoLS4xem0yMy4xLTEuNGgtMi44djguOWgtMTEuNHYtOC45aC0yLjl2MjAuMmgyLjl2LTguNmgxMS40djguNmgyLjh6bTI1LjggMGgtMi44djE1LjhsLTEzLjYtMTUuOEg0NzZ2MjAuMmgyLjZ2LTE1LjRsMTMuNyAxNS40aDIuNHptOSAxMC4xYzAtNC42IDMuMi03LjcgNy45LTcuN3M3LjkgMy4yIDcuOSA3LjdjMCA0LjMtMy4yIDcuNy03LjkgNy43YTcuNSA3LjUgMCAwIDEtNy45LTcuN20tMi45IDBjMCA1LjMgNC4xIDEwLjQgMTAuOCAxMC40IDYuOCAwIDEwLjktNSAxMC45LTEwLjQgMC01LjYtNC4xLTEwLjQtMTAuOC0xMC40LTYuOC4yLTEwLjkgNC44LTEwLjkgMTAuNG0zMC42LTEwLjFoLTIuOXYyMC4yaDExLjl2LTIuNmgtOXptMTYuMSAxMC4xYzAtNC42IDMuMi03LjcgNy45LTcuN3M3LjkgMy4yIDcuOSA3LjdjMCA0LjMtMy4yIDcuNy03LjkgNy43YTcuNiA3LjYgMCAwIDEtNy45LTcuN20tMyAwYzAgNS4zIDQuMSAxMC40IDEwLjggMTAuNCA2LjggMCAxMC45LTUgMTAuOS0xMC40IDAtNS42LTQuMS0xMC40LTEwLjgtMTAuNC02LjYgMC0xMC45IDQuOC0xMC45IDEwLjRtNDUuNy4yaC02Ljh2Mi42aDMuOXY0LjFjLTEuNC4zLTIuNy45LTQuMy45LTQuOCAwLTguMi0zLjItOC4yLTcuNyAwLTQuMyAzLjItNy43IDcuOS03LjcgMi42IDAgNC44LjcgNy4yIDEuOXYtMi45Yy0zLjItMS4yLTQuOC0xLjktNy4yLTEuOS02LjIgMC0xMC44IDQuNi0xMC44IDEwLjZzNC42IDEwLjQgMTAuOCAxMC40YzIuNyAwIDUtLjMgNy43LTEuN1Y0NjBoLS4yem0xMy4zLTMuMy01LjUtN2gtMy42bDcuNyA5LjR2MTAuOGgyLjl2LTEwLjRsNy40LTkuOEg2MDl6Ii8+Cjwvc3ZnPgo=')";
            document.body.style.backgroundRepeat = "no-repeat";
            document.body.style.backgroundPosition = "center center";
            document.body.style.backgroundAttachment = "fixed";
            document.body.style.backgroundSize = "contain";
        }

        // Remove background image when Emscripten is loaded
        function removeBackgroundImage() {
            document.body.style.backgroundImage = "none";
        }
    
        // Set background image on page load
        setBackgroundImage();
    
        var isInitialized = false;
        var failedToInitialize = false;
    
        function updateWindowSize() {
            var w = window,
                d = document,
                e = d.documentElement,
                g = d.getElementsByTagName('body')[0],
                x = w.innerWidth || e.clientWidth || g.clientWidth,
                y = w.innerHeight || e.clientHeight || g.clientHeight;
            Module.setWindowSize(x, y);
        }
    
        window.setInterval(function () {
            if (isInitialized == false) return;
    
            updateWindowSize();
    
        }, 500);
    
        function onkeydown(event) {
            if (event.ctrlKey ||
                (event.keyCode >= 112 && event.keyCode <= 123)) {
                event.stopImmediatePropagation();
                return;
            }
    
            if (event.keyCode == 8 || // Backspace
                event.keyCode == 9 || // Tab
                event.keyCode == 46 || // Delete
                (event.keyCode >= 37 && event.keyCode <= 40)) { // Arrow keys
                event.preventDefault();
            }
        }
    
        function init() {
            document.getElementById('container_status').innerHTML = "WebAssembly module initialized successfully!"
            document.getElementById('container_status').style.color = "#00ff00";
    
            window.addEventListener('keydown', onkeydown, true);
            // This enables our app to get keyboard focus when displayed through an iframe
            // https://supernapie.com/blog/keyboard-focus-in-an-iframe/
            window.addEventListener('load', function () {
                window.focus();
                document.body.addEventListener('click', function (e) {
                    window.focus();
                }, false);
            });
    
            if (isInitialized == false) {
                updateWindowSize();
                isInitialized = true;
            }
            {
                var status = document.getElementById("description");
                status.hidden = true;
            }
    
            // Remove background image once Emscripten is fully loaded and displaying
            removeBackgroundImage();
        }
    
        function getQueryParam(parameterName) {
            const queryParams = new URLSearchParams(window.location.search);
            return queryParams.get(parameterName);
        }
    
        function buildCommandLineArguments() {
            var param = getQueryParam('start')
            if (param)
                return ['--start', param]
            return []
        }
    
        var Module = {
            arguments: buildCommandLineArguments(),
            preRun: [(function () { })],
            postRun: [(function () {
                if (failedToInitialize) return;
                init();
            })],
            canvas: (function () {
                var canvas = document.getElementById('canvas');
                canvas.addEventListener("webglcontextlost", function (e) {
                    alert('WebGL context lost. You will need to reload the page.'); e.preventDefault();
                }, false);
                return canvas;
            })(),
            print: function (text) {
                text = Array.prototype.slice.call(arguments).join(' ');
                console.log(text);
            },
            printErr: function (text) {
                text = Array.prototype.slice.call(arguments).join(' ');
                console.error(text);
            },
            setStatus: function (text) {
                if (text) {
                    console.log("html module status: " + text);
                }
            }
        };
    
        window.onerror = function (event) {
            failedToInitialize = true;
            let reason = JSON.stringify(event);
            console.log("onerror: " + reason);
            document.getElementById('container_status').innerHTML = reason;
            document.getElementById('container_status').innerHTML += '<br>This browser is not supported. Please try a different browser';
            document.getElementById('container_status').style.color = "#ff0000";
        };
    </script>
    
    {{{ SCRIPT }}}

</body>

</html>

================================================
FILE: Assets/animations/None.anm
================================================
PlayFrame 0 10
Loop 0

================================================
FILE: Assets/animations/CS230_Final/PassengerAngry.anm
================================================
PlayFrame 3 0.7
PlayFrame 4 0.7
PlayFrame 3 0.7
PlayFrame 5 0.7
Loop 0

================================================
FILE: Assets/animations/CS230_Final/PassengerIdle.anm
================================================
PlayFrame 0 0.7
PlayFrame 1 0.7
PlayFrame 0 0.7
PlayFrame 2 0.7
Loop 0

================================================
FILE: Assets/animations/CS230_Final/PassengerSad.anm
================================================
PlayFrame 6 0.7
PlayFrame 7 0.7
PlayFrame 6 0.7
PlayFrame 8 0.7
Loop 0

================================================
FILE: Assets/animations/CS230_Final/Shining.anm
================================================
PlayFrame 0 1.0
PlayFrame 1 .1
PlayFrame 2 .1
PlayFrame 3 .1
PlayFrame 4 10
End

================================================
FILE: Assets/animations/CS230_Final/Tears.anm
================================================
PlayFrame 0 1.0
PlayFrame 1 .1
PlayFrame 2 .1
PlayFrame 3 .1
PlayFrame 4 4
End

================================================
FILE: Assets/animations/DemoSceneShowcase/Flame.anm
================================================
PlayFrame 0 0.4
PlayFrame 1 0.3
PlayFrame 2 0.4
PlayFrame 3 0.25
End

================================================
FILE: Assets/animations/DemoSceneShowcase/MeteorBit.anm
================================================
PlayFrame 0 1.0
PlayFrame 1 .1
PlayFrame 2 .1
PlayFrame 3 .1
PlayFrame 4 20
End

================================================
FILE: Assets/animations/DemoSceneShowcase/SamuraiRun.anm
================================================
PlayFrame 0 0.05
PlayFrame 1 0.05
PlayFrame 2 0.05
PlayFrame 3 0.05
PlayFrame 4 0.05
PlayFrame 5 0.05
PlayFrame 6 0.05
PlayFrame 7 0.05
PlayFrame 8 0.05
PlayFrame 9 0.05
PlayFrame 10 0.05
PlayFrame 11 0.05
PlayFrame 12 0.05
PlayFrame 13 0.05
PlayFrame 14 0.05
PlayFrame 15 0.05
Loop 0

================================================
FILE: Assets/Data/characters.json
================================================
{
  "Dragon": {
    "maxHP": 140,
    "speed": 5,
    "maxActionPoints": 2,
    "baseAttackPower": 0,
    "attackDice": "3d6",
    "baseDefensePower": 0,
    "defenseDice": "2d8",
    "attackRange": 3,
    "spellSlots": {
      "1": 4,
      "2": 3,
      "3": 2,
      "4": 2,
      "5": 1
    }
  },
  "Fighter": {
    "maxHP": 90,
    "speed": 3,
    "maxActionPoints": 2,
    "baseAttackPower": 5,
    "attackDice": "2d6",
    "baseDefensePower": 0,
    "defenseDice": "1d10",
    "attackRange": 1,
    "spellSlots": {
      "1": 2,
      "2": 2
    }
  }
}

================================================
FILE: Assets/shaders/basic_vtx_clr_attribute.frag
================================================
#version 300 es
precision mediump float;

/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

in vec3 vColor;

layout(location = 0) out vec4 FragColor;

void main()
{
    FragColor = vec4(vColor, 1.0);
}

================================================
FILE: Assets/shaders/pass_thru_pos2d_clr.vert
================================================
#version 300 es

/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vColor;

void main()
{
    gl_Position = vec4(aVertexPosition, 0.0, 1.0);
    vColor      = aVertexColor;
}

================================================
FILE: Assets/shaders/BatchRenderer2D/quad.frag
================================================
#version 300 es
/*****/
precision mediump float;

/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

//every GPU have different amount limit of texture
//have to ask to OpenGL, in fragment shader, programically
#ifndef MAX_TEXTURE_SLOTS
#define MAX_TEXTURE_SLOTS 8// we will ask opengl programically
#endif

uniform sampler2D uTextures[MAX_TEXTURE_SLOTS];//'' : array size must be a constant integer expression

in vec2 vTexCoord;
flat in vec4 vTint;
flat in int vTextureIndex;
layout(location=0)out vec4 FragColor;

void main()
{
    // FragColor = texture(uTextures[vTextureIndex], vTexCoord) * vTint;
    //300es version need to use constexpr index so..
    vec4 tex_color;

    switch(vTextureIndex){
        case 0:tex_color=texture(uTextures[0],vTexCoord);break;
    
        case 1:tex_color=texture(uTextures[1],vTexCoord);break;
    
        #if MAX_TEXTURE_SLOTS>2
        case 2:tex_color=texture(uTextures[2],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>3
        case 3:tex_color=texture(uTextures[3],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>4
        case 4:tex_color=texture(uTextures[4],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>5
        case 5:tex_color=texture(uTextures[5],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>6
        case 6:tex_color=texture(uTextures[6],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>7
        case 7:tex_color=texture(uTextures[7],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>8
        case 8:tex_color=texture(uTextures[8],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>9
        case 9:tex_color=texture(uTextures[9],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>10
        case 10:tex_color=texture(uTextures[10],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>11
        case 11:tex_color=texture(uTextures[11],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>12
        case 12:tex_color=texture(uTextures[12],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>13
        case 13:tex_color=texture(uTextures[13],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>14
        case 14:tex_color=texture(uTextures[14],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>15
        case 15:tex_color=texture(uTextures[15],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>16
        case 16:tex_color=texture(uTextures[16],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>17
        case 17:tex_color=texture(uTextures[17],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>18
        case 18:tex_color=texture(uTextures[18],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>19
        case 19:tex_color=texture(uTextures[19],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>20
        case 20:tex_color=texture(uTextures[20],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>21
        case 21:tex_color=texture(uTextures[21],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>22
        case 22:tex_color=texture(uTextures[22],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>23
        case 23:tex_color=texture(uTextures[23],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>24
        case 24:tex_color=texture(uTextures[24],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>25
        case 25:tex_color=texture(uTextures[25],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>26
        case 26:tex_color=texture(uTextures[26],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>27
        case 27:tex_color=texture(uTextures[27],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>28
        case 28:tex_color=texture(uTextures[28],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>29
        case 29:tex_color=texture(uTextures[29],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>30
        case 30:tex_color=texture(uTextures[30],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>31
        case 31:tex_color=texture(uTextures[31],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>32
        case 32:tex_color=texture(uTextures[32],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>33
        case 33:tex_color=texture(uTextures[33],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>34
        case 34:tex_color=texture(uTextures[34],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>35
        case 35:tex_color=texture(uTextures[35],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>36
        case 36:tex_color=texture(uTextures[36],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>37
        case 37:tex_color=texture(uTextures[37],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>38
        case 38:tex_color=texture(uTextures[38],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>39
        case 39:tex_color=texture(uTextures[39],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>40
        case 40:tex_color=texture(uTextures[40],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>41
        case 41:tex_color=texture(uTextures[41],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>42
        case 42:tex_color=texture(uTextures[42],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>43
        case 43:tex_color=texture(uTextures[43],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>44
        case 44:tex_color=texture(uTextures[44],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>45
        case 45:tex_color=texture(uTextures[45],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>46
        case 46:tex_color=texture(uTextures[46],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>47
        case 47:tex_color=texture(uTextures[47],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>48
        case 48:tex_color=texture(uTextures[48],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>49
        case 49:tex_color=texture(uTextures[49],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>50
        case 50:tex_color=texture(uTextures[50],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>51
        case 51:tex_color=texture(uTextures[51],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>52
        case 52:tex_color=texture(uTextures[52],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>53
        case 53:tex_color=texture(uTextures[53],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>54
        case 54:tex_color=texture(uTextures[54],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>55
        case 55:tex_color=texture(uTextures[55],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>56
        case 56:tex_color=texture(uTextures[56],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>57
        case 57:tex_color=texture(uTextures[57],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>58
        case 58:tex_color=texture(uTextures[58],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>59
        case 59:tex_color=texture(uTextures[59],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>60
        case 60:tex_color=texture(uTextures[60],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>61
        case 61:tex_color=texture(uTextures[61],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>62
        case 62:tex_color=texture(uTextures[62],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>63
        case 63:tex_color=texture(uTextures[63],vTexCoord);break;
        #endif
    }
    tex_color*=vTint;
    
    FragColor=tex_color;
    
    if(FragColor.a==0.)
    discard;

}

================================================
FILE: Assets/shaders/BatchRenderer2D/quad.vert
================================================
#version 300 es

/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

layout(location = 0) in vec2 aWorldPosition;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec4 aTint;
layout(location = 3) in int aTextureIndex;
layout(location = 4) in float aDepth;

out vec2 vTexCoord;
//by default, any output variable interpolated
//but vTint has to be same across the triangle(for each pixels)
//so put flat
flat out vec4 vTint;
flat out int vTextureIndex;

// uniform mat3 uModel; //get rid of it so that cpu do this 
// uniform mat3 uToNDC; //instead using uniformblock
layout(std140) uniform NDC
{
    mat3 uToNDC;
};

// uniform mat3 uTexCoordTransform; //get rid of it so that cpu do this 

/**
why give model xform task to CPU?
we have lots of vertex(duplicated)
it is more 
*/

void main()
{
    vec3 ndc_point = uToNDC * /* uModel * */ vec3(aWorldPosition, 1.0); //we assume that vertex position is already in world space(we dont need model xformation)
    gl_Position = vec4(ndc_point.xy, aDepth, 1.0);
    vTexCoord = aTexCoord.st;//don't need texcoord xform anymore, just copy
    vTint = aTint;
    vTextureIndex = aTextureIndex;
}

================================================
FILE: Assets/shaders/BatchRenderer2D/sdf.frag
================================================
#version 300 es
precision mediump float;

/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
* (Batch Renderer Version)
  */

// 1. Receive all uniforms as 'in' variables
in vec2 vTestPoint;
flat in vec4 vFillColor;
flat in vec4 vLineColor;
flat in vec2 vWorldSize;
flat in float vLineWidth;
flat in int vShape;

layout(location = 0) out vec4 FragColor;

// --- sdCircle, sdRectangle functions are identical to the original ---
float sdCircle( vec2 p, float r )
{
    return length(p) - r;
}

float sdRectangle( vec2 point, vec2 half_dim )
{
    vec2 d = abs(point)-half_dim;
    return length(max(d,0.0)) + min(max(d.x,d.y),0.0);
}

// 2. Modify evalute_color function to use 'v' (in) variables instead of uniforms
vec4 evalute_color(float sdf)
{
    float fill_alpha = (sdf < 0.0) ? 1.0 : 0.0;
    // 'uLineWidth' -> 'vLineWidth'
    float outline_alpha = (abs(sdf) < vLineWidth * 0.5) ? 1.0 : 0.0; 

    // 'uFillColor' -> 'vFillColor'
    vec4 fill_color = vec4(vFillColor.rgb, fill_alpha * vFillColor.a);
    // 'uLineColor' -> 'vLineColor'
    vec4 line_color = vec4(vLineColor.rgb, outline_alpha * vLineColor.a);
    
    return mix(fill_color,line_color,line_color.a);

}

void main()
{
    float sdf = 0.0;

    // 3. Check 'vShape' (from vertex) instead of 'uShape' (uniform)
    if(vShape == 0){ // This pixel belongs to a Circle
        // 'uWorldSize' -> 'vWorldSize'
        float radius = min(vWorldSize.x ,vWorldSize.y) * 0.5; 
        sdf = sdCircle(vTestPoint, radius);
    }
    else if(vShape == 1){ // This pixel belongs to a Rectangle
        // 'uWorldSize' -> 'vWorldSize'
        sdf = sdRectangle(vTestPoint, 0.5 * vWorldSize); 
    }
    
    vec4 color = evalute_color(sdf);
    if(color.a <= 0.0 )
        discard;
    FragColor = color;

}

================================================
FILE: Assets/shaders/BatchRenderer2D/sdf.vert
================================================
#version 300 es

/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
* (Batch Renderer Version)
  */

// 1. Receive all per-object data as attributes
layout(location = 0) in vec2 aWorldPosition;  // World coordinates calculated on the CPU
layout(location = 1) in vec2 aTestPoint;      // vTestPoint calculated on the CPU
layout(location = 2) in vec4 aFillColor;
layout(location = 3) in vec4 aLineColor;
layout(location = 4) in vec2 aWorldSize;
layout(location = 5) in float aLineWidth;
layout(location = 6) in int aShape;
layout(location = 7) in float aDepth;

// 2. Common UBO (Camera)
layout(std140) uniform NDC
{
    mat3 uToNDC;
};

// 3. Variables to pass to the Fragment Shader
out vec2 vTestPoint;
flat out vec4 vFillColor;
flat out vec4 vLineColor;
flat out vec2 vWorldSize;
flat out float vLineWidth;
flat out int vShape;

void main()
{
    // 4. Use the pre-calculated aWorldPosition, same as the Batch Texture Shader
    vec3 ndc_point = uToNDC * vec3(aWorldPosition, 1.0); 
    gl_Position = vec4(ndc_point.xy, aDepth, 1.0);

    // 5. Pass all attributes directly to the Fragment Shader
    vTestPoint = aTestPoint;
    vFillColor = aFillColor;
    vLineColor = aLineColor;
    vWorldSize = aWorldSize;
    vLineWidth = aLineWidth;
    vShape = aShape;

}

================================================
FILE: Assets/shaders/DemoBufferTypes/background.frag
================================================
#version 300 es
precision mediump float;

/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

in vec3 vColor;

layout(location = 0) out vec4 FragColor;

void main()
{
    FragColor = vec4(vColor, 1.0);
}

================================================
FILE: Assets/shaders/DemoBufferTypes/background.vert
================================================
#version 300 es

/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vColor;

layout(std140) uniform NDC
{
    mat3 uToNDC;
};

void main()
{
    gl_Position = vec4((uToNDC * vec3(aVertexPosition, 1.0)).xy, 0.0, 1.0);
    vColor      = aVertexColor;
}

================================================
FILE: Assets/shaders/DemoBufferTypes/villager.frag
================================================
#version 300 es
precision mediump float;

/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

in vec3 vColor;

layout(location = 0) out vec4 FragColor;

void main()
{
    FragColor = vec4(vColor, 1.0);
}

================================================
FILE: Assets/shaders/DemoBufferTypes/villager.vert
================================================
#version 300 es

/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

layout(std140) uniform NDC
{
    mat3 uToNDC;
};

uniform mat3 uModel;

out vec3 vColor;

void main()
{
    vec3 ndc_point = uToNDC * uModel * vec3(aVertexPosition, 1.0);
    gl_Position    = vec4(ndc_point.xy, 0.0, 1.0);
    vColor         = aVertexColor;
}

================================================
FILE: Assets/shaders/DemoTexturing/combine.frag
================================================
#version 300 es
precision mediump float;

/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

in vec3 vColor;
in vec2 vTextureCoordinates;

layout(location = 0) out vec4 fFragClr;

uniform sampler2D uTex2d;
uniform float     uModulateColor;
uniform float     uProcTex;
uniform float     uTileSize;
uniform float     uUseImage;
uniform bool      uUseTextureAlpha;

const vec4 cyan = vec4(1.0, 0.0, 1.0, 1.0);
const vec4 teal = vec4(0.0, 0.68, 0.94, 1.0);

void main()
{
    vec4 interpolated_color = mix(vec4(1.0), vec4(vColor, 1.0), uModulateColor);
    vec4 procedural_color   = mix(vec4(1.0), (0.0 == mod(floor(gl_FragCoord.x / uTileSize) + floor(gl_FragCoord.y / uTileSize), 2.0)) ? cyan : teal, uProcTex);
    vec4 texture_color      = mix(vec4(1.0), texture(uTex2d, vTextureCoordinates), uUseImage);
    if (!uUseTextureAlpha)
    {
        texture_color.a = 1.0;
    }

    fFragClr = interpolated_color * procedural_color * texture_color;

}

================================================
FILE: Assets/shaders/DemoTexturing/combine.vert
================================================
#version 300 es

/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;
layout(location = 2) in vec2 aVertexTextureCoordinates;

out vec3 vColor;
out vec2 vTextureCoordinates;

uniform float uTexCoordScale;

uniform mat3 uToNDC;
uniform mat3 uModel;

void main()
{
    vec3 ndc_position   = uToNDC * uModel * vec3(aVertexPosition, 1.0);
    gl_Position         = vec4(ndc_position.xy, 0.0, 1.0);
    vColor              = aVertexColor;
    vTextureCoordinates = aVertexTextureCoordinates * uTexCoordScale;
}

================================================
FILE: Assets/shaders/ImmediateRenderer2D/quad.frag
================================================
#version 300 es
precision         mediump float;

/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

uniform sampler2D uTex2d;

in vec2 vTexCoord;

layout(location = 0) out vec4 fFragClr;

uniform vec4 uTint; //  cover with new color

//use all variable!!!!!!!!!!!!!!
void main()
{
    fFragClr = texture(uTex2d, vTexCoord) * uTint;

    if(fFragClr.a == 0.0)
    discard;

}

================================================
FILE: Assets/shaders/ImmediateRenderer2D/quad.vert
================================================
#version 300 es

/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aTexCoord;

out vec2 vTexCoord;

layout(std140) uniform NDC
{
    mat3 uToNDC;
};

uniform mat3 uModel;
uniform mat3 uTexCoordTransform; //for drawing just part of image
uniform float uDepth;

void main()
{
    vec3 ndc_position   = uToNDC * uModel * vec3(aVertexPosition, 1.0);
    gl_Position         = vec4(ndc_position.xy, uDepth, 1.0);
    vec3 tex_coords = uTexCoordTransform * vec3(aTexCoord,1.0);
    vTexCoord = tex_coords.st ;
}

================================================
FILE: Assets/shaders/ImmediateRenderer2D/sdf.frag
================================================
#version 300 es
precision mediump float;

/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

in vec2 vTestPoint;

layout(location = 0) out vec4 FragColor;

uniform vec4 uFillColor;
uniform vec4 uLineColor;
uniform vec2 uWorldSize;
uniform float uLineWidth;
uniform int uShape;

float sdCircle( vec2 p, float r )
{
    return length(p) - r;
}

float sdRectangle( vec2 point, vec2 half_dim )
{
    vec2 d = abs(point)-half_dim;
    return length(max(d,0.0)) + min(max(d.x,d.y),0.0);
}

//evalute the color based off sdf
vec4 evalute_color(float sdf)
{
    float fill_alpha = (sdf < 0.0) ? 1.0 : 0.0;
    float outline_alpha = (abs(sdf) < uLineWidth * 0.5) ? 1.0 : 0.0;

    vec4 fill_color = vec4(uFillColor.rgb, fill_alpha * uFillColor.a);//modulate,mix
    vec4 line_color = vec4(uLineColor.rgb, outline_alpha * uLineColor.a);//modulate,mix
    
    return mix(fill_color,line_color,line_color.a);

}

void main()
{
    //based off shape evaluate the sdf
    float sdf = 0.0;
    if(uShape == 0){
        float radius = min(uWorldSize.x ,uWorldSize.y) * 0.5;
        sdf = sdCircle(vTestPoint, radius);
    }
    else if(uShape == 1){
        sdf = sdRectangle(vTestPoint, 0.5 * uWorldSize);
    }

    //get the color
    vec4 color = evalute_color(sdf);
    if(color.a <= 0.0 )
        discard;
    //set color, discard empty space
    FragColor = color;

}

================================================
FILE: Assets/shaders/ImmediateRenderer2D/sdf.vert
================================================
#version 300 es

/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

layout(location = 0) in vec2 aVertexPosition;

uniform mat3 uModel;
layout(std140) uniform NDC
{
    mat3 uToNDC;
};
uniform vec2 uSDFScale;

out vec2 vTestPoint;

uniform float uDepth;
void main()
{
    vec3 ndc_point = uToNDC * uModel * vec3(aVertexPosition,1.0);
    gl_Position = vec4(ndc_point.xy, uDepth, 1.0);
    vTestPoint = aVertexPosition * uSDFScale; //scale
}

================================================
FILE: Assets/shaders/InstancedRenderer2D/quad.frag
================================================
#version 300 es
/*****/
precision mediump float;

/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

//every GPU have different amount limit of texture
//have to ask to OpenGL, in fragment shader, programically
#ifndef MAX_TEXTURE_SLOTS
#define MAX_TEXTURE_SLOTS 8// we will ask opengl programically
#endif

uniform sampler2D uTextures[MAX_TEXTURE_SLOTS];//'' : array size must be a constant integer expression
// we have to treat this uTextures as MAX_TEXTURE_SLOTS uniform variables
//have to set their binding index

in vec2 vTexCoord;
flat in vec4 vTint;
flat in int vTextureIndex;
layout(location=0)out vec4 FragColor;

void main()
{
    // FragColor = texture(uTextures[vTextureIndex], vTexCoord) * vTint;
    //300es version need to use constexpr index so..
    vec4 tex_color;

    switch(vTextureIndex){
        case 0:tex_color=texture(uTextures[0],vTexCoord);break;
    
        case 1:tex_color=texture(uTextures[1],vTexCoord);break;
    
        #if MAX_TEXTURE_SLOTS>2
        case 2:tex_color=texture(uTextures[2],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>3
        case 3:tex_color=texture(uTextures[3],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>4
        case 4:tex_color=texture(uTextures[4],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>5
        case 5:tex_color=texture(uTextures[5],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>6
        case 6:tex_color=texture(uTextures[6],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>7
        case 7:tex_color=texture(uTextures[7],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>8
        case 8:tex_color=texture(uTextures[8],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>9
        case 9:tex_color=texture(uTextures[9],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>10
        case 10:tex_color=texture(uTextures[10],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>11
        case 11:tex_color=texture(uTextures[11],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>12
        case 12:tex_color=texture(uTextures[12],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>13
        case 13:tex_color=texture(uTextures[13],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>14
        case 14:tex_color=texture(uTextures[14],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>15
        case 15:tex_color=texture(uTextures[15],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>16
        case 16:tex_color=texture(uTextures[16],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>17
        case 17:tex_color=texture(uTextures[17],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>18
        case 18:tex_color=texture(uTextures[18],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>19
        case 19:tex_color=texture(uTextures[19],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>20
        case 20:tex_color=texture(uTextures[20],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>21
        case 21:tex_color=texture(uTextures[21],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>22
        case 22:tex_color=texture(uTextures[22],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>23
        case 23:tex_color=texture(uTextures[23],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>24
        case 24:tex_color=texture(uTextures[24],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>25
        case 25:tex_color=texture(uTextures[25],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>26
        case 26:tex_color=texture(uTextures[26],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>27
        case 27:tex_color=texture(uTextures[27],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>28
        case 28:tex_color=texture(uTextures[28],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>29
        case 29:tex_color=texture(uTextures[29],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>30
        case 30:tex_color=texture(uTextures[30],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>31
        case 31:tex_color=texture(uTextures[31],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>32
        case 32:tex_color=texture(uTextures[32],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>33
        case 33:tex_color=texture(uTextures[33],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>34
        case 34:tex_color=texture(uTextures[34],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>35
        case 35:tex_color=texture(uTextures[35],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>36
        case 36:tex_color=texture(uTextures[36],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>37
        case 37:tex_color=texture(uTextures[37],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>38
        case 38:tex_color=texture(uTextures[38],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>39
        case 39:tex_color=texture(uTextures[39],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>40
        case 40:tex_color=texture(uTextures[40],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>41
        case 41:tex_color=texture(uTextures[41],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>42
        case 42:tex_color=texture(uTextures[42],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>43
        case 43:tex_color=texture(uTextures[43],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>44
        case 44:tex_color=texture(uTextures[44],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>45
        case 45:tex_color=texture(uTextures[45],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>46
        case 46:tex_color=texture(uTextures[46],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>47
        case 47:tex_color=texture(uTextures[47],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>48
        case 48:tex_color=texture(uTextures[48],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>49
        case 49:tex_color=texture(uTextures[49],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>50
        case 50:tex_color=texture(uTextures[50],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>51
        case 51:tex_color=texture(uTextures[51],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>52
        case 52:tex_color=texture(uTextures[52],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>53
        case 53:tex_color=texture(uTextures[53],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>54
        case 54:tex_color=texture(uTextures[54],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>55
        case 55:tex_color=texture(uTextures[55],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>56
        case 56:tex_color=texture(uTextures[56],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>57
        case 57:tex_color=texture(uTextures[57],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>58
        case 58:tex_color=texture(uTextures[58],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>59
        case 59:tex_color=texture(uTextures[59],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>60
        case 60:tex_color=texture(uTextures[60],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>61
        case 61:tex_color=texture(uTextures[61],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>62
        case 62:tex_color=texture(uTextures[62],vTexCoord);break;
        #endif
        #if MAX_TEXTURE_SLOTS>63
        case 63:tex_color=texture(uTextures[63],vTexCoord);break;
        #endif
    }
    tex_color*=vTint;
    
    FragColor=tex_color;
    
    if(FragColor.a==0.)
    discard;

}

================================================
FILE: Assets/shaders/InstancedRenderer2D/quad.vert
================================================
#version 300 es

/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

//per vertex
layout(location = 0) in vec2 aModelPosition;
layout(location = 1) in vec2 aTexCoord;

//per instance
layout(location = 2) in vec3 aModelRow0;
layout(location = 3) in vec3 aModelRow1;
layout(location = 4) in vec4 aTint;
layout(location = 5) in vec2 aTexCoordScale;
layout(location = 6) in vec2 aTexCoordOffset;
layout(location = 7) in int  aTextureIndex;
layout(location = 8) in float aDepth;

out vec2 vTexCoord;
//by default, any output variable interpolated
//but vTint has to be same across the triangle(for each pixels)
//so put flat
flat out vec4 vTint;
flat out int vTextureIndex;

// uniform mat3 uModel; //get rid of it so that cpu do this 
layout(std140) uniform NDC
{
    mat3 uToNDC;
};
// uniform mat3 uTexCoordTransform; //get rid of it so that cpu do this 

/**
why give model xform task to CPU?
we have lots of vertex(duplicated)
it is more 
*/

void main()
{
    vec2 world_position;
    world_position.x = aModelPosition.x * aModelRow0[0] + aModelPosition.y * aModelRow0[1] + aModelRow0[2];
    world_position.y = aModelPosition.x * aModelRow1[0] + aModelPosition.y * aModelRow1[1] + aModelRow1[2];
    vec3 ndc_point = uToNDC * /* uModel * */ vec3(world_position, 1.0); //we assume that vertex position is already in world space(we dont need model xformation)
    gl_Position = vec4(ndc_point.xy, aDepth, 1.0);
    vTexCoord = aTexCoord * aTexCoordScale + aTexCoordOffset; //get atlas of texture if need
    vTint = aTint;
    vTextureIndex = aTextureIndex;
}

================================================
FILE: Assets/shaders/InstancedRenderer2D/sdf.frag
================================================
#version 300 es
precision mediump float;

/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
* (Batch Renderer Version)
  */

// 1. Receive all uniforms as 'in' variables
in vec2 vTestPoint;
flat in vec4 vFillColor;
flat in vec4 vLineColor;
flat in vec2 vWorldSize;
flat in float vLineWidth;
flat in int vShape;

layout(location = 0) out vec4 FragColor;

// --- sdCircle, sdRectangle functions are identical to the original ---
float sdCircle( vec2 p, float r )
{
    return length(p) - r;
}

float sdRectangle( vec2 point, vec2 half_dim )
{
    vec2 d = abs(point)-half_dim;
    return length(max(d,0.0)) + min(max(d.x,d.y),0.0);
}

// 2. Modify evalute_color function to use 'v' (in) variables instead of uniforms
vec4 evalute_color(float sdf)
{
    float fill_alpha = (sdf < 0.0) ? 1.0 : 0.0;
    // 'uLineWidth' -> 'vLineWidth'
    float outline_alpha = (abs(sdf) < vLineWidth * 0.5) ? 1.0 : 0.0; 

    // 'uFillColor' -> 'vFillColor'
    vec4 fill_color = vec4(vFillColor.rgb, fill_alpha * vFillColor.a);
    // 'uLineColor' -> 'vLineColor'
    vec4 line_color = vec4(vLineColor.rgb, outline_alpha * vLineColor.a);
    
    return mix(fill_color,line_color,line_color.a);

}

void main()
{
    float sdf = 0.0;

    // 3. Check 'vShape' (from vertex) instead of 'uShape' (uniform)
    if(vShape == 0){ // This pixel belongs to a Circle
        // 'uWorldSize' -> 'vWorldSize'
        float radius = min(vWorldSize.x ,vWorldSize.y) * 0.5; 
        sdf = sdCircle(vTestPoint, radius);
    }
    else if(vShape == 1){ // This pixel belongs to a Rectangle
        // 'uWorldSize' -> 'vWorldSize'
        sdf = sdRectangle(vTestPoint, 0.5 * vWorldSize); 
    }
    
    vec4 color = evalute_color(sdf);
    if(color.a <= 0.0 )
        discard;
    FragColor = color;

}

================================================
FILE: Assets/shaders/InstancedRenderer2D/sdf.vert
================================================
#version 300 es

/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
* (Batch Renderer Version)
  */

layout(location = 0) in vec2 aModelPosition;

layout(location = 1) in vec3 aModelRow0;
layout(location = 2) in vec3 aModelRow1;
// layout(location = 3) in vec2 aTestPoint;      // vTestPoint doesn't calculated in CPU anymore, but instead in here!!
layout(location = 3) in vec4 aFillColor;
layout(location = 4) in vec4 aLineColor;
layout(location = 5) in vec2 aWorldSize;
layout(location = 6) in float aLineWidth;
layout(location = 7) in int aShape;
layout(location = 8) in float aDepth;

layout(std140) uniform NDC
{
    mat3 uToNDC;
};

out vec2 vTestPoint;
flat out vec4 vFillColor;
flat out vec4 vLineColor;
flat out vec2 vWorldSize;
flat out float vLineWidth;
flat out int vShape;

void main()
{
    vec2 world_position;
    world_position.x = aModelPosition.x * aModelRow0[0] + aModelPosition.y * aModelRow0[1] + aModelRow0[2];
    world_position.y = aModelPosition.x * aModelRow1[0] + aModelPosition.y * aModelRow1[1] + aModelRow1[2];
    vec3 ndc_point = uToNDC * vec3(world_position, 1.0); 
    gl_Position = vec4(ndc_point.xy, aDepth, 1.0); // Use 1 depth for SDF

    // vTestPoint = aTestPoint;
    vTestPoint = aModelPosition * aWorldSize;
    vFillColor = aFillColor;
    vLineColor = aLineColor;
    vWorldSize = aWorldSize;
    vLineWidth = aLineWidth;
    vShape = aShape;

}

================================================
FILE: Assets/sprites/CS230_Final/Bomb.spt
================================================
Assets/images/CS230_Final/Bomb.png
FrameSize 32 32
HotSpot 0 0
RectCollision 0 0 32 32

================================================
FILE: Assets/sprites/CS230_Final/Bread.spt
================================================
Assets/images/CS230_Final/Bread.png
FrameSize 32 32
HotSpot 0 0

================================================
FILE: Assets/sprites/CS230_Final/Bus.spt
================================================
Assets/images/CS230_Final/Bus.png
FrameSize 288 720
HotSpot 0 0

================================================
FILE: Assets/sprites/CS230_Final/Hotdog.spt
================================================
Assets/images/CS230_Final/Hotdog.png
FrameSize 32 32
HotSpot 0 0

================================================
FILE: Assets/sprites/CS230_Final/KimBab.spt
================================================
Assets/images/CS230_Final/KimBab.png
FrameSize 32 32
HotSpot 0 0

================================================
FILE: Assets/sprites/CS230_Final/Passenger.spt
================================================
Assets/images/CS230_Final/Passenger.png
FrameSize 48 48
HotSpot 0 0
RectCollision -20 -20 76 124
Frame 0 0
Frame 48 0
Frame 96 0
Frame 0 48
Frame 48 48
Frame 96 48
Frame 0 96
Frame 48 96
Frame 96 96
Anim Assets/animations/CS230_Final/PassengerIdle.anm
Anim Assets/animations/CS230_Final/PassengerAngry.anm
Anim Assets/animations/CS230_Final/PassengerSad.anm

================================================
FILE: Assets/sprites/CS230_Final/Player.spt
================================================
Assets/images/CS230_Final/Player.png
HotSpot 0 0
FrameSize 32 32
RectCollision 0 0 32 32

================================================
FILE: Assets/sprites/CS230_Final/Shining.spt
================================================
Assets/images/CS230_Final/Shining.png
HotSpot 3 3
FrameSize 7 7
Frame 0 0
Frame 7 0
Frame 14 0
Frame 21 0
Frame 28 0
Anim Assets/animations/CS230_Final/Shining.anm

================================================
FILE: Assets/sprites/CS230_Final/Shoes.spt
================================================
Assets/images/CS230_Final/Shoes.png
FrameSize 32 32
HotSpot 0 0
RectCollision 0 0 32 32

================================================
FILE: Assets/sprites/CS230_Final/Snack.spt
================================================
Assets/images/CS230_Final/Snack.png
FrameSize 32 32
HotSpot 0 0

================================================
FILE: Assets/sprites/CS230_Final/Strawberry.spt
================================================
Assets/images/CS230_Final/Strawberry.png
FrameSize 32 32
HotSpot 0 0

================================================
FILE: Assets/sprites/CS230_Final/Tears.spt
================================================
Assets/images/CS230_Final/Tears.png
HotSpot 3 3
FrameSize 8 8
Frame 0 0
Frame 8 0
Frame 16 0
Frame 24 0
Frame 32 0
Anim Assets/animations/CS230_Final/Tears.anm

================================================
FILE: Assets/sprites/DemoSceneShowcase/Flame.spt
================================================
Assets/images/DemoSceneShowcase/Flame.png
FrameSize 64 64
HotSpot 0 0
NumFrames 4
Anim Assets/animations/DemoSceneShowcase/Flame.anm

================================================
FILE: Assets/sprites/DemoSceneShowcase/Meteor.spt
================================================
Assets/images/DemoSceneShowcase/Meteor.png
FrameSize 142 139
HotSpot 71 69
CircleCollision 70
NumFrames 4
Anim Assets/animations/None.anm
Anim Assets/animations/DemoSceneShowcase/MeteorBit.anm

================================================
FILE: Assets/sprites/DemoSceneShowcase/Samurai.spt
================================================
Assets/images/DemoSceneShowcase/SamuraiRun.png
FrameSize 96 96
HotSpot 55 30     
HotSpot 64 32     
CircleCollision 30
NumFrames 16
Anim Assets/animations/DemoSceneShowcase/SamuraiRun.anm

================================================
FILE: cmake/CompilerWarnings.cmake
================================================

# author Rudy Castan

# date 2025 Fall

# CS200 Computer Graphics I

# copyright DigiPen Institute of Technology

# from here:

# 

# https://github.com/lefticus/cppbestpractices/blob/master/02-Use_the_Tools_Available.md

function(set_project_warnings project_name)
  option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" TRUE)

  set(MSVC_WARNINGS
      /W4 # Baseline reasonable warnings
      /w14242 # 'identifier': conversion from 'type1' to 'type1', possible loss
              # of data
      /w14254 # 'operator': conversion from 'type1:field_bits' to
              # 'type2:field_bits', possible loss of data
      /w14263 # 'function': member function does not override any base class
              # virtual member function
      /w14265 # 'classname': class has virtual functions, but destructor is not
              # virtual instances of this class may not be destructed correctly
      /w14287 # 'operator': unsigned/negative constant mismatch
      /we4289 # nonstandard extension used: 'variable': loop control variable
              # declared in the for-loop is used outside the for-loop scope
      /w14296 # 'operator': expression is always 'boolean_value'
      /w14311 # 'variable': pointer truncation from 'type1' to 'type2'
      /w14545 # expression before comma evaluates to a function which is missing
              # an argument list
      /w14546 # function call before comma missing argument list
      /w14547 # 'operator': operator before comma has no effect; expected
              # operator with side-effect
      /w14549 # 'operator': operator before comma has no effect; did you intend
              # 'operator'?
      /w14555 # expression has no effect; expected expression with side- effect
      /w14619 # pragma warning: there is no warning number 'number'
      /w14640 # Enable warning on thread un-safe static member initialization
      /w14826 # Conversion from 'type1' to 'type_2' is sign-extended. This may
              # cause unexpected runtime behavior.
      /w14905 # wide string literal cast to 'LPSTR'
      /w14906 # string literal cast to 'LPWSTR'
      /w14928 # illegal copy-initialization; more than one user-defined
              # conversion has been implicitly applied
      /permissive- # standards conformance mode for MSVC compiler.
      /wd4201 # warning C4201 : nonstandard extension used : nameless struct / union
  )

  set(CLANG_WARNINGS
      -Wall
      -Wextra # reasonable and standard
      -Wshadow # warn the user if a variable declaration shadows one from a
               # parent context
      $<$<COMPILE_LANGUAGE:CXX>:-Wnon-virtual-dtor> # warn the user if a class with virtual functions has a
                         # non-virtual destructor. This helps catch hard to
                         # track down memory errors
      $<$<COMPILE_LANGUAGE:CXX>:-Wold-style-cast> # warn for c-style casts
      -Wcast-align # warn for potential performance problem casts
      -Wunused # warn on anything being unused
      $<$<COMPILE_LANGUAGE:CXX>:-Woverloaded-virtual> # warn if you overload (not override) a virtual
                           # function
      -Wpedantic # warn if non-standard C++ is used
      -Wconversion # warn on type conversions that may lose data
      -Wsign-conversion # warn on sign conversions
      -Wnull-dereference # warn if a null dereference is detected
      -Wdouble-promotion # warn if float is implicit promoted to double
      -Wformat=2 # warn on security issues around functions that format output
                 # (ie printf)
    #   -Wno-gnu-anonymous-struct # allow anonymous-struct
    #   -Wno-nested-anon-types
  )

  if (WARNINGS_AS_ERRORS)
    set(CLANG_WARNINGS ${CLANG_WARNINGS} -Werror)
    set(MSVC_WARNINGS ${MSVC_WARNINGS} /WX)
  endif()

  set(GCC_WARNINGS
      ${CLANG_WARNINGS}
      -Wmisleading-indentation # warn if indentation implies blocks where blocks
                               # do not exist
      -Wduplicated-cond # warn if if / else chain has duplicated conditions
      -Wduplicated-branches # warn if if / else branches have duplicated code
      -Wlogical-op # warn about logical operations being used where bitwise were
                   # probably wanted
      $<$<COMPILE_LANGUAGE:CXX>:-Wuseless-cast> # warn if you perform a cast to the same type
  )

  if(MSVC)
    set(PROJECT_WARNINGS ${MSVC_WARNINGS})
  elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    set(PROJECT_WARNINGS ${CLANG_WARNINGS})
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(PROJECT_WARNINGS ${GCC_WARNINGS})
  else()
    message(AUTHOR_WARNING "No compiler warnings set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
  endif()

  target_compile_options(${project_name} INTERFACE ${PROJECT_WARNINGS})

endfunction()

================================================
FILE: cmake/Dependencies.cmake
================================================

# author Rudy Castan

# date 2025 Fall

# CS200 Computer Graphics I

# copyright DigiPen Institute of Technology

include(FetchContent)

include(cmake/dependencies/OpenGL.cmake)    #defines target the_opengl
include(cmake/dependencies/GLEW.cmake)      # defines target the_glew
include(cmake/dependencies/SDL2.cmake)      # defines target the_sdl2
include(cmake/dependencies/DearImGUI.cmake) # defines target the_imgui   ;  note DearImGUI.cmake depends on SDL2.cmake
include(cmake/dependencies/GSL.cmake)       # defines target the_gsl
include(cmake/dependencies/STB.cmake)       # defines target the_stb

add_library(dependencies INTERFACE)

target_link_libraries(dependencies INTERFACE 
    the_opengl
    the_glew
    the_sdl2
    the_imgui
    the_gsl
    the_stb
)

================================================
FILE: cmake/StandardProjectSettings.cmake
================================================

# author Rudy Castan

# date 2025 Fall

# CS200 Computer Graphics I

# copyright DigiPen Institute of Technology

include(FetchContent)
set(FETCHCONTENT_QUIET TRUE)
set(CMAKE_VERBOSE_MAKEFILE OFF)

# https://cmake.org/cmake/help/latest/policy/CMP0135.html

if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

# Set a default build type if none was specified

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE
      Release
      CACHE STRING "Choose the type of build." FORCE)

endif()

if(NOT CMAKE_CONFIGURATION_TYPES)

# Set the possible values of build type for cmake-gui, ccmake

  set_property(
    CACHE CMAKE_BUILD_TYPE
    PROPERTY STRINGS
             "Debug"
             "Release"
             "MinSizeRel"
             "RelWithDebInfo")
endif()

# Generate compile_commands.json to make it easier to work with clang based tools

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Put exe targets into the root of the build folder

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} config_upper)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${config_upper} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach()

================================================
FILE: cmake/dependencies/DearImGUI.cmake
================================================

# author Rudy Castan

# date 2025 Fall

# CS200 Computer Graphics I

# copyright DigiPen Institute of Technology

# Depends on SDL2 and OpenGL

FetchContent_Declare(
    dearimgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG a28cb615ff2c2ed8901397b00762d557cae24760 # latest from docking branch as of 8/22/2025
)
FetchContent_MakeAvailable(dearimgui)

add_library(the_imgui STATIC
    ${dearimgui_SOURCE_DIR}/imgui.cpp ${dearimgui_SOURCE_DIR}/imgui.h
    ${dearimgui_SOURCE_DIR}/imconfig.h ${dearimgui_SOURCE_DIR}/imgui_internal.h
    ${dearimgui_SOURCE_DIR}/imgui_draw.cpp
    ${dearimgui_SOURCE_DIR}/imgui_tables.cpp
    ${dearimgui_SOURCE_DIR}/imgui_widgets.cpp
    ${dearimgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp ${dearimgui_SOURCE_DIR}/backends/imgui_impl_opengl3.h
    ${dearimgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
    ${dearimgui_SOURCE_DIR}/backends/imgui_impl_sdl2.h
)

target_include_directories(the_imgui SYSTEM PUBLIC ${dearimgui_SOURCE_DIR} ${dearimgui_SOURCE_DIR}/backends)
target_link_libraries(the_imgui PRIVATE the_sdl2)

================================================
FILE: cmake/dependencies/GLEW.cmake
================================================

# author Rudy Castan

# date 2025 Fall

# CS200 Computer Graphics I

# copyright DigiPen Institute of Technology

# We will use GLEW for OpenGL bindings

# Linux platforms have a very easy way to install these depenencies and expose them to compilers so,

# we will use the builtin find_package

# Emscripten has their own port of GLEW builtin. We don't even need to specify any flags.

# Windows does not have a simple way to get it, so we download official windows binaries and link against those

add_library(the_glew INTERFACE)

if(NOT WIN32 AND NOT EMSCRIPTEN)
    # on    Mac : brew install glew
    # on Ubuntu : apt install libglew-dev
    set(GLEW_STATIC_LIBS TRUE)
    find_package(GLEW REQUIRED)
    target_link_libraries(the_glew INTERFACE ${GLEW_STATIC_LIBRARIES} $<$<PLATFORM_ID:Linux>:GL>)
    target_include_directories(the_glew SYSTEM INTERFACE ${GLEW_INCLUDE_DIRS})
elseif(WIN32)
    # download binaries for GLEW for windows x64
    FetchContent_Declare(
        glew
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        URL "https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0-win32.zip"
    )
    FetchContent_MakeAvailable(glew)

    target_link_directories(the_glew INTERFACE ${glew_SOURCE_DIR}/lib/Release/x64)
    target_link_libraries(the_glew INTERFACE glew32s) # note that is the name of the glew32s.lib file we need to link in
    target_include_directories(the_glew SYSTEM INTERFACE ${glew_SOURCE_DIR}/include)
    target_compile_definitions(the_glew INTERFACE GLEW_STATIC)

endif()

================================================
FILE: cmake/dependencies/GSL.cmake
================================================

# author Rudy Castan

# date 2025 Fall

# CS200 Computer Graphics I

# copyright DigiPen Institute of Technology

FetchContent_Declare(
    gsl
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    URL https://github.com/microsoft/GSL/archive/refs/tags/v4.2.0.tar.gz
    URL_HASH MD5=5f3d2f7ef9c6351503c0c8f1f9390144
)
FetchContent_MakeAvailable(gsl)

add_library(the_gsl INTERFACE)
target_include_directories(the_gsl SYSTEM INTERFACE ${gsl_SOURCE_DIR}/include)

================================================
FILE: cmake/dependencies/OpenGL.cmake
================================================

# author Rudy Castan

# date 2025 Fall

# CS200 Computer Graphics I

# copyright DigiPen Institute of Technology

# most platforms should have OpenGL already available

# debian linux : libgl1-mesa-dev (not that installing GLEW installs this as a dependency)

find_package(OpenGL REQUIRED)

add_library(the_opengl INTERFACE)
target_link_libraries(the_opengl INTERFACE ${OPENGL_LIBRARIES})

if(EMSCRIPTEN)
    # We want WebGL 2
    # WebGL 2 is almost the same as OpenGL ES 3 which is almost the same as OpenGL 3.3
    # MIN_WEBGL_VERSION=2           - Specifies the lowest WebGL version to target. Pass MIN_WEBGL_VERSION=2 to drop support for WebGL 1.0
    # MAX_WEBGL_VERSION=2           - Specifies the highest WebGL version to target. Pass -sMAX_WEBGL_VERSION=2 to enable targeting WebGL 2.
    # https://emscripten.org/docs/porting/multimedia_and_graphics/OpenGL-support.html

    target_link_options(the_opengl INTERFACE -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2)
    target_compile_definitions(the_opengl INTERFACE IS_WEBGL2)

endif()

================================================
FILE: cmake/dependencies/SDL2.cmake
================================================

# author Rudy Castan

# date 2025 Fall

# CS200 Computer Graphics I

# copyright DigiPen Institute of Technology

# We will be using SDL2 for windowing & gl context creation

# Linux platforms have a very easy way to install these depenencies and expose them to compilers so,

# we will use the builtin find_package

# Emscripten has their own port of SDL2 builtin. We can just #include, define --use-port=sdl2, and start using it.

# Windows does not have a simple way to get it, so we download official windows binaries and link against those

add_library(the_sdl2 INTERFACE)

if(WIN32)
    # download binaries for SDL2 for windows x64
    FetchContent_Declare(
        sdl2
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        URL https://github.com/libsdl-org/SDL/releases/download/release-2.32.8/SDL2-devel-2.32.8-VC.zip
        URL_HASH MD5=13172db35a91f3baac59e47187a2ebbb
    )
    FetchContent_MakeAvailable(sdl2)

    target_include_directories(the_sdl2 SYSTEM INTERFACE ${sdl2_SOURCE_DIR}/include)
    
    target_link_directories(the_sdl2 INTERFACE ${sdl2_SOURCE_DIR}/lib/x64)
    target_link_libraries(the_sdl2 INTERFACE SDL2)
    target_compile_definitions(the_sdl2 INTERFACE SDL_MAIN_HANDLED)
    
    # Define a custom target to copy SDL2.dll to the build directory
    set(TEMP_EXE_FOLDER $<IF:$<BOOL:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}>,${CMAKE_RUNTIME_OUTPUT_DIRECTORY},${CMAKE_BINARY_DIR}>)
    add_custom_target(copy_sdl2_dll
    COMMAND ${CMAKE_COMMAND} -E copy
            ${sdl2_SOURCE_DIR}/lib/x64/SDL2.dll
            ${TEMP_EXE_FOLDER}/SDL2.dll
            DEPENDS ${sdl2_SOURCE_DIR}/lib/x64/SDL2.dll
            COMMENT "Copying SDL2.dll to executable directory"
    )
    add_dependencies(the_sdl2 copy_sdl2_dll)

else()
    if(EMSCRIPTEN)
        # --use-port=sdl2                     - we want version 2 rather than SDL1
        # https://emscripten.org/docs/tools_reference/settings_reference.html?highlight=use_sdl#use-sdl
        target_compile_options(the_sdl2 INTERFACE --use-port=sdl2)
        target_link_options(the_sdl2 INTERFACE --use-port=sdl2)
    else()
        # on    Mac : brew install sdl2
        # on Ubuntu : apt install libsdl2-dev
        find_package(SDL2 REQUIRED)
        target_include_directories(the_sdl2 SYSTEM INTERFACE ${SDL2_INCLUDE_DIRS})
        target_link_libraries(the_sdl2 INTERFACE ${SDL2_LIBRARIES})
    endif()
endif()

================================================
FILE: cmake/dependencies/STB.cmake
================================================

# author Rudy Castan

# date 2025 Fall

# CS200 Computer Graphics I

# copyright DigiPen Institute of Technology

FetchContent_Declare(
    stb_github
    GIT_REPOSITORY https://github.com/nothings/stb.git
    # latest of master branch as of 8/22/2025
    GIT_TAG f58f558c120e9b32c217290b80bad1a0729fbb2c
)

FetchContent_MakeAvailable(stb_github)

if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/stb_implementation.cpp)
    set(STB_IMPLEMENTATION_CODE "// This file is auto-generated from cmake/depenendencies/STB.cmake
    #define STB_IMAGE_IMPLEMENTATION
    #include \"stb_image.h\"
    #define STB_PERLIN_IMPLEMENTATION
    #include \"stb_perlin.h\"
    //#include \"stb_vorbis.c\"
    ")

    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/stb_implementation.cpp ${STB_IMPLEMENTATION_CODE})
    set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/stb_implementation.cpp PROPERTIES GENERATED TRUE)

endif()

add_library(the_stb STATIC ${CMAKE_CURRENT_BINARY_DIR}/stb_implementation.cpp)
target_include_directories(the_stb SYSTEM PUBLIC ${stb_github_SOURCE_DIR})

================================================
FILE: docs/DebuggingWeb.md
================================================

# Debugging Web Platform

Debugging a web version in the browser is not as seamless as Visual Studio, but we can configure **VSCode** to provide a similar experience.

This guide is based on the following **reference**: [WASM Debugging with Emscripten and VSCode](https://floooh.github.io/2023/11/11/emscripten-ide.html).

---

## Setup

We will be using **VSCode + CMake + Emscripten**.

### Prerequisites

1. **Install [VSCode](https://code.visualstudio.com/Download).**
2. **Set up CMake and Emscripten** by following the [Development Environment](DevEnvironment.md) guide.

### Required VSCode Extensions

Ensure you have the following extensions installed:

- `ms-vscode.cpptools` (C++ Tools)
- `ms-vscode.cmake-tools` (CMake Integration)
- `ms-vscode.wasm-dwarf-debugging` (WebAssembly Debugging)
- `ms-vscode.live-server` (Local Server for Debugging)

---

## Debugging Steps

1. **Open your project folder in VSCode.**
2. Open the command palette:
   - **Windows/Linux**: `Ctrl + Shift + P`
   - **macOS**: `Cmd + Shift + P`
3. Search for **CMake: Select Configure Preset** and choose `Web Debug` or `Web Debug on Windows`.
4. Open the `Run & Debug` tab (`Ctrl + Shift + D`).
5. In the dropdown, select the browser for debugging (`Chrome` or `Edge`).
6. Start the debugging session by:
   - Pressing `F5`, or
   - Clicking the green play button.
7. This launches a local web server on port `3000` and opens the browser to load your HTML page for debugging.
8. **Set a breakpoint** in your code while it's running to step through execution.

Now you can debug your web project just like in a native environment!

---

## Using the Browser Console for Debugging Output

In addition to setting breakpoints, you can use the browser’s developer console to view debug output and log messages.

### Opening the Developer Console:

- **Google Chrome** or **Microsoft Edge**:
  1. Open the browser.
  2. Press `F12` or `Ctrl + Shift + I` (`Cmd + Option + I` on macOS).
  3. Click on the **Console** tab.

### Viewing Debug Output:

- Using functions like `printf`, `std::cout` and our own logging system messages will be shown here.
- You can also check for warnings, errors, and network requests in the console to help diagnose issues.
- **If the webpage isn't behaving as you expect then this should be the first place to look for hints**

---

By using the browser console alongside VSCode debugging, you can gain more insights into your program’s execution and troubleshoot effectively.

================================================
FILE: docs/DevEnvironment.md
================================================

# Environment Setup

## Windows OS Setup

Install the following tools:

1. [**Visual Studio**](https://visualstudio.microsoft.com/downloads/)
   - Select C++-related packages during installation.
2. [**CMake**](https://cmake.org/download/)
   - Ensure it is available on the command line (`PATH`) if prompted.
3. [**Git SCM**](https://git-scm.com/downloads)
   - Ensure it is available on the command line (`PATH`) if prompted.
4. [**Ninja Build**](https://github.com/ninja-build/ninja/releases)
   - Manually add it to the command line (`PATH`).

## Web / Emscripten Setup

### Important Notice

**Do not use the Windows version of Emscripten for production.** Due to line-ending differences, generated output files may not work properly when uploaded to a web server. Instead, use Emscripten on a Linux-based OS such as macOS or Ubuntu (_[WSL](https://learn.microsoft.com/en-us/windows/wsl/install) works too_).

### Installation Steps

1. Review [Emscripten Platform-Specific Notes](https://emscripten.org/docs/getting_started/downloads.html#platform-notes-installation-instructions-sdk) for any prerequisites, such as Python 3.
2. Open a terminal and run:

```sh
   # Clone the emsdk repository
   git clone https://github.com/emscripten-core/emsdk.git

   # Navigate to the directory
   cd emsdk

   # Fetch the latest version of the SDK (if needed)
   git pull

   # Install the SDK tools
   ./emsdk install 4.0.13

   # Activate this version for the current user
   ./emsdk activate 4.0.13

   # Set environment variables for the current terminal session
   source ./emsdk_env.sh
```

### Emscripten Setup on Windows

If your main development platform is Windows, you should use [WSL](https://learn.microsoft.com/en-us/windows/wsl/install) for creating `Release` builds.

However, for debugging with breakpoints, `WSL` may not work reliably. In this case, install the Windows version of Emscripten in your **User** directory (e.g., `C:/Users/<your-username>`). Follow these steps:

```sh
# Navigate to your User directory
cd %USERPROFILE%

# Clone the emsdk repository
git clone https://github.com/emscripten-core/emsdk.git

# Navigate to the directory
cd emsdk

# Install the SDK tools
emsdk install 4.0.13

# Activate this version
emsdk activate 4.0.13
```

For more details on debugging, see [Web Debugging](DebuggingWeb.md).

## Ubuntu / Debian OS Setup

### Install Required Tools

You need **GNU development tools** such as `make`, `git`, and other dependencies:

```sh
sudo apt install build-essential git cmake ninja-build libsdl2-dev libglew-dev libopenal-dev
```

## macOS Setup

### Install Xcode

Xcode is the integrated development environment (IDE) for macOS and includes necessary C++ tools.

1. Open the **App Store** and search for "Xcode" to install it.

2. Launch Xcode after installation to complete the setup.

3. Open **Terminal** (Applications > Utilities or use Spotlight Search).

4. Run the following command to install Command Line Tools:
   
   ```sh
   xcode-select --install
   ```

5. Follow the on-screen instructions.

### Install Development Tools & Libraries

1. **Install Homebrew** (if not already installed):
   
   - Visit [Homebrew's website](https://brew.sh) and follow the installation instructions.

2. **Install CMake, SDL2, and GLEW using Homebrew**:
   
   ```sh
   brew install cmake ninja sdl2 glew openal-soft
   ```

This will install the required development tools and dependencies automatically.

================================================
FILE: scripts/scan_build_project.py
================================================
"""
file: scan_build_project.py
author: Rudy Castan
date: 2025 Fall
course: CS200 Computer Graphics I
copyright: DigiPen Institute of Technology
"""

import os
import re
import sys
import platform
import subprocess
import argparse
import time
import threading
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

TODO_PATTERN = re.compile(r'TODO|FIXME', re.IGNORECASE)
OPENGL_PATTERN = re.compile(r'\b(gl[A-Z][a-zA-Z0-9_]*)\(')

# ANSI color codes for better output

class Colors:
    RED = '\033[91m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    BLUE = '\033[94m'
    MAGENTA = '\033[95m'
    CYAN = '\033[96m'
    WHITE = '\033[97m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    END = '\033[0m'

def colored_print(text, color=Colors.WHITE, bold=False):
    """Print colored text to stdout"""
    prefix = Colors.BOLD if bold else ""
    print(f"{prefix}{color}{text}{Colors.END}")

def print_separator(title="", char="=", width=80):
    """Print a separator line with optional title"""
    if title:
        title_with_spaces = f" {title} "
        padding = (width - len(title_with_spaces)) // 2
        line = char * padding + title_with_spaces + char * padding
        if len(line) < width:
            line += char
    else:
        line = char * width
    colored_print(line, Colors.CYAN, bold=True)

class BuildSpinner:
    """ASCII spinner animation for build progress"""
    def __init__(self):
        self.spinner_chars = ['⠋', '⠙', '⠹', '⠸', '⠼', '⠴', '⠦', '⠧', '⠇', '⠏']
        self.spinning = False
        self.spinner_thread = None
        self.current_message = ""
        self.start_time = None
        self.progress_info = None  # (current, total) for progress bar
        self.last_line_length = 0  # Track length of last printed line for proper clearing

    def _create_progress_bar(self, current, total, width=20):
        """Create a simple ASCII progress bar"""
        if total == 0:
            return ""
    
        filled = int(width * current / total)
        bar = "█" * filled + "░" * (width - filled)
        percentage = int(100 * current / total)
        return f" [{bar}] {percentage}%"
    
    def _get_terminal_width(self):
        """Get terminal width, with fallback"""
        try:
            import shutil
            return shutil.get_terminal_size().columns
        except:
            return 80  # fallback width
    
    def _clear_line_and_print(self, content):
        """Clear the current line and print new content, handling trailing characters"""
        # Calculate the display length without ANSI color codes
        plain_content = re.sub(r'\033\[[0-9;]*m', '', content)
        content_length = len(plain_content)
    
        # If the new content is shorter than the last line, pad with spaces
        terminal_width = self._get_terminal_width()
        clear_length = max(self.last_line_length, content_length)
    
        # Ensure we don't exceed terminal width
        if clear_length > terminal_width - 1:
            clear_length = terminal_width - 1
    
        # Clear line with spaces, then print content
        if content_length < self.last_line_length:
            # Need to clear trailing characters
            padded_content = content + ' ' * (self.last_line_length - content_length)
            print(f'\r{padded_content}\r{content}', end='', flush=True)
        else:
            print(f'\r{content}', end='', flush=True)
    
        self.last_line_length = content_length
    
    def _spin(self):
        """Internal spinning method"""
        idx = 0
        while self.spinning:
            char = self.spinner_chars[idx % len(self.spinner_chars)]
    
            # Add elapsed time if we have a start time
            time_str = ""
            if self.start_time:
                elapsed = time.time() - self.start_time
                time_str = f" ({elapsed:.1f}s)"
    
            # Add progress bar if we have progress info
            progress_str = ""
            if self.progress_info:
                current, total = self.progress_info
                progress_str = self._create_progress_bar(current, total)
    
            # Build the complete spinner line
            spinner_line = f'{Colors.YELLOW}{char}{Colors.END} {self.current_message}{Colors.CYAN}{progress_str}{Colors.END}{Colors.BLUE}{time_str}{Colors.END}'
    
            # Clear line and print spinner with message
            self._clear_line_and_print(spinner_line)
            time.sleep(0.1)
            idx += 1
    
    def start(self, message="Building...", progress=None):
        """Start the spinner with a message and optional progress info"""
        if not self.spinning:
            self.current_message = message
            self.progress_info = progress
            self.start_time = time.time()
            self.spinning = True
            self.spinner_thread = threading.Thread(target=self._spin, daemon=True)
            self.spinner_thread.start()
    
    def update_message(self, message, progress=None):
        """Update the spinner message and progress"""
        self.current_message = message
        if progress is not None:
            self.progress_info = progress
    
    def stop(self, final_message=None):
        """Stop the spinner and optionally print a final message"""
        if self.spinning:
            self.spinning = False
            if self.spinner_thread:
                self.spinner_thread.join(timeout=0.2)
    
            # Clear the entire line properly by overwriting with spaces
            if self.last_line_length > 0:
                clear_line = ' ' * self.last_line_length
                print(f'\r{clear_line}\r', end='', flush=True)
                self.last_line_length = 0
    
            if final_message:
                print(final_message)

def find_todo_comments(file_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        lines = file.readlines()
    return [(i + 1, line.strip()) for i, line in enumerate(lines) if TODO_PATTERN.search(line)]

def find_opengl_usage(file_path):
    if file_path.endswith('GL.cpp'):
        return []
    with open(file_path, 'r', encoding='utf-8') as file:
        lines = file.readlines()
    return [(i + 1, match) for i, line in enumerate(lines) for match in OPENGL_PATTERN.findall(line)]

def scan_file(file_path, skip_todos=False, skip_opengl=False):
    log_output = []
    todos = find_todo_comments(file_path) if not skip_todos else []
    opengl_issues = find_opengl_usage(file_path) if not skip_opengl and file_path.endswith((".cpp", ".hpp", ".h")) else []

    if todos:
        log_output.append(f"[TODO Found] {file_path}")
        for line, comment in todos:
            log_output.append(f"  Line {line}: {comment}")
    
    if opengl_issues:
        log_output.append(f"[Bad OpenGL Usage] {file_path}")
        for line, func in opengl_issues:
            log_output.append(f"  Line {line}: {func} should be wrapped (e.g., GL::{func[2:]})")
    
    if log_output:
        colored_print("\n".join(log_output), Colors.YELLOW if todos else Colors.RED)
    
    return bool(todos), bool(opengl_issues)

def scan_directory(directory, skip_todos=False, skip_opengl=False):
    if skip_todos and skip_opengl:
        colored_print("⏭️  Skipping all scanning (--skip-todos and --skip-opengl flags used)", Colors.YELLOW)
        return

    if skip_todos:
        colored_print("⏭️  Skipping TODO scan (--skip-todos flag used)", Colors.YELLOW)
    
    if skip_opengl:
        colored_print("⏭️  Skipping OpenGL scan (--skip-opengl flag used)", Colors.YELLOW)
    
    has_todo, has_opengl_issue = False, False
    scan_title = "TODO/FIXME"
    if not skip_todos and not skip_opengl:
        scan_title = "TODO/FIXME & OpenGL SCAN"
    elif not skip_todos:
        scan_title = "TODO/FIXME SCAN"
    elif not skip_opengl:
        scan_title = "OpenGL SCAN"
    
    if not skip_todos or not skip_opengl:
        print_separator(scan_title)
        colored_print(f"📁 Scanning directory: {directory}", Colors.BLUE, bold=True)
        print()
    
    scanned_files = 0
    with ThreadPoolExecutor() as executor:
        futures = []
        for root, _, files in os.walk(directory):
            if "build" in root:
                continue
            for file in files:
                if file.endswith((".cpp", ".hpp", ".h", ".vert", ".frag", ".cmake", ".txt", ".html")):
                    file_path = os.path.join(root, file)
                    futures.append(executor.submit(scan_file, file_path, skip_todos, skip_opengl))
                    scanned_files += 1
    
        for future in futures:
            todo_found, opengl_issue_found = future.result()
            has_todo |= todo_found
            has_opengl_issue |= opengl_issue_found
    
    if has_todo:
        colored_print(f"\n❌ TODO comments found in {scanned_files} scanned files. Fix them before proceeding.", Colors.RED, bold=True)
    
    if has_opengl_issue:
        colored_print(f"\n❌ Bad OpenGL usage found in {scanned_files} scanned files. Fix them before proceeding.", Colors.RED, bold=True)
    
    if has_todo or has_opengl_issue:
        sys.exit(1)
    elif not skip_todos or not skip_opengl:
        success_msg = "✅ No "
        if not skip_todos and not skip_opengl:
            success_msg += "TODO/FIXME comments or bad OpenGL usage"
        elif not skip_todos:
            success_msg += "TODO/FIXME comments"
        elif not skip_opengl:
            success_msg += "bad OpenGL usage"
        success_msg += f" found in {scanned_files} scanned files!"
        colored_print(success_msg, Colors.GREEN, bold=True)

def windows_to_wsl_path(win_path: str) -> str:
    win_path = os.path.abspath(win_path)
    match = re.match(r"([A-Za-z]):\\(.*)", win_path)
    if not match:
        raise ValueError("Invalid Windows path format")
    drive, path = match.groups()
    return "/mnt/" + drive.lower() + "/" + path.replace("\\", "/")

def run_cmake_command(folder, build_type, target):
    linux_prefix = []
    build_dir = os.path.join(folder, f'build/{target}-{build_type.lower()}')

    if platform.system() == "Windows" and target == "web":
        linux_prefix = ['wsl']
        folder = windows_to_wsl_path(folder)
        build_dir = windows_to_wsl_path(build_dir)
    
    start_time = time.time()
    
    # Configure step
    configure_start = time.time()
    cmake_configure = subprocess.run(linux_prefix + ['cmake', '--preset', f'{target}-{build_type.lower()}', '-S', folder], capture_output=True, text=True, encoding="utf-8")
    configure_time = time.time() - configure_start
    
    if cmake_configure.returncode != 0:
        return cmake_configure.stderr + '\n' + cmake_configure.stdout, build_type, target, 0, configure_time, 0
    
    # Build step
    build_start = time.time()
    config_build_type = build_type if build_type != "developer-release" else "Release"
    cmake_build = subprocess.run(linux_prefix + ['cmake', '--build', build_dir, '--config', config_build_type], capture_output=True, text=True, encoding="utf-8")
    build_time = time.time() - build_start
    total_time = time.time() - start_time
    
    if cmake_build.returncode != 0:
        return cmake_build.stderr + '\n' + cmake_build.stdout, build_type, target, total_time, configure_time, build_time
    
    return "", build_type, target, total_time, configure_time, build_time

def get_executable_info(folder, build_type, target):
    """Get information about the built executable and how to run it"""
    build_dir = Path(folder) / f'build/{target}-{build_type.lower()}'

    if target == "web":
        # Web builds create HTML files
        html_file = build_dir / "engine_porting.html"
        if html_file.exists():
            return {
                'type': 'web',
                'path': str(html_file),
                'run_command': f"python3 -m http.server 8000 # Then open http://localhost:8000/{html_file.name}",
                'directory': str(build_dir)
            }
    else:
        # Native builds create executables
        exe_name = "engine_porting.exe" if platform.system() == "Windows" else "engine_porting"
        exe_file = build_dir / exe_name
        if exe_file.exists():
            return {
                'type': 'executable',
                'path': str(exe_file),
                'run_command': f"cd {build_dir} && ./{exe_name}",
                'directory': str(build_dir)
            }
    
    return None

def build_project(folder, target_filter=None, build_type_filter=None):
    print_separator("BUILD PROCESS")
    colored_print("🔨 Starting build process...", Colors.BLUE, bold=True)

    error_output = []
    build_results = []
    total_start_time = time.time()
    
    build_types = ['debug', 'developer-release', 'release']
    targets = ['windows', 'web'] if platform.system() == "Windows" else ['linux', 'web']
    
    # Apply filters
    if target_filter:
        targets = [t for t in targets if t in target_filter]
    if build_type_filter:
        build_types = [b for b in build_types if b in build_type_filter]
    
    total_builds = len(targets) * len(build_types)
    
    # Start a global spinner for the entire build process
    spinner = BuildSpinner()
    spinner.start(f"Building {total_builds} configuration{'s' if total_builds > 1 else ''}...", progress=(0, total_builds))
    
    with ThreadPoolExecutor() as executor:
        futures = []
        current_build = 0
    
        for target in targets:
            for build_type in build_types:
                current_build += 1
                build_name = f"{target.upper()} {build_type}"
                future = executor.submit(run_cmake_command, folder, build_type, target)
                futures.append((future, target, build_type, current_build, build_name))
    
        completed_builds = 0
        for future, target, build_type, build_number, build_name in futures:
            # Update spinner with current progress
            spinner.update_message(f"Building {build_name}...", progress=(completed_builds, total_builds))
    
            error_messages, returned_build_type, returned_target, total_time, configure_time, build_time = future.result()
            completed_builds += 1
    
            # Temporarily stop spinner to show result
            spinner.stop()
    
            if error_messages:
                colored_print(f"❌ [{build_number}/{total_builds}] {returned_target.upper()} {returned_build_type} build failed ({total_time:.1f}s)", Colors.RED, bold=True)
                # Store structured error information for better reporting
                error_output.append({
                    'target': returned_target,
                    'build_type': returned_build_type,
                    'build_number': build_number,
                    'total_builds': total_builds,
                    'time': total_time,
                    'configure_time': configure_time,
                    'build_time': build_time,
                    'error_messages': error_messages
                })
                build_results.append({
                    'target': returned_target,
                    'build_type': returned_build_type,
                    'success': False,
                    'time': total_time,
                    'configure_time': configure_time,
                    'build_time': build_time
                })
            else:
                colored_print(f"✅ [{build_number}/{total_builds}] {returned_target.upper()} {returned_build_type} built successfully ({total_time:.1f}s)", Colors.GREEN, bold=True)
                build_results.append({
                    'target': returned_target,
                    'build_type': returned_build_type,
                    'success': True,
                    'time': total_time,
                    'configure_time': configure_time,
                    'build_time': build_time
                })
    
            # Restart spinner if there are more builds
            if completed_builds < total_builds:
                remaining = total_builds - completed_builds
                spinner.start(f"Continuing with {remaining} remaining build{'s' if remaining > 1 else ''}...", progress=(completed_builds, total_builds))
    
    # Make sure spinner is stopped
    spinner.stop()
    
    total_build_time = time.time() - total_start_time
    
    # Print build summary
    print_separator("BUILD SUMMARY")
    successful_builds = [r for r in build_results if r['success']]
    failed_builds = [r for r in build_results if not r['success']]
    
    colored_print(f"📊 Total builds: {len(build_results)}", Colors.BLUE, bold=True)
    colored_print(f"✅ Successful: {len(successful_builds)}", Colors.GREEN, bold=True)
    colored_print(f"❌ Failed: {len(failed_builds)}", Colors.RED, bold=True)
    colored_print(f"⏱️  Total time: {total_build_time:.1f}s", Colors.BLUE, bold=True)
    
    if successful_builds:
        print_separator("HOW TO RUN YOUR BUILDS")
    
        for result in successful_builds:
            exe_info = get_executable_info(folder, result['build_type'], result['target'])
            if exe_info:
                colored_print(f"\n🎯 {result['target'].upper()} {result['build_type']}", Colors.CYAN, bold=True)
    
                if exe_info['type'] == 'web':
                    colored_print(f"   📄 HTML file: {exe_info['path']}", Colors.WHITE)
                    colored_print(f"   🌐 To run: cd {exe_info['directory']}", Colors.YELLOW)
                    colored_print(f"           python3 -m http.server 8000", Colors.YELLOW)
                    colored_print(f"           # Then open: http://localhost:8000/engine_porting.html", Colors.YELLOW)
                else:
                    colored_print(f"   📱 Executable: {exe_info['path']}", Colors.WHITE)
                    colored_print(f"   ▶️  To run: {exe_info['run_command']}", Colors.YELLOW)
    
        # Print quick commands section
        print_separator("QUICK RUN COMMANDS")
        colored_print("Copy and paste these commands to run your builds:", Colors.BLUE, bold=True)
        print()
    
        for result in successful_builds:
            exe_info = get_executable_info(folder, result['build_type'], result['target'])
            if exe_info:
                if exe_info['type'] == 'web':
                    colored_print(f"# {result['target'].upper()} {result['build_type']} (Web)", Colors.CYAN)
                    colored_print(f"cd {exe_info['directory']} && python3 -m http.server 8000", Colors.GREEN)
                    print()
                else:
                    colored_print(f"# {result['target'].upper()} {result['build_type']} (Native)", Colors.CYAN)
                    colored_print(f"{exe_info['run_command']}", Colors.GREEN)
                    print()
    
    if error_output:
        print_separator("BUILD ERRORS")
        colored_print(f"⚠️  {len(error_output)} build{'s' if len(error_output) > 1 else ''} failed. Details below:", Colors.RED, bold=True)
        print()
    
        for i, error_info in enumerate(error_output, 1):
            # Header for each error
            colored_print(f"┌─ Error {i}/{len(error_output)}: {error_info['target'].upper()} {error_info['build_type']}", Colors.RED, bold=True)
            colored_print(f"│  Build time: {error_info['time']:.1f}s (configure: {error_info['configure_time']:.1f}s, compile: {error_info['build_time']:.1f}s)", Colors.YELLOW)
            colored_print("│", Colors.RED)
    
            # Split error messages into lines and format them
            error_lines = error_info['error_messages'].strip().split('\n')
            for line in error_lines:
                if line.strip():  # Skip empty lines
                    # Highlight different types of error messages
                    if 'error:' in line.lower() or 'fatal error:' in line.lower():
                        colored_print(f"│  {line}", Colors.RED)
                    elif 'warning:' in line.lower():
                        colored_print(f"│  {line}", Colors.YELLOW)
                    elif 'CMake Error' in line or 'Error' in line:
                        colored_print(f"│  {line}", Colors.RED)
                    elif line.startswith('  ') or line.startswith('\t'):
                        # Indented lines (usually context)
                        colored_print(f"│  {line}", Colors.WHITE)
                    else:
                        # Regular lines
                        colored_print(f"│  {line}", Colors.WHITE)
    
            # Footer for each error
            if i < len(error_output):
                colored_print("└─" + "─" * 70, Colors.RED)
                print()  # Extra spacing between errors
            else:
                colored_print("└─" + "─" * 70, Colors.RED)
    
        print()
        colored_print("💡 Tips for fixing build errors:", Colors.CYAN, bold=True)
        colored_print("   • Check the first error message - later ones might be cascading", Colors.CYAN)
        colored_print("   • Look for 'error:' and 'fatal error:' lines (highlighted in red above)", Colors.CYAN)
        colored_print("   • Make sure all dependencies are installed", Colors.CYAN)
        colored_print("   • Try cleaning build directory: rm -rf build/", Colors.CYAN)

def main():
    parser = argparse.ArgumentParser(
        description="Scans a project directory for TODOs and builds it using CMake.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  %(prog)s                                    # Scan and build all configurations
  %(prog)s --skip-todos                       # Skip TODO scan, build all
  %(prog)s --skip-opengl                      # Skip OpenGL scan, build all
  %(prog)s --skip-build                       # Scan only, no building
  %(prog)s --skip-todos --skip-opengl         # Skip all scans, build only
  %(prog)s --skip-build --skip-opengl         # TODO scan only
  %(prog)s --target linux web                # Build only linux and web targets
  %(prog)s --build-type debug release        # Build only debug and release configurations
  %(prog)s --target web --build-type debug   # Build only web debug configuration
        """
    )
    parser.add_argument("directory", nargs='?', default=os.getcwd(), 
                        help="Project directory (default: current working directory)")
    parser.add_argument("--skip-todos", action="store_true", 
                        help="Skip TODO/FIXME scanning")
    parser.add_argument("--skip-opengl", action="store_true", 
                        help="Skip OpenGL usage scanning")
    parser.add_argument("--skip-build", action="store_true", 
                        help="Skip building the project (scan only)")
    parser.add_argument("--target", nargs="+", choices=['linux', 'windows', 'web'],
                        help="Build only specified targets")
    parser.add_argument("--build-type", nargs="+", choices=['debug', 'developer-release', 'release'],
                        help="Build only specified build types")

    args = parser.parse_args()
    
    print_separator("CS200 PROJECT BUILD SCRIPT")
    colored_print(f"🚀 Starting project analysis and build", Colors.BLUE, bold=True)
    colored_print(f"📁 Working directory: {args.directory}", Colors.WHITE)
    
    scan_directory(args.directory, skip_todos=args.skip_todos, skip_opengl=args.skip_opengl)
    
    if not args.skip_build:
        build_project(args.directory, target_filter=args.target, build_type_filter=args.build_type)
    else:
        colored_print("\n⏭️  Skipping build process (--skip-build flag used)", Colors.YELLOW, bold=True)

if __name__ == "__main__":
    if sys.stdout.encoding.lower() != "utf-8":
        sys.stdout.reconfigure(encoding="utf-8")
    if sys.stderr.encoding.lower() != "utf-8":
        sys.stderr.reconfigure(encoding="utf-8")
    main()

================================================
FILE: source/CMakeLists.txt
================================================

# author Rudy Castan

# date 2025 Fall

# CS200 Computer Graphics I

# copyright DigiPen Institute of Technology

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SOURCE_CODE 

    Engine/Engine.hpp Engine/Engine.cpp
    Engine/Error.hpp
    Engine/Font.hpp Engine/Font.cpp
    Engine/Fonts.h
    Engine/FPS.hpp
    Engine/GameState.hpp
    Engine/GameStateManager.hpp Engine/GameStateManager.cpp
    Engine/Input.hpp Engine/Input.cpp
    Engine/Logger.hpp Engine/Logger.cpp
    Engine/Matrix.hpp Engine/Matrix.cpp
    Engine/Path.hpp Engine/Path.cpp
    Engine/Random.hpp Engine/Random.cpp
    Engine/Rect.hpp
    Engine/Texture.hpp Engine/Texture.cpp
    Engine/TextureManager.hpp Engine/TextureManager.cpp
    Engine/TextManager.hpp Engine/TextManager.cpp
    Engine/Timer.hpp
    Engine/Vec2.hpp Engine/Vec2.cpp
    Engine/Window.hpp Engine/Window.cpp
    Engine/Animation.cpp Engine/Animation.h
    Engine/Camera.cpp Engine/Camera.h
    Engine/Collision.cpp Engine/Collision.h
    Engine/Component.h
    Engine/ComponentManager.h
    Engine/GameObject.cpp Engine/GameObject.h
    Engine/GameObjectManager.cpp Engine/GameObjectManager.h
    Engine/Particle.cpp Engine/Particle.h
    Engine/ShowCollision.cpp Engine/ShowCollision.h
    Engine/Sprite.cpp Engine/Sprite.h
    
    OpenGL/Buffer.hpp OpenGL/Buffer.cpp
    OpenGL/Environment.hpp
    OpenGL/Framebuffer.hpp OpenGL/Framebuffer.cpp
    OpenGL/GL.cpp OpenGL/GL.hpp
    OpenGL/GLConstants.hpp
    OpenGL/GLTypes.hpp
    OpenGL/Handle.hpp
    OpenGL/Shader.cpp OpenGL/Shader.hpp
    OpenGL/Texture.hpp OpenGL/Texture.cpp
    OpenGL/VertexArray.cpp OpenGL/VertexArray.hpp
    
    CS200/Image.hpp CS200/Image.cpp
    CS200/ImGuiHelper.hpp CS200/ImGuiHelper.cpp
    CS200/ImmediateRenderer2D.hpp CS200/ImmediateRenderer2D.cpp
    CS200/BatchRenderer2D.hpp CS200/BatchRenderer2D.cpp
    CS200/InstancedRenderer2D.hpp CS200/InstancedRenderer2D.cpp
    CS200/IRenderer2D.hpp
    CS200/NDC.hpp
    CS200/Renderer2DUtils.hpp CS200/Renderer2DUtils.cpp
    CS200/RenderingAPI.hpp CS200/RenderingAPI.cpp
    CS200/RGBA.hpp
    
    Demo/DemoShapes.hpp Demo/DemoShapes.cpp
    Demo/DemoFramebuffer.hpp Demo/DemoFramebuffer.cpp
    Demo/DemoText.hpp Demo/DemoText.cpp
    Demo/DemoVAO.hpp Demo/DemoVAO.cpp
    Demo/DemoBufferTypes.hpp Demo/DemoBufferTypes.cpp
    Demo/DemoTexturing.hpp Demo/DemoTexturing.cpp
    Demo/DemoCS230Textures.hpp Demo/DemoCS230Textures.cpp
    Demo/DemoBatchInstance.hpp Demo/DemoBatchInstance.cpp
    
    Demo/DemoSceneShowcase/SceneState.hpp Demo/DemoSceneShowcase/SceneState.cpp
    Demo/DemoSceneShowcase/Samurai.h Demo/DemoSceneShowcase/Samurai.cpp
    Demo/DemoSceneShowcase/Map.h Demo/DemoSceneShowcase/Map.cpp
    
    Game/Background.h Game/Background.cpp
    Game/GameObjectTypes.h
    Game/MainMenu.h Game/MainMenu.cpp
    Game/Particles.h
    Game/Score.h Game/Score.cpp
    Game/Splash.h Game/Splash.cpp
    Game/States.h
    
    Game/CS230_Final/Components/Bounce.h Game/CS230_Final/Components/Bounce.cpp
    Game/CS230_Final/Components/Grid.h Game/CS230_Final/Components/Grid.cpp
    Game/CS230_Final/Components/Random.h Game/CS230_Final/Components/Random.cpp
    Game/CS230_Final/Components/Ziggle.h Game/CS230_Final/Components/Ziggle.cpp
    
    Game/CS230_Final/Objects/Bus.h Game/CS230_Final/Objects/Bus.cpp
    Game/CS230_Final/Objects/BusLine.h
    Game/CS230_Final/Objects/Constants.h
    Game/CS230_Final/Objects/Bus.h Game/CS230_Final/Objects/Bus.cpp
    Game/CS230_Final/Objects/Food.h Game/CS230_Final/Objects/Food.cpp
    Game/CS230_Final/Objects/Obstacle.h Game/CS230_Final/Objects/Obstacle.cpp
    Game/CS230_Final/Objects/Passenger.h Game/CS230_Final/Objects/Passenger.cpp
    Game/CS230_Final/Objects/Player.h Game/CS230_Final/Objects/Player.cpp
    
    Game/CS230_Final/States/BadSandwich.h Game/CS230_Final/States/BadSandwich.cpp
    Game/CS230_Final/States/GoodSandwich.h Game/CS230_Final/States/GoodSandwich.cpp
    Game/CS230_Final/States/NormalSandwich.h Game/CS230_Final/States/NormalSandwich.cpp
    Game/CS230_Final/States/Project.h Game/CS230_Final/States/Project.cpp
    
    Game/States/ConsoleTest.h Game/States/ConsoleTest.cpp
    Game/States/RenderingTest.h Game/States/RenderingTest.cpp
    
    
    main.cpp

)

add_executable(engine_porting ${SOURCE_CODE})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_CODE})

target_link_libraries(engine_porting PRIVATE project_options dependencies)
target_include_directories(engine_porting PRIVATE .)

# Check the IS_DEVELOPER_VERSION cache variable

# This is set by the cmake configure preset

if (IS_DEVELOPER_VERSION)
    target_compile_definitions(engine_porting PRIVATE DEVELOPER_VERSION)
endif()

if(EMSCRIPTEN)

    # https://emscripten.org/docs/tools_reference/settings_reference.html
    # ASSERTIONS=1                  - we want asserts to work
    # WASM=1                        - we want web assembly generated rather than just javascript
    # DISABLE_EXCEPTION_CATCHING=0  - we are using exceptions so let's not disable them
    # ALLOW_MEMORY_GROWTH=1         - we don't know exactly how much heap space we'll need so allow it to grow
    # EXIT_RUNTIME=1                - have exiting actually stop the program
    # SINGLE_FILE=1                 - generate everything into one html file
    # --embed-file                  - https://emscripten.org/docs/tools_reference/emcc.html#emcc-embed-file
    # --use-preload-cache           - help with faster reloads : https://emscripten.org/docs/compiling/Deploying-Pages.html#providing-a-quick-second-time-load
    # -lembind                      - to call c++ from javascript https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html
    # --shell-file                  - to customize the webpage https://emscripten.org/docs/compiling/Deploying-Pages.html#build-files-and-custom-shell
    target_link_options(engine_porting PRIVATE 
    -sASSERTIONS=$<$<BOOL:${IS_DEVELOPER_VERSION}>:1>$<$<NOT:$<BOOL:${IS_DEVELOPER_VERSION}>>:0>
    -sWASM=1 
    -sDISABLE_EXCEPTION_CATCHING=0 
    -sALLOW_MEMORY_GROWTH=1 
    -sEXIT_RUNTIME=1 
    -sSINGLE_FILE=1 
    --embed-file ${CMAKE_SOURCE_DIR}/Assets@/Assets
    --use-preload-cache
    -lembind
    --shell-file ${CMAKE_SOURCE_DIR}/app_resources/web/index_shell.html
    )
    
    set_target_properties(engine_porting PROPERTIES SUFFIX ".html")

elseif(WIN32)

    target_link_options(engine_porting PRIVATE 
        $<IF:$<BOOL:${IS_DEVELOPER_VERSION}>,/SUBSYSTEM:CONSOLE,/SUBSYSTEM:WINDOWS>
        /ENTRY:mainCRTStartup)
    
    set(ICON_RC ${CMAKE_CURRENT_BINARY_DIR}/app.rc)
    if(NOT EXISTS ${ICON_RC})
        set(ICON_FILE ${CMAKE_SOURCE_DIR}/app_resources/windows/icon.ico)
        file(WRITE ${ICON_RC} "IDR_MAINFRAME ICON \"${ICON_FILE}\"\nIDI_ICON1 ICON DISCARDABLE \"${ICON_FILE}\"")
    endif()
    
    target_sources(engine_porting PRIVATE ${ICON_RC})

endif()

================================================
FILE: source/main.cpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2024 Fall
* \copyright DigiPen Institute of Technology
  */

#include "Demo/DemoShapes.hpp"
#include "Engine/Engine.hpp"
#include "Engine/GameStateManager.hpp"
#include "Engine/Window.hpp"
#include "Game/Splash.h"

namespace
{
    [[maybe_unused]] int  gWindowWidth  = 400;
    [[maybe_unused]] int  gWindowHeight = 400;
    [[maybe_unused]] bool gNeedResize   = false;
}

#if defined(__EMSCRIPTEN__)

# include <emscripten.h>

# include <emscripten/bind.h>

# include <emscripten/em_asm.h>

void main_loop()
{
    Engine& engine = Engine::Instance();
    if (gNeedResize)
    {
        Engine::GetWindow().ForceResize(gWindowWidth, gWindowHeight);
        gNeedResize = false;
    }

    engine.Update();
    
    if (engine.HasGameEnded())
    {
        emscripten_cancel_main_loop();
        engine.Stop();
    }

}

EMSCRIPTEN_BINDINGS(main_window)
{
    emscripten::function(
        "setWindowSize", emscripten::optional_override(
                             [](int sizeX, int sizeY)
                             {
                                 sizeX                  = (sizeX < 400) ? 400 : sizeX;
                                 sizeY                  = (sizeY < 400) ? 400 : sizeY;
                                 const auto window_size = Engine::GetWindow().GetSize();
                                 if (sizeX != window_size.x || sizeY != window_size.y)
                                 {
                                     gNeedResize   = true;
                                     gWindowWidth  = sizeX;
                                     gWindowHeight = sizeY;
                                 }
                             }));
}
#endif

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    Engine& engine = Engine::Instance();
    engine.Start("Taekyung Ho CS200 HW6");
    engine.GetGameStateManager().PushState<Splash>();

    //std::ifstream in_file("Assets/sprites/CS230_Final/Bomb.spt ");
    
    //if (in_file.is_open() == false)
    //{
    //    throw std::runtime_error("Failed to load ");
    //}

#if !defined(__EMSCRIPTEN__)
    while (engine.HasGameEnded() == false)
    {
        engine.Update();
    }
    engine.Stop();
#else
    // https://emscripten.org/docs/api_reference/emscripten.h.html#c.emscripten_set_main_loop
    constexpr bool simulate_infinite_loop  = true;
    constexpr int  match_browser_framerate = -1;
    emscripten_set_main_loop(main_loop, match_browser_framerate, simulate_infinite_loop);
#endif
    return 0;
}

================================================
FILE: source/CS200/BatchRenderer2D.cpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "BatchRenderer2D.hpp"

#include "Engine/Path.hpp"
#include "OpenGL/Buffer.hpp"
#include "OpenGL/GL.hpp"
#include "OpenGL/VertexArray.hpp"
#include "Renderer2DUtils.hpp"
#include <fstream>
#include <numeric>
#include <sstream>

namespace CS200
{
    BatchRenderer2D::BatchRenderer2D(unsigned max_quads)
    {
        maxVertices = max_quads * 4; // each quad have 4 vertices
        maxIndices    = max_quads * 6;
        vertexData.resize(maxVertices);
        sdfVertexData.resize(maxVertices);

        // wait until other stuffs are ready.. ->Init
    }
    
    BatchRenderer2D::BatchRenderer2D(BatchRenderer2D&& other) noexcept
        : vertexData(std::move(other.vertexData)),
          vertexBufferHandle(other.vertexBufferHandle),
          texturingCombineShader(std::move(other.texturingCombineShader)),
          modelHandle(other.modelHandle),
          sdfVertexData(std::move(other.sdfVertexData)),
          sdfVertexBufferHandle(other.sdfVertexBufferHandle),
          sdfShader(std::move(other.sdfShader)),
          sdfModelHandle(other.sdfModelHandle),
          sdfVertexDataEnd(other.sdfVertexDataEnd),
          sdfIndexCount(other.sdfIndexCount),
          indexBufferHandle(other.indexBufferHandle),
          camera_uniform_buffer(other.camera_uniform_buffer),
          camera_array(other.camera_array),
          currentCameraMatrix(other.currentCameraMatrix),
          maxVertices(other.maxVertices),
          maxIndices(other.maxIndices),
          vertexDataEnd(other.vertexDataEnd),
          indexCount(other.indexCount),
          textureSlots(std::move(other.textureSlots)),
          activeTextureSize(other.activeTextureSize),
          draw_call(other.draw_call), 
          texture_call(other.texture_call)
    {
        other.vertexBufferHandle     = 0;
        other.modelHandle             = 0;
        other.sdfVertexBufferHandle     = 0;
        other.sdfModelHandle         = 0;
        other.indexBufferHandle         = 0;
        other.camera_uniform_buffer     = 0;
        other.texturingCombineShader = {};
        other.sdfShader                 = {};
        other.vertexDataEnd             = nullptr;
        other.indexCount             = 0;
        other.sdfVertexDataEnd         = nullptr;
        other.sdfIndexCount             = 0;
        other.activeTextureSize         = 0;
        other.draw_call                 = 0;
        other.texture_call             = 0;
    }
    
    BatchRenderer2D& BatchRenderer2D::operator=(BatchRenderer2D&& other) noexcept
    {
        std::swap(vertexData, other.vertexData);
        std::swap(vertexBufferHandle, other.vertexBufferHandle);
        std::swap(indexBufferHandle, other.indexBufferHandle);
        std::swap(modelHandle, other.modelHandle);
        std::swap(texturingCombineShader, other.texturingCombineShader);
        std::swap(currentCameraMatrix, other.currentCameraMatrix);
    
        std::swap(sdfVertexData, other.sdfVertexData);
        std::swap(sdfVertexBufferHandle, other.sdfVertexBufferHandle);
        std::swap(sdfShader, other.sdfShader);
        std::swap(sdfModelHandle, other.sdfModelHandle);
        std::swap(sdfVertexDataEnd, other.sdfVertexDataEnd);
        std::swap(sdfIndexCount, other.sdfIndexCount);
    
        std::swap(camera_uniform_buffer, other.camera_uniform_buffer);
        std::swap(camera_array, other.camera_array);
        std::swap(draw_call, other.draw_call);
        std::swap(texture_call, other.texture_call);
    
        std::swap(maxVertices, other.maxVertices);
        std::swap(maxIndices, other.maxIndices);
        std::swap(vertexDataEnd, other.vertexDataEnd);
        std::swap(indexCount, other.indexCount);
        std::swap(textureSlots, other.textureSlots);
        std::swap(activeTextureSize, other.activeTextureSize);
        return *this;
    }
    
    BatchRenderer2D::~BatchRenderer2D()
    {
        Shutdown();
    }
    
    void BatchRenderer2D::Init()
    {
        // get how many texture opengl can draw
        GLint max_tex_units = 0;
        GL::GetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_tex_units); // check with docs.gl to get minimum(16) and maximum
        textureSlots.resize(static_cast<size_t>(std::min(max_tex_units, 64)));
    
        // load shaders with parsing
        const std::filesystem::path vertex_file = assets::locate_asset("Assets/shaders/BatchRenderer2D/quad.vert");
        std::ifstream                vert_stream(vertex_file);
        std::stringstream            vert_text_stream;
        vert_text_stream << vert_stream.rdbuf();
        const std::string vertex_glsl = vert_text_stream.str();
    
    
        const std::filesystem::path fragment_file = assets::locate_asset("Assets/shaders/BatchRenderer2D/quad.frag");
        std::ifstream                frag_stream(fragment_file);
        std::stringstream            frag_text_stream;
        frag_text_stream << frag_stream.rdbuf();
        std::string          frag_glsl        = frag_text_stream.str();
        const size_t      first_newline = frag_glsl.find('\n');
        const std::string define_line    = "\n#define MAX_TEXTURE_SLOTS " + std::to_string(textureSlots.size());
        frag_glsl.insert(first_newline, define_line);
    
        texturingCombineShader = OpenGL::CreateShader(std::string_view{ vertex_glsl }, std::string_view{ frag_glsl });
    
    
        // have to set their binding index
        GL::UseProgram(texturingCombineShader.Shader);
    
        std::vector<int> sampler_binding_values(textureSlots.size());
        std::iota(sampler_binding_values.begin(), sampler_binding_values.end(), 0);
        const GLint location = GL::GetUniformLocation(texturingCombineShader.Shader, "uTextures");
        GL::Uniform1iv(location, static_cast<GLsizei>(textureSlots.size()), sampler_binding_values.data());
    
        GL::UseProgram(0);
    
        // create vertex array object, buffer vertices, buffer indices
        vertexBufferHandle = OpenGL::CreateBuffer(OpenGL::BufferType::Vertices, static_cast<GLsizeiptr>(sizeof(QuadVertex) * maxVertices));
    
    
        // setup index buffer
    
        // unlike vertex buffer that gonna change every frame, index don't change
        // i.e. 0 1 2 2 3 0 ... << this pattern repeat
        // but just amount of index gonna change(how many do we need?)
        std::vector<unsigned> indice_values(maxIndices);
        unsigned              offset = 0;
        for (unsigned i = 0; i < maxIndices; i += 6)
        {
            indice_values[i + 0] = offset + 0;
            indice_values[i + 1] = offset + 1;
            indice_values[i + 2] = offset + 2;
            indice_values[i + 3] = offset + 2;
            indice_values[i + 4] = offset + 3;
            indice_values[i + 5] = offset + 0;
            offset += 4;
        }
    
        indexBufferHandle = OpenGL::CreateBuffer(OpenGL::BufferType::Indices, std::as_bytes(std::span{ indice_values }));
    
        // Create vertex array object
        const auto layout = {
            OpenGL::VertexBuffer{ vertexBufferHandle, { OpenGL::Attribute::Float2, OpenGL::Attribute::Float2, OpenGL::Attribute::UByte4ToNormalized, OpenGL::Attribute::Int, OpenGL::Attribute::Float } }
        };
        modelHandle = OpenGL::CreateVertexArrayObject(layout, indexBufferHandle);
    
    
        // SDF
        //  create vertex array object, buffer vertices, buffer indices
        sdfShader = OpenGL::CreateShader(assets::locate_asset("Assets/shaders/BatchRenderer2D/sdf.vert"), assets::locate_asset("Assets/shaders/BatchRenderer2D/sdf.frag"));
    
        sdfVertexBufferHandle = OpenGL::CreateBuffer(OpenGL::BufferType::Vertices, static_cast<GLsizeiptr>(sizeof(SDFVertex) * maxVertices));
        const auto sdfLayout  = {
             OpenGL::VertexBuffer{ sdfVertexBufferHandle,
                                   {
                                       OpenGL::Attribute::Float2,              // aWorldPosition
                                       OpenGL::Attribute::Float2,              // aTestPoint
                                       OpenGL::Attribute::UByte4ToNormalized, // aFillColor
                                       OpenGL::Attribute::UByte4ToNormalized, // aLineColor
                                       OpenGL::Attribute::Float2,              // aWorldSize
                                       OpenGL::Attribute::Float,              // aLineWidth
                                       OpenGL::Attribute::Int,                  // aShape
                                       OpenGL::Attribute::Float                  // aDepth
                                   } }
        };
        sdfModelHandle = OpenGL::CreateVertexArrayObject(sdfLayout, indexBufferHandle);
    
        //- Create uniform buffer for camera/view-projection matrix
        camera_uniform_buffer = OpenGL::CreateBuffer(OpenGL::BufferType::UniformBlocks, sizeof(camera_array));
    
        OpenGL::BindUniformBufferToShader(texturingCombineShader.Shader, 0, camera_uniform_buffer, "NDC");
        OpenGL::BindUniformBufferToShader(sdfShader.Shader, 0, camera_uniform_buffer, "NDC");
    }
    
    void BatchRenderer2D::Shutdown()
    {
        OpenGL::DestroyShader(texturingCombineShader);
        OpenGL::DestroyShader(sdfShader);
    
        GL::DeleteBuffers(1, &vertexBufferHandle), vertexBufferHandle        = 0;
        GL::DeleteBuffers(1, &indexBufferHandle), indexBufferHandle            = 0;
        GL::DeleteBuffers(1, &sdfVertexBufferHandle), sdfVertexBufferHandle = 0;
    
        GL::DeleteBuffers(1, &camera_uniform_buffer), camera_uniform_buffer = 0;
    
        GL::DeleteVertexArrays(1, &modelHandle), modelHandle       = 0;
        GL::DeleteVertexArrays(1, &sdfModelHandle), sdfModelHandle = 0;
    }
    
    void BatchRenderer2D::BeginScene(const Math::TransformationMatrix& view_projection)
    {
        //- Store matrix for potential later use
        currentCameraMatrix = view_projection;
    
        //- Convert 3x3 matrix to 4x3 format for uniform buffer
        updateCameraUniformValues(currentCameraMatrix);
    
        //- Update uniform buffer with new matrix data
        OpenGL::UpdateBufferData(OpenGL::BufferType::UniformBlocks, camera_uniform_buffer, std::as_bytes(std::span{ camera_array }));
    
        //- Bind uniform buffer for use by shaders
        GL::BindBuffer(GL_UNIFORM_BUFFER, camera_uniform_buffer);
    
        draw_call     = 0;
        texture_call = 0;
        startBatch();
    }
    
    void BatchRenderer2D::EndScene()
    {
        flush();
    }
    
    void BatchRenderer2D::DrawQuad(const Math::TransformationMatrix& transform, OpenGL::TextureHandle texture, Math::vec2 texture_coord_bl, Math::vec2 texture_coord_tr, CS200::RGBA tintColor, float depth)
    {
        if (sdfIndexCount + 6 > maxIndices)
        {
            flush();
        }
    
        if (indexCount + 6 > maxIndices)
        {
            flush();
        }
    
        int     tex_index = 0;
        bool found       = false;
        for (size_t i = 0; i < activeTextureSize; ++i)
        {
            if (textureSlots[i] == texture)
            {
                found      = true;
                tex_index = static_cast<int>(i);
            }
        }
    
        if (!found)
        {
            if (activeTextureSize >= textureSlots.size())
            {
                flush();
            }
            tex_index                        = static_cast<int>(activeTextureSize);
            textureSlots[activeTextureSize] = texture;
            ++activeTextureSize;
        }
    
        // Convert texture_coords_lbrt (left, bottom, right, top) to texture coordinate transform matrix
        const float left   = static_cast<float>(texture_coord_bl.x);
        const float bottom = static_cast<float>(texture_coord_bl.y);
        const float right  = static_cast<float>(texture_coord_tr.x);
        const float top       = static_cast<float>(texture_coord_tr.y);
    
        const std::array<float, 2> texture_coords[4] = {
            {  left, bottom }, //  bottom left
            { right, bottom }, //  bottom right
            { right,     top }, //  top right
            {  left,    top }  //  top left
        };
    
        // we don't have to make texcoord_transform matrix, just use 4 texture coords right away!
    
        // const std::array<unsigned char, 4> tint = pack_color(tint_color);
    
        constexpr std::array<float, 2> model_positions[4] = {
            { -0.5, -0.5 }, //  bottom left
            { +0.5, -0.5 }, //  bottom right
            { +0.5, +0.5 }, //  top right
            { -0.5, +0.5 }    //  top left
        };
    
    
        for (unsigned i = 0; i < 4; ++i) // i is for 4 vertex(bottom/top - right/left)
        {
            // matrix multiply manually (3by 3, transform matrix) * (3 by 1, position matrix) => model to world!
            const float x =
                static_cast<float>(static_cast<double>(model_positions[i][0])  * transform[0][0] + static_cast<double>(model_positions[i][1])  * transform[0][1] + transform[0][2]);
            const float y = static_cast<float>(static_cast<double>(model_positions[i][0]) * transform[1][0] + static_cast<double>(model_positions[i][1]) * transform[1][1] + transform[1][2]);
    
            vertexDataEnd->x            = x;
            vertexDataEnd->y            = y;
            vertexDataEnd->s            = texture_coords[i][0];
            vertexDataEnd->t            = texture_coords[i][1];
            vertexDataEnd->tint            = ColorArray(tintColor);
            vertexDataEnd->textureIndex = tex_index;
            vertexDataEnd->depth        = depth;
            ++vertexDataEnd;
        }
        indexCount += 6;
    
        ++texture_call;
    }
    
    void BatchRenderer2D::DrawCircle(
        [[maybe_unused]] const Math::TransformationMatrix& transform, [[maybe_unused]] CS200::RGBA fill_color, [[maybe_unused]] CS200::RGBA line_color, [[maybe_unused]] double line_width, float depth)
    {
        if (indexCount + 6 > maxIndices)
        {
            flush();
        }
        if (sdfIndexCount + 6 > maxIndices)
        {
            flush();
        }
    
        const auto sdf_transform = Renderer2DUtils::CalculateSDFTransform(transform, line_width);
        const auto fill_bytes     = ColorArray(fill_color);
        const auto line_bytes     = ColorArray(line_color);
    
        constexpr std::array<float, 2> model_positions[4] = {
            { -0.5, -0.5 }, //  bottom left
            { +0.5, -0.5 }, //  bottom right
            { +0.5, +0.5 }, //  top right
            { -0.5, +0.5 }    //  top left
        };
    
        for (unsigned i = 0; i < 4; ++i)
        {
            const float x = model_positions[i][0] * sdf_transform.QuadTransform[0] + model_positions[i][1] * sdf_transform.QuadTransform[3] + sdf_transform.QuadTransform[6];
            const float y = model_positions[i][0] * sdf_transform.QuadTransform[1] + model_positions[i][1] * sdf_transform.QuadTransform[4] + sdf_transform.QuadTransform[7];
    
            const float s = model_positions[i][0] * sdf_transform.QuadSize[0];
            const float t = model_positions[i][1] * sdf_transform.QuadSize[1];
    
            sdfVertexDataEnd->x              = x;
            sdfVertexDataEnd->y              = y;
            sdfVertexDataEnd->testPoint_s = s;
            sdfVertexDataEnd->testPoint_t = t;
            sdfVertexDataEnd->fillColor      = fill_bytes;
            sdfVertexDataEnd->lineColor      = line_bytes;
            sdfVertexDataEnd->worldSize_x = sdf_transform.WorldSize[0];
            sdfVertexDataEnd->worldSize_y = sdf_transform.WorldSize[1];
            sdfVertexDataEnd->lineWidth      = static_cast<float>(line_width);
            sdfVertexDataEnd->shape          = static_cast<int>(SDFShape::Circle); // 0
            sdfVertexDataEnd->depth          = depth;
    
            ++sdfVertexDataEnd;
        }
        sdfIndexCount += 6;
    
        ++texture_call;
    }
    
    void BatchRenderer2D::DrawRectangle(
        [[maybe_unused]] const Math::TransformationMatrix& transform, [[maybe_unused]] CS200::RGBA fill_color, [[maybe_unused]] CS200::RGBA line_color, [[maybe_unused]] double line_width, float depth)
    {
        if (indexCount + 6 > maxIndices)
        {
            flush();
        }
        if (sdfIndexCount + 6 > maxIndices)
        {
            flush();
        }
        const auto sdf_transform = Renderer2DUtils::CalculateSDFTransform(transform, line_width);
        const auto fill_bytes     = ColorArray(fill_color);
        const auto line_bytes     = ColorArray(line_color);
    
        constexpr std::array<float, 2> model_positions[4] = {
            { -0.5, -0.5 }, //  bottom left
            { +0.5, -0.5 }, //  bottom right
            { +0.5, +0.5 }, //  top right
            { -0.5, +0.5 }    //  top left
        };
    
        for (unsigned i = 0; i < 4; ++i)
        {
            const float x = model_positions[i][0] * sdf_transform.QuadTransform[0] + model_positions[i][1] * sdf_transform.QuadTransform[3] + sdf_transform.QuadTransform[6];
            const float y = model_positions[i][0] * sdf_transform.QuadTransform[1] + model_positions[i][1] * sdf_transform.QuadTransform[4] + sdf_transform.QuadTransform[7];
            const float s = model_positions[i][0] * sdf_transform.QuadSize[0];
            const float t = model_positions[i][1] * sdf_transform.QuadSize[1];
    
            sdfVertexDataEnd->x              = x;
            sdfVertexDataEnd->y              = y;
            sdfVertexDataEnd->testPoint_s = s;
            sdfVertexDataEnd->testPoint_t = t;
            sdfVertexDataEnd->fillColor      = fill_bytes;
            sdfVertexDataEnd->lineColor      = line_bytes;
            sdfVertexDataEnd->worldSize_x = sdf_transform.WorldSize[0];
            sdfVertexDataEnd->worldSize_y = sdf_transform.WorldSize[1];
            sdfVertexDataEnd->lineWidth      = static_cast<float>(line_width);
            sdfVertexDataEnd->shape          = static_cast<int>(SDFShape::Rectangle); // 1
            sdfVertexDataEnd->depth          = depth;
    
            ++sdfVertexDataEnd;
        }
        sdfIndexCount += 6;
    
        ++texture_call;
    }
    
    void BatchRenderer2D::DrawLine(
        [[maybe_unused]] const Math::TransformationMatrix& transform, [[maybe_unused]] Math::vec2 start_point, [[maybe_unused]] Math::vec2 end_point, [[maybe_unused]] CS200::RGBA line_color,
        [[maybe_unused]] double line_width, float depth)
    {
        const auto line_transform = Renderer2DUtils::CalculateLineTransform(transform, start_point, end_point, line_width);
        DrawRectangle(line_transform, line_color, line_color, line_width,depth);
    }
    
    void BatchRenderer2D::DrawLine([[maybe_unused]] Math::vec2 start_point, [[maybe_unused]] Math::vec2 end_point, [[maybe_unused]] CS200::RGBA line_color, [[maybe_unused]] double line_width, float depth)
    {
        DrawLine(Math::TransformationMatrix{}, start_point, end_point, line_color, line_width, depth);
    }
    
    void BatchRenderer2D::startBatch()
    {
        vertexDataEnd      = vertexData.data();
        indexCount          = 0;
        activeTextureSize = 0;
    
        sdfVertexDataEnd = sdfVertexData.data();
        sdfIndexCount     = 0;
    
    }
    
    void BatchRenderer2D::flush()
    {
        if (indexCount > 0)
        {
            // upload our vertices(vertex buffer is dynamic)
            const ptrdiff_t                     vertex_count  = vertexDataEnd - vertexData.data();
            const std::span                     data_span       = std::span{ vertexData.data(), static_cast<size_t>(vertex_count) };
            const std::span<const std::byte> bytes_to_send = std::as_bytes(data_span);
    
            GL::BindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
            GL::BufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(QuadVertex) * maxVertices), nullptr, GL_DYNAMIC_DRAW); // orphaning
    
            OpenGL::UpdateBufferData(OpenGL::BufferType::Vertices, vertexBufferHandle, bytes_to_send);
    
    
            // select our texture
            for (size_t i = 0; i < activeTextureSize; ++i)
            {
                GL::ActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + i));
                GL::BindTexture(GL_TEXTURE_2D, textureSlots[i]);
            }
    
            // draw
            GL::UseProgram(texturingCombineShader.Shader);
            GL::BindVertexArray(modelHandle);
            GL::DrawElements(GL_TRIANGLES, static_cast<GLsizei>(indexCount), GL_UNSIGNED_INT, nullptr);
            ++draw_call;
        }
    
        if (sdfIndexCount > 0)
        {
            const ptrdiff_t                     sdf_vertex_count_ptrdiff = sdfVertexDataEnd - sdfVertexData.data();
            const std::span                     sdf_data_span              = std::span{ sdfVertexData.data(), static_cast<size_t>(sdf_vertex_count_ptrdiff) };
            const std::span<const std::byte> sdf_bytes_to_send          = std::as_bytes(sdf_data_span);
    
            GL::BindBuffer(GL_ARRAY_BUFFER, sdfVertexBufferHandle);
            GL::BufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(SDFVertex) * maxVertices), nullptr, GL_DYNAMIC_DRAW); // orphaning
            OpenGL::UpdateBufferData(OpenGL::BufferType::Vertices, sdfVertexBufferHandle, sdf_bytes_to_send);
    
            GL::UseProgram(sdfShader.Shader);
            GL::BindVertexArray(sdfModelHandle);
            GL::DrawElements(GL_TRIANGLES, static_cast<GLsizei>(sdfIndexCount), GL_UNSIGNED_INT, nullptr);
            ++draw_call;
        }
    
    
        // unbind stuff
        GL::BindVertexArray(0);
        GL::UseProgram(0);
        GL::BindTexture(GL_TEXTURE_2D, 0);
        GL::BindBuffer(GL_ARRAY_BUFFER, 0);
    
        startBatch(); // reset
    }
    
    void BatchRenderer2D::updateCameraUniformValues(const Math::TransformationMatrix& view_projection)
    {
        const auto as_3x3 = Renderer2DUtils::to_opengl_mat3(view_projection);
        for (std::size_t col = 0; col < 3; ++col)
        {
            const std::size_t src_offset = col * 3;
            const std::size_t dst_offset = col * 4;
    
            camera_array[dst_offset + 0] = as_3x3[src_offset + 0]; // how?****
            camera_array[dst_offset + 1] = as_3x3[src_offset + 1];
            camera_array[dst_offset + 2] = as_3x3[src_offset + 2];
            camera_array[dst_offset + 3] = 0.0f;
        }
    }
    
    size_t BatchRenderer2D::GetDrawCallCounter()
    {
        return draw_call;
    }
    
    size_t BatchRenderer2D::GetDrawTextureCounter()
    {
        return texture_call;
    }

} // namespace CS200

================================================
FILE: source/CS200/BatchRenderer2D.hpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once

#include "Engine/Matrix.hpp"
#include "IRenderer2D.hpp"
#include "OpenGL/Shader.hpp"
#include "OpenGL/VertexArray.hpp"
#include <array>
#include <vector>

/**
 *

* basic idea - either buffer is full(reached max_quads) or user invoked endscene-> draw one time
  */
  namespace CS200
  {
   class BatchRenderer2D : public IRenderer2D
   {
   public:
  
       BatchRenderer2D(unsigned max_quads = 10'000);
       BatchRenderer2D(const BatchRenderer2D& other) = delete;
       BatchRenderer2D(BatchRenderer2D&& other) noexcept;
       BatchRenderer2D& operator=(const BatchRenderer2D& other) = delete;
       BatchRenderer2D& operator=(BatchRenderer2D&& other) noexcept;
       ~BatchRenderer2D() override;
      
       void Init() override;
       void Shutdown() override;
       // void BeginScene(std::span<const float, 9> ndc_matrix) override;
       void BeginScene(const Math::TransformationMatrix& view_projection) override;
       void EndScene() override;
       void
           DrawQuad(const Math::TransformationMatrix& transform, OpenGL::TextureHandle texture, Math::vec2 texture_coord_bl, Math::vec2 texture_coord_tr, CS200::RGBA tintColor, float depth) override;
       // void DrawQuad(std::span<const float, 9> transform, OpenGL::Handle texture, std::span<const float, 4> texture_coords_lbrt, std::span<const float, 4> tint_color) override;
       void DrawCircle(const Math::TransformationMatrix& transform, CS200::RGBA fill_color, CS200::RGBA line_color, double line_width, float depth) override;
       void DrawRectangle(const Math::TransformationMatrix& transform, CS200::RGBA fill_color, CS200::RGBA line_color, double line_width, float depth) override;
       void DrawLine(const Math::TransformationMatrix& transform, Math::vec2 start_point, Math::vec2 end_point, CS200::RGBA line_color, double line_width, float depth) override;
       void DrawLine(Math::vec2 start_point, Math::vec2 end_point, CS200::RGBA line_color, double line_width, float depth) override;
  
   private:
  
       struct QuadVertex
       {
           float                         x = 0, y = 0;
           float                         s = 0, t = 0;
           std::array<unsigned char, 4> tint{};
           int                             textureIndex = 0;
           float                         depth;
       };
      
       std::vector<QuadVertex> vertexData{};
       OpenGL::BufferHandle    vertexBufferHandle{};
      
       OpenGL::CompiledShader texturingCombineShader{};
      
       OpenGL::VertexArrayHandle modelHandle{};
      
       // sdf
       struct SDFVertex
       {
           float                         x = 0, y = 0;                       // Layout 0: aWorldPosition
           float                         testPoint_s = 0, testPoint_t = 0; // Layout 1: aTestPoint
           std::array<unsigned char, 4> fillColor{};                       // Layout 2: aFillColor
           std::array<unsigned char, 4> lineColor{};                       // Layout 3: aLineColor
           float                         worldSize_x = 0, worldSize_y = 0; // Layout 4: aWorldSize
           float                         lineWidth = 0;                       // Layout 5: aLineWidth
           int                             shape       = 0;                       // Layout 6: aShape (0=Circle, 1=Rect)
           float                         depth       = 0;                       // Layout 7: aDepth
       };
      
       std::vector<SDFVertex>      sdfVertexData{};
       OpenGL::BufferHandle      sdfVertexBufferHandle{};
       OpenGL::CompiledShader      sdfShader{};
       OpenGL::VertexArrayHandle sdfModelHandle{};
       SDFVertex*                  sdfVertexDataEnd = nullptr; // pointing where we are
       unsigned                  sdfIndexCount       = 0;
      
       OpenGL::BufferHandle       indexBufferHandle{};
       OpenGL::BufferHandle       camera_uniform_buffer{};
       std::array<float, 12>       camera_array{};
       Math::TransformationMatrix currentCameraMatrix{};
       // limit how much we're going to put into that vertex buffer
       unsigned                   maxVertices = 0;
       unsigned                   maxIndices  = 0;
      
       void updateCameraUniformValues(const Math::TransformationMatrix& view_projection);

        enum class SDFShape : uint8_t
        {
            Circle      = 0,
            Rectangle = 1,
        };
        // void DrawSDF(const Math::TransformationMatrix& transform, CS200::RGBA fill_color, CS200::RGBA line_color, double line_width, SDFShape sdf_shape);
    
    
        QuadVertex* vertexDataEnd = nullptr; // pointing where we are
        unsigned    indexCount      = 0;
    
        // OpenGL::Handle theTexture = 0;
        std::vector<OpenGL::TextureHandle> textureSlots;
        size_t                               activeTextureSize = 0;
    
    private:
        void flush(); // when quad amount is reached to max_quad
        void startBatch();
    
        size_t draw_call = 0;
        size_t GetDrawCallCounter() override;
    
        size_t texture_call = 0;
        size_t GetDrawTextureCounter() override;
    };

}

================================================
FILE: source/CS200/Image.cpp
================================================
﻿/**

* \file
* \author Rudy Castan
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "Image.hpp"

#include "Engine/Error.hpp"
#include "Engine/Path.hpp"

#include <stb_image.h>
#include <utility>

namespace CS200
{
    Image::Image(const std::filesystem::path& image_path, bool flip_vertical)
    {
        const std::filesystem::path image_path_ctor = assets::locate_asset(image_path);
        stbi_set_flip_vertically_on_load(flip_vertical);
        constexpr int num_channels       = 4;                                                                                                            // rgba
        int           files_num_channels = 0;                                                                                                            // to here
        image_data                       = stbi_load(image_path_ctor.string().c_str(), &dimensions.x, &dimensions.y, &files_num_channels, num_channels); // loading, use dynamic memory so we need free
        if (!image_data)
        {
            throw_error_message("Loading Fail ");
        }
    }

    Image::Image(Image&& temporary) noexcept : image_data{ temporary.image_data }, dimensions{ temporary.dimensions }
    {
        temporary.image_data = nullptr;
        temporary.dimensions = { 0, 0 };
    }
    
    Image& Image::operator=(Image&& temporary) noexcept
    {
        std::swap(image_data, temporary.image_data);
        std::swap(dimensions, temporary.dimensions);
        return *this;
    }
    
    Image::~Image()
    {
        if (image_data)
        {
            stbi_image_free(image_data);
        }
    }
    
    const RGBA* Image::data() const noexcept
    {
        return reinterpret_cast<const RGBA*>(image_data);
    }
    
    RGBA* Image::data() noexcept
    {
        return reinterpret_cast<RGBA*>(image_data);
    }
    
    Math::ivec2 Image::GetSize() const noexcept
    {
        return dimensions;
    }

}

================================================
FILE: source/CS200/Image.hpp
================================================
/**

* \file
* \author Rudy Castan
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once

#include "Engine/Vec2.hpp"
#include "RGBA.hpp"
#include <filesystem>
#include <gsl/gsl>

#include <stb_image.h>

namespace CS200
{
    /**
     * \brief RAII wrapper for loading and managing image pixel data from files
     *
     * The Image class provides a safe, automatic way to load image files (PNG, JPG, etc.)
     * and access their pixel data for use in graphics applications. It handles all the
     * complexity of file loading, memory management, and data conversion.
     *
     * Key Features:
     * - Automatic file loading using stb_image library
     * - Always converts to consistent RGBA format (4 bytes, 32bits per pixel)
     * - RAII memory management (automatic cleanup in destructor)
     * - Move-only semantics to prevent expensive copying
     * - Optional vertical flipping for different coordinate systems
     *
     * Common Use Cases:
     * - Loading textures for sprites, backgrounds, UI elements
     * - Reading image data for procedural generation or analysis
     * - Converting various image formats to a consistent RGBA format
     * - Preparing pixel data for upload to GPU textures
     *
     * Memory Layout:
     * - Pixels stored in row-major order (left-to-right, top-to-bottom)
     * - Each pixel is 4 bytes: Red, Green, Blue, Alpha (0-255 each)
     * - Total memory = width × height × 4 bytes
     *
     * Example Usage:
     * \code
     * // Load an image file
     * Image sprite_image("sprites/player.png");
     *
     * // Get image properties
     * auto size = sprite_image.GetSize();
     * int width = size.x, height = size.y;
     *
     * // Access pixel data
     * const RGBA* pixels = sprite_image.data();
     * RGBA top_left_pixel = pixels[0];
     *
     * // Move to another Image (efficient)
     * Image moved_image = std::move(sprite_image);
     * \endcode
     */
    class Image
    {
    public:
        /**
         * \brief Load an image from file and store its pixel data
         * \param image_path Path to the image file (relative to Assets folder, like "Assets/ship.png")
         * \param flip_vertical Whether to flip the image vertically when loading (default: false)
         *
         * Implementation notes:
         * - Use assets::locate_asset() to find the full file path
         * - Use stb_image library functions to load the image data
         * - Always load as 4-channel RGBA regardless of source format
         * - Set stbi_set_flip_vertically_on_load() before loading
         * - Throw an error if loading fails
         * - Store the loaded pixel data and image dimensions
         */
        explicit Image(const std::filesystem::path& image_path, bool flip_vertical = false);

        /**
         * \brief Copy constructor - deleted to prevent accidental copying
         * Images manage dynamic memory and should not be copied
         */
        Image(const Image&) = delete;
    
        /**
         * \brief Copy assignment - deleted to prevent accidental copying
         * Images manage dynamic memory and should not be copied
         */
        Image& operator=(const Image&) = delete;
    
        /**
         * \brief Move constructor - transfer ownership of image data
         * \param temporary The temporary Image object to move from
         *
         * Implementation notes:
         * - Transfer ownership of pixel data pointer and size
         * - Set the source object's data to nullptr and size to {0,0}
         * - Use noexcept to enable move optimizations
         */
        Image(Image&& temporary) noexcept;
    
        /**
         * \brief Move assignment - transfer ownership of image data
         * \param temporary The temporary Image object to move from
         * \return Reference to this object
         *
         * Implementation notes:
         * - Use std::swap to exchange data between objects
         * - This safely handles self-assignment and cleanup
         */
        Image& operator=(Image&& temporary) noexcept;
    
        /**
         * \brief Destructor - free the allocated image data
         *
         * Implementation notes:
         * - Check if pixel data pointer is not nullptr
         * - Use stbi_image_free() to properly release memory allocated by stb_image
         */
        ~Image();
    
        /**
         * \brief Get read-only access to the pixel data array
         * \return Const pointer to the first RGBA pixel
         *
         * Implementation notes:
         * - Return the stored pixel data pointer as const
         * - Pixels are stored in row-major order (left-to-right, top-to-bottom)
         */
        const RGBA* data() const noexcept;
    
        /**
         * \brief Get read-write access to the pixel data array
         * \return Pointer to the first RGBA pixel for modification
         *
         * Implementation notes:
         * - Return the stored pixel data pointer for modification
         * - Pixels are stored in row-major order (left-to-right, top-to-bottom)
         */
        RGBA* data() noexcept;
    
        /**
         * \brief Get the dimensions of the loaded image
         * \return Vector containing width (x) and height (y) in pixels
         *
         * Implementation notes:
         * - Return the stored image dimensions
         * - Width and height are set during image loading
         */
        Math::ivec2 GetSize() const noexcept;
    
    private:
    
        stbi_uc*    image_data = nullptr;
        Math::ivec2 dimensions;
    };

}

================================================
FILE: source/CS200/ImGuiHelper.cpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "ImGuiHelper.hpp"

#include <SDL.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl2.h>
#include <imgui.h>
#include <imgui_internal.h> // for DockBuilderGetCentralNode until they stabilize make DockBuilder

namespace
{
    std::string   gImGuiSaveFilePath;
    SDL_Window*   gCachedWindow    = nullptr;
    SDL_GLContext gCachedGLContext = nullptr;
}

namespace ImGuiHelper
{
    void Initialize(gsl::not_null<SDL_Window*> sdl_window, gsl::not_null<SDL_GLContext> gl_context, const std::filesystem::path& ini_file_path)
    {
        // Cache the window and context for later use
        gCachedWindow    = sdl_window;
        gCachedGLContext = gl_context;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        {
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
            gImGuiSaveFilePath = ini_file_path.string();
            io.IniFilename     = gImGuiSaveFilePath.c_str();
        }
        ImGui_ImplSDL2_InitForOpenGL(sdl_window, gl_context);
        ImGui_ImplOpenGL3_Init();
    }
    
    void FeedEvent(const SDL_Event& event)
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
    }
    
    Viewport Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
    
        // enable docking on main window, based off of imgui docking demo
        {
            const ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoDockingInCentralNode;
            const ImGuiWindowFlags   window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                                                  ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
            const ImGuiViewport* const main_viewport   = ImGui::GetMainViewport();
            const auto                 window_position = main_viewport->Pos;
            const auto                 window_size     = main_viewport->Size;
            ImGui::SetNextWindowPos(window_position);
            ImGui::SetNextWindowSize(window_size);
            ImGui::SetNextWindowViewport(main_viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::Begin("Main Window Dockspace", nullptr, window_flags);
            ImGui::PopStyleVar(3);
            const ImGuiID dockspace_id = ImGui::GetID("Main Window Dockspace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    
            // How to get central area : https://github.com/ocornut/imgui/issues/5921#issuecomment-1327801959
            // Central Node is the middle area where we want the main display to be
            const ImGuiDockNode* const node = ImGui::DockBuilderGetCentralNode(dockspace_id);
            if (node == nullptr) [[unlikely]]
                return Viewport{ 0, 0, static_cast<int>(window_size.x), static_cast<int>(window_size.y) };
            // the central node's position is relative to the monitor, so we need main viewport to turn relative to the window
            const int opengl_x = static_cast<int>((node->Pos.x - window_position.x)); // convert relative to window x
            const int opengl_y =
                static_cast<int>((window_size.y - ((node->Pos.y - window_position.y) + node->Size.y))); // convert relative to window x and then convert to opengl convention where 0,0 is bottom left
            const int opengl_w = static_cast<int>(node->Size.x);                                        // width of central node is what we want
            const int opengl_h = static_cast<int>(node->Size.y);                                        // height of central node is what we want
            ImGui::End();                                                                               // end main window docking
            return Viewport{ opengl_x, opengl_y, opengl_w, opengl_h };
        }
    }
    
    void End()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        const ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(gCachedWindow, gCachedGLContext);
        }
    }
    
    void Shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    
        gCachedWindow    = nullptr;
        gCachedGLContext = nullptr;
    }

}

================================================
FILE: source/CS200/ImGuiHelper.hpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once

#include <filesystem>
#include <gsl/gsl>

struct SDL_Window;
typedef void* SDL_GLContext;
union SDL_Event;

namespace ImGuiHelper
{
    void Initialize(gsl::not_null<SDL_Window*> sdl_window, gsl::not_null<SDL_GLContext> gl_context, const std::filesystem::path& ini_file_path = "imgui.ini");
    void FeedEvent(const SDL_Event& event);

    struct Viewport
    {
        int  x = 0, y = 0;
        int  width = 0, height = 0;
        bool operator==(const Viewport&) const = default;
    };
    
    Viewport Begin();
    void     End();
    void     Shutdown();

}

================================================
FILE: source/CS200/ImmediateRenderer2D.cpp
================================================
/**

* \file
* \author Rudy Castan
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "ImmediateRenderer2D.hpp"
  #include "Engine/Engine.hpp"
  #include "Engine/Matrix.hpp"
  #include "Engine/Path.hpp"
  #include "Engine/Texture.hpp"
  #include "Engine/Window.hpp"
  #include "NDC.hpp"
  #include "OpenGL/Buffer.hpp"
  #include "OpenGL/GL.hpp"
  #include "Renderer2DUtils.hpp"
  #include "RenderingAPI.hpp"
  #include <span>
  #include <utility>

namespace CS200
{

    void ImmediateRenderer2D::Init()
    {
        /** - Create index buffer with quad indices (0,1,2,2,3,0)
         * - Create vertex buffer with quad vertices (-0.5 to 0.5 range)
         * - Set up VAO with position and texture coordinate attributes
         * - Create SDF vertex buffer (position-only attributes) */
    
        //- Load and compile vertex/fragment shaders from Assets/shaders/
        const std::filesystem::path vertex_file   = assets::locate_asset("Assets/shaders/ImmediateRenderer2D/quad.vert");
        const std::filesystem::path fragment_file = assets::locate_asset("Assets/shaders/ImmediateRenderer2D/quad.frag");
        texturingCombineShader                    = OpenGL::CreateShader(vertex_file, fragment_file);
    
        sdfShader = OpenGL::CreateShader(assets::locate_asset("Assets/shaders/ImmediateRenderer2D/sdf.vert"), assets::locate_asset("Assets/shaders/ImmediateRenderer2D/sdf.frag"));
    
        struct position
        {
            float x, y;
        };
    
        struct texture_coordinate
        {
            float s, t;
        };
    
        constexpr std::array positions = {
            position{ -0.5f, -0.5f }, // bottom-left
            position{ -0.5f,  0.5f }, // top-left
            position{  0.5f,  0.5f }, // top-right
            position{  0.5f, -0.5f }  // bottom-right
        };
    
        constexpr std::array texture_coordinates = {
            texture_coordinate{ 0.0f, 0.0f }, // bottom-left
            texture_coordinate{ 0.0f, 1.0f }, // top-left
            texture_coordinate{ 1.0f, 1.0f }, // top-right
            texture_coordinate{ 1.0f, 0.0f }  // bottom-right
        };
    
        constexpr std::array<unsigned char, 6> indices = { 0, 3, 2, 0, 2, 1 };
    
        quad.positionBufferHandle = OpenGL::CreateBuffer(OpenGL::BufferType::Vertices, std::as_bytes(std::span{ positions }));
        quad.texCoordBufferHandle = OpenGL::CreateBuffer(OpenGL::BufferType::Vertices, std::as_bytes(std::span{ texture_coordinates }));
        quad.indexBufferHandle    = OpenGL::CreateBuffer(OpenGL::BufferType::Indices, std::as_bytes(std::span{ indices }));
        quad.indicesCount         = static_cast<GLsizei>(indices.size());
        const auto layout         = {
            OpenGL::VertexBuffer{ quad.positionBufferHandle, { OpenGL::Attribute::Float2 } },
            OpenGL::VertexBuffer{ quad.texCoordBufferHandle, { OpenGL::Attribute::Float2 } }
        };
        quad.modelHandle = OpenGL::CreateVertexArrayObject(layout, quad.indexBufferHandle);
    
    
        //- Create SDF vertex buffer (position-only attributes)
    
        sdfBufferHandle                 = OpenGL::CreateBuffer(OpenGL::BufferType::Vertices, std::as_bytes(std::span{ positions }));
        const auto layout_position_only = {
            OpenGL::VertexBuffer{ quad.positionBufferHandle, { OpenGL::Attribute::Float2 } }
        };
        sdfVeretexArrayHandle = OpenGL::CreateVertexArrayObject(layout_position_only, quad.indexBufferHandle);
        //- Create uniform buffer for camera/view-projection matrix
       camera_uniform_buffer = OpenGL::CreateBuffer(OpenGL::BufferType::UniformBlocks, sizeof(camera_array));
    
    
        //- Bind uniform buffer to both shaders with name "Camera"
        //OpenGL::BindUniformBufferToShader(texturingCombineShader.Shader, 0, camera_uniform_buffer, "NDC");
    }
    
    void ImmediateRenderer2D::Shutdown()
    {
        OpenGL::DestroyShader(texturingCombineShader);
        OpenGL::DestroyShader(sdfShader);
    
        GL::DeleteBuffers(1, &quad.positionBufferHandle), quad.positionBufferHandle = 0;
        GL::DeleteBuffers(1, &quad.texCoordBufferHandle), quad.texCoordBufferHandle = 0;
        GL::DeleteBuffers(1, &quad.indexBufferHandle), quad.indexBufferHandle       = 0;
        GL::DeleteBuffers(1, &sdfBufferHandle), sdfBufferHandle                     = 0;
    
        GL::DeleteVertexArrays(1, &quad.modelHandle), quad.modelHandle           = 0;
        GL::DeleteVertexArrays(1, &sdfVeretexArrayHandle), sdfVeretexArrayHandle = 0;
    }
    
    void ImmediateRenderer2D::BeginScene([[maybe_unused]] const Math::TransformationMatrix& view_projection)
    {
        //- Store matrix for potential later use
        currentCameraMatrix = view_projection;
    
        //- Convert 3x3 matrix to 4x3 format for uniform buffer
        updateCameraUniformValues(currentCameraMatrix);
    
        //- Update uniform buffer with new matrix data
        OpenGL::UpdateBufferData(OpenGL::BufferType::UniformBlocks, camera_uniform_buffer, std::as_bytes(std::span{ camera_array }));
    
        //- Bind uniform buffer for use by shaders
        GL::BindBuffer(GL_UNIFORM_BUFFER, camera_uniform_buffer);
    
        OpenGL::BindUniformBufferToShader(texturingCombineShader.Shader, 0, camera_uniform_buffer, "NDC");
    
        draw_call = 0;
        texture_call = 0;
    }
    
    void ImmediateRenderer2D::EndScene()
    {
    
    }
    
    void ImmediateRenderer2D::DrawQuad(
        [[maybe_unused]] const Math::TransformationMatrix& transform, OpenGL::TextureHandle texture, Math::vec2 texture_coord_bl, Math::vec2 texture_coord_tr, CS200::RGBA tintColor, float depth)
    {
        //- Bind texture to texture unit 0
        GL::UseProgram(texturingCombineShader.Shader);
        GL::ActiveTexture(GL_TEXTURE0);
        GL::BindTexture(GL_TEXTURE_2D, texture);
    
        // - Calculate texture coordinate transformation matrix - by bl and tr, and translate to opengl version !!
        std::array<float, 9> texture_transform = { static_cast<float>(texture_coord_tr.x - texture_coord_bl.x),
                                                   0.f,
                                                   0.f, // column1
                                                   0.f,
                                                   static_cast<float>(texture_coord_tr.y - texture_coord_bl.y),
                                                   0.f, // column2
                                                   static_cast<float>(texture_coord_bl.x),
                                                   static_cast<float>(texture_coord_bl.y),
                                                   1.f };
    
        //- Set shader uniforms: model matrix, depth, texture transform, tint color
        const auto& locations = texturingCombineShader.UniformLocations;
        GL::Uniform1i(locations.at("uTex2d"), 0);
    
        const auto world_transform_opengl = Renderer2DUtils::to_opengl_mat3(transform);
        // std::array<float,9> world_transform_opengl{ 128.f, 0.0f, 0.0f, 0.0f, 128.f, 0.0f, 0.0f,0.0f, 1.0f };
        GL::UniformMatrix3fv(locations.at("uModel"), 1, GL_FALSE, world_transform_opengl.data());
    
        GL::UniformMatrix3fv(locations.at("uTexCoordTransform"), 1, GL_FALSE, texture_transform.data());
    
    
        GL::Uniform1f(locations.at("uDepth"), depth);
    
    
        const auto colors = unpack_color(tintColor);
        GL::Uniform4f(locations.at("uTint"), colors[0], colors[1], colors[2], colors[3]);
    
    
        //- Draw using quad VAO and index buffer
        GL::BindVertexArray(quad.modelHandle);
        constexpr GLenum  primitive_pattern        = GL_TRIANGLES;
        constexpr GLenum  indices_type             = GL_UNSIGNED_BYTE;
        constexpr GLvoid* byte_offset_into_indices = nullptr;
        GL::DrawElements(primitive_pattern, quad.indicesCount, indices_type, byte_offset_into_indices);
        ++draw_call;
        ++texture_call;
        GL::BindTexture(GL_TEXTURE_2D, 0);
        GL::BindVertexArray(0);
        GL::UseProgram(0);
    }
    
    void ImmediateRenderer2D::DrawCircle(const Math::TransformationMatrix& transform, CS200::RGBA fill_color, CS200::RGBA line_color, double line_width, float depth)
    {
        DrawSDF(transform, fill_color, line_color, line_width, SDFShape::Circle, depth);
    }
    
    void ImmediateRenderer2D::DrawRectangle(const Math::TransformationMatrix& transform, CS200::RGBA fill_color, CS200::RGBA line_color, double line_width, float depth)
    {
        DrawSDF(transform, fill_color, line_color, line_width, SDFShape::Rectangle, depth);
    }
    
    void ImmediateRenderer2D::DrawLine(const Math::TransformationMatrix& transform, Math::vec2 start_point, Math::vec2 end_point, CS200::RGBA line_color, double line_width, float depth)
    {
        const auto line_transform = Renderer2DUtils::CalculateLineTransform(transform, start_point, end_point, line_width);
        DrawSDF(line_transform, line_color, line_color, line_width, SDFShape::Rectangle, depth);
    }
    
    void ImmediateRenderer2D::DrawLine(Math::vec2 start_point, Math::vec2 end_point, CS200::RGBA line_color, double line_width, float depth)
    {
        DrawLine(Math::TransformationMatrix{}, start_point, end_point, line_color, line_width, depth);
    }
    
    void ImmediateRenderer2D::updateCameraUniformValues(const Math::TransformationMatrix& view_projection)
    {
        const auto as_3x3 = Renderer2DUtils::to_opengl_mat3(view_projection);
        for (std::size_t col = 0; col < 3; ++col)
        {
            const std::size_t src_offset = col * 3;
            const std::size_t dst_offset = col * 4;
    
            camera_array[dst_offset + 0] = as_3x3[src_offset + 0]; // how?****
            camera_array[dst_offset + 1] = as_3x3[src_offset + 1];
            camera_array[dst_offset + 2] = as_3x3[src_offset + 2];
            camera_array[dst_offset + 3] = 0.0f;
        }
    }
    
    void ImmediateRenderer2D::DrawSDF(const Math::TransformationMatrix& transform, CS200::RGBA fill_color, CS200::RGBA line_color, double line_width, SDFShape sdf_shape, float depth)
    {
        GL::UseProgram(sdfShader.Shader);
        // Calculate SDF-specific transform using Renderer2DUtils::CalculateSDFTransform()
        const auto  sdf_transform = Renderer2DUtils::CalculateSDFTransform(transform, line_width);
        // Set all SDF shader uniforms (model, colors, size, line width, shape type)
        const auto& locations     = sdfShader.UniformLocations;
    
        // vertex
       //GL::UniformMatrix3fv(locations.at("uToNDC"), 1, GL_FALSE, CS200::Renderer2DUtils::to_opengl_mat3(CS200::build_ndc_matrix(Engine::GetWindow().GetSize())).data());
        GL::UniformMatrix3fv(locations.at("uModel"), 1, GL_FALSE, sdf_transform.QuadTransform.data());
        GL::Uniform2f(locations.at("uSDFScale"), sdf_transform.QuadSize[0], sdf_transform.QuadSize[1]);
        GL::Uniform1f(locations.at("uDepth"), depth);
    
        // fragment
        GL::Uniform4fv(locations.at("uFillColor"), 1, CS200::unpack_color(fill_color).data());
        GL::Uniform4fv(locations.at("uLineColor"), 1, CS200::unpack_color(line_color).data());
        GL::Uniform2fv(locations.at("uWorldSize"), 1, sdf_transform.WorldSize.data());
        GL::Uniform1f(locations.at("uLineWidth"), static_cast<float>(line_width));
        GL::Uniform1i(locations.at("uShape"), static_cast<int>(sdf_shape));
    
        // Use SDF vertex array and draw triangles
        GL::BindVertexArray(sdfVeretexArrayHandle);
        constexpr GLenum  primitive_pattern        = GL_TRIANGLES;
        constexpr GLenum  indices_type             = GL_UNSIGNED_BYTE;
        constexpr GLvoid* byte_offset_into_indices = nullptr;
        GL::DrawElements(primitive_pattern, quad.indicesCount, indices_type, byte_offset_into_indices);
        ++draw_call;
        ++texture_call;
        // Shape rendering handled entirely in fragment shader
        GL::BindVertexArray(0);
        GL::UseProgram(0);
    }
    
    size_t ImmediateRenderer2D::GetDrawCallCounter()
    {
        return draw_call;
    }
    
    size_t ImmediateRenderer2D::GetDrawTextureCounter()
    {
        return texture_call;
    }
    
    
    ImmediateRenderer2D::ImmediateRenderer2D(ImmediateRenderer2D&& other) noexcept
        : quad(other.quad),                                                   // 1.
          texturingCombineShader(std::move(other.texturingCombineShader)), // 2.
          camera_uniform_buffer(other.camera_uniform_buffer),               // 3.
          sdfBufferHandle(other.sdfBufferHandle),                           // 4.
          sdfShader(std::move(other.sdfShader)),                           // 5.
          sdfVeretexArrayHandle(other.sdfVeretexArrayHandle),               // 6.
          camera_array(other.camera_array),                                   // 7.
          currentCameraMatrix(other.currentCameraMatrix),                   // 8.
          draw_call(other.draw_call),                                       // 9.
          texture_call(other.texture_call)                                   // 10.
    {
        other.quad.positionBufferHandle = 0;
        other.quad.texCoordBufferHandle = 0;
        other.quad.indexBufferHandle    = 0;
        other.quad.indicesCount            = 0;
        other.quad.modelHandle            = 0;
    
        other.texturingCombineShader = {};
        other.camera_uniform_buffer     = 0;
        other.sdfBufferHandle         = 0;
        other.sdfShader                 = {};
        other.sdfVeretexArrayHandle     = 0;
    
        other.draw_call       = 0;
        other.texture_call = 0;
    }
    
    ImmediateRenderer2D& ImmediateRenderer2D::operator=(ImmediateRenderer2D&& other) noexcept
    {
        //- Use std::swap to exchange all resources
        //- Safely handles self-assignment
    
        if (this == &other)
        {
            return *this;
        }
    
        std::swap(quad, other.quad);
        std::swap(texturingCombineShader, other.texturingCombineShader);
        std::swap(camera_uniform_buffer, other.camera_uniform_buffer);
        std::swap(sdfBufferHandle, other.sdfBufferHandle);
        std::swap(sdfShader, other.sdfShader);
        std::swap(sdfVeretexArrayHandle, other.sdfVeretexArrayHandle);
        std::swap(camera_array, other.camera_array);
        std::swap(currentCameraMatrix, other.currentCameraMatrix);
        std::swap(draw_call, other.draw_call);
        std::swap(texture_call, other.texture_call);
    
        return *this;
    }
    
    ImmediateRenderer2D::~ImmediateRenderer2D()
    {
        Shutdown();
    }

}

================================================
FILE: source/CS200/ImmediateRenderer2D.hpp
================================================
/**

* \file
* \author Rudy Castan
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once

#include "Engine/Matrix.hpp"
#include "IRenderer2D.hpp"
#include "OpenGL/Shader.hpp"
#include "OpenGL/VertexArray.hpp"
#include <array>

namespace CS200
{
    /**
     * \brief Immediate-mode 2D renderer for drawing sprites, shapes, and lines
     *
     * ImmediateRenderer2D provides a simple, immediate-mode interface for 2D graphics rendering.
     * "Immediate mode" means each draw call renders directly to the screen without batching or
     * optimization - perfect for learning graphics programming and prototyping.
     *
     * Key Features:
     * - Textured quad rendering with tint colors and texture coordinate mapping
     * - SDF (Signed Distance Field) based shape rendering for perfect circles and rectangles
     * - Line rendering with arbitrary thickness
     * - Camera/view-projection matrix support for world-to-screen transformations
     * - Hardware-accelerated OpenGL rendering with custom shaders
     *
     * Rendering Pipeline:
     * 1. Init() - Set up OpenGL resources (shaders, buffers, vertex arrays)
     * 2. BeginScene() - Set camera/view matrix for the frame
     * 3. Draw*() calls - Render individual primitives immediately
     * 4. EndScene() - Finalize the frame (currently no-op)
     * 5. Shutdown() - Clean up OpenGL resources
     *
     * Technical Implementation:
     * - Uses two rendering paths: textured quads and SDF shapes
     * - Quad rendering: Standard texture mapping with transform and tint
     * - SDF rendering: Fragment shader-based shapes with perfect edges and outlines
     * - Uniform buffer for camera data shared between shaders
     * - Immediate submission to GPU (no batching)
     *
     * Common Use Cases:
     * - Sprite rendering for games (characters, backgrounds, UI)
     * - Debug visualization (bounding boxes, collision shapes)
     * - Simple 2D graphics applications
     * - Educational graphics programming
     *
     * Example Usage:
     * \code
     * // Create and initialize renderer (typically done in Engine initialization)
     * ImmediateRenderer2D renderer;
     * renderer.Init();
     *
     * // In your game loop update/draw function:
     *
     * // Set up NDC camera matrix for screen-space rendering
     * Math::ivec2 screen_size = {800, 600};  // Your window/viewport size
     * auto ndc_matrix = CS200::build_ndc_matrix(screen_size);
     * renderer.BeginScene(ndc_matrix);
     *
     * // Draw a textured sprite (position/rotation/scale transform)
     * auto sprite_transform = Math::TranslationMatrix({100, 200}) *
     *                        Math::RotationMatrix(45.0) *
     *                        Math::ScaleMatrix({64, 64});
     * renderer.DrawQuad(sprite_transform, texture_handle, {0,0}, {1,1}, CS200::WHITE);
     *
     * // Draw shapes with fills and outlines
     * auto circle_transform = Math::TranslationMatrix({300, 300}) * Math::ScaleMatrix({50, 50});
     * renderer.DrawCircle(circle_transform, CS200::WHITE, CS200::BLACK, 2.0);
     *
     * // Draw debug lines
     * renderer.DrawLine({0, 0}, {100, 100}, CS200::WHITE, 1.0);
     *
     * renderer.EndScene();
     *
     * // Cleanup when shutting down
     * renderer.Shutdown();
     * \endcode
     */
    class ImmediateRenderer2D : public IRenderer2D
    {
    public:
        /**
         * \brief Default constructor - creates uninitialized renderer
         *
         * Implementation notes:
         * - Initialize all handles/resources to invalid/zero values
         * - Must call Init() before use
         */
        ImmediateRenderer2D() = default;

        /**
         * \brief Copy constructor deleted - renderer manages unique OpenGL resources
         */
        ImmediateRenderer2D(const ImmediateRenderer2D& other) = delete;
    
        /**
         * \brief Move constructor - transfer ownership of OpenGL resources
         * \param other The renderer to move from
         *
         * Implementation notes:
         * - Transfer all OpenGL handles (VAOs, buffers, shaders)
         * - Set source object's handles to zero/invalid
         * - Move shader objects using std::move()
         * - Copy view projection matrix data
         */
        ImmediateRenderer2D(ImmediateRenderer2D&& other) noexcept;
    
        /**
         * \brief Copy assignment deleted - renderer manages unique OpenGL resources
         */
        ImmediateRenderer2D& operator=(const ImmediateRenderer2D& other) = delete;
    
        /**
         * \brief Move assignment - transfer ownership of OpenGL resources
         * \param other The renderer to move from
         * \return Reference to this object
         *
         * Implementation notes:
         * - Use std::swap to exchange all resources
         * - Safely handles self-assignment
         * - Automatic cleanup of previous resources
         */
        ImmediateRenderer2D& operator=(ImmediateRenderer2D&& other) noexcept;
    
        /**
         * \brief Destructor - automatically cleans up OpenGL resources
         *
         * Implementation notes:
         * - Call Shutdown() to clean up resources
         * - Safe to call even if Init() was never called
         */
        ~ImmediateRenderer2D() override;
    
        /**
         * \brief Initialize OpenGL resources for rendering
         *
         * Implementation notes:
         * - Create index buffer with quad indices (0,1,2,2,3,0)
         * - Create vertex buffer with quad vertices (-0.5 to 0.5 range)
         * - Set up VAO with position and texture coordinate attributes
         * - Create SDF vertex buffer (position-only attributes) 
         * - Load and compile vertex/fragment shaders from Assets/shaders/
         * - Create uniform buffer for camera/view-projection matrix
         * - Bind uniform buffer to both shaders with name "Camera"
         */
        void Init() override;
    
        /**
         * \brief Clean up all OpenGL resources
         *
         * Implementation notes:
         * - Delete all vertex arrays, buffers using OpenGL delete functions
         * - Destroy shader programs using OpenGL::DestroyShader()
         * - Set all handles back to zero/invalid
         * - Safe to call multiple times
         */
        void Shutdown() override;
    
        /**
         * \brief Begin a new frame with camera/view transformation
         * \param view_projection Combined view and projection matrix for the frame
         *
         * Implementation notes:
         * - Convert 3x3 matrix to 4x3 format for uniform buffer
         * - Update uniform buffer with new matrix data
         * - Bind uniform buffer for use by shaders
         * - Store matrix for potential later use
         */
        void BeginScene(const Math::TransformationMatrix& view_projection) override;
    
        /**
         * \brief End the current frame (currently no operations needed)
         *
         * Implementation notes:
         * - No cleanup or finalization needed for immediate mode
         * - Could be used for debugging/profiling in future
         */
        void EndScene() override;
    
        /**
         * \brief Draw a textured quad with transformation and tinting
         * \param transform World transformation matrix (position, rotation, scale)
         * \param texture OpenGL texture handle to sample from
         * \param texture_coord_bl Bottom-left texture coordinate (typically {0,0})
         * \param texture_coord_tr Top-right texture coordinate (typically {1,1})
         * \param tintColor Color to multiply with texture (RGBA::White for no tint)
         *
         * Implementation notes:
         * - Calculate texture coordinate transformation matrix
         * - Set shader uniforms: model matrix, depth, texture transform, tint color
         * - Bind texture to texture unit 0
         * - Draw using quad VAO and index buffer
         * - Use GL_TRIANGLES with 6 indices (2 triangles)
         */
        void DrawQuad(const Math::TransformationMatrix& transform, OpenGL::TextureHandle texture, Math::vec2 texture_coord_bl, Math::vec2 texture_coord_tr, CS200::RGBA tintColor, float depth) override;
    
        /**
         * \brief Draw a filled circle with optional outline using SDF rendering
         * \param transform World transformation matrix (position, rotation, scale)
         * \param fill_color Interior color of the circle
         * \param line_color Outline color of the circle
         * \param line_width Width of the outline in world units
         *
         * Implementation notes:
         * - Use SDF (Signed Distance Field) shader for perfect circle
         * - Call DrawSDF() with SDFShape::Circle
         * - Radius determined by transform scale
         */
        void DrawCircle(const Math::TransformationMatrix& transform, CS200::RGBA fill_color, CS200::RGBA line_color, double line_width, float depth) override;
        /**
         * \brief Draw a filled rectangle with optional outline using SDF rendering
         * \param transform World transformation matrix (position, rotation, scale)
         * \param fill_color Interior color of the rectangle
         * \param line_color Outline color of the rectangle
         * \param line_width Width of the outline in world units
         *
         * Implementation notes:
         * - Use SDF (Signed Distance Field) shader for perfect rectangle
         * - Call DrawSDF() with SDFShape::Rectangle
         * - Size determined by transform scale
         */
        void DrawRectangle(const Math::TransformationMatrix& transform, CS200::RGBA fill_color, CS200::RGBA line_color, double line_width, float depth) override;
        /**
         * \brief Draw a line segment with specified thickness
         * \param transform Additional transformation to apply to the line
         * \param start_point Starting point of the line in local coordinates
         * \param end_point Ending point of the line in local coordinates
         * \param line_color Color of the line
         * \param line_width Thickness of the line in world units
         *
         * Implementation notes:
         * - Calculate line transformation using Renderer2DUtils::CalculateLineTransform()
         * - Draw as a rotated/scaled rectangle using SDF rendering
         * - Both fill and line colors set to same value
         */
        void DrawLine(const Math::TransformationMatrix& transform, Math::vec2 start_point, Math::vec2 end_point, CS200::RGBA line_color, double line_width, float depth) override;
        /**
         * \brief Draw a line segment with specified thickness (identity transform)
         * \param start_point Starting point of the line in world coordinates
         * \param end_point Ending point of the line in world coordinates
         * \param line_color Color of the line
         * \param line_width Thickness of the line in world units
         *
         * Implementation notes:
         * - Convenience overload that calls other DrawLine() with identity matrix
         * - Useful for simple line drawing without additional transformations
         */
        void DrawLine(Math::vec2 start_point, Math::vec2 end_point, CS200::RGBA line_color, double line_width, float depth) override;
    private:
    
        struct object
        {
            OpenGL::BufferHandle      positionBufferHandle{};
            OpenGL::BufferHandle      texCoordBufferHandle{};
            OpenGL::BufferHandle      indexBufferHandle{};
            GLsizei                   indicesCount{};
            OpenGL::VertexArrayHandle modelHandle{};
        } quad{};
    
        OpenGL::CompiledShader texturingCombineShader{};
        OpenGL::BufferHandle   camera_uniform_buffer{};
    
        //sdf
        OpenGL::BufferHandle      sdfBufferHandle{};
        OpenGL::CompiledShader    sdfShader{};
        OpenGL::VertexArrayHandle sdfVeretexArrayHandle{};
    
    
        std::array<float, 12> camera_array{};
    
        /**
         * \brief Helper function for converting 3x3 matrix to 4x3 format for uniform buffer
         * \param view_projection Combined view and projection matrix for the frame
         *
         */
        void updateCameraUniformValues(const Math::TransformationMatrix& view_projection);
    
        Math::TransformationMatrix currentCameraMatrix{};
    
        // SDF Shape identifiers - must be kept in sync with sdf.frag shader
        enum class SDFShape : uint8_t
        {
            Circle    = 0,
            Rectangle = 1,
        };
    
        /**
         * \brief Internal SDF rendering function used by shape drawing methods
         * \param transform World transformation matrix
         * \param fill_color Interior color of the shape
         * \param line_color Outline color of the shape
         * \param line_width Width of the outline in world units
         * \param sdf_shape Type of SDF shape to render
         *
         * Implementation notes:
         * - Calculate SDF-specific transform using Renderer2DUtils::CalculateSDFTransform()
         * - Set all SDF shader uniforms (model, colors, size, line width, shape type)
         * - Use SDF vertex array and draw triangles
         * - Shape rendering handled entirely in fragment shader
         */
        void DrawSDF(const Math::TransformationMatrix& transform, CS200::RGBA fill_color, CS200::RGBA line_color, double line_width, SDFShape sdf_shape, float depth);
    
        size_t draw_call = 0;
        size_t GetDrawCallCounter() override;
    
        size_t texture_call = 0;
        size_t GetDrawTextureCounter() override;
    };

}

================================================
FILE: source/CS200/InstancedRenderer2D.cpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "InstancedRenderer2D.hpp"

#include "Engine/Path.hpp"

#include "OpenGL/Buffer.hpp"
#include "OpenGL/GL.hpp"
#include "OpenGL/VertexArray.hpp"
#include "Renderer2DUtils.hpp"

#include <fstream>
#include <numeric>
#include <sstream>

namespace CS200

{

    InstancedRenderer2D::InstancedRenderer2D([[maybe_unused]] unsigned max_sprites)
    {
        maxInstances    = max_sprites;
        maxSDFInstances = max_sprites;
        instanceData.reserve(maxInstances);
        sdfInstanceData.reserve(maxSDFInstances);
    }
    
    InstancedRenderer2D::InstancedRenderer2D(InstancedRenderer2D&& other) noexcept
        : instanceData(std::move(other.instanceData)),
          texturingCombineShader(std::move(other.texturingCombineShader)),
          fixedVertexBufferHandle(other.fixedVertexBufferHandle),
          instanceBufferHandle(other.instanceBufferHandle),
          modelHandle(other.modelHandle),
          sdfFixedVertexBufferHandle(other.sdfFixedVertexBufferHandle),
          sdfInstanceBufferHandle(other.sdfInstanceBufferHandle),
          sdfInstanceData(std::move(other.sdfInstanceData)),
          sdfShader(std::move(other.sdfShader)),
          sdfModelHandle(other.sdfModelHandle),
          maxSDFInstances(other.maxSDFInstances),
          indexBufferHandle(other.indexBufferHandle),
          camera_uniform_buffer(other.camera_uniform_buffer),
          camera_array(other.camera_array),
          currentCameraMatrix(other.currentCameraMatrix),
          maxInstances(other.maxInstances),
          textureSlots(std::move(other.textureSlots)),
          activeTextureSize(other.activeTextureSize),
          draw_call(other.draw_call),
          texture_call(other.texture_call)
    {
        other.fixedVertexBufferHandle     = 0;
        other.instanceBufferHandle         = 0;
        other.modelHandle                 = 0;
        other.sdfFixedVertexBufferHandle = 0;
        other.sdfInstanceBufferHandle     = 0;
        other.sdfModelHandle             = 0;
        other.indexBufferHandle             = 0;
        other.camera_uniform_buffer         = 0;
    
        other.texturingCombineShader = {};
        other.sdfShader                 = {};
    
        other.maxInstances        = 0;
        other.maxSDFInstances    = 0;
        other.activeTextureSize = 0;
        other.draw_call            = 0;
        other.texture_call        = 0;
    }
    
    InstancedRenderer2D& InstancedRenderer2D::operator=(InstancedRenderer2D&& other) noexcept
    {
        std::swap(instanceData, other.instanceData);
        std::swap(texturingCombineShader, other.texturingCombineShader);
        std::swap(fixedVertexBufferHandle, other.fixedVertexBufferHandle);
        std::swap(instanceBufferHandle, other.instanceBufferHandle);
        std::swap(modelHandle, other.modelHandle);
    
        std::swap(sdfInstanceData, other.sdfInstanceData);
        std::swap(sdfFixedVertexBufferHandle, other.sdfFixedVertexBufferHandle);
        std::swap(sdfInstanceBufferHandle, other.sdfInstanceBufferHandle);
        std::swap(sdfShader, other.sdfShader);
        std::swap(sdfModelHandle, other.sdfModelHandle);
        std::swap(maxSDFInstances, other.maxSDFInstances);
    
        std::swap(indexBufferHandle, other.indexBufferHandle);
        std::swap(camera_uniform_buffer, other.camera_uniform_buffer);
        std::swap(camera_array, other.camera_array);
        std::swap(currentCameraMatrix, other.currentCameraMatrix);
        std::swap(maxInstances, other.maxInstances);
        std::swap(textureSlots, other.textureSlots);
        std::swap(activeTextureSize, other.activeTextureSize);
        std::swap(draw_call, other.draw_call);
        std::swap(texture_call, other.texture_call);
    
        return *this;
    }
    
    InstancedRenderer2D::~InstancedRenderer2D()
    {
        Shutdown();
    }
    
    void InstancedRenderer2D::Init()
    
    {
        // get max texture units
        // get glsl code and update the fragment shader
        // create the shader
        // set th binding values for textures array
    
        // get how many texture opengl can draw
        GLint max_tex_units = 0;
        GL::GetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_tex_units); // check with docs.gl to get minimum(16) and maximum
        textureSlots.resize(static_cast<size_t>(std::min(max_tex_units, 64)));
    
    
        // load shaders with parsing
        const std::filesystem::path vertex_file = assets::locate_asset("Assets/shaders/InstancedRenderer2D/quad.vert");
        std::ifstream                vert_stream(vertex_file);
        std::stringstream            vert_text_stream;
        vert_text_stream << vert_stream.rdbuf();
        const std::string vertex_glsl = vert_text_stream.str();
    
        const std::filesystem::path fragment_file = assets::locate_asset("Assets/shaders/InstancedRenderer2D/quad.frag");
        std::ifstream                frag_stream(fragment_file);
        std::stringstream            frag_text_stream;
        frag_text_stream << frag_stream.rdbuf();
        std::string frag_glsl = frag_text_stream.str();
    
        const size_t      first_newline = frag_glsl.find('\n');
        const std::string define_line    = "\n#define MAX_TEXTURE_SLOTS " + std::to_string(textureSlots.size());
        frag_glsl.insert(first_newline, define_line);
    
        texturingCombineShader = OpenGL::CreateShader(std::string_view{ vertex_glsl }, std::string_view{ frag_glsl });
    
        // have to set their binding index
        GL::UseProgram(texturingCombineShader.Shader);
    
        std::vector<int> sampler_binding_values(textureSlots.size());
        std::iota(sampler_binding_values.begin(), sampler_binding_values.end(), 0);
        const GLint location = GL::GetUniformLocation(texturingCombineShader.Shader, "uTextures");
        GL::Uniform1iv(location, static_cast<GLsizei>(textureSlots.size()), sampler_binding_values.data());
    
        GL::UseProgram(0);
    
        // create our fixed buffer data
        // create index buffer data
        // create our instanced buffer
        // create VAO
    
        constexpr float fixed_sprite_vertices[][4] = {
            // bottom left
            { -0.5f, -0.5f, 0.0f, 0.0f },
            // bottom right
            {  0.5f, -0.5f, 1.0f, 0.0f },
            // top right
            {  0.5f,    0.5f, 1.0f, 1.0f },
            // top left
            { -0.5f,     0.5f, 0.0f, 1.0f }
        };
    
        constexpr unsigned char indicies[] = { 0, 1, 2, 0, 2, 3 };
    
        fixedVertexBufferHandle = OpenGL::CreateBuffer(OpenGL::BufferType::Vertices, std::as_bytes(std::span{ fixed_sprite_vertices }));
        indexBufferHandle        = OpenGL::CreateBuffer(OpenGL::BufferType::Indices, std::as_bytes(std::span{ indicies }));
        instanceBufferHandle    = OpenGL::CreateBuffer(OpenGL::BufferType::Vertices, static_cast<GLsizeiptr>(sizeof(QuadInstance) * maxInstances));
    
        auto fixedbuffer_and_instancebuffer = {
            OpenGL::VertexBuffer{ fixedVertexBufferHandle,{ OpenGL::Attribute::Float2, OpenGL::Attribute::Float2 }                    },
            OpenGL::VertexBuffer{      instanceBufferHandle,
                                  { OpenGL::Attribute::Float3.WithDivisor(1), OpenGL::Attribute::Float3.WithDivisor(1), OpenGL::Attribute::UByte4ToNormalized.WithDivisor(1),
                                    OpenGL::Attribute::Float2.WithDivisor(1), OpenGL::Attribute::Float2.WithDivisor(1), OpenGL::Attribute::Int.WithDivisor(1),
                                    OpenGL::Attribute::Float.WithDivisor(1) } }
        };
    
        modelHandle = OpenGL::CreateVertexArrayObject(fixedbuffer_and_instancebuffer, indexBufferHandle);
    
        // SDF
        //  create vertex array object, buffer vertices, buffer indices
        sdfShader = OpenGL::CreateShader(assets::locate_asset("Assets/shaders/InstancedRenderer2D/sdf.vert"), assets::locate_asset("Assets/shaders/InstancedRenderer2D/sdf.frag"));
    
        constexpr float position_vertices[][2] = {
            // bottom left
            { -0.5f, -0.5f },
            // bottom right
            {  0.5f, -0.5f },
            // top right
            {  0.5f,    0.5f },
            // top left
            { -0.5f,     0.5f }
        };
        sdfFixedVertexBufferHandle = OpenGL::CreateBuffer(OpenGL::BufferType::Vertices, std::as_bytes(std::span{ position_vertices }));
        sdfInstanceBufferHandle       = OpenGL::CreateBuffer(OpenGL::BufferType::Vertices, static_cast<GLsizeiptr>(sizeof(SDFInstance) * maxInstances));
    
        const auto sdf_fix_instance = {
            OpenGL::VertexBuffer{ sdfFixedVertexBufferHandle,{ OpenGL::Attribute::Float2 }    }, //  Layout 0: aModelPosition                                                        },
            OpenGL::VertexBuffer{      sdfInstanceBufferHandle,
                                  {
                                  OpenGL::Attribute::Float3.WithDivisor(1),                // Layout 1: aModelRow0
                                  OpenGL::Attribute::Float3.WithDivisor(1),                // Layout 2: aModelRow1
                                  OpenGL::Attribute::UByte4ToNormalized.WithDivisor(1), // Layout 3: aFillColor
                                  OpenGL::Attribute::UByte4ToNormalized.WithDivisor(1), // Layout 4: aLineColor
                                  OpenGL::Attribute::Float2.WithDivisor(1),                // Layout 5: aWorldSize
                                  OpenGL::Attribute::Float.WithDivisor(1),                // Layout 6: aLineWidth
                                  OpenGL::Attribute::Int.WithDivisor(1),                // Layout 7: aShape (0=Circle, 1=Rect)
                                  OpenGL::Attribute::Float.WithDivisor(1),                // Layout 8: aDepth
                                  } }
        };
        sdfModelHandle = OpenGL::CreateVertexArrayObject(sdf_fix_instance, indexBufferHandle);
    
        camera_uniform_buffer = OpenGL::CreateBuffer(OpenGL::BufferType::UniformBlocks, sizeof(camera_array));
        OpenGL::BindUniformBufferToShader(texturingCombineShader.Shader, 0, camera_uniform_buffer, "NDC");
        OpenGL::BindUniformBufferToShader(sdfShader.Shader, 0, camera_uniform_buffer, "NDC");
    }
    
    void InstancedRenderer2D::Shutdown()
    
    {
        OpenGL::DestroyShader(texturingCombineShader);
        OpenGL::DestroyShader(sdfShader);
    
        GL::DeleteBuffers(1, &fixedVertexBufferHandle), fixedVertexBufferHandle          = 0;
        GL::DeleteBuffers(1, &instanceBufferHandle), instanceBufferHandle              = 0;
        GL::DeleteBuffers(1, &sdfFixedVertexBufferHandle), sdfFixedVertexBufferHandle = 0;
        GL::DeleteBuffers(1, &sdfInstanceBufferHandle), sdfInstanceBufferHandle          = 0;
        GL::DeleteBuffers(1, &indexBufferHandle), indexBufferHandle                      = 0;
        GL::DeleteBuffers(1, &camera_uniform_buffer), camera_uniform_buffer              = 0;
    
        GL::DeleteVertexArrays(1, &modelHandle), modelHandle       = 0;
        GL::DeleteVertexArrays(1, &sdfModelHandle), sdfModelHandle = 0;
    
        instanceData.clear();
        sdfInstanceData.clear();
        textureSlots.clear();
    
        activeTextureSize = 0;
        draw_call          = 0;
        texture_call      = 0;
    }
    
    void InstancedRenderer2D::BeginScene(const Math::TransformationMatrix& view_projection)
    {
        //- Store matrix for potential later use
        currentCameraMatrix = view_projection;
    
        //- Convert 3x3 matrix to 4x3 format for uniform buffer
        updateCameraUniformValues(currentCameraMatrix);
    
    
        //- Update uniform buffer with new matrix data
        OpenGL::UpdateBufferData(OpenGL::BufferType::UniformBlocks, camera_uniform_buffer, std::as_bytes(std::span{ camera_array }));
    
        //- Bind uniform buffer for use by shaders
        GL::BindBuffer(GL_UNIFORM_BUFFER, camera_uniform_buffer);
    
        draw_call     = 0;
        texture_call = 0;
        startBatch();
    }
    
    void InstancedRenderer2D::EndScene()
    {
        flush();
    }
    
    void InstancedRenderer2D::DrawQuad(
        const Math::TransformationMatrix& transform, OpenGL::TextureHandle texture, Math::vec2 texture_coord_bl, Math::vec2 texture_coord_tr, CS200::RGBA tintColor, float depth)
    {
        if (instanceData.size() >= maxInstances)
        {
            flush();
        }
    
        if (sdfInstanceData.size() >= maxSDFInstances)
        {
            flush();
        }
        int tex_index = 0;
        bool found = false;
    
        for (size_t i = 0; i < activeTextureSize; ++i)
        {
            if (textureSlots[i] == texture)
            {
                found = true;
                tex_index = static_cast<int>(i);
            }
        }
    
    
        if (!found)
        {
            if (activeTextureSize >= textureSlots.size())
            {
                flush();
            }
            tex_index = static_cast<int>(activeTextureSize);
            textureSlots[activeTextureSize] = texture;
            ++activeTextureSize;
        }
    
    
        const float left = static_cast<float>(texture_coord_bl.x);
        const float bottom = static_cast<float>(texture_coord_bl.y);
        const float right = static_cast<float>(texture_coord_tr.x);
        const float top = static_cast<float>(texture_coord_tr.y);
    
        QuadInstance instance;
        instance.textureIndex = tex_index;
        instance.texScale[0] = right - left;
        instance.texScale[1] = top - bottom;
        instance.texOffset[0] = left;
        instance.texOffset[1] = bottom;
        instance.transformrow0[0] = static_cast<float>(transform[0][0]);
        instance.transformrow0[1] = static_cast<float>(transform[0][1]);
        instance.transformrow0[2] = static_cast<float>(transform[0][2]);
        instance.transformrow1[0] = static_cast<float>(transform[1][0]);
        instance.transformrow1[1] = static_cast<float>(transform[1][1]);
        instance.transformrow1[2] = static_cast<float>(transform[1][2]);
        instance.tint = ColorArray(tintColor);
        instance.depth              = depth;
    
        instanceData.push_back(instance);
    
        ++texture_call;
    }
    
    void InstancedRenderer2D::startBatch()
    
    {
        instanceData.clear();
    
        activeTextureSize = 0;
    
    
        sdfInstanceData.clear();
    }
    
    void InstancedRenderer2D::flush()
    {
        if (!instanceData.empty()) [[unlikely]]
        {
            GL::BindBuffer(GL_ARRAY_BUFFER, instanceBufferHandle);
            GL::BufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(QuadInstance) * maxInstances), nullptr, GL_DYNAMIC_DRAW);
            OpenGL::UpdateBufferData(OpenGL::BufferType::Vertices, instanceBufferHandle, std::as_bytes(std::span{ instanceData.data(), instanceData.size() }));
    
            // select our texture
            for (size_t i = 0; i < activeTextureSize; ++i)
            {
                GL::ActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + i));
                GL::BindTexture(GL_TEXTURE_2D, textureSlots[i]);
            }
            GL::UseProgram(texturingCombineShader.Shader);
            GL::BindVertexArray(modelHandle);
            GL::DrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr, static_cast<GLsizei>(instanceData.size()));
            ++draw_call;
        }
    
        if (!sdfInstanceData.empty())
        {
            GL::BindBuffer(GL_ARRAY_BUFFER, sdfInstanceBufferHandle);
            GL::BufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(SDFInstance) * maxSDFInstances), nullptr, GL_DYNAMIC_DRAW);
    
            OpenGL::UpdateBufferData(OpenGL::BufferType::Vertices, sdfInstanceBufferHandle, std::as_bytes(std::span{ sdfInstanceData.data(), sdfInstanceData.size() }));
    
            GL::UseProgram(sdfShader.Shader);
            GL::BindVertexArray(sdfModelHandle);
            GL::DrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr, static_cast<GLsizei>(sdfInstanceData.size()));
            ++draw_call;
        }
        GL::BindVertexArray(0);
        GL::UseProgram(0);
        GL::BindTexture(GL_TEXTURE_2D, 0);
        GL::BindBuffer(GL_ARRAY_BUFFER, 0);
    
        startBatch();
    }
    
    void InstancedRenderer2D::DrawCircle(
        [[maybe_unused]] const Math::TransformationMatrix& transform, [[maybe_unused]] CS200::RGBA fill_color, [[maybe_unused]] CS200::RGBA line_color, [[maybe_unused]] double line_width, float depth)
    {
        if (instanceData.size() >= maxInstances)
        {
            flush();
        }
    
        if (sdfInstanceData.size() >= maxSDFInstances)
        {
            flush();
        }
    
        const auto sdf_transform = Renderer2DUtils::CalculateSDFTransform(transform, line_width);
        const auto fill_bytes     = ColorArray(fill_color);
        const auto line_bytes     = ColorArray(line_color);
    
        SDFInstance sdf_instance;
    
        sdf_instance.transformrow0[0] = static_cast<float>(transform[0][0]);
        sdf_instance.transformrow0[1] = static_cast<float>(transform[0][1]);
        sdf_instance.transformrow0[2] = static_cast<float>(transform[0][2]);
    
        sdf_instance.transformrow1[0] = static_cast<float>(transform[1][0]);
        sdf_instance.transformrow1[1] = static_cast<float>(transform[1][1]);
        sdf_instance.transformrow1[2] = static_cast<float>(transform[1][2]);
    
        sdf_instance.fillColor     = fill_bytes;
        sdf_instance.lineColor     = line_bytes;
        sdf_instance.worldSize_x = static_cast<float>(sdf_transform.WorldSize[0]);
        sdf_instance.worldSize_y = static_cast<float>(sdf_transform.WorldSize[1]);
        sdf_instance.lineWidth     = static_cast<float>(line_width);
        sdf_instance.shape         = static_cast<int>(SDFShape::Circle); // 0
        sdf_instance.depth         = depth;
    
        sdfInstanceData.push_back(sdf_instance);
    
        ++texture_call;
    }
    
    void InstancedRenderer2D::DrawRectangle(
        [[maybe_unused]] const Math::TransformationMatrix& transform, [[maybe_unused]] CS200::RGBA fill_color, [[maybe_unused]] CS200::RGBA line_color, [[maybe_unused]] double line_width, float depth)
    {
        if (instanceData.size() >= maxInstances)
        {
            flush();
        }
    
        if (sdfInstanceData.size() >= maxSDFInstances)
        {
            flush();
        }
    
        const auto sdf_transform = Renderer2DUtils::CalculateSDFTransform(transform, line_width);
        const auto fill_bytes     = ColorArray(fill_color);
        const auto line_bytes     = ColorArray(line_color);
    
        SDFInstance sdf_instance;
    
        sdf_instance.transformrow0[0] = static_cast<float>(transform[0][0]);
        sdf_instance.transformrow0[1] = static_cast<float>(transform[0][1]);
        sdf_instance.transformrow0[2] = static_cast<float>(transform[0][2]);
    
        sdf_instance.transformrow1[0] = static_cast<float>(transform[1][0]);
        sdf_instance.transformrow1[1] = static_cast<float>(transform[1][1]);
        sdf_instance.transformrow1[2] = static_cast<float>(transform[1][2]);
    
        sdf_instance.fillColor     = fill_bytes;
        sdf_instance.lineColor     = line_bytes;
        sdf_instance.worldSize_x = static_cast<float>(sdf_transform.WorldSize[0]);
        sdf_instance.worldSize_y = static_cast<float>(sdf_transform.WorldSize[1]);
        sdf_instance.lineWidth     = static_cast<float>(line_width);
        sdf_instance.shape         = static_cast<int>(SDFShape::Rectangle); // 1
        sdf_instance.depth         = depth;
    
        sdfInstanceData.push_back(sdf_instance);
    
        ++texture_call;
    }
    
    void InstancedRenderer2D::DrawLine(
        [[maybe_unused]] const Math::TransformationMatrix& transform, [[maybe_unused]] Math::vec2 start_point, [[maybe_unused]] Math::vec2 end_point, [[maybe_unused]] CS200::RGBA line_color,
        [[maybe_unused]] double line_width, float depth)
    {
        const auto line_transform = Renderer2DUtils::CalculateLineTransform(transform, start_point, end_point, line_width);
        DrawRectangle(line_transform, line_color, line_color, line_width, depth);
    }
    
    void InstancedRenderer2D::DrawLine(
        [[maybe_unused]] Math::vec2 start_point, [[maybe_unused]] Math::vec2 end_point, [[maybe_unused]] CS200::RGBA line_color, [[maybe_unused]] double line_width, float depth)
    {
        DrawLine(Math::TransformationMatrix{}, start_point, end_point, line_color, line_width, depth);
    }
    
    void InstancedRenderer2D::updateCameraUniformValues(const Math::TransformationMatrix& view_projection)
    {
        const auto as_3x3 = Renderer2DUtils::to_opengl_mat3(view_projection);
        for (std::size_t col = 0; col < 3; ++col)
        {
            const std::size_t src_offset = col * 3;
            const std::size_t dst_offset = col * 4;
    
    
            camera_array[dst_offset + 0] = as_3x3[src_offset + 0]; // how?****
            camera_array[dst_offset + 1] = as_3x3[src_offset + 1];
            camera_array[dst_offset + 2] = as_3x3[src_offset + 2];
            camera_array[dst_offset + 3] = 0.0f;
        }
    }
    
    size_t InstancedRenderer2D::GetDrawCallCounter()
    {
        return draw_call;
    }
    
    size_t InstancedRenderer2D::GetDrawTextureCounter()
    {
        return texture_call;
    }

}

================================================
FILE: source/CS200/InstancedRenderer2D.hpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#pragma once

#include "IRenderer2D.hpp"

#include "Engine/Matrix.hpp"

#include "OpenGL/Shader.hpp"
#include "OpenGL/VertexArray.hpp"
#include <array>
#include <vector>

/**
 one model,
 lots of instances
 sharing buffer static -> positions(because we use single quad!!)
and each instance has their own dynamic buffer

 ->color
 ->texture
 ->model xform
 ->texcoords xform
 */

namespace CS200
{
    class InstancedRenderer2D : public IRenderer2D
    {
    public:
        InstancedRenderer2D(unsigned max_sprites = 10'000); // means max_instances
        InstancedRenderer2D(const InstancedRenderer2D& other) = delete;
        InstancedRenderer2D(InstancedRenderer2D&& other) noexcept;
        InstancedRenderer2D& operator=(const InstancedRenderer2D& other) = delete;
        InstancedRenderer2D& operator=(InstancedRenderer2D&& other) noexcept;
        ~InstancedRenderer2D() override;

        void Init() override;
        void Shutdown() override;
        void BeginScene(const Math::TransformationMatrix& view_projection) override;
        void EndScene() override;
        void
            DrawQuad(const Math::TransformationMatrix& transform, OpenGL::TextureHandle texture, Math::vec2 texture_coord_bl, Math::vec2 texture_coord_tr, CS200::RGBA tintColor, float depth) override;
        // void DrawQuad(std::span<const float, 9> transform, OpenGL::Handle texture, std::span<const float, 4> texture_coords_lbrt, std::span<const float, 4> tint_color) override;
    
        void DrawCircle(const Math::TransformationMatrix& transform, CS200::RGBA fill_color, CS200::RGBA line_color, double line_width, float depth) override;
        void DrawRectangle(const Math::TransformationMatrix& transform, CS200::RGBA fill_color, CS200::RGBA line_color, double line_width, float depth) override;
        void DrawLine(const Math::TransformationMatrix& transform, Math::vec2 start_point, Math::vec2 end_point, CS200::RGBA line_color, double line_width, float depth) override;
        void DrawLine(Math::vec2 start_point, Math::vec2 end_point, CS200::RGBA line_color, double line_width, float depth) override;
    
    private:
        struct QuadInstance // maybe we can make more compact? bit width, ...
        {
            /*float x = 0, y = 0;*/                             // don't need for each instance anymore!!
            float                         transformrow0[3]{}; // instead having vertex for each instance, we have transform mat for each instance!
            float                         transformrow1[3]{};
            std::array<unsigned char, 4> tint{};        // caution !!! to use createvao helper func, make order same as in shader's attrib!!!!!
            /*float s = 0, t = 0;*/                        // don't need for each instance anymore!!
            float                         texScale[2]{}; // instead having texcoord for each instance, we have transform mat of texcoord for each instance with compacted version
            float                         texOffset[2]{};
            int                             textureIndex = 0;
            float                         depth          = 0.f;
        };
    
        std::vector<QuadInstance> instanceData{};
        OpenGL::CompiledShader      texturingCombineShader;
        OpenGL::BufferHandle      fixedVertexBufferHandle{};
        OpenGL::BufferHandle      instanceBufferHandle{};
        OpenGL::VertexArrayHandle modelHandle{};
    
        // sdf
        struct SDFInstance
        {
            // float                         x = 0, y = 0;
            float                         transformrow0[3]{};               // Layout 1: aModelRow0
            float                         transformrow1[3]{};               // Layout 2: aModelRow1
            std::array<unsigned char, 4> fillColor{};                       // Layout 3: aFillColor
            std::array<unsigned char, 4> lineColor{};                       // Layout 4: aLineColor
            float                         worldSize_x = 0, worldSize_y = 0; // Layout 5: aWorldSize
            float                         lineWidth = 0;                       // Layout 6: aLineWidth
            int                             shape       = 0;                       // Layout 7: aShape (0=Circle, 1=Rect)
            float                         depth       = 0.f;                       // Layout 8: aDepth
        };
    
        OpenGL::BufferHandle      sdfFixedVertexBufferHandle{};
        OpenGL::BufferHandle      sdfInstanceBufferHandle{};
        std::vector<SDFInstance>  sdfInstanceData{};
        OpenGL::CompiledShader      sdfShader{};
        OpenGL::VertexArrayHandle sdfModelHandle{};
    
        unsigned maxSDFInstances = 0;
    
        OpenGL::BufferHandle indexBufferHandle{};
    
        enum class SDFShape : uint8_t
        {
            Circle      = 0,
            Rectangle = 1,
        };
    
    
        // ndc block
    
        OpenGL::BufferHandle camera_uniform_buffer{};
    
        std::array<float, 12> camera_array{};
    
        Math::TransformationMatrix currentCameraMatrix{};
    
    
        unsigned maxInstances = 0;
    
    
        std::vector<OpenGL::TextureHandle> textureSlots;
    
        size_t activeTextureSize = 0;
    
    
    private:
    
        void updateCameraUniformValues(const Math::TransformationMatrix& view_projection);
    
        void flush(); // when quad amount is reached to max_quad
    
        void startBatch();
    
        size_t draw_call;
        size_t GetDrawCallCounter() override;
    
        size_t texture_call = 0;
        size_t GetDrawTextureCounter() override;
    };

}

================================================
FILE: source/CS200/IRenderer2D.hpp
================================================
/**

* \file
* \author Rudy Castan
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once

#include "Engine/Vec2.hpp"
#include "OpenGL/Texture.hpp"
#include "RGBA.hpp"

namespace Math
{
    class TransformationMatrix;
}

namespace CS200
{
    class IRenderer2D
    {
    public:

        virtual ~IRenderer2D() = default;
    
        virtual void Init() = 0;        
        virtual void Shutdown() = 0;
        virtual void BeginScene(const Math::TransformationMatrix& view_projection) = 0;
        virtual void EndScene() = 0;
    
        virtual void DrawQuad(
            const Math::TransformationMatrix& transform, OpenGL::TextureHandle texture, Math::vec2 texture_coord_bl = Math::vec2{ 0.0, 0.0 }, Math::vec2 texture_coord_tr = Math::vec2{ 1.0, 1.0 },
            CS200::RGBA tintColor = CS200::WHITE, float depth = 1.f) = 0;
        virtual void
            DrawCircle(const Math::TransformationMatrix& transform, CS200::RGBA fill_color = CS200::CLEAR, CS200::RGBA line_color = CS200::WHITE, double line_width = 2.0, float depth = 0.f) = 0;
        virtual void
            DrawRectangle(const Math::TransformationMatrix& transform, CS200::RGBA fill_color = CS200::CLEAR, CS200::RGBA line_color = CS200::WHITE, double line_width = 2.0, float depth = 0.f) = 0;
        virtual void
            DrawLine(const Math::TransformationMatrix& transform, Math::vec2 startPoint, Math::vec2 endPoint, CS200::RGBA line_color = CS200::WHITE, double line_width = 2.0, float depth = 0.f) = 0;
        virtual void DrawLine(Math::vec2 start_point, Math::vec2 end_point, CS200::RGBA line_color = CS200::WHITE, double line_width = 2.0, float depth = 0.f) = 0;
    
        virtual size_t GetDrawCallCounter() = 0;
        virtual size_t GetDrawTextureCounter() = 0;
    };

}

================================================
FILE: source/CS200/NDC.hpp
================================================
﻿/**

* \file
* \author Rudy Castan
* \author Taekyung ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once
  #include "Engine/Matrix.hpp"
  #include "Engine/Vec2.hpp"

namespace CS200
{
    /**
     * \brief Create a transformation matrix that converts screen coordinates to NDC
     * \param view_size Width and height of the viewport/screen in pixels
     * \return Transformation matrix for screen-to-NDC conversion
     *
     * \note The returned matrix transforms FROM screen coordinates TO NDC coordinates
     * \note This is typically used once per frame in BeginScene()
     * \note Screen coordinates assume (0,0) at bottom-left, (width,height) at top-right
     *
     * NDC (Normalized Device Coordinates) is a standard coordinate system used by graphics
     * APIs where all visible coordinates range from -1 to +1 in both X and Y axes.
     * This system is hardware-standard and allows graphics pipelines to work consistently
     * across different screen resolutions and aspect ratios.
     *
     * Purpose and Benefits:
     * - Provides resolution-independent coordinate system for rendering
     * - Standardizes coordinate space for graphics hardware (GPUs expect NDC)
     * - Enables consistent camera/viewport transformations
     * - Simplifies clipping and culling operations in graphics pipeline
     * - Makes shaders and rendering code portable across different screen sizes
     *
     * Coordinate System Mapping:
     * \code
     * We want to map (0, w) to (-1,1) and (0,h) to (-1,1)
     *             (w,h)                  (1,1)
     *      +--------+             +--------+
     *      |        |             |        |
     *      | cam    |     --->    | ndc    |
     *      +--------+             +--------+
     *    (0,0)                 (-1,-1)
     * \endcode
     *
     * Mathematical Transformation:
     * 1. Scale: Divide by half-dimensions to get 0-2 range
     * 2. Translate: Subtract 1 to center around origin (-1 to +1)
     * 3. Formula: ndc = (screen_coord / (dimension/2)) - 1
     *
     * Common Use Cases:
     * - Camera/view matrix setup for 2D rendering
     * - Converting mouse coordinates to world coordinates
     * - Setting up orthographic projections
     * - Viewport-independent UI positioning
     * - Cross-platform graphics coordinate normalization
     *
     * Integration with Graphics Pipeline:
     * Window Coordinates → World Coordinates → NDC → GPU Rendering
     */
    inline Math::TransformationMatrix build_ndc_matrix(Math::ivec2 view_size, [[maybe_unused]] bool is_centered = false) noexcept
    {
        if(is_centered)
        {
            return Math::ScaleMatrix({ 2.0 / view_size.x, 2.0 / view_size.y });
        }
        return Math::TranslationMatrix(Math::vec2{ -1.0, -1.0 }) * Math::ScaleMatrix({ 2.0 / view_size.x, 2.0 / view_size.y });
    }
}

================================================
FILE: source/CS200/Renderer2DUtils.cpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "Renderer2DUtils.hpp"

#include <algorithm>
#include <cmath>

namespace CS200::Renderer2DUtils
{
    Math::TransformationMatrix CalculateLineTransform(const Math::TransformationMatrix& transform, const Math::vec2& start_point, const Math::vec2& end_point, double line_width) noexcept
    {
        const Math::vec2 line_vector = end_point - start_point;

        const double            angle             = std::atan2(line_vector.y, line_vector.x);
        constexpr double        center_multiplier = 0.5;
        const Math::vec2        center_point      = (start_point + end_point) * center_multiplier;
        const Math::ScaleMatrix scale_matrix{
            { line_vector.Length(), line_width }
        };
        const Math::RotationMatrix    rotation_matrix{ angle };
        const Math::TranslationMatrix translation_matrix{ center_point };
        const auto                    final_transform = transform * translation_matrix * rotation_matrix * scale_matrix;
        return final_transform;
    }
    
    SDFTransform CalculateSDFTransform(const Math::TransformationMatrix& transform, double line_width) noexcept
    {
        const vec2  world_size{ static_cast<float>(std::sqrt(transform[0][0] * transform[0][0] + transform[1][0] * transform[1][0])),
                               static_cast<float>(std::sqrt(transform[0][1] * transform[0][1] + transform[1][1] * transform[1][1])) };
        const float line_width_addition = std::max(static_cast<float>(line_width), 0.0f);
        const vec2  quad_size           = { world_size[0] + line_width_addition, world_size[1] + line_width_addition };
    
        const vec2 scale_up       = { quad_size[0] / world_size[0], quad_size[1] / world_size[1] };
        mat3       quad_transform = to_opengl_mat3(transform);
        quad_transform[0] *= scale_up[0];
        quad_transform[1] *= scale_up[0];
        quad_transform[3] *= scale_up[1];
        quad_transform[4] *= scale_up[1];
        return { quad_transform, world_size, quad_size };
    }

}

================================================
FILE: source/CS200/Renderer2DUtils.hpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once

#include "Engine/Matrix.hpp"
#include "Engine/Vec2.hpp"
#include "RGBA.hpp"
#include <array>
#include <optional>

namespace CS200::Renderer2DUtils
{

    using mat3 = std::array<float, 9>; 
    using vec2 = std::array<float, 2>; 
    
    
    inline mat3 to_opengl_mat3(const Math::TransformationMatrix& transform) noexcept
    {
        return { static_cast<float>(transform[0][0]), static_cast<float>(transform[1][0]), static_cast<float>(transform[2][0]),
                 static_cast<float>(transform[0][1]), static_cast<float>(transform[1][1]), static_cast<float>(transform[2][1]),
                 static_cast<float>(transform[0][2]), static_cast<float>(transform[1][2]), static_cast<float>(transform[2][2]) };
    }
    
    
    Math::TransformationMatrix CalculateLineTransform(const Math::TransformationMatrix& transform, const Math::vec2& start_point, const Math::vec2& end_point, double line_width) noexcept;
    
    
    struct SDFTransform
    {
        mat3 QuadTransform; 
        vec2 WorldSize;     
        vec2 QuadSize;      
    };
    
    
    SDFTransform CalculateSDFTransform(const Math::TransformationMatrix& transform, double line_width) noexcept;

}

================================================
FILE: source/CS200/RenderingAPI.cpp
================================================
/**

* \file
* \author Rudy Castan
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "RenderingAPI.hpp"

#include "Engine/Engine.hpp"
#include "Engine/Error.hpp"
#include "Engine/Logger.hpp"
#include "OpenGL/Environment.hpp"
#include <GL/glew.h>
#include <cassert>

#include "OpenGL/GL.hpp"

namespace
{
#if defined(DEVELOPER_VERSION) && not defined(IS_WEBGL2)
    void OpenGLMessageCallback(
        [[maybe_unused]] unsigned source, [[maybe_unused]] unsigned type, [[maybe_unused]] unsigned id, unsigned severity, [[maybe_unused]] int length, const char* message,
        [[maybe_unused]] const void* userParam)
    {
        switch (severity)
        {
            case GL_DEBUG_SEVERITY_HIGH: Engine::GetLogger().LogError(message); return;
            case GL_DEBUG_SEVERITY_MEDIUM: Engine::GetLogger().LogError(message); return;
            case GL_DEBUG_SEVERITY_LOW: Engine::GetLogger().LogVerbose(message); return;
            case GL_DEBUG_SEVERITY_NOTIFICATION: Engine::GetLogger().LogVerbose(message); return;
        }

        assert(false && "Unknown severity level!");
    }

#endif
}

namespace CS200::RenderingAPI
{
    void Init() noexcept
    {
        GLint major = 0, minor = 0;

        GL::GetIntegerv(GL_MAJOR_VERSION, &major);
        GL::GetIntegerv(GL_MINOR_VERSION, &minor);
        if (OpenGL::version(major, minor) < OpenGL::version(OpenGL::MinimumRequiredMajorVersion, OpenGL::MinimumRequiredMinorVersion))
            throw_error_message("Unsupported OpenGL version ", major, '.', minor, "\n We need OpenGL ", OpenGL::MinimumRequiredMajorVersion, '.', OpenGL::MinimumRequiredMinorVersion, " or higher");
    
        if (OpenGL::MajorVersion == 0)
        {
            OpenGL::MajorVersion = major;
            OpenGL::MinorVersion = minor;
        }
    
        GL::GetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &OpenGL::MaxTextureImageUnits);
        GL::GetIntegerv(GL_MAX_TEXTURE_SIZE, &OpenGL::MaxTextureSize);
        GL::GetIntegerv(GL_MAJOR_VERSION, &OpenGL::MajorVersion);
        GL::GetIntegerv(GL_MINOR_VERSION, &OpenGL::MinorVersion);
        int max_element_vertices;
        GL::GetIntegerv(GL_MAX_ELEMENTS_VERTICES, &max_element_vertices);
        int max_element_indices;
        GL::GetIntegerv(GL_MAX_ELEMENTS_INDICES, &max_element_indices);
        int max_viewport_dims[2];
        GL::GetIntegerv(GL_MAX_VIEWPORT_DIMS, max_viewport_dims);

#if defined(DEVELOPER_VERSION) && not defined(IS_WEBGL2)
        // Debug callback functionality requires OpenGL 4.3+ or KHR_debug extension
        if (OpenGL::current_version() >= OpenGL::version(4, 3))
        {
            GL::Enable(GL_DEBUG_OUTPUT);
            GL::Enable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            GL::DebugMessageCallback(OpenGLMessageCallback, nullptr);
            GL::DebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
        }
#endif

        GL::Enable(GL_BLEND);
        GL::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //GL::Disable(GL_DEPTH_TEST);
        GL::Enable(GL_DEPTH_TEST);
    
        // GL_MAX_TEXTURE_IMAGE_UNITS, GL_MAX_TEXTURE_SIZE, GL_MAX_VIEWPORT_DIMS
        Engine::GetLogger().LogDebug("VENDOR : " + std::to_string(GL_VENDOR));
        Engine::GetLogger().LogDebug("RENDERER : " + std::to_string(GL_RENDERER));
        Engine::GetLogger().LogDebug("VERSION : " + std::to_string(GL_VERSION));
        Engine::GetLogger().LogDebug("SHADING LANGUAGE VERSION : " + std::to_string(GL_SHADING_LANGUAGE_VERSION));
        Engine::GetLogger().LogDebug("MAJOR VERSION : " + std::to_string(OpenGL::MajorVersion));
        Engine::GetLogger().LogDebug("MINOR VERSION : " + std::to_string(OpenGL::MinorVersion));
        Engine::GetLogger().LogDebug("MAX ELEMENTS VERTICES : " + std::to_string(max_element_vertices));
        Engine::GetLogger().LogDebug("MAX ELEMENTS INDICES : " + std::to_string(max_element_indices));
        Engine::GetLogger().LogDebug("MAX TEXTURE IMAGE UNITS : " + std::to_string(OpenGL::MaxTextureImageUnits));
        Engine::GetLogger().LogDebug("MAX TEXTURE SIZE : " + std::to_string(OpenGL::MaxTextureSize));
        Engine::GetLogger().LogDebug("MAX VIEWPORT DIMS : " + std::to_string(max_viewport_dims[0]) + ", " + std::to_string(max_viewport_dims[1]));
    }
    
    void SetClearColor(CS200::RGBA color) noexcept
    {
        const auto rgba = CS200::unpack_color(color);
        GL::ClearColor(rgba[0], rgba[1], rgba[2], rgba[3]);
    }
    
    void Clear() noexcept
    {
        //GL::Clear(GL_COLOR_BUFFER_BIT);
        GL::Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    void SetViewport(Math::ivec2 size, Math::ivec2 anchor_left_bottom) noexcept
    {
        GL::Viewport(anchor_left_bottom.x, anchor_left_bottom.y, size.x, size.y);
    }

}

================================================
FILE: source/CS200/RenderingAPI.hpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once

#include "Engine/Vec2.hpp"
#include "RGBA.hpp"

namespace CS200::RenderingAPI
{
    void Init() noexcept;
    void SetClearColor(CS200::RGBA color) noexcept;
    void Clear() noexcept;
    void SetViewport(Math::ivec2 size, Math::ivec2 anchor_left_bottom = { 0, 0 }) noexcept;
}

================================================
FILE: source/CS200/RGBA.hpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once

#include <array>
#include <cstdint>

namespace CS200
{
    /**
     * \brief Compact 32-bit color representation for efficient graphics operations
     *
     * RGBA provides a memory-efficient way to store and manipulate colors using a single
     * 32-bit integer. This format is widely used in graphics programming because it packs
     * four 8-bit color channels (Red, Green, Blue, Alpha) into one value that can be
     * easily passed around, stored in arrays, and processed by graphics hardware.
     *
     * The color format uses the layout: 0xRRGGBBAA where:
     * - RR = Red channel (bits 31-24)
     * - GG = Green channel (bits 23-16)
     * - BB = Blue channel (bits 15-8)
     * - AA = Alpha channel (bits 7-0)
     *
     * Each channel ranges from 0x00 (0) to 0xFF (255), providing 256 levels per channel
     * and over 16 million possible color combinations with transparency support.
     *
     * This compact representation is ideal for:
     * - Storing vertex colors in graphics buffers
     * - Passing colors as function parameters
     * - Performing fast bitwise color operations
     * - Interfacing with graphics APIs that expect packed colors
     */
    using RGBA = uint32_t;

    /** \brief Pure white color (255, 255, 255, 255) - fully opaque white */
    constexpr RGBA WHITE = 0xffffffff;
    
    /** \brief Pure black color (0, 0, 0, 255) - fully opaque black */
    constexpr RGBA BLACK = 0x000000ff;
    
    /** \brief Transparent color (0, 0, 0, 0) - completely transparent black */
    constexpr RGBA CLEAR = 0x00000000;
    
    /** \brief Light Gray color (200, 200, 200, 255) */
    constexpr RGBA LIGHTGRAY = 0xc8c8c8ff;
    
    /** \brief Gray color (130, 130, 130, 255) */
    constexpr RGBA GRAY = 0x828282ff;
    
    /** \brief Dark Gray color (80, 80, 80, 255) */
    constexpr RGBA DARKGRAY = 0x505050ff;
    
    /** \brief Yellow color (253, 249, 0, 255) */
    constexpr RGBA YELLOW = 0xfdf900ff;
    
    /** \brief Gold color (255, 203, 0, 255) */
    constexpr RGBA GOLD = 0xffcb00ff;
    
    /** \brief Orange color (255, 161, 0, 255) */
    constexpr RGBA ORANGE = 0xffa100ff;
    
    /** \brief Pink color (255, 109, 194, 255) */
    constexpr RGBA PINK = 0xff6dc2ff;
    
    /** \brief Red color (230, 41, 55, 255) */
    constexpr RGBA RED = 0xe62937ff;
    
    /** \brief Maroon color (190, 33, 55, 255) */
    constexpr RGBA MAROON = 0xbe2137ff;
    
    /** \brief Green color (0, 228, 48, 255) */
    constexpr RGBA GREEN = 0x00e430ff;
    
    /** \brief Lime color (0, 158, 47, 255) */
    constexpr RGBA LIME = 0x009e2fff;
    
    /** \brief Dark Green color (0, 117, 44, 255) */
    constexpr RGBA DARKGREEN = 0x00752cff;
    
    /** \brief Sky Blue color (102, 191, 255, 255) */
    constexpr RGBA SKYBLUE = 0x66bffff;
    
    /** \brief Blue color (0, 121, 241, 255) */
    constexpr RGBA BLUE = 0x0079f1ff;
    
    /** \brief Dark Blue color (0, 82, 172, 255) */
    constexpr RGBA DARKBLUE = 0x0052acff;
    
    /** \brief Purple color (200, 122, 255, 255) */
    constexpr RGBA PURPLE = 0xc87affff;
    
    /** \brief Violet color (135, 60, 190, 255) */
    constexpr RGBA VIOLET = 0x873cbeff;
    
    /** \brief Dark Purple color (112, 31, 126, 255) */
    constexpr RGBA DARKPURPLE = 0x701f7eff;
    
    /** \brief Beige color (211, 176, 131, 255) */
    constexpr RGBA BEIGE = 0xd3b083ff;
    
    /** \brief Brown color (127, 106, 79, 255) */
    constexpr RGBA BROWN = 0x7f6a4fff;
    
    /** \brief Dark Brown color (76, 63, 47, 255) */
    constexpr RGBA DARKBROWN = 0x4c3f2fff;
    
    /** \brief Magenta color (255, 0, 255, 255) */
    constexpr RGBA MAGENTA = 0xff00ffff;
    
    
    
    /**
     * \brief Convert packed RGBA color to floating-point component array
     * \param rgba 32-bit packed color in RGBA format
     * \return Array of 4 floats [r, g, b, a] normalized to [0.0, 1.0] range
     *
     * Unpacks a compact RGBA color into separate floating-point components that
     * are commonly required by graphics APIs like OpenGL. Each 8-bit integer
     * channel (0-255) is converted to a normalized float (0.0-1.0).
     *
     * This conversion is essential for:
     * - Passing colors to OpenGL shader uniforms
     * - Performing floating-point color math operations
     * - Interfacing with APIs that expect normalized color values
     * - Blending and interpolation calculations
     *
     * The bit extraction isolates each color channel:
     * - Red: (rgba & 0xff000000) >> 24
     * - Green: (rgba & 0x00ff0000) >> 16
     * - Blue: (rgba & 0x0000ff00) >> 8
     * - Alpha: (rgba & 0x000000ff) >> 0
     *
     * Each extracted value is then divided by 255.0f to normalize to [0.0, 1.0].
     */
    constexpr std::array<float, 4> unpack_color(RGBA rgba) noexcept
    {
        constexpr float scale = 1.0f / 255.0f;
        return { static_cast<float>((rgba & 0xff000000) >> 24) * scale, static_cast<float>((rgba & 0x00ff0000) >> 16) * scale, static_cast<float>((rgba & 0x0000ff00) >> 8) * scale,
                 static_cast<float>((rgba & 0x000000ff) >> 0) * scale };
    }
    
    /**
     * \brief Convert floating-point color components to packed RGBA format
     * \param color Array of 4 floats [r, g, b, a] in normalized [0.0, 1.0] range
     * \return 32-bit packed color in RGBA format (0xRRGGBBAA)
     *
     * Packs separate floating-point color components into a compact RGBA color
     * suitable for efficient storage and graphics operations. This is the inverse
     * operation of unpack_color(), converting normalized float values back into
     * the 8-bit integer format used by graphics hardware and APIs.
     *
     * This conversion is essential for:
     * - Converting computed color results back to graphics-friendly format
     * - Storing blended or interpolated colors efficiently
     * - Interfacing with graphics APIs that expect packed color values
     * - Optimizing memory usage in color arrays and vertex buffers
     *
     * The packing process:
     * 1. Scale each float component from [0.0, 1.0] to [0.0, 255.0]
     * 2. Clamp values to valid range [0, 255] to handle out-of-bounds inputs
     * 3. Convert to 8-bit integers (uint8_t)
     * 4. Shift and combine channels into final RGBA format:
     *    - Red: bits 31-24 (R << 24)
     *    - Green: bits 23-16 (G << 16)
     *    - Blue: bits 15-8 (B << 8)
     *    - Alpha: bits 7-0 (A << 0)
     *
     * Input values are automatically clamped to [0.0, 1.0] range to prevent
     * overflow and ensure valid color output even with out-of-range inputs.
     */
    constexpr RGBA pack_color(const std::array<float, 4>& color) noexcept
    {
        constexpr float scale = 255.0f;
        const float     r = color[0] * scale, g = color[1] * scale, b = color[2] * scale, a = color[3] * scale;
        const uint8_t   R = static_cast<uint8_t>(r <= 255.0f ? (r >= 0.0f ? r : 0.0f) : 255.0f);
        const uint8_t   G = static_cast<uint8_t>(g <= 255.0f ? (g >= 0.0f ? g : 0.0f) : 255.0f);
        const uint8_t   B = static_cast<uint8_t>(b <= 255.0f ? (b >= 0.0f ? b : 0.0f) : 255.0f);
        const uint8_t   A = static_cast<uint8_t>(a <= 255.0f ? (a >= 0.0f ? a : 0.0f) : 255.0f);
        return (static_cast<RGBA>(R) << 24) | (static_cast<RGBA>(G) << 16) | (static_cast<RGBA>(B) << 8) | (static_cast<RGBA>(A) << 0);
    }
    
    /**
     * \brief Convert RGBA format to ABGR format by reversing byte order
     * \param rgba Color in RGBA format (0xRRGGBBAA)
     * \return Color converted to ABGR format (0xAABBGGRR)
     *
     * Converts between different color byte ordering formats that are used by
     * various graphics systems and file formats. This conversion is necessary
     * when interfacing with systems that expect colors in ABGR order instead
     * of the standard RGBA order.
     *
     * The conversion process:
     * 1. Extract each color channel from the original RGBA value
     * 2. Rearrange the channels from RGBA order to ABGR order
     * 3. Pack the rearranged channels into a new 32-bit value
     *
     * Common use cases:
     * - Converting colors for specific graphics APIs or hardware
     * - Interfacing with image file formats that use different byte orders
     * - Preparing colors for systems with different endianness
     * - Working with legacy graphics formats that expect ABGR ordering
     *
     * The byte reversal ensures compatibility across different systems while
     * maintaining the same color information in a different memory layout.
     */
    constexpr uint32_t rgba_to_abgr(RGBA rgba) noexcept
    {
        const uint8_t r = static_cast<uint8_t>((rgba & 0xff000000) >> 24);
        const uint8_t g = static_cast<uint8_t>((rgba & 0x00ff0000) >> 16);
        const uint8_t b = static_cast<uint8_t>((rgba & 0x0000ff00) >> 8);
        const uint8_t a = static_cast<uint8_t>((rgba & 0x000000ff) >> 0);
    
        return (static_cast<uint32_t>(a) << 24) | (static_cast<uint32_t>(b) << 16) | (static_cast<uint32_t>(g) << 8) | (static_cast<uint32_t>(r) << 0);
    }
    
    constexpr uint32_t argb_to_rgba(RGBA rgba) noexcept
    {
        const uint8_t r = static_cast<uint8_t>((rgba & 0x00ff0000) >> 16);
        const uint8_t g = static_cast<uint8_t>((rgba & 0x0000ff00) >> 8);
        const uint8_t b = static_cast<uint8_t>((rgba & 0x000000ff) >> 0);
        const uint8_t a = static_cast<uint8_t>((rgba & 0xff000000) >> 24);
    
        return (static_cast<uint32_t>(a) << 24) | (static_cast<uint32_t>(b) << 16) | (static_cast<uint32_t>(g) << 8) | (static_cast<uint32_t>(r) << 0);
    }
    
    constexpr std::array<unsigned char, 4> ColorArray(RGBA rgba)
    {
        return std::array<unsigned char, 4>({ static_cast<unsigned char>((rgba & 0xff000000) >> 24), static_cast<unsigned char>((rgba & 0x00ff0000) >> 16),
                                              static_cast<unsigned char>((rgba & 0x0000ff00) >> 8), static_cast<unsigned char>((rgba & 0x000000ff) >> 0) });
    }

}

================================================
FILE: source/Demo/DemoBatchInstance.cpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "CS200/BatchRenderer2D.hpp"
  #include "Engine/GameStateManager.hpp"
  #include "Engine/Input.hpp"
  #include "Engine/Path.hpp"
  #include "Engine/Random.hpp"
  #include "Engine/TextureManager.hpp"
  #include "Game/MainMenu.h"

#include <imgui.h>
#include "DemoBatchInstance.hpp"

// Request high-performance GPU on systems with multiple GPUs (laptops with integrated + discrete)
// https://docs.nvidia.com/gameworks/content/technologies/desktop/optimus.htm
// https://gpuopen.com/learn/amdpowerxpressrequesthighperformance/
// https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
// Windows: Use __declspec(dllexport)

# define GPU_EXPORT __declspec(dllexport)

#else
// Linux/Mac: Use visibility attribute

# define GPU_EXPORT __attribute__((visibility("default")))

#endif

extern "C"
{
// NVIDIA Optimus: Request high-performance GPU
GPU_EXPORT unsigned long NvOptimusEnablement = 0x00000001;

// AMD PowerXpress: Request high-performance GPU
GPU_EXPORT int AmdPowerXpressRequestHighPerformance = 0x00000001;
}

void DemoBatchInstance::Load()
{
    // Cache OpenGL renderer info
    OpenGLRenderer = reinterpret_cast<const char*>(GL::GetString(GL_RENDERER));
    GL::GetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &MaxTextureUnits);

    // // Initialize renderer
    // Renderer = std::make_unique<CS200::ImmediateRenderer2D>();
    // Renderer->Init();
    
    auto& texture_manager = Engine::GetTextureManager();
    texture_manager.SwitchRenderer(CS230::TextureManager::RendererType::Immediate);
    
    for (size_t i = 0; i < ROBOT_VARIATIONS; ++i)
    {
        // Load robot texture
        std::ostringstream sout;
        sout << "Assets/images/DemoBatchInstance/variations/robot_var_" << std::setfill('0') << std::setw(2) << (i + 1) << ".png";
    
        robotTextures[i] = texture_manager.Load(sout.str());
    }
    // Create random robots
    constexpr int NUM_ROBOTS = 20;
    Robots.reserve(NUM_ROBOTS);
    for (int i = 0; i < NUM_ROBOTS; ++i)
    {
        Robots.push_back(CreateRandomRobot());
    }
    
    // Initialize FPS tracking
    LastTicks = SDL_GetTicks();
    
    CS200::RenderingAPI::SetClearColor(0x578FE5FF);

}

void DemoBatchInstance::Unload()
{
}

void DemoBatchInstance::Update([[maybe_unused]] double dt)
{
    auto                        texture_manager          = Engine::GetTextureManager();
    [[maybe_unused]] const auto current_renderer_type = texture_manager.GetCurrentRendererType();
    // Update FPS tracker
    const Uint32                currentTicks          = SDL_GetTicks();
    const Uint32                deltaTicks              = currentTicks - LastTicks;
    const double                deltaSeconds          = deltaTicks / 1000.0;
    LastTicks                                          = currentTicks;
    FPSTracker.Update(deltaSeconds);

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape))
    {
        Engine::GetGameStateManager().PopState();
        Engine::GetGameStateManager().PushState<MainMenu>();
    }

}

void DemoBatchInstance::Draw()
{
    CS200::RenderingAPI::Clear();
    // auto& renderer_2d = Engine::GetRenderer2D();
    CS200::IRenderer2D* renderer_2d = Engine::GetTextureManager().GetRenderer2D();
    renderer_2d->BeginScene(CS200::build_ndc_matrix(Engine::GetWindow().GetSize()));
    // Draw each robot
    for (const auto& robot : Robots)
    {
        // Tint color
        std::array<float, 4> tint{ robot.r, robot.g, robot.b, 1.0f };

        robotTextures[static_cast<size_t>(robot.variation)]->Draw(Math::TranslationMatrix(robot.position), { robot.frame * ROBOT_FRAME_SIZE.x, 0 }, ROBOT_FRAME_SIZE, CS200::pack_color(tint));
    }
    
    renderer_2d->EndScene();
    current_draw_call = renderer_2d->GetDrawCallCounter();
    current_draw_texture_call = renderer_2d->GetDrawTextureCounter();

}

void DemoBatchInstance::DrawImGui()
{
    ImGui::Begin("Demo Settings");

    // Display FPS at the top
    ImGui::Text("FPS: %d", static_cast<int>(FPSTracker));
    ImGui::Separator();
    
    ImGui::Text("Draw Call Counter: %d", static_cast<int>(current_draw_call));
    ImGui::Text("Draw Texture Call count: %d", static_cast<int>(current_draw_texture_call));
    ImGui::Separator();
    
    ImGui::Text("Activated Texture count: %d", static_cast<int>(ROBOT_VARIATIONS));
    ImGui::Separator();
    
    // Display OpenGL renderer info
    if (OpenGLRenderer)
    {
        ImGui::Text("OpenGL Renderer: %s", OpenGLRenderer);
        ImGui::Text("Max Texture Units: %d", MaxTextureUnits);
        ImGui::Separator();
    }
    
    // Renderer selection
    auto&       texture_manager         = Engine::GetTextureManager();
    const auto current_renderer_type = texture_manager.GetCurrentRendererType();
    // const auto renderer_2d = texture_manager.GetRenderer2D();
    ImGui::Text("Renderer:");
    if (ImGui::RadioButton("Immediate", current_renderer_type == CS230::TextureManager::RendererType::Immediate))
    {
        texture_manager.SwitchRenderer(CS230::TextureManager::RendererType::Immediate);
    }
    ImGui::SameLine();
    
    if (ImGui::RadioButton("Batch", current_renderer_type == CS230::TextureManager::RendererType::Batch))
    {
        texture_manager.SwitchRenderer(CS230::TextureManager::RendererType::Batch);
    }
    
    ImGui::SameLine();
    if (ImGui::RadioButton("Instanced", current_renderer_type == CS230::TextureManager::RendererType::Instanced))
    {
        texture_manager.SwitchRenderer(CS230::TextureManager::RendererType::Instanced);
    }
    ImGui::Separator();
    
    // VSync toggle
    if (ImGui::Checkbox("VSync", &VSyncEnabled))
    {
        // https://wiki.libsdl.org/SDL_GL_SetSwapInterval
        constexpr int ADAPTIVE_VSYNC = -1;
        constexpr int VSYNC             = 1;
        constexpr int NO_VSYNC         = 0;
    
        if (VSyncEnabled)
        {
            // Try adaptive vsync first, fall back to regular vsync
            if (const auto result = SDL_GL_SetSwapInterval(ADAPTIVE_VSYNC); result != 0)
            {
                SDL_GL_SetSwapInterval(VSYNC);
            }
        }
        else
        {
            SDL_GL_SetSwapInterval(NO_VSYNC);
        }
    }
    ImGui::Separator();
    
    // Display current robot count
    ImGui::Text("Current Robot Count: %zu", Robots.size());
    ImGui::Separator();
    
    // Amounts for adding/removing
    constexpr int     amounts[]    = { 1, 10, 100, 1000, 10000, 100000 };
    constexpr size_t MAX_ROBOTS = 1000000; // Sanity limit to prevent crashes
    
    // Add robots buttons
    ImGui::Text("Add Robots:");
    for (int amount : amounts)
    {
        // Disable button if it would exceed max limit
        const bool can_add = (Robots.size() + static_cast<size_t>(amount)) <= MAX_ROBOTS;
        if (!can_add)
        {
            ImGui::BeginDisabled();
        }
    
        if (ImGui::Button((std::string("+") + std::to_string(amount)).c_str()))
        {
            const size_t new_count = std::min(Robots.size() + static_cast<size_t>(amount), MAX_ROBOTS);
            const size_t to_add       = new_count - Robots.size();
    
            if (to_add > 0)
            {
                Robots.reserve(new_count);
                for (size_t i = 0; i < to_add; ++i)
                {
                    Robots.push_back(CreateRandomRobot());
                }
            }
        }
    
        if (!can_add)
        {
            ImGui::EndDisabled();
        }
        ImGui::SameLine();
    }
    ImGui::NewLine();
    
    // Remove robots buttons
    ImGui::Text("Remove Robots:");
    for (int amount : amounts)
    {
        // Disable button if there are no robots to remove
        const bool can_remove = !Robots.empty();
        if (!can_remove)
        {
            ImGui::BeginDisabled();
        }
    
        if (ImGui::Button((std::string("-") + std::to_string(amount)).c_str()))
        {
            const size_t to_remove = std::min(static_cast<size_t>(amount), Robots.size());
            if (to_remove > 0)
            {
                Robots.resize(Robots.size() - to_remove);
            }
        }
    
        if (!can_remove)
        {
            ImGui::EndDisabled();
        }
        ImGui::SameLine();
    }
    ImGui::NewLine();
    
    ImGui::Separator();
    
    // Clear all button
    const bool has_robots = !Robots.empty();
    if (!has_robots)
    {
        ImGui::BeginDisabled();
    }
    
    if (ImGui::Button("Clear All"))
    {
        Robots.clear();
    }
    
    if (!has_robots)
    {
        ImGui::EndDisabled();
    }
    
    // Show warning when approaching limit
    if (Robots.size() > static_cast<size_t>(MAX_ROBOTS * 0.8))
    {
        ImGui::Separator();
        ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "Warning: Approaching maximum robot limit!");
    }
    
    ImGui::End();

}

DemoBatchInstance::Robot DemoBatchInstance::CreateRandomRobot()
{
    const Math::vec2 window_size = Engine::GetWindow().GetSize();

    Robot             robot;
    robot.position.x = (util::random(0.0, window_size.x));
    robot.position.y = (util::random(0.0, window_size.y));
    robot.frame         = util::random(ROBOT_NUM_FRAMES);
    if (static_cast<float>(util::random(0.0, 1.0)) < 0.85f)
    {
        robot.r = robot.g = robot.b = 1.0f;
    }
    else
    {
        robot.r = static_cast<float>(util::random(0.5, 1.0));
        robot.g = static_cast<float>(util::random(0.6, 1.0));
        robot.b = static_cast<float>(util::random(0.45, 1.0));
    }
    robot.variation = util::random(static_cast<int>(ROBOT_VARIATIONS));
    return robot;

}

================================================
FILE: source/Demo/DemoBatchInstance.hpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once
  #include <GL/glew.h>
  #include <SDL.h>
  #include <array>
  #include <imgui.h>
  #include <memory>
  #include <stb_image.h>
  #include <vector>

#include "Engine/Engine.hpp"
#include "Engine/FPS.hpp"
#include "Engine/GameState.hpp"
#include "Engine/Texture.hpp"
#include "Engine/Vec2.hpp"
#include "Engine/Window.hpp"

#include "OpenGL/Buffer.hpp"

#include "CS200/IRenderer2D.hpp"
#include "CS200/ImmediateRenderer2D.hpp"
#include "CS200/NDC.hpp"
#include "CS200/RenderingAPI.hpp"
#include "OpenGL/GL.hpp"

class DemoBatchInstance : public CS230::GameState
{
public:
    void Load() override;
    void Unload() override;
    void Update(double dt) override;
    void Draw() override;
    void DrawImGui() override;

    gsl::czstring GetName() const override
    {
        return "DemoBatchInstance";
    };

private:

    // Robot sprite sheet constants
    static constexpr Math::ivec2 ROBOT_FRAME_SIZE{ 63, 127 };
    static constexpr int         ROBOT_NUM_FRAMES = 5;
    static constexpr size_t         ROBOT_VARIATIONS = 64;
    
    // Robot instance data
    struct Robot
    {
        Math::vec2 position;
        int           frame;
        float       r, g, b; // tint color
        int           variation;
    };
    
    std::vector<Robot>                                              Robots;
    // std::unique_ptr<CS200::IRenderer2D>             Renderer;
    // OpenGL::Handle                 gRobotTexture = 0;
    // std::array<OpenGL::Handle, ROBOT_VARIATIONS> RobotTextures{};
    std::array<std::shared_ptr<CS230::Texture>, ROBOT_VARIATIONS> robotTextures{};
    util::FPS                                                      FPSTracker;
    Uint32                                                          LastTicks          = 0;
    bool                                                          VSyncEnabled      = true;
    const char*                                                      OpenGLRenderer  = nullptr;
    int                                                              MaxTextureUnits = 0;
    size_t current_draw_call = 0;
    size_t current_draw_texture_call = 0;
    
    
    // Helper function to create a random robot
    Robot CreateRandomRobot();

};

================================================
FILE: source/Demo/DemoBufferTypes.hpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "CS200/NDC.hpp"
  #include "CS200/RGBA.hpp"
  #include "Engine/GameState.hpp"
  #include "OpenGL/Buffer.hpp"
  #include "OpenGL/Shader.hpp"
  #include "OpenGL/VertexArray.hpp"
  #include <array>
  #include <vector>

class DemoBufferTypes : public CS230::GameState
{
public:
    void          Load() override;
    void          Unload() override;
    void          Update(double dt) override;
    void          Draw()  override;
    void          DrawImGui() override;
    gsl::czstring GetName() const override;

private:
    OpenGL::CompiledShader backgroundShader{};
    OpenGL::CompiledShader villagerShader{};
    OpenGL::BufferHandle   uniformBlock{};
    std::array<float, 12>  toNDC{};

    struct object
    {
        OpenGL::BufferHandle      vertexBufferHandle{};
        OpenGL::BufferHandle      indexBufferHandle{};
        GLsizei                   indicesCount{};
        OpenGL::VertexArrayHandle modelHandle{};
    } background{}, villager{};
    
    static constexpr std::size_t MAX_NUMBER_VILLAGERS = 16384;
    
    struct VillagerData
    {
        Math::vec2 position{};
        Math::vec2 targetPosition{};
        Math::vec2 scale{ 16.0, 16.0 };
        Math::vec2 targetScale{};
        double     rotation{};
        double     targetRotation{};
    
        // Animation parameters
        Math::vec2 positionOffset{};
        Math::vec2 scaleOffset{};
        double     rotationSpeed{};
        Math::vec2 positionSpeed{};
        Math::vec2 scaleSpeed{};
        double     timeOffset{};
        bool       alive{ true };
        bool       shouldDraw{ true };
    };
    
    std::vector<VillagerData> villagers;
    Math::vec2                currentDisplaySize{};
    
    constexpr static int QuadSize = 64;
    
    // Noise generation constants
    constexpr static float NoiseFrequency  = 1.0f / (static_cast<float>(QuadSize) * 4.0f);
    constexpr static float NoiseLacunarity = 2.0f;
    constexpr static float NoiseGain       = 0.5f;
    constexpr static int   NoiseLayers     = 5;
    
    // Animation wave constants
    constexpr static float WaveFrequency1 = 1.0f;
    constexpr static float WaveFrequency2 = 2.3f;
    constexpr static float WaveFrequency3 = 0.7f;
    constexpr static float WaveMix1       = 0.5f;
    constexpr static float WaveMix2       = 0.3f;
    constexpr static float WaveMix3       = 0.2f;
    
    struct Vertex
    {
        float                        x, y;
        std::array<unsigned char, 4> color;
    };
    
    std::vector<Vertex>         backgroundVertices;
    std::vector<unsigned short> backgroundIndices;

private:
    void        loadShaders();
    void        createVillagerModel();
    void        bounceVillager();
    void        updateNDCUniformValues();
    void        updateBackgroundModel();
    static void drawObject(const object& object);

    // Helper functions for updateBackgroundModel()
    struct AnimationParams
    {
        float elapsedTime;
        float quadTiltSize;
    };
    
    struct GridParams
    {
        int numQuadsWide;
        int numQuadsTall;
    };
    
    static AnimationParams calculateAnimationParameters();
    bool                   ensureBackgroundBuffersCapacity(const GridParams& grid_params);
    void                   generateQuadVertices(int row, int column, const GridParams& grid_params, const AnimationParams& anim_params);
    void                   updateBackgroundBuffersOnGPU(int num_required_vertices, bool indices_need_update) const;
    
    void increase_number_of_villagers(std::size_t current_size);
    void decrease_number_of_villagers(std::size_t current_size);
    void regenerate_all_villagers();
    void generateRandomVillager(VillagerData& villagerData, const Math::vec2& screenSize) const;
    void updateVillagers();

};

================================================
FILE: source/Demo/DemoCS230Textures.cpp
================================================
/**

* \file
* \author Rudy Castan
* \author Jonathan Holmes
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#include "DemoCS230Textures.hpp"

#include "CS200/IRenderer2D.hpp"
#include "CS200/RenderingAPI.hpp"
#include "DemoTexturing.hpp"
#include "Engine/Engine.hpp"
#include "Engine/GameStateManager.hpp"
#include "Engine/Matrix.hpp"
#include "Engine/Texture.hpp"
#include "Engine/TextureManager.hpp"
#include "Engine/Window.hpp"
#include "../Game/MainMenu.h"

#include <cmath>
#include <imgui.h>

void DemoCS230Textures::Load()
{
    auto&      texture_manager        = Engine::GetTextureManager();
    texture_manager.SwitchRenderer(CS230::TextureManager::RendererType::Immediate);
    const auto background_image_paths = { "Assets/images/DemoCS230Textures/Planets.png", "Assets/images/DemoCS230Textures/Ships.png", "Assets/images/DemoCS230Textures/Foreground.png" };
    for (const auto& path : background_image_paths)
    {
        backgroundTextures.push_back(texture_manager.Load(path));
    }

    robotTexture = texture_manager.Load("Assets/images/DemoCS230Textures/Robot.png");
    catTexture   = texture_manager.Load("Assets/images/DemoCS230Textures/Cat.png");
    
    initializeRobotAnimations();
    initializeCatAnimations();
    
    CS200::RenderingAPI::SetClearColor(0x2E3440FF);

}

template <typename T, typename FLOAT = double>
static void ease_to_target(T& current, const T& target, FLOAT delta_time, FLOAT weight = 1.0)
{
    const auto easing = std::min(delta_time * weight, static_cast<FLOAT>(1.0));
    current += easing * (target - current);
}

void DemoCS230Textures::Update([[maybe_unused]]double dt)
{
    const auto& environment = Engine::GetWindowEnvironment();
    updateAnimation(environment.DeltaTime);
    const auto     delta_time = static_cast<float>(environment.DeltaTime);
    constexpr auto weight     = 1.5f;
    ease_to_target(backgroundTintColor[0], targetBackgroundTintColor[0], delta_time, weight);
    ease_to_target(backgroundTintColor[1], targetBackgroundTintColor[1], delta_time, weight);
    ease_to_target(backgroundTintColor[2], targetBackgroundTintColor[2], delta_time, weight);
    ease_to_target(backgroundTintColor[3], targetBackgroundTintColor[3], delta_time, weight);
    ease_to_target(characterTintColor[0], targetCharacterTintColor[0], delta_time, weight);
    ease_to_target(characterTintColor[1], targetCharacterTintColor[1], delta_time, weight);
    ease_to_target(characterTintColor[2], targetCharacterTintColor[2], delta_time, weight);
    ease_to_target(characterTintColor[3], targetCharacterTintColor[3], delta_time, weight);
}

void DemoCS230Textures::Draw() 
{
    CS200::RenderingAPI::Clear();
    auto renderer_2d = Engine::GetTextureManager().GetRenderer2D();
    renderer_2d->BeginScene(CS200::build_ndc_matrix(Engine::GetWindow().GetSize()));
    const auto background_tint = CS200::pack_color(backgroundTintColor);
    for (const auto& texture : backgroundTextures)
    {
        texture->Draw(Math::TransformationMatrix{}, background_tint);
    }
    std::shared_ptr<CS230::Texture>  currentTexture = (selectedCharacter == CharacterType::Robot) ? robotTexture : catTexture;
    const auto       middle_x       = Engine::GetWindowEnvironment().DisplaySize.x / 2.0;
    const auto       texel_base     = getCurrentFrameTexelPosition();
    const auto       frame_size     = getCurrentFrameSize();
    const auto       hot_spot       = getCurrentHotSpot();
    constexpr double floor_y        = 80.0;
    const auto       to_center      = Math::TranslationMatrix(Math::vec2{ static_cast<double>(-hot_spot.x), static_cast<double>(-hot_spot.y) });
    const auto       scale          = faceRight ? Math::ScaleMatrix({ 1.0, 1.0 }) : Math::ScaleMatrix({ -1.0, 1.0 });
    const auto       translate      = Math::TranslationMatrix(Math::vec2{ middle_x, floor_y });
    const auto       transform      = translate * scale * to_center;
    const auto       character_tint = CS200::pack_color(characterTintColor);
    currentTexture->Draw(transform, texel_base, frame_size, character_tint);
    renderer_2d->EndScene();
}

void DemoCS230Textures::DrawImGui()
{
    if (ImGui::Begin("CS230 Textures Demo"))
    {
        const auto timing = Engine::GetWindowEnvironment();
        ImGui::LabelText("FPS", "%d", timing.FPS);
        ImGui::SeparatorText("Tint Color Controls");
        ImGui::ColorEdit4("Background Tint", targetBackgroundTintColor.data());
        ImGui::ColorEdit4("Character Tint", targetCharacterTintColor.data());

        ImGui::SeparatorText("Character Selection");
    
        static const char* character_names[] = { "Robot", "Cat" };
        int                character_index   = static_cast<int>(selectedCharacter);
    
        if (ImGui::Combo("Character", &character_index, character_names, IM_ARRAYSIZE(character_names)))
        {
            selectedCharacter = static_cast<CharacterType>(character_index);
            currentFrameIndex = 0;
            animationTimer    = 0.0;
        }
    
        if (selectedCharacter == CharacterType::Robot)
        {
            ImGui::SeparatorText("Robot Animation Controls");
    
            static const char* robot_animation_names[] = { "None", "RobotDead", "RobotWalking", "RobotAngry" };
            int                current_anim_index      = static_cast<int>(currentRobotAnimation);
    
            if (ImGui::Combo("Animation", &current_anim_index, robot_animation_names, IM_ARRAYSIZE(robot_animation_names)))
            {
                currentRobotAnimation = static_cast<RobotAnimation>(current_anim_index);
                currentFrameIndex     = 0;
                animationTimer        = 0.0;
            }
        }
        else // Cat
        {
            ImGui::SeparatorText("Cat Animation Controls");
    
            static const char* cat_animation_names[] = { "CatIdle", "CatRunning", "CatJumping", "CatFalling" };
            int                current_anim_index    = static_cast<int>(currentCatAnimation);
    
            if (ImGui::Combo("Animation", &current_anim_index, cat_animation_names, IM_ARRAYSIZE(cat_animation_names)))
            {
                currentCatAnimation = static_cast<CatAnimation>(current_anim_index);
                currentFrameIndex   = 0;
                animationTimer      = 0.0;
            }
        }
    
        ImGui::SeparatorText("Direction Controls");
    
        // Direction control
        ImGui::BeginDisabled(!faceRight);
        if (ImGui::Button("Face Left", ImVec2(80, 0)))
        {
            faceRight = false;
        }
        ImGui::EndDisabled();
    
        ImGui::SameLine();
    
        ImGui::BeginDisabled(faceRight);
        if (ImGui::Button("Face Right", ImVec2(80, 0)))
        {
            faceRight = true;
        }
        ImGui::EndDisabled();
    
        ImGui::SeparatorText("Animation Info");
        const auto& animations = getCurrentAnimations();
        const int   anim_index = getCurrentAnimationIndex();
        const auto& anim       = animations[static_cast<size_t>(anim_index)];
        ImGui::Text("Current Animation: %s", anim.name.c_str());
        ImGui::Text("Frame Count: %zu", anim.frames.size());
        ImGui::Text("Current Frame Index: %d", currentFrameIndex);
        ImGui::Text("Loop Frame: %d", anim.loopFrame);
        const auto& currentFrame = anim.frames[static_cast<size_t>(currentFrameIndex)];
        ImGui::Text("Current Sprite Frame: %d", currentFrame.frameIndex);
        ImGui::Text("Frame Duration: %.2f seconds", currentFrame.duration);
        ImGui::Text("Animation Timer: %.2f seconds", animationTimer);
        const double totalDuration = getTotalAnimationDuration();
        const double elapsedTime   = getCurrentAnimationElapsedTime();
        const double progress      = elapsedTime / totalDuration;
        ImGui::Text("Animation Progress: %.1f%% (%.2f/%.2f seconds)", progress * 100.0, elapsedTime, totalDuration);
        ImGui::ProgressBar(static_cast<float>(progress), ImVec2(-1.0f, 0.0f));
        if (ImGui::Button("Reset Animation"))
        {
            currentFrameIndex = 0;
            animationTimer    = 0.0;
        }
    
    
        ImGui::SeparatorText("Hot Spot and Frame Size");
        const auto hot_spot   = getCurrentHotSpot();
        const auto frame_size = getCurrentFrameSize();
        ImGui::Text("Hot Spot: (%d, %d)", hot_spot.x, hot_spot.y);
        ImGui::Text("Frame Size: %dx%d", frame_size.x, frame_size.y);
    
        ImGui::SeparatorText("Switch Demo");
        if (ImGui::Button("Switch to Demo Texturing"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<DemoTexturing>();
        }
        if (ImGui::Button("Switch to MainMenu"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<MainMenu>();
        }
    }
    ImGui::End();

}

void DemoCS230Textures::Unload()
{
    auto& texture_manager = Engine::GetTextureManager();
    texture_manager.Unload();
    backgroundTextures.clear();
    robotTexture = nullptr;
    catTexture   = nullptr;
}

gsl::czstring DemoCS230Textures::GetName() const
{
    return "Demo CS230 Textures";
}

void DemoCS230Textures::initializeRobotAnimations()
{
    robotAnimations.clear();
    robotAnimations.resize(4); // 4 animations: None, RobotDead, RobotWalking, RobotAngry

    // Animation: None - PlayFrame 0 10
    robotAnimations[static_cast<int>(RobotAnimation::None)] = { "None", { { 0, 10.0 } }, 0 };
    
    // Animation: RobotDead - PlayFrame 2 5
    robotAnimations[static_cast<int>(RobotAnimation::RobotDead)] = { "RobotDead", { { 2, 5.0 } }, 0 };
    
    // Animation: RobotWalking - PlayFrame 0 0.2, PlayFrame 1 0.2
    robotAnimations[static_cast<int>(RobotAnimation::RobotWalking)] = {
        "RobotWalking", { { 0, 0.2 }, { 1, 0.2 } },
         0
    };
    
    // Animation: RobotAngry - PlayFrame 3 0.1, PlayFrame 4 0.1
    robotAnimations[static_cast<int>(RobotAnimation::RobotAngry)] = {
        "RobotAngry", { { 3, 0.1 }, { 4, 0.1 } },
         0
    };

}

void DemoCS230Textures::initializeCatAnimations()
{
    catAnimations.clear();
    catAnimations.resize(4); // 4 animations: CatIdle, CatRunning, CatJumping, CatFalling

    // Animation: CatIdle
    catAnimations[static_cast<int>(CatAnimation::CatIdle)] = {
        "CatIdle",
        { { 0, 6.0 }, { 1, 0.5 }, { 2, 0.1 }, { 1, 0.5 }, { 2, 0.1 }, { 1, 0.5 }, { 0, 3.0 }, { 1, 0.5 }, { 2, 0.3 }, { 1, 0.5 },
          { 2, 0.3 }, { 1, 0.5 }, { 0, 3.0 }, { 1, 0.5 }, { 2, 1.0 }, { 1, 0.3 }, { 2, 2.0 }, { 3, 0.4 }, { 4, 0.4 }, { 5, 0.4 } },
        16  // Loop back to frame 16
    };
    
    // Animation: CatRunning - PlayFrame 6 .1, PlayFrame 0 .1, PlayFrame 7 .1, PlayFrame 0 .1, Loop 0
    catAnimations[static_cast<int>(CatAnimation::CatRunning)] = {
        "CatRunning", { { 6, 0.1 }, { 0, 0.1 }, { 7, 0.1 }, { 0, 0.1 } },
         0
    };
    
    // Animation: CatJumping - PlayFrame 9 3, Loop 0
    catAnimations[static_cast<int>(CatAnimation::CatJumping)] = { "CatJumping", { { 9, 3.0 } }, 0 };
    
    // Animation: CatFalling - PlayFrame 8 3, Loop 0
    catAnimations[static_cast<int>(CatAnimation::CatFalling)] = { "CatFalling", { { 8, 3.0 } }, 0 };

}

void DemoCS230Textures::updateAnimation(double deltaTime)
{
    const auto& animations = getCurrentAnimations();
    const int   anim_index = getCurrentAnimationIndex();
    const auto& anim       = animations[static_cast<size_t>(anim_index)];
    animationTimer += deltaTime;
    const auto& currentFrame = anim.frames[static_cast<size_t>(currentFrameIndex)];
    if (animationTimer >= currentFrame.duration)
    {
        animationTimer    = 0.0;
        currentFrameIndex = (currentFrameIndex + 1);
        if (static_cast<size_t>(currentFrameIndex) >= anim.frames.size())
        {
            currentFrameIndex = anim.loopFrame;
        }
    }
}

int DemoCS230Textures::getCurrentSpriteFrame() const
{
    const auto& animations = getCurrentAnimations();
    const int   anim_index = getCurrentAnimationIndex();
    const auto& anim       = animations[static_cast<size_t>(anim_index)];
    return anim.frames[static_cast<size_t>(currentFrameIndex)].frameIndex;
}

Math::ivec2 DemoCS230Textures::getCurrentFrameTexelPosition() const
{
    const int spriteFrame = getCurrentSpriteFrame();
    if (selectedCharacter == CharacterType::Robot)
    {
        return Math::ivec2{ spriteFrame * ROBOT_FRAME_SIZE.x, 0 };
    }
    else
    {
        return CAT_FRAME_POSITIONS[static_cast<size_t>(spriteFrame)];
    }
}

Math::ivec2 DemoCS230Textures::getCurrentFrameSize() const
{
    return (selectedCharacter == CharacterType::Robot) ? ROBOT_FRAME_SIZE : CAT_FRAME_SIZE;
}

Math::ivec2 DemoCS230Textures::getCurrentHotSpot() const
{
    return (selectedCharacter == CharacterType::Robot) ? ROBOT_HOT_SPOT : CAT_HOT_SPOT;
}

double DemoCS230Textures::getTotalAnimationDuration() const
{
    const auto& animations    = getCurrentAnimations();
    const int   anim_index    = getCurrentAnimationIndex();
    const auto& anim          = animations[static_cast<size_t>(anim_index)];
    double      totalDuration = 0.0;
    for (const auto& frame : anim.frames)
    {
        totalDuration += frame.duration;
    }
    return totalDuration;
}

double DemoCS230Textures::getCurrentAnimationElapsedTime() const
{
    const auto& animations  = getCurrentAnimations();
    const int   anim_index  = getCurrentAnimationIndex();
    const auto& anim        = animations[static_cast<size_t>(anim_index)];
    double      elapsedTime = 0.0;
    for (int i = 0; i < currentFrameIndex && i < static_cast<int>(anim.frames.size()); ++i)
    {
        elapsedTime += anim.frames[static_cast<size_t>(i)].duration;
    }
    elapsedTime += animationTimer;
    return elapsedTime;
}

const std::vector<DemoCS230Textures::Animation>& DemoCS230Textures::getCurrentAnimations() const
{
    return (selectedCharacter == CharacterType::Robot) ? robotAnimations : catAnimations;
}

int DemoCS230Textures::getCurrentAnimationIndex() const
{
    return (selectedCharacter == CharacterType::Robot) ? static_cast<int>(currentRobotAnimation) : static_cast<int>(currentCatAnimation);
}

================================================
FILE: source/Demo/DemoCS230Textures.hpp
================================================
/**

* \file
* \author Rudy Castan
* \author Jonathan Holmes
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#pragma once

#include "Engine/GameState.hpp"
#include "Engine/Vec2.hpp"
#include <array>
#include <memory>
#include <string>
#include <vector>

namespace CS230
{
    class Texture;
}

class DemoCS230Textures : public CS230::GameState
{
public:
    void          Load() override;
    void          Update(double dt) override;
    void          Unload() override;
    void          Draw()  override;
    void          DrawImGui() override;
    gsl::czstring GetName() const override;

private:

    struct AnimationFrame
    {
        int    frameIndex{};
        double duration{}; // in seconds
    };
    
    struct Animation
    {
        std::string                 name{};
        std::vector<AnimationFrame> frames{};
        int                         loopFrame{ 0 };
    };
    
    enum class RobotAnimation
    {
        None         = 0,
        RobotDead    = 1,
        RobotWalking = 2,
        RobotAngry   = 3
    };
    
    enum class CatAnimation
    {
        CatIdle    = 0,
        CatRunning = 1,
        CatJumping = 2,
        CatFalling = 3
    };
    
    enum class CharacterType
    {
        Robot = 0,
        Cat   = 1
    };
    
    // Robot sprite sheet info
    static constexpr Math::ivec2 ROBOT_HOT_SPOT{ 30, 20 };
    static constexpr Math::ivec2 ROBOT_FRAME_SIZE{ 63, 127 };
    static constexpr int         ROBOT_NUM_FRAMES = 5;
    
    // Cat sprite sheet info
    static constexpr Math::ivec2 CAT_HOT_SPOT{ 65, 15 };
    static constexpr Math::ivec2 CAT_FRAME_SIZE{ 128, 128 };
    static constexpr int         CAT_NUM_FRAMES = 10;
    
    // Cat frame positions in texture (texel coordinates)
    static constexpr std::array<Math::ivec2, CAT_NUM_FRAMES> CAT_FRAME_POSITIONS = {
        {
         { 0, 0 },     // Frame 0
            { 128, 0 },   // Frame 1
            { 256, 0 },   // Frame 2
            { 384, 0 },   // Frame 3
            { 512, 0 },   // Frame 4
            { 0, 128 },   // Frame 5
            { 128, 128 }, // Frame 6
            { 256, 128 }, // Frame 7
            { 384, 128 }, // Frame 8
            { 512, 128 }  // Frame 9
        }
    };
    
    std::vector<std::shared_ptr<CS230::Texture>> backgroundTextures;
    std::shared_ptr<CS230::Texture>              robotTexture              = nullptr;
    std::shared_ptr<CS230::Texture>              catTexture                = nullptr;
    std::array<float, 4>         backgroundTintColor       = { 0.1f, 0.2f, 0.3f, 0.4f };
    std::array<float, 4>         characterTintColor        = { 0.4f, 0.3f, 0.2f, 0.1f };
    std::array<float, 4>         targetBackgroundTintColor = { 1.0f, 1.0f, 1.0f, 1.0f };
    std::array<float, 4>         targetCharacterTintColor  = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    // Character selection and animation state
    CharacterType          selectedCharacter = CharacterType::Cat;
    std::vector<Animation> robotAnimations;
    std::vector<Animation> catAnimations;
    RobotAnimation         currentRobotAnimation = RobotAnimation::None;
    CatAnimation           currentCatAnimation   = CatAnimation::CatIdle;
    int                    currentFrameIndex     = 0;
    double                 animationTimer        = 0.0;
    bool                   faceRight             = true;

private:
    void                          initializeRobotAnimations();
    void                          initializeCatAnimations();
    void                          updateAnimation(double deltaTime);
    int                           getCurrentSpriteFrame() const;
    Math::ivec2                   getCurrentFrameTexelPosition() const;
    Math::ivec2                   getCurrentFrameSize() const;
    Math::ivec2                   getCurrentHotSpot() const;
    double                        getTotalAnimationDuration() const;
    double                        getCurrentAnimationElapsedTime() const;
    const std::vector<Animation>& getCurrentAnimations() const;
    int                           getCurrentAnimationIndex() const;
};

================================================
FILE: source/Demo/DemoFramebuffer.cpp
================================================
/**

* \file
* \author Rudy Castan
* \author Jonathan Holmes
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#include "DemoFramebuffer.hpp"

#include "CS200/IRenderer2D.hpp"
#include "CS200/NDC.hpp"
#include "CS200/RenderingAPI.hpp"
#include "DemoShapes.hpp"
#include "DemoText.hpp"
#include "Engine/Engine.hpp"
#include "Engine/GameStateManager.hpp"
#include "Engine/Matrix.hpp"
#include "Engine/Random.hpp"
#include "Engine/Texture.hpp"
#include "Engine/TextureManager.hpp"
#include "Engine/Window.hpp"
#include "OpenGL/GL.hpp"
#include "../Game/MainMenu.h"

#include <cmath>
#include <imgui.h>

void DemoFramebuffer::Load()
{
    auto& texture_manager = Engine::GetTextureManager();
    texture_manager.SwitchRenderer(CS230::TextureManager::RendererType::Immediate);
    const auto background_image_paths = { "Assets/images/DemoFramebuffer/Planets.png", "Assets/images/DemoFramebuffer/Ships.png", "Assets/images/DemoFramebuffer/Foreground.png" };
    for (const auto& path : background_image_paths)
    {
        backgroundTextures.push_back(texture_manager.Load(path));
    }

    robotTexture = texture_manager.Load("Assets/images/DemoFramebuffer/Robot.png");
    catTexture   = texture_manager.Load("Assets/images/DemoFramebuffer/Cat.png");
    
    initializeRobotAnimations();
    initializeCatAnimations();
    
    CS200::RenderingAPI::SetClearColor(0x2E3440FF);
    
    // Initialize character states
    idleCat.animation  = CatAnimation::CatIdle;
    idleCat.frameIndex = 0;
    idleCat.timer      = 0.0;
    idleCat.position   = Math::vec2{ 70.0, 80.0 };
    idleCat.faceRight  = true;
    
    jumpingCat.animation  = CatAnimation::CatJumping;
    jumpingCat.frameIndex = 0;
    jumpingCat.timer      = 0.0;
    jumpingCat.position   = Math::vec2{ 700.0, 80.0 };
    jumpingCat.faceRight  = true;
    
    walkingRobot.animation     = RobotAnimation::RobotWalking;
    walkingRobot.frameIndex    = 0;
    walkingRobot.timer         = 0.0;
    walkingRobot.position      = Math::vec2{ 400.0, 80.0 };
    walkingRobot.faceRight     = true;
    walkingRobot.walkDirection = 1.0;   // 1 for right, -1 for left
    walkingRobot.walkSpeed     = 100.0; // pixels per second
    
    initializeWindParticles();

}

template <typename T, typename FLOAT = double>
static void ease_to_target(T& current, const T& target, FLOAT delta_time, FLOAT weight = 1.0)
{
    const auto easing = std::min(delta_time * weight, static_cast<FLOAT>(1.0));
    current += easing * (target - current);
}

void DemoFramebuffer::Update([[maybe_unused]]double dt)
{
    const auto&  environment = Engine::GetWindowEnvironment();
    const double delta_time  = environment.DeltaTime;

    // Ease wind direction towards target
    ease_to_target(windDirection, targetWindDirection, static_cast<float>(delta_time), 1.0f);
    
    ease_to_target(currentParticleCount, static_cast<float>(targetParticleCount), static_cast<float>(delta_time), 0.5f);
    const int newParticleCount = static_cast<int>(std::round(currentParticleCount));
    if (newParticleCount != particleCount)
    {
        particleCount = newParticleCount;
        windParticles.resize(static_cast<size_t>(particleCount));
    }
    
    // Update idle cat
    updateCatAnimation(idleCat, delta_time);
    
    // Update jumping cat with vertical movement
    updateCatAnimation(jumpingCat, delta_time);
    // Add jumping motion (simple sine wave based on animation progress)
    const double jump_progress = jumpingCat.timer / catAnimations[static_cast<int>(CatAnimation::CatJumping)].frames[0].duration;
    const double jump_height   = 150.0 * std::sin(jump_progress * 3.14159); // Simple arc
    jumpingCat.position.y      = 80.0 + jump_height;
    
    // Update walking robot with horizontal movement
    updateRobotAnimation(walkingRobot, delta_time);
    walkingRobot.position.x += walkingRobot.walkDirection * walkingRobot.walkSpeed * delta_time;
    
    if (walkingRobot.position.x <= 130.0)
    {
        walkingRobot.walkDirection = 1.0;
        walkingRobot.faceRight     = true;
    }
    else if (walkingRobot.position.x >= 670.0)
    {
        walkingRobot.walkDirection = -1.0;
        walkingRobot.faceRight     = false;
    }
    
    updateWindParticles(delta_time);

}

void DemoFramebuffer::Draw() 
{
    CS200::RenderingAPI::Clear();

    auto renderer_2d          = Engine::GetTextureManager().GetRenderer2D();
    const auto [width, height] = Engine::GetWindow().GetSize();
    
    // Begin offscreen rendering for wind particles
    const auto render_info = beginOffscreenRendering();
    
    // Render wind particles to offscreen buffer
    drawWindParticles();
    
    // End offscreen rendering and get the scene texture
    const auto scene_texture = endOffscreenRendering(render_info);
    
    // Store texture for ImGui display (clean up previous texture)
    if (lastFramebufferTexture != 0)
    {
        GL::DeleteTextures(1, &lastFramebufferTexture);
    }
    lastFramebufferTexture = scene_texture;
    
    // Render main scene to screen
    renderer_2d->BeginScene(CS200::build_ndc_matrix(Engine::GetWindow().GetSize()));
    
    // Draw background
    for (const auto& texture : backgroundTextures)
    {
        texture->Draw(Math::TransformationMatrix{});
    }
    
    // Draw characters
    drawCat(idleCat);
    drawCat(jumpingCat);
    drawRobot(walkingRobot);
    
    // Conditionally draw scene texture overlay
    if (enableFramebufferOverlay)
    {
        const auto to_center = Math::TranslationMatrix(Math::vec2{ static_cast<double>(width) / 2.0, static_cast<double>(height) / 2.0 });
        const auto scale     = Math::ScaleMatrix({ static_cast<double>(width), static_cast<double>(height) });
        const auto rotate    = Math::RotationMatrix(static_cast<double>(windDirection));
        const auto transform = to_center * rotate * scale;
        renderer_2d->DrawQuad(transform, scene_texture);
    }
    
    renderer_2d->EndScene();
    
    // Note: Don't delete scene_texture here anymore since we're storing it for ImGui

}

void DemoFramebuffer::DrawImGui()
{
    // Main control panel
    if (ImGui::Begin("Demo Controls"))
    {
        ImGui::Checkbox("Enable Framebuffer Overlay", &enableFramebufferOverlay);

        ImGui::SeparatorText("Wind Particle System Controls");
        ImGui::SliderAngle("Wind Direction", &targetWindDirection, 0.0f, 360.0f);
        ImGui::SliderInt("Particle Count", &targetParticleCount, 0, 100);
    
        // Wind speed and direction controls
        ImGui::Text("Wind Speed Range:");
        ImGui::SliderFloat("Min Speed", &windSpeedMin, 10.0f, 200.0f, "%.1f px/s");
        ImGui::SliderFloat("Max Speed", &windSpeedMax, 10.0f, 201.0f, "%.1f px/s");
        if (windSpeedMin >= windSpeedMax)
        {
            windSpeedMax = windSpeedMin + 1.0f;
        }
    
        ImGui::Text("Particle Size Range:");
        ImGui::SliderFloat("Min Size", &particleSizeMin, 0.5f, 10.0f, "%.1f px");
        ImGui::SliderFloat("Max Size", &particleSizeMax, 0.5f, 11.0f, "%.1f px");
        if (particleSizeMin >= particleSizeMax)
        {
            particleSizeMax = particleSizeMin + 1.0f;
        }
    
        ImGui::Text("Particle Color:");
        ImGui::ColorEdit3("Color", particleColor, ImGuiColorEditFlags_Float);
    
        ImGui::SeparatorText("Framebuffer Information");
        if (lastFramebufferTexture != 0)
        {
            const auto [width, height] = Engine::GetWindow().GetSize();
            const auto fb_width        = width / 2;
            const auto fb_height       = height / 2;
            ImGui::Text("Resolution: %dx%d", fb_width, fb_height);
    
            ImGui::SeparatorText("Texture Viewer");
            const float aspect_ratio   = static_cast<float>(fb_width) / static_cast<float>(fb_height);
            const float window_width   = ImGui::GetContentRegionAvail().x;
            const float display_width  = std::max(window_width - 20.0f, 20.0f);
            const float display_height = display_width / aspect_ratio;
            ImGui::Text("Wind Particles Texture");
    
            // Calculate contrasting background color based on particle color
            // Convert particle color to perceived brightness using luminance formula
            const float  luminance     = 0.299f * particleColor[0] + 0.587f * particleColor[1] + 0.114f * particleColor[2];
            const float  contrast_grey = 1.0f - (3.0f * luminance * luminance - 2.0f * luminance * luminance * luminance);
            const ImVec4 background_color(contrast_grey, contrast_grey, contrast_grey, 1.0f);
    
            // Note: ImGui expects texture coordinates with (0,0) at top-left, but OpenGL has (0,0) at bottom-left
            // So we need to flip the V coordinate
            ImGui::ImageWithBg(
                static_cast<ImTextureID>(lastFramebufferTexture), ImVec2(display_width, display_height), ImVec2(0, 1), // uv0 - top-left in ImGui = bottom-left in OpenGL
                ImVec2(1, 0), background_color);
        }
    
        ImGui::SeparatorText("Switch Demo");
        if (ImGui::Button("Switch to Demo Shapes"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<DemoShapes>();
        }
        if (ImGui::Button("Switch to Demo Text"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<DemoText>();
        }
        if (ImGui::Button("Switch to MainMenu"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<MainMenu>();
        }
    }
    ImGui::End();

}

void DemoFramebuffer::Unload()
{
    // Clean up stored framebuffer texture
    if (lastFramebufferTexture != 0)
    {
        GL::DeleteTextures(1, &lastFramebufferTexture);
        lastFramebufferTexture = 0;
    }
}

gsl::czstring DemoFramebuffer::GetName() const
{
    return "Demo Framebuffer";
}

void DemoFramebuffer::initializeRobotAnimations()
{
    robotAnimations.clear();
    robotAnimations.resize(4); // 4 animations: None, RobotDead, RobotWalking, RobotAngry

    // Animation: None - PlayFrame 0 10
    robotAnimations[static_cast<int>(RobotAnimation::None)] = { "None", { { 0, 10.0 } }, 0 };
    
    // Animation: RobotDead - PlayFrame 2 5
    robotAnimations[static_cast<int>(RobotAnimation::RobotDead)] = { "RobotDead", { { 2, 5.0 } }, 0 };
    
    // Animation: RobotWalking - PlayFrame 0 0.2, PlayFrame 1 0.2
    robotAnimations[static_cast<int>(RobotAnimation::RobotWalking)] = {
        "RobotWalking", { { 0, 0.2 }, { 1, 0.2 } },
         0
    };
    
    // Animation: RobotAngry - PlayFrame 3 0.1, PlayFrame 4 0.1
    robotAnimations[static_cast<int>(RobotAnimation::RobotAngry)] = {
        "RobotAngry", { { 3, 0.1 }, { 4, 0.1 } },
         0
    };

}

void DemoFramebuffer::initializeCatAnimations()
{
    catAnimations.clear();
    catAnimations.resize(4); // 4 animations: CatIdle, CatRunning, CatJumping, CatFalling

    // Animation: CatIdle
    catAnimations[static_cast<int>(CatAnimation::CatIdle)] = {
        "CatIdle",
        { { 0, 6.0 }, { 1, 0.5 }, { 2, 0.1 }, { 1, 0.5 }, { 2, 0.1 }, { 1, 0.5 }, { 0, 3.0 }, { 1, 0.5 }, { 2, 0.3 }, { 1, 0.5 },
          { 2, 0.3 }, { 1, 0.5 }, { 0, 3.0 }, { 1, 0.5 }, { 2, 1.0 }, { 1, 0.3 }, { 2, 2.0 }, { 3, 0.4 }, { 4, 0.4 }, { 5, 0.4 } },
        16  // Loop back to frame 16
    };
    
    // Animation: CatRunning - PlayFrame 6 .1, PlayFrame 0 .1, PlayFrame 7 .1, PlayFrame 0 .1, Loop 0
    catAnimations[static_cast<int>(CatAnimation::CatRunning)] = {
        "CatRunning", { { 6, 0.1 }, { 0, 0.1 }, { 7, 0.1 }, { 0, 0.1 } },
         0
    };
    
    // Animation: CatJumping - PlayFrame 9 3, Loop 0
    catAnimations[static_cast<int>(CatAnimation::CatJumping)] = { "CatJumping", { { 9, 3.0 } }, 0 };
    
    // Animation: CatFalling - PlayFrame 8 3, Loop 0
    catAnimations[static_cast<int>(CatAnimation::CatFalling)] = { "CatFalling", { { 8, 3.0 } }, 0 };

}

void DemoFramebuffer::updateCatAnimation(CatState& character, double delta_time)
{
    const auto& anim = catAnimations[static_cast<size_t>(character.animation)];
    character.timer += delta_time;
    const auto& current_frame = anim.frames[static_cast<size_t>(character.frameIndex)];
    if (character.timer >= current_frame.duration)
    {
        character.timer      = 0.0;
        character.frameIndex = (character.frameIndex + 1);
        if (static_cast<size_t>(character.frameIndex) >= anim.frames.size())
        {
            character.frameIndex = anim.loopFrame;
        }
    }
}

void DemoFramebuffer::updateRobotAnimation(RobotState& character, double delta_time)
{
    const auto& anim = robotAnimations[static_cast<size_t>(character.animation)];
    character.timer += delta_time;
    const auto& current_frame = anim.frames[static_cast<size_t>(character.frameIndex)];
    if (character.timer >= current_frame.duration)
    {
        character.timer      = 0.0;
        character.frameIndex = (character.frameIndex + 1);
        if (static_cast<size_t>(character.frameIndex) >= anim.frames.size())
        {
            character.frameIndex = anim.loopFrame;
        }
    }
}

void DemoFramebuffer::drawCat(const CatState& character) const
{
    const auto& anim         = catAnimations[static_cast<size_t>(character.animation)];
    const int   sprite_frame = anim.frames[static_cast<size_t>(character.frameIndex)].frameIndex;
    const auto  texel_base   = CAT_FRAME_POSITIONS[static_cast<size_t>(sprite_frame)];
    const auto  frame_size   = CAT_FRAME_SIZE;
    const auto  hot_spot     = CAT_HOT_SPOT;

    const auto to_center = Math::TranslationMatrix(Math::vec2{ static_cast<double>(-hot_spot.x), static_cast<double>(-hot_spot.y) });
    const auto scale     = character.faceRight ? Math::ScaleMatrix({ 1.0, 1.0 }) : Math::ScaleMatrix({ -1.0, 1.0 });
    const auto translate = Math::TranslationMatrix(character.position);
    const auto transform = translate * scale * to_center;
    
    catTexture->Draw(transform, texel_base, frame_size);

}

void DemoFramebuffer::drawRobot(const RobotState& character) const
{
    const auto& anim         = robotAnimations[static_cast<size_t>(character.animation)];
    const int   sprite_frame = anim.frames[static_cast<size_t>(character.frameIndex)].frameIndex;
    const auto  texel_base   = Math::ivec2{ sprite_frame * ROBOT_FRAME_SIZE.x, 0 };
    const auto  frame_size   = ROBOT_FRAME_SIZE;
    const auto  hot_spot     = ROBOT_HOT_SPOT;

    const auto to_center = Math::TranslationMatrix(Math::vec2{ static_cast<double>(-hot_spot.x), static_cast<double>(-hot_spot.y) });
    const auto scale     = character.faceRight ? Math::ScaleMatrix({ 1.0, 1.0 }) : Math::ScaleMatrix({ -1.0, 1.0 });
    const auto translate = Math::TranslationMatrix(character.position);
    const auto transform = translate * scale * to_center;
    
    robotTexture->Draw(transform, texel_base, frame_size);

}

void DemoFramebuffer::initializeWindParticles()
{
    windParticles.clear();
    for (int i = 0; i < particleCount; ++i)
    {
        WindParticle particle;
        spawnWindParticle(particle);
        windParticles.push_back(particle);
    }
}

void DemoFramebuffer::spawnWindParticle(WindParticle& particle) const
{
    const auto [width, height] = Engine::GetWindow().GetSize() / 2;
    // Always spawn from left edge for left-to-right movement
    particle.position          = Math::vec2{ -20.0, util::random(0.0, static_cast<double>(height)) };

    // Calculate velocity for left-to-right movement
    const double speed = util::random(static_cast<double>(windSpeedMin), static_cast<double>(windSpeedMax));
    particle.velocity  = Math::vec2{
        speed,                  // Horizontal movement (left to right)
        util::random(-5.0, 5.0) // Small vertical variation
    };
    
    particle.size      = util::random(static_cast<double>(particleSizeMin), static_cast<double>(particleSizeMax));
    particle.lifeTimer = 0.0;
    particle.maxLife   = util::random(3.0, 4.0 + 4 * width / 400.0);

}

void DemoFramebuffer::updateWindParticles(double delta_time)
{
    const auto [width, height] = Engine::GetWindow().GetSize() / 2;

    for (auto& particle : windParticles)
    {
        particle.position.x += particle.velocity.x * delta_time;
        particle.position.y += particle.velocity.y * delta_time + std::sin(particle.lifeTimer * 3.1415) * 0.1 * particle.size;
        particle.lifeTimer += delta_time;
        const double life_ratio = particle.lifeTimer / particle.maxLife;
        particle.alpha          = (1.0 - life_ratio);
        if (particle.position.x > width + 20 || particle.lifeTimer >= particle.maxLife)
        {
            spawnWindParticle(particle);
        }
    }

}

void DemoFramebuffer::drawWindParticles() const
{
    auto texture_manager = Engine::GetTextureManager();
    auto renderer_2d = texture_manager.GetRenderer2D();

    for (const auto& particle : windParticles)
    {
        if (particle.alpha > 0.0)
        {
            // Create transform for particle
            const auto        translate  = Math::TranslationMatrix(particle.position);
            const auto        scale      = Math::ScaleMatrix({ particle.size, particle.size });
            const auto        transform  = translate * scale;
            // Set color with alpha using configurable color
            const float       alpha      = static_cast<float>(particle.alpha);
            const CS200::RGBA dust_color = CS200::pack_color({ particleColor[0], particleColor[1], particleColor[2], alpha });
            // Draw particle as a small circle
            renderer_2d->DrawCircle(transform, dust_color, CS200::CLEAR);
        }
    }

}

DemoFramebuffer::RenderInfo DemoFramebuffer::beginOffscreenRendering() const
{
    RenderInfo render_info;
    auto      renderer_2d     = Engine::GetTextureManager().GetRenderer2D();
    const auto [width, height] = Engine::GetWindow().GetSize();

    // End current scene
    renderer_2d->EndScene();
    
    // Set up offscreen framebuffer
    render_info.Size   = { width / 2, height / 2 };
    render_info.Target = OpenGL::CreateFramebufferWithColor(render_info.Size);
    
    // Save current OpenGL state
    GL::GetFloatv(GL_COLOR_CLEAR_VALUE, render_info.ClearColor.data());
    GL::GetIntegerv(GL_VIEWPORT, render_info.Viewport.data());
    
    // Switch to offscreen rendering
    const auto ndc_matrix = Math::ScaleMatrix({ 1.0, 1.0 }) * CS200::build_ndc_matrix(render_info.Size);
    renderer_2d->BeginScene(ndc_matrix);
    GL::BindFramebuffer(GL_FRAMEBUFFER, render_info.Target.Framebuffer);
    GL::Viewport(0, 0, render_info.Size.x, render_info.Size.y);
    GL::ClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    GL::Clear(GL_COLOR_BUFFER_BIT);
    
    return render_info;

}

GLuint DemoFramebuffer::endOffscreenRendering(const RenderInfo& render_info) const
{
    auto renderer_2d = Engine::GetTextureManager().GetRenderer2D();

    // End offscreen scene
    renderer_2d->EndScene();
    
    // Restore OpenGL state
    GL::BindFramebuffer(GL_FRAMEBUFFER, 0);
    GL::Viewport(render_info.Viewport[0], render_info.Viewport[1], render_info.Viewport[2], render_info.Viewport[3]);
    GL::ClearColor(render_info.ClearColor[0], render_info.ClearColor[1], render_info.ClearColor[2], render_info.ClearColor[3]);
    
    // Clean up framebuffer but keep the color texture
    const auto scene_texture         = render_info.Target.ColorAttachment;
    auto       framebuffer_to_delete = render_info.Target.Framebuffer;
    GL::DeleteFramebuffers(1, &framebuffer_to_delete);
    
    return scene_texture;

}

================================================
FILE: source/Demo/DemoFramebuffer.hpp
================================================
/**

* \file
* \author Rudy Castan
* \author Jonathan Holmes
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#pragma once

#include "Engine/GameState.hpp"
#include "Engine/Vec2.hpp"
#include "OpenGL/Framebuffer.hpp"
#include <array>
#include <memory>
#include <string>
#include <vector>

namespace CS230
{
    class Texture;
}

class DemoFramebuffer : public CS230::GameState
{
public:
    void          Load() override;
    void          Update(double dt) override;
    void          Unload() override;
    void          Draw()  override;
    void          DrawImGui() override;
    gsl::czstring GetName() const override;

private:

    struct AnimationFrame
    {
        int    frameIndex{};
        double duration{}; // in seconds
    };
    
    struct Animation
    {
        std::string                 name{};
        std::vector<AnimationFrame> frames{};
        int                         loopFrame{ 0 };
    };
    
    enum class RobotAnimation
    {
        None         = 0,
        RobotDead    = 1,
        RobotWalking = 2,
        RobotAngry   = 3
    };
    
    enum class CatAnimation
    {
        CatIdle    = 0,
        CatRunning = 1,
        CatJumping = 2,
        CatFalling = 3
    };
    
    // Robot sprite sheet info
    static constexpr Math::ivec2 ROBOT_HOT_SPOT{ 30, 20 };
    static constexpr Math::ivec2 ROBOT_FRAME_SIZE{ 63, 127 };
    static constexpr int         ROBOT_NUM_FRAMES = 5;
    
    // Cat sprite sheet info
    static constexpr Math::ivec2 CAT_HOT_SPOT{ 65, 15 };
    static constexpr Math::ivec2 CAT_FRAME_SIZE{ 128, 128 };
    static constexpr int         CAT_NUM_FRAMES = 10;
    
    // Cat frame positions in texture (texel coordinates)
    static constexpr std::array<Math::ivec2, CAT_NUM_FRAMES> CAT_FRAME_POSITIONS = {
        Math::ivec2{   0,   0 }, // Frame 0
        Math::ivec2{ 128,   0 }, // Frame 1
        Math::ivec2{ 256,   0 }, // Frame 2
        Math::ivec2{ 384,   0 }, // Frame 3
        Math::ivec2{ 512,   0 }, // Frame 4
        Math::ivec2{   0, 128 }, // Frame 5
        Math::ivec2{ 128, 128 }, // Frame 6
        Math::ivec2{ 256, 128 }, // Frame 7
        Math::ivec2{ 384, 128 }, // Frame 8
        Math::ivec2{ 512, 128 }  // Frame 9
    };
    
    std::vector<std::shared_ptr<CS230::Texture>> backgroundTextures;
    std::shared_ptr<CS230::Texture>              robotTexture = nullptr;
    std::shared_ptr<CS230::Texture>              catTexture   = nullptr;
    
    // Animation data
    std::vector<Animation> robotAnimations;
    std::vector<Animation> catAnimations;
    
    struct CatState
    {
        CatAnimation animation{};
        int          frameIndex{};
        double       timer{};
        Math::vec2   position{};
        bool         faceRight{};
    };
    
    struct RobotState
    {
        RobotAnimation animation{};
        int            frameIndex{};
        double         timer{};
        Math::vec2     position{};
        bool           faceRight{};
        double         walkDirection{}; // 1 for right, -1 for left
        double         walkSpeed{};     // pixels per second
    };
    
    CatState   idleCat;
    CatState   jumpingCat;
    RobotState walkingRobot;
    
    struct RenderInfo
    {
        OpenGL::FramebufferWithColor Target{};
        Math::ivec2                  Size{};
        std::array<GLfloat, 4>       ClearColor{};
        std::array<GLint, 4>         Viewport{};
    };
    
    struct WindParticle
    {
        Math::vec2 position{};
        Math::vec2 velocity{};
        double     size{};
        double     alpha{};
        double     lifeTimer{};
        double     maxLife{};
    };
    
    std::vector<WindParticle> windParticles;
    
    // ImGui control variables
    bool enableFramebufferOverlay = true;
    
    // Wind particle controls
    int   particleCount        = 3;
    int   targetParticleCount  = 50;
    float currentParticleCount = 3.0f;
    float windSpeedMin         = 80.0f;
    float windSpeedMax         = 140.0f;
    float particleSizeMin      = 1.5f;
    float particleSizeMax      = 4.5f;
    float particleColor[3]     = { 0.9f, 0.8f, 0.6f }; // RGB color
    float windDirection        = 0.0f;
    float targetWindDirection  = 0.0f;
    
    // Store the last rendered framebuffer texture for ImGui display
    mutable GLuint lastFramebufferTexture = 0;

private:
    void       initializeRobotAnimations();
    void       initializeCatAnimations();
    void       updateRobotAnimation(RobotState& character, double delta_time);
    void       updateCatAnimation(CatState& character, double delta_time);
    void       drawRobot(const RobotState& character) const;
    void       drawCat(const CatState& character) const;
    void       initializeWindParticles();
    void       spawnWindParticle(WindParticle& particle) const;
    void       updateWindParticles(double delta_time);
    void       drawWindParticles() const;
    RenderInfo beginOffscreenRendering() const;
    GLuint     endOffscreenRendering(const RenderInfo& render_info) const;
};

================================================
FILE: source/Demo/DemoShapes.cpp
================================================
/**

* \file
* \author Rudy Castan
* \author Jonathan Holmes
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#include "DemoShapes.hpp"
#include "CS200/IRenderer2D.hpp"
#include "CS200/NDC.hpp"
#include "CS200/RGBA.hpp"
#include "CS200/RenderingAPI.hpp"
#include "DemoFramebuffer.hpp"
#include "DemoText.hpp"
#include "Engine/Engine.hpp"
#include "Engine/GameStateManager.hpp"
#include "Engine/Input.hpp"
#include "Engine/Logger.hpp"
#include "Engine/Matrix.hpp"
#include "Engine/Window.hpp"
#include "Engine/TextureManager.hpp"
#include "../Game/MainMenu.h"
#include <cmath>
#include <imgui.h>
#include <iomanip>
#include <numbers>
#include <sstream>

// Arithmetic operators for std::array<float, 4> to support color easing
namespace
{
    std::array<float, 4> operator-(const std::array<float, 4>& a, const std::array<float, 4>& b)
    {
        return { a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3] };
    }

    std::array<float, 4> operator*(double scalar, const std::array<float, 4>& arr)
    {
        const auto s = static_cast<float>(scalar);
        return { s * arr[0], s * arr[1], s * arr[2], s * arr[3] };
    }
    
    std::array<float, 4>& operator+=(std::array<float, 4>& a, const std::array<float, 4>& b)
    {
        a[0] += b[0];
        a[1] += b[1];
        a[2] += b[2];
        a[3] += b[3];
        return a;
    }

}

void DemoShapes::Load()
{
    auto& texture_manager = Engine::GetTextureManager();
    texture_manager.SwitchRenderer(CS230::TextureManager::RendererType::Immediate);

    CS200::RenderingAPI::SetClearColor(0x252525FF);
    
    targetShapePosition     = shapePosition;
    targetShapeRotation     = 0.0;
    targetShapeScale        = { 100.0, 100.0 };
    currentFillColor        = CS200::unpack_color(fillColor);
    currentLineColor        = CS200::unpack_color(lineColor);

}

template <typename T, typename FLOAT = double>
static void ease_to_target(T& current, const T& target, FLOAT delta_time, FLOAT weight = 1.0)
{
    const auto easing = std::min(delta_time * weight, static_cast<FLOAT>(1.0));
    current += easing * (target - current);
}

void DemoShapes::Update([[maybe_unused]]double dt)
{
    const auto& environment = Engine::GetWindowEnvironment();

    // Update input handling (which modifies target values)
    updateInput();
    
    // Apply animations if enabled (modify target values)
    if (animateRotation)
    {
        targetShapeRotation += environment.DeltaTime * 1.5; // 1.5 radians per second
    }
    if (targetShapeRotation > std::numbers::pi * 2.0 && shapeRotation > std::numbers::pi * 2.0)
    {
        targetShapeRotation -= std::numbers::pi * 2.0;
        shapeRotation -= std::numbers::pi * 2.0;
    }
    if (animateScale)
    {
        const double scale_factor_x = 1.0 + 0.3 * std::sin(environment.ElapsedTime * 2.0);
        const double scale_factor_y = 1.0 + 0.3 * std::cos(environment.ElapsedTime * 2.0);
        targetShapeScale            = { 200.0 * scale_factor_x, 200.0 * scale_factor_y };
    }
    
    // Check if shape is offscreen and bring it back to center
    const auto   window_size  = Engine::GetWindow().GetSize();
    // Use shape size as margin - larger shapes trigger reset sooner
    const double margin       = std::max(shapeScale.x, shapeScale.y) + 50.0; // Shape size + 50px buffer
    const bool   is_offscreen = (shapePosition.x < -margin || shapePosition.x > window_size.x + margin || shapePosition.y < -margin || shapePosition.y > window_size.y + margin);
    
    if (is_offscreen)
    {
        // Reset target position to window center to bring shape back
        targetShapePosition.x = window_size.x / 2.0;
        targetShapePosition.y = window_size.y / 2.0;
    }
    
    // Ease current values toward target values
    ease_to_target(shapePosition, targetShapePosition, environment.DeltaTime, 2.0);
    ease_to_target(shapeRotation, targetShapeRotation, environment.DeltaTime, 2.0);
    ease_to_target(shapeScale, targetShapeScale, environment.DeltaTime, 2.0);
    ease_to_target(lineWidth, targetLineWidth, environment.DeltaTime, 2.0);
    
    // Ease colors toward target colors and update packed colors
    ease_to_target(currentFillColor, targetFillColor, environment.DeltaTime, 2.0);
    ease_to_target(currentLineColor, targetLineColor, environment.DeltaTime, 2.0);
    fillColor = CS200::pack_color(currentFillColor);
    lineColor = CS200::pack_color(currentLineColor);

}

void DemoShapes::Draw() 
{
    CS200::RenderingAPI::Clear();
    auto renderer2d = Engine::GetTextureManager().GetRenderer2D();
    renderer2d->BeginScene(CS200::build_ndc_matrix(Engine::GetWindow().GetSize()));

    drawCurrentShape();
    
    renderer2d->EndScene();

}

void DemoShapes::DrawImGui()
{
    if (ImGui::Begin("Demo Controls"))
    {
        // Shape selection
        ImGui::Text("Shape Type:");
        if (ImGui::RadioButton("Rectangle", currentShape == ShapeType::Rectangle))
            currentShape = ShapeType::Rectangle;
        ImGui::SameLine();
        if (ImGui::RadioButton("Circle", currentShape == ShapeType::Circle))
            currentShape = ShapeType::Circle;
        ImGui::SameLine();
        if (ImGui::RadioButton("Line", currentShape == ShapeType::Line))
            currentShape = ShapeType::Line;

        ImGui::SeparatorText("Render Mode");
    
        // Render mode selection
        if (ImGui::RadioButton("Filled", currentRenderMode == RenderMode::Filled))
            currentRenderMode = RenderMode::Filled;
        ImGui::SameLine();
        if (ImGui::RadioButton("Outlined", currentRenderMode == RenderMode::Outlined))
            currentRenderMode = RenderMode::Outlined;
        ImGui::SameLine();
        if (ImGui::RadioButton("Both", currentRenderMode == RenderMode::Both))
            currentRenderMode = RenderMode::Both;
    
        ImGui::SeparatorText("Transform");
    
        // Transform controls (modify target values for smooth easing)
        float      pos[2]      = { static_cast<float>(targetShapePosition.x), static_cast<float>(targetShapePosition.y) };
        const auto window_size = Engine::GetWindow().GetSize();
        const auto range_limit = static_cast<float>(std::max(window_size.x, window_size.y) + 100);
        if (ImGui::SliderFloat2("Position", pos, -100.0f, range_limit))
        {
            targetShapePosition.x = static_cast<double>(pos[0]);
            targetShapePosition.y = static_cast<double>(pos[1]);
        }
    
        float rotation = static_cast<float>(targetShapeRotation);
        if (ImGui::SliderAngle("Rotation", &rotation))
            targetShapeRotation = static_cast<double>(rotation);
    
        float scale[2] = { static_cast<float>(targetShapeScale.x), static_cast<float>(targetShapeScale.y) };
        if (ImGui::SliderFloat2("Scale", scale, 10.0f, 300.0f))
        {
            targetShapeScale.x = static_cast<double>(scale[0]);
            targetShapeScale.y = static_cast<double>(scale[1]);
        }
    
        ImGui::SeparatorText("Colors");
    
        // Color controls (modify target colors for smooth easing)
        ImGui::ColorEdit3("Fill Color", targetFillColor.data());
        ImGui::ColorEdit3("Line Color", targetLineColor.data());
    
        float line_width_float = static_cast<float>(targetLineWidth);
        if (ImGui::SliderFloat("Line Width", &line_width_float, 0.5f, 64.0f))
        {
            targetLineWidth = static_cast<double>(line_width_float);
        }
    
        ImGui::SeparatorText("Animation");
    
        // Animation controls
        ImGui::Checkbox("Animate Rotation", &animateRotation);
        ImGui::Checkbox("Animate Scale", &animateScale);
    
        ImGui::SeparatorText("Statistics");
    
        // Statistics
        ImGui::Text("Controls: Arrow Keys - Move, Q/E - Rotate");
        ImGui::Text("Current Mode: %s", getRenderModeString());
        ImGui::Text("Current Shape: %s", getShapeTypeString());
    
        ImGui::SeparatorText("Switch Demo");
        if (ImGui::Button("Switch to Demo Framebuffer"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<DemoFramebuffer>();
        }
        if (ImGui::Button("Switch to Demo Text"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<DemoText>();
        }
    
        if (ImGui::Button("Switch to MainMenu"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<MainMenu>();
        }
    }
    ImGui::End();

}

void DemoShapes::Unload()
{
    Engine::GetLogger().LogEvent("DemoShapes: Unloaded");
}

gsl::czstring DemoShapes::GetName() const
{
    return "Demo Shapes - 2D Rendering Showcase";
}

void DemoShapes::updateInput()
{
    const auto&  input          = Engine::GetInput();
    const auto&  environment    = Engine::GetWindowEnvironment();
    const double move_speed     = 200.0; // pixels per second
    const double rotation_speed = 2.0;   // radians per second

    // Movement controls (modify target values for smooth easing)
    if (input.KeyDown(CS230::Input::Keys::Left))
        targetShapePosition.x -= move_speed * environment.DeltaTime;
    if (input.KeyDown(CS230::Input::Keys::Right))
        targetShapePosition.x += move_speed * environment.DeltaTime;
    if (input.KeyDown(CS230::Input::Keys::Up))
        targetShapePosition.y += move_speed * environment.DeltaTime;
    if (input.KeyDown(CS230::Input::Keys::Down))
        targetShapePosition.y -= move_speed * environment.DeltaTime;
    
    // Rotation controls (modify target values for smooth easing)
    if (input.KeyDown(CS230::Input::Keys::Q))
        targetShapeRotation -= rotation_speed * environment.DeltaTime;
    if (input.KeyDown(CS230::Input::Keys::E))
        targetShapeRotation += rotation_speed * environment.DeltaTime;

}

void DemoShapes::drawCurrentShape() const
{
    switch (currentShape)
    {
        case ShapeType::Rectangle: drawRectangles(); break;
        case ShapeType::Circle: drawCircles(); break;
        case ShapeType::Line: drawLines(); break;
    }
}

void DemoShapes::drawRectangles() const
{
    auto      renderer2d = Engine::GetTextureManager().GetRenderer2D();
    const auto transform  = getShapeTransform();

    // Draw main rectangle with current settings
    renderer2d->DrawRectangle(transform, getFillColor(), getLineColor(), lineWidth);
    
    // Draw additional example rectangles to show different modes
    const double offset_x    = 200.0;
    const double small_scale = 60.0;
    
    // Filled only example
    auto filled_transform =
        Math::TranslationMatrix(Math::vec2{ shapePosition.x - offset_x, shapePosition.y + 150.0 }) * Math::RotationMatrix(shapeRotation * 0.5) * Math::ScaleMatrix({ small_scale, small_scale });
    renderer2d->DrawRectangle(filled_transform, 0x4CAF50FF, CS200::CLEAR, 0.0);
    
    // Outlined only example
    auto outlined_transform =
        Math::TranslationMatrix(Math::vec2{ shapePosition.x, shapePosition.y + 150.0 }) * Math::RotationMatrix(-shapeRotation * 0.5) * Math::ScaleMatrix({ small_scale, small_scale });
    renderer2d->DrawRectangle(outlined_transform, CS200::CLEAR, 0xFF9800FF, 2.0);
    
    // Both fill and outline example
    auto both_transform =
        Math::TranslationMatrix(Math::vec2{ shapePosition.x + offset_x, shapePosition.y + 150.0 }) * Math::RotationMatrix(shapeRotation * 0.3) * Math::ScaleMatrix({ small_scale, small_scale });
    renderer2d->DrawRectangle(both_transform, 0x9C27B0FF, 0xFFEB3BFF, 3.0);

}

void DemoShapes::drawCircles() const
{
    auto      renderer2d = Engine::GetTextureManager().GetRenderer2D();
    const auto transform  = getShapeTransform();

    // Draw main circle with current settings
    renderer2d->DrawCircle(transform, getFillColor(), getLineColor(), lineWidth);
    
    // Draw additional example circles to show different modes
    const double offset_x    = 200.0;
    const double small_scale = 60.0;
    
    // Filled only example
    auto filled_transform = Math::TranslationMatrix(Math::vec2{ shapePosition.x - offset_x, shapePosition.y + 150.0 }) * Math::ScaleMatrix({ small_scale, small_scale });
    renderer2d->DrawCircle(filled_transform, 0xF44336FF, CS200::CLEAR, 0.0);
    
    // Outlined only example
    auto outlined_transform = Math::TranslationMatrix(Math::vec2{ shapePosition.x, shapePosition.y + 150.0 }) * Math::ScaleMatrix({ small_scale, small_scale });
    renderer2d->DrawCircle(outlined_transform, CS200::CLEAR, 0x2196F3FF, 2.0);
    
    // Both fill and outline example
    auto both_transform = Math::TranslationMatrix(Math::vec2{ shapePosition.x + offset_x, shapePosition.y + 150.0 }) * Math::ScaleMatrix({ small_scale, small_scale });
    renderer2d->DrawCircle(both_transform, 0xFF5722FF, 0x00BCD4FF, 3.0);

}

void DemoShapes::drawLines() const
{
    auto renderer2d = Engine::GetTextureManager().GetRenderer2D();

    // Draw transformation-based line (transforms with the shape)
    const auto transform = Math::TranslationMatrix(shapePosition) * Math::RotationMatrix(shapeRotation);
    renderer2d->DrawLine(transform * Math::ScaleMatrix({ shapeScale.x, 1.0 }), Math::vec2{ -0.5, 0.0 }, Math::vec2{ 0.5, 0.0 }, getLineColor(), lineWidth);
    renderer2d->DrawLine(transform * Math::ScaleMatrix({ 1.0, shapeScale.y }), Math::vec2{ 0.0, -0.5 }, Math::vec2{ 0.0, 0.5 }, getLineColor(), lineWidth);
    
    const auto display_size = Engine::GetWindowEnvironment().DisplaySize;
    // Draw world-coordinate lines (fixed positions)
    const auto into_screen  = lineWidth * 0.5;
    renderer2d->DrawLine({ 0.0, into_screen }, { display_size.x, into_screen }, lineColor, lineWidth);
    renderer2d->DrawLine({ into_screen, 0.0 }, { into_screen, display_size.y }, lineColor, lineWidth);
    renderer2d->DrawLine({ 0.0, display_size.y - into_screen }, { display_size.x, display_size.y - into_screen }, lineColor, lineWidth);
    renderer2d->DrawLine({ display_size.x - into_screen, 0.0 }, { display_size.x - into_screen, display_size.y }, lineColor, lineWidth);

}

Math::TransformationMatrix DemoShapes::getShapeTransform() const
{
    return Math::TranslationMatrix(shapePosition) * Math::RotationMatrix(shapeRotation) * Math::ScaleMatrix(shapeScale);
}

CS200::RGBA DemoShapes::getFillColor() const
{
    switch (currentRenderMode)
    {
        case RenderMode::Filled:
        case RenderMode::Both: return fillColor;
        case RenderMode::Outlined: return CS200::CLEAR;
        default: return CS200::CLEAR;
    }
}

CS200::RGBA DemoShapes::getLineColor() const
{
    switch (currentRenderMode)
    {
        case RenderMode::Outlined:
        case RenderMode::Both: return lineColor;
        case RenderMode::Filled: return CS200::CLEAR;
        default: return CS200::CLEAR;
    }
}

const char* DemoShapes::getRenderModeString() const
{
    switch (currentRenderMode)
    {
        case RenderMode::Filled: return "Filled";
        case RenderMode::Outlined: return "Outlined";
        case RenderMode::Both: return "Both";
        default: return "Unknown";
    }
}

const char* DemoShapes::getShapeTypeString() const
{
    switch (currentShape)
    {
        case ShapeType::Rectangle: return "Rectangle";
        case ShapeType::Circle: return "Circle";
        case ShapeType::Line: return "Line";
        default: return "Unknown";
    }
}

================================================
FILE: source/Demo/DemoShapes.hpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#pragma once

#include "CS200/RGBA.hpp"
#include "Engine/GameState.hpp"
#include "Engine/Matrix.hpp"
#include "Engine/Vec2.hpp"
#include <array>
#include <gsl/gsl>

class DemoShapes : public CS230::GameState
{
public:
    void          Load() override;
    void          Update(double dt) override;
    void          Unload() override;
    void          Draw() override;
    void          DrawImGui() override;
    gsl::czstring GetName() const override;

private:

    enum class RenderMode
    {
        Filled,
        Outlined,
        Both
    };
    
    
    enum class ShapeType
    {
        Rectangle,
        Circle,
        Line
    };
    
    // Shape properties
    Math::vec2 shapePosition{ -300.0, -300.0 };
    double     shapeRotation = 0.0;
    Math::vec2 shapeScale{ 100.0, 100.0 };
    
    // Target values for smooth easing
    Math::vec2 targetShapePosition{ 0.0, 0.0 };
    double     targetShapeRotation = 0.0;
    Math::vec2 targetShapeScale{ 100.0, 100.0 };
    
    // Visual properties
    CS200::RGBA fillColor = CS200::BLACK;
    CS200::RGBA lineColor = CS200::BLACK;
    double      lineWidth = 10.0;
    
    // Current visual properties (using float arrays for smooth color easing)
    std::array<float, 4> currentFillColor = { 0.259f, 0.522f, 0.957f, 1.0f };
    std::array<float, 4> currentLineColor = { 0.859f, 0.267f, 0.216f, 1.0f };
    double               targetLineWidth  = 4.0;
    std::array<float, 4> targetFillColor  = { 0.259f, 0.522f, 0.957f, 1.0f };
    std::array<float, 4> targetLineColor  = { 0.859f, 0.267f, 0.216f, 1.0f };
    
    // Demo state
    RenderMode currentRenderMode = RenderMode::Both;
    ShapeType  currentShape      = ShapeType::Rectangle;
    
    // Animation and interaction
    bool animateRotation = false;
    bool animateScale    = false;

private:
    void                       updateInput();
    void                       drawCurrentShape() const;
    void                       drawRectangles() const;
    void                       drawCircles() const;
    void                       drawLines() const;
    void                       drawColorPalette() const;
    Math::TransformationMatrix getShapeTransform() const;
    CS200::RGBA                getFillColor() const;
    CS200::RGBA                getLineColor() const;
    const char*                getRenderModeString() const;
    const char*                getShapeTypeString() const;
};

================================================
FILE: source/Demo/DemoText.cpp
================================================
/**

* \file
* \author Generated
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#include "DemoText.hpp"
#include "CS200/IRenderer2D.hpp"
#include "CS200/NDC.hpp"
#include "CS200/RenderingAPI.hpp"
#include "DemoFramebuffer.hpp"
#include "DemoShapes.hpp"
#include "Engine/Engine.hpp"
#include "Engine/GameStateManager.hpp"
#include "Engine/Texture.hpp"
#include "Engine/Window.hpp"
#include "Engine/TextureManager.hpp"
#include "../Game/MainMenu.h"
#include <imgui.h>
#include <sstream>

void DemoText::Load()
{
    auto& texture_manager = Engine::GetTextureManager();
    texture_manager.SwitchRenderer(CS230::TextureManager::RendererType::Immediate);
    CS200::RenderingAPI::SetClearColor(0x2E3440FF);

    simpleFont   = std::make_unique<CS230::Font>("Assets/fonts/Font_Simple.png");
    outlinedFont = std::make_unique<CS230::Font>("Assets/fonts/Font_Outlined.png");
    
    updateCachedTextures();

}

void DemoText::Update([[maybe_unused]]double dt)
{
    const auto& environment = Engine::GetWindowEnvironment();

    if (environment.ElapsedTime - lastOccasionalTextUpdate >= settings.OccasionalUpdateInterval)
    {
        lastOccasionalTextUpdate = environment.ElapsedTime;
        occasionalCounter++;
        occasionalText = "Sometimes changing: " + std::to_string(occasionalCounter);
    }
    
    if (environment.ElapsedTime - lastFrequentTextUpdate >= settings.FrequentUpdateInterval)
    {
        lastFrequentTextUpdate = environment.ElapsedTime;
        frequentCounter++;
        frequentText = "Frequent: " + std::to_string(frequentCounter);
    }
    
    updateCachedTextures();

}

void DemoText::Unload()
{
}

void DemoText::Draw() 
{
    CS200::RenderingAPI::Clear();
    auto renderer2d = Engine::GetTextureManager().GetRenderer2D();
    renderer2d->BeginScene(CS200::build_ndc_matrix(Engine::GetWindow().GetSize()));

    const auto   display_size = Engine::GetWindowEnvironment().DisplaySize;
    // Draw world-coordinate lines (fixed positions)
    const double line_width   = 16.0;
    const auto   into_screen  = line_width * 0.5;
    const auto   rect_size    = display_size - Math::vec2{ into_screen, into_screen };
    // const auto lineColor = CS200::BLACK;
    renderer2d->DrawRectangle(Math::TranslationMatrix(rect_size * 0.5) * Math::ScaleMatrix(rect_size), 0x2E3440FF, CS200::BLACK, line_width);
    // renderer2d.DrawLine({ 0.0, into_screen }, { display_size.x, into_screen }, lineColor, line_width);
    // renderer2d.DrawLine({ into_screen, 0.0 }, { into_screen, display_size.y }, lineColor, line_width);
    // renderer2d.DrawLine({ 0.0, display_size.y - into_screen }, { display_size.x, display_size.y - into_screen }, lineColor, line_width);
    // renderer2d.DrawLine({ display_size.x - into_screen, 0.0 }, { display_size.x - into_screen, display_size.y }, lineColor, line_width);
    
    constexpr double BOTTOM_START = 10.0;
    
    // Calculate center X position based on the widest text
    double center_x  = LEFT_MARGIN;
    double max_width = 0.0;
    
    // Find the widest text among all displayed texts
    if (settings.ShowSimpleFont)
    {
        if (auto texture = simpleFont->PrintToTexture(frequentText, 0x00FFFFFF))
            max_width = std::max(max_width, static_cast<double>(texture->GetSize().x) * settings.TextScale);
        if (auto texture = simpleFont->PrintToTexture(occasionalText, 0xFF00FFFF))
            max_width = std::max(max_width, static_cast<double>(texture->GetSize().x) * settings.TextScale);
        if (auto texture = simpleFont->PrintToTexture(staticText, settings.TextColor))
            max_width = std::max(max_width, static_cast<double>(texture->GetSize().x) * settings.TextScale);
    }
    
    if (settings.ShowOutlinedFont)
    {
        if (auto texture = outlinedFont->PrintToTexture(frequentText, 0xFF8000FF))
            max_width = std::max(max_width, static_cast<double>(texture->GetSize().x) * settings.TextScale);
        if (auto texture = outlinedFont->PrintToTexture(occasionalText, 0xFFFF00FF))
            max_width = std::max(max_width, static_cast<double>(texture->GetSize().x) * settings.TextScale);
        if (auto texture = outlinedFont->PrintToTexture(staticText, settings.TextColor))
            max_width = std::max(max_width, static_cast<double>(texture->GetSize().x) * settings.TextScale);
    }
    
    // Calculate the starting X position for center alignment
    const auto window_size = Engine::GetWindow().GetSize();
    center_x               = (window_size.x - max_width) / 2.0;
    
    double current_y = BOTTOM_START;
    
    if (settings.ShowSimpleFont)
    {
        drawText(frequentText, Math::vec2{ center_x, current_y }, *simpleFont, 0x00FFFFFF);
        current_y += LINE_HEIGHT;
    
        drawText(occasionalText, Math::vec2{ center_x, current_y }, *simpleFont, 0xFF00FFFF);
        current_y += LINE_HEIGHT;
    
        drawText(staticText, Math::vec2{ center_x, current_y }, *simpleFont, settings.TextColor);
        current_y += LINE_HEIGHT;
    }
    
    if (settings.ShowOutlinedFont)
    {
        drawText(frequentText, Math::vec2{ center_x, current_y }, *outlinedFont, 0xFF8000FF);
        current_y += LINE_HEIGHT;
    
        drawText(occasionalText, Math::vec2{ center_x, current_y }, *outlinedFont, 0xFFFF00FF);
        current_y += LINE_HEIGHT;
    
        drawText(staticText, Math::vec2{ center_x, current_y }, *outlinedFont, settings.TextColor);
        current_y += LINE_HEIGHT;
    }
    
    if (settings.ShowCacheAddresses)
    {
        drawCacheInfo(current_y, center_x);
    }
    
    renderer2d->EndScene();

}

void DemoText::DrawImGui()
{
    if (ImGui::Begin("Demo Controls"))
    {
        ImGui::Checkbox("Show Simple Font", &settings.ShowSimpleFont);
        ImGui::Checkbox("Show Outlined Font", &settings.ShowOutlinedFont);
        ImGui::Checkbox("Show Cache Addresses", &settings.ShowCacheAddresses);

        ImGui::SeparatorText("Text Appearance");
    
        float color[4] = { static_cast<float>((settings.TextColor >> 24) & 0xFF) / 255.0f, static_cast<float>((settings.TextColor >> 16) & 0xFF) / 255.0f,
                           static_cast<float>((settings.TextColor >> 8) & 0xFF) / 255.0f, static_cast<float>(settings.TextColor & 0xFF) / 255.0f };
        if (ImGui::ColorEdit4("Text Color", color))
        {
            settings.TextColor =
                (static_cast<uint32_t>(color[0] * 255) << 24) | (static_cast<uint32_t>(color[1] * 255) << 16) | (static_cast<uint32_t>(color[2] * 255) << 8) | static_cast<uint32_t>(color[3] * 255);
        }
    
        float text_scale = static_cast<float>(settings.TextScale);
        ImGui::SliderFloat("Text Scale", &text_scale, 0.5f, 3.0f);
        settings.TextScale = static_cast<double>(text_scale);
    
        ImGui::SeparatorText("Update Intervals");
    
        float intervals[] = { static_cast<float>(settings.OccasionalUpdateInterval), static_cast<float>(settings.FrequentUpdateInterval) };
        ImGui::SliderFloat("Occasional Update Interval", intervals, 0.5f, 5.0f);
        ImGui::SliderFloat("Frequent Update Interval", intervals + 1, 0.1f, 2.0f);
        settings.OccasionalUpdateInterval = static_cast<double>(intervals[0]);
        settings.FrequentUpdateInterval   = static_cast<double>(intervals[1]);
    
        ImGui::SeparatorText("Current Text Content");
        ImGui::TextWrapped("Static: %s", staticText.c_str());
        ImGui::TextWrapped("Occasional: %s", occasionalText.c_str());
        ImGui::TextWrapped("Frequent: %s", frequentText.c_str());
    
        ImGui::SeparatorText("Cache Information");
        ImGui::Text("Static Text Address: %p", staticTextAddress);
        ImGui::Text("Occasional Text Address: %p", occasionalTextAddress);
        ImGui::Text("Frequent Text Address: %p", frequentTextAddress);
        ImGui::Text("Blinking Header Address: %p", blinkingHeaderAddress);
    
        ImGui::SeparatorText("Cache Analysis");
    
        if (staticTextAddress == lastStaticAddress && lastStaticAddress != nullptr)
        {
            ImGui::TextColored(ImVec4(0, 1, 0, 1), "Static text is cached (same address)");
        }
        else
        {
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "Static text address changed");
            lastStaticAddress = staticTextAddress;
        }
    
        if (blinkingHeaderAddress == lastBlinkingAddress && lastBlinkingAddress != nullptr)
        {
            ImGui::TextColored(ImVec4(0, 1, 0, 1), "Blinking header is cached (same address)");
        }
        else
        {
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "Blinking header address changed");
            lastBlinkingAddress = blinkingHeaderAddress;
        }
    
        ImGui::SeparatorText("Switch Demo");
        if (ImGui::Button("Switch to Demo Framebuffer"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<DemoFramebuffer>();
        }
        if (ImGui::Button("Switch to Demo Shapes"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<DemoShapes>();
        }
    
        if (ImGui::Button("Switch to MainMenu"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<MainMenu>();
        }
    }
    
    ImGui::End();

}

gsl::czstring DemoText::GetName() const
{
    return "Text Demo";
}

void DemoText::updateCachedTextures()
{
    if (simpleFont)
    {
        staticTextTexture = simpleFont->PrintToTexture(staticText, settings.TextColor);
        staticTextAddress = staticTextTexture.get();

        occasionalTextTexture = simpleFont->PrintToTexture(occasionalText, 0xFF00FFFF);
        occasionalTextAddress = occasionalTextTexture.get();
    
        frequentTextTexture = simpleFont->PrintToTexture(frequentText, 0x00FFFFFF);
        frequentTextAddress = frequentTextTexture.get();
    }

}

void DemoText::drawText(const std::string& text, const Math::vec2& position, CS230::Font& font, CS200::RGBA color) const
{
    if (auto text_texture = font.PrintToTexture(text, color); text_texture)
    {
        const auto transform = Math::TranslationMatrix(position) * Math::ScaleMatrix(Math::vec2{ settings.TextScale, settings.TextScale });
        text_texture->Draw(transform, color);
    }
}

void DemoText::drawCacheInfo(double start_y, double x_offset) const
{
    if (!simpleFont)
        return;

    double current_y = start_y;
    
    std::stringstream frequent_info;
    frequent_info << "Frequent: " << std::hex << frequentTextAddress;
    drawText(frequent_info.str(), Math::vec2{ x_offset, current_y }, *outlinedFont, CS200::WHITE);
    current_y += LINE_HEIGHT;
    
    std::stringstream occasional_info;
    occasional_info << "Occasional: " << std::hex << occasionalTextAddress;
    drawText(occasional_info.str(), Math::vec2{ x_offset, current_y }, *outlinedFont, CS200::WHITE);
    current_y += LINE_HEIGHT;
    
    std::stringstream static_info;
    static_info << "Static: " << std::hex << staticTextAddress;
    drawText(static_info.str(), Math::vec2{ x_offset, current_y }, *outlinedFont, CS200::WHITE);
    current_y += LINE_HEIGHT;
    
    std::stringstream blinking_info;
    blinking_info << "Blinking: " << std::hex << blinkingHeaderAddress;
    drawText(blinking_info.str(), Math::vec2{ x_offset, current_y }, *outlinedFont, 0xAAAAAAFF);
    current_y += LINE_HEIGHT;
    
    const uint64_t current_frame = Engine::GetWindowEnvironment().FrameCount;
    const uint64_t cycle_frame   = current_frame & (BLINKING_CYCLE_FRAMES - 1);
    
    if (const bool should_show_blinking_header = cycle_frame >= VISIBLE_START_FRAME; should_show_blinking_header)
    {
        auto temp_blinking_texture = outlinedFont->PrintToTexture("Cache Demo - Memory Addresses:", CS200::WHITE);
        blinkingHeaderAddress      = temp_blinking_texture.get();
        const auto transform       = Math::TranslationMatrix(Math::vec2{ x_offset, current_y }) * Math::ScaleMatrix(Math::vec2{ settings.TextScale, settings.TextScale });
        temp_blinking_texture->Draw(transform, CS200::WHITE);
    }

}

================================================
FILE: source/Demo/DemoText.hpp
================================================
/**

* \file
* \author Generated
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#pragma once

#include "CS200/RGBA.hpp"
#include "Engine/Font.hpp"
#include "Engine/GameState.hpp"
#include "Engine/Vec2.hpp"
#include <gsl/gsl>
#include <memory>

class DemoText : public CS230::GameState
{
public:
    void          Load() override;
    void          Update(double dt) override;
    void          Unload() override;
    void          Draw()  override;
    void          DrawImGui() override;
    gsl::czstring GetName() const override;

private:
    std::unique_ptr<CS230::Font> simpleFont;
    std::unique_ptr<CS230::Font> outlinedFont;

    double lastOccasionalTextUpdate = 0.0;
    double lastFrequentTextUpdate   = 0.0;
    
    std::string staticText     = "This text never changes";
    std::string occasionalText = "Sometimes changing: 0";
    std::string frequentText   = "Frequent: 0";
    
    int occasionalCounter = 0;
    int frequentCounter   = 0;
    
    std::shared_ptr<CS230::Texture> staticTextTexture;
    std::shared_ptr<CS230::Texture> occasionalTextTexture;
    std::shared_ptr<CS230::Texture> frequentTextTexture;
    
    void*         staticTextAddress     = nullptr;
    void*         occasionalTextAddress = nullptr;
    void*         frequentTextAddress   = nullptr;
    mutable void* blinkingHeaderAddress = nullptr;
    
    void* lastStaticAddress   = nullptr;
    void* lastBlinkingAddress = nullptr;
    
    struct Settings
    {
        bool        ShowSimpleFont           = true;
        bool        ShowOutlinedFont         = true;
        bool        ShowCacheAddresses       = true;
        CS200::RGBA TextColor                = CS200::WHITE;
        double      TextScale                = 1.0;
        double      OccasionalUpdateInterval = 2.0;
        double      FrequentUpdateInterval   = 0.5;
    } settings;
    
    static constexpr double   LEFT_MARGIN           = 50.0;
    static constexpr double   LINE_HEIGHT           = 64.0;
    static constexpr uint64_t BLINKING_CYCLE_FRAMES = 256;
    static constexpr uint64_t VISIBLE_START_FRAME   = 30;

private:
    void updateCachedTextures();
    void drawText(const std::string& text, const Math::vec2& position, CS230::Font& font, CS200::RGBA color = CS200::WHITE) const;
    void drawCacheInfo(double start_y, double x_offset) const;
};

================================================
FILE: source/Demo/DemoTexturing.hpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "CS200/NDC.hpp"
  #include "CS200/RGBA.hpp"
  #include "Engine/GameState.hpp"
  #include "OpenGL/Buffer.hpp"
  #include "OpenGL/Shader.hpp"
  #include "OpenGL/Texture.hpp"
  #include "OpenGL/VertexArray.hpp"
  #include <array>
  #include <vector>

class DemoTexturing : public CS230::GameState
{
public:
    void          Load() override;
    void          Unload() override;
    void          Update(double dt) override;
    void          Draw() override;
    void          DrawImGui() override;
    gsl::czstring GetName() const override;

private:
    OpenGL::CompiledShader texturingCombineShader{};

    struct object
    {
        OpenGL::BufferHandle      positionBufferHandle{};
        OpenGL::BufferHandle      colorBufferHandle{};
        OpenGL::BufferHandle      texCoordBufferHandle{};
        OpenGL::BufferHandle      indexBufferHandle{};
        GLsizei                   indicesCount{};
        OpenGL::VertexArrayHandle modelHandle{};
    } quad{};
    
    constexpr static int QuadSize = 256;
    
    OpenGL::TextureHandle duckTextureHandle{};
    OpenGL::TextureHandle noiseTextureHandle{};
    OpenGL::TextureHandle logoTextureHandle{};
    
    enum class TextureType
    {
        Duck  = 0,
        Noise = 1,
        Logo  = 2
    };
    
    struct Settings
    {
        int                   FilteringIndex           = 0;
        std::array<int, 2>    WrapIndex                = { 0, 0 };
        float                 TexCoordScale            = 1.0f;
        float                 TargetTexCoordScale      = 1.0f;
        bool                  ModulateColor            = false;
        bool                  ApplyProceduralTexture   = false;
        float                 ProceduralTileSize       = 32.0f;
        float                 TargetProceduralTileSize = 32.0f;
        bool                  UseTexture               = true;
        TextureType           SelectedTexture          = TextureType::Duck;
        bool                  DoBlending               = false;
        bool                  AnimateProceduralTexture = false;
        static constexpr auto MAX_TILE_SIZE            = 256.0f;
        static constexpr auto MIN_TILE_SIZE            = 16.0f;
    } settings;

private:
    void loadShaders();
    void createQuadModel();
    void createNoiseTexture();
    void createLogoTexture();
    void imgui_pick_filtering();
    void imgui_pick_wrapping(const char* label, OpenGL::TextureCoordinate which_coord);
};

================================================
FILE: source/Demo/DemoVAO.cpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "DemoVAO.hpp"
  #include "CS200/RenderingAPI.hpp"
  #include "Engine/Engine.hpp"
  #include "Engine/GameStateManager.hpp"
  #include "OpenGL/GL.hpp"
  #include "OpenGL/Shader.hpp"
  #include "OpenGL/VertexArray.hpp"
  #include "../Game/MainMenu.h"
  #include <algorithm>
  #include <imgui.h>

void DemoVAO::Load()
{
    using filepath = std::filesystem::path;
    simpleShader   = OpenGL::CreateShader(filepath{ "Assets/shaders/pass_thru_pos2d_clr.vert" }, filepath{ "Assets/shaders/basic_vtx_clr_attribute.frag" });

    GL::GenBuffers(static_cast<GLsizei>(bufferHandles.size()), bufferHandles.data());
    GL::GenBuffers(static_cast<GLsizei>(indexBufferHandles.size()), indexBufferHandles.data());
    
    create_1buffer_struct_of_arrays_style();
    create_1buffer_array_of_structs_style();
    create_parallel_buffers_style();

}

void DemoVAO::Unload()
{
    OpenGL::DestroyShader(simpleShader);
    GL::DeleteVertexArrays(1, &leftEyeModel), leftEyeModel   = 0;
    GL::DeleteVertexArrays(1, &rightEyeModel), rightEyeModel = 0;
    GL::DeleteVertexArrays(1, &mouthModel), mouthModel       = 0;
    GL::DeleteBuffers(static_cast<GLsizei>(bufferHandles.size()), bufferHandles.data());
    std::fill(std::begin(bufferHandles), std::end(bufferHandles), 0);
    GL::DeleteBuffers(static_cast<GLsizei>(indexBufferHandles.size()), indexBufferHandles.data());
    std::fill(std::begin(indexBufferHandles), std::end(indexBufferHandles), 0);
}

void DemoVAO::Update([[maybe_unused]]double dt)
{
    hue += 0.25f;
    if (hue >= 360.0f)
        hue -= 360.0f;
}

void DemoVAO::Draw() 
{
    constexpr GLsizei        indices_count            = 6;
    constexpr GLenum         primitive_pattern        = GL_TRIANGLES;
    constexpr GLenum         left_eye_indices_type    = GL_UNSIGNED_INT;
    constexpr GLenum         right_eye_indices_type   = GL_UNSIGNED_SHORT;
    constexpr GLenum         mouth_indices_type       = GL_UNSIGNED_BYTE;
    constexpr GLvoid*        byte_offset_into_indices = nullptr;
    constexpr OpenGL::Handle no_object                = 0;

    calculate_and_set_clear_color();
    CS200::RenderingAPI::Clear();
    
    GL::UseProgram(simpleShader.Shader);
    
    GL::BindVertexArray(leftEyeModel);
    GL::DrawElements(primitive_pattern, indices_count, left_eye_indices_type, byte_offset_into_indices);
    
    GL::BindVertexArray(rightEyeModel);
    GL::DrawElements(primitive_pattern, indices_count, right_eye_indices_type, byte_offset_into_indices);
    
    GL::BindVertexArray(mouthModel);
    GL::DrawElements(primitive_pattern, indices_count, mouth_indices_type, byte_offset_into_indices);
    
    GL::BindVertexArray(no_object);
    GL::UseProgram(no_object);

}

void DemoVAO::DrawImGui()
{
    ImGui::Begin("Program Info");
    {
        ImGui::LabelText("FPS", "%d", Engine::GetWindowEnvironment().FPS);
        {
            float r = 0, g = 0, b = 0;
            ImGui::ColorConvertHSVtoRGB(hue / 360.0f, saturation, value, r, g, b);
            ImGui::LabelText("Background Color", "RGB(%.0f,%.0f,%.0f)", static_cast<double>(r * 255), static_cast<double>(g * 255), static_cast<double>(b * 255));
        }
        ImGui::SeparatorText("Switch Demo");
        if (ImGui::Button("Switch to MainMenu"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<MainMenu>();
        }

    }
    ImGui::End();

}

DemoVAO::~DemoVAO()
{
    Unload();
}

void DemoVAO::calculate_and_set_clear_color() const
{
    float r = 0, g = 0, b = 0;
    ImGui::ColorConvertHSVtoRGB(hue / 360.0f, saturation, value, r, g, b);
    GL::ClearColor(r, g, b, 1.0f);
}

namespace
{
    struct vec2
    {
        float x = 0;
        float y = 0;
    };

    struct color3
    {
        float r = 0;
        float g = 0;
        float b = 0;
    };

}

void DemoVAO::create_1buffer_struct_of_arrays_style() //left eye
{
    constexpr std::array positions = {
        vec2{ -0.2f, 0.2f },
        vec2{ -0.2f, 0.6f },
        vec2{ -0.6f, 0.6f },
        vec2{ -0.6f, 0.2f }
    };
    constexpr auto       positions_byte_size = static_cast<GLsizeiptr>(sizeof(vec2) * positions.size());
    constexpr std::array colors              = {
        color3{ 1, 1, 1 },
        color3{ 1, 0, 0 },
        color3{ 0, 1, 0 },
        color3{ 0, 0, 1 }
    };
    constexpr auto                    colors_byte_size   = static_cast<GLsizeiptr>(sizeof(color3) * colors.size());
    constexpr auto                    buffer_size        = positions_byte_size + colors_byte_size;
    constexpr std::array<unsigned, 6> indices            = { 0, 1, 2, 2, 3, 0 };
    constexpr const void*             no_data            = nullptr;
    const auto&                       leftEyeVertBuffer  = bufferHandles[0];
    const auto&                       leftEyeIndexBuffer = indexBufferHandles[0];

    GL::BindBuffer(GL_ARRAY_BUFFER, leftEyeVertBuffer);
    GL::BufferData(GL_ARRAY_BUFFER, buffer_size, no_data, GL_STATIC_DRAW);//whole data size
    GL::BufferSubData(GL_ARRAY_BUFFER, 0, positions_byte_size, positions.data()); //sub data size
    GL::BufferSubData(GL_ARRAY_BUFFER, positions_byte_size, colors_byte_size, colors.data());
    GL::BindBuffer(GL_ARRAY_BUFFER, 0);
    
    GL::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, leftEyeIndexBuffer);
    GL::BufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);
    GL::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    const auto layout_description = {
        OpenGL::VertexBuffer{ leftEyeVertBuffer,                      OpenGL::BufferLayout{ { OpenGL::Attribute::Float2 } } },
        OpenGL::VertexBuffer{ leftEyeVertBuffer, OpenGL::BufferLayout{ positions_byte_size, { OpenGL::Attribute::Float3 } } }
    };
    leftEyeModel = OpenGL::CreateVertexArrayObject(layout_description, leftEyeIndexBuffer);

}

namespace
{
    struct Vertex
    {
        vec2   position{};
        color3 color{};
    };

}

void DemoVAO::create_1buffer_array_of_structs_style() //right eye
{
    constexpr std::array vertices = {
        Vertex{ vec2{ 0.6f, 0.2f }, color3{ 1, 0, 0 } },
        Vertex{ vec2{ 0.6f, 0.6f }, color3{ 0, 1, 0 } },
        Vertex{ vec2{ 0.2f, 0.6f }, color3{ 0, 0, 1 } },
        Vertex{ vec2{ 0.2f, 0.2f }, color3{ 1, 1, 1 } }
    };
    constexpr std::array<unsigned short, 6> indices = { 0, 1, 2, 2, 3, 0 };

    const auto& rightEyeVertBuffer  = bufferHandles[1];
    const auto& rightEyeIndexBuffer = indexBufferHandles[1];
    
    GL::BindBuffer(GL_ARRAY_BUFFER, rightEyeVertBuffer);
    GL::BufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);
    GL::BindBuffer(GL_ARRAY_BUFFER, 0);
    
    GL::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, rightEyeIndexBuffer);
    GL::BufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);
    GL::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    const auto layout = OpenGL::VertexBuffer{ rightEyeVertBuffer, OpenGL::BufferLayout{ { OpenGL::Attribute::Float2, OpenGL::Attribute::Float3 } } };
    rightEyeModel     = OpenGL::CreateVertexArrayObject(layout, rightEyeIndexBuffer);

}

void DemoVAO::create_parallel_buffers_style() //mouth //why parallel?
{
    constexpr std::array positions = {
        vec2{  0.6f, -0.6f },
        vec2{  0.6f, -0.2f },
        vec2{ -0.6f, -0.2f },
        vec2{ -0.6f, -0.6f }
    };
    constexpr std::array colors = {
        color3{ 0, 0, 1 },
        color3{ 1, 1, 1 },
        color3{ 1, 0, 0 },
        color3{ 0, 1, 0 }
    };
    constexpr std::array<unsigned char, 6> indices = { 0, 1, 2, 2, 3, 0 };

    const auto& mouthVertBufferPosition = bufferHandles[2];
    const auto& mouthVertBufferColor    = bufferHandles[3];
    const auto& mouthIndexBuffer        = indexBufferHandles[2];
    
    
    GL::BindBuffer(GL_ARRAY_BUFFER, mouthVertBufferPosition);
    GL::BufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(positions[0]), positions.data(), GL_STATIC_DRAW);
    GL::BindBuffer(GL_ARRAY_BUFFER, 0);
    
    
    GL::BindBuffer(GL_ARRAY_BUFFER, mouthVertBufferColor);
    GL::BufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(colors[0]), colors.data(), GL_STATIC_DRAW);
    GL::BindBuffer(GL_ARRAY_BUFFER, 0);
    
    GL::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, mouthIndexBuffer);
    GL::BufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);
    GL::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    const auto layout_description = {
        OpenGL::VertexBuffer{ mouthVertBufferPosition, OpenGL::BufferLayout{ { OpenGL::Attribute::Float2 } } },
        OpenGL::VertexBuffer{    mouthVertBufferColor, OpenGL::BufferLayout{ { OpenGL::Attribute::Float3 } } }
    };
    mouthModel = OpenGL::CreateVertexArrayObject(layout_description, mouthIndexBuffer);

}

================================================
FILE: source/Demo/DemoVAO.hpp
================================================
#pragma once
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "Engine/GameState.hpp"
  #include "OpenGL/Handle.hpp"
  #include "OpenGL/Shader.hpp"
  #include <array>

namespace OpenGL
{
    using BufferHandle      = Handle;
    using VertexArrayHandle = Handle;
}

class DemoVAO : public CS230::GameState
{
public:
    void Load() override;
    void Unload() override;
    void Update(double dt) override;
    void Draw() override;
    void DrawImGui() override;

    gsl::czstring GetName() const override
    {
        return "Demo VOA";
    }

public:
    DemoVAO() = default;
    ~DemoVAO() override;
    DemoVAO(const DemoVAO&)            = delete;
    DemoVAO(DemoVAO&&)                 = delete;
    DemoVAO& operator=(const DemoVAO&) = delete;
    DemoVAO& operator=(DemoVAO&&)      = delete;

private:
    float                               hue        = 218.5f;
    static constexpr float              saturation = 0.578f;
    static constexpr float              value      = 0.929f;
    OpenGL::CompiledShader              simpleShader{};
    std::array<OpenGL::BufferHandle, 4> bufferHandles{};
    std::array<OpenGL::BufferHandle, 3> indexBufferHandles{};
    OpenGL::VertexArrayHandle           leftEyeModel{}, rightEyeModel{}, mouthModel{};

private:
    void calculate_and_set_clear_color() const;
    void create_1buffer_struct_of_arrays_style(); // left eye
    void create_1buffer_array_of_structs_style(); // right eye
    void create_parallel_buffers_style();         // mouth
};

================================================
FILE: source/Demo/DemoSceneShowcase/Map.cpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "Map.h"
  #include <numbers>

#include "Engine/GameStateManager.hpp"
#include "Engine/TextureManager.hpp"

#include "Game/Particles.h"

Map::Map(Math::ivec2 tileSize, Math::ivec2 tileAmount, Samurai* samurai_ptr)
    : tile_size(tileSize), tile_amount(tileAmount), samurai(samurai_ptr)
{
    for (int i = 0; i < tile_amount.x; ++i)
    {
        for (int j = 0; j < tile_amount.y; ++j)
        {
            grid_info[{ i, j }].first = false;
        }
    }
}

void Map::Update([[maybe_unused]] double dt)
{
    const Math::vec2 samurai_position = samurai->GetPosition() /*+ static_cast<Math::vec2>(samurai->GetGOComponent<CS230::Sprite>()->GetHotSpot(1))*/;
    Math::vec2         grid_pos{};
    for (int i = 0; i < tile_amount.x; ++i)
    {
        for (int j = 0; j < tile_amount.y; ++j)
        {
            if ((samurai_position.x >= i * tile_size.x && samurai_position.x <= (i + 1) * tile_size.x) && (samurai_position.y >= j * tile_size.y && samurai_position.y <= (j + 1) * tile_size.y))
            {
                grid_pos                  = Math::vec2{ static_cast<double>(i * tile_size.x), static_cast<double>(j * tile_size.y) } + Math::vec2{ tile_size.x / 2.0, tile_size.y / 2.0 };
                grid_info[{ i, j }].first = true;
                grid_info[{ i, j }].second += dt;
            }
            else
            {
                grid_info[{ i, j }].first = false;
                grid_info[{ i, j }].second += dt;
            }
        }
    }
}

void Map::Draw(float depth)
{
    CS200::RGBA            tile_color;
    CS200::IRenderer2D* renderer_ptr = Engine::GetTextureManager().GetRenderer2D();
    Math::vec2            grid_pos{};
    const auto            tears_particle = Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::Tears>>();
    const auto            shine_particle = Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::Shining>>();

    for (int i = 0; i < tile_amount.x; ++i)
    {
        for (int j = 0; j < tile_amount.y; ++j)
        {
            grid_pos = Math::vec2{ static_cast<double>(i * tile_size.x), static_cast<double>(j * tile_size.y) } + Math::vec2{ tile_size.x / 2.0, tile_size.y / 2.0 };
            if (grid_info[{ i, j }].first)
            {
                tile_color = CS200::PURPLE;
                if (tears_particle && grid_info[{ i, j }].second >= PARTICLE_TIME)
                {
                    tears_particle->Emit(5, grid_pos + Math::to_vec2(tile_size) * 0.5, { 0, 0 }, { -100, -100 }, std::numbers::pi);
                    grid_info[{ i, j }].second = 0.0;
                }
            }
            else
            {
                tile_color = CS200::BLACK;
                if (shine_particle && grid_info[{ i, j }].second >= PARTICLE_TIME)
                {
                    shine_particle->Emit(5, grid_pos + Math::to_vec2(tile_size) * 0.5, { 0, 0 }, { -100, -100 }, std::numbers::pi);
                    grid_info[{ i, j }].second = 0.0;
                }
            }
            renderer_ptr->DrawRectangle(Math::TranslationMatrix(grid_pos) * Math::ScaleMatrix(tile_size), tile_color, CS200::WHITE, 2.0, depth);
        }
    }

}

================================================
FILE: source/Demo/DemoSceneShowcase/Map.h
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once
  #include <map>
  #include "Engine/Component.h"
  #include "Engine/Vec2.hpp"
  #include "Engine/Timer.hpp"

#include "Demo/DemoSceneShowcase/Samurai.h"

class Map : public CS230::Component
{
public:
    Map(Math::ivec2 tileSize,Math::ivec2 tileAmount,Samurai* samurai_ptr);
    void Update(double dt) override;
    void Draw(float depth);

private:
    static constexpr double              PARTICLE_TIME = 2.5;
    const Math::ivec2 tile_size;
    const Math::ivec2 tile_amount;
    std::map<std::pair<int, int>, std::pair<bool, double>> grid_info; //<x,y> , <on_player,time>
    Samurai* samurai;
};

================================================
FILE: source/Demo/DemoSceneShowcase/Samurai.cpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#include "Samurai.h"
#include "Engine/Input.hpp"

Samurai::Samurai() : 
    GameObject({100,100})
{
    AddGOComponent(new CS230::Sprite("Assets/sprites/DemoSceneShowcase/Samurai.spt", this));
    AddGOComponent(new CS230::ShowCollision());
    GetGOComponent<CS230::Sprite>()->PlayAnimation(0);
    SetRotation(30.0);
}

void Samurai::Update([[maybe_unused]] double dt)
{
    GameObject::Update(dt);
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right))
    {
        SetVelocity({ velocity.x, GetVelocity().y });
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left))
    {
        SetVelocity({ -velocity.x, GetVelocity().y });
    }
    else
    {
        SetVelocity({ 0, GetVelocity().y });
    }

    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Up))
    {
        SetVelocity({ GetVelocity().x, velocity.y });
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Down))
    {
        SetVelocity({ GetVelocity().x, -velocity.y });
    }
    else
    {
        SetVelocity({ GetVelocity().x, 0 });
    }
    
    if(Engine::GetInput().KeyDown(CS230::Input::Keys::A))
    {
        UpdateRotation(ROTATIONSPEED * dt);
    }
    if(Engine::GetInput().KeyDown(CS230::Input::Keys::D))
    {
        UpdateRotation(-ROTATIONSPEED * dt);
    }

}

void Samurai::Draw(Math::TransformationMatrix camera_matrix, unsigned int color, float depth)
{
    GameObject::Draw(camera_matrix * Math::ScaleMatrix(1.0), color, depth);
}

================================================
FILE: source/Demo/DemoSceneShowcase/Samurai.h
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once
  #include "Engine/GameObject.h"
  #include "Engine/Matrix.hpp"

class Samurai : public CS230::GameObject
{
public:
    Samurai();

    GameObjectTypes Type() override
    {
        return GameObjectTypes::Samurai;
    }
    
    std::string TypeName() override
    {
        return "Samurai";
    }
    
    bool CanCollideWith([[maybe_unused]] GameObjectTypes other_object_type) override
    {
        return true;
    };
    
    void ResolveCollision([[maybe_unused]] GameObject* other_object) override { };
    void Update(double dt) override;
    void Draw(Math::TransformationMatrix camera_matrix, unsigned int color, float depth) override;

private:
    Math::vec2 velocity = { 100.0, 100.0 };
    static constexpr double ROTATIONSPEED = 5;
};

================================================
FILE: source/Demo/DemoSceneShowcase/SceneState.cpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "SceneState.hpp"
  #include <imgui.h>
  #include "Engine/Collision.h"
  #include "Engine/Input.hpp"
  #include "Engine/TextureManager.hpp"
  #include "Engine/Window.hpp"
  #include "Engine/Timer.hpp"

#include "CS200/IRenderer2D.hpp"
#include "CS200/NDC.hpp"
#include "CS200/RenderingAPI.hpp"
#include "CS200/ImguiHelper.hpp"

#include "OpenGL/Environment.hpp"

#include "Game/CS230_Final/Components/Grid.h"
#include "Game/MainMenu.h"
#include "Game/Particles.h"

#include "Demo/DemoSceneShowcase/Map.h"
#include "Demo/DemoSceneShowcase/Samurai.h"

void SceneState::Load()
{
    Engine::GetTextureManager().SwitchRenderer(CS230::TextureManager::RendererType::Batch);

#ifdef DEVELOPER_VERSION
    AddGSComponent(new CS230::ShowCollision());
    //AddGSComponent(new Grid());
#endif

    if (!OpenGL::IsWebGL)
    {
        Engine::GetWindow().ForceResize(TILESIZE.x * TILEAMOUNT.x, TILESIZE.y * TILEAMOUNT.y);
        Engine::GetWindow().SetWindowPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    }
    AddGSComponent(new CS230::GameObjectManager);
    AddGSComponent(new CS230::ParticleManager<Particles::Shining>());
    AddGSComponent(new CS230::ParticleManager<Particles::Tears>());
    
    samurai = new Samurai();
    GetGSComponent<CS230::GameObjectManager>()->Add(samurai);
    AddGSComponent(new Map(TILESIZE, TILEAMOUNT, samurai));
    
    // Initialize FPS tracking
    LastTicks = SDL_GetTicks();
    
    CS200::RenderingAPI::SetClearColor(0xFFFFFFFF);

}

void SceneState::Update([[maybe_unused]] double dt)
{
    UpdateGSComponents(dt);
    GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);

    // Update FPS tracker
    const Uint32 currentTicks = SDL_GetTicks();
    const Uint32 deltaTicks      = currentTicks - LastTicks;
    const double deltaSeconds = deltaTicks / 1000.0;
    LastTicks                  = currentTicks;
    FPSTracker.Update(deltaSeconds);
    
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape))
    {
        Engine::GetGameStateManager().PopState();
        Engine::GetGameStateManager().PushState<MainMenu>();
    }

}

void SceneState::Unload()
{
    GetGSComponent<CS230::GameObjectManager>()->Unload();
    ClearGSComponents();
}

void SceneState::Draw()
{
    CS200::RenderingAPI::Clear();
    CS200::IRenderer2D* renderer_2d = Engine::GetTextureManager().GetRenderer2D();
    renderer_2d->BeginScene(CS200::build_ndc_matrix(Engine::GetWindow().GetSize()));
    GetGSComponent<Map>()->Draw(0.8f);
#ifdef DEVELOPER_VERSION
    //GetGSComponent<Grid>()->Draw(Grid::DotColor::black,0.2f);
#endif
    GetGSComponent<CS230::GameObjectManager>()->DrawAll(Math::TransformationMatrix());

    renderer_2d->EndScene();
    current_draw_call = renderer_2d->GetDrawCallCounter();
    current_draw_texture_call = renderer_2d->GetDrawTextureCounter();

}

void SceneState::DrawImGui()
{

    ImGui::Begin("Demo Settings");
    
    // Display FPS at the top
    ImGui::Text("FPS: %d", static_cast<int>(FPSTracker));
    ImGui::Separator();
    
    ImGui::Text("Draw Call Counter: %d", static_cast<int>(current_draw_call));
    ImGui::Text("Draw Texture Call Counter: %d", static_cast<int>(current_draw_texture_call));
    ImGui::Separator();
    
    // VSync toggle
    if (ImGui::Checkbox("VSync", &VSyncEnabled))
    {
        // https://wiki.libsdl.org/SDL_GL_SetSwapInterval
        constexpr int ADAPTIVE_VSYNC = -1;
        constexpr int VSYNC             = 1;
        constexpr int NO_VSYNC         = 0;
    
        if (VSyncEnabled)
        {
            // Try adaptive vsync first, fall back to regular vsync
            if (const auto result = SDL_GL_SetSwapInterval(ADAPTIVE_VSYNC); result != 0)
            {
                SDL_GL_SetSwapInterval(VSYNC);
            }
        }
        else
        {
            SDL_GL_SetSwapInterval(NO_VSYNC);
        }
    }
    ImGui::Separator();
    
    // Renderer selection
    auto&       texture_manager         = Engine::GetTextureManager();
    const auto current_renderer_type = texture_manager.GetCurrentRendererType();
    // const auto renderer_2d = texture_manager.GetRenderer2D();
    ImGui::Text("Renderer:");
    
    if (ImGui::RadioButton("Batch", current_renderer_type == CS230::TextureManager::RendererType::Batch))
    {
        texture_manager.SwitchRenderer(CS230::TextureManager::RendererType::Batch);
    }
    
    ImGui::SameLine();
    if (ImGui::RadioButton("Instanced", current_renderer_type == CS230::TextureManager::RendererType::Instanced))
    {
        texture_manager.SwitchRenderer(CS230::TextureManager::RendererType::Instanced);
    }
    ImGui::Separator();
    
    ImGui::End();

}

================================================
FILE: source/Demo/DemoSceneShowcase/SceneState.hpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once
  #include <SDL.h>

#include "Engine/GameState.hpp"
#include "Engine/GameObjectManager.h"
#include "Engine/Particle.h"
#include "Engine/Vec2.hpp"
#include "Engine/FPS.hpp"

#include "Game/Particles.h"

#include "Demo/DemoSceneShowcase/Samurai.h"

class SceneState : public CS230::GameState
{
public:
    SceneState() = default;
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;
    void DrawImGui() override;

    gsl::czstring GetName() const override
    {
        return "Demo Scene state";
    }

private:
    Samurai* samurai = nullptr;
    static constexpr Math::ivec2 TILESIZE = { 96, 96 };
    static constexpr Math::ivec2 TILEAMOUNT  = { 8, 8 };

    util::FPS FPSTracker;
    Uint32      LastTicks = 0;
    bool      VSyncEnabled = true;
    
    size_t current_draw_call = 0;
    size_t current_draw_texture_call = 0;

};

================================================
FILE: source/Engine/Animation.cpp
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Animation.cpp
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    April 16, 2025
*/
#include "Animation.h"
#include "Logger.hpp"
#include "Path.hpp"

CS230::Animation::Animation(const std::filesystem::path& animation_file) : current_command(0)
{
    const std::filesystem::path anm_path = assets::locate_asset(animation_file);

    if (anm_path.extension() != ".anm")
    {
        throw std::runtime_error(animation_file.generic_string() + " is not a .anm file");
    }
    
    
    std::ifstream in_file(anm_path);
    if (in_file.is_open() == false)
    {
        throw std::runtime_error("Failed to load " + animation_file.generic_string());
    }
    
    std::string command;
    while (in_file.eof() == false)
    {
        in_file >> command;
        if (command == "PlayFrame")
        {
            size_t frame;
            float  target_time;
            in_file >> frame;
            in_file >> target_time;
    
            commands.push_back(new PlayFrame(frame, static_cast<double>(target_time)));
        }
        else if (command == "Loop")
        {
            size_t loop_to_frame;
            in_file >> loop_to_frame;
            commands.push_back(new Loop(loop_to_frame));
        }
        else if (command == "End")
        {
            commands.push_back(new End());
        }
        else
        {
            Engine::GetLogger().LogError(command + " in " + animation_file.generic_string());
        }
    }
    Reset();

}

CS230::Animation::Animation() : Animation("./Assets/animations/None.anm")
{
}

CS230::Animation::~Animation()
{
    for (Command* command : commands)
    {
        delete command;
    }
    commands.clear();
}

void CS230::Animation::Update(double dt)
{
    current_frame->Update(dt);
    if (current_frame->Ended() == true)
    {
        current_frame->ResetTime();
        current_command++;
        if (commands[current_command]->Type() == CommandType::PlayFrame)
        {
            current_frame = static_cast<PlayFrame*>(commands[current_command]);
        }
        else if (commands[current_command]->Type() == CommandType::Loop)
        {
            Loop* loop_data = static_cast<Loop*>(commands[current_command]);
            current_command = loop_data->LoopIndex();
            if (commands[current_command]->Type() == CommandType::PlayFrame)
            {
                current_frame = static_cast<PlayFrame*>(commands[current_command]);
            }
            else
            {
                Engine::GetLogger().LogError("Loop does not go to PlayFrame");
                Reset();
            }
        }
        else if (commands[current_command]->Type() == CommandType::End)
        {
            ended = true;
        }
    }
}

size_t CS230::Animation::CurrentFrame()
{
    return current_frame->Frame();
}

void CS230::Animation::Reset()
{
    current_command = 0;
    ended           = false;
    current_frame   = static_cast<PlayFrame*>(commands[current_command]);
    current_frame->ResetTime();
}

bool CS230::Animation::Ended()
{
    return ended;
}

CS230::Animation::PlayFrame::PlayFrame(size_t _frame, double duration) : frame(_frame), target_time(duration), timer(0.0)
{
}

void CS230::Animation::PlayFrame::Update(double dt)
{
    timer += dt;
}

bool CS230::Animation::PlayFrame::Ended()
{
    if (timer >= target_time)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CS230::Animation::PlayFrame::ResetTime()
{
    timer = 0.0;
}

size_t CS230::Animation::PlayFrame::Frame()
{
    return frame;
}

CS230::Animation::Loop::Loop(size_t _loop_index) : loop_index(_loop_index)
{
}

size_t CS230::Animation::Loop::LoopIndex()
{
    return loop_index;
}

================================================
FILE: source/Engine/Animation.h
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Animation.h
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    April 16, 2025
*/

#pragma once
#include <vector>
#include <filesystem>
#include "Engine.hpp"

namespace CS230 {
    class Animation {
    public:
        Animation();
        Animation(const std::filesystem::path& animation_file);
        ~Animation();

        void Update(double dt);
        size_t CurrentFrame();
        void Reset();
        bool Ended();
    private:
        enum class CommandType {
            PlayFrame,
            Loop,
            End,
        };
        class Command {
        public:
            virtual ~Command() {}
            virtual CommandType Type() = 0;
        };
    
    
        class End : public Command {
        public:
            virtual CommandType Type() override { return CommandType::End; }
        private:
        };
    
    
        class Loop : public Command {
        public:
            Loop(size_t loop_index);
            virtual CommandType Type() override { return CommandType::Loop; }
            size_t LoopIndex();
        private:
            size_t loop_index;
        };
    
        class PlayFrame : public Command {
        public:
            PlayFrame(size_t frame, double duration);
            virtual CommandType Type() override { return CommandType::PlayFrame; }
            void Update(double dt);
            bool Ended();
            void ResetTime();
            size_t Frame();
        private:
            size_t frame;
            double target_time;
            double timer;
        };
    
        size_t current_command;
        std::vector<Command*> commands;
        bool ended;
        PlayFrame* current_frame;
    };

}

================================================
FILE: source/Engine/Camera.cpp
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Camera.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/
#include "Camera.h"
#include "Engine.hpp"
#include "Matrix.hpp"

CS230::Camera::Camera(Math::rect _player_zone) :  position(Math::vec2{0.0,0.0}),rotation(0.0), scale(Math::vec2{1.0,1.0}), player_zone(_player_zone)  {}

bool& CS230::Camera::SetFirstPersonView()
{
    return first_person_view;
}

bool& CS230::Camera::SetAnchoring()
{
    return anchoring;
}

void CS230::Camera::SetPosition(Math::vec2 new_position){
    position = new_position;
    is_position_outdated = true;
}

void CS230::Camera::SetRotation(double new_rotation)
{
    if(first_person_view)
    {
        rotation = new_rotation;
        is_rotation_outdated = true;
    }
}

void CS230::Camera::SetScale(Math::vec2 new_scale)
{
    if(first_person_view)
    {
        scale = new_scale;
        is_scale_outdated = true;
    }
}

const Math::vec2& CS230::Camera::GetPosition() const { return position; }

void CS230::Camera::SetLimit(Math::irect new_limit){
    limit = new_limit;
}

void CS230::Camera::Update(const Math::vec2& player_position){
    if(anchoring)
    {
        SetPosition(player_position);
        return;
    }
    // SetPosition(player_position); // always center on player
    if (player_position.x > player_zone.Right() + position.x) {
        position.x = player_position.x - player_zone.Right();
        is_position_outdated = true;
    }
    if (player_position.x - position.x < player_zone.Left()) {
        position.x = player_position.x - player_zone.Left();
        is_position_outdated = true;
    }

    if (player_position.y > player_zone.Top() + position.y) {
        position.y = player_position.y - player_zone.Top();
        is_position_outdated = true;
    }
    if (player_position.y - position.y < player_zone.Bottom()) {
        position.y = player_position.y - player_zone.Bottom();
        is_position_outdated = true;
    }
    
    
    if (position.x < limit.Left()) {
        position.x = limit.Left();
        is_position_outdated = true;
    }
    if (position.x > limit.Right()) {
        position.x = limit.Right();
        is_position_outdated = true;
    }
    if (position.y < limit.Bottom()) {
        position.y = limit.Bottom();
        is_position_outdated = true;
    }
    if (position.y > limit.Top()) {
        position.y = limit.Top();
        is_position_outdated = true;
    }

}

Math::TransformationMatrix CS230::Camera::GetMatrix() {
    if(first_person_view){
        if(is_position_outdated || is_rotation_outdated || is_scale_outdated){
            camera_matrix = Math::TranslationMatrix(position) * Math::RotationMatrix(rotation) * Math::ScaleMatrix(scale);
            view_matrix = camera_matrix;
            std::swap(view_matrix[0][1], view_matrix[1][0]);
            view_matrix[0][2] = -(camera_matrix[0][0] * camera_matrix[0][2] + camera_matrix[1][0] * camera_matrix[1][2]);
            view_matrix[1][2] = -(camera_matrix[0][1] * camera_matrix[0][2] + camera_matrix[1][1] * camera_matrix[1][2]);
            is_position_outdated = false;
            is_rotation_outdated = false;
            is_scale_outdated = false;

        }
    }
    else
    {
        if(is_position_outdated){
            camera_matrix = Math::TranslationMatrix(position) ;
            view_matrix = camera_matrix;
            view_matrix[0][2] = -(camera_matrix[0][0] * camera_matrix[0][2] + camera_matrix[1][0] * camera_matrix[1][2]);
            view_matrix[1][2] = -(camera_matrix[0][1] * camera_matrix[0][2] + camera_matrix[1][1] * camera_matrix[1][2]);
            is_position_outdated = false;
        }
    }
    return view_matrix;

}

================================================
FILE: source/Engine/Camera.h
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Camera.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once

#include "Component.h"
#include "Matrix.hpp"
#include "Rect.hpp"
#include "Vec2.hpp"

namespace CS230
{
    class Camera : public Component
    {
    public:
        Camera(Math::rect player_zone);
        bool&              SetFirstPersonView();
        bool&              SetAnchoring();
        void              SetPosition(Math::vec2 new_position);
        void              SetRotation(double new_rotation);
        void              SetScale(Math::vec2 new_scale);
        const Math::vec2& GetPosition() const;
        void              SetLimit(Math::irect new_limit);
        using Component::Update; // say i'll use this version too, so don't hide anymore
        void                       Update(const Math::vec2& player_position);
        Math::TransformationMatrix GetMatrix();

    private:
        Math::irect                   limit;
        bool                       first_person_view{ true };
        bool                       anchoring{ true };
        Math::vec2                   position;
        bool                       is_position_outdated{ true };
        double                       rotation;
        bool                       is_rotation_outdated{ true };
        Math::vec2                   scale;
        bool                       is_scale_outdated{ true };
        Math::rect                   player_zone;
        Math::TransformationMatrix camera_matrix{};
        Math::TransformationMatrix view_matrix{};
    };

}

================================================
FILE: source/Engine/Collision.cpp
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Component.cpp
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    May 17, 2025
*/

#include "Collision.h"
#include "../CS200/IRenderer2D.hpp"
#include "../CS200/RGBA.hpp"
#include "Engine.hpp"
#include "Logger.hpp"
#include "TextureManager.hpp"

namespace CS230
{
    RectCollision::RectCollision(Math::irect _boundary, CS230::GameObject* _object) : boundary(_boundary), object(_object)
    {
    }

    void RectCollision::Draw(Math::TransformationMatrix display_matrix, float depth)
    {
        /*const double render_height = rlGetFramebufferHeight();
    
        bottom_left.y = bottom_left.y * -1 + render_height;
        bottom_right.y = bottom_right.y * -1 + render_height;
        top_left.y = top_left.y * -1 + render_height;
        top_right.y = top_right.y * -1 + render_height;
    
    
        DrawLine(int(top_left.x), int(top_left.y), int(top_right.x), int(top_right.y), WHITE);
        DrawLine(int(bottom_right.x), int(bottom_right.y), int(top_right.x), int(top_right.y), WHITE);
        DrawLine(int(bottom_right.x), int(bottom_right.y), int(bottom_left.x), int(bottom_left.y), WHITE);
        DrawLine(int(top_left.x), int(top_left.y), int(bottom_left.x), int(bottom_left.y), WHITE);*/
        auto& texture_manager = Engine::GetTextureManager();
        //texture_manager.SwitchRenderer(CS230::TextureManager::RendererType::Immediate);
        Math::rect world_boundary = WorldBoundary();
        auto       renderer2d      = texture_manager.GetRenderer2D();
    
        // [[maybe_unused]] Math::vec2 bottom_left  = /*display_matrix * */ Math::vec2{ world_boundary.Left(), world_boundary.Bottom() };
        // [[maybe_unused]] Math::vec2 bottom_right = /*display_matrix * */ Math::vec2{ world_boundary.Right(), world_boundary.Bottom() };
        // [[maybe_unused]] Math::vec2 top_left     = /*display_matrix * */ Math::vec2{ world_boundary.Left(), world_boundary.Top() };
        // [[maybe_unused]] Math::vec2 top_right    = /*display_matrix * */ Math::vec2{ world_boundary.Right(), world_boundary.Top() };
    
        // const auto center_matrix = display_matrix * Math::TranslationMatrix(world_boundary.Center());
    
        renderer2d->DrawRectangle(display_matrix*Math::TranslationMatrix(world_boundary.Center())*Math::ScaleMatrix(world_boundary.Size()), CS200::CLEAR, CS200::BLACK, line_width,depth);
    }
    
    Math::rect RectCollision::WorldBoundary()
    {
        return { object->GetMatrix() * static_cast<Math::vec2>(boundary.point_1), object->GetMatrix() * static_cast<Math::vec2>(boundary.point_2) };
    }
    
    bool RectCollision::IsCollidingWith(GameObject* other_object)
    {
        Collision* other_collider = other_object->GetGOComponent<Collision>();
    
    
        if (other_collider == nullptr)
        {
            // Engine::GetLogger().LogError("No collision component found");
            return false;
        }
    
    
        if (other_collider->Shape() != CollisionShape::Rect)
        {
            Engine::GetLogger().LogError("Rect vs unsupported type");
            return false;
        }
    
        Math::rect rectangle_1 = WorldBoundary();
        Math::rect rectangle_2 = dynamic_cast<RectCollision*>(other_collider)->WorldBoundary();
    
        if (!((rectangle_1.Right() <= rectangle_2.Left()) || (rectangle_1.Left() >= rectangle_2.Right()) || (rectangle_1.Top() <= rectangle_2.Bottom()) || (rectangle_1.Bottom() >= rectangle_2.Top())))
        {
            return true;
        }
        return false;
    }
    
    bool RectCollision::IsCollidingWith(Math::vec2 point)
    {
        Math::rect rectangle = WorldBoundary();
        if (!((rectangle.Left() > point.x) || (rectangle.Right() < point.x) || (rectangle.Top() < point.y) || (rectangle.Bottom() > point.y)))
        {
            return true;
        }
        return false;
    }
    
    CircleCollision::CircleCollision(double _radius, GameObject* _object) :  object(_object), radius(_radius)
    {
    }
    
    void CircleCollision::Draw(Math::TransformationMatrix display_matrix,float depth)
    {
        // const double render_height = rlGetFramebufferHeight();
        // Math::vec2 transformed_position = display_matrix * object->GetPosition();
        // transformed_position.y = transformed_position.y * -1 + render_height;
        // const int num_segments = 36;
        // Math::vec2 previous_vertex;
        // for (int i = 0; i <= num_segments + 1; i++) {
        //     double theta = 2.0 * PI * static_cast<double>(i) / static_cast<double>(num_segments);
        //     Math::vec2 vertex = {
        //         transformed_position.x + GetRadius() * std::cos(theta),
        //         transformed_position.y + GetRadius() * std::sin(theta)
        //     };
        //     if (i > 0) {
        //         DrawLine(int(vertex.x), int(vertex.y), int(previous_vertex.x), int(previous_vertex.y), WHITE);
        //     }
        //     previous_vertex = vertex;
        // }
        auto& texture_manager = Engine::GetTextureManager();
        //texture_manager.SwitchRenderer(CS230::TextureManager::RendererType::Immediate);
        const auto transform = display_matrix * Math::TranslationMatrix(object->GetPosition()) * Math::ScaleMatrix(2 * GetRadius());
        auto       renderer2d = texture_manager.GetRenderer2D();
        renderer2d->DrawCircle(transform, CS200::CLEAR, CS200::BLACK, line_width, depth);
    }
    
    double CircleCollision::GetRadius()
    {
        return std::min(object->GetScale().x, object->GetScale().x) * radius;
    }
    
    bool CircleCollision::IsCollidingWith(GameObject* other_object)
    {
        Collision* other_collider = other_object->GetGOComponent<Collision>();
    
    
        if (other_collider == nullptr)
        {
            // Engine::GetLogger().LogError("No collision component found");
            return false;
        }
    
    
        if (other_collider->Shape() != CollisionShape::Circle)
        {
            Engine::GetLogger().LogError("Circle vs unsupported type");
            return false;
        }
        double     _radius        = GetRadius();
        Math::vec2 position       = object->GetPosition();
        double     other_radius   = dynamic_cast<CircleCollision*>(other_collider)->GetRadius();
        Math::vec2 other_position = other_object->GetPosition();
    
        if (((position.x - other_position.x) * (position.x - other_position.x) + (position.y - other_position.y) * (position.y - other_position.y)) <
            ((_radius + other_radius) * (_radius + other_radius)))
        {
            return true;
        }
        return false;
    }
    
    bool CircleCollision::IsCollidingWith(Math::vec2 point)
    {
        double     _radius  = GetRadius();
        Math::vec2 position = object->GetPosition();
    
        if (((position.x - point.x) * (position.x - point.x) + (position.y - point.y) * (position.y - point.y)) < (_radius * _radius))
        {
            return true;
        }
        return false;
    }

}

================================================
FILE: source/Engine/Collision.h
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Collision.h
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    May 18, 2025
*/
#pragma once
#include "Component.h"
#include "Rect.hpp"
#include "GameObject.h"
#include "Matrix.hpp"

namespace Math {
    class TransformationMatrix;
}

namespace CS230 {
    class GameObject;

    class Collision : public Component {
    public:
        enum class CollisionShape {
            Rect,
            Circle
        };
        virtual CollisionShape Shape() = 0;
        virtual void Draw(Math::TransformationMatrix display_matrix,float depth = 0.f) = 0;
        virtual bool IsCollidingWith(GameObject* other_object) = 0;
        virtual bool IsCollidingWith(Math::vec2 point) = 0;
    };
    
    class RectCollision : public Collision {
    public:
        RectCollision(Math::irect _boundary, GameObject* _object);
        CollisionShape Shape() override {
            return CollisionShape::Rect;
        }
        void Draw(Math::TransformationMatrix display_matrix, float depth) override;
        Math::rect WorldBoundary();
        bool IsCollidingWith(GameObject* other_object) override;
        bool IsCollidingWith(Math::vec2 point) override;
    private:
        Math::irect boundary;
        GameObject* object;
    
        static constexpr double line_width = 2.0;
    };
    
    class CircleCollision : public Collision {
    public:
        CircleCollision(double radius, GameObject* object);
        CollisionShape Shape() override {
            return CollisionShape::Circle;
        }
    
        void Draw(Math::TransformationMatrix display_matrix,float depth) override;
        double GetRadius();
        bool IsCollidingWith(GameObject* other_object) override;
        bool IsCollidingWith(Math::vec2 point) override;
    private:
        GameObject* object;
        double radius;
        static constexpr double line_width = 5.0;
    };

}

================================================
FILE: source/Engine/Component.h
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Component.h
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    May 17, 2025
*/
#pragma once

namespace CS230 {
    class Component {
    public:
        virtual ~Component() {};
        virtual void Update([[maybe_unused]] double dt) {};
    };
}

================================================
FILE: source/Engine/ComponentManager.h
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  ComponentManager.h
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    May 17, 2025
*/
#pragma once
#include <algorithm>
#include <vector>
#include <stdexcept>

#include "Component.h"

namespace CS230
{
    class ComponentManager
    {
    public:
        ~ComponentManager()
        {
            Clear();
        }

        void UpdateAll(double dt)
        {
            for (Component* component : components)
            {
                component->Update(dt);
            }
        }
    
        void AddComponent(Component* component)
        {
            components.push_back(component);
        }
    
        template <typename T>
        T* GetComponent()
        {
            for (Component* component : components)
            {
                T* ptr = dynamic_cast<T*>(component);
                if (ptr != nullptr)
                {
                    return ptr;
                }
            }
            return nullptr;
        }
    
        template <typename T>
        void RemoveComponent()
        {
            auto it = std::find_if(components.begin(), components.end(), [](Component* element) { return (dynamic_cast<T*>(element) != nullptr); });
            delete *it;
            components.erase(it);
        }
    
        void Clear()
        {
            for (Component* component : components)
            {
                delete component;
            }
            components.clear();
        }
    
    private:
        std::vector<Component*> components;
    };

}

================================================
FILE: source/Engine/Engine.cpp
================================================
/**

* \file
* \author Rudy Castan
* \author Jonathan Holmes
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "Engine.hpp"
  #include "CS200/ImGuiHelper.hpp"
  #include "CS200/ImmediateRenderer2D.hpp"
  #include "CS200/NDC.hpp"
  #include "CS200/RenderingAPI.hpp"
  #include "FPS.hpp"
  #include "Font.hpp"
  #include "GameState.hpp"
  #include "GameStateManager.hpp"
  #include "Input.hpp"
  #include "Logger.hpp"
  #include "TextManager.hpp"
  #include "TextureManager.hpp"
  #include "Timer.hpp"
  #include "Window.hpp"

#include <chrono>

// Pimpl implementation class
class Engine::Impl
{
public:
    Impl()
        :
#ifdef DEVELOPER_VERSION
          logger(CS230::Logger::Severity::Debug, true, std::chrono::system_clock::now())
#else
          logger(CS230::Logger::Severity::Debug, true, std::chrono::system_clock::now())
#endif
          ,
          window{}, input{}
    {
    }

    CS230::Logger            logger;
    CS230::Window            window{};
    CS230::Input            input{};
    ImGuiHelper::Viewport    viewport{};
    util::FPS                fps{};
    util::Timer                timer{};
    WindowEnvironment        environment{};
    CS230::GameStateManager gameStateManager{};
    // CS200::IRenderer2D*        renderer2D = nullptr;
    CS230::TextureManager    textureManager{};
    TextManager                textManager{};

};

Engine& Engine::Instance()
{
    static Engine instance;
    return instance;
}

CS230::Logger& Engine::GetLogger()
{
    return Instance().impl->logger;
}

CS230::Window& Engine::GetWindow()
{
    return Instance().impl->window;
}

CS230::Input& Engine::GetInput()
{
    return Instance().impl->input;
}

const WindowEnvironment& Engine::GetWindowEnvironment()
{
    return Instance().impl->environment;
}

CS230::GameStateManager& Engine::GetGameStateManager()
{
    return Instance().impl->gameStateManager;
}

// CS200::IRenderer2D& Engine::GetRenderer2D()
// {
//     return Instance().impl->renderer2D;
// }

CS230::TextureManager& Engine::GetTextureManager()
{
    return Instance().impl->textureManager;
}

TextManager& Engine::GetTextManager()
{
    return Instance().impl->textManager;
}

void Engine::Start(std::string_view window_title)
{
    impl->logger.LogEvent("Engine Started");
#if defined(DEVELOPER_VERSION)
    impl->logger.LogEvent("Developer Build");
#endif
    impl->window.Start(window_title);
    auto& window = impl->window;

    const auto window_size = window.GetSize();
    impl->viewport           = { 0, 0, window_size.x, window_size.y };
    CS200::RenderingAPI::SetViewport(window_size);
    impl->environment.DisplaySize = { static_cast<double>(window_size.x), static_cast<double>(window_size.y) };
    ImGuiHelper::Initialize(window.GetSDLWindow(), window.GetGLContext());
    window.SetEventCallback(ImGuiHelper::FeedEvent);
    impl->textureManager.Init();
    // impl->renderer2D.Init();
    impl->timer.ResetTimeStamp();
    impl->textManager.Init();

}

void Engine::Stop()
{
    impl->textureManager.Shutdown();
    // impl->renderer2D.Shutdown();
    impl->gameStateManager.Clear();
    ImGuiHelper::Shutdown();
    impl->logger.LogEvent("Engine Stopped");
}

void Engine::Update()
{
    updateEnvironment();

    // service update
    auto& environment = impl->environment;
    impl->window.Update();
    impl->input.Update();
    
    auto& state_manager = impl->gameStateManager;
    state_manager.Update(environment.DeltaTime);
    const auto          viewport        = impl->viewport;
    const Math::ivec2 viewport_size = { viewport.width, viewport.height };
    CS200::RenderingAPI::SetViewport(viewport_size, { viewport.x, viewport.y });
    state_manager.Draw();
    impl->viewport = ImGuiHelper::Begin();
    state_manager.DrawImGui();
    ImGuiHelper::End();

}

bool Engine::HasGameEnded()
{
    return impl->window.IsClosed() || impl->gameStateManager.HasGameEnded();
}

Engine::Engine() : impl(new Impl())
{
}

Engine::~Engine()
{
    delete impl;
}

void Engine::updateEnvironment()
{
    auto& environment      = impl->environment;
    environment.DeltaTime = impl->timer.GetElapsedSeconds();
    impl->timer.ResetTimeStamp();
    environment.ElapsedTime += environment.DeltaTime;
    ++environment.FrameCount;
    impl->fps.Update(environment.DeltaTime);
    environment.FPS                  = impl->fps;
    const auto viewport              = impl->viewport;
    impl->environment.DisplaySize = { static_cast<double>(viewport.width), static_cast<double>(viewport.height) };
}

================================================
FILE: source/Engine/Engine.hpp
================================================
/**

* \file
* \author Rudy Castan
* \author Jonathan Holmes
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once

#include "Vec2.hpp"
#include <filesystem>
#include <gsl/gsl>
#include <memory>
#include <string_view>

namespace CS230
{
    class Logger;
    class Window;
    class Input;
    class GameState;
    class GameStateManager;
    class TextureManager;
    class Font;

}

namespace CS200
{
    class IRenderer2D;
}

class TextManager;
class EventBus;
class CombatSystem;

/**

* \brief Runtime information about the window and application state

* 

* WindowEnvironment provides access to essential runtime metrics and window

* properties that are commonly needed by game logic, rendering systems, and

* debugging tools. This information is updated each frame to reflect the

* current state of the application.

* 

* Timing Information:

* - DeltaTime: Time elapsed since the last frame (for frame-rate independent movement)

* - ElapsedTime: Total time since application started (for animations and effects)

* - FrameCount: Total number of frames rendered (for debugging and profiling)

* - FPS: Current frames per second (for performance monitoring)

* 

* Display Information:

* - DisplaySize: Current viewport dimensions in pixels (for coordinate calculations)

* 

* Common use cases:

* - Frame-rate independent animations and movement

* - Performance monitoring and debugging

* - UI scaling based on viewport size

* - Time-based effects and animations
    */
    struct WindowEnvironment
    {
    int        FPS         = 0;   ///< Current frames per second
    uint64_t   FrameCount  = 0;   ///< Total frames rendered since start
    double     DeltaTime   = 0.0; ///< Time in seconds since last frame
    double     ElapsedTime = 0.0; ///< Total time in seconds since application start
    Math::vec2 DisplaySize{};     ///< Current viewport size in pixels
    };

/**

* \brief Central application engine managing all core systems and subsystems

* 

* Engine serves as the main application framework that coordinates all major

* subsystems including windowing, input handling, rendering, game state management,

* and resource management. It implements the singleton pattern to provide global

* access to these systems while maintaining proper initialization order and

* cleanup procedures.

* 

* Architecture and Design:

* - Singleton pattern ensures single engine instance across the application

* - Pimpl idiom hides implementation details and reduces compilation dependencies

* - Static accessor methods provide convenient access to subsystems

* - Manages complete application lifecycle from startup to shutdown

* 

* Core Subsystems:

* - Window: SDL-based window management and OpenGL context creation

* - Input: Keyboard, mouse, and controller input handling

* - Renderer2D: High-level 2D graphics rendering system

* - GameStateManager: State machine for different application screens/modes

* - TextureManager: Resource management for texture assets

* - Logger: Debug and event logging system

* 

* Application Lifecycle:

* 1. Start(): Initialize all subsystems and create window

* 2. Update(): Process one frame of the main loop (input, logic, rendering)

* 3. HasGameEnded(): Check if application should terminate

* 4. Stop(): Clean shutdown of all subsystems

* 

* The engine handles the complex initialization order required by modern

* graphics applications, including OpenGL context creation, ImGui setup,

* and proper resource management throughout the application lifecycle.
  */

class Engine
{
public:
    /**
     * \brief Get the singleton Engine instance
     * \return Reference to the single Engine instance
     *
     * Provides access to the singleton Engine instance, creating it on first
     * access using lazy initialization. This ensures the engine is available
     * throughout the application lifetime while maintaining single-instance
     * semantics.
     *
     * The singleton is implemented with a static local variable, providing
     * thread-safe initialization in C++11 and later, and automatic cleanup
     * when the application terminates.
     */
    static Engine& Instance();

    /**
     * \brief Access the application logging system
     * \return Reference to the Logger instance for debug and event logging
     *
     * Provides access to the centralized logging system for debug output,
     * error reporting, and event tracking. The logger configuration differs
     * between development and release builds, with more verbose output
     * available in development versions.
     *
     * Common uses:
     * - Debug information and variable values
     * - Error reporting and exception details
     * - Performance metrics and timing information
     * - Application lifecycle events
     */
    static CS230::Logger& GetLogger();
    
    /**
     * \brief Access the window management system
     * \return Reference to the Window instance for display and context management
     *
     * Provides access to the window system that manages the application window,
     * OpenGL context, and display properties. This includes window creation,
     * resizing, fullscreen control, and event handling integration.
     *
     * Window capabilities:
     * - Window creation and destruction
     * - OpenGL context management
     * - Display mode and resolution control
     * - Event system integration
     * - Cross-platform window handling
     */
    static CS230::Window& GetWindow();
    
    /**
     * \brief Access the input handling system
     * \return Reference to the Input instance for keyboard, mouse, and controller input
     *
     * Provides access to the unified input system that handles all user input
     * devices including keyboard, mouse, and game controllers. The system
     * provides both immediate state queries and event-based input handling.
     *
     * Input capabilities:
     * - Keyboard state and key press/release events
     * - Mouse position, button states, and scroll wheel
     * - Game controller support with analog and digital inputs
     * - Input mapping and configuration
     * - Frame-coherent input state management
     */
    static CS230::Input& GetInput();
    
    /**
     * \brief Access current window and timing environment information
     * \return Const reference to WindowEnvironment with current frame data
     *
     * Provides read-only access to essential runtime information including
     * timing data, frame statistics, and display properties. This information
     * is updated each frame and is commonly used for frame-rate independent
     * calculations and performance monitoring.
     *
     * Available information:
     * - Delta time for frame-rate independent movement
     * - Total elapsed time for animations and effects
     * - Current FPS for performance monitoring
     * - Frame count for debugging and profiling
     * - Current viewport size for coordinate calculations
     */
    static const WindowEnvironment& GetWindowEnvironment();
    
    /**
     * \brief Access the game state management system
     * \return Reference to GameStateManager for application state control
     *
     * Provides access to the state machine that manages different application
     * modes such as menus, gameplay, pause screens, and loading states. The
     * state manager handles transitions between states and ensures proper
     * initialization and cleanup of state-specific resources.
     *
     * State management features:
     * - State transitions with proper lifecycle management
     * - State stack for overlay states (pause menus, dialogs)
     * - Automatic resource management per state
     * - Event propagation to active states
     * - Clean separation of application logic by state
     */
    static CS230::GameStateManager& GetGameStateManager();
    
    /**
     * \brief Access the 2D rendering system
     * \return Reference to IRenderer2D for all 2D graphics operations
     *
     * Provides access to the high-level 2D rendering system that abstracts
     * OpenGL complexity and provides efficient rendering of 2D graphics
     * primitives. The renderer handles batching, state management, and
     * coordinate system transformations automatically.
     *
     * Rendering capabilities:
     * - Sprite and texture rendering with transformations
     * - Primitive shapes (rectangles, circles, lines)
     * - Text rendering with font support
     * - Efficient batch rendering for performance
     * - Camera and viewport transformations
     * - Blend modes and rendering effects
     */
    // static CS200::IRenderer2D& GetRenderer2D();
    
    /**
     * \brief Access the texture resource management system
     * \return Reference to TextureManager for texture loading and caching
     *
     * Provides access to the texture management system that handles loading,
     * caching, and lifecycle management of texture resources. The manager
     * prevents duplicate loading of textures and ensures efficient GPU
     * memory usage.
     *
     * Texture management features:
     * - Automatic texture loading from various image formats
     * - Reference counting and automatic cleanup
     * - Texture caching to prevent duplicate resources
     * - Efficient GPU memory management
     * - Support for different texture formats and properties
     */
    static CS230::TextureManager& GetTextureManager();
    
    static TextManager& GetTextManager();
    
    static EventBus& GetEventBus();
    
    static CombatSystem& GetCombatSystem();

public:
    /**
     * \brief Initialize and start the engine with all subsystems
     * \param window_title Title to display in the window title bar
     *
     * Performs complete engine initialization including window creation, OpenGL
     * context setup, subsystem initialization, and resource loading. This must
     * be called before any other engine operations and establishes the foundation
     * for all subsequent application functionality.
     *
     * Initialization sequence:
     * - Creates application window with OpenGL context
     * - Initializes OpenGL state and rendering API
     * - Sets up ImGui for debugging and development UI
     * - Initializes 2D renderer and graphics systems
     * - Configures input handling and event processing
     * - Starts timing systems for frame rate calculation
     *
     * The function handles the complex dependencies between subsystems and
     * ensures everything is properly configured before the application begins
     * its main execution loop.
     *
     * Error handling:
     * If initialization fails, the function may throw exceptions or log
     * critical errors. The application should handle these cases appropriately.
     */
    void Start(std::string_view window_title);

    /**
     * \brief Shutdown the engine and clean up all resources
     *
     * Performs orderly shutdown of all engine subsystems, ensuring proper
     * cleanup of resources and graceful termination. This should be called
     * when the application is ready to exit, typically after the main loop
     * has ended.
     *
     * Shutdown sequence:
     * - Cleans up 2D renderer and graphics resources
     * - Clears all game states and their resources
     * - Shuts down ImGui and development tools
     * - Releases OpenGL context and window resources
     * - Performs final logging and cleanup
     *
     * The shutdown process ensures that all GPU resources are properly
     * released and that the application can terminate cleanly without
     * resource leaks or system instability.
     */
    void Stop();
    
    /**
     * \brief Process one frame of the application main loop
     *
     * Executes a complete frame cycle including input processing, game logic
     * updates, rendering operations, and timing calculations. This function
     * should be called repeatedly in the main application loop until the
     * application is ready to terminate.
     *
     * Frame processing sequence:
     * - Updates timing information and frame statistics
     * - Processes window events and input state
     * - Updates the current game state logic
     * - Sets up rendering viewport and coordinate systems
     * - Renders the current game state with 2D graphics
     * - Handles ImGui rendering for development tools
     * - Prepares for the next frame
     *
     * The function handles the coordination between all subsystems and
     * ensures that each frame is processed consistently and efficiently.
     * It also manages the rendering pipeline and coordinate system
     * transformations automatically.
     */
    void Update();
    
    /**
     * \brief Check if the application should terminate
     * \return True if the application should exit, false to continue running
     *
     * Determines whether the application main loop should continue or terminate
     * based on window close events, user input, or game state conditions.
     * This is typically checked after each Update() call to decide whether
     * to continue the main loop.
     *
     * Termination conditions:
     * - User closes the window (clicking X button or Alt+F4)
     * - Game state manager signals application end
     * - Critical errors that require application termination
     *
     * The function provides a clean way to check for termination conditions
     * without requiring direct access to window or state management internals.
     */
    bool HasGameEnded();

private:
    // Forward declaration for Pimpl (Pointer to Implementation) idiom
    // This hides implementation details and reduces compilation dependencies
    class Impl;
    gsl::owner<Impl*> impl = nullptr;

private:
    // Singleton pattern: private constructor and destructor
    // prevent external instantiation and ensure single instance
    Engine();
    ~Engine();

    // Internal method for updating frame timing and window environment
    // Called each frame to maintain current runtime statistics
    void updateEnvironment();

};

================================================
FILE: source/Engine/Error.hpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once

#include "Engine.hpp"
#include "Logger.hpp"
#include <filesystem>
#include <source_location>
#include <sstream>
#include <utility>

namespace details
{
    template <typename... Messages>
    [[noreturn]] void internal_throw_report_and_throw_error(std::source_location caller_location, Messages&&... more_messages)
    {
        std::ostringstream error_message_stream;
        error_message_stream << '{' << std::filesystem::path(caller_location.file_name()).filename().string() << "}(" << caller_location.line() << ") : " << caller_location.function_name() << '\n';
        (error_message_stream << ... << std::forward<Messages>(more_messages));
        const auto message_string = error_message_stream.str();
        Engine::GetLogger().LogError(message_string);
        throw std::runtime_error{ message_string };
    }
}

template <typename M1>
[[noreturn]] void throw_error_message(M1&& m1, std::source_location caller_location = std::source_location::current())
{
    details::internal_throw_report_and_throw_error(caller_location, std::forward<M1>(m1));
}

template <typename M1, typename M2>
[[noreturn]] void throw_error_message(M1&& m1, M2&& m2, std::source_location caller_location = std::source_location::current())
{
    details::internal_throw_report_and_throw_error(caller_location, std::forward<M1>(m1), std::forward<M2>(m2));
}

template <typename M1, typename M2, typename M3>
[[noreturn]] void throw_error_message(M1&& m1, M2&& m2, M3&& m3, std::source_location caller_location = std::source_location::current())
{
    details::internal_throw_report_and_throw_error(caller_location, std::forward<M1>(m1), std::forward<M2>(m2), std::forward<M3>(m3));
}

template <typename M1, typename M2, typename M3, typename M4>
[[noreturn]] void throw_error_message(M1&& m1, M2&& m2, M3&& m3, M4&& m4, std::source_location caller_location = std::source_location::current())
{
    details::internal_throw_report_and_throw_error(caller_location, std::forward<M1>(m1), std::forward<M2>(m2), std::forward<M3>(m3), std::forward<M4>(m4));
}

template <typename M1, typename M2, typename M3, typename M4, typename M5>
[[noreturn]] void throw_error_message(M1&& m1, M2&& m2, M3&& m3, M4&& m4, M5&& m5, std::source_location caller_location = std::source_location::current())
{
    details::internal_throw_report_and_throw_error(caller_location, std::forward<M1>(m1), std::forward<M2>(m2), std::forward<M3>(m3), std::forward<M4>(m4), std::forward<M5>(m5));
}

template <typename M1, typename M2, typename M3, typename M4, typename M5, typename M6>
[[noreturn]] void throw_error_message(M1&& m1, M2&& m2, M3&& m3, M4&& m4, M5&& m5, M6&& m6, std::source_location caller_location = std::source_location::current())
{
    details::internal_throw_report_and_throw_error(caller_location, std::forward<M1>(m1), std::forward<M2>(m2), std::forward<M3>(m3), std::forward<M4>(m4), std::forward<M5>(m5), std::forward<M6>(m6));
}

template <typename M1, typename M2, typename M3, typename M4, typename M5, typename M6, typename M7>
[[noreturn]] void throw_error_message(M1&& m1, M2&& m2, M3&& m3, M4&& m4, M5&& m5, M6&& m6, M7&& m7, std::source_location caller_location = std::source_location::current())
{
    details::internal_throw_report_and_throw_error(
        caller_location, std::forward<M1>(m1), std::forward<M2>(m2), std::forward<M3>(m3), std::forward<M4>(m4), std::forward<M5>(m5), std::forward<M6>(m6), std::forward<M7>(m7));
}

template <typename M1, typename M2, typename M3, typename M4, typename M5, typename M6, typename M7, typename M8>
[[noreturn]] void throw_error_message(M1&& m1, M2&& m2, M3&& m3, M4&& m4, M5&& m5, M6&& m6, M7&& m7, M8&& m8, std::source_location caller_location = std::source_location::current())
{
    details::internal_throw_report_and_throw_error(
        caller_location, std::forward<M1>(m1), std::forward<M2>(m2), std::forward<M3>(m3), std::forward<M4>(m4), std::forward<M5>(m5), std::forward<M6>(m6), std::forward<M7>(m7),
        std::forward<M8>(m8));
}

template <typename M1, typename M2, typename M3, typename M4, typename M5, typename M6, typename M7, typename M8, typename M9>
[[noreturn]] void throw_error_message(M1&& m1, M2&& m2, M3&& m3, M4&& m4, M5&& m5, M6&& m6, M7&& m7, M8&& m8, M9&& m9, std::source_location caller_location = std::source_location::current())
{
    details::internal_throw_report_and_throw_error(
        caller_location, std::forward<M1>(m1), std::forward<M2>(m2), std::forward<M3>(m3), std::forward<M4>(m4), std::forward<M5>(m5), std::forward<M6>(m6), std::forward<M7>(m7), std::forward<M8>(m8),
        std::forward<M9>(m9));
}

template <typename M1, typename M2, typename M3, typename M4, typename M5, typename M6, typename M7, typename M8, typename M9, typename M10>
[[noreturn]] void
    throw_error_message(M1&& m1, M2&& m2, M3&& m3, M4&& m4, M5&& m5, M6&& m6, M7&& m7, M8&& m8, M9&& m9, M10&& m10, std::source_location caller_location = std::source_location::current())
{
    details::internal_throw_report_and_throw_error(
        caller_location, std::forward<M1>(m1), std::forward<M2>(m2), std::forward<M3>(m3), std::forward<M4>(m4), std::forward<M5>(m5), std::forward<M6>(m6), std::forward<M7>(m7), std::forward<M8>(m8),
        std::forward<M9>(m9), std::forward<M10>(m10));
}

================================================
FILE: source/Engine/Font.cpp
================================================
/**

* \file
* \author Rudy Castan
* \author Jonathan Holmes
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#include "Font.hpp"

#include "CS200/Image.hpp"
#include "Engine.hpp"
#include "Error.hpp"
#include "Matrix.hpp"
#include "Path.hpp"
#include "TextureManager.hpp"
#include <algorithm>
#include <stb_image.h>

/*

* 1. Load font texture and parse character boundaries during construction
* 2. Measure text dimensions for layout calculations
* 3. Render text to texture or directly to screen using character sprites
* 4. Support for colored text and transformation matrices
     */
     namespace CS230
     {
     Font::Font(const std::filesystem::path& file_name) : texture(file_name), image(file_name /*std::filesystem::path("Assets/Test.png")*/, is_image_flipped)
     {
       //  * Font Image Requirements:
       //  * - Characters arranged horizontally in a single row
       //  * - First pixel must be white (0xFFFFFFFF) as a format marker

        /*[[maybe_unused]] const auto _00       = GetPixel({ 0, 0 });
        [[maybe_unused]] const auto _00_array = CS200::ColorArray(_00);
    
        [[maybe_unused]] const auto _10       = GetPixel({ 1, 0 });
        [[maybe_unused]] const auto _10_array = CS200::ColorArray(_10);
    
        [[maybe_unused]] const auto _20       = GetPixel({ 2, 0 });
        [[maybe_unused]] const auto _20_array = CS200::ColorArray(_20);
    
        [[maybe_unused]] const auto _30       = GetPixel({ 3, 0 });
        [[maybe_unused]] const auto _30_array = CS200::ColorArray(_30);
    
        [[maybe_unused]] const auto _01       = GetPixel({ 0, 1 });
        [[maybe_unused]] const auto _01_array = CS200::ColorArray(_01);
    
        [[maybe_unused]] const auto _11       = GetPixel({ 1, 1 });
        [[maybe_unused]] const auto _11_array = CS200::ColorArray(_11);
    
        [[maybe_unused]] const auto _21       = GetPixel({ 2, 1 });
        [[maybe_unused]] const auto _21_array = CS200::ColorArray(_21);
    
        [[maybe_unused]] const auto _31       = GetPixel({ 3, 1 });
        [[maybe_unused]] const auto _31_array = CS200::ColorArray(_31);
    
        [[maybe_unused]] const auto _02       = GetPixel({ 0, 2 });
        [[maybe_unused]] const auto _02_array = CS200::ColorArray(_02);
    
        [[maybe_unused]] const auto _12       = GetPixel({ 1, 2 });
        [[maybe_unused]] const auto _12_array = CS200::ColorArray(_12);
    
        [[maybe_unused]] const auto _22       = GetPixel({ 2, 2 });
        [[maybe_unused]] const auto _22_array = CS200::ColorArray(_22);
    
        [[maybe_unused]] const auto _32       = GetPixel({ 3, 2 });
        [[maybe_unused]] const auto _32_array = CS200::ColorArray(_32);*/
    
    
        if (GetPixel({ 0, 0 }) == CS200::WHITE)
        {
            FindCharRects();
        }
        else
        {
            Engine::GetLogger().LogError("Font " + file_name.string() + " texture has wrong format!");
            throw std::runtime_error("Font fromat error");
        }
        //  * - Color changes between characters indicate boundaries
        //  * - Characters cover ASCII range from space (' ') to 'z'
        //  * - Image should contain exactly the expected number of characters
        //  *
        //  * Parsing Process:
        //  * The constructor scans the top row of pixels to detect color changes,
        //  * which indicate character boundaries. Each character's rectangular
        //  * region is calculated and stored for later use during text rendering.
        //  *
        //  * Error Handling:
        //  * If the font file is malformed (wrong format, missing characters, or
        //  * incorrect structure), the constructor will throw an error to indicate
        //  * the problem. This ensures that only valid fonts are used for rendering.
    }
    
    std::shared_ptr<Texture> Font::PrintToTexture(const std::string& text, CS200::RGBA color)
    {
        const auto&       window_environment = Engine::GetWindowEnvironment();
        //  * Advanced Caching System:
        //  * - Cache key: Combination of text string and color (format: "text_0xCOLOR")
        const std::string cache_key{ text + std::string("_0x") + std::to_string(color) };
    
        //  * - Frame tracking: Each cached texture records when it was last accessed
        for (auto it = textures.begin(); it != textures.end();)
        {
            // ++(it->second.time);
            //  * - Reference counting: Uses shared_ptr for automatic memory management
    
            //  * - Intelligent cleanup: Removes old textures only when they have single reference and are older than 60 frames
            if ((window_environment.FrameCount - it->second.timestamp) > 60 && it->second.texture.use_count() == 1)
            {
                it = textures.erase(it);
            }
            else
            {
                ++it;
            }
        }
    
        //  * - Performance optimization: Eliminates redundant text rendering operations
    
        //          * Caching Strategy:
        //  * 1. Check cache using generated key (text + color combination)
        //  * 2. If found: Update last-used frame timestamp and return cached texture
        //  * 3. If not found: Create new texture, cache it, and return
        //  * 4. Periodic cleanup: Remove textures older than 60 frames with reference count of 1
    
        if (textures.find(cache_key) == textures.end())
        {
            //          * Rendering Process (for new textures):
            //  * 1. Measure total text dimensions to determine optimal texture size
            const Math::ivec2 text_size = MeasureText(text /*std::string("hello")*/);
    
            //  * 2. Create render target texture using TextureManager
            auto& texture_manager = Engine::GetTextureManager();
            texture_manager.StartRenderTextureMode(text_size.x, text_size.y);
            Math::TransformationMatrix matrix{};
            for (const char c : text /*std::string("hello")*/)
            {
                DrawChar(matrix, c, color);
            }
            auto target_texture = texture_manager.EndRenderTextureMode();
            //  * 3. Render each character from font atlas to the target texture
    
            //  * 4. Store in cache with current frame timestamp
            //  * 5. Return shared_ptr for client use
    
            textures[cache_key] = { window_environment.FrameCount, target_texture };
    
            Engine::GetLogger().LogEvent("Loading Texture: " + text);
        }
        else
        {
            textures[cache_key].timestamp = window_environment.FrameCount;
        }
        return textures[cache_key].texture;
    }
    
    void Font::FindCharRects()
    {
        CS200::RGBA check_color = GetPixel({ 0, 0 });
        CS200::RGBA next_color;
    
        int height = texture.GetSize().y;
    
        int x = 0;
        for (int index = 0; index < num_chars; index++)
        {
            int width = 0;
    
            do
            {
                width++;
                next_color = GetPixel({ x + width, 0 });
            } while (check_color == next_color);
    
            check_color = next_color;
    
            char_rects[index].point_2 = { x + width , height };
            char_rects[index].point_1 = { x, 1  }; // 1 mean ignore line above
            x += width;
        }
        // stbi_image_free(image_data);
        // image.~Image();
    }
    
    Math::irect& Font::GetCharRect(char c)
    {
        if (c >= ' ' && c <= 'z')
        {
            return char_rects[c - ' '];
        }
        else
        {
            Engine::GetLogger().LogError("Char '" + std::to_string(c) + "' not found");
            return char_rects[0];
        }
    }
    
    Math::ivec2 Font::MeasureText(std::string text)
    {
        Math::ivec2 text_size = GetCharRect(text[0]).Size();
        for (size_t i = 1; i < text.size(); ++i)
        {
            text_size.x += GetCharRect(text[i]).Size().x;
            if (GetCharRect(text[i]).Size().y > GetCharRect(text[i - 1]).Size().y)
            {
                text_size.y = GetCharRect(text[i]).Size().y;
            }
        }
        return text_size;
    }
    
    void Font::DrawChar(Math::TransformationMatrix& matrix, char c, CS200::RGBA color)
    {
        const Math::irect& display_rect   = GetCharRect(c);
    
        const Math::ivec2 top_left_texel = { display_rect.Left(), display_rect.Bottom() }; //top_left is 0,0!!
        if (c != ' ')
        {
            //const auto to_center     = Math::TranslationMatrix(Math::vec2(display_rect.Size().x / 2.0, display_rect.Size().y / 2.0));
            const auto flip          = Math::ScaleMatrix(Math::vec2{ 1, -1 });
            //const auto to_bottomleft = Math::TranslationMatrix(Math::vec2(display_rect.Size().x / 2.0, -display_rect.Size().y / 2.0));
            const auto flip_quad     = flip;
            texture.Draw(matrix * flip_quad, top_left_texel, display_rect.Size(), color);
        }
        matrix *= Math::TranslationMatrix(Math::ivec2{ display_rect.Size().x, 0 });
    }
    
    CS200::RGBA Font::GetPixel(Math::ivec2 texel) // tl is (0,0) !!
    {
        const CS200::RGBA* image_data = image.data();
        const auto         image_size = image.GetSize();
        // if (is_image_flipped)
        //{
        //     const int   index        = (image_size.x * image_size.y - 1) - (texel.x + texel.y * image_size.x);
        //     CS200::RGBA return_color = CS200::rgba_to_abgr(CS200::argb_to_rgba(image_data[index])); // very weird..argb?
    
        //    return return_color; // endian!!!
        //}
        // else
        //{
        const int   index        = texel.x + texel.y * image_size.x;
        CS200::RGBA return_color = CS200::rgba_to_abgr(image_data[index]);
    
        return return_color; // endian!!!
        //}
    }

}    

================================================
FILE: source/Engine/Font.hpp
================================================
/**

* \file
* \author Rudy Castan
* \author Jonathan Holmes
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#pragma once
#include "Rect.hpp"
#include "Texture.hpp"
#include "Vec2.hpp"
#include <filesystem>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>

namespace CS230
{
    /**
     * \brief Bitmap font system for rendering text using pre-generated font textures
     *
     * Font provides a lightweight and efficient text rendering system based on
     * bitmap font textures. Rather than using complex font rasterization at runtime,
     * this system loads pre-rendered character sets from image files and uses them
     * to compose text strings quickly and efficiently.
     *
     * Bitmap Font Advantages:
     * - Consistent visual appearance across all platforms and systems
     * - Fast rendering performance with minimal runtime computation
     * - Predictable memory usage and loading times
     * - Simple integration with existing texture and rendering systems
     * - Pixel-perfect control over character appearance and spacing
     *
     * Font File Format:
     * The system expects specially formatted font textures where characters are
     * arranged horizontally in a single row, with specific color markers to
     * indicate character boundaries. The first pixel must be white, and color
     * changes signal the separation between characters.
     *
     * Character Set:
     * Supports ASCII characters from space (' ') to lowercase 'z', covering
     * basic alphanumeric characters, punctuation, and symbols commonly used
     * in game interfaces and debugging displays.
     *
     * Text Rendering Workflow:
     * 1. Load font texture and parse character boundaries during construction
     * 2. Measure text dimensions for layout calculations
     * 3. Render text to texture or directly to screen using character sprites
     * 4. Support for colored text and transformation matrices
     *
     * This font system is particularly well-suited for game development where
     * consistent, fast text rendering is more important than dynamic font
     * sizing or complex typography features.
     */
    class Font
    {
    public:
        /**
         * \brief Load and initialize a bitmap font from an image file
         * \param file_name Path to the font texture image file
         *
         * Constructs a Font object by loading a specially formatted bitmap font
         * texture and parsing the character boundary information. The constructor
         * analyzes the font image to determine where each character begins and
         * ends, creating a lookup table for efficient character rendering.
         *
         * Font Image Requirements:
         * - Characters arranged horizontally in a single row
         * - First pixel must be white (0xFFFFFFFF) as a format marker
         * - Color changes between characters indicate boundaries
         * - Characters cover ASCII range from space (' ') to 'z'
         * - Image should contain exactly the expected number of characters
         *
         * Parsing Process:
         * The constructor scans the top row of pixels to detect color changes,
         * which indicate character boundaries. Each character's rectangular
         * region is calculated and stored for later use during text rendering.
         *
         * Error Handling:
         * If the font file is malformed (wrong format, missing characters, or
         * incorrect structure), the constructor will throw an error to indicate
         * the problem. This ensures that only valid fonts are used for rendering.
         *
         * The loaded font is immediately ready for text rendering operations
         * and will remain valid for the lifetime of the Font object.
         */
        Font(const std::filesystem::path& file_name);

        /**
         * \brief Render text string to a cached texture for efficient reuse
         * \param text String of text to render using this font
         * \param color RGBA color value for the text (default: white)
         * \return Shared pointer to texture containing the rendered text (cached if previously rendered)
         *
         * Creates or retrieves a cached texture containing the rendered text string,
         * allowing the text to be used like any other texture in the rendering system.
         * This approach enables text to be drawn with transformations, effects,
         * and blending modes just like sprite graphics.
         *
         * Advanced Caching System:
         * - Cache key: Combination of text string and color (format: "text_0xCOLOR")
         * - Frame tracking: Each cached texture records when it was last accessed
         * - Reference counting: Uses shared_ptr for automatic memory management
         * - Intelligent cleanup: Removes old textures only when they have single reference and are older than 60 frames
         * - Performance optimization: Eliminates redundant text rendering operations
         *
         * Caching Strategy:
         * 1. Check cache using generated key (text + color combination)
         * 2. If found: Update last-used frame timestamp and return cached texture
         * 3. If not found: Create new texture, cache it, and return
         * 4. Periodic cleanup: Remove textures older than 60 frames with reference count of 1
         *
         * Rendering Process (for new textures):
         * 1. Measure total text dimensions to determine optimal texture size
         * 2. Create render target texture using TextureManager
         * 3. Render each character from font atlas to the target texture
         * 4. Store in cache with current frame timestamp
         * 5. Return shared_ptr for client use
         *
         * Memory Management Benefits:
         * - Shared ownership: Multiple objects can reference the same text texture
         * - Automatic cleanup: Textures are removed when no longer referenced elsewhere
         * - Frame-based aging: Prevents immediate removal of frequently used text
         * - Cache efficiency: Only removes textures that are truly unused
         *
         * Text-to-Texture Advantages:
         * - Caching eliminates redundant text rendering for repeated strings
         * - Supports full transformation matrices (rotation, scaling, positioning)
         * - Enables text participation in sprite batching and effects systems
         * - Provides consistent rendering performance regardless of text complexity
         * - Allows text to be treated as standard texture assets
         *
         * Color and Formatting:
         * The color parameter applies a tint to the entire text string while
         * preserving original font character shapes, anti-aliasing, and spacing.
         * Different colors of the same text are cached separately for maximum
         * flexibility without color bleeding between cache entries.
         */
        std::shared_ptr<Texture> PrintToTexture(const std::string& text, CS200::RGBA color = 0xFFFFFFFF);
    
    private:
        void         FindCharRects();
        Math::irect& GetCharRect(char c);
        Math::ivec2  MeasureText(std::string text);
        void         DrawChar(Math::TransformationMatrix& matrix, char c, CS200::RGBA color = CS200::WHITE);
        CS200::RGBA  GetPixel(Math::ivec2 texel);
    
    
        Texture texture;
    
        struct TimeTexture
        {
            uint64_t                 timestamp{};
            std::shared_ptr<Texture> texture{};
        };
    
        std::map<const std::string, TimeTexture> textures; // <key, <time stamp, texture shared_ptr>>
        static constexpr int                     num_chars    = 'z' - ' ' + 1;
        static constexpr int                     num_channels = 4; // rgba
        Math::irect                              char_rects[num_chars];
        CS200::Image                             image;
        Math::ivec2                              dimensions;
        static constexpr bool                    is_image_flipped = false;
    };

}

================================================
FILE: source/Engine/Fonts.h
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Fonts.h
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    May 5, 2025
*/
#pragma once
enum Fonts {
    Simple,
    Outlined
};

================================================
FILE: source/Engine/FPS.hpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once

#include <cmath>

namespace util
{
    class FPS
    {
        double timeCounter = 0;
        double numFrames   = 0;
        double fps         = 0;

    public:
        constexpr void Update(double delta_time_seconds) noexcept
        {
            ++numFrames;
            timeCounter += delta_time_seconds;
            if (timeCounter > 1.0)
            {
                fps = numFrames / timeCounter;
                timeCounter -= 1.0;
                numFrames = 0;
            }
        }
    
        operator long long() const noexcept
        {
            return std::llround(fps);
        }
    
        operator int() const noexcept
        {
            return static_cast<int>(std::lround(fps));
        }
    };

}

================================================
FILE: source/Engine/GameObject.cpp
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObject.cpp
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    April 25, 2025
*/
#include "GameObject.h"
#include "GameState.hpp"
#include "GameStateManager.hpp"
#include "ShowCollision.h"

#include <numbers>

CS230::GameObject::GameObject(Math::vec2 _position) :
    GameObject(_position, 0, { 1, 1 })
{
}

CS230::GameObject::GameObject(Math::vec2 _position, double _rotation, Math::vec2 _scale) :

    current_state(&state_none),
    matrix_outdated(true),
    destroy(false),
    position(_position),
    velocity(Math::vec2{ 0.0,0.0 }),
    scale(_scale),
    rotation(_rotation)    

{}

bool CS230::GameObject::IsCollidingWith(GameObject* other_object)
{
    Collision* collider = GetGOComponent<Collision>();
    return collider != nullptr && collider->IsCollidingWith(other_object);
}

bool CS230::GameObject::IsCollidingWith(Math::vec2 point)
{
    Collision* collider = GetGOComponent<Collision>();
    return collider != nullptr && collider->IsCollidingWith(point);
}

bool CS230::GameObject::CanCollideWith([[maybe_unused]]GameObjectTypes other_object_type)
{
    return false;
}

void CS230::GameObject::Update(double dt) {
    current_state->Update(this, dt);
    //sprite.Update(dt);
    if (velocity.x != 0 || velocity.y != 0) {
        UpdatePosition(velocity * dt);
    }
    UpdateGOComponents(dt);
    current_state->CheckExit(this);
}

void CS230::GameObject::change_state(State* new_state) {
    current_state = new_state;
    current_state->Enter(this);
}

void CS230::GameObject::Draw(Math::TransformationMatrix camera_matrix, unsigned int color , float depth )
{

    Sprite* sprite = GetGOComponent<Sprite>();
    if (sprite != nullptr) {
    
        float real_depth;
        if (DrawPriority() != DRAWPRIORITY)
        {
            real_depth = 1.f - (static_cast<float>(DrawPriority()) / 100.0f);
            if (0.7f < real_depth)
                real_depth = 0.7f;
            if (0.3f > real_depth)
                real_depth = 0.3f;
        }
        else
        {
            real_depth = depth;
        }
        sprite->Draw(camera_matrix * GetMatrix(), color, real_depth);
    }
    Collision* collision = GetGOComponent<Collision>();
    ShowCollision* showcollision = Engine::GetGameStateManager().GetGSComponent<ShowCollision>();
    if (showcollision != nullptr) {
        if ((collision != nullptr) && (showcollision->Enabled() == true)) {
            collision->Draw(camera_matrix,0.f);
        }
    }

}

const Math::TransformationMatrix& CS230::GameObject::GetMatrix() {
    if (matrix_outdated == true) {
        object_matrix = Math::TranslationMatrix(position) * Math::RotationMatrix(rotation) * Math::ScaleMatrix(scale);
        matrix_outdated = false;
    }    
    return object_matrix;
}

const Math::vec2& CS230::GameObject::GetPosition() const
{
    return position;
}

const Math::vec2& CS230::GameObject::GetVelocity() const
{
    return velocity;
}

const Math::vec2& CS230::GameObject::GetScale() const
{
    return scale;
}

double CS230::GameObject::GetRotation() const
{
    return rotation;
}

void CS230::GameObject::SetPosition(Math::vec2 new_position) {
    position = new_position;
    matrix_outdated = true;
}

void CS230::GameObject::UpdatePosition(Math::vec2 delta) {
    position += delta;
    matrix_outdated = true;
}

void CS230::GameObject::SetVelocity(Math::vec2 new_velocity){
    velocity = new_velocity;
    matrix_outdated = true;
}

void CS230::GameObject::UpdateVelocity(Math::vec2 delta)
{
    velocity += delta;
    matrix_outdated = true;
}

void CS230::GameObject::SetScale(Math::vec2 new_scale)
{
    scale = new_scale;
    matrix_outdated = true;
}

void CS230::GameObject::UpdateScale(Math::vec2 delta)
{
    scale += delta;
    matrix_outdated = true;
}

void CS230::GameObject::SetRotation(double new_rotation)
{
    rotation = new_rotation;
    matrix_outdated = true;
}

void CS230::GameObject::UpdateRotation(double delta)
{
    rotation += delta;
    matrix_outdated = true;
}

================================================
FILE: source/Engine/GameObject.h
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObject.h
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    April 25, 2025
*/

#pragma once
#include "../Game/GameObjectTypes.h"
#include "ComponentManager.h"
#include "ShowCollision.h"
#include "Sprite.h"

namespace Math
{
    class TransformationMatrix;
}

namespace CS230
{
    class Component;

    class GameObject
    {
    public:
        friend class Sprite;
        GameObject(Math::vec2 position);
        GameObject(Math::vec2 position, double rotation, Math::vec2 scale);
    
        virtual ~GameObject()
        {
        }
    
        virtual GameObjectTypes Type()     = 0;
        virtual std::string     TypeName() = 0;
    
        virtual int UpdatePriority() const
        {
            return UPDATEPRIORITY;
        }
    
        virtual int DrawPriority() const
        {
            return DRAWPRIORITY; // higher for later, upper means low depth, 30 - 70 fix
        }
    
        bool         IsCollidingWith(GameObject* other_object);
        bool         IsCollidingWith(Math::vec2 point);
        virtual bool CanCollideWith(GameObjectTypes other_object_type);
        virtual void ResolveCollision([[maybe_unused]] GameObject* other_object) { };
    
        virtual void Update(double dt);
        virtual void Draw(Math::TransformationMatrix camera_matrix, unsigned int color = 0xFFFFFFFF, float depth = 0.5f);
    
        const Math::TransformationMatrix& GetMatrix();
        const Math::vec2&                 GetPosition() const;
        const Math::vec2&                 GetVelocity() const;
        const Math::vec2&                 GetScale() const;
        double                            GetRotation() const;
    
        template <typename T>
        T* GetGOComponent()
        {
            return componentmanager.GetComponent<T>();
        }
    
        void SetPosition(Math::vec2 new_position);
        void SetVelocity(Math::vec2 new_velocity);
        void UpdateVelocity(Math::vec2 delta);
    
        const bool& Destroyed() const
        {
            return destroy;
        }
    
        void Destroy()
        {
            destroy = true;
        }
    
        static constexpr int DRAWPRIORITY = 50;
        static constexpr int UPDATEPRIORITY = 10;
    
    protected:
    
        void UpdatePosition(Math::vec2 delta);
    
    
        void SetScale(Math::vec2 new_scale);
        void UpdateScale(Math::vec2 delta);
        void SetRotation(double new_rotation);
        void UpdateRotation(double delta);
    
        class State
        {
        public:
            virtual void        Enter(GameObject* object)             = 0;
            virtual void        Update(GameObject* object, double dt) = 0;
            virtual void        CheckExit(GameObject* object)         = 0;
            virtual std::string GetName()                             = 0;
    
            virtual ~State()
            {
            }
        };
    
        State* current_state;
        void   change_state(State* new_state);
    
        bool matrix_outdated;
    
        void AddGOComponent(Component* component)
        {
            componentmanager.AddComponent(component);
        }
    
        template <typename T>
        void RemoveGOComponent()
        {
            componentmanager.RemoveComponent<T>();
        }
    
        void ClearGOComponents()
        {
            componentmanager.Clear();
        }
    
        void UpdateGOComponents(double dt)
        {
            componentmanager.UpdateAll(dt);
        }
    
    
    private:
        bool destroy;
    
        class State_None : public State
        {
        public:
            void Enter(GameObject*) override
            {
            }
    
            void Update(GameObject*, double) override
            {
            }
    
            void CheckExit(GameObject*) override
            {
            }
    
            std::string GetName() override
            {
                return "";
            }
    
            ~State_None()
            {
            }
        };
    
        State_None state_none;
    
        Math::TransformationMatrix object_matrix;
    
    
        Math::vec2 position;
        Math::vec2 velocity;
        Math::vec2 scale;
        double     rotation;
    
        ComponentManager componentmanager;
    };

}

================================================
FILE: source/Engine/GameObjectManager.cpp
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObjectManager.cpp
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    April 25, 2025
*/
#include "GameObjectManager.h"
#include "Logger.hpp"

void CS230::GameObjectManager::Add(GameObject* object){
    objects.push_back(object);
}

void CS230::GameObjectManager::Unload(){
    for (GameObject* object : objects) {
        delete object;
    }
    objects.clear();
}

void CS230::GameObjectManager::UpdateAll(double dt){
    std::vector<GameObject*> destroy_objects;
    for (GameObject* object : objects) {
        object->Update(dt);
        if (object->Destroyed() == true) {
            destroy_objects.push_back(object);
        }
    }
    for (GameObject* destroy_object : destroy_objects) {
        objects.remove(destroy_object);
        delete destroy_object;
    }
}

void CS230::GameObjectManager::SortForUpdate()
{
    objects.sort([](GameObject* a, GameObject* b) { return a->UpdatePriority() < b->UpdatePriority(); });
}

void CS230::GameObjectManager::DrawAll(Math::TransformationMatrix camera_matrix){
    for (GameObject* object : objects) {
        object->Draw(camera_matrix);        
    }
}

void CS230::GameObjectManager::CollisionTest()
{
    for (GameObject* object1 : objects) {
        for (GameObject* object2 : objects) {
            if (object1 != object2 && object1->CanCollideWith(object2->Type())) {
                if (object1->IsCollidingWith(object2)) {
                    Engine::GetLogger().LogEvent("Collision Detected: " + object1->TypeName() + " and " + object2->TypeName());
                    object1->ResolveCollision(object2);
                }
            }
        }
    }
}

================================================
FILE: source/Engine/GameObjectManager.h
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObjectManager.h
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    April 25, 2025
*/

#pragma once
#include <list>
#include "GameObject.h"
#include "Matrix.hpp"
#include "Component.h"

namespace Math { class TransformationMatrix; }

namespace CS230 {
    class GameObjectManager : public CS230::Component{
    public:
        void Add(GameObject* object);
        void Unload();

        void UpdateAll(double dt);
        void SortForUpdate();
        void DrawAll(Math::TransformationMatrix camera_matrix);
    
        void CollisionTest();
    
        const std::list<GameObject*>& GetAll() const { return objects; }
    private:
        std::list<GameObject*> objects;
    };

}

================================================
FILE: source/Engine/GameState.hpp
================================================
/**

* \file
* \author Rudy Castan
* \author Jonathan Holmes
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once

#include "ComponentManager.h"
#include <gsl/gsl>

namespace CS230
{
    class GameState
    {
    public:
        virtual void          Load()            = 0;
        virtual void          Update(double dt) = 0;
        virtual void          Unload()          = 0;
        virtual void          Draw()            = 0;
        virtual void          DrawImGui()       = 0;
        virtual gsl::czstring GetName() const   = 0;
        virtual ~GameState()                    = default;

        template <typename T>
        T* GetGSComponent()
        {
            return componentmanager.GetComponent<T>();
        }
    
    protected:
        void AddGSComponent(Component* component)
        {
            componentmanager.AddComponent(component);
        }
    
        void UpdateGSComponents(double dt)
        {
            componentmanager.UpdateAll(dt);
        }
    
        template <typename T>
        void RemoveGSComponent()
        {
            componentmanager.RemoveComponent<T>();
        }
    
        void ClearGSComponents()
        {
            componentmanager.Clear();
        }
    
    private:
        ComponentManager componentmanager;
    };

}

================================================
FILE: source/Engine/GameStateManager.cpp
================================================
/**

* \file
* \author Rudy Castan
* \author Jonathan Holmes
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "GameStateManager.hpp"
  #include "GameObjectManager.h"

namespace CS230
{
    void GameStateManager::PopState()
    {
        using namespace std::literals;
        auto* const state = mGameStateStack.back().get();
        mToClear.push_back(std::move(mGameStateStack.back()));
        mGameStateStack.erase(mGameStateStack.end() - 1);
        Engine::GetLogger().LogEvent("Exiting state "s + state->GetName());
        state->Unload();
    }

    void GameStateManager::Update(double dt)
    {
        mToClear.clear();
        mGameStateStack.back()->Update(dt);
        if (!mGameStateStack.empty())
        {
            GameObjectManager* current_gameobject_manager = mGameStateStack.back()->GetGSComponent<GameObjectManager>();
            if (current_gameobject_manager != nullptr)
            {
                current_gameobject_manager->CollisionTest();
            }
        }
    }
    
    void GameStateManager::Draw()
    {
        for (auto& game_state : mGameStateStack)
        {
            game_state->Draw();
        }
    }
    
    void GameStateManager::DrawImGui()
    {
        if (!mGameStateStack.empty())
        {
            mGameStateStack.back()->DrawImGui();
        }
    }
    
    void GameStateManager::Clear()
    {
        while (!mGameStateStack.empty())
            PopState();
        mToClear.clear();
    }

}

================================================
FILE: source/Engine/GameStateManager.hpp
================================================
/**

* \file
* \author Rudy Castan
* \author Jonathan Holmes
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once

#include "Engine/Engine.hpp"
#include "Engine/Logger.hpp"
#include "GameState.hpp"
#include <memory>
#include <vector>

namespace CS230
{
    class GameStateManager
    {
    public:
        template <typename STATE>
        void PushState();
        void PopState();
        void Update(double);
        void Draw();
        void DrawImGui();

        [[nodiscard]] bool HasGameEnded() const
        {
            return mGameStateStack.empty();
        }
    
        void Clear();
    
        template <typename T>
        T* GetGSComponent()
        {
            return mGameStateStack.back()->GetGSComponent<T>();
        }
    
    private:
        std::vector<std::unique_ptr<GameState>> mGameStateStack;
        std::vector<std::unique_ptr<GameState>> mToClear;
    };
    
    template <typename STATE>
    void GameStateManager::PushState()
    {
        using namespace std::literals;
        mGameStateStack.push_back(std::make_unique<STATE>());
        const auto& state = mGameStateStack.back();
        Engine::GetLogger().LogEvent("Entering state "s + state->GetName());
        state->Load();
    }

}

================================================
FILE: source/Engine/Input.cpp
================================================
/**

* \file
* \author Rudy Castan
* \author Jonathan Holmes
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#include "Input.hpp"
#include "Engine.hpp"
#include "Logger.hpp"
#include <SDL.h>

namespace CS230
{
    Input::Input()
    {
        Init();
    }

    void Input::Init()
    {
        previousKeys.fill(false);
        currentKeys.fill(false);
    }
    
    void Input::Update()
    {
        previousKeys = currentKeys;
        // via SDL get keyboard state
        // mark each keyboard that is down
        for (Keys key = Keys::A; key < Keys::Count; ++key)
        {
            const auto   sdl_key        = convert_cs230_to_sdl(static_cast<Keys>(key));
            const Uint8* keyboard_state = SDL_GetKeyboardState(nullptr);
            SetKeyDown(key, keyboard_state[sdl_key]);
            if (KeyJustPressed(key))
            {
                Engine::GetLogger().LogDebug("Key Pressed");
            }
            else if (KeyJustReleased(key))
            {
                Engine::GetLogger().LogDebug("Key Released");
            }
        }
    }
    
    bool Input::KeyDown(Input::Keys key) const
    {
        return currentKeys[static_cast<std::size_t>(key)];
    }
    
    bool Input::KeyJustReleased(Input::Keys key) const
    {
        const std::size_t index = static_cast<std::size_t>(key);
        return !currentKeys[index] && previousKeys[index];
    }
    
    bool Input::KeyJustPressed(Input::Keys key) const
    {
        const std::size_t index = static_cast<std::size_t>(key);
        return currentKeys[index] && !previousKeys[index];
    }
    
    void Input::SetKeyDown(Input::Keys key, bool is_pressed)
    {
        currentKeys[static_cast<std::size_t>(key)] = is_pressed;
    }
    
    SDL_Scancode convert_cs230_to_sdl(Input::Keys cs230_key)
    {
        switch (cs230_key)
        {
            case CS230::Input::Keys::A: return SDL_SCANCODE_A;
            case CS230::Input::Keys::B: return SDL_SCANCODE_B;
            case CS230::Input::Keys::C: return SDL_SCANCODE_C;
            case CS230::Input::Keys::D: return SDL_SCANCODE_D;
            case CS230::Input::Keys::E: return SDL_SCANCODE_E;
            case CS230::Input::Keys::F: return SDL_SCANCODE_F;
            case CS230::Input::Keys::G: return SDL_SCANCODE_G;
            case CS230::Input::Keys::H: return SDL_SCANCODE_H;
            case CS230::Input::Keys::I: return SDL_SCANCODE_I;
            case CS230::Input::Keys::J: return SDL_SCANCODE_J;
            case CS230::Input::Keys::K: return SDL_SCANCODE_K;
            case CS230::Input::Keys::L: return SDL_SCANCODE_L;
            case CS230::Input::Keys::M: return SDL_SCANCODE_M;
            case CS230::Input::Keys::N: return SDL_SCANCODE_N;
            case CS230::Input::Keys::O: return SDL_SCANCODE_O;
            case CS230::Input::Keys::P: return SDL_SCANCODE_P;
            case CS230::Input::Keys::Q: return SDL_SCANCODE_Q;
            case CS230::Input::Keys::R: return SDL_SCANCODE_R;
            case CS230::Input::Keys::S: return SDL_SCANCODE_S;
            case CS230::Input::Keys::T: return SDL_SCANCODE_T;
            case CS230::Input::Keys::U: return SDL_SCANCODE_U;
            case CS230::Input::Keys::V: return SDL_SCANCODE_V;
            case CS230::Input::Keys::W: return SDL_SCANCODE_W;
            case CS230::Input::Keys::X: return SDL_SCANCODE_X;
            case CS230::Input::Keys::Y: return SDL_SCANCODE_Y;
            case CS230::Input::Keys::Z: return SDL_SCANCODE_Z;
            case CS230::Input::Keys::Space: return SDL_SCANCODE_SPACE;
            case CS230::Input::Keys::Enter: return SDL_SCANCODE_RETURN;
            case CS230::Input::Keys::Left: return SDL_SCANCODE_LEFT;
            case CS230::Input::Keys::Up: return SDL_SCANCODE_UP;
            case CS230::Input::Keys::Right: return SDL_SCANCODE_RIGHT;
            case CS230::Input::Keys::Down: return SDL_SCANCODE_DOWN;
            case CS230::Input::Keys::Escape: return SDL_SCANCODE_ESCAPE;
            case CS230::Input::Keys::Tab: return SDL_SCANCODE_TAB;
            case CS230::Input::Keys::One: return SDL_SCANCODE_1;
            case CS230::Input::Keys::Two: return SDL_SCANCODE_2;
            case CS230::Input::Keys::Three: return SDL_SCANCODE_3;
            case CS230::Input::Keys::Four: return SDL_SCANCODE_4;
            default: return SDL_SCANCODE_UNKNOWN; // SDL's equivalent of an unknown key
        }
    }

}

================================================
FILE: source/Engine/Input.hpp
================================================
/**

* \file
* \author Rudy Castan
* \author Jonathan Holmes
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#pragma once
#include <SDL.h>
#include <gsl/gsl>
#include <vector>

namespace CS230
{
    class Input
    {
    public:
        enum class Keys
        {
            A,
            B,
            C,
            D,
            E,
            F,
            G,
            H,
            I,
            J,
            K,
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z,
            Space,
            Enter,
            Left,
            Up,
            Right,
            Down,
            Escape,
            Tab,
            One,
            Two,
            Three,
            Four,
            Count
        };

        Input();
        void Init();
        void Update();
    
        bool KeyDown(Keys key) const;
        bool KeyJustReleased(Keys key) const;
        bool KeyJustPressed(Keys key) const;
    
    private:
        std::array<bool, static_cast<std::size_t>(Keys::Count)> previousKeys;
        std::array<bool, static_cast<std::size_t>(Keys::Count)> currentKeys;
        void                                                    SetKeyDown(Keys key, bool is_pressed);
    };
    
    constexpr Input::Keys& operator++(Input::Keys& the_key) noexcept
    {
        the_key = static_cast<Input::Keys>(static_cast<unsigned>(the_key) + 1);
        return the_key;
    }
    
    SDL_Scancode convert_cs230_to_sdl(Input::Keys cs230_key);
    
    constexpr gsl::czstring to_string(Input::Keys key) noexcept
    {
        switch (key)
        {
            case Input::Keys::A: return "A";
            case Input::Keys::B: return "B";
            case Input::Keys::C: return "C";
            case Input::Keys::D: return "D";
            case Input::Keys::E: return "E";
            case Input::Keys::F: return "F";
            case Input::Keys::G: return "G";
            case Input::Keys::H: return "H";
            case Input::Keys::I: return "I";
            case Input::Keys::J: return "J";
            case Input::Keys::K: return "K";
            case Input::Keys::L: return "L";
            case Input::Keys::M: return "M";
            case Input::Keys::N: return "N";
            case Input::Keys::O: return "O";
            case Input::Keys::P: return "P";
            case Input::Keys::Q: return "Q";
            case Input::Keys::R: return "R";
            case Input::Keys::S: return "S";
            case Input::Keys::T: return "T";
            case Input::Keys::U: return "U";
            case Input::Keys::V: return "V";
            case Input::Keys::W: return "W";
            case Input::Keys::X: return "X";
            case Input::Keys::Y: return "Y";
            case Input::Keys::Z: return "Z";
            case Input::Keys::Space: return "Space";
            case Input::Keys::Enter: return "Enter";
            case Input::Keys::Left: return "Left";
            case Input::Keys::Up: return "Up";
            case Input::Keys::Right: return "Right";
            case Input::Keys::Down: return "Down";
            case Input::Keys::Escape: return "Escape";
            case Input::Keys::Tab: return "Tab";
            case Input::Keys::One: return "One";
            case Input::Keys::Two: return "Two";
            case Input::Keys::Three: return "Three";
            case Input::Keys::Four: return "Four";
            case Input::Keys::Count: return "Count";
        }
        return "Unknown";
    }

}

================================================
FILE: source/Engine/Logger.cpp
================================================
/**

* \file
* \author Rudy Castan
* \author Jonathan Holmes
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#include "Logger.hpp"
#include <iostream>

namespace CS230
{
    Logger::Logger(Severity severity, bool use_console, std::chrono::system_clock::time_point _start_time) : min_level(severity), out_stream("Trace.log"), start_time(_start_time)
    {
        if (use_console == true)
        {
            out_stream.basic_ios<char>::rdbuf(std::cout.rdbuf());
            ;
        }
    }

    void Logger::LogError(std::string text)
    {
        log(Severity::Error, text);
    }
    
    void Logger::LogEvent(std::string text)
    {
        log(Severity::Event, text);
    }
    
    void Logger::LogDebug(std::string text)
    {
        log(Severity::Debug, text);
    }
    
    void Logger::LogVerbose(std::string text)
    {
        log(Severity::Verbose, text);
    }
    
    void Logger::log(Severity severity, std::string message)
    {
        std::map<CS230::Logger::Severity, std::string> get_error_level = {
            { CS230::Logger::Severity::Verbose, "Verbose" },
            {   CS230::Logger::Severity::Debug,   "Debug" },
            {   CS230::Logger::Severity::Event,   "Event" },
            {   CS230::Logger::Severity::Error,   "Error" }
        };
        std::string answer = get_error_level[severity] + "\t" + message;
        //===========map_version
    
    
        if (int(CS230::Logger::min_level) <= int(severity))
        {
            out_stream.precision(4);
            out_stream << '[' << std::fixed << seconds_since_start() << "]\t";
            out_stream << answer << "\n";
        }
        return;
    }
    
    double Logger::seconds_since_start()
    {
        return std::chrono::duration<double>(std::chrono::system_clock::now() -start_time).count();
    }
    
    // note the proper way to redirect the rdbuf is `stream.basic_ios<char>::rdbuf(other_stream.rdbuf());`
    // note that we don't need a destructor ~Logger() if all we are doing is closing the streams. The std stream classes impl Rule of 5 and will auto flush & close themselves

}

================================================
FILE: source/Engine/Logger.hpp
================================================
/**

* \file
* \author Rudy Castan
* \author Jonathan Holmes
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#pragma once
#include <chrono>
#include <fstream>
#include <map>
#include <string>

namespace CS230
{
    class Logger
    {
    public:
        enum class Severity
        {
            Verbose, // Minor messages
            Debug,   // Only used while actively debugging
            Event,   // General event, like key press or state change
            Error    // Errors, such as file load errors
        };
        Logger(Severity severity, bool use_console, std::chrono::system_clock::time_point start_time);

        void LogError(std::string text);
    
        void LogEvent(std::string text);
    
        void LogDebug(std::string text);
    
        void LogVerbose(std::string text);
    
    private:
        Severity                              min_level;
        std::ofstream                         out_stream;
        std::chrono::system_clock::time_point start_time;
        void                                  log(Severity severity, std::string message);
        double                                seconds_since_start();
    };

}

================================================
FILE: source/Engine/Matrix.cpp
================================================
/**

* \file
* \author Rudy Castan
* \author Jonathan Holmes
* \author Taekyung ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#include "Matrix.hpp"
#include <cmath>

namespace Math
{
    TransformationMatrix::TransformationMatrix()
    {
        Reset();
    }

    double* TransformationMatrix::operator[](int index)
    {
        return const_cast<double*>((static_cast<TransformationMatrix const&>(*this))[index]);
    }
    
    const double* TransformationMatrix::operator[](int index) const
    {
        return matrix[index];
    }
    
    TransformationMatrix TransformationMatrix::operator*(TransformationMatrix m) const
    {
        TransformationMatrix result;
    
        result.matrix[0][0] = matrix[0][0] * m[0][0] + matrix[0][1] * m[1][0] + matrix[0][2] * m[2][0];
        result.matrix[0][1] = matrix[0][0] * m[0][1] + matrix[0][1] * m[1][1] + matrix[0][2] * m[2][1];
        result.matrix[0][2] = matrix[0][0] * m[0][2] + matrix[0][1] * m[1][2] + matrix[0][2] * m[2][2];
        result.matrix[1][0] = matrix[1][0] * m[0][0] + matrix[1][1] * m[1][0] + matrix[1][2] * m[2][0];
        result.matrix[1][1] = matrix[1][0] * m[0][1] + matrix[1][1] * m[1][1] + matrix[1][2] * m[2][1];
        result.matrix[1][2] = matrix[1][0] * m[0][2] + matrix[1][1] * m[1][2] + matrix[1][2] * m[2][2];
        result.matrix[2][0] = matrix[2][0] * m[0][0] + matrix[2][1] * m[1][0] + matrix[2][2] * m[2][0];
        result.matrix[2][1] = matrix[2][0] * m[0][1] + matrix[2][1] * m[1][1] + matrix[2][2] * m[2][1];
        result.matrix[2][2] = matrix[2][0] * m[0][2] + matrix[2][1] * m[1][2] + matrix[2][2] * m[2][2];
    
        return result;
    }
    
    TransformationMatrix TransformationMatrix::Inverse() const
    {
        TransformationMatrix inv;
    
        const double m00 = matrix[0][0]; const double m01 = matrix[0][1]; const double m02 = matrix[0][2];
        const double m10 = matrix[1][0]; const double m11 = matrix[1][1]; const double m12 = matrix[1][2];
        const double m20 = matrix[2][0]; const double m21 = matrix[2][1]; const double m22 = matrix[2][2];
    
        double det = m00 * (m11 * m22 - m12 * m21) 
                   - m01 * (m10 * m22 - m12 * m20) 
                   + m02 * (m10 * m21 - m11 * m20);
    
        if (std::abs(det) < 1e-5) 
        {
            inv.Reset(); 
            return inv;
        }
    
        double invDet = 1.0 / det;
        // Row 0
        inv[0][0] =  (m11 * m22 - m12 * m21) * invDet;
        inv[0][1] = -(m01 * m22 - m02 * m21) * invDet; // Transposed indices (0,1 -> cofactor of 1,0)
        inv[0][2] =  (m01 * m12 - m02 * m11) * invDet; 
    
        // Row 1
        inv[1][0] = -(m10 * m22 - m12 * m20) * invDet;
        inv[1][1] =  (m00 * m22 - m02 * m20) * invDet;
        inv[1][2] = -(m00 * m12 - m02 * m10) * invDet;
    
        // Row 2
        inv[2][0] =  (m10 * m21 - m11 * m20) * invDet;
        inv[2][1] = -(m00 * m21 - m01 * m20) * invDet;
        inv[2][2] =  (m00 * m11 - m01 * m10) * invDet;
    
        return inv;
    }
    
    
    TransformationMatrix& TransformationMatrix::operator*=(TransformationMatrix m)
    {
        (*this) = (*this) * m;
        return (*this);
    }
    
    vec2 TransformationMatrix::operator*(vec2 v) const
    {
        Math::vec2 result;
        result.x = matrix[0][0] * v.x + matrix[0][1] * v.y + matrix[0][2];
        result.y = matrix[1][0] * v.x + matrix[1][1] * v.y + matrix[1][2];
        return result;
    }
    
    vec3 TransformationMatrix::operator*(vec3 v) const
    {
        Math::vec3 result;
        result.x = matrix[0][0] * v.x + matrix[0][1] * v.y + matrix[0][2] * v.x;
        result.y = matrix[1][0] * v.x + matrix[1][1] * v.y + matrix[1][2] * v.z;
        return result;
    }
    
    void TransformationMatrix::Reset()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                matrix[i][j] = 0;
            }
        }
        matrix[0][0] = 1.0;
        matrix[1][1] = 1.0;
        matrix[2][2] = 1.0;
    }
    
    TranslationMatrix::TranslationMatrix(ivec2 translate)
    {
        Reset();
        matrix[0][2] = translate.x;
        matrix[1][2] = translate.y;
    }
    
    TranslationMatrix::TranslationMatrix(vec2 translate)
    {
        Reset();
        matrix[0][2] = translate.x;
        matrix[1][2] = translate.y;
    }
    
    RotationMatrix::RotationMatrix(double theta)
    {
        Reset();
        matrix[0][0] = std::cos(theta);
        matrix[0][1] = -std::sin(theta);
        matrix[1][0] = std::sin(theta);
        matrix[1][1] = std::cos(theta);
    }
    
    ScaleMatrix::ScaleMatrix(double scale)
    {
        Reset();
        matrix[0][0] *= scale;
        matrix[1][1] *= scale;
    }
    
    ScaleMatrix::ScaleMatrix(vec2 scale)
    {
        Reset();
        matrix[0][0] *= scale.x;
        matrix[1][1] *= scale.y;
    }

}

================================================
FILE: source/Engine/Matrix.hpp
================================================
/**

* \file
* \author Rudy Castan
* \author Jonathan Holmes
* \author Taekyung ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#pragma once
#include "Vec2.hpp"

namespace Math
{
    class TransformationMatrix
    {
    public:
        TransformationMatrix();

        double* operator[](int index);
    
        const double* operator[](int index) const;
    
        TransformationMatrix operator*(TransformationMatrix m) const;
        TransformationMatrix Inverse() const;
    
        TransformationMatrix& operator*=(TransformationMatrix m);
        vec2                  operator*(vec2 v) const;
        vec3                  operator*(vec3 v) const;
        void                  Reset();
    
    
    protected:
        double matrix[3][3];
    };
    
    class TranslationMatrix : public TransformationMatrix
    {
    public:
        TranslationMatrix(ivec2 translate);
        TranslationMatrix(vec2 translate);
    };
    
    class RotationMatrix : public TransformationMatrix
    {
    public:
        RotationMatrix(double theta);
    };
    
    class ScaleMatrix : public TransformationMatrix
    {
    public:
        ScaleMatrix(double scale);
        ScaleMatrix(vec2 scale);
    };
    
    inline static bool IsIdentityMatrix(const Math::TransformationMatrix& mat)
    {
        return mat[0][0] == 1.0 && mat[0][1] == 0.0 && mat[0][2] == 0.0 && mat[1][0] == 0.0 && mat[1][1] == 1.0 && mat[1][2] == 0.0 && mat[2][0] == 0.0 && mat[2][1] == 0.0 && mat[2][2] == 1.0;
    }

}

================================================
FILE: source/Engine/Particle.cpp
================================================
#include "Particle.h"
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Particle.cpp
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    June 6, 2025
*/

namespace CS230 {
    Particle::Particle(const std::filesystem::path& sprite_file) : 

        GameObject({0,0}),
        life(0.0)
    {
        AddGOComponent(new Sprite(sprite_file, this));
    }
    
    
    void Particle::Start(Math::vec2 _position, Math::vec2 _velocity, double max_life, CS200::RGBA _color)
    {
        SetPosition(_position);
        SetVelocity(_velocity);
        life = max_life;
        real_color = _color;
        GetGOComponent<Sprite>()->PlayAnimation(0);
    }
    
    void Particle::Update(double dt) {
        if (Alive()) {
            life -= dt;
            //Engine::GetLogger().LogDebug(std::to_string(life));
            GameObject::Update(dt);
        }
    }
    
    void Particle::Draw(Math::TransformationMatrix camera_matrix, [[maybe_unused]]unsigned int color, float depth)
    {
        if (Alive()) {
            GameObject::Draw(camera_matrix, real_color, depth);
        }
    }

}

================================================
FILE: source/Engine/Particle.h
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Particle.h
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    June 6, 2025
*/
#pragma once
#include "../Game/GameObjectTypes.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "GameStateManager.hpp"

namespace CS230
{
    class Particle : public GameObject
    {
    public:
        Particle(const std::filesystem::path& sprite_file);
        void Start(Math::vec2 _position, Math::vec2 _velocity, double max_life, CS200::RGBA _color = CS200::WHITE);
        void Update(double dt) override;
        void Draw(Math::TransformationMatrix camera_matrix, unsigned int color = 0xFFFFFFFF, float depth = 0.5f) override;

        int DrawPriority() const override
        {
            return 70;
        }
        bool Alive()
        {
            return life > 0;
        }
    
        GameObjectTypes Type() override
        {
            return GameObjectTypes::Particle;
        }
    
    private:
        double life;
        CS200::RGBA real_color;
    };
    
    template <typename T>
    class ParticleManager : public Component
    {
    public:
        ParticleManager();
        ~ParticleManager();
        void Emit(size_t count, Math::vec2 emitter_position, Math::vec2 emitter_velocity, Math::vec2 direction, double spread, CS200::RGBA = CS200::WHITE);
    
    private:
        std::vector<T*> particles;
        size_t             index;
    };
    
    template <typename T>
    inline ParticleManager<T>::ParticleManager() : index(0)
    {
        int max_count = T::MaxCount;
        auto game_object_mamager = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>();
        for (int i = 0; i < max_count; ++i)
        {
            T* new_particle = new T();
    
            game_object_mamager->Add(new_particle);
    
            particles.push_back(new_particle);
        }
    }
    
    template <typename T>
    inline ParticleManager<T>::~ParticleManager()
    {
        //for (T* particle : particles)
        //{
        //    particle->Destroy();
        //}
        particles.clear();
    }
    
    template <typename T>
    inline void ParticleManager<T>::Emit(size_t count, Math::vec2 emitter_position, Math::vec2 emitter_velocity, Math::vec2 direction, double spread, CS200::RGBA color)
    {
        for (size_t i = 0; i < count; ++i)
        {
            if ((particles[i])&&(particles[i]->Alive()))
            {
                Engine::GetLogger().LogEvent("Particle overwritten");
            }
            double angle_variation = 0.0;
            if (spread != 0)
            {
                angle_variation = static_cast<double>((rand() % static_cast<int>(spread * 1024)) / 1024) - spread / 2;
            }
            Math::vec2 random_magnitude  = direction * static_cast<double>(static_cast<float>((rand() % 1024) / 2048) + 0.5f);
            Math::vec2 particle_velocity = Math::RotationMatrix(angle_variation) * random_magnitude + emitter_velocity;
            particles[index]->Start(emitter_position, particle_velocity, T::MaxLife,color);
    
            ++index;
            if (index >= particles.size())
            {
                index = 0;
            }
        }
    }

}

================================================
FILE: source/Engine/Path.cpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "Path.hpp"

#include <SDL.h>
#include <optional>

namespace
{
    std::optional<std::filesystem::path> try_get_asset_path(const std::filesystem::path& starting_directory)
    {
        namespace fs                 = std::filesystem;
        fs::path       assets_parent = fs::absolute(starting_directory);
        const fs::path root          = assets_parent.root_path();

        // note that the do while loop is needed because on the web platform the starting folder is the root and that's also where the assets folder should be
        do
        {
            const fs::path assets_folder = assets_parent / "Assets";
            if (fs::is_directory(assets_folder))
            {
                return assets_parent;
            }
            // if assets not found then try looking the in parent folder
            assets_parent = assets_parent.parent_path();
        } while (assets_parent != root);
    
        return std::nullopt;
    }

}

namespace assets
{

    std::filesystem::path get_base_path()
    {
        namespace fs                  = std::filesystem;
        static fs::path assets_folder = []()
        {
            auto result = try_get_asset_path(fs::current_path());
            if (result)
                return result.value();
            // try from the exe path rather than the current working directory
            const auto base_path = SDL_GetBasePath();
            result               = try_get_asset_path(base_path);
            SDL_free(base_path);
            if (result)
                return result.value();
            throw std::runtime_error{ "Failed to find Assets folder in parent folders" };
        }();
        return assets_folder;
    }
    
    std::filesystem::path locate_asset(const std::filesystem::path& asset_path)
    {
        auto asset_filepath = asset_path;
        if (!std::filesystem::exists(asset_filepath))
        {
            // try prepending the asset directory path
            asset_filepath = get_base_path() / asset_filepath;
            if (!std::filesystem::exists(asset_filepath))
            {
                throw std::runtime_error("Failed to locate asset: " + asset_path.string());
            }
        }
        return asset_filepath;
    }

}

================================================
FILE: source/Engine/Path.hpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once

#include <filesystem>

namespace assets
{

    std::filesystem::path get_base_path();
    std::filesystem::path locate_asset(const std::filesystem::path& asset_path);

}

================================================
FILE: source/Engine/Random.cpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "Random.hpp"

#include <cassert>
#include <chrono>
#include <random>
#include <thread>

namespace
{
    using namespace std;
    using namespace chrono;

    mt19937_64& Engine()
    {
        thread_local static mt19937_64 engine{ static_cast<mt19937_64::result_type>(system_clock::now().time_since_epoch().count()) + hash<thread::id>{}(this_thread::get_id()) };
        return engine;
    }

}

namespace util
{
    double random(double min_inclusive, double max_exclusive) noexcept
    {
        assert(min_inclusive < max_exclusive);
        return std::uniform_real_distribution<double>(min_inclusive, max_exclusive)(Engine());
    }

    int random(int min_inclusive, int max_exclusive) noexcept
    {
        assert(min_inclusive < max_exclusive - 1);
        return std::uniform_int_distribution<int>(min_inclusive, max_exclusive - 1)(Engine());
    }
    
    int random(int max_exclusive) noexcept
    {
        return random(0, max_exclusive);
    }

}

================================================
FILE: source/Engine/Random.hpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once

namespace util
{
    double random(double min_inclusive = 0.0, double max_exclusive = 1.0) noexcept;
    int    random(int min_inclusive, int max_exclusive) noexcept;
    int    random(int max_exclusive) noexcept;
}

================================================
FILE: source/Engine/Rect.hpp
================================================
 /**

* \file

* \author Rudy Castan

* \author Jonathan Holmes

* \author Taekyung Ho

* \date 2025 Fall

* \par CS200 Computer Graphics I

* \copyright DigiPen Institute of Technology
  */
  
  #pragma once
  #include "Vec2.hpp"
  #include <algorithm>
  
  namespace Math
  {
   struct [[nodiscard]] rect
   {
  
       Math::vec2 point_1{ 0.0, 0.0 };
       Math::vec2 point_2{ 0.0, 0.0 };
      
       double Left() const noexcept
       {
           return std::min(point_1.x, point_2.x);
       }
      
       double Right() const noexcept
       {
           return std::max(point_1.x, point_2.x);
       }
      
       double Top() const noexcept
       {
           return std::max(point_1.y, point_2.y);
       }
      
       double Bottom() const noexcept
       {
           return std::min(point_1.y, point_2.y);
       }
      
       Math::vec2 Center() const noexcept{
          return {(Left() + Right()) * 0.5, (Top() + Bottom()) * 0.5};
       }
       Math::vec2 Size() const noexcept
       {
           return { Right() - Left(), Top() - Bottom() };
       }
  
   };
  
   struct [[nodiscard]] irect
   {
  
       Math::ivec2 point_1{ 0, 0 };
       Math::ivec2 point_2{ 0, 0 };
      
       int Left() const noexcept
       {
           return std::min(point_1.x, point_2.x);
       }
      
       int Right() const noexcept
       {
           return std::max(point_1.x, point_2.x);
       }
      
       int Top() const noexcept
       {
           return std::max(point_1.y, point_2.y);
       }
      
       int Bottom() const noexcept
       {
           return std::min(point_1.y, point_2.y);
       }
      
       Math::ivec2 Size() const noexcept
       {
           return { Right() - Left(), Top() - Bottom() };
       }
  
   };
  }

================================================
FILE: source/Engine/ShowCollision.cpp
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  ShowCollision.cpp
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    May 17, 2025
*/
#include "ShowCollision.h"
#include "Input.hpp"

CS230::ShowCollision::ShowCollision() : enabled(true) {}

void CS230::ShowCollision::Update([[maybe_unused]]double dt) {
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Tab) == true) {
        enabled = !enabled;
    }
}

bool CS230::ShowCollision::Enabled() {
    return enabled;
}

================================================
FILE: source/Engine/ShowCollision.h
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  ShowCollision.h
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    May 17, 2025
*/
#pragma once
#include "Component.h"
#include "Engine.hpp"
namespace CS230 {
    class ShowCollision : public CS230::Component {
    public:
        ShowCollision();
        void Update(double dt) override;
        bool Enabled();
    private:
        bool enabled;
    };
}

================================================
FILE: source/Engine/Sprite.cpp
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Sprite.cpp
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    March 19, 2025
*/

#include "GameObject.h"
#include "Sprite.h"
#include "TextureManager.hpp"
#include "Logger.hpp"
#include "Path.hpp"
#include <fstream>

CS230::Sprite::Sprite(const std::filesystem::path& sprite_file, GameObject* _given_object) {
    Load(sprite_file, _given_object);
}

CS230::Sprite::~Sprite()
{
    for (Animation* animation : animations) {
        delete animation;
    }
    animations.clear();
}

CS230::Sprite::Sprite(Sprite&& temporary) noexcept :
    texture(std::move(temporary.texture)),
    hotspots(std::move(temporary.hotspots)),
    current_animation(temporary.current_animation),
    frame_size(temporary.frame_size),
    frame_texels(std::move(temporary.frame_texels)),
    animations(std::move(temporary.animations))
{}

CS230::Sprite& CS230::Sprite::operator=(Sprite && temporary) noexcept
{
    std::swap(texture, temporary.texture);
    std::swap(hotspots, temporary.hotspots);
    std::swap(current_animation, temporary.current_animation);
    std::swap(frame_size, temporary.frame_size);
    std::swap(frame_texels, frame_texels);
    std::swap(animations, temporary.animations);
    return *this;
}

void CS230::Sprite::Update(double dt)
{
    animations[current_animation]->Update(dt);
}

void CS230::Sprite::Load(const std::filesystem::path& sprite_file, GameObject* _given_object)
{
    const std::filesystem::path sprite_path = assets::locate_asset(sprite_file);
    given_object = _given_object;
    animations.clear();
    if (sprite_path.extension() != ".spt")
    {
        throw std::runtime_error(sprite_path.generic_string() + " is not a .spt file");
    }

    std::ifstream               in_file(sprite_path);
    
    if (in_file.is_open() == false) {
        throw std::runtime_error("Failed to load " + sprite_path.generic_string());
    }
    
    hotspots.clear();
    frame_texels.clear();
    
    std::string text;
    in_file >> text;
    texture = Engine::GetTextureManager().Load(text);
    frame_size = Engine::GetTextureManager().Load(text)->GetSize();
    
    in_file >> text;
    while (in_file.eof() == false) {
        if (text == "FrameSize") {
            in_file >> frame_size.x;
            in_file >> frame_size.y;
        }
    
        else if (text == "NumFrames") {
            int frame_count;
            in_file >> frame_count;
            for (int i = 0; i < frame_count; i++) {
                frame_texels.push_back({ frame_size.x * i, 0 });
            }
        }
        else if (text == "Frame") {
            int frame_location_x, frame_location_y;
            in_file >> frame_location_x;
            in_file >> frame_location_y;
            frame_texels.push_back({ frame_location_x, frame_location_y });
        }
        else if (text == "HotSpot") {
            int hotspot_x, hotspot_y;
            in_file >> hotspot_x;
            in_file >> hotspot_y;
            hotspots.push_back({ hotspot_x, hotspot_y });
        }
        else if (text == "Anim") {
            in_file >> text;
            animations.push_back(new Animation(text));
        }
        else if (text == "RectCollision") {
            Math::irect boundary;
            in_file >> boundary.point_1.x >> boundary.point_1.y >> boundary.point_2.x >> boundary.point_2.y;
            if (given_object == nullptr) {
                Engine::GetLogger().LogError("Cannot add collision to a null object");
            }
            else {
                given_object->AddGOComponent(new RectCollision(boundary, given_object));
            }
        }
        else if (text == "CircleCollision") {
            double radius;
            in_file >> radius;
            if (given_object == nullptr) {
                Engine::GetLogger().LogError("Cannot add collision to a null object");
            }
            else {
                given_object->AddGOComponent(new CircleCollision(radius, given_object));
            }
        }
        else {
            Engine::GetLogger().LogError("Unknown command: " + text);
        }
        in_file >> text;
    }
    if (frame_texels.empty() == true) {
        frame_texels.push_back({ 0,0 });
    }
    
    if (animations.empty() == true) {
        animations.push_back(new Animation());
        PlayAnimation(0);
    }

}

void CS230::Sprite::Draw(Math::TransformationMatrix display_matrix, unsigned int color, float depth)
{
    texture->Draw(display_matrix * Math::TranslationMatrix(-GetHotSpot(0)), GetFrameTexel(animations[current_animation]->CurrentFrame()), GetFrameSize(), color,depth);
}

Math::ivec2 CS230::Sprite::GetHotSpot(size_t index)
{
    if ( index > hotspots.size()) {
        Engine::GetLogger().LogDebug("Invalid index in hospot!");
        return Math::ivec2{ 0,0 };
    }
    return hotspots[index];
}

Math::ivec2 CS230::Sprite::GetFrameSize()
{
    return frame_size;
}

void CS230::Sprite::PlayAnimation(size_t animation)
{
    if (animation >= animations.size()) {
        Engine::GetLogger().LogDebug("Invalid index in animation!");
        current_animation = 0;
        return;
    }
    current_animation = animation;
    animations[current_animation]->Reset();
}

bool CS230::Sprite::AnimationEnded()
{
    return animations[current_animation]->Ended();
}

Math::ivec2 CS230::Sprite::GetFrameTexel(size_t index) const
{
    if ( index >= frame_texels.size()) {
        Engine::GetLogger().LogDebug("Invalid index in frametexles!");
        return Math::ivec2{ 0,0 };
    }
    return frame_texels[index];
}

================================================
FILE: source/Engine/Sprite.h
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Sprite.h
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    March 19, 2025
*/

#pragma once
#include <string>
#include "Vec2.hpp"
#include "Texture.hpp"
#include "Matrix.hpp"
#include "Engine.hpp"
#include "Animation.h"
#include "Component.h"
#include "Collision.h"

namespace CS230 {
    class GameObject;
    class Sprite : public Component {
    public:
        Sprite(const std::filesystem::path& sprite_file,GameObject* given_object);
        ~Sprite();

        Sprite(const Sprite&) = delete;
        Sprite& operator=(const Sprite&) = delete;
    
        Sprite(Sprite&& temporary) noexcept;
        Sprite& operator=(Sprite&& temporary) noexcept;
        void Update(double dt) override;
        void Load(const std::filesystem::path& sprite_file, GameObject* _given_object);
        void        Draw(Math::TransformationMatrix display_matrix, unsigned int color = 0xFFFFFFFF, float depth = 0.5f);
        Math::ivec2 GetHotSpot(size_t index);
        Math::ivec2 GetFrameSize();
    
        void PlayAnimation(size_t animation);
        bool AnimationEnded();
    
        const size_t& CurrentAnimation() const { return current_animation; }
    private:
        Math::ivec2 GetFrameTexel(size_t index) const;
        // Texture* texture;
        std::shared_ptr<CS230::Texture> texture;
        std::vector<Math::ivec2> hotspots;
    
        size_t current_animation;
        Math::ivec2 frame_size;
        std::vector<Math::ivec2> frame_texels;
        std::vector<Animation*> animations;
    
        GameObject* given_object;
    };

}

================================================
FILE: source/Engine/TextManager.cpp
================================================
#include "TextManager.hpp"

void TextManager::DrawText(const std::string& text, const Math::vec2& position, Fonts font, const Math::vec2& scale, CS200::RGBA color) const
{
    if (auto text_texture = fonts[font]->PrintToTexture(text, color); text_texture)
    {
        const auto transform = Math::TranslationMatrix(position) * Math::ScaleMatrix(scale);
        text_texture->Draw(transform, color);
    }
}

void TextManager::Init()
{
    add_font("Assets/fonts/Font_Simple.png");
    add_font("Assets/fonts/Font_Outlined.png");
}

void TextManager::add_font(const std::filesystem::path& file_name)
{
    fonts.push_back(std::make_unique<CS230::Font>(file_name));
}

================================================
FILE: source/Engine/TextManager.hpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par GAM200 Engine Porting
* \copyright DigiPen Institute of Technology
  */
  #include "Font.hpp"
  #include "Fonts.h"
  #include <memory>
  #include <vector>

class TextManager
{
public:
    TextManager() = default;
    void Init();
    void DrawText(const std::string& text, const Math::vec2& position, Fonts font, const Math::vec2& scale = { 1.0, 1.0 }, CS200::RGBA color = CS200::WHITE) const;

private:
    // static CS230::Font* get_font(size_t);

    void add_font(const std::filesystem::path& file_name);
    
    std::vector<std::unique_ptr<CS230::Font>> fonts{};

};

================================================
FILE: source/Engine/Texture.cpp
================================================
/**

* \file
* \author Rudy Castan
* \author Jonathan Holmes
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#include "Texture.hpp"

#include "CS200/IRenderer2D.hpp"
#include "CS200/Image.hpp"
#include "Engine.hpp"
#include "Matrix.hpp"
#include "OpenGL/GL.hpp"
#include "TextureManager.hpp"
#include "Window.hpp"

namespace CS230
{

    void Texture::Draw([[maybe_unused]] const Math::TransformationMatrix& display_matrix, unsigned int color, float depth)
    {
        Draw(display_matrix, { 0, 0 }, image_size, color, depth);
    }
    
    void Texture::Draw(const Math::TransformationMatrix& display_matrix, Math::ivec2 texel_position, Math::ivec2 frame_size, unsigned int color, float depth)
    {
        CS200::IRenderer2D* renderer = Engine::GetTextureManager().GetRenderer2D();
    
    
        // OpenGL Texture: (0,0) Bottom-Left
        // Image Pixel: (0,0) Top-Left
        const double u_left      = static_cast<double>(texel_position.x) / image_size.x;
        const double u_right  = static_cast<double>(texel_position.x + frame_size.x) / image_size.x;
        // V_top  = 1.0 - (y / height)
        // V_bottom  = 1.0 - ((y + h) / height)
        const double v_top      = 1.0 - (static_cast<double>(texel_position.y) / image_size.y);
        const double v_bottom = 1.0 - (static_cast<double>(texel_position.y + frame_size.y) / image_size.y);
    
        const Math::vec2 texel_coord_bl = { u_left, v_bottom };
        const Math::vec2 texel_coord_tr = { u_right, v_top };
    
        Math::vec2 set_bottom_left{ frame_size.x * 0.5, frame_size.y * 0.5 };
        const auto world_transformation = display_matrix * Math::TranslationMatrix(set_bottom_left) * Math::ScaleMatrix(frame_size);
    
        renderer->DrawQuad(world_transformation, textureHandle, texel_coord_bl, texel_coord_tr, color, depth);
    }
    
    Math::ivec2 Texture::GetSize() const
    {
        return image_size;
    }
    
    Texture::~Texture()
    {
        GL::DeleteTextures(1, &textureHandle), textureHandle = 0;
    }
    
    Texture::Texture(Texture&& temporary) noexcept : image_size{ std::move(temporary.image_size) }, textureHandle{ std::move(temporary.textureHandle) }
    {
        temporary.textureHandle = 0;
        temporary.image_size    = { 0, 0 };
    }
    
    Texture& Texture::operator=(Texture&& temporary) noexcept
    {
        std::swap(image_size, (temporary.image_size));
        std::swap(textureHandle, temporary.textureHandle);
        return *this;
    }
    
    Texture::Texture(const std::filesystem::path& file_name)
    {
        const auto image = CS200::Image{ file_name, true };
        image_size         = image.GetSize();
        textureHandle     = OpenGL::CreateTextureFromImage(image, OpenGL::Filtering::NearestPixel, OpenGL::Wrapping::ClampToEdge);
    }
    
    Texture::Texture([[maybe_unused]] OpenGL::TextureHandle given_texture, [[maybe_unused]] Math::ivec2 the_size) : image_size{ the_size }, textureHandle{ given_texture }
    {
    }

}

================================================
FILE: source/Engine/Texture.hpp
================================================
/**

* \file
* \author Rudy Castan
* \author Jonathan Holmes
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#pragma once

#include "CS200/Image.hpp"
#include "Matrix.hpp"
#include "OpenGL/Texture.hpp"
#include <filesystem>
#include <memory>

#include "Vec2.hpp"

namespace CS230
{
    class Font;

    /**
     * \brief High-level texture wrapper for 2D graphics rendering and resource management
     *
     * Texture provides a convenient, RAII-compliant wrapper around OpenGL texture objects
     * that simplifies texture loading, rendering, and resource management. The class handles
     * the complex details of OpenGL texture creation, coordinate system transformations,
     * and automatic memory cleanup while providing an intuitive interface for 2D graphics.
     *
     * Key Features:
     * - Automatic texture loading from image files with proper format conversion
     * - RAII resource management ensuring textures are properly cleaned up
     * - High-level drawing interface with transformation matrix support
     * - Sprite sheet support for animation and texture atlases
     * - Integration with the 2D renderer for efficient batched rendering
     * - Move semantics for efficient texture transfers and storage
     *
     * Resource Management:
     * The texture automatically handles OpenGL texture creation and deletion through
     * RAII principles. Move-only semantics prevent accidental texture duplication
     * while allowing efficient transfer of texture ownership between objects.
     *
     * Coordinate Systems:
     * The class handles the conversion between different coordinate systems:
     * - Image coordinates (pixel-based, top-left origin)
     * - Texture coordinates (normalized 0-1 range, bottom-left origin)
     * - World coordinates (transformation matrix-based positioning)
     *
     * Common Use Cases:
     * - Sprite rendering for games and interactive applications
     * - UI element graphics and interface components
     * - Texture atlas rendering for efficient sprite animation
     * - Background and environment art rendering
     * - Font glyph rendering (through Font class integration)
     *
     * The texture integrates seamlessly with the engine's transformation system,
     * allowing for easy scaling, rotation, and positioning of graphics elements.
     */
    class Texture
    {
    public:
    
    
        friend class TextureManager;
        friend class Font;
    
        /**
         * \brief Draw the entire texture with transformation and color tinting
         * \param display_matrix Transformation matrix for positioning, scaling, and rotation
         * \param color RGBA color value for tinting the texture (default: white/no tint)
         *
         * Renders the complete texture to the screen using the provided transformation
         * matrix to control positioning, scaling, and rotation. This is the primary
         * method for drawing sprites, UI elements, and other texture-based graphics.
         *
         * Transformation Handling:
         * The method automatically handles the necessary coordinate system conversions
         * and applies appropriate scaling and translation to ensure the texture appears
         * correctly positioned according to the transformation matrix. The texture is
         * drawn with its center as the transformation origin.
         *
         * Color Tinting:
         * The color parameter allows for real-time tinting of the texture without
         * modifying the original image data. This enables effects like:
         * - Color-based visual feedback (damage flashing, selection highlighting)
         * - Transparency and fade effects through alpha channel modification
         * - Uniform lighting or environmental color effects
         * - UI state visualization (disabled buttons, hover states)
         *
         * Rendering Integration:
         * The method integrates with the engine's 2D renderer for efficient batched
         * rendering, automatically managing texture binding and shader state for
         * optimal performance when drawing multiple textures.
         */
        void Draw(const Math::TransformationMatrix& display_matrix, unsigned int color = 0xFFFFFFFF, float depth = 0.6f);
    
        /**
         * \brief Draw a rectangular region of the texture (sprite sheet support)
         * \param display_matrix Transformation matrix for positioning, scaling, and rotation
         * \param texel_position Top-left corner position in pixel coordinates within the texture
         * \param frame_size Size of the region to draw in pixels
         * \param color RGBA color value for tinting the texture (default: white/no tint)
         *
         * Renders a specific rectangular region of the texture, enabling sprite sheet
         * functionality, texture atlases, and animation frame rendering. This method
         * is essential for efficient graphics where multiple sprites or animation
         * frames are packed into a single texture file.
         *
         * Sprite Sheet Applications:
         * - Character animation frames stored in a grid layout
         * - UI element collections (buttons, icons, decorative elements)
         * - Tile sets for 2D game environments
         * - Font glyph rendering from character atlases
         * - Particle effect textures with multiple variations
         *
         * Coordinate System:
         * The texel_position uses pixel coordinates with (0,0) at the top-left
         * of the texture, following standard image coordinate conventions. The
         * method automatically converts these to the appropriate OpenGL texture
         * coordinates for rendering.
         *
         * Performance Benefits:
         * Using sprite sheets reduces texture binding overhead and improves
         * rendering performance by allowing multiple related graphics to be
         * stored in a single texture object, enabling more efficient batching.
         *
         * The transformation matrix affects the final rendered size and position,
         * while frame_size determines which portion of the texture is sampled.
         */
        void Draw(const Math::TransformationMatrix& display_matrix, Math::ivec2 texel_position, Math::ivec2 frame_size, unsigned int color = 0xFFFFFFFF, float depth = 0.f);
    
        /**
         * \brief Get the dimensions of the texture in pixels
         * \return Vector containing width and height of the texture
         *
         * Returns the original size of the texture as loaded from the image file,
         * providing essential information for layout calculations, collision detection,
         * and coordinate system conversions. This size information is particularly
         * useful when working with sprite sheets or when precise positioning is required.
         *
         * Common uses:
         * - Calculating sprite sheet frame positions and sizes
         * - Determining collision boundaries for texture-based objects
         * - Computing appropriate scaling factors for different screen resolutions
         * - Layout calculations for UI elements and text rendering
         * - Animation frame calculations and sprite positioning
         *
         * The returned size reflects the texture's native resolution and remains
         * constant regardless of how the texture is drawn or transformed during rendering.
         */
        Math::ivec2 GetSize() const;
    
        /**
         * \brief Destructor ensuring proper OpenGL resource cleanup
         *
         * Automatically releases the underlying OpenGL texture object when the
         * Texture instance is destroyed, preventing GPU memory leaks and ensuring
         * proper resource management. This follows RAII principles to guarantee
         * cleanup even in the presence of exceptions or early returns.
         */
        ~Texture();
    
        /**
         * \brief Get the underlying OpenGL texture handle for advanced operations
         * \return OpenGL texture handle for direct OpenGL operations
         *
         * Provides access to the raw OpenGL texture handle for advanced rendering
         * operations that require direct OpenGL texture binding or integration
         * with custom rendering systems. This method should be used sparingly
         * and only when the high-level interface is insufficient.
         *
         * Advanced use cases:
         * - Integration with custom shader programs
         * - Direct OpenGL texture operations
         * - Interfacing with third-party graphics libraries
         * - Performance-critical rendering paths that bypass the 2D renderer
         *
         * Handle Ownership:
         * The returned handle remains owned by the Texture object and should not
         * be manually deleted or modified. The handle becomes invalid when the
         * Texture object is destroyed.
         */
        [[nodiscard]] OpenGL::TextureHandle GetHandle() const
        {
            return textureHandle;
        }
    
    
    private:
        // Private constructors - textures can only be created through TextureManager or Font
        // This ensures proper resource management and prevents accidental texture duplication
        explicit Texture(const std::filesystem::path& file_name);
        // for new texture!! check texturemanager!!
        Texture(OpenGL::TextureHandle given_texture, Math::ivec2 the_size);
    
    
    public:
        /**
         * \brief Deleted copy constructor and assignment operator
         *
         * Textures use move-only semantics to prevent accidental duplication of
         * OpenGL resources. Copying textures would require expensive GPU operations
         * and could lead to resource management complications, so copy operations
         * are explicitly disabled to encourage efficient resource usage patterns.
         */
        Texture(const Texture&)               = delete;
        Texture& operator=(const Texture&) = delete;
    
        /**
         * \brief Move constructor for efficient texture transfer
         * \param temporary Texture object to move from (will be left in valid but empty state)
         *
         * Efficiently transfers ownership of the OpenGL texture resource from one
         * Texture object to another without copying GPU data. The source texture
         * is left in a safe, destructible state with no valid texture handle.
         *
         * Move semantics enable:
         * - Efficient storage of textures in containers (std::vector, std::map)
         * - Return of textures from factory functions without copying
         * - Transfer of texture ownership between different systems
         * - Optimal performance when reorganizing texture collections
         */
        Texture(Texture&& temporary) noexcept;
    
        /**
         * \brief Move assignment operator for efficient texture replacement
         * \param temporary Texture object to move from (will be left in valid but empty state)
         * \return Reference to this texture after the move operation
         *
         * Replaces the current texture with another texture's resources using
         * efficient move semantics. The previous texture resource is properly
         * cleaned up, and the new resource is transferred without GPU data copying.
         *
         * The operation uses swap semantics to ensure exception safety and
         * guarantee that both the old and new textures are handled correctly
         * even if unexpected conditions occur during the transfer.
         */
        Texture& operator=(Texture&& temporary) noexcept;
    
    
    private:
    
    
        // CS200::Image image; // use initialize member list -> or it will be initialized with default ctor -> but it doesn't exist!!
        Math::ivec2              image_size;
        OpenGL::TextureHandle textureHandle;
    };

}

================================================
FILE: source/Engine/TextureManager.cpp
================================================
/**

* \file
* \author Rudy Castan
* \author Jonathan Holmes
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#include "TextureManager.hpp"
#include "CS200/IRenderer2D.hpp"
#include "CS200/NDC.hpp"
#include "Engine.hpp"
#include "Logger.hpp"
#include "OpenGL/GL.hpp"
#include "Path.hpp"
#include "Texture.hpp"
#include "Window.hpp"

namespace CS230
{
    std::shared_ptr<Texture> TextureManager::Load(const std::filesystem::path& file_name)
    {
        const std::filesystem::path file_path = assets::locate_asset(file_name);
        if (textures.find(file_path) == textures.end())
        {
            // textures[file_name] = new Texture(file_name);
            textures[file_path] = std::shared_ptr<Texture>(new Texture(file_path));

            Engine::GetLogger().LogEvent("Loading Texture: " + file_path.string());
        }
        return textures[file_path];
    }
    
    void TextureManager::Init()
    {
        current_renderer_type = RendererType::Immediate;
        // Create and initialize new renderer
        switch (current_renderer_type)
        {
            case RendererType::Immediate: renderer2D = std::make_unique<CS200::ImmediateRenderer2D>(); break;
            case RendererType::Batch: renderer2D = std::make_unique<CS200::BatchRenderer2D>(); break;
            case RendererType::Instanced: renderer2D = std::make_unique<CS200::InstancedRenderer2D>(); break;
            default: renderer2D = std::make_unique<CS200::ImmediateRenderer2D>(); break;
        }
    
        if (renderer2D)
        {
            renderer2D->Init();
        }
        else
        {
            throw std::runtime_error("renderer initialize failed!");
        }
    }
    
    void TextureManager::Unload()
    {
        for (std::pair<std::filesystem::path, std::shared_ptr<Texture>> texture : textures)
        {
            // delete texture.second;
            Engine::GetLogger().LogEvent("Unload Texture: " + texture.first.string());
        }
        textures.clear();
    }
    
    void TextureManager::StartRenderTextureMode([[maybe_unused]] int width, [[maybe_unused]] int height)
    {
        // auto& renderer_2d = Engine::GetRenderer2D();
        auto& render_info = get_render_info();
        //  * - Ends current 2D renderer scene to ensure clean state transition
        CS200::IRenderer2D* renderer_2d = GetRenderer2D();
        renderer_2d->EndScene();
    
        //  * - Creates OpenGL framebuffer with color attachment of specified dimensions
        render_info.Size   = { width, height };
        render_info.Target = OpenGL::CreateFramebufferWithColor(Math::ivec2{ width, height });
    
        //  * - Saves current viewport, clear color, and rendering state for restoration
        GL::GetFloatv(GL_COLOR_CLEAR_VALUE, render_info.ClearColor.data());
        GL::GetIntegerv(GL_VIEWPORT, render_info.Viewport.data());
    
        //  * - Sets up Y-flipped coordinate system for proper texture orientation
        const auto ndc_matrix = Math::ScaleMatrix({ 1.0, -1.0 }) * CS200::build_ndc_matrix(render_info.Size);
        renderer_2d->BeginScene(ndc_matrix);
    
        //  * - Binds framebuffer as render target, replacing screen rendering
        GL::BindFramebuffer(GL_FRAMEBUFFER, render_info.Target.Framebuffer);
        GL::Viewport(0, 0, render_info.Size.x, render_info.Size.y);
    
        //  * - Clears render target with transparent black (0,0,0,0) for clean start
        GL::ClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        GL::Clear(GL_COLOR_BUFFER_BIT);
    }
    
    std::shared_ptr<Texture> TextureManager::EndRenderTextureMode()
    {
        CS200::IRenderer2D* renderer_2d = GetRenderer2D();
        auto& render_info = get_render_info();
        // * Cleanup and Restoration Process:
        //  * - Ends current 2D renderer scene to flush any pending draw operations
        renderer_2d->EndScene();
        //  * - Unbinds framebuffer (returns to default screen framebuffer 0)
        GL::BindFramebuffer(GL_FRAMEBUFFER, 0);
        //  * - Restores original viewport dimensions from saved state
        GL::Viewport(render_info.Viewport[0], render_info.Viewport[1], render_info.Viewport[2], render_info.Viewport[3]);
        //  * - Restores original clear color values from saved state
        GL::ClearColor(render_info.ClearColor[0], render_info.ClearColor[1], render_info.ClearColor[2], render_info.ClearColor[3]);
        //  * - Begins new 2D renderer scene with screen-appropriate coordinate system
        renderer_2d->BeginScene(CS200::build_ndc_matrix(Engine::GetWindow().GetSize()));
        //  * - Deletes temporary framebuffer to free GPU resources
        auto framebuffer_to_delete = render_info.Target.Framebuffer;
        GL::DeleteFramebuffers(1, &framebuffer_to_delete);
    
    
        //          * Texture Creation:
        //  * Creates a new Texture object by wrapping the framebuffer's color attachment:
        auto scene_texture                   = new Texture(render_info.Target.ColorAttachment, render_info.Size);
        //  * - Transfers ownership of OpenGL texture ID from framebuffer to Texture object
        render_info.Target.ColorAttachment = 0; // old one
        //  * - Preserves original dimensions specified in StartRenderTextureMode()
        //  * - Maintains RGBA format with alpha channel for transparency support
        //  * - Content includes all drawing operations performed during render-to-texture mode
        return std::shared_ptr<Texture>(scene_texture);
    }
    
    void TextureManager::SwitchRenderer(RendererType type)
    {
        if (current_renderer_type == type)
            return; // Already using this renderer
    
        // Shutdown current renderer
        if (renderer2D)
        {
            renderer2D->Shutdown();
            renderer2D.reset();
        }
    
        // Create and initialize new renderer
        current_renderer_type = type;
        switch (type)
        {
            case RendererType::Immediate: renderer2D = std::make_unique<CS200::ImmediateRenderer2D>(); break;
            case RendererType::Batch: renderer2D = std::make_unique<CS200::BatchRenderer2D>(); break;
            case RendererType::Instanced: renderer2D = std::make_unique<CS200::InstancedRenderer2D>(); break;
            default: renderer2D = std::make_unique<CS200::ImmediateRenderer2D>(); break;
        }
    
        if (renderer2D)
        {
            renderer2D->Init();
        }
    }
    
    TextureManager::RendererType TextureManager::GetCurrentRendererType() const
    {
        return current_renderer_type;
    }
    
    CS200::IRenderer2D* TextureManager::GetRenderer2D()
    {
        return renderer2D.get();
    }
    
    void TextureManager::Shutdown()
    {
        renderer2D->Shutdown();
        renderer2D.reset();
    }

}

================================================
FILE: source/Engine/TextureManager.hpp
================================================

#pragma once
#include "CS200/BatchRenderer2D.hpp"
#include "CS200/InstancedRenderer2D.hpp"
#include "CS200/IRenderer2D.hpp"
#include "CS200/ImmediateRenderer2D.hpp"
#include "OpenGL/Framebuffer.hpp"
#include <filesystem>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

namespace CS230
{
    class Texture;

    class TextureManager
    {
    public:
        enum class RendererType
        {
            Immediate,
            Batch,
            Instanced
        };
    
        std::shared_ptr<Texture> Load(const std::filesystem::path& file_name);
    
        void                            Init();
        void                            Unload();
        static void                        StartRenderTextureMode(int width, int height);
        static std::shared_ptr<Texture> EndRenderTextureMode();
        void                            SwitchRenderer(RendererType type);
        RendererType                    GetCurrentRendererType() const;
        static CS200::IRenderer2D*        GetRenderer2D();
        void                            Shutdown();
    
    
    private:
        RendererType                                      current_renderer_type = RendererType::Immediate;
        inline static std::unique_ptr<CS200::IRenderer2D> renderer2D{};
    
        std::map<std::filesystem::path, std::shared_ptr<Texture>> textures;
    
        struct RenderInfo
        {
            // RenderInfo() = default;
            OpenGL::FramebufferWithColor Target{};
            Math::ivec2                     Size{};
            std::array<GLfloat, 4>         ClearColor{};
            std::array<GLint, 4>         Viewport{};
        };
    
        // inline static RenderInfo render_info{};
    
        static RenderInfo& get_render_info()
        {
            static RenderInfo instance;
            return instance;
        }
    };

}

================================================
FILE: source/Engine/Timer.hpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once

#include <chrono>
#include "Component.h"
namespace util
{
    class [[nodiscard]] Timer : public CS230::Component{
    private:
        using clock_t  = std::chrono::steady_clock;
        using second_t = std::chrono::duration<double, std::ratio<1>>;

        std::chrono::time_point<clock_t> timeStamp;
    
    public:
        Timer() noexcept : timeStamp(clock_t::now())
        {
        }
    
        void ResetTimeStamp() noexcept
        {
            timeStamp = clock_t::now();
        }
    
        double GetElapsedSeconds() const noexcept
        {
            return std::chrono::duration_cast<second_t>(clock_t::now() - timeStamp).count();
        }
    };

}

================================================
FILE: source/Engine/Vec2.cpp
================================================
/**

* \file
* \author Jonathan Holmes
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#include "Vec2.hpp"
#include <cmath>

namespace Math
{
    ivec2::ivec2(const vec2& v) noexcept : x(static_cast<int>(v.x)), y(static_cast<int>(v.y))
    {
    }

     ivec2& ivec2::operator+=(const ivec2& rhs) noexcept
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    
     ivec2& ivec2::operator-=(const ivec2& rhs) noexcept
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    
     ivec2& ivec2::operator*=(int scalar) noexcept
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    
     ivec2& ivec2::operator/=(int scalar) noexcept
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }
    
     ivec2 ivec2::operator+() const noexcept
    {
        ivec2 new_vec{ this->x, this->y };
        return new_vec;
    }
    
     ivec2 ivec2::operator-() const noexcept
    {
        ivec2 new_vec{ -this->x, -this->y };
        return new_vec;
    }
    
    double ivec2::Length()
    {
        return std::sqrt(x* x + y*y);
    }
    
     ivec2 operator+(const ivec2& lhs, const ivec2& rhs) noexcept
    {
        ivec2 new_vec{ lhs.x + rhs.x, lhs.y + rhs.y };
        return new_vec;
    }
    
     ivec2 operator-(const ivec2& lhs, const ivec2& rhs) noexcept
    {
        ivec2 new_vec{ lhs.x - rhs.x, lhs.y - rhs.y };
        return new_vec;
    }
    
     ivec2 operator*(const ivec2& v, int scalar) noexcept
    {
        ivec2 new_vec{ v.x * scalar, v.y * scalar };
        return new_vec;
    }
    
     ivec2 operator*(int scalar, const ivec2& v) noexcept
    {
        ivec2 new_vec{ v.x * scalar, v.y * scalar };
        return new_vec;
    }
    
    
     ivec2 operator/(const ivec2& v, int scalar) noexcept
    {
        ivec2 new_vec{ v.x / scalar, v.y / scalar };
        return new_vec;
    }
    
     bool operator==(const ivec2& lhs, const ivec2& rhs) noexcept
    {
        return (lhs.x == rhs.x) && (lhs.y == rhs.y);
    }
    
     bool operator!=(const ivec2& lhs, const ivec2& rhs) noexcept
    {
        return !(lhs == rhs);
    }
    
    std::ostream& operator<<(std::ostream& os, const ivec2& v)
    {
        os << v.x << ", " << v.y << "\n";
        return os;
    }
    
    std::istream& operator>>(std::istream& is, ivec2& v)
    {
        is >> v.x >> v.y;
        return is;
    }
    
    /*===============================ivec3==================================*/
    
    ivec3::ivec3(const vec3& v) noexcept : x(static_cast<int>(v.x)), y(static_cast<int>(v.y)), z(static_cast<int>(v.z))
    {
    }
    
     ivec3& ivec3::operator+=(const ivec3& rhs) noexcept
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }
    
     ivec3& ivec3::operator-=(const ivec3& rhs) noexcept
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }
    
     ivec3& ivec3::operator*=(int scalar) noexcept
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
    
     ivec3& ivec3::operator/=(int scalar) noexcept
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }
    
     ivec3 ivec3::operator+() const noexcept
    {
        ivec3 new_vec{ this->x, this->y, this->z };
        return new_vec;
    }
    
     ivec3 ivec3::operator-() const noexcept
    {
        ivec3 new_vec{ -this->x, -this->y, -this->z };
        return new_vec;
    }
    
    double ivec3::Length()
    {
        return std::sqrt(x*x + y*y + z*z);
    }
    
     ivec3 operator+(const ivec3& lhs, const ivec3& rhs) noexcept
    {
        ivec3 new_vec{ lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
        return new_vec;
    }
    
     ivec3 operator-(const ivec3& lhs, const ivec3& rhs) noexcept
    {
        ivec3 new_vec{ lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
        return new_vec;
    }
    
     ivec3 operator*(const ivec3& v, int scalar) noexcept
    {
        ivec3 new_vec{ v.x * scalar, v.y * scalar, v.z * scalar };
        return new_vec;
    }
    
     ivec3 operator*(int scalar, const ivec3& v) noexcept
    {
        ivec3 new_vec{ v.x * scalar, v.y * scalar, v.z * scalar };
        return new_vec;
    }
    
     ivec3 operator/(const ivec3& v, int scalar) noexcept
    {
        ivec3 new_vec{ v.x / scalar, v.y / scalar, v.z / scalar };
        return new_vec;
    }
    
     bool operator==(const ivec3& lhs, const ivec3& rhs) noexcept
    {
        return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z);
    }
    
     bool operator!=(const ivec3& lhs, const ivec3& rhs) noexcept
    {
        return !(lhs == rhs);
    }
    
    std::ostream& operator<<(std::ostream& os, const ivec3& v)
    {
        os << v.x << ", " << v.y << v.z << "\n";
        return os;
    }
    
    std::istream& operator>>(std::istream& is, ivec3& v)
    {
        is >> v.x >> v.y >> v.z;
        return is;
    }
    
    /*===========================vec2=================================================*/
     vec2& vec2::operator+=(const vec2& rhs) noexcept
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    
     vec2& vec2::operator-=(const vec2& rhs) noexcept
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    
     vec2& vec2::operator*=(int scalar) noexcept
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    
     vec2& vec2::operator/=(int scalar) noexcept
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }
    
     vec2 vec2::operator+() const noexcept
    {
        vec2 new_vec{ this->x, this->y };
        return new_vec;
    }
    
     vec2 vec2::operator-() const noexcept
    {
        vec2 new_vec{ -this->x, -this->y };
        return new_vec;
    }
    
     double vec2::Length() const noexcept
    {
        return std::sqrt(x*x + y*y);
    }
    
    vec2 vec2::Normalize()
    {
        vec2 normalized = {x/Length(),y/Length()};
        return normalized;
    }
    
     vec2 operator+(const vec2& lhs, const vec2& rhs) noexcept
    {
        vec2 new_vec{ lhs.x + rhs.x, lhs.y + rhs.y };
        return new_vec;
    }
    
     vec2 operator-(const vec2& lhs, const vec2& rhs) noexcept
    {
        vec2 new_vec{ lhs.x - rhs.x, lhs.y - rhs.y };
        return new_vec;
    }
    
     vec2 operator*(const vec2& v, int scalar) noexcept
    {
        vec2 new_vec{ v.x * scalar, v.y * scalar };
        return new_vec;
    }
    
     vec2 operator*(int scalar, const vec2& v) noexcept
    {
        vec2 new_vec{ v.x * scalar, v.y * scalar };
        return new_vec;
    }
    
     vec2 operator*(const vec2& v, double scalar) noexcept
    {
        vec2 new_vec{ v.x * scalar, v.y * scalar };
        return new_vec;
    }
    
     vec2 operator*(double scalar, const vec2& v) noexcept
    {
        vec2 new_vec{ v.x * scalar, v.y * scalar };
        return new_vec;
    }
    
     vec2 operator/(const vec2& v, int scalar) noexcept
    {
        vec2 new_vec{ v.x / scalar, v.y / scalar };
        return new_vec;
    }
    
     bool operator==(const vec2& lhs, const vec2& rhs) noexcept
    {
        return (lhs.x == rhs.x) && (lhs.y == rhs.y);
    }
    
     bool operator!=(const vec2& lhs, const vec2& rhs) noexcept
    {
        return !(lhs == rhs);
    }
    
    std::ostream& operator<<(std::ostream& os, const vec2& v)
    {
        os << v.x << ", " << v.y << "\n";
        return os;
    }
    
    std::istream& operator>>(std::istream& is, vec2& v)
    {
        is >> v.x >> v.y;
        return is;
    }
    
    /*===========================fvec2=================================================*/
     fvec2& fvec2::operator+=(const fvec2& rhs) noexcept
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    
     fvec2& fvec2::operator-=(const fvec2& rhs) noexcept
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    
     fvec2& fvec2::operator*=(int scalar) noexcept
    {
        x *= static_cast<float>(scalar);
        y *= static_cast<float>(scalar);
        return *this;
    }
    
     fvec2& fvec2::operator/=(int scalar) noexcept
    {
        x /= static_cast<float>(scalar);
        y /= static_cast<float>(scalar);
        return *this;
    }
    
     fvec2 fvec2::operator+() const noexcept
    {
        fvec2 new_vec{ this->x, this->y };
        return new_vec;
    }
    
     fvec2 fvec2::operator-() const noexcept
    {
        fvec2 new_vec{ -this->x, -this->y };
        return new_vec;
    }
    
     float fvec2::Length() const noexcept
    {
        return std::sqrt(x*x + y*y);
    }
    
    fvec2 fvec2::Normalize()
    {
        fvec2 normalized = {x/Length(),y/Length()};
        return normalized;
    }
    
     fvec2 operator+(const fvec2& lhs, const fvec2& rhs) noexcept
    {
        fvec2 new_vec{ lhs.x + rhs.x, lhs.y + rhs.y };
        return new_vec;
    }
    
     fvec2 operator-(const fvec2& lhs, const fvec2& rhs) noexcept
    {
        fvec2 new_vec{ lhs.x - rhs.x, lhs.y - rhs.y };
        return new_vec;
    }
    
     fvec2 operator*(const fvec2& v, int scalar) noexcept
    {
        fvec2 new_vec{ v.x * static_cast<float>(scalar), v.y * static_cast<float>(scalar) };
        return new_vec;
    }
    
     fvec2 operator*(int scalar, const fvec2& v) noexcept
    {
        fvec2 new_vec{ v.x * static_cast<float>(scalar), v.y * static_cast<float>(scalar) };
        return new_vec;
    }
    
     fvec2 operator*(const fvec2& v, float scalar) noexcept
    {
        fvec2 new_vec{ v.x * scalar, v.y * scalar };
        return new_vec;
    }
    
     fvec2 operator*(float scalar, const fvec2& v) noexcept
    {
        fvec2 new_vec{ v.x * scalar, v.y * scalar };
        return new_vec;
    }
    
     fvec2 operator/(const fvec2& v, int scalar) noexcept
    {
        fvec2 new_vec{ v.x / static_cast<float>(scalar), v.y / static_cast<float>(scalar) };
        return new_vec;
    }
    
     bool operator==(const fvec2& lhs, const fvec2& rhs) noexcept
    {
        return (lhs.x == rhs.x) && (lhs.y == rhs.y);
    }
    
     bool operator!=(const fvec2& lhs, const fvec2& rhs) noexcept
    {
        return !(lhs == rhs);
    }
    
    std::ostream& operator<<(std::ostream& os, const fvec2& v)
    {
        os << v.x << ", " << v.y << "\n";
        return os;
    }
    
    std::istream& operator>>(std::istream& is, fvec2& v)
    {
        is >> v.x >> v.y;
        return is;
    }
    
    vec2 to_vec2(const fvec2& rhs)
    {
        return {static_cast<double>(rhs.x), static_cast<double>(rhs.y)};
    }
    
    vec2 to_vec2(const ivec2& rhs)
    {
        return {static_cast<double>(rhs.x), static_cast<double>(rhs.y)};
    }
    
    fvec2 to_fvec2(const vec2& rhs)
    {
        return {static_cast<float>(rhs.x), static_cast<float>(rhs.y)};
    }
    
    fvec2 to_fvec2(const ivec2& rhs)
    {
        return {static_cast<float>(rhs.x), static_cast<float>(rhs.y)};
    }
    
    ivec2 to_ivec2(const fvec2& rhs)
    {
        return {static_cast<int>(rhs.x), static_cast<int>(rhs.y)};
    }
    
    ivec2 to_ivec2(const vec2& rhs)
    {
        return {static_cast<int>(rhs.x), static_cast<int>(rhs.y)};
    }
    
    /*===============================vec3==================================*/
     vec3& vec3::operator+=(const vec3& rhs) noexcept
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }
    
     vec3& vec3::operator-=(const vec3& rhs) noexcept
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }
    
     vec3& vec3::operator*=(int scalar) noexcept
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
    
     vec3& vec3::operator/=(int scalar) noexcept
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }
    
     vec3 vec3::operator+() const noexcept
    {
        vec3 new_vec{ this->x, this->y, this->z };
        return new_vec;
    }
    
     vec3 vec3::operator-() const noexcept
    {
        vec3 new_vec{ -this->x, -this->y, -this->z };
        return new_vec;
    }
    
    double vec3::Length()
    {
        return std::sqrt(x*x + y*y + z*z);
    }
    
     vec3 operator+(const vec3& lhs, const vec3& rhs) noexcept
    {
        vec3 new_vec{ lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
        return new_vec;
    }
    
     vec3 operator-(const vec3& lhs, const vec3& rhs) noexcept
    {
        vec3 new_vec{ lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
        return new_vec;
    }
    
     vec3 operator*(const vec3& v, int scalar) noexcept
    {
        vec3 new_vec{ v.x * scalar, v.y * scalar, v.z * scalar };
        return new_vec;
    }
    
     vec3 operator*(int scalar, const vec3& v) noexcept
    {
        vec3 new_vec{ v.x * scalar, v.y * scalar, v.z * scalar };
        return new_vec;
    }
    
     vec3 operator/(const vec3& v, int scalar) noexcept
    {
        vec3 new_vec{ v.x / scalar, v.y / scalar, v.z / scalar };
        return new_vec;
    }
    
     bool operator==(const vec3& lhs, const vec3& rhs) noexcept
    {
        return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z);
    }
    
     bool operator!=(const vec3& lhs, const vec3& rhs) noexcept
    {
        return !(lhs == rhs);
    }
    
    std::ostream& operator<<(std::ostream& os, const vec3& v)
    {
        os << v.x << ", " << v.y << v.z << "\n";
        return os;
    }
    
    std::istream& operator>>(std::istream& is, vec3& v)
    {
        is >> v.x >> v.y >> v.z;
        return is;
    }

}

================================================
FILE: source/Engine/Vec2.hpp
================================================
/**

* \file
* \author Jonathan Holmes
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#pragma once
#include <cmath>
#include <iostream>
#include <limits>

namespace Math
{

    struct vec2;
    struct vec3;
    
    struct [[nodiscard]] ivec2
    {
        int x{ 0 };
        int y{ 0 };
    
        // Constructors
        ivec2() noexcept = default;
        // ivec2(int _x, int _y) noexcept : x(_x), y(_y) { };
        constexpr ivec2(int _x, int _y) noexcept : x(_x), y(_y) { };
        // ivec2(const ivec2& rhs) = default;
        //  ivec2(int xy) noexcept;
    
        // Conversion
        ivec2(const vec2& v) noexcept;
    
        // Arithmetic operators
        ivec2& operator+=(const ivec2& rhs) noexcept;
        ivec2& operator-=(const ivec2& rhs) noexcept;
        ivec2& operator*=(int scalar) noexcept;
        ivec2& operator/=(int scalar) noexcept;
    
        // Unary operators
        ivec2 operator+() const noexcept;
        ivec2 operator-() const noexcept;
    
        // length
        double Length();
    };
    
    // Non-member operators
    ivec2 operator+(const ivec2& lhs, const ivec2& rhs) noexcept;
    ivec2 operator-(const ivec2& lhs, const ivec2& rhs) noexcept;
    ivec2 operator*(const ivec2& v, int scalar) noexcept;
    ivec2 operator*(int scalar, const ivec2& v) noexcept;
    ivec2 operator/(const ivec2& v, int scalar) noexcept;
    
    // Comparison operators
    bool operator==(const ivec2& lhs, const ivec2& rhs) noexcept;
    bool operator!=(const ivec2& lhs, const ivec2& rhs) noexcept;
    
    // Stream operators
    std::ostream& operator<<(std::ostream& os, const ivec2& v);
    std::istream& operator>>(std::istream& is, ivec2& v);
    
    struct ivec3
    {
        int x{ 0 };
        int y{ 0 };
        int z{ 0 };
    
        // Constructors
        ivec3() noexcept = default;
        ivec3(int _x, int _y, int _z) noexcept : x(_x), y(_y), z(_z) { };
        // ivec3(const ivec3& rhs) = default;
        //  ivec3(int xy) noexcept;
    
        // Conversion
        ivec3(const vec3& v) noexcept;
    
        // Arithmetic operators
        ivec3& operator+=(const ivec3& rhs) noexcept;
        ivec3& operator-=(const ivec3& rhs) noexcept;
        ivec3& operator*=(int scalar) noexcept;
        ivec3& operator/=(int scalar) noexcept;
    
        // Unary operators
        ivec3 operator+() const noexcept;
        ivec3 operator-() const noexcept;
    
        // length
        double Length();
    };
    
    // Non-member operators
    ivec3 operator+(const ivec3& lhs, const ivec3& rhs) noexcept;
    ivec3 operator-(const ivec3& lhs, const ivec3& rhs) noexcept;
    ivec3 operator*(const ivec3& v, int scalar) noexcept;
    ivec3 operator*(int scalar, const ivec3& v) noexcept;
    ivec3 operator/(const ivec3& v, int scalar) noexcept;
    
    // Comparison operators
    bool operator==(const ivec3& lhs, const ivec3& rhs) noexcept;
    bool operator!=(const ivec3& lhs, const ivec3& rhs) noexcept;
    
    // Stream operators
    std::ostream& operator<<(std::ostream& os, const ivec3& v);
    std::istream& operator>>(std::istream& is, ivec3& v);
    
    struct vec2
    {
        double x{ 0 };
        double y{ 0 };
    
        // Constructors
        vec2() noexcept = default;
        constexpr vec2(double _x, double _y) noexcept : x(_x), y(_y) { };
        //  vec2(const vec2& v) noexcept = default;
        // vec2(const vec2& rhs) = default;
        //  vec2(int xy) noexcept;
    
        // Conversion
        vec2(const ivec2& v) noexcept : x(static_cast<double>(v.x)), y(static_cast<double>(v.y)) { };
    
        // Arithmetic operators
        vec2& operator+=(const vec2& rhs) noexcept;
        vec2& operator-=(const vec2& rhs) noexcept;
        vec2& operator*=(int scalar) noexcept;
        vec2& operator/=(int scalar) noexcept;
    
        // Unary operators
        vec2 operator+() const noexcept;
        vec2 operator-() const noexcept;
    
        // length
        double Length() const noexcept;
    
        bool operator<(const vec2& other) const
        {
            return (x < other.x) || (x == other.x && y < other.y);
        }
    
        // normalize
        vec2 Normalize();
    };
    
    // Non-member operators
    vec2 operator+(const vec2& lhs, const vec2& rhs) noexcept;
    vec2 operator-(const vec2& lhs, const vec2& rhs) noexcept;
    vec2 operator*(const vec2& v, int scalar) noexcept;
    vec2 operator*(int scalar, const vec2& v) noexcept;
    vec2 operator*(const vec2& v, double scalar) noexcept;
    vec2 operator*(double scalar, const vec2& v) noexcept;
    vec2 operator/(const vec2& v, int scalar) noexcept;
    
    // Comparison operators
    bool operator==(const vec2& lhs, const vec2& rhs) noexcept;
    bool operator!=(const vec2& lhs, const vec2& rhs) noexcept;
    
    // Stream operators
    std::ostream& operator<<(std::ostream& os, const vec2& v);
    std::istream& operator>>(std::istream& is, vec2& v);
    
    struct fvec2
    {
        float x{ 0 };
        float y{ 0 };
    
        // Constructors
        fvec2() noexcept = default;
        constexpr fvec2(float _x, float _y) noexcept : x(_x), y(_y) { };
        //  vec2(const vec2& v) noexcept = default;
        // vec2(const vec2& rhs) = default;
        //  vec2(int xy) noexcept;
    
        // Conversion
        fvec2(const ivec2& v) noexcept : x(static_cast<float>(v.x)), y(static_cast<float>(v.y)) { };
    
        // Arithmetic operators
        fvec2& operator+=(const fvec2& rhs) noexcept;
        fvec2& operator-=(const fvec2& rhs) noexcept;
        fvec2& operator*=(int scalar) noexcept;
        fvec2& operator/=(int scalar) noexcept;
    
        // Unary operators
        fvec2 operator+() const noexcept;
        fvec2 operator-() const noexcept;
    
        // length
        float Length() const noexcept;
    
        bool operator<(const fvec2& other) const
        {
            return (x < other.x) || (x == other.x && y < other.y);
        }
    
        // normalize
        fvec2 Normalize();
    };
    
    // Non-member operators
    fvec2 operator+(const fvec2& lhs, const fvec2& rhs) noexcept;
    fvec2 operator-(const fvec2& lhs, const fvec2& rhs) noexcept;
    fvec2 operator*(const fvec2& v, int scalar) noexcept;
    fvec2 operator*(int scalar, const fvec2& v) noexcept;
    fvec2 operator*(const fvec2& v, float scalar) noexcept;
    fvec2 operator*(float scalar, const fvec2& v) noexcept;
    fvec2 operator/(const fvec2& v, int scalar) noexcept;
    
    // Comparison operators
    bool operator==(const fvec2& lhs, const fvec2& rhs) noexcept;
    bool operator!=(const fvec2& lhs, const fvec2& rhs) noexcept;
    
    // Stream operators
    std::ostream& operator<<(std::ostream& os, const fvec2& v);
    std::istream& operator>>(std::istream& is, fvec2& v);
    
    vec2 to_vec2(const fvec2& rhs);
    vec2 to_vec2(const ivec2& rhs);
    
    fvec2 to_fvec2(const vec2& rhs);
    fvec2 to_fvec2(const ivec2& rhs);
    
    ivec2 to_ivec2(const fvec2& rhs);
    ivec2 to_ivec2(const vec2& rhs);
    
    
    struct vec3
    {
        double x{ 0 };
        double y{ 0 };
        double z{ 0 };
    
        // Constructors
        vec3() noexcept = default;
        vec3(double _x, double _y, double _z) noexcept : x(_x), y(_y), z(_z) { };
        // vec3(const vec3& rhs) = default;
        //  vec3(int xy) noexcept;
    
        // Conversion
        vec3(const ivec3& v) noexcept : x(static_cast<double>(v.x)), y(static_cast<double>(v.y)), z(static_cast<double>(v.z)) { };
    
        // Arithmetic operators
        vec3& operator+=(const vec3& rhs) noexcept;
        vec3& operator-=(const vec3& rhs) noexcept;
        vec3& operator*=(int scalar) noexcept;
        vec3& operator/=(int scalar) noexcept;
    
        // Unary operators
        vec3 operator+() const noexcept;
        vec3 operator-() const noexcept;
    
        // length
        double Length();
    };
    
    // Non-member operators
    vec3 operator+(const vec3& lhs, const vec3& rhs) noexcept;
    vec3 operator-(const vec3& lhs, const vec3& rhs) noexcept;
    vec3 operator*(const vec3& v, int scalar) noexcept;
    vec3 operator*(int scalar, const vec3& v) noexcept;
    vec3 operator/(const vec3& v, int scalar) noexcept;
    
    // Comparison operators
    bool operator==(const vec3& lhs, const vec3& rhs) noexcept;
    bool operator!=(const vec3& lhs, const vec3& rhs) noexcept;
    
    // Stream operators
    std::ostream& operator<<(std::ostream& os, const vec3& v);
    std::istream& operator>>(std::istream& is, vec3& v);

}

================================================
FILE: source/Engine/Window.cpp
================================================
/**

* \file Window.cpp
* \author Rudy Castan
* \author Jonathan Holmes
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#include "Window.hpp"
#include "../OpenGL/GL.hpp"
#include "CS200/RenderingAPI.hpp"
#include "Engine.hpp"
#include "Error.hpp"
#include "Logger.hpp"
#include <GL/glew.h>
#include <SDL.h>
#include <functional>
#include <sstream>

namespace
{
    void hint_gl(SDL_GLattr attr, int value)
    {
        // // https://wiki.libsdl.org/SDL2/SDL_GL_SetAttribute
        if (const auto success = SDL_GL_SetAttribute(attr, value); success != 0)
        {
            Engine::GetLogger().LogError(std::string{ "Failed to Set GL Attribute: " } + SDL_GetError());
        }
    }
}

namespace CS230
{

    /*Basic setup*/
    void Window::setupSDLWindow(std::string_view title)
    {
        // Part 1 - Initialize SDL for visual use
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            throw_error_message("Failed to init SDK error: ", SDL_GetError());
        }

// Part 2 - Configure OpenGL context attributes (before window creation)
#if defined(IS_WEBGL2)
        hint_gl(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        hint_gl(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        hint_gl(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#else
        hint_gl(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif
        hint_gl(SDL_GL_DOUBLEBUFFER, true);
        hint_gl(SDL_GL_STENCIL_SIZE, 8);
        hint_gl(SDL_GL_DEPTH_SIZE, 24);
        hint_gl(SDL_GL_RED_SIZE, 8);
        hint_gl(SDL_GL_GREEN_SIZE, 8);
        hint_gl(SDL_GL_BLUE_SIZE, 8);
        hint_gl(SDL_GL_ALPHA_SIZE, 8);
        hint_gl(SDL_GL_MULTISAMPLEBUFFERS, 1);
        hint_gl(SDL_GL_MULTISAMPLESAMPLES, 4);

        // Part 3 - Create the SDL window
        sdl_window = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, default_width, default_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        if (sdl_window == nullptr)
        {
            throw_error_message("Failed to create window: ", SDL_GetError());
        }
    }
    
    /*Setup GL*/
    void Window::setupOpenGL()
    {
        // Create OpenGL context
        if (gl_context = SDL_GL_CreateContext(sdl_window); gl_context == nullptr)
        {
            throw_error_message("Failed to create opengl context: ", SDL_GetError());
        }
    
        // Make context current
        SDL_GL_MakeCurrent(sdl_window, gl_context);
    
        // Initialize GLEW for extension loading
        if (const auto result = glewInit(); GLEW_OK != result)
        {
            throw_error_message("Unable to initialize GLEW - error: ", glewGetErrorString(result));
        }
    
        // Configure VSync
        constexpr int ADAPTIVE_VSYNC = -1;
        constexpr int VSYNC          = 1;
        if (const auto result = SDL_GL_SetSwapInterval(ADAPTIVE_VSYNC); result != 0)
        {
            SDL_GL_SetSwapInterval(VSYNC);
        }
    
        // Initialize our rendering abstraction layer
        CS200::RenderingAPI::Init();
    }
    
    void Window::Start(std::string_view title)
    {
        setupSDLWindow(title);
        setupOpenGL();
        window_size.x = default_width;
        window_size.y = default_height;
    
        // Get actual drawable size for high-DPI displays
        SDL_GL_GetDrawableSize(sdl_window, &window_size.x, &window_size.y);
    
    
        GL::Viewport(0, 0, window_size.x, window_size.y);
    
        // Set initial clear color through our rendering abstraction
        CS200::RenderingAPI::SetClearColor(default_background);
    }
    
    void Window::Update()
    {
        SDL_GL_SwapWindow(sdl_window);
    
    
        SDL_Event event{ 0 };
        while (SDL_PollEvent(&event) != 0)
        {
            eventCallback(event);
    
            switch (event.window.event)
            {
                case SDL_WINDOWEVENT_CLOSE: closed = true; break;
                case SDL_WINDOWEVENT_RESIZED: window_size = { event.window.data1, event.window.data2 }; break;
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    SDL_GL_GetDrawableSize(sdl_window, &window_size.x, &window_size.y);
                    GL::Viewport(0, 0, window_size.x, window_size.y);
                    break;
                    break;
                default: break;
            }
        }
    }
    
    bool Window::IsClosed() const
    {
        return closed;
    }
    
    void Window::Clear(CS200::RGBA color)
    {
        auto c = CS200::unpack_color(color);
        GL::ClearColor(c[0], c[1], c[2], c[3]);
        GL::Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    void Window::ForceResize(int desired_width, int desired_height)
    {
        SDL_SetWindowSize(sdl_window, desired_width, desired_height);
        window_size.x = desired_width;
        window_size.y = desired_height;
    }
    
    void Window::SetWindowPosition(int x, int y)
    {
        SDL_SetWindowPosition(sdl_window,x,y);
    }
    
    SDL_Window* Window::GetSDLWindow() const
    {
        return sdl_window;
    }
    
    SDL_GLContext Window::GetGLContext() const
    {
        return gl_context;
    }
    
    void Window::SetEventCallback(WindowEventCallback callback)
    {
        eventCallback = std::move(callback);
    }
    
    float Window::background_r = 0.0f;
    float Window::background_g = 0.0f;
    float Window::background_b = 0.0f;
    
    void Window::SetBackgroundColor(float r, float g, float b) noexcept
    {
        background_r = r;
        background_g = g;
        background_b = b;
    }
    
    //Math::ivec2 Window::GetWindowSize() const
    //{
    //    return window_size;
    //}
    
    Window::~Window()
    {
        if (gl_context)
        {
            SDL_GL_DeleteContext(gl_context);
        }
        if (sdl_window)
        {
            SDL_DestroyWindow(sdl_window);
        }
    
        SDL_Quit();
    }

}

================================================
FILE: source/Engine/Window.hpp
================================================
/**

* \file
* \author Rudy Castan
* \author Jonathan Holmes
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once
  #include "CS200/RGBA.hpp"
  #include "Vec2.hpp"
  #include <functional>
  #include <gsl/gsl>
  #include <string_view>

struct SDL_Window;
typedef void*           SDL_GLContext;
typedef union SDL_Event SDL_Event;

namespace CS230
{
    class Window
    {
    public:
        Window() noexcept = default;
        ~Window();

        Window(const Window&)                = delete;
        Window& operator=(const Window&)     = delete;
        Window(Window&&) noexcept            = delete;
        Window& operator=(Window&&) noexcept = delete;
    
    public:
        void Start(std::string_view title);
        void Update();
        bool IsClosed() const;
    
        [[nodiscard]] Math::ivec2 GetSize() const noexcept
        {
            return { window_size.x, window_size.y };
        }
    
        void          Clear(CS200::RGBA color);
        void          ForceResize(int w, int h);
        void          SetWindowPosition(int x, int y);
        SDL_Window*   GetSDLWindow() const;
        SDL_GLContext GetGLContext() const;
    
        using WindowEventCallback = std::function<void(const SDL_Event&)>;
        void SetEventCallback(WindowEventCallback callback);
    
        static void SetBackgroundColor(float r, float g, float b) noexcept;
    
        // Math::ivec2 GetWindowSize() const;
    
    private:
    
        void setupSDLWindow(std::string_view title);
        void setupOpenGL();
    
    
        const int                     default_width      = 800;
        const int                     default_height     = 600;
        Math::ivec2                   window_size        = { default_width, default_height };
        static constexpr unsigned int default_background = UINT_MAX;
        static constexpr CS200::RGBA  default_background1{ CS200::WHITE };
    
        gsl::owner<SDL_Window*>   sdl_window = nullptr;
        gsl::owner<SDL_GLContext> gl_context = nullptr;
        bool                      closed     = false;
        // Math::ivec2               size       = { 800, 600 };
    
        WindowEventCallback eventCallback;
    
        std::function<void(SDL_Event)> func_event_callback;
        static float                   background_r;
        static float                   background_g;
        static float                   background_b;
    };

}

================================================
FILE: source/Game/Background.cpp
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Background.cpp
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    March 29, 2025
*/

#include "Background.h"
#include "../Engine/TextureManager.hpp"

void Background::Add(const std::filesystem::path& texture_path, double speed){
    backgrounds.push_back(ParallaxLayer{Engine::GetTextureManager().Load(texture_path),speed});
}

void Background::Unload(){
    backgrounds.clear();
}

void Background::Draw(const CS230::Camera& camera) {
    for (ParallaxLayer& background : backgrounds) {
        Math::vec2 inverted_position = -Math::vec2{ camera.GetPosition().x * background.speed, camera.GetPosition().y };
        Math::TranslationMatrix new_matrix = Math::TranslationMatrix(inverted_position);
        background.texture->Draw(new_matrix);
    }
}

Math::ivec2 Background::GetSize()
{
    return backgrounds.back().texture->GetSize();
}

================================================
FILE: source/Game/Background.h
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Background.h
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    March 29, 2025
*/

#pragma once
#include "../Engine/Engine.hpp"
#include "../Engine/Texture.hpp"
#include "../Engine/Camera.h"
#include "../Engine/Component.h"

class Background : public CS230::Component{
public:
    void Add(const std::filesystem::path& texture_path, double speed);
    void Unload();
    void Draw(const CS230::Camera& camera);
    Math::ivec2 GetSize();
private:
    struct ParallaxLayer {
        std::shared_ptr<CS230::Texture> texture;
        double speed = 1;
    };

    std::vector<ParallaxLayer> backgrounds;

};

================================================
FILE: source/Game/GameObjectTypes.h
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObjectTypes.h
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    May 20, 2025
*/
#pragma once
enum class GameObjectTypes {
    //Score,
    Bus,
    Player,
    Food,
    Passenger,
    Obstacle,
    Particle,
    Character,
    Samurai,
    Count
};

================================================
FILE: source/Game/MainMenu.cpp
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  MainMenu.cpp
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    May 6, 2025
*/
#include "MainMenu.h"
#include "CS200/IRenderer2D.hpp"
#include "CS200/NDC.hpp"
#include "CS200/RenderingAPI.hpp"
#include "Demo/DemoBatchInstance.hpp"
#include "Demo/DemoSceneShowcase/SceneState.hpp"
#include "Demo/DemoBufferTypes.hpp"
#include "Demo/DemoCS230Textures.hpp"
#include "Demo/DemoFramebuffer.hpp"
#include "Demo/DemoShapes.hpp"
#include "Demo/DemoText.hpp"
#include "Demo/DemoTexturing.hpp"
#include "Demo/DemoVAO.hpp"
#include "Engine/Engine.hpp"
#include "Engine/GameStateManager.hpp"
#include "Engine/Input.hpp"
#include "Engine/TextManager.hpp"
#include "Engine/TextureManager.hpp"
#include "Engine/Window.hpp"

#include "OpenGL/Environment.hpp"

#include "Game/CS230_Final/States/Project.h"
#include "Game/States/ConsoleTest.h"
#include "Game/States/RenderingTest.h"
#include "States.h"
#include <imgui.h>

// (0.0 = 0%, 1.0 = 100%)
namespace
{
    // --- Menu UI Ratio ---
    const double TITLE_X_RATIO               = 0.25;
    const double TITLE_Y_RATIO_FROM_BOTTOM = 0.8;
    const double TITLE_SCALE_VAL           = 1.5;

    const double MENU_CENTER_X_RATIO     = 0.5;
    const double MENU_WIDTH_RATIO         = 0.4;
    const double MENU_ITEM_HEIGHT_RATIO     = 0.05;
    const double MENU_ITEM_SPACING_RATIO = 0.03;
    const double MENU_START_Y_RATIO         = 0.4;

}

MainMenu::MainMenu() : current_option(Option::CS230Final)
{
}

void MainMenu::DrawImGui()
{
    if (ImGui::Begin("Demo Controls"))
    {
        if (ImGui::Button("Switch to Demo DemoBufferTypes"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<DemoBufferTypes>();
        }
        if (ImGui::Button("Switch to Demo DemoCS230Textures"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<DemoCS230Textures>();
        }
        if (ImGui::Button("Switch to Demo DemoFramebuffer"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<DemoFramebuffer>();
        }
        if (ImGui::Button("Switch to Demo DemoShapes"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<DemoShapes>();
        }
        if (ImGui::Button("Switch to Demo DemoText"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<DemoText>();
        }
        if (ImGui::Button("Switch to Demo DemoTexturing"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<DemoTexturing>();
        }
        if (ImGui::Button("Switch to Demo DemoVAO"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<DemoVAO>();
        }
        if (ImGui::Button("Switch to Demo HW6Demo1"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<DemoBatchInstance>();
        }
        if (ImGui::Button("Switch to Demo HW6Demo2"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<SceneState>();
        }
    }
    ImGui::End();
}

void MainMenu::select_option()
{
    switch (current_option)
    {

        case MainMenu::Option::CS230Final:
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<Project>();
            break;
    
        case MainMenu::Option::ConsoleTest:
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<ConsoleTest>();
            break;
    
        case MainMenu::Option::RenderingTest:
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<RenderingTest>();
            break;
    
        case MainMenu::Option::Exit: Engine::GetGameStateManager().PopState(); break;
        case MainMenu::Option::COUNT: break;
    }

}

void MainMenu::Load()
{
    CS200::RenderingAPI::SetClearColor(0x000000FF);
    if (!OpenGL::IsWebGL)
    {
        Engine::GetWindow().ForceResize(default_window_size.x, default_window_size.y);
        Engine::GetWindow().SetWindowPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    }
    Option temp_option = current_option;
    while (temp_option != Option::COUNT)
    {
        colors[temp_option] = non_seleted_color;
        temp_option            = static_cast<Option>(static_cast<int>(temp_option) + 1);
    }
    update_colors();

    const auto window_size = default_window_size;
    
    title_pos.x = window_size.x * TITLE_X_RATIO;
    title_pos.y = window_size.y * TITLE_Y_RATIO_FROM_BOTTOM;
    title_scale = Math::vec2{ TITLE_SCALE_VAL, TITLE_SCALE_VAL };
    
    const double text_width          = window_size.x * MENU_WIDTH_RATIO;
    const double text_x              = (window_size.x * MENU_CENTER_X_RATIO) - (text_width / 2.0);
    const double text_height      = window_size.y * MENU_ITEM_HEIGHT_RATIO;
    const double start_y_from_top = window_size.y * MENU_START_Y_RATIO;
    
    const double item_bottom_y_from_top       = start_y_from_top + text_height;
    const double item_bottom_y_from_bottom = window_size.y - item_bottom_y_from_top;
    
    menu_start_pos_bl       = Math::vec2{ text_x, item_bottom_y_from_bottom };
    menu_item_size           = Math::vec2{ text_width, text_height };
    menu_item_total_height = text_height + (window_size.y * MENU_ITEM_SPACING_RATIO);

}

void MainMenu::Update([[maybe_unused]] double dt)
{
    CS230::Input& input          = Engine::GetInput();
    // Math::vec2      mouse_pos      = input.GetMousePos();
    // auto          window_size = Engine::GetWindow().GetSize();

    update_colors();
    if (input.KeyJustReleased(CS230::Input::Keys::Up))
    {
        int current_index = static_cast<int>(current_option);
        int total_options = static_cast<int>(Option::COUNT);
        current_index      = (current_index - 1 + total_options) % total_options;
        current_option      = static_cast<Option>(current_index);
    }
    else if (input.KeyJustReleased(CS230::Input::Keys::Down))
    {
        int current_index = static_cast<int>(current_option);
        int total_options = static_cast<int>(Option::COUNT);
        current_index      = (current_index + 1) % total_options;
        current_option      = static_cast<Option>(current_index);
    }
    else if (input.KeyJustReleased(CS230::Input::Keys::Enter))
    {
        select_option();
    }
    
    
    // bool mouse_is_hovering = false;
    // int     total_options       = static_cast<int>(Option::COUNT);
    // for (int i = 0; i < total_options; ++i)
    // {
    //     double item_bottom_y = menu_start_pos_bl.y - (i * menu_item_total_height);
    
    //     Math::vec2 rect_pos{ menu_start_pos_bl.x, item_bottom_y };
    //     Math::vec2 rect_size = menu_item_size;
    
    //     if (IsPointInRect(mouse_pos, rect_pos, rect_size))
    //     {
    //         current_option      = static_cast<Option>(i);
    //         mouse_is_hovering = true;
    //         break;
    //     }
    // }
    
    // if (input.MouseJustPressed(0) && mouse_is_hovering)
    // {
    //     select_option();
    // }

}

void MainMenu::Unload()
{
}

void MainMenu::Draw()
{
    CS200::RenderingAPI::Clear();
    auto renderer_2d = Engine::GetTextureManager().GetRenderer2D();
    renderer_2d->BeginScene(CS200::build_ndc_matrix(Engine::GetWindow().GetSize()));

    auto& text_manager = Engine::GetTextManager();
    
    text_manager.DrawText("Engine Porting", title_pos, Fonts::Outlined, title_scale, title_color);
    
    double current_item_y = 0;
    int       i              = 0;
    
    // Option: cs230 final
    i               = static_cast<int>(Option::CS230Final);
    current_item_y = menu_start_pos_bl.y - (i * menu_item_total_height);
    text_manager.DrawText("CS230 Final", Math::vec2{ menu_start_pos_bl.x, current_item_y }, Fonts::Outlined, { 1.0, 1.0 }, colors[Option::CS230Final]);
    
    // Option: console test
    i               = static_cast<int>(Option::ConsoleTest);
    current_item_y = menu_start_pos_bl.y - (i * menu_item_total_height);
    text_manager.DrawText("Console test", Math::vec2{ menu_start_pos_bl.x, current_item_y }, Fonts::Outlined, { 1.0, 1.0 }, colors[Option::ConsoleTest]);
    
    // Option: rendering test
    i               = static_cast<int>(Option::RenderingTest);
    current_item_y = menu_start_pos_bl.y - (i * menu_item_total_height);
    text_manager.DrawText("Rendering test", Math::vec2{ menu_start_pos_bl.x, current_item_y }, Fonts::Outlined, { 1.0, 1.0 }, colors[Option::RenderingTest]);
    
    // Option: exit
    i               = static_cast<int>(Option::Exit);
    current_item_y = menu_start_pos_bl.y - (i * menu_item_total_height);
    text_manager.DrawText("Exit", Math::vec2{ menu_start_pos_bl.x, current_item_y }, Fonts::Outlined, { 1.0, 1.0 }, colors[Option::Exit]);
    
    renderer_2d->EndScene();

}

gsl::czstring MainMenu::GetName() const
{
    return "MainMenu";
}

void MainMenu::update_colors()
{
    for (auto& color : colors)
    {
        if (color.first == current_option)
        {
            color.second = seleted_color;        
        }
        else
        {
            color.second = non_seleted_color;
        }
    }
}

================================================
FILE: source/Game/MainMenu.h
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  MainMenu.h
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    May 6, 2025
*/

#pragma once

#include "../Engine/Engine.hpp"
#include "../Engine/Font.hpp"
#include "../Engine/GameState.hpp"
#include "../Engine/Texture.hpp"

#include "../Engine/Fonts.h"

class MainMenu : public CS230::GameState
{
public:
    MainMenu();
    void                         Load() override;
    void                         Update(double dt) override;
    void                         Unload() override;
    void                         Draw() override;
    void                         DrawImGui() override;
    gsl::czstring                 GetName() const override;
    static constexpr CS200::RGBA title_color       = 0x9A2EFEFF;
    static constexpr CS200::RGBA non_seleted_color = 0xFFFFFFFF;
    static constexpr CS200::RGBA seleted_color       = 0x3ADF00FF;

private:
    enum class Option
    {
        CS230Final,
        ConsoleTest,
        RenderingTest,
        Exit,
        COUNT
    };
    Option current_option;

    std::map<Option, CS200::RGBA> colors;
    
    
    Math::vec2 title_pos;
    Math::vec2 title_scale;
    
    Math::vec2 menu_start_pos_bl;
    Math::vec2 menu_item_size;
    double       menu_item_total_height;
    
    void select_option();
    void update_colors();
    
    static constexpr Math::ivec2 default_window_size = { 800, 600 };

};

================================================
FILE: source/Game/Particles.h
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Particles.h
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    May 29, 2025
*/
#pragma once
#include "../Engine/Particle.h"

namespace Particles
{
    class Smoke : public CS230::Particle
    {
    public:
        Smoke() : Particle("Assets/Smoke.spt") { };

        std::string TypeName() override
        {
            return "Smoke Particle";
        }
    
        static constexpr int    MaxCount = 3;
        static constexpr double MaxLife  = 5.0;
    };
    
    class Hit : public CS230::Particle
    {
    public:
        Hit() : Particle("Assets/Hit.spt") { };
    
        std::string TypeName() override
        {
            return "Hit Particle";
        }
    
        static constexpr int    MaxCount = 10;
        static constexpr double MaxLife  = 1.0;
    };
    
    class MeteorBit : public CS230::Particle
    {
    public:
    
        MeteorBit() : Particle("Assets/sprites/DemoSceneShowcase/Meteor.spt") { };
    
        std::string TypeName() override
        {
            return "MeteorBit Particle";
        }
    
        static constexpr int    MaxCount = 150;
        static constexpr double MaxLife  = 1.25;
    };
    
    class Tears : public CS230::Particle
    {
    public:
        Tears() : Particle("Assets/sprites/CS230_Final/Tears.spt") { };
    
        std::string TypeName() override
        {
            return "Tears Particle";
        }
    
        static constexpr int    MaxCount = 30;
        static constexpr double MaxLife  = 3.0;
    };
    
    class Shining : public CS230::Particle
    {
    public:
        Shining() : Particle("Assets/sprites/CS230_Final/Shining.spt") { };
    
        std::string TypeName() override
        {
            return "Shining Particle";
        }
    
        static constexpr int    MaxCount = 50;
        static constexpr double MaxLife  = 3.0;
    };
    
    class Flame : public CS230::Particle
    {
    public:
        Flame() : Particle("Assets/sprites/DemoSceneShowcase/Flame.spt") { };
    
        std::string TypeName() override
        {
            return "Flame Particle";
        }
    
        static constexpr int    MaxCount = 5;
        static constexpr double MaxLife     = 1.25;
    };

}

================================================
FILE: source/Game/Score.cpp
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Score.cpp
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    May 29, 2025
*/
#include "Score.h"

Score::Score( int _value) 
    :  value(_value){}

void Score::Add(int dv)
{
    value += dv;
}

void Score::Sub(int dv)
{
    value -= dv;
}

================================================
FILE: source/Game/Score.h
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Score.h
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    May 29, 2025
*/
#pragma once

#include "../Engine/GameObject.h"
#include "../Engine/Vec2.hpp"
class Score : public CS230::Component {
public:
    Score(int value);
    void Add(int dv = 1);
    void Sub(int dv = 1);
    const int& Value() const { return value; }
private:
    int value;
};

================================================
FILE: source/Game/Splash.cpp
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Splash.cpp
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    March 12, 2025
*/
#include "../Engine/Engine.hpp"
#include "../Engine/TextureManager.hpp"
#include "../Engine/Logger.hpp"
#include "../Engine/GameStateManager.hpp"
#include "../Engine/Window.hpp"
#include "../CS200/RenderingAPI.hpp"
#include "../CS200/IRenderer2D.hpp"
#include "../CS200/NDC.hpp"
#include "MainMenu.h"
#include "Splash.h"

void Splash::Load() {
    counter = 0.0;
    texture = Engine::GetTextureManager().Load("Assets/images/Splash/DigiPen.png");
}

void Splash::Update([[maybe_unused]] double dt) {
    Engine::GetLogger().LogDebug(std::to_string(counter));
    if (counter >= 0.7) {
        Engine::GetGameStateManager().PopState();
        Engine::GetGameStateManager().PushState<MainMenu>();
    }
    counter+=dt;
}

void Splash::Unload()
{
}

void Splash::Draw()  {

    CS200::RenderingAPI::Clear();
    auto renderer_2d = Engine::GetTextureManager().GetRenderer2D();
    renderer_2d->BeginScene(CS200::build_ndc_matrix(Engine::GetWindow().GetSize()));
    texture->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - texture->GetSize()) / 2 }));
    
    renderer_2d->EndScene();

}

void Splash::DrawImGui()
{
}

gsl::czstring Splash::GetName() const
{
    return "Splash";
}

================================================
FILE: source/Game/Splash.h
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Splash.h
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    March 12, 2025
*/

#pragma once
#include "../Engine/GameState.hpp"
#include "../Engine/Texture.hpp"

class Splash : public CS230::GameState
{
public:
    // Splash();
    void          Load() override;
    void          Update(double dt) override;
    void          Unload() override;
    void          Draw() override;
    void          DrawImGui() override;
    gsl::czstring GetName() const override;

private:
    double                          counter = 0;
    std::shared_ptr<CS230::Texture> texture;
};

================================================
FILE: source/Game/States.h
================================================
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  States.h
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    March 12, 2025
*/
#pragma once
enum class States {
    Splash,
    MainMenu,
    Final
};

================================================
FILE: source/Game/CS230_Final/Components/Bounce.cpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #include "Bounce.h"
  #include "../../../Engine/GameObject.h"

Bounce::Bounce(CS230::GameObject* _given_object, Math::vec2 _start_position, bool _looping, double _timer)
    : given_object(_given_object), start_position(_start_position), looping(_looping), timer(_timer)
{
}

void Bounce::Update(double dt)
{
    if (looping == false)
    {
        if (timer >= 0.0 && (timer - dt) >= 0.0)
        {
            timer -= dt;
        }
        else
        {
            timer = 0.0;
        }
    }

    if (looping == true || (looping == false && timer > 0.0))
    {
        if (given_object->GetPosition().y <= start_position.y)
        {
            given_object->SetVelocity({ given_object->GetVelocity().x, bounce_velocity });
            // Engine::GetLogger().LogDebug("just bounced");
        }
        else
        {
            given_object->UpdateVelocity({ 0, -100 * dt });
            // Engine::GetLogger().LogDebug("falling");
        }
    }

}

================================================
FILE: source/Game/CS230_Final/Components/Bounce.h
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #pragma once
  #include "../../../Engine/Component.h"
  #include "../../../Engine/GameObject.h"

class Bounce : public CS230::Component
{
public:
    Bounce(CS230::GameObject*, Math::vec2, bool, double timer = 0.0);
    void                    Update(double dt) override;
    static constexpr double bounce_velocity = 50;

private:
    CS230::GameObject* given_object;
    Math::vec2         start_position;
    bool               looping;
    double             timer;
};

================================================
FILE: source/Game/CS230_Final/Components/Grid.cpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #include "Grid.h"
  #include "../../../Engine/Input.hpp"
  #include "../../../Engine/TextureManager.hpp"
  #include "../../../Engine/Window.hpp"

Grid::Grid()
{
    window_size = Engine::GetWindow().GetSize();
    white_dot   = Engine::GetTextureManager().Load("Assets/images/CS230_Final/WhiteDot.png");
    black_dot   = Engine::GetTextureManager().Load("Assets/images/CS230_Final/BlackDot.png");
    red_dot     = Engine::GetTextureManager().Load("Assets/images/CS230_Final/RedDot.png");
    blue_dot    = Engine::GetTextureManager().Load("Assets/images/CS230_Final/BlueDot.png");
}

void Grid::Update([[maybe_unused]] double dt)
{
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Tab))
    {
        draw = !draw;
    }
    if(window_size != Engine::GetWindow().GetSize()){
        window_size = Engine::GetWindow().GetSize();
    }
}

void Grid::Draw(DotColor dc,float depth)
{
    if (draw)
    {
        for (int i = 0; i <= window_size.y / 10; ++i)
        {
            for (int j = 0; j <= window_size.x / 10; ++j)
            {
                Math::TransformationMatrix draw_matrix = Math::TranslationMatrix(Math::ivec2{ j * 10, i * 10 }) /** Math::TranslationMatrix(-camera.GetPosition())*/;
                if (i == 0 && j == 0)
                {
                    blue_dot->Draw(draw_matrix * Math::ScaleMatrix(4.0),CS200::WHITE,depth);
                }
                else if (i == 0 || i == window_size.y / 10 || j == 0 || j == window_size.x / 10)
                {
                    red_dot->Draw(draw_matrix * Math::ScaleMatrix(2.0), CS200::WHITE, depth);
                }
                else
                {
                    switch (dc)
                    {
                    case DotColor::white: white_dot->Draw(draw_matrix, CS200::WHITE, depth);
                        break;

                    case DotColor::black: black_dot->Draw(draw_matrix, CS200::WHITE, depth);
                        break;
                    }
    
                }
            }
        }
    }

}

================================================
FILE: source/Game/CS230_Final/Components/Grid.h
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #pragma once
  #include "../../../Engine/Camera.h"
  #include "../../../Engine/Component.h"
  #include "../../../Engine/Engine.hpp"
  #include "../../../Engine/Fonts.h"
  #include "../../../Engine/Texture.hpp"
  #include "../../../Engine/Vec2.hpp"
  #include <filesystem>
  #include <memory>

class Grid : public CS230::Component
{
public:
    enum class DotColor
    {
        black,
        white
    };
    Grid();
    void Update(double dt) override;
    void Draw(DotColor,float);

private:
    Math::ivec2                        window_size;
    bool                            draw = true;
    std::shared_ptr<CS230::Texture> white_dot;
    std::shared_ptr<CS230::Texture> black_dot;
    std::shared_ptr<CS230::Texture> red_dot;
    std::shared_ptr<CS230::Texture> blue_dot;
};

================================================
FILE: source/Game/CS230_Final/Components/Random.cpp
================================================
/**

* \file

* \author Taekyung Ho

* \date 2025 Spring

* \par CS230

* \copyright DigiPen Institute of Technology
  */
  #include "Random.h"
  #include "../../../Engine/Logger.hpp"
  int Random::PickRandomIndex(size_t amount, bool same_probability, const std::vector<double>& probability_array)
  {
   if (same_probability == true) {
  
       double uniform_weight = 100.0 / static_cast<double>(amount);
       std::vector<double> weight;
       for (size_t i = 0; i < amount; ++i) {
           weight.push_back(uniform_weight);
       }
       std::discrete_distribution<> dist(weight.begin(), weight.end());
       return dist(gen);
  
   }
   else {
  
       if (amount <= 0) {
           Engine::GetLogger().LogDebug("Invalid amount: must be greater than 0.");
           return -1;
       }
       if (probability_array.size() != amount) {
           Engine::GetLogger().LogDebug("Random::PickRandomIndex - Mismatched size: expected "
               + std::to_string(amount) + ", got " + std::to_string(probability_array.size()));
           return -1;
       }
       std::discrete_distribution<> dist(probability_array.begin(), probability_array.end());
       return dist(gen);
  
   }
  }

================================================
FILE: source/Game/CS230_Final/Components/Random.h
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #pragma once
  #include <random>
  #include <vector>

#include "../../../Engine/Engine.hpp"
#include "../../../Engine/Component.h"

class Random : public CS230::Component {
public:
    Random() :gen(rd()){}

    int PickRandomIndex(size_t amount, bool same_probability, const std::vector<double>& probability_array = {});

private:
    std::random_device rd;
    std::mt19937 gen;
};

================================================
FILE: source/Game/CS230_Final/Components/Ziggle.cpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #include "Ziggle.h"

Ziggle::Ziggle(CS230::GameObject* _given_object, bool _looping, double _timer) : 
    given_object(_given_object),
    looping(_looping),
    timer(_timer){}

void Ziggle::Update(double dt) {
    if (looping == false) {
        if (timer >= 0.0 && (timer - dt) >= 0.0) {
            timer -= dt;
        }
        else {
            timer = 0.0;

        }
    }
    if (looping == true || (looping == false && timer > 0.0)) {
        if (toggle) {
            toggle = !toggle;
            given_object->SetPosition({ given_object->GetPosition().x - ziggle_velocity,given_object->GetPosition().y });
        }
        else {
            toggle = !toggle;
            given_object->SetPosition({ given_object->GetPosition().x + ziggle_velocity,given_object->GetPosition().y });
        }
    }

}

void Ziggle::Set(double new_timer) {
    timer = new_timer;
}

================================================
FILE: source/Game/CS230_Final/Components/Ziggle.h
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #pragma once
  #include "../../../Engine/Component.h"
  #include "../../../Engine/GameObject.h"

class Ziggle : public CS230::Component {
public:
    Ziggle(CS230::GameObject* , bool , double _timer = 0.0);
    void Update(double dt) override;
    void Set(double new_timer) ;
    static constexpr double ziggle_velocity = 5;
private:
    CS230::GameObject* given_object;
    bool looping;
    // bool finished = false;
    double timer;
    bool toggle = false;
};

================================================
FILE: source/Game/CS230_Final/Objects/Bus.cpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #include "Bus.h"
  #include "../../../Engine/GameStateManager.hpp"
  #include "../../Score.h"
  #include "Player.h"

Bus::Bus(Player* player_ptr) :  GameObject({ BusStartPosition, 0 }), player(player_ptr)
{
    AddGOComponent(new CS230::Sprite("Assets/sprites/CS230_Final/Bus.spt", this));
    AddGOComponent(new CS230::ShowCollision());
}

void Bus::Update(double dt)
{
    GameObject::Update(dt);

    // double player_bottom = player->GetGOComponent<CS230::RectCollision>()->WorldBoundary().Bottom();
    double player_top = player->GetGOComponent<CS230::RectCollision>()->WorldBoundary().Top();
    
    std::vector<bool>& player_can_steel = player->SetCanSteel();
    
    // line1
    if (player_top >= start_line[static_cast<int>(BusLine::line1)] && player_top < end_line[static_cast<int>(BusLine::line1)])
    {
        player_can_steel[static_cast<int>(BusLine::line1)] = true;
        player_can_steel[static_cast<int>(BusLine::line2)] = false;
        player_can_steel[static_cast<int>(BusLine::line3)] = false;
        player_can_steel[static_cast<int>(BusLine::line4)] = false;
        player_can_steel[static_cast<int>(BusLine::line5)] = false;
    }
    else if (player_top >= end_line[static_cast<int>(BusLine::line1)] && player_top < start_line[static_cast<int>(BusLine::line2)])
    {
        player_can_steel[static_cast<int>(BusLine::line1)] = false;
        player_can_steel[static_cast<int>(BusLine::line2)] = false;
        player_can_steel[static_cast<int>(BusLine::line3)] = false;
        player_can_steel[static_cast<int>(BusLine::line4)] = false;
        player_can_steel[static_cast<int>(BusLine::line5)] = false;
    }
    
    // line2
    else if (player_top >= start_line[static_cast<int>(BusLine::line2)] && player_top < end_line[static_cast<int>(BusLine::line2)])
    {
        player_can_steel[static_cast<int>(BusLine::line1)] = false;
        player_can_steel[static_cast<int>(BusLine::line2)] = true;
        player_can_steel[static_cast<int>(BusLine::line3)] = false;
        player_can_steel[static_cast<int>(BusLine::line4)] = false;
        player_can_steel[static_cast<int>(BusLine::line5)] = false;
    }
    else if (player_top >= end_line[static_cast<int>(BusLine::line2)] && player_top < start_line[static_cast<int>(BusLine::line3)])
    {
        player_can_steel[static_cast<int>(BusLine::line1)] = false;
        player_can_steel[static_cast<int>(BusLine::line2)] = false;
        player_can_steel[static_cast<int>(BusLine::line3)] = false;
        player_can_steel[static_cast<int>(BusLine::line4)] = false;
        player_can_steel[static_cast<int>(BusLine::line5)] = false;
    }
    
    // line3
    else if (player_top >= start_line[static_cast<int>(BusLine::line3)] && player_top < end_line[static_cast<int>(BusLine::line3)])
    {
        player_can_steel[static_cast<int>(BusLine::line1)] = false;
        player_can_steel[static_cast<int>(BusLine::line2)] = false;
        player_can_steel[static_cast<int>(BusLine::line3)] = true;
        player_can_steel[static_cast<int>(BusLine::line4)] = false;
        player_can_steel[static_cast<int>(BusLine::line5)] = false;
    }
    else if (player_top >= end_line[static_cast<int>(BusLine::line3)] && player_top < start_line[static_cast<int>(BusLine::line4)])
    {
        player_can_steel[static_cast<int>(BusLine::line1)] = false;
        player_can_steel[static_cast<int>(BusLine::line2)] = false;
        player_can_steel[static_cast<int>(BusLine::line3)] = false;
        player_can_steel[static_cast<int>(BusLine::line4)] = false;
        player_can_steel[static_cast<int>(BusLine::line5)] = false;
    }
    
    // line4
    else if (player_top >= start_line[static_cast<int>(BusLine::line4)] && player_top < end_line[static_cast<int>(BusLine::line4)])
    {
        player_can_steel[static_cast<int>(BusLine::line1)] = false;
        player_can_steel[static_cast<int>(BusLine::line2)] = false;
        player_can_steel[static_cast<int>(BusLine::line3)] = false;
        player_can_steel[static_cast<int>(BusLine::line4)] = true;
        player_can_steel[static_cast<int>(BusLine::line5)] = false;
    }
    else if (player_top >= end_line[static_cast<int>(BusLine::line4)] && player_top < start_line[static_cast<int>(BusLine::line5)])
    {
        player_can_steel[static_cast<int>(BusLine::line1)] = false;
        player_can_steel[static_cast<int>(BusLine::line2)] = false;
        player_can_steel[static_cast<int>(BusLine::line3)] = false;
        player_can_steel[static_cast<int>(BusLine::line4)] = false;
        player_can_steel[static_cast<int>(BusLine::line5)] = false;
    }
    
    // line5
    else if (player_top >= start_line[static_cast<int>(BusLine::line5)] && player_top < end_line[static_cast<int>(BusLine::line5)])
    {
        player_can_steel[static_cast<int>(BusLine::line1)] = false;
        player_can_steel[static_cast<int>(BusLine::line2)] = false;
        player_can_steel[static_cast<int>(BusLine::line3)] = false;
        player_can_steel[static_cast<int>(BusLine::line4)] = false;
        player_can_steel[static_cast<int>(BusLine::line5)] = true;
    }
    else if (player_top >= end_line[static_cast<int>(BusLine::line5)])
    {
        player_can_steel[static_cast<int>(BusLine::line1)] = false;
        player_can_steel[static_cast<int>(BusLine::line2)] = false;
        player_can_steel[static_cast<int>(BusLine::line3)] = false;
        player_can_steel[static_cast<int>(BusLine::line4)] = false;
        player_can_steel[static_cast<int>(BusLine::line5)] = false;
    
        const auto score = player->GetGOComponent<Score>();
        if(score == nullptr){
            throw std::runtime_error("no score, logical issue");
        }
        if (score->Value() >= 80)
        {
            is_end         = true;
            sandwich_level = SandwichLevel::GoodSandwich;
            // Engine::GetGameStateManager().PopState();
            // Engine::GetGameStateManager().PushState<GoodSandwich>();
        }
        else if (player->GetGOComponent<Score>()->Value() < 80 && player->GetGOComponent<Score>()->Value() >= 40)
        {
            is_end         = true;
            sandwich_level = SandwichLevel::NormalSandwich;
            // Engine::GetGameStateManager().PopState();
            // Engine::GetGameStateManager().PushState<NormalSandwich>();
        }
        else
        {
            is_end         = true;
            sandwich_level = SandwichLevel::BadSandwich;
            // Engine::GetGameStateManager().PopState();
            // Engine::GetGameStateManager().PushState<BadSandwich>();
        }
    }
    
    // if (player_can_steel[static_cast<int>(BusLine::line1)]) {
    //    Engine::GetLogger().LogDebug("line1 true");
    // }
    // else if (player_can_steel[static_cast<int>(BusLine::line2)]) {
    //    Engine::GetLogger().LogDebug("line2 true");
    // }
    // else if (player_can_steel[static_cast<int>(BusLine::line3)]) {
    //    Engine::GetLogger().LogDebug("line3 true");
    // }
    // else if (player_can_steel[static_cast<int>(BusLine::line4)]) {
    //    Engine::GetLogger().LogDebug("line4 true");
    // }
    // else if (player_can_steel[static_cast<int>(BusLine::line5)]) {
    //    Engine::GetLogger().LogDebug("line5 true");
    // }

}

================================================
FILE: source/Game/CS230_Final/Objects/Bus.h
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #pragma once
  #include "../../../Engine/GameObjectManager.h"
  #include "../../../Engine/Collision.h"

#include "Constants.h"
#include "../../States.h"
#include "BusLine.h"

class Player;
class Bus : public CS230::GameObject {
public:
    Bus(Player* player_ptr);
    void            Update(double dt) override;
    GameObjectTypes Type() override { return GameObjectTypes::Bus; }
    std::string        TypeName() override { return "Bus"; }
    int DrawPriority() const override { return 30; }

    int UpdatePriority() const override
    {
        return CS230::GameObject::UPDATEPRIORITY;
    }
    
    //bool            CanCollideWith(GameObjectTypes other_object_type) override;
    
    bool IsEnd() const
    {
        return is_end;
    }
    enum class SandwichLevel
    {
        GoodSandwich,
        NormalSandwich,
        BadSandwich
    }sandwich_level = SandwichLevel::NormalSandwich;

private:
    Player* player;
    bool    is_end = false;

    const std::vector<double> start_line = {
        0,144,288,432,576
    };
    
    const std::vector<double> end_line = {
        96,240,384,528,672
    };

};

================================================
FILE: source/Game/CS230_Final/Objects/BusLine.h
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #pragma once

enum class BusLine
{
    line1,
    line2,
    line3,
    line4,
    line5
};

================================================
FILE: source/Game/CS230_Final/Objects/Constants.h
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #pragma once

static constexpr int BusStartPosition = 156;
static constexpr int PlayerWidthHeight = 32;
static constexpr int PassengerWidthHeight = PlayerWidthHeight + PlayerWidthHeight / 2;
static constexpr int SeatWidthHeight = PlayerWidthHeight * 3;
static constexpr int GapHeight = PlayerWidthHeight + PlayerWidthHeight/2;
static constexpr int PassengerPadding = 20;
//static constexpr int GoodSandwichScore = 100;

================================================
FILE: source/Game/CS230_Final/Objects/Food.cpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #include "Food.h"
  #include "../../../Engine/GameStateManager.hpp"
  #include "../../../Engine/Particle.h"
  #include "../../Particles.h"
  #include "Passenger.h"

Food::Food(Passenger* _owner, Math::vec2 pos) : GameObject(pos + Math::vec2{ PassengerWidthHeight * 2 / 3, PassengerWidthHeight * 2 / 3 }), owner(_owner)
{
    AddGOComponent(new Bounce(this, GetPosition(), true));
    int result = Engine::GetGameStateManager().GetGSComponent<Random>()->PickRandomIndex(5, true); // index 0: Bread, 1: Hotdog, 2: KimBab, 3: Snack, 4: Strawberry

    switch (result)
    {
        case 0: AddGOComponent(new CS230::Sprite("Assets/sprites/CS230_Final/Bread.spt", this)); break;
        case 1: AddGOComponent(new CS230::Sprite("Assets/sprites/CS230_Final/Hotdog.spt", this)); break;
        case 2: AddGOComponent(new CS230::Sprite("Assets/sprites/CS230_Final/KimBab.spt", this)); break;
        case 3: AddGOComponent(new CS230::Sprite("Assets/sprites/CS230_Final/Snack.spt", this)); break;
        case 4: AddGOComponent(new CS230::Sprite("Assets/sprites/CS230_Final/Strawberry.spt", this)); break;
    }
    AddGOComponent(new CS230::ShowCollision());

}

void Food::Update(double dt)
{
    GameObject::Update(dt);
    if (owner->GetHasFood() == false)
    {
        const auto shining_particle = Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::Shining>>();
        if (!shining_particle)
        {
            throw std::logic_error("no shining particle");
        }
        shining_particle->Emit(1, GetPosition(), { 0, 0 }, { -10, -10 }, 3.1415926535 / 3);
        shining_particle->Emit(1, Math::vec2{ PlayerWidthHeight / 2, 0 } + GetPosition(), { 0, 0 }, { 10, 10 }, 3.1415926535 / 3);
        shining_particle->Emit(1, Math::vec2{ 0, PlayerWidthHeight / 2 } + GetPosition(), { 0, 0 }, { 10, -10 }, 3.1415926535 / 3);
        Destroy();
    }
}

================================================
FILE: source/Game/CS230_Final/Objects/Food.h
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #pragma once

#include "../../../Engine/GameObject.h"
#include "../Components/Bounce.h"
#include "../Components/Random.h"

class Passenger;

class Food : public CS230::GameObject {
public:
    Food(Passenger*, Math::vec2 pos);
    virtual int        DrawPriority() const override { return 33; }

    int UpdatePriority() const override
    {
        return CS230::GameObject::UPDATEPRIORITY + 2;
    }
    GameObjectTypes Type() override { return GameObjectTypes::Food; }
    std::string        TypeName() override { return "Food"; }
    void            Update(double dt) override;

private:
    Passenger* owner;
};

================================================
FILE: source/Game/CS230_Final/Objects/Obstacle.cpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #include "Obstacle.h"
  #include "Player.h"
  #include "../../../Engine/GameStateManager.hpp"
  Obstacle::Obstacle(Player* _player, Math::vec2 pos) :
   GameObject(pos),
   player(_player)
  {
   int result = Engine::GetGameStateManager().GetGSComponent<Random>()->PickRandomIndex(2,true);// index 0: Bomb, 1: Shoes
   switch (result)
   {
   case 0:
  
       AddGOComponent(new CS230::Sprite("Assets/sprites/CS230_Final/Bomb.spt", this));
       break;
  
   case 1:
  
       AddGOComponent(new CS230::Sprite("Assets/sprites/CS230_Final/Shoes.spt", this));
       break;
  
   }
   AddGOComponent(new CS230::ShowCollision());
  }

bool Obstacle::CanCollideWith(GameObjectTypes other_object_type) {
    if (other_object_type == GameObjectTypes::Player) {
        return true;
    }
    return false;
}

void Obstacle::ResolveCollision(GameObject* other_object) {
    if (other_object->Type() == GameObjectTypes::Player) {
        player->GetGOComponent<Score>()->Sub(10);
        Destroy();
    }
}

================================================
FILE: source/Game/CS230_Final/Objects/Obstacle.h
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #pragma once
  #include "../../../Engine/GameObject.h"
  #include "../../Score.h"
  #include "../Components/Random.h"
  #include "../Components/Ziggle.h"

class Player;
class Obstacle : public CS230::GameObject {
public:
    Obstacle(Player*, Math::vec2 pos);
    int            DrawPriority() const override{ return 32; }

    int UpdatePriority() const override
    {
        return CS230::GameObject::UPDATEPRIORITY + 3;
    }
    GameObjectTypes        Type() override { return GameObjectTypes::Obstacle; }
    std::string            TypeName() override { return "Obstacle"; }
    
    bool                CanCollideWith(GameObjectTypes other_object_type) override;
    void                ResolveCollision(GameObject* other_object) override;

private:
    Player* player;
};

================================================
FILE: source/Game/CS230_Final/Objects/Passenger.cpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #include "Passenger.h"
  #include "../../../Engine/ShowCollision.h"
  #include "../../../Engine/Timer.hpp"
  #include "../../Score.h"

Passenger::Passenger(BusLine _busline, Player* _player, int is_right)
    : GameObject(
          { BusStartPosition + static_cast<double>(is_right * SeatWidthHeight * 2) + PassengerPadding,
            static_cast<double>(static_cast<int>(_busline) * (SeatWidthHeight + GapHeight)) + PassengerPadding }),
      player(_player), busline(_busline)
{
    AddGOComponent(new CS230::Sprite("Assets/sprites/CS230_Final/Passenger.spt", this));
    AddGOComponent(new util::Timer());
    AddGOComponent(new CS230::ShowCollision());
    current_state = &state_idle;
    current_state->Enter(this);
    Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new Food(this, GetPosition()));
}

bool Passenger::CanCollideWith(GameObjectTypes other_object_type)
{
    if (other_object_type == GameObjectTypes::Player)
    {
        return true;
    }
    return false;
}

void Passenger::ResolveCollision(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Player)
    {
        if (has_food == true && get_mad == false)
        {
            if (player->GetCanSteel()[static_cast<size_t>(busline)] == true)
            {
                has_food = false;
                change_state(&state_sad);
            }
            else
            {
                get_mad = true;
                change_state(&state_angry);
            }
        }
    }
}

void Passenger::State_Idle::Enter([[maybe_unused]] GameObject* object)
{
    Passenger* passenger = static_cast<Passenger*>(object);
    passenger->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
}

void Passenger::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{
}

void Passenger::State_Idle::CheckExit([[maybe_unused]] GameObject* object)
{
}

void Passenger::State_Angry::Enter([[maybe_unused]] GameObject* object)
{
    Passenger* passenger = static_cast<Passenger*>(object);
    passenger->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Angry));
    passenger->player->GetGOComponent<Score>()->Sub(10);
}

void Passenger::State_Angry::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{
}

void Passenger::State_Angry::CheckExit([[maybe_unused]] GameObject* object)
{
}

void Passenger::State_Sad::Enter([[maybe_unused]] GameObject* object)
{
    Passenger* passenger = static_cast<Passenger*>(object);
    passenger->player->GetGOComponent<Score>()->Add(20);
    passenger->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Sad));
    const auto timer = passenger->GetGOComponent<util::Timer>();
    if (!timer)
    {
        throw std::logic_error("No Timer in Passenger!");
    }
    else
    {
        timer->ResetTimeStamp();
    }
    const auto tears_particle = Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::Tears>>();
    if (tears_particle)
    {
       tears_particle->Emit(1, Math::vec2{ 10, PassengerWidthHeight * 2 / 3 } + passenger->GetPosition(), { 0, 0 }, { -10, -10 }, 3.1415926535 / 3);
        tears_particle->Emit(1, Math::vec2{ PassengerWidthHeight - 10, PassengerWidthHeight * 2 / 3 } + passenger->GetPosition(), { 0, 0 }, { 10, -10 }, 3.1415926535 / 3);
    }
}

void Passenger::State_Sad::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{
    Passenger* passenger = static_cast<Passenger*>(object);
    const auto timer = passenger->GetGOComponent<util::Timer>();
    if ((timer)&&(timer->GetElapsedSeconds() >= cry_timer))
    {
        if (!timer)
        {
            throw std::logic_error("No Timer in Passenger!");
        }
        else{
            timer->ResetTimeStamp();
        }

        const auto tears_particle = Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::Tears>>();
        if (tears_particle)
        {
            tears_particle->Emit(1, Math::vec2{ 10, PassengerWidthHeight * 2 / 3 } + passenger->GetPosition(), { 0, 0 }, { -10, -10 }, 3.1415926535 / 3);
            tears_particle->Emit(1, Math::vec2{ PassengerWidthHeight - 10, PassengerWidthHeight * 2 / 3 } + passenger->GetPosition(), { 0, 0 }, { 10, -10 }, 3.1415926535 / 3);
        }
    }

}

void Passenger::State_Sad::CheckExit([[maybe_unused]] GameObject* object)
{
}

================================================
FILE: source/Game/CS230_Final/Objects/Passenger.h
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #pragma once
  #include <random>

#include "../../../Engine/GameObject.h"
#include "../../../Engine/Particle.h"
#include "../../../Engine/Timer.hpp"

#include "BusLine.h"
#include "Player.h"
#include "Constants.h"
#include "../../../Engine/Fonts.h"
#include "../../Particles.h"
#include "Food.h"

class Passenger : public CS230::GameObject {
public:
    Passenger(BusLine ,Player* , int is_right);
    GameObjectTypes        Type() override { return GameObjectTypes::Passenger; }
    std::string            TypeName() override { return "Passenger"; }

    int DrawPriority() const override
    {
        return 31;
    }
    
    int UpdatePriority() const override
    {
        return CS230::GameObject::UPDATEPRIORITY + 1;
    }
    bool                CanCollideWith(GameObjectTypes other_object_type) override;
    void                ResolveCollision(GameObject* other_object) override;
    
    bool                GetHasFood() const { return has_food; }

private:
    static constexpr double cry_timer = 1.0;
    Player*                 player;
    BusLine                 busline;
    bool                    has_food = true;
    bool                    get_mad = false;

    enum class Animations {
        Idle,
        Angry,
        Sad
    };
    
    
    class State_Idle : public CS230::GameObject::State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };
    
    State_Idle state_idle;
    
    class State_Angry : public CS230::GameObject::State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Angry"; }
    };
    
    State_Angry state_angry;
    
    class State_Sad : public CS230::GameObject::State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Sad"; }
    };
    
    State_Sad state_sad;

};

================================================
FILE: source/Game/CS230_Final/Objects/Player.cpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #include "Player.h"
  #include "../../../Engine/Window.hpp"
  #include "../../../Engine/Input.hpp"
  #include "../../../Engine/TextManager.hpp"

Player::Player() : 
    GameObject({ BusStartPosition+SeatWidthHeight + SeatWidthHeight/2 - PlayerWidthHeight/2,0 })
{
    AddGOComponent(new CS230::Sprite("Assets/sprites/CS230_Final/Player.spt", this));
    AddGOComponent(new Score(0));
    AddGOComponent(new Ziggle(this, false,0.0));
    AddGOComponent(new CS230::ShowCollision());
    score = GetGOComponent<Score>()->Value();
    //score_texture = (Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Score", 0xFFFFFFFF));
    //score_amount_texture = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture(std::to_string(score), 0xFFFFFFFF);
    window_height = Engine::GetWindow().GetSize().y;
    SetVelocity({ 0,0 });
}

void Player::Update([[maybe_unused]] double dt) {
    GameObject::Update(dt);
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
        SetVelocity({ player_velocity.x,GetVelocity().y});
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left)) {
        SetVelocity({ -player_velocity.x,GetVelocity().y });
    }
    else {
        SetVelocity({ 0,GetVelocity().y });
    }

    //if (Engine::GetInput().KeyDown(CS230::Input::Keys::Up)) {
    //    SetVelocity({ GetVelocity().x,player_velocity.y });
    //}
    //else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Down)) {
    //    SetVelocity({ GetVelocity().x,-player_velocity.y });
    //}
    //else {
    //    SetVelocity({ GetVelocity().x,0 });
    //}
    update_score_text();

}

void Player::Draw(Math::TransformationMatrix camera_matrix, unsigned int color, float depth)
{
    GameObject::Draw(camera_matrix,color,depth);
    auto& text_manager = Engine::GetTextManager();
    text_manager.DrawText("Score", Math::vec2{ 0, window_height - 68 }, Fonts::Outlined, { 1.0, 1.0 }, 0xFFFFFFFF);
    text_manager.DrawText(std::to_string(score), Math::vec2{ 0, window_height - 68 - 68 }, Fonts::Outlined, { 1.0, 1.0 }, 0xFFFFFFFF);
}

bool Player::CanCollideWith(GameObjectTypes other_object_type) {
    if (other_object_type == GameObjectTypes::Passenger || other_object_type == GameObjectTypes::Obstacle) {
        return true;
    }
    return false;
}

void Player::ResolveCollision(GameObject* other_object) {
    if (other_object->Type() == GameObjectTypes::Passenger) {
        Math::rect player_rect = GetGOComponent<CS230::RectCollision>()->WorldBoundary();
        Math::rect passenger_rect = other_object->GetGOComponent<CS230::RectCollision>()->WorldBoundary();

        if (player_rect.Left() < passenger_rect.Left()) {
            UpdatePosition(Math::vec2{ (passenger_rect.Left() - player_rect.Right()-7), 0.0 });
            SetVelocity({ 0, GetVelocity().y });
        }
        else {
            UpdatePosition(Math::vec2{ (passenger_rect.Right() - player_rect.Left()+7), 0.0 });
            SetVelocity({ 0, GetVelocity().y });
        }
    }
    else if (other_object->Type() == GameObjectTypes::Obstacle) {
        GetGOComponent<Ziggle>()->Set(0.5);
    }

}

void Player::update_score_text() {
    const auto current_score = GetGOComponent<Score>();
    if ((current_score)&& (score != current_score->Value())) {
        score = current_score->Value();
    }
}

================================================
FILE: source/Game/CS230_Final/Objects/Player.h
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #pragma once

#include "../../../Engine/GameObject.h"

#include "Bus.h"
#include "Constants.h"
#include "Passenger.h"
#include "../../Score.h"
#include "../Components/Ziggle.h"

class Player : public CS230::GameObject {
public:
    Player();
    void                Update(double dt) override;
    void Draw(Math::TransformationMatrix camera_matrix, unsigned int color = 0xFFFFFFFF, float depth = 0.5f) override;
    GameObjectTypes        Type() override { return GameObjectTypes::Player; }
    std::string            TypeName() override { return "Player"; }

    bool                CanCollideWith(GameObjectTypes other_object_type) override;
    void                ResolveCollision(GameObject* other_object) override;
    
    
    int                    DrawPriority() const override { return 31; }
    int                    UpdatePriority() const override { return CS230::GameObject::UPDATEPRIORITY + 2; }
    
    const Math::vec2&    GetPosition() const { return GameObject::GetPosition(); }
    
    std::vector<bool>&            SetCanSteel() { return can_steel; }
    const std::vector<bool>&    GetCanSteel() const{ return can_steel; }
    
    //int                            GetScore() { return score; }

private:
    const Math::vec2    player_velocity = { 96.0,96.0 };

    int                    score = 0;
    // CS230::Texture*        score_texture = nullptr;
    // CS230::Texture*        score_amount_texture = nullptr;
    void                update_score_text();
    
    std::vector<bool>    can_steel = { false,false,false,false,false };
    
    double window_height;

};

================================================
FILE: source/Game/CS230_Final/States/BadSandwich.cpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #include "BadSandwich.h"
  #include "Project.h"
  #include "../../MainMenu.h"
  #include "../../../Engine/TextureManager.hpp"
  #include "../../../Engine/GameStateManager.hpp"
  #include "../../../Engine/Input.hpp"
  #include "../../../Engine/Window.hpp"

#include "CS200/NDC.hpp"
void BadSandwich::Load() {
    texture = Engine::GetTextureManager().Load("Assets/images/CS230_Final/BadSandwich.png");
}

void BadSandwich::Update([[maybe_unused]] double dt) {
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape))
    {
        Engine::GetGameStateManager().PopState();
        Engine::GetGameStateManager().PushState<MainMenu>();
    }

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R))
    {
        Engine::GetGameStateManager().PopState();
        Engine::GetGameStateManager().PushState<Project>();
    }

}

void BadSandwich::Unload() {

}

void BadSandwich::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
    auto renderer_2d = Engine::GetTextureManager().GetRenderer2D();
    renderer_2d->BeginScene(CS200::build_ndc_matrix(Engine::GetWindow().GetSize()));
    texture->Draw(Math::TransformationMatrix());

    renderer_2d->EndScene();

}

================================================
FILE: source/Game/CS230_Final/States/BadSandwich.h
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #pragma once
  #include "../../../Engine/GameState.hpp"
  #include "../../../Engine/Engine.hpp"
  #include "../../../Engine/Texture.hpp"

class BadSandwich : public CS230::GameState {
public:
    BadSandwich(){}

    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;
    void DrawImGui() override { };
    
    gsl::czstring GetName() const override
    {
        return "Bad Sandwich";
    }

private:
    std::shared_ptr<CS230::Texture> texture;
};

================================================
FILE: source/Game/CS230_Final/States/GoodSandwich.cpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #include "GoodSandwich.h"
  #include "Project.h"
  #include "../../MainMenu.h"
  #include "../../../Engine/TextureManager.hpp"
  #include "../../../Engine/GameStateManager.hpp"
  #include "../../../Engine/Input.hpp"
  #include "../../../Engine/Window.hpp"

#include "CS200/NDC.hpp"
void GoodSandwich::Load() {
    texture = Engine::GetTextureManager().Load("Assets/images/CS230_Final/GoodSandwich.png");
}

void GoodSandwich::Update([[maybe_unused]] double dt) {
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape))
    {
        Engine::GetGameStateManager().PopState();
        Engine::GetGameStateManager().PushState<MainMenu>();
    }

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R))
    {
        Engine::GetGameStateManager().PopState();
        Engine::GetGameStateManager().PushState<Project>();
    }

}

void GoodSandwich::Unload() {

}

void GoodSandwich::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
    auto renderer_2d = Engine::GetTextureManager().GetRenderer2D();
    renderer_2d->BeginScene(CS200::build_ndc_matrix(Engine::GetWindow().GetSize()));
    texture->Draw(Math::TransformationMatrix());

    renderer_2d->EndScene();

}

================================================
FILE: source/Game/CS230_Final/States/GoodSandwich.h
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #pragma once
  #include "../../../Engine/Engine.hpp"
  #include "../../../Engine/Texture.hpp"
  #include "../../../Engine/GameState.hpp"

class GoodSandwich : public CS230::GameState {
public:
    GoodSandwich(){}

    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;
    void DrawImGui() override { };
    
    gsl::czstring GetName() const override
    {
        return "Good Sandwich";
    }

private:
    std::shared_ptr<CS230::Texture> texture;
};

================================================
FILE: source/Game/CS230_Final/States/NormalSandwich.cpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #include "NormalSandwich.h"
  #include "Project.h"
  #include "../../MainMenu.h"
  #include "../../../Engine/TextureManager.hpp"
  #include "../../../Engine/GameStateManager.hpp"
  #include "../../../Engine/Input.hpp"
  #include "../../../Engine/Window.hpp"

#include "CS200/NDC.hpp"
void NormalSandwich::Load() {
    texture = Engine::GetTextureManager().Load("Assets/images/CS230_Final/NormalSandwich.png");
}

void NormalSandwich::Update([[maybe_unused]] double dt) {
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape)) {
        Engine::GetGameStateManager().PopState();
        Engine::GetGameStateManager().PushState<MainMenu>();
    }

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R)) {
        Engine::GetGameStateManager().PopState();
        Engine::GetGameStateManager().PushState<Project>();
    }

}

void NormalSandwich::Unload() {

}

void NormalSandwich::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
    auto renderer_2d = Engine::GetTextureManager().GetRenderer2D();
    renderer_2d->BeginScene(CS200::build_ndc_matrix(Engine::GetWindow().GetSize()));
    texture->Draw(Math::TransformationMatrix());

    renderer_2d->EndScene();

}

================================================
FILE: source/Game/CS230_Final/States/NormalSandwich.h
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #pragma once
  #include "../../../Engine/GameState.hpp"
  #include "../../../Engine/Engine.hpp"
  #include "../../../Engine/Texture.hpp"

class NormalSandwich : public CS230::GameState
{
public:
    NormalSandwich()
    {
    }

    void          Load() override;
    void          Update(double dt) override;
    void          Unload() override;
    void          Draw() override;
    void          DrawImGui() override { };
    
    gsl::czstring GetName() const override
    {
        return "NormalSandwich";
    }

private:
    std::shared_ptr<CS230::Texture> texture;
};

================================================
FILE: source/Game/CS230_Final/States/Project.cpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #include "Project.h"
  #include "../../MainMenu.h"
  #include "BadSandwich.h"
  #include "Engine/Input.hpp"
  #include "Engine/TextureManager.hpp"
  #include "Engine/Window.hpp"
  #include "GoodSandwich.h"
  #include "NormalSandwich.h"
  #include "OpenGL/Environment.hpp"
  #include <SDL.h>
  #include <imgui.h>

#include "CS200/IRenderer2D.hpp"
#include "CS200/NDC.hpp"
#include "CS200/RenderingAPI.hpp"

Project::Project() : player_ptr(nullptr)
// camera(nullptr)
{
}

void Project::Load()
{
    Engine::GetLogger().LogDebug("CS230 Final start loading");
    Engine::GetTextureManager().SwitchRenderer(CS230::TextureManager::RendererType::Immediate);
    // srand(static_cast<unsigned int>(time(NULL)));
    // Engine::GetWindow().SetSize({ default_width, default_height });
    /*camera = new CS230::Camera({ Math::vec2{ 0,0 }, static_cast<Math::vec2>(Engine::GetWindow().GetSize()) });
    camera->SetLimit({ {0,0},Engine::GetWindow().GetSize() });
    AddGSComponent(camera);*/
    // GetGSComponent<CS230::Camera>()->SetPosition({ 0.0, 0.0 });
    if (!OpenGL::IsWebGL)
    {
        Engine::GetWindow().ForceResize(600, 800);
        Engine::GetWindow().SetWindowPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    }

#ifdef DEVELOPER_VERSION
    AddGSComponent(new CS230::ShowCollision());
    AddGSComponent(new Grid());
#endif
    AddGSComponent(new Random());
    AddGSComponent(new CS230::GameObjectManager);
    AddGSComponent(new CS230::ParticleManager<Particles::Tears>());
    AddGSComponent(new CS230::ParticleManager<Particles::Shining>());

    player_ptr = new Player();
    GetGSComponent<CS230::GameObjectManager>()->Add(player_ptr);
    bus_ptr = new Bus(player_ptr);
    GetGSComponent<CS230::GameObjectManager>()->Add(bus_ptr);
    GetGSComponent<CS230::GameObjectManager>()->Add(new Passenger(BusLine::line1, player_ptr, 0));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Passenger(BusLine::line2, player_ptr, 0));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Passenger(BusLine::line3, player_ptr, 0));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Passenger(BusLine::line4, player_ptr, 0));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Passenger(BusLine::line5, player_ptr, 0));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Passenger(BusLine::line1, player_ptr, 1));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Passenger(BusLine::line2, player_ptr, 1));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Passenger(BusLine::line3, player_ptr, 1));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Passenger(BusLine::line4, player_ptr, 1));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Passenger(BusLine::line5, player_ptr, 1));
    GetGSComponent<CS230::GameObjectManager>()->Add(
        new Obstacle(player_ptr, { (BusStartPosition + SeatWidthHeight + PlayerWidthHeight * (static_cast<double>(rand()) / RAND_MAX) * 2), SeatWidthHeight * 2 }));
    GetGSComponent<CS230::GameObjectManager>()->Add(
        new Obstacle(player_ptr, { (BusStartPosition + SeatWidthHeight + PlayerWidthHeight * (static_cast<double>(rand()) / RAND_MAX) * 2), SeatWidthHeight * 3 }));
    GetGSComponent<CS230::GameObjectManager>()->Add(
        new Obstacle(player_ptr, { (BusStartPosition + SeatWidthHeight + PlayerWidthHeight * (static_cast<double>(rand()) / RAND_MAX) * 2), SeatWidthHeight * 5 }));
    
    CS200::RenderingAPI::SetClearColor(0x000000FF);
    
    Engine::GetLogger().LogDebug("CS230 Final finish loading");

}

void Project::Update([[maybe_unused]] double dt)
{
    UpdateGSComponents(dt);

    GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);
    
    // Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->SortForDraw();
    Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->SortForUpdate();
    if (bus_ptr->IsEnd())
    {
        Bus::SandwichLevel level = bus_ptr->sandwich_level;
        switch (level)
        {
            case Bus::SandwichLevel::GoodSandwich:
                Engine::GetGameStateManager().PopState();
                Engine::GetGameStateManager().PushState<GoodSandwich>();
                break;
            case Bus::SandwichLevel::NormalSandwich:
                Engine::GetGameStateManager().PopState();
                Engine::GetGameStateManager().PushState<NormalSandwich>();
                break;
            case Bus::SandwichLevel::BadSandwich:
                Engine::GetGameStateManager().PopState();
                Engine::GetGameStateManager().PushState<BadSandwich>();
                break;
            default: break;
        }
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape))
    {
        Engine::GetGameStateManager().PopState();
        Engine::GetGameStateManager().PushState<MainMenu>();
    }

}

void Project::Unload()
{
    GetGSComponent<CS230::GameObjectManager>()->Unload();
    ClearGSComponents();
    player_ptr = nullptr;
    bus_ptr       = nullptr;
    // camera = nullptr;
}

void Project::Draw()
{
    CS200::RenderingAPI::Clear();
    auto renderer_2d = Engine::GetTextureManager().GetRenderer2D();
    renderer_2d->BeginScene(CS200::build_ndc_matrix(Engine::GetWindow().GetSize()));
    // Math::TransformationMatrix camera_matrix = camera->GetMatrix();
#ifdef DEVELOPER_VERSION
    GetGSComponent<Grid>()->Draw(Grid::DotColor::black, 0.2f);
#endif
    GetGSComponent<CS230::GameObjectManager>()->DrawAll(Math::TransformationMatrix());

    renderer_2d->EndScene();

}

void Project::DrawImGui()
{
    ImGui::Begin("Renderer Settings");
    ImGui::Separator();

    // Renderer selection
    auto&       texture_manager         = Engine::GetTextureManager();
    const auto current_renderer_type = texture_manager.GetCurrentRendererType();
    // const auto renderer_2d = texture_manager.GetRenderer2D();
    ImGui::Text("Renderer:");
    if (ImGui::RadioButton("Immediate", current_renderer_type == CS230::TextureManager::RendererType::Immediate))
    {
        texture_manager.SwitchRenderer(CS230::TextureManager::RendererType::Immediate);
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Batch", current_renderer_type == CS230::TextureManager::RendererType::Batch))
    {
        texture_manager.SwitchRenderer(CS230::TextureManager::RendererType::Batch);
    }
    
    ImGui::SameLine();
    if (ImGui::RadioButton("Instanced", current_renderer_type == CS230::TextureManager::RendererType::Instanced))
    {
        texture_manager.SwitchRenderer(CS230::TextureManager::RendererType::Instanced);
    }
    ImGui::Separator();
    
    ImGui::End();

}

gsl::czstring Project::GetName() const
{
    return "Final Project";
}

================================================
FILE: source/Game/CS230_Final/States/Project.h
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Spring
* \par CS230
* \copyright DigiPen Institute of Technology
  */
  #pragma once
  #include "Engine/GameState.hpp"
  #include "Engine/Texture.hpp"
  #include "Engine/Camera.h"
  #include "Engine/GameObjectManager.h"

#include "../Components/Grid.h"
#include "../Objects/Player.h"
#include "../Objects/Bus.h"
#include "../Objects/BusLine.h"
#include "../Objects/Passenger.h"
#include "../../Particles.h"
#include "../Objects/Obstacle.h"
#include "../Components/Random.h"
class Project : public CS230::GameState {
public:
    Project();
    void          Load() override;
    void          Update(double dt) override;
    void          Unload() override;
    void          Draw() override;
    void          DrawImGui() override;
    gsl::czstring GetName() const override;

private:
    Player* player_ptr;
    Bus* bus_ptr;
    //CS230::Camera* camera;
    //static constexpr int default_width = 600;
    //static constexpr int default_height = 800;
};

================================================
FILE: source/Game/States/ConsoleTest.cpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "ConsoleTest.h"
  #include "Engine/Engine.hpp"
  #include "Engine/Input.hpp"
  #include "Engine/GameStateManager.hpp"
  #include "Engine/Window.hpp"
  #include "Engine/TextureManager.hpp"

#include "CS200/IRenderer2D.hpp"
#include "CS200/NDC.hpp"

#include "Game/MainMenu.h"

#include <imgui.h>

ConsoleTest::ConsoleTest()
{
}

void ConsoleTest::Load()
{

}

void ConsoleTest::Update([[maybe_unused]] double dt)
{
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape))
    {
        Engine::GetGameStateManager().PopState();
        Engine::GetGameStateManager().PushState<MainMenu>();
    }

}

void ConsoleTest::Draw()
{
    Engine::GetWindow().Clear(0x1a1a1aff);
    auto renderer_2d = Engine::GetTextureManager().GetRenderer2D();

    renderer_2d->BeginScene(CS200::build_ndc_matrix(Engine::GetWindow().GetSize()));
    
    
    renderer_2d->EndScene();

}

void ConsoleTest::DrawImGui()
{
    ImGui::Begin("Tests");

    ImGui::End();

}

void ConsoleTest::Unload()
{
}

================================================
FILE: source/Game/States/ConsoleTest.h
================================================
/**

* \file

* \author Taekyung Ho

* \date 2025 Fall

* \par CS200 Computer Graphics I

* \copyright DigiPen Institute of Technology
  */
  #pragma once
  #include "./Engine/GameState.hpp"
  class ConsoleTest : public CS230::GameState
  {
  public:
   ConsoleTest();
   void          Load() override;
   void          Update(double dt) override;
   void          Unload() override;
   void          Draw() override;
   void          DrawImGui() override;
  
   gsl::czstring GetName() const override
   {
  
       return "Console Test";
  
   }
  };

================================================
FILE: source/Game/States/RenderingTest.cpp
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "RenderingTest.h"
  #include "Engine/Engine.hpp"
  #include "Engine/GameStateManager.hpp"
  #include "Engine/Input.hpp"
  #include "Engine/ShowCollision.h"
  #include "Engine/TextureManager.hpp"
  #include "Engine/Window.hpp"
  #include "Engine/Camera.h"

#include "Engine/Particle.h"
#include <imgui.h>
#include <numbers>

#include "./CS200/IRenderer2D.hpp"
#include "./CS200/NDC.hpp"
#include "CS200/RenderingAPI.hpp"

#include "Game/CS230_Final/Components/Grid.h"
#include "Game/MainMenu.h"
#include "Game/Particles.h"

#include "Demo/DemoSceneShowcase/Samurai.h"

#include <numbers>

void RenderingTest::Load()
{
    Engine::GetTextureManager().SwitchRenderer(CS230::TextureManager::RendererType::Immediate);
#ifdef DEVELOPER_VERSION
    AddGSComponent(new CS230::ShowCollision());
    //AddGSComponent(new Grid());
#endif
    AddGSComponent(new CS230::GameObjectManager);
    //testTexture = Engine::GetTextureManager().Load("Assets/images/Test/mario.png");

    samurai = new Samurai();
    GetGSComponent<CS230::GameObjectManager>()->Add(samurai);
    //AddGSComponent(new CS230::ParticleManager<Particles::Tears>());
    //AddGSComponent(new CS230::ParticleManager<Particles::Shining>());
    //AddGSComponent(new CS230::ParticleManager<Particles::Flame>());
    //AddGSComponent(new CS230::Camera(Math::rect{ static_cast<Math::vec2>(Engine::GetWindow().GetSize()) * 0.3, static_cast<Math::vec2>(Engine::GetWindow().GetSize()) * 0.7 }));
    //GetGSComponent<CS230::Camera>()->SetLimit({ {0,0},{3000,3000} });
    //GetGSComponent<CS230::Camera>()->SetAnchoring() = true;
    //GetGSComponent<CS230::Camera>()->SetPosition(samurai->GetPosition());
    //GetGSComponent<CS230::Camera>()->SetFirstPersonView() = first_person_view;
    //GetGSComponent<CS230::Camera>()->SetScale(camera_scale);
    //GetGSComponent<CS230::Camera>()->SetRotation(camera_rotation);
    
    CS200::RenderingAPI::SetClearColor(CS200::WHITE);

}

void RenderingTest::Update([[maybe_unused]] double dt)
{
    UpdateGSComponents(dt);

    //GetGSComponent<CS230::Camera>()->Update(samurai->GetPosition());
    
    GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape)) // very bottom!!
    {
        Engine::GetGameStateManager().PopState();
        Engine::GetGameStateManager().PushState<MainMenu>();
        return;
    }

}

void RenderingTest::Draw()
{
    CS200::RenderingAPI::Clear();
    auto renderer_2d = Engine::GetTextureManager().GetRenderer2D();
    renderer_2d->BeginScene(CS200::build_ndc_matrix(Engine::GetWindow().GetSize(),false) /** GetGSComponent<CS230::Camera>()->GetMatrix()*/);
    GetGSComponent<CS230::GameObjectManager>()->DrawAll(Math::TransformationMatrix());

#ifdef DEVELOPER_VERSION
    //GetGSComponent<Grid>()->Draw(Grid::DotColor::white, 0.2f);
#endif

    //testTexture->Draw(
    //    Math::TranslationMatrix(Math::to_vec2(translate)) * Math::RotationMatrix(static_cast<double>(rotate / 180 * std::numbers::pi_v<float>)) * Math::ScaleMatrix(Math::to_vec2(scale)));
    renderer_2d->EndScene();

}

void RenderingTest::DrawImGui()
{
    if (Engine::GetWindow().GetSize() != window_size)
    {
        window_size = Engine::GetWindow().GetSize();
    }

    //if (ImGui::Begin("Texture Controls"))
    //{
    //    ImGui::SliderFloat("Scale X", &(scale.x), -20.f, 20.0f, "%.1f px/s");
    //    ImGui::SliderFloat("Scale Y", &(scale.y), -20.f, 20.0f, "%.1f px/s");
    //    ImGui::SliderFloat("Rotate", &rotate, 0.f, 360.0f, "%.1f px/s");
    //    ImGui::SliderFloat("Translate X", &(translate.x), 0.0f, static_cast<float>(window_size.x) - 100.f, "%.1f px/s");
    //    ImGui::SliderFloat("Translate Y", &(translate.y), 0.0f, static_cast<float>(window_size.y) - 100.f, "%.1f px/s");
    //}
    //ImGui::End();
    
    /*if (ImGui::Begin("Particle Controls"))
    {
        if (ImGui::Button("Shine"))
        {
            const auto shining_particle = Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::Shining>>();
            if (!shining_particle)
            {
                throw std::logic_error("no shining particle");
            }
            shining_particle->Emit(10, Math::to_vec2(translate), { 0, 0 }, { 20, 20 }, std::numbers::pi * 2);
        }
        ImGui::SameLine();
    
        if (ImGui::Button("Tears"))
        {
            const auto tears_particle = Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::Tears>>();
            if (tears_particle)
            {
                tears_particle->Emit(10, Math::to_vec2(translate), { 0, 0 }, { -20, -20 }, std::numbers::pi * 2);
            }
        }
    
        ImGui::SameLine();
    
        if (ImGui::Button("Flame"))
        {
            const auto tears_particle = Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::Flame>>();
            if (tears_particle)
            {
                tears_particle->Emit(1, Math::to_vec2(translate), { 0, 0 }, { 0, 20 }, std::numbers::pi * 2, 0xF36301FF);
            }
        }
    }
    ImGui::End();*/
    
    ImGui::Begin("Renderer Settings");
    ImGui::Separator();
    
    // Renderer selection
    auto&       texture_manager         = Engine::GetTextureManager();
    const auto current_renderer_type = texture_manager.GetCurrentRendererType();
    // const auto renderer_2d = texture_manager.GetRenderer2D();
    ImGui::Text("Renderer:");
    
    if (ImGui::RadioButton("Immediate", current_renderer_type == CS230::TextureManager::RendererType::Immediate))
    {
        texture_manager.SwitchRenderer(CS230::TextureManager::RendererType::Immediate);
    }
    
    ImGui::SameLine();
    
    if (ImGui::RadioButton("Batch", current_renderer_type == CS230::TextureManager::RendererType::Batch))
    {
        texture_manager.SwitchRenderer(CS230::TextureManager::RendererType::Batch);
    }
    
    ImGui::SameLine();
    if (ImGui::RadioButton("Instanced", current_renderer_type == CS230::TextureManager::RendererType::Instanced))
    {
        texture_manager.SwitchRenderer(CS230::TextureManager::RendererType::Instanced);
    }
    ImGui::Separator();
    
    ImGui::End();
    
    /*ImGui::Begin("Camera Controls");
    float fcamera_rotation = static_cast<float>(camera_rotation);
    if (ImGui::SliderFloat("Camera Rotation", &fcamera_rotation, -180.f, 180.f))
    {
        camera_rotation = static_cast<double>(fcamera_rotation);
        GetGSComponent<CS230::Camera>()->SetRotation(static_cast<double>(camera_rotation / 180.f * std::numbers::pi_v<float>));
    }
    Math::fvec2 fcamera_scale = Math::to_fvec2(camera_scale);
    bool scale_changed = false;
    if (ImGui::SliderFloat("Camera ScaleX", &fcamera_scale.x, 0.1f, 10.f))
    {
        camera_scale.x = static_cast<double>(fcamera_scale.x);
        scale_changed = true;
    }
    if (ImGui::SliderFloat("Camera ScaleY", &fcamera_scale.y, 0.1f, 10.f))
    {
        camera_scale.y = static_cast<double>(fcamera_scale.y);
        scale_changed = true;
    }
    if (scale_changed)
    {
        GetGSComponent<CS230::Camera>()->SetScale(camera_scale);
    }
    
    if (ImGui::Checkbox("First Person View", &first_person_view))
    {
        GetGSComponent<CS230::Camera>()->SetFirstPersonView() = first_person_view;
    }
    ImGui::End();*/

}

void RenderingTest::Unload()
{
    GetGSComponent<CS230::GameObjectManager>()->Unload();
    ClearGSComponents();
}

================================================
FILE: source/Game/States/RenderingTest.h
================================================
/**

* \file
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once
  #include <memory>

#include "./Engine/GameState.hpp"
#include "./Engine/Texture.hpp"

#include "Demo/DemoSceneShowcase/Samurai.h"

class RenderingTest : public CS230::GameState
{
public:
    RenderingTest() = default;
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;
    void DrawImGui() override;

    gsl::czstring GetName() const override
    {
        return "Rendering Test";
    }

private:
    Samurai*                        samurai = nullptr;
    //std::shared_ptr<CS230::Texture> testTexture = nullptr;
    //Math::fvec2 scale = {1.f,1.f};
    //float rotate = 0.f;
    //Math::fvec2 translate = {0.f,0.f};
    Math::ivec2 window_size;

    //double camera_rotation = 0.0;
    //Math::vec2 camera_scale = { 1.0, 1.0 };
    
    //bool first_person_view = true;

};

================================================
FILE: source/OpenGL/Buffer.cpp
================================================
/**

* \file
* \author Rudy Castan
* \author Taekyung ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "Buffer.hpp"

#include "GL.hpp"

namespace OpenGL
{
    BufferHandle CreateBuffer(BufferType type, GLsizeiptr size_in_bytes) noexcept
    {
        BufferHandle new_buffer{};
        GL::GenBuffers(1, &new_buffer);
        GL::BindBuffer(static_cast<GLenum>(type), new_buffer);
        GL::BufferData(static_cast<GLenum>(type), size_in_bytes, nullptr, GL_DYNAMIC_DRAW);
        GL::BindBuffer(static_cast<GLenum>(type), 0);
        // https://docs.gl/es3/glGenBuffers
        // https://docs.gl/es3/glBindBuffer
        // https://docs.gl/es3/glBufferData
        return new_buffer;
    }

    BufferHandle CreateBuffer(BufferType type, std::span<const std::byte> static_buffer_data) noexcept
    {
        BufferHandle new_buffer{};
        GL::GenBuffers(1, &new_buffer);
        GL::BindBuffer(static_cast<GLenum>(type), new_buffer);
        GL::BufferData(static_cast<GLenum>(type), static_cast<GLsizeiptr>(static_buffer_data.size() * sizeof(static_buffer_data[0])), static_buffer_data.data(), GL_STATIC_DRAW);
        GL::BindBuffer(static_cast<GLenum>(type), 0);
        // https://docs.gl/es3/glGenBuffers
        // https://docs.gl/es3/glBindBuffer
        // https://docs.gl/es3/glBufferData
        return new_buffer;
    }
    
    void UpdateBufferData(BufferType type, BufferHandle buffer, std::span<const std::byte> data_to_copy, GLsizei starting_offset) noexcept
    {
        // https://docs.gl/es3/glBindBuffer
        // https://docs.gl/es3/glBufferSubData
        GL::BindBuffer(static_cast<GLenum>(type), buffer);
        GL::BufferSubData(static_cast<GLenum>(type), starting_offset, static_cast<GLsizeiptr>(data_to_copy.size() * sizeof(data_to_copy[0])), data_to_copy.data());
        GL::BindBuffer(static_cast<GLenum>(type), 0);
    }

}

================================================
FILE: source/OpenGL/Buffer.hpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once

#include "GLConstants.hpp"
#include "Handle.hpp"
#include <span>

namespace OpenGL
{
    /**
     * \brief Descriptive alias for OpenGL buffer object handles
     *
     * BufferHandle provides a more specific and readable name for the generic
     * OpenGL handle type. While it doesn't add type safety (it's still the same
     * underlying type as other OpenGL handles), it makes the code's intent clearer
     * by indicating that this handle specifically refers to buffer objects.
     *
     * This alias helps with:
     * - Code readability: immediately clear this refers to a buffer
     * - Documentation: function signatures clearly indicate buffer parameters
     * - Consistency: uniform naming convention across the OpenGL wrapper
     *
     * Note: This is purely a naming convenience - the compiler treats BufferHandle
     * identically to the generic Handle type, so mixing them won't cause errors.
     * The real type safety comes from the BufferType enum and API design.
     */
    using BufferHandle = Handle;

    /**
     * \brief Enumeration of OpenGL buffer types for different rendering purposes
     *
     * BufferType categorizes buffers based on their intended use in the graphics
     * pipeline. Each type corresponds to a specific OpenGL buffer target that
     * determines how the GPU will access and use the buffer data.
     *
     * The enum values map directly to OpenGL constants but provide a more
     * type-safe and readable interface. This helps prevent binding buffers
     * to incorrect targets and makes the code's intent clearer.
     *
     * Buffer Types:
     * - Vertices: Stores vertex attribute data (positions, colors, texture coordinates)
     * - Indices: Stores element indices for indexed drawing operations
     * - UniformBlocks: Stores uniform data shared across multiple shader invocations
     */
    enum class BufferType : GLenum
    {
        Vertices      = GL_ARRAY_BUFFER,         ///< Vertex attribute data buffer
        Indices       = GL_ELEMENT_ARRAY_BUFFER, ///< Element index buffer for indexed drawing
        UniformBlocks = GL_UNIFORM_BUFFER        ///< Uniform block data buffer
    };
    /**
     * \brief Create an empty buffer with specified size for dynamic data
     * \param type The type of buffer to create (Vertices, Indices, or UniformBlocks)
     * \param size_in_bytes Size of the buffer in bytes
     * \return Handle to the newly created buffer object
     *
     * Creates an OpenGL buffer object with allocated storage but no initial data.
     * This is optimal for buffers that will be updated frequently during runtime,
     * such as dynamic vertex data, animated geometry, or per-frame uniform data.
     *
     * The buffer is configured for dynamic usage patterns, making it suitable for:
     * - Vertex data that changes every frame (particle systems, UI elements)
     * - Temporary geometry that gets rebuilt frequently
     * - Buffers that will be updated with new data using UpdateBufferData()
     *
     * Memory allocation happens on the GPU, but no data transfer occurs during
     * creation. The buffer contents are undefined until data is uploaded.
     *
     * The implementation uses GL_DYNAMIC_DRAW usage hint, indicating that the
     * buffer contents will be modified repeatedly and used for drawing operations.
     */
    [[nodiscard]] BufferHandle CreateBuffer(BufferType type, GLsizeiptr size_in_bytes) noexcept;
    
    /**
     * \brief Create a buffer initialized with static data
     * \param type The type of buffer to create (Vertices, Indices, or UniformBlocks)
     * \param static_buffer_data Span containing the initial data to upload
     * \return Handle to the newly created buffer object
     *
     * Creates an OpenGL buffer object and immediately uploads the provided data.
     * This is optimal for buffers containing static data that won't change during
     * the application's lifetime, such as fixed mesh geometry, constant lookup
     * tables, or unchanging uniform block data.
     *
     * The buffer is configured for static usage patterns, making it suitable for:
     * - Static mesh geometry (terrain, buildings, fixed models)
     * - Constant index arrays for standard shapes (quads, cubes)
     * - Lookup tables and constant uniform data
     * - Any data that remains unchanged after initial upload
     *
     * Memory allocation and data transfer happen atomically during creation,
     * ensuring the buffer is immediately ready for use in rendering operations.
     *
     * The implementation uses GL_STATIC_DRAW usage hint, indicating that the
     * buffer contents will be set once and used repeatedly for drawing.
     */
    [[nodiscard]] BufferHandle CreateBuffer(BufferType type, std::span<const std::byte> static_buffer_data) noexcept;
    
    /**
     * \brief Update existing buffer with new data
     * \param type The type of buffer being updated
     * \param buffer Handle to the buffer object to update
     * \param data_to_copy Span containing the new data to upload
     * \param starting_offset Byte offset within the buffer where copying begins (default: 0)
     *
     * Uploads new data to an existing buffer object, either replacing all contents
     * or updating a specific region. This is essential for dynamic buffers that
     * need frequent updates, such as animated vertex data, changing uniform values,
     * or streaming geometry data.
     *
     * The function provides flexibility for partial updates:
     * - Full buffer replacement: starting_offset = 0, data spans entire buffer
     * - Partial updates: starting_offset > 0, data spans subset of buffer
     * - Streaming updates: sequential calls with different offsets
     *
     * Common usage patterns:
     * - Updating vertex positions for animated objects
     * - Streaming new geometry data for dynamic scenes
     * - Modifying uniform block data for per-object parameters
     * - Updating index buffers for dynamic mesh topology
     *
     * The buffer must have sufficient capacity to hold the new data starting
     * from the specified offset. The function performs efficient GPU memory
     * transfers using OpenGL's buffer sub-data operations.
     */
    void UpdateBufferData(BufferType type, BufferHandle buffer, std::span<const std::byte> data_to_copy, GLsizei starting_offset = 0) noexcept;

}

================================================
FILE: source/OpenGL/Environment.hpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once

namespace OpenGL
{
    inline int MajorVersion         = 0;
    inline int MinorVersion         = 0;
    inline int MaxTextureImageUnits = 2;
    inline int MaxTextureSize       = 64;

    constexpr int version(int major, int minor) noexcept
    {
        return major * 100 + minor * 10;
    }
    
    inline int current_version() noexcept
    {
        return version(MajorVersion, MinorVersion);
    }

#if defined(IS_WEBGL2)
    constexpr bool IsWebGL                     = true;
    // WEBGL2 is expressed as 3.0 ES
    constexpr int  MinimumRequiredMajorVersion = 3;
    constexpr int  MinimumRequiredMinorVersion = 0;
#else
    constexpr bool IsWebGL                     = false;
    constexpr int  MinimumRequiredMajorVersion = 3;
    constexpr int  MinimumRequiredMinorVersion = 3;
#endif
}

================================================
FILE: source/OpenGL/Framebuffer.cpp
================================================
/**

* \file
* \author Rudy Castan
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "Framebuffer.hpp"
  #include "Engine/Engine.hpp"
  #include "Engine/Logger.hpp"
  #include "GL.hpp"
  #include "Texture.hpp"

namespace
{
    void verify_framebuffer_complete(OpenGL::FramebufferHandle framebuffer);
}

namespace OpenGL
{
    FramebufferWithColor CreateFramebufferWithColor(Math::ivec2 size)
    {
        FramebufferWithColor fb{};
        //  * - A color texture attachment in RGBA format for storing rendered pixels
        fb.ColorAttachment = CreateRGBATexture(size);
        GL::GenFramebuffers(1,&(fb.Framebuffer));
        GL::BindFramebuffer(GL_FRAMEBUFFER, fb.Framebuffer);
        GL::FramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,fb.ColorAttachment, 0);
        //  * - Proper draw buffer configuration for color output
        constexpr GLenum draw_buffers[] = { GL_COLOR_ATTACHMENT0 };
        GL::DrawBuffers(1, draw_buffers);
        //  * - Complete framebuffer validation to ensure it's ready for use
        verify_framebuffer_complete(fb.Framebuffer);
        return fb;
    }

    void DestroyFramebufferWithColor(FramebufferWithColor& framebuffer_with_color) noexcept
    {
        GL::DeleteTextures(1, &framebuffer_with_color.ColorAttachment), framebuffer_with_color.ColorAttachment = 0;
        GL::DeleteFramebuffers(1, &framebuffer_with_color.Framebuffer), framebuffer_with_color.Framebuffer       = 0;
    }

}

namespace
{
    void verify_framebuffer_complete(OpenGL::FramebufferHandle framebuffer)
    {
        GL::BindFramebuffer(GL_FRAMEBUFFER,framebuffer);
        const auto status_result = GL::CheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status_result == GL_FRAMEBUFFER_COMPLETE)
        {
            GL::BindFramebuffer(GL_FRAMEBUFFER, 0);
            return; // Framebuffer is complete and ready to use
        }

        std::ostringstream message;
        message << "Framebuffer creation failed: status = 0x" << std::hex << status_result << std::dec << "\n";
    
        switch (status_result)
        {
            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                message << "\t[Attachment Error] One or more framebuffer attachments (e.g. textures or renderbuffers) are incomplete or incompatible.\n"
                        << "\t-> Double-check format consistency and ensure all attached resources are properly initialized.\n";
                break;
    
            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                message << "\t[Missing Attachment] No color, depth, or stencil attachment was provided.\n"
                        << "\t-> Make sure at least one valid image is attached using glFramebufferTexture or glFramebufferRenderbuffer.\n";
                break;
    
            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
                message << "\t[Draw Buffer Error] Draw buffers are referencing attachments that don't exist or are incomplete.\n"
                        << "\t-> Confirm that GL_COLOR_ATTACHMENTx exists for each buffer in GL::DrawBuffers().\n";
                break;
    
            case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
                message << "\t[Read Buffer Error] Read buffer (glReadBuffer) is referencing an incomplete or missing attachment.\n"
                        << "\t-> Check if glReadBuffer is targeting an attachment that's properly set up.\n";
                break;
    
            case GL_FRAMEBUFFER_UNSUPPORTED:
                message << "\t[Unsupported Configuration] This framebuffer configuration is not supported by the OpenGL implementation.\n"
                        << "\t-> Try simplifying formats, avoid non-standard combinations, and confirm hardware support.\n";
                break;
    
            default:
                message << "\t[Unknown Error] Framebuffer status not recognized. Raw code: " << status_result << "\n"
                        << "\t-> Investigate texture formats and attachment completeness. Enable OpenGL debug output for deeper insights.\n";
                break;
        }
    
        Engine::GetLogger().LogError(message.str());
        GL::BindFramebuffer(GL_FRAMEBUFFER, 0);
        throw std::runtime_error{ message.str() };
    }

}

================================================
FILE: source/OpenGL/Framebuffer.hpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once

#include "Engine/Vec2.hpp"
#include "Handle.hpp"
#include "Texture.hpp"

namespace OpenGL
{
    /**
     * \brief Descriptive alias for OpenGL framebuffer object handles
     *
     * FramebufferHandle provides a more specific and readable name for the generic
     * OpenGL handle type when referring to framebuffer objects. Like other handle
     * aliases, this improves code clarity without adding compile-time type safety.
     */
    using FramebufferHandle = Handle;

    /**
     * \brief Complete framebuffer setup with color attachment for render-to-texture operations
     *
     * FramebufferWithColor represents a fully configured OpenGL framebuffer that can
     * be used as a render target. This struct bundles together the framebuffer object
     * and its associated color texture, providing everything needed for off-screen
     * rendering or render-to-texture effects.
     *
     * Purpose and Use Cases:
     * - Render-to-texture operations (post-processing effects, shadows, reflections)
     * - Off-screen rendering for UI elements or HUD components
     * - Multi-pass rendering techniques (deferred rendering, G-buffers)
     * - Creating texture atlases or procedural textures at runtime
     * - Screen capture and screenshot functionality
     *
     * The framebuffer acts as a rendering target that redirects all drawing operations
     * to the attached texture instead of the screen. This enables sophisticated
     * graphics techniques where the rendered result becomes input for subsequent
     * rendering passes or post-processing effects.
     *
     * Resource Management:
     * Both the framebuffer and its color texture must be properly destroyed when
     * no longer needed to prevent OpenGL resource leaks. The struct design makes
     * it easy to manage these related resources as a single unit.
     */
    struct [[nodiscard]] FramebufferWithColor
    {
        /** \brief Handle to the OpenGL framebuffer object */
        FramebufferHandle Framebuffer = 0;
    
        /** \brief Handle to the color texture attached to this framebuffer */
        TextureHandle ColorAttachment = 0;
    };
    
    /**
     * \brief Create a complete framebuffer with color texture attachment
     * \param size Dimensions of the framebuffer and its color texture in pixels
     * \return Fully configured framebuffer ready for rendering operations
     *
     * Creates a complete framebuffer setup suitable for render-to-texture operations.
     * This function handles all the complex OpenGL setup required for off-screen
     * rendering, including texture creation, framebuffer configuration, and
     * attachment binding.
     *
     * The created framebuffer includes:
     * - A color texture attachment in RGBA format for storing rendered pixels
     * - Proper draw buffer configuration for color output
     * - Complete framebuffer validation to ensure it's ready for use
     *
     * Common usage patterns:
     * - Post-processing pipelines: render scene to texture, then apply effects
     * - Shadow mapping: render depth information from light's perspective
     * - Reflection/refraction: capture environment from different viewpoints
     * - UI rendering: create interface elements as textures
     *
     * The implementation creates an RGBA texture matching the specified dimensions
     * and attaches it as GL_COLOR_ATTACHMENT0. The framebuffer is validated for
     * completeness before being returned, throwing an exception if setup fails.
     *
     * Memory considerations:
     * The texture size directly affects GPU memory usage (width × height × 4 bytes
     * for RGBA). Large framebuffers can impact performance and memory consumption.
     */
    FramebufferWithColor CreateFramebufferWithColor(Math::ivec2 size);
    
    /**
     * \brief Safely destroy framebuffer and release all associated resources
     * \param framebuffer_with_color Framebuffer structure to destroy (will be reset to zero)
     *
     * Properly cleans up both the framebuffer object and its associated color texture,
     * preventing OpenGL resource leaks. This function ensures that all GPU resources
     * are returned to the system and the structure is reset to a safe state.
     *
     * Resource cleanup includes:
     * - Deleting the OpenGL framebuffer object
     * - Deleting the associated color texture
     * - Resetting both handles to zero for safety
     *
     * The function is designed to be safe to call multiple times on the same
     * structure, as it resets handles to zero after deletion. This prevents
     * double-deletion errors that could occur with manual resource management.
     *
     * Usage patterns:
     * - Call when framebuffer is no longer needed
     * - Include in cleanup/shutdown code
     * - Use in RAII wrapper destructors for automatic cleanup
     * - Call before reassigning framebuffer variables
     *
     * After calling this function, the framebuffer structure should not be used
     * for rendering operations until a new framebuffer is created.
     */
    void DestroyFramebufferWithColor(FramebufferWithColor& framebuffer_with_color) noexcept;

}

================================================
FILE: source/OpenGL/GL.cpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  // Include GLEW first to define OpenGL functions and constants
  #include <GL/glew.h>

#include "Engine/Engine.hpp"
#include "Engine/Logger.hpp"
#include "GL.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

#if defined(DEVELOPER_VERSION)

# include <source_location>

# define VOID_SOURCE_LOCATION const std::source_location caller_location

# define SOURCE_LOCATION      , VOID_SOURCE_LOCATION

# define glCheck(expression)                                                                                                                                                                        \

        expression;                                                                                                                                                                                    \
        glCheckError(caller_location.file_name(), caller_location.line(), caller_location.function_name(), #expression)

namespace
{
    inline void glCheckError(const char* file, unsigned line, const char* function_name, const char* opengl_function)
    {
        GLenum errorCode = glGetError();

        if (errorCode == GL_NO_ERROR)
            return;
    
        const std::string  fileString  = file;
        std::string        error       = "Unknown error";
        std::string        description = "No description";
        std::ostringstream serr;
    
        serr << "OpenGL call " << opengl_function << " failed in " << fileString.substr(fileString.find_last_of("\\/") + 1) << "(" << line << ")."
             << "\nwithin Function:\n   " << function_name << "\nError description:\n   ";
        int loop_limit = 0;
        while (errorCode != GL_NO_ERROR && loop_limit < 3)
        {
            ++loop_limit;
            switch (errorCode)
            {
                case GL_INVALID_ENUM:
                    {
                        error       = "GL_INVALID_ENUM";
                        description = "An unacceptable value has been specified for an enumerated argument.";
                        break;
                    }
    
                case GL_INVALID_VALUE:
                    {
                        error       = "GL_INVALID_VALUE";
                        description = "A numeric argument is out of range.";
                        break;
                    }
    
                case GL_INVALID_OPERATION:
                    {
                        error       = "GL_INVALID_OPERATION";
                        description = "The specified operation is not allowed in the current state.";
                        break;
                    }
    
                case GL_STACK_OVERFLOW:
                    {
                        error       = "GL_STACK_OVERFLOW";
                        description = "This command would cause a stack overflow.";
                        break;
                    }
    
                case GL_STACK_UNDERFLOW:
                    {
                        error       = "GL_STACK_UNDERFLOW";
                        description = "This command would cause a stack underflow.";
                        break;
                    }
    
                case GL_OUT_OF_MEMORY:
                    {
                        error       = "GL_OUT_OF_MEMORY";
                        description = "There is not enough memory left to execute the command.";
                        break;
                    }
    
                default:
                    {
                        error += " " + std::to_string(errorCode);
                        break;
                    }
            }
    
            serr << error << "\n   " << description << "\n\n";
            errorCode = glGetError();
        }
        Engine::GetLogger().LogError(serr.str());
        assert(false);
    }

}
#else

# define SOURCE_LOCATION

# define VOID_SOURCE_LOCATION void

# define glCheck(expression)  expression

#endif

namespace GL
{
    const GLubyte* GetString(GLenum name SOURCE_LOCATION)
    {
        glCheck(const auto the_string = glGetString(name));
        return the_string;
    }

    GLboolean IsBuffer(GLuint buffer SOURCE_LOCATION)
    {
        glCheck(const auto result = glIsBuffer(buffer));
        return result;
    }
    
    GLboolean IsEnabled(GLenum cap SOURCE_LOCATION)
    {
        glCheck(const auto result = glIsEnabled(cap));
        return result;
    }
    
    GLboolean IsProgram(GLuint program SOURCE_LOCATION)
    {
        glCheck(const auto result = glIsProgram(program));
        return result;
    }
    
    GLboolean IsShader(GLuint shader SOURCE_LOCATION)
    {
        glCheck(const auto result = glIsShader(shader));
        return result;
    }
    
    GLboolean IsTexture(GLuint texture SOURCE_LOCATION)
    {
        glCheck(const auto result = glIsTexture(texture));
        return result;
    }
    
    GLenum GetError(void)
    {
        // Note: We don't use glCheck here since this function IS the error checker
        return glGetError();
    }
    
    GLint GetAttribLocation(GLuint program, const GLchar* name SOURCE_LOCATION)
    {
        glCheck(const auto location = glGetAttribLocation(program, name));
        return location;
    }
    
    GLint GetUniformLocation(GLuint program, const GLchar* name SOURCE_LOCATION)
    {
        glCheck(const auto location = glGetUniformLocation(program, name));
        return location;
    }
    
    GLuint CreateProgram(VOID_SOURCE_LOCATION)
    {
        glCheck(const auto program = glCreateProgram());
        return program;
    }
    
    GLuint CreateShader(GLenum shaderType SOURCE_LOCATION)
    {
        glCheck(const auto shader = glCreateShader(shaderType));
        return shader;
    }
    
    void ActiveTexture(GLenum texture SOURCE_LOCATION)
    {
        glCheck(glActiveTexture(texture));
    }
    
    void AttachShader(GLuint program, GLuint shader SOURCE_LOCATION)
    {
        glCheck(glAttachShader(program, shader));
    }
    
    void BindBuffer(GLenum target, GLuint buffer SOURCE_LOCATION)
    {
        glCheck(glBindBuffer(target, buffer));
    }
    
    void BindBufferBase(GLenum target, GLuint index, GLuint buffer SOURCE_LOCATION)
    {
        glCheck(glBindBufferBase(target, index, buffer));
    }
    
    void BindTexture(GLenum target, GLuint texture SOURCE_LOCATION)
    {
        glCheck(glBindTexture(target, texture));
    }
    
    void BlendEquation(GLenum mode SOURCE_LOCATION)
    {
        glCheck(glBlendEquation(mode));
    }
    
    void BlendFunc(GLenum sfactor, GLenum dfactor SOURCE_LOCATION)
    {
        glCheck(glBlendFunc(sfactor, dfactor));
    }
    
    void BufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage SOURCE_LOCATION)
    {
        glCheck(glBufferData(target, size, data, usage));
    }
    
    void BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data SOURCE_LOCATION)
    {
        glCheck(glBufferSubData(target, offset, size, data));
    }
    
    void Clear(GLbitfield mask SOURCE_LOCATION)
    {
        glCheck(glClear(mask));
    }
    
    void ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha SOURCE_LOCATION)
    {
        glCheck(glClearColor(red, green, blue, alpha));
    }
    
    void CompileShader(GLuint shader SOURCE_LOCATION)
    {
        glCheck(glCompileShader(shader));
    }
    
    void CullFace(GLenum mode SOURCE_LOCATION)
    {
        glCheck(glCullFace(mode));
    }
    
    void DeleteBuffers(GLsizei n, const GLuint* buffers SOURCE_LOCATION)
    {
        glCheck(glDeleteBuffers(n, buffers));
    }
    
    void DeleteProgram(GLuint program SOURCE_LOCATION)
    {
        glCheck(glDeleteProgram(program));
    }
    
    void DeleteShader(GLuint shader SOURCE_LOCATION)
    {
        glCheck(glDeleteShader(shader));
    }
    
    void DeleteTextures(GLsizei n, const GLuint* textures SOURCE_LOCATION)
    {
        glCheck(glDeleteTextures(n, textures));
    }
    
    void DepthMask(GLboolean flag SOURCE_LOCATION)
    {
        glCheck(glDepthMask(flag));
    }
    
    void Disable(GLenum cap SOURCE_LOCATION)
    {
        glCheck(glDisable(cap));
    }
    
    void DrawArrays(GLenum mode, GLint first, GLsizei count SOURCE_LOCATION)
    {
        glCheck(glDrawArrays(mode, first, count));
    }
    
    void DrawBuffers(GLsizei n, const GLenum* bufs SOURCE_LOCATION)
    {
        glCheck(glDrawBuffers(n, bufs));
    }
    
    void DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices SOURCE_LOCATION)
    {
        glCheck(glDrawElements(mode, count, type, indices));
    }
    
    void Enable(GLenum cap SOURCE_LOCATION)
    {
        glCheck(glEnable(cap));
    }
    
    void EnableVertexAttribArray(GLuint index SOURCE_LOCATION)
    {
        glCheck(glEnableVertexAttribArray(index));
    }
    
    void FrontFace(GLenum mode SOURCE_LOCATION)
    {
        glCheck(glFrontFace(mode));
    }
    
    void GenBuffers(GLsizei n, GLuint* buffers SOURCE_LOCATION)
    {
        glCheck(glGenBuffers(n, buffers));
    }
    
    void GenTextures(GLsizei n, GLuint* textures SOURCE_LOCATION)
    {
        glCheck(glGenTextures(n, textures));
    }
    
    void GetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name SOURCE_LOCATION)
    {
        glCheck(glGetActiveAttrib(program, index, bufSize, length, size, type, name));
    }
    
    void GetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name SOURCE_LOCATION)
    {
        glCheck(glGetActiveUniform(program, index, bufSize, length, size, type, name));
    }
    
    void GetBooleanv(GLenum pname, GLboolean* data SOURCE_LOCATION)
    {
        glCheck(glGetBooleanv(pname, data));
    }
    
    void GetIntegerv(GLenum pname, GLint* data SOURCE_LOCATION)
    {
        glCheck(glGetIntegerv(pname, data));
    }
    
    void GetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog SOURCE_LOCATION)
    {
        glCheck(glGetProgramInfoLog(program, maxLength, length, infoLog));
    }
    
    void GetProgramiv(GLuint program, GLenum pname, GLint* params SOURCE_LOCATION)
    {
        glCheck(glGetProgramiv(program, pname, params));
    }
    
    void GetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog SOURCE_LOCATION)
    {
        glCheck(glGetShaderInfoLog(shader, maxLength, length, infoLog));
    }
    
    void GetShaderiv(GLuint shader, GLenum pname, GLint* params SOURCE_LOCATION)
    {
        glCheck(glGetShaderiv(shader, pname, params));
    }
    
    void GetUniformfv(GLuint program, GLint location, GLfloat* params SOURCE_LOCATION)
    {
        glCheck(glGetUniformfv(program, location, params));
    }
    
    void GetUniformiv(GLuint program, GLint location, GLint* params SOURCE_LOCATION)
    {
        glCheck(glGetUniformiv(program, location, params));
    }
    
    void GetUniformuiv(GLuint program, GLint location, GLuint* params SOURCE_LOCATION)
    {
        glCheck(glGetUniformuiv(program, location, params));
    }
    
    void Hint(GLenum target, GLenum mode SOURCE_LOCATION)
    {
        glCheck(glHint(target, mode));
    }
    
    void LinkProgram(GLuint program SOURCE_LOCATION)
    {
        glCheck(glLinkProgram(program));
    }
    
    void PolygonOffset(GLfloat factor, GLfloat units SOURCE_LOCATION)
    {
        glCheck(glPolygonOffset(factor, units));
    }
    
    void ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels SOURCE_LOCATION)
    {
        glCheck(glReadPixels(x, y, width, height, format, type, pixels));
    }
    
    void ShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length SOURCE_LOCATION)
    {
        glCheck(glShaderSource(shader, count, string, length));
    }
    
    void TexImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data SOURCE_LOCATION)
    {
        glCheck(glTexImage2D(target, level, internalFormat, width, height, border, format, type, data));
    }
    
    void TexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations SOURCE_LOCATION)
    {
        glCheck(glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations));
    }
    
    void TexParameterfv(GLenum target, GLenum pname, const GLfloat* params SOURCE_LOCATION)
    {
        glCheck(glTexParameterfv(target, pname, params));
    }
    
    void TexParameteri(GLenum target, GLenum pname, GLint param SOURCE_LOCATION)
    {
        glCheck(glTexParameteri(target, pname, param));
    }
    
    void TexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels SOURCE_LOCATION)
    {
        glCheck(glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels));
    }
    
    void Uniform1f(GLint location, GLfloat v0 SOURCE_LOCATION)
    {
        glCheck(glUniform1f(location, v0));
    }
    
    void Uniform1i(GLint location, GLint v0 SOURCE_LOCATION)
    {
        glCheck(glUniform1i(location, v0));
    }
    
    void Uniform1iv(GLint location, GLsizei count, const GLint* value SOURCE_LOCATION)
    {
        glCheck(glUniform1iv(location, count, value));
    }
    
    void Uniform1ui(GLint location, GLuint v0 SOURCE_LOCATION)
    {
        glCheck(glUniform1ui(location, v0));
    }
    
    void Uniform2f(GLint location, GLfloat v0, GLfloat v1 SOURCE_LOCATION)
    {
        glCheck(glUniform2f(location, v0, v1));
    }
    
    void Uniform2fv(GLint location, GLsizei count, const GLfloat* value SOURCE_LOCATION)
    {
        glCheck(glUniform2fv(location, count, value));
    }
    
    void Uniform2i(GLint location, GLint v0, GLint v1 SOURCE_LOCATION)
    {
        glCheck(glUniform2i(location, v0, v1));
    }
    
    void Uniform2ui(GLint location, GLuint v0, GLuint v1 SOURCE_LOCATION)
    {
        glCheck(glUniform2ui(location, v0, v1));
    }
    
    void Uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2 SOURCE_LOCATION)
    {
        glCheck(glUniform3f(location, v0, v1, v2));
    }
    
    void Uniform3fv(GLint location, GLsizei count, const GLfloat* value SOURCE_LOCATION)
    {
        glCheck(glUniform3fv(location, count, value));
    }
    
    void Uniform3i(GLint location, GLint v0, GLint v1, GLint v2 SOURCE_LOCATION)
    {
        glCheck(glUniform3i(location, v0, v1, v2));
    }
    
    void Uniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2 SOURCE_LOCATION)
    {
        glCheck(glUniform3ui(location, v0, v1, v2));
    }
    
    void Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3 SOURCE_LOCATION)
    {
        glCheck(glUniform4f(location, v0, v1, v2, v3));
    }
    
    void Uniform4fv(GLint location, GLsizei count, const GLfloat* value SOURCE_LOCATION)
    {
        glCheck(glUniform4fv(location, count, value));
    }
    
    void Uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3 SOURCE_LOCATION)
    {
        glCheck(glUniform4i(location, v0, v1, v2, v3));
    }
    
    void Uniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3 SOURCE_LOCATION)
    {
        glCheck(glUniform4ui(location, v0, v1, v2, v3));
    }
    
    void UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value SOURCE_LOCATION)
    {
        glCheck(glUniformMatrix2fv(location, count, transpose, value));
    }
    
    void UniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value SOURCE_LOCATION)
    {
        glCheck(glUniformMatrix2x3fv(location, count, transpose, value));
    }
    
    void UniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value SOURCE_LOCATION)
    {
        glCheck(glUniformMatrix2x4fv(location, count, transpose, value));
    }
    
    void UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value SOURCE_LOCATION)
    {
        glCheck(glUniformMatrix3fv(location, count, transpose, value));
    }
    
    void UniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value SOURCE_LOCATION)
    {
        glCheck(glUniformMatrix3x2fv(location, count, transpose, value));
    }
    
    void UniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value SOURCE_LOCATION)
    {
        glCheck(glUniformMatrix3x4fv(location, count, transpose, value));
    }
    
    void UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value SOURCE_LOCATION)
    {
        glCheck(glUniformMatrix4fv(location, count, transpose, value));
    }
    
    void UniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value SOURCE_LOCATION)
    {
        glCheck(glUniformMatrix4x2fv(location, count, transpose, value));
    }
    
    void UniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value SOURCE_LOCATION)
    {
        glCheck(glUniformMatrix4x3fv(location, count, transpose, value));
    }
    
    void UseProgram(GLuint program SOURCE_LOCATION)
    {
        glCheck(glUseProgram(program));
    }
    
    void ClearDepth(GLdouble depth SOURCE_LOCATION)
    {
        glCheck(glClearDepth(depth));
    }
    
    void ClearStencil(GLint s SOURCE_LOCATION)
    {
        glCheck(glClearStencil(s));
    }
    
    void ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha SOURCE_LOCATION)
    {
        glCheck(glColorMask(red, green, blue, alpha));
    }
    
    void CopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border SOURCE_LOCATION)
    {
        glCheck(glCopyTexImage2D(target, level, internalformat, x, y, width, height, border));
    }
    
    void CopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height SOURCE_LOCATION)
    {
        glCheck(glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height));
    }
    
    void DepthRange(GLdouble nearVal, GLdouble farVal SOURCE_LOCATION)
    {
        glCheck(glDepthRange(nearVal, farVal));
    }
    
    void DetachShader(GLuint program, GLuint shader SOURCE_LOCATION)
    {
        glCheck(glDetachShader(program, shader));
    }
    
    void DisableVertexAttribArray(GLuint index SOURCE_LOCATION)
    {
        glCheck(glDisableVertexAttribArray(index));
    }
    
    void DrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid* indices SOURCE_LOCATION)
    {
        glCheck(glDrawRangeElements(mode, start, end, count, type, indices));
    }
    
    void GetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders SOURCE_LOCATION)
    {
        glCheck(glGetAttachedShaders(program, maxCount, count, shaders));
    }
    
    void GetFloatv(GLenum pname, GLfloat* data SOURCE_LOCATION)
    {
        glCheck(glGetFloatv(pname, data));
    }
    
    void GetShaderSource(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source SOURCE_LOCATION)
    {
        glCheck(glGetShaderSource(shader, bufSize, length, source));
    }
    
    void GetTexParameterfv(GLenum target, GLenum pname, GLfloat* params SOURCE_LOCATION)
    {
        glCheck(glGetTexParameterfv(target, pname, params));
    }
    
    void GetTexParameteriv(GLenum target, GLenum pname, GLint* params SOURCE_LOCATION)
    {
        glCheck(glGetTexParameteriv(target, pname, params));
    }
    
    void GetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params SOURCE_LOCATION)
    {
        glCheck(glGetVertexAttribfv(index, pname, params));
    }
    
    void GetVertexAttribiv(GLuint index, GLenum pname, GLint* params SOURCE_LOCATION)
    {
        glCheck(glGetVertexAttribiv(index, pname, params));
    }
    
    void GetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid** pointer SOURCE_LOCATION)
    {
        glCheck(glGetVertexAttribPointerv(index, pname, pointer));
    }
    
    void LineWidth(GLfloat width SOURCE_LOCATION)
    {
        glCheck(glLineWidth(width));
    }
    
    void PixelStorei(GLenum pname, GLint param SOURCE_LOCATION)
    {
        glCheck(glPixelStorei(pname, param));
    }
    
    void Scissor(GLint x, GLint y, GLsizei width, GLsizei height SOURCE_LOCATION)
    {
        glCheck(glScissor(x, y, width, height));
    }
    
    void StencilMask(GLuint mask SOURCE_LOCATION)
    {
        glCheck(glStencilMask(mask));
    }
    
    void StencilMaskSeparate(GLenum face, GLuint mask SOURCE_LOCATION)
    {
        glCheck(glStencilMaskSeparate(face, mask));
    }
    
    void TexParameterf(GLenum target, GLenum pname, GLfloat param SOURCE_LOCATION)
    {
        glCheck(glTexParameterf(target, pname, param));
    }
    
    void TexParameteriv(GLenum target, GLenum pname, const GLint* params SOURCE_LOCATION)
    {
        glCheck(glTexParameteriv(target, pname, params));
    }
    
    void Uniform1fv(GLint location, GLsizei count, const GLfloat* value SOURCE_LOCATION)
    {
        glCheck(glUniform1fv(location, count, value));
    }
    
    void Uniform1uiv(GLint location, GLsizei count, const GLuint* value SOURCE_LOCATION)
    {
        glCheck(glUniform1uiv(location, count, value));
    }
    
    void Uniform2iv(GLint location, GLsizei count, const GLint* value SOURCE_LOCATION)
    {
        glCheck(glUniform2iv(location, count, value));
    }
    
    void Uniform2uiv(GLint location, GLsizei count, const GLuint* value SOURCE_LOCATION)
    {
        glCheck(glUniform2uiv(location, count, value));
    }
    
    void Uniform3iv(GLint location, GLsizei count, const GLint* value SOURCE_LOCATION)
    {
        glCheck(glUniform3iv(location, count, value));
    }
    
    void Uniform3uiv(GLint location, GLsizei count, const GLuint* value SOURCE_LOCATION)
    {
        glCheck(glUniform3uiv(location, count, value));
    }
    
    void Uniform4iv(GLint location, GLsizei count, const GLint* value SOURCE_LOCATION)
    {
        glCheck(glUniform4iv(location, count, value));
    }
    
    void Uniform4uiv(GLint location, GLsizei count, const GLuint* value SOURCE_LOCATION)
    {
        glCheck(glUniform4uiv(location, count, value));
    }
    
    void VertexAttrib1f(GLuint index, GLfloat v0 SOURCE_LOCATION)
    {
        glCheck(glVertexAttrib1f(index, v0));
    }
    
    void VertexAttrib1fv(GLuint index, const GLfloat* v SOURCE_LOCATION)
    {
        glCheck(glVertexAttrib1fv(index, v));
    }
    
    void VertexAttrib2f(GLuint index, GLfloat v0, GLfloat v1 SOURCE_LOCATION)
    {
        glCheck(glVertexAttrib2f(index, v0, v1));
    }
    
    void VertexAttrib2fv(GLuint index, const GLfloat* v SOURCE_LOCATION)
    {
        glCheck(glVertexAttrib2fv(index, v));
    }
    
    void VertexAttrib3f(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2 SOURCE_LOCATION)
    {
        glCheck(glVertexAttrib3f(index, v0, v1, v2));
    }
    
    void VertexAttrib3fv(GLuint index, const GLfloat* v SOURCE_LOCATION)
    {
        glCheck(glVertexAttrib3fv(index, v));
    }
    
    void VertexAttrib4f(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3 SOURCE_LOCATION)
    {
        glCheck(glVertexAttrib4f(index, v0, v1, v2, v3));
    }
    
    void VertexAttrib4fv(GLuint index, const GLfloat* v SOURCE_LOCATION)
    {
        glCheck(glVertexAttrib4fv(index, v));
    }
    
    void ValidateProgram(GLuint program SOURCE_LOCATION)
    {
        glCheck(glValidateProgram(program));
    }
    
    void VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer SOURCE_LOCATION)
    {
        glCheck(glVertexAttribPointer(index, size, type, normalized, stride, pointer));
    }
    
    void Viewport(GLint x, GLint y, GLsizei width, GLsizei height SOURCE_LOCATION)
    {
        glCheck(glViewport(x, y, width, height));
    }
    
    GLenum CheckFramebufferStatus(GLenum target SOURCE_LOCATION)
    {
        glCheck(const GLenum status = glCheckFramebufferStatus(target));
        return status;
    }
    
    void BindFramebuffer(GLenum target, GLuint framebuffer SOURCE_LOCATION)
    {
        glCheck(glBindFramebuffer(target, framebuffer));
    }
    
    void BindRenderbuffer(GLenum target, GLuint renderbuffer SOURCE_LOCATION)
    {
        glCheck(glBindRenderbuffer(target, renderbuffer));
    }
    
    void BindVertexArray(GLuint array SOURCE_LOCATION)
    {
        glCheck(glBindVertexArray(array));
    }
    
    void DeleteFramebuffers(GLsizei n, GLuint* framebuffers SOURCE_LOCATION)
    {
        glCheck(glDeleteFramebuffers(n, framebuffers));
    }
    
    void DeleteVertexArrays(GLsizei n, const GLuint* arrays SOURCE_LOCATION)
    {
        glCheck(glDeleteVertexArrays(n, arrays));
    }
    
    void FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level SOURCE_LOCATION)
    {
        glCheck(glFramebufferTexture2D(target, attachment, textarget, texture, level));
    }
    
    void GenFramebuffers(GLsizei n, GLuint* framebuffers SOURCE_LOCATION)
    {
        glCheck(glGenFramebuffers(n, framebuffers));
    }
    
    void GenVertexArrays(GLsizei n, GLuint* arrays SOURCE_LOCATION)
    {
        glCheck(glGenVertexArrays(n, arrays));
    }
    
    GLboolean IsFramebuffer(GLuint framebuffer SOURCE_LOCATION)
    {
        glCheck(const auto result = glIsFramebuffer(framebuffer));
        return result;
    }
    
    GLboolean IsRenderbuffer(GLuint renderbuffer SOURCE_LOCATION)
    {
        glCheck(const auto result = glIsRenderbuffer(renderbuffer));
        return result;
    }
    
    GLboolean IsQuery(GLuint id SOURCE_LOCATION)
    {
        glCheck(const auto result = glIsQuery(id));
        return result;
    }
    
    GLboolean IsSampler(GLuint id SOURCE_LOCATION)
    {
        glCheck(const auto result = glIsSampler(id));
        return result;
    }
    
    GLboolean IsSync(GLsync sync SOURCE_LOCATION)
    {
        glCheck(const auto result = glIsSync(sync));
        return result;
    }
    
    GLboolean IsTransformFeedback(GLuint id SOURCE_LOCATION)
    {
        glCheck(const auto result = glIsTransformFeedback(id));
        return result;
    }
    
    GLenum ClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout SOURCE_LOCATION)
    {
        glCheck(const auto result = glClientWaitSync(sync, flags, timeout));
        return result;
    }
    
    GLint GetFragDataLocation(GLuint program, const char* name SOURCE_LOCATION)
    {
        glCheck(const auto location = glGetFragDataLocation(program, name));
        return location;
    }
    
    GLsync FenceSync(GLenum condition, GLbitfield flags SOURCE_LOCATION)
    {
        glCheck(const auto sync = glFenceSync(condition, flags));
        return sync;
    }
    
    GLuint GetUniformBlockIndex(GLuint program, const GLchar* uniformBlockName SOURCE_LOCATION)
    {
        glCheck(const auto index = glGetUniformBlockIndex(program, uniformBlockName));
        return index;
    }
    
    void BeginQuery(GLenum target, GLuint id SOURCE_LOCATION)
    {
        glCheck(glBeginQuery(target, id));
    }
    
    void BeginTransformFeedback(GLenum primitiveMode SOURCE_LOCATION)
    {
        glCheck(glBeginTransformFeedback(primitiveMode));
    }
    
    void ClearBufferfi(GLenum buffer, GLint drawBuffer, GLfloat depth, GLint stencil SOURCE_LOCATION)
    {
        glCheck(glClearBufferfi(buffer, drawBuffer, depth, stencil));
    }
    
    void ClearBufferfv(GLenum buffer, GLint drawBuffer, const GLfloat* value SOURCE_LOCATION)
    {
        glCheck(glClearBufferfv(buffer, drawBuffer, value));
    }
    
    void ClearBufferiv(GLenum buffer, GLint drawBuffer, const GLint* value SOURCE_LOCATION)
    {
        glCheck(glClearBufferiv(buffer, drawBuffer, value));
    }
    
    void ClearBufferuiv(GLenum buffer, GLint drawBuffer, const GLuint* value SOURCE_LOCATION)
    {
        glCheck(glClearBufferuiv(buffer, drawBuffer, value));
    }
    
    void ClearDepthf(GLfloat depth SOURCE_LOCATION)
    {
        glCheck(glClearDepthf(depth));
    }
    
    void CompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data SOURCE_LOCATION)
    {
        glCheck(glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data));
    }
    
    void CompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid* data SOURCE_LOCATION)
    {
        glCheck(glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data));
    }
    
    void CompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data SOURCE_LOCATION)
    {
        glCheck(glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data));
    }
    
    void CompressedTexSubImage3D(
        GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid* data SOURCE_LOCATION)
    {
        glCheck(glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data));
    }
    
    void CopyBufferSubData(GLenum readtarget, GLenum writetarget, GLintptr readoffset, GLintptr writeoffset, GLsizeiptr size SOURCE_LOCATION)
    {
        glCheck(glCopyBufferSubData(readtarget, writetarget, readoffset, writeoffset, size));
    }
    
    void CopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height SOURCE_LOCATION)
    {
        glCheck(glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height));
    }
    
    void CreateRenderbuffers(GLsizei n, GLuint* renderbuffers SOURCE_LOCATION)
    {
        glCheck(glCreateRenderbuffers(n, renderbuffers));
    }
    
    void CreateSamplers(GLsizei n, GLuint* samplers SOURCE_LOCATION)
    {
        glCheck(glCreateSamplers(n, samplers));
    }
    
    void CreateTransformFeedbacks(GLsizei n, GLuint* ids SOURCE_LOCATION)
    {
        glCheck(glCreateTransformFeedbacks(n, ids));
    }
    
    void DeleteQueries(GLsizei n, const GLuint* ids SOURCE_LOCATION)
    {
        glCheck(glDeleteQueries(n, ids));
    }
    
    void DeleteRenderbuffers(GLsizei n, GLuint* renderbuffers SOURCE_LOCATION)
    {
        glCheck(glDeleteRenderbuffers(n, renderbuffers));
    }
    
    void DeleteSamplers(GLsizei n, const GLuint* samplers SOURCE_LOCATION)
    {
        glCheck(glDeleteSamplers(n, samplers));
    }
    
    void DeleteSync(GLsync sync SOURCE_LOCATION)
    {
        glCheck(glDeleteSync(sync));
    }
    
    void DeleteTransformFeedbacks(GLsizei n, const GLuint* ids SOURCE_LOCATION)
    {
        glCheck(glDeleteTransformFeedbacks(n, ids));
    }
    
    void DepthRangef(GLfloat n, GLfloat f SOURCE_LOCATION)
    {
        glCheck(glDepthRangef(n, f));
    }
    
    void DrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei primcount SOURCE_LOCATION)
    {
        glCheck(glDrawArraysInstanced(mode, first, count, primcount));
    }
    
    void DrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount SOURCE_LOCATION)
    {
        glCheck(glDrawElementsInstanced(mode, count, type, indices, primcount));
    }
    
    void EndQuery(GLenum target SOURCE_LOCATION)
    {
        glCheck(glEndQuery(target));
    }
    
    void EndTransformFeedback(VOID_SOURCE_LOCATION)
    {
        glCheck(glEndTransformFeedback());
    }
    
    void FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer SOURCE_LOCATION)
    {
        glCheck(glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer));
    }
    
    void FramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer SOURCE_LOCATION)
    {
        glCheck(glFramebufferTextureLayer(target, attachment, texture, level, layer));
    }
    
    void GenerateMipmap(GLenum target SOURCE_LOCATION)
    {
        glCheck(glGenerateMipmap(target));
    }
    
    void GenQueries(GLsizei n, GLuint* ids SOURCE_LOCATION)
    {
        glCheck(glGenQueries(n, ids));
    }
    
    void GenRenderbuffers(GLsizei n, GLuint* renderbuffers SOURCE_LOCATION)
    {
        glCheck(glGenRenderbuffers(n, renderbuffers));
    }
    
    void GenSamplers(GLsizei n, GLuint* samplers SOURCE_LOCATION)
    {
        glCheck(glGenSamplers(n, samplers));
    }
    
    void GenTransformFeedbacks(GLsizei n, GLuint* ids SOURCE_LOCATION)
    {
        glCheck(glGenTransformFeedbacks(n, ids));
    }
    
    void GetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params SOURCE_LOCATION)
    {
        glCheck(glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params));
    }
    
    void GetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName SOURCE_LOCATION)
    {
        glCheck(glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName));
    }
    
    void GetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params SOURCE_LOCATION)
    {
        glCheck(glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params));
    }
    
    void GetBooleani_v(GLenum target, GLuint index, GLboolean* data SOURCE_LOCATION)
    {
        glCheck(glGetBooleani_v(target, index, data));
    }
    
    void GetBufferParameteri64v(GLenum target, GLenum value, GLint64* data SOURCE_LOCATION)
    {
        glCheck(glGetBufferParameteri64v(target, value, data));
    }
    
    void GetBufferParameteriv(GLenum target, GLenum value, GLint* data SOURCE_LOCATION)
    {
        glCheck(glGetBufferParameteriv(target, value, data));
    }
    
    void GetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid* data SOURCE_LOCATION)
    {
        glCheck(glGetBufferSubData(target, offset, size, data));
    }
    
    void GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params SOURCE_LOCATION)
    {
        glCheck(glGetFramebufferAttachmentParameteriv(target, attachment, pname, params));
    }
    
    void GetInteger64i_v(GLenum target, GLuint index, GLint64* data SOURCE_LOCATION)
    {
        glCheck(glGetInteger64i_v(target, index, data));
    }
    
    void GetInteger64v(GLenum pname, GLint64* data SOURCE_LOCATION)
    {
        glCheck(glGetInteger64v(pname, data));
    }
    
    void GetIntegeri_v(GLenum target, GLuint index, GLint* data SOURCE_LOCATION)
    {
        glCheck(glGetIntegeri_v(target, index, data));
    }
    
    void GetQueryiv(GLenum target, GLenum pname, GLint* params SOURCE_LOCATION)
    {
        glCheck(glGetQueryiv(target, pname, params));
    }
    
    void GetQueryObjectuiv(GLuint id, GLenum pname, GLuint* params SOURCE_LOCATION)
    {
        glCheck(glGetQueryObjectuiv(id, pname, params));
    }
    
    void GetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params SOURCE_LOCATION)
    {
        glCheck(glGetRenderbufferParameteriv(target, pname, params));
    }
    
    void GetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat* params SOURCE_LOCATION)
    {
        glCheck(glGetSamplerParameterfv(sampler, pname, params));
    }
    
    void GetSamplerParameteriv(GLuint sampler, GLenum pname, GLint* params SOURCE_LOCATION)
    {
        glCheck(glGetSamplerParameteriv(sampler, pname, params));
    }
    
    void GetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values SOURCE_LOCATION)
    {
        glCheck(glGetSynciv(sync, pname, bufSize, length, values));
    }
    
    void GetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, char* name SOURCE_LOCATION)
    {
        glCheck(glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name));
    }
    
    void GetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar** uniformNames, GLuint* uniformIndices SOURCE_LOCATION)
    {
        glCheck(glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices));
    }
    
    void GetVertexAttribIiv(GLuint index, GLenum pname, GLint* params SOURCE_LOCATION)
    {
        glCheck(glGetVertexAttribIiv(index, pname, params));
    }
    
    void GetVertexAttribIuiv(GLuint index, GLenum pname, GLuint* params SOURCE_LOCATION)
    {
        glCheck(glGetVertexAttribIuiv(index, pname, params));
    }
    
    void PauseTransformFeedback(VOID_SOURCE_LOCATION)
    {
        glCheck(glPauseTransformFeedback());
    }
    
    void ReadBuffer(GLenum mode SOURCE_LOCATION)
    {
        glCheck(glReadBuffer(mode));
    }
    
    void RenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height SOURCE_LOCATION)
    {
        glCheck(glRenderbufferStorage(target, internalformat, width, height));
    }
    
    void RenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height SOURCE_LOCATION)
    {
        glCheck(glRenderbufferStorageMultisample(target, samples, internalformat, width, height));
    }
    
    void ResumeTransformFeedback(VOID_SOURCE_LOCATION)
    {
        glCheck(glResumeTransformFeedback());
    }
    
    void SamplerParameterf(GLuint sampler, GLenum pname, GLfloat param SOURCE_LOCATION)
    {
        glCheck(glSamplerParameterf(sampler, pname, param));
    }
    
    void SamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat* params SOURCE_LOCATION)
    {
        glCheck(glSamplerParameterfv(sampler, pname, params));
    }
    
    void SamplerParameteri(GLuint sampler, GLenum pname, GLint param SOURCE_LOCATION)
    {
        glCheck(glSamplerParameteri(sampler, pname, param));
    }
    
    void SamplerParameteriv(GLuint sampler, GLenum pname, const GLint* params SOURCE_LOCATION)
    {
        glCheck(glSamplerParameteriv(sampler, pname, params));
    }
    
    void TexImage3D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid* data SOURCE_LOCATION)
    {
        glCheck(glTexImage3D(target, level, internalFormat, width, height, depth, border, format, type, data));
    }
    
    void TexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth SOURCE_LOCATION)
    {
        glCheck(glTexStorage3D(target, levels, internalformat, width, height, depth));
    }
    
    void TexSubImage3D(
        GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid* data SOURCE_LOCATION)
    {
        glCheck(glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data));
    }
    
    void TransformFeedbackVaryings(GLuint program, GLsizei count, const char** varyings, GLenum bufferMode SOURCE_LOCATION)
    {
        glCheck(glTransformFeedbackVaryings(program, count, varyings, bufferMode));
    }
    
    void UniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding SOURCE_LOCATION)
    {
        glCheck(glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding));
    }
    
    void VertexAttribDivisor(GLuint index, GLuint divisor SOURCE_LOCATION)
    {
        glCheck(glVertexAttribDivisor(index, divisor));
    }
    
    void VertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer SOURCE_LOCATION)
    {
        glCheck(glVertexAttribIPointer(index, size, type, stride, pointer));
    }
    
    void WaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout SOURCE_LOCATION)
    {
        glCheck(glWaitSync(sync, flags, timeout));
    }
    
    void TexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height SOURCE_LOCATION)
    {
        glCheck(glTexStorage2D(target, levels, internalformat, width, height));
    }

#if !defined(IS_WEBGL2)

    // OpenGL 4.3+ Debug functions
    void DebugMessageCallback(DEBUGPROC callback, const void* userParam SOURCE_LOCATION)
    {
        glCheck(glDebugMessageCallback(callback, userParam));
    }
    
    void DebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled SOURCE_LOCATION)
    {
        glCheck(glDebugMessageControl(source, type, severity, count, ids, enabled));
    }

#endif

}

================================================
FILE: source/OpenGL/GL.hpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once
  #include "GLConstants.hpp"
  #include "GLTypes.hpp"

#if defined(DEVELOPER_VERSION)

# include <source_location>

# define VOID_SOURCE_LOCATION const std::source_location caller_location = std::source_location::current()

# define SOURCE_LOCATION      , VOID_SOURCE_LOCATION

#else

# define SOURCE_LOCATION

# define VOID_SOURCE_LOCATION void

#endif

namespace GL
{
    // Opengl Version 2.0
    const GLubyte* GetString(GLenum name SOURCE_LOCATION);
    GLboolean      IsBuffer(GLuint buffer SOURCE_LOCATION);
    GLboolean      IsEnabled(GLenum cap SOURCE_LOCATION);
    GLboolean      IsProgram(GLuint program SOURCE_LOCATION);
    GLboolean      IsShader(GLuint shader SOURCE_LOCATION);
    GLboolean      IsTexture(GLuint texture SOURCE_LOCATION);
    GLenum         GetError(void);
    GLint          GetAttribLocation(GLuint program, const GLchar* name SOURCE_LOCATION);
    GLint          GetUniformLocation(GLuint program, const GLchar* name SOURCE_LOCATION);
    GLuint         CreateProgram(VOID_SOURCE_LOCATION);
    GLuint         CreateShader(GLenum shaderType SOURCE_LOCATION);
    void           ActiveTexture(GLenum texture SOURCE_LOCATION);
    void           AttachShader(GLuint program, GLuint shader SOURCE_LOCATION);
    void           BindBuffer(GLenum target, GLuint buffer SOURCE_LOCATION);
    void           BindBufferBase(GLenum target, GLuint index, GLuint buffer SOURCE_LOCATION);
    void           BindTexture(GLenum target, GLuint texture SOURCE_LOCATION);
    void           BlendEquation(GLenum mode SOURCE_LOCATION);
    void           BlendFunc(GLenum sfactor, GLenum dfactor SOURCE_LOCATION);
    void           BufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage SOURCE_LOCATION);
    void           BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data SOURCE_LOCATION);
    void           Clear(GLbitfield mask SOURCE_LOCATION);
    void           ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha SOURCE_LOCATION);
    void           ClearDepth(GLdouble depth SOURCE_LOCATION);
    void           ClearStencil(GLint s SOURCE_LOCATION);
    void           ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha SOURCE_LOCATION);
    void           CompileShader(GLuint shader SOURCE_LOCATION);
    void           CopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border SOURCE_LOCATION);
    void           CopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height SOURCE_LOCATION);
    void           CullFace(GLenum mode SOURCE_LOCATION);
    void           DeleteBuffers(GLsizei n, const GLuint* buffers SOURCE_LOCATION);
    void           DeleteProgram(GLuint program SOURCE_LOCATION);
    void           DeleteShader(GLuint shader SOURCE_LOCATION);
    void           DeleteTextures(GLsizei n, const GLuint* textures SOURCE_LOCATION);
    void           DepthMask(GLboolean flag SOURCE_LOCATION);
    void           DepthRange(GLdouble nearVal, GLdouble farVal SOURCE_LOCATION);
    void           DetachShader(GLuint program, GLuint shader SOURCE_LOCATION);
    void           Disable(GLenum cap SOURCE_LOCATION);
    void           DisableVertexAttribArray(GLuint index SOURCE_LOCATION);
    void           DrawArrays(GLenum mode, GLint first, GLsizei count SOURCE_LOCATION);
    void           DrawBuffers(GLsizei n, const GLenum* bufs SOURCE_LOCATION);
    void           DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices SOURCE_LOCATION);
    void           DrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid* indices SOURCE_LOCATION);
    void           Enable(GLenum cap SOURCE_LOCATION);
    void           EnableVertexAttribArray(GLuint index SOURCE_LOCATION);
    void           FrontFace(GLenum mode SOURCE_LOCATION);
    void           GenBuffers(GLsizei n, GLuint* buffers SOURCE_LOCATION);
    void           GenTextures(GLsizei n, GLuint* textures SOURCE_LOCATION);
    void           GetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name SOURCE_LOCATION);
    void           GetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name SOURCE_LOCATION);
    void           GetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders SOURCE_LOCATION);
    void           GetBooleanv(GLenum pname, GLboolean* data SOURCE_LOCATION);
    void           GetFloatv(GLenum pname, GLfloat* data SOURCE_LOCATION);
    void           GetIntegerv(GLenum pname, GLint* data SOURCE_LOCATION);
    void           GetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog SOURCE_LOCATION);
    void           GetProgramiv(GLuint program, GLenum pname, GLint* params SOURCE_LOCATION);
    void           GetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog SOURCE_LOCATION);
    void           GetShaderiv(GLuint shader, GLenum pname, GLint* params SOURCE_LOCATION);
    void           GetShaderSource(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source SOURCE_LOCATION);
    void           GetTexParameterfv(GLenum target, GLenum pname, GLfloat* params SOURCE_LOCATION);
    void           GetTexParameteriv(GLenum target, GLenum pname, GLint* params SOURCE_LOCATION);
    void           GetUniformfv(GLuint program, GLint location, GLfloat* params SOURCE_LOCATION);
    void           GetUniformiv(GLuint program, GLint location, GLint* params SOURCE_LOCATION);
    void           GetUniformuiv(GLuint program, GLint location, GLuint* params SOURCE_LOCATION);
    void           GetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params SOURCE_LOCATION);
    void           GetVertexAttribiv(GLuint index, GLenum pname, GLint* params SOURCE_LOCATION);
    void           GetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid** pointer SOURCE_LOCATION);
    void           Hint(GLenum target, GLenum mode SOURCE_LOCATION);
    void           LineWidth(GLfloat width SOURCE_LOCATION);
    void           LinkProgram(GLuint program SOURCE_LOCATION);
    void           PixelStorei(GLenum pname, GLint param SOURCE_LOCATION);
    void           PolygonOffset(GLfloat factor, GLfloat units SOURCE_LOCATION);
    void           ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels SOURCE_LOCATION);
    void           Scissor(GLint x, GLint y, GLsizei width, GLsizei height SOURCE_LOCATION);
    void           ShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length SOURCE_LOCATION);
    void           StencilMask(GLuint mask SOURCE_LOCATION);
    void           StencilMaskSeparate(GLenum face, GLuint mask SOURCE_LOCATION);
    void           TexImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data SOURCE_LOCATION);
    void           TexParameterf(GLenum target, GLenum pname, GLfloat param SOURCE_LOCATION);
    void           TexParameterfv(GLenum target, GLenum pname, const GLfloat* params SOURCE_LOCATION);
    void           TexParameteri(GLenum target, GLenum pname, GLint param SOURCE_LOCATION);
    void           TexParameteriv(GLenum target, GLenum pname, const GLint* params SOURCE_LOCATION);
    void           TexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels SOURCE_LOCATION);
    void           Uniform1f(GLint location, GLfloat v0 SOURCE_LOCATION);
    void           Uniform1fv(GLint location, GLsizei count, const GLfloat* value SOURCE_LOCATION);
    void           Uniform1i(GLint location, GLint v0 SOURCE_LOCATION);
    void           Uniform1iv(GLint location, GLsizei count, const GLint* value SOURCE_LOCATION);
    void           Uniform1ui(GLint location, GLuint v0 SOURCE_LOCATION);
    void           Uniform1uiv(GLint location, GLsizei count, const GLuint* value SOURCE_LOCATION);
    void           Uniform2f(GLint location, GLfloat v0, GLfloat v1 SOURCE_LOCATION);
    void           Uniform2fv(GLint location, GLsizei count, const GLfloat* value SOURCE_LOCATION);
    void           Uniform2i(GLint location, GLint v0, GLint v1 SOURCE_LOCATION);
    void           Uniform2iv(GLint location, GLsizei count, const GLint* value SOURCE_LOCATION);
    void           Uniform2ui(GLint location, GLuint v0, GLuint v1 SOURCE_LOCATION);
    void           Uniform2uiv(GLint location, GLsizei count, const GLuint* value SOURCE_LOCATION);
    void           Uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2 SOURCE_LOCATION);
    void           Uniform3fv(GLint location, GLsizei count, const GLfloat* value SOURCE_LOCATION);
    void           Uniform3i(GLint location, GLint v0, GLint v1, GLint v2 SOURCE_LOCATION);
    void           Uniform3iv(GLint location, GLsizei count, const GLint* value SOURCE_LOCATION);
    void           Uniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2 SOURCE_LOCATION);
    void           Uniform3uiv(GLint location, GLsizei count, const GLuint* value SOURCE_LOCATION);
    void           Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3 SOURCE_LOCATION);
    void           Uniform4fv(GLint location, GLsizei count, const GLfloat* value SOURCE_LOCATION);
    void           Uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3 SOURCE_LOCATION);
    void           Uniform4iv(GLint location, GLsizei count, const GLint* value SOURCE_LOCATION);
    void           Uniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3 SOURCE_LOCATION);
    void           Uniform4uiv(GLint location, GLsizei count, const GLuint* value SOURCE_LOCATION);
    void           UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value SOURCE_LOCATION);
    void           UniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value SOURCE_LOCATION);
    void           UniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value SOURCE_LOCATION);
    void           UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value SOURCE_LOCATION);
    void           UniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value SOURCE_LOCATION);
    void           UniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value SOURCE_LOCATION);
    void           UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value SOURCE_LOCATION);
    void           UniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value SOURCE_LOCATION);
    void           UniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value SOURCE_LOCATION);
    void           UseProgram(GLuint program SOURCE_LOCATION);
    void           ValidateProgram(GLuint program SOURCE_LOCATION);
    void           VertexAttrib1f(GLuint index, GLfloat v0 SOURCE_LOCATION);
    void           VertexAttrib1fv(GLuint index, const GLfloat* v SOURCE_LOCATION);
    void           VertexAttrib2f(GLuint index, GLfloat v0, GLfloat v1 SOURCE_LOCATION);
    void           VertexAttrib2fv(GLuint index, const GLfloat* v SOURCE_LOCATION);
    void           VertexAttrib3f(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2 SOURCE_LOCATION);
    void           VertexAttrib3fv(GLuint index, const GLfloat* v SOURCE_LOCATION);
    void           VertexAttrib4f(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3 SOURCE_LOCATION);
    void           VertexAttrib4fv(GLuint index, const GLfloat* v SOURCE_LOCATION);
    void           VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer SOURCE_LOCATION);
    void           Viewport(GLint x, GLint y, GLsizei width, GLsizei height SOURCE_LOCATION);

    // Opengl Version 3.0
    GLboolean IsFramebuffer(GLuint framebuffer SOURCE_LOCATION);
    GLboolean IsQuery(GLuint id SOURCE_LOCATION);
    GLboolean IsRenderbuffer(GLuint renderbuffer SOURCE_LOCATION);
    GLboolean IsSampler(GLuint id SOURCE_LOCATION);
    GLboolean IsSync(GLsync sync SOURCE_LOCATION);
    GLboolean IsTransformFeedback(GLuint id SOURCE_LOCATION);
    GLenum    CheckFramebufferStatus(GLenum target SOURCE_LOCATION);
    GLenum    ClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout SOURCE_LOCATION);
    GLint     GetFragDataLocation(GLuint program, const char* name SOURCE_LOCATION);
    GLsync    FenceSync(GLenum condition, GLbitfield flags SOURCE_LOCATION);
    GLuint    GetUniformBlockIndex(GLuint program, const GLchar* uniformBlockName SOURCE_LOCATION);
    void      BeginQuery(GLenum target, GLuint id SOURCE_LOCATION);
    void      BeginTransformFeedback(GLenum primitiveMode SOURCE_LOCATION);
    void      BindFramebuffer(GLenum target, GLuint framebuffer SOURCE_LOCATION);
    void      BindRenderbuffer(GLenum target, GLuint renderbuffer SOURCE_LOCATION);
    void      BindVertexArray(GLuint array SOURCE_LOCATION);
    void      ClearBufferfi(GLenum buffer, GLint drawBuffer, GLfloat depth, GLint stencil SOURCE_LOCATION);
    void      ClearBufferfv(GLenum buffer, GLint drawBuffer, const GLfloat* value SOURCE_LOCATION);
    void      ClearBufferiv(GLenum buffer, GLint drawBuffer, const GLint* value SOURCE_LOCATION);
    void      ClearBufferuiv(GLenum buffer, GLint drawBuffer, const GLuint* value SOURCE_LOCATION);
    void      ClearDepthf(GLfloat depth SOURCE_LOCATION);
    void      CompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data SOURCE_LOCATION);
    void CompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid* data SOURCE_LOCATION);
    void CompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data SOURCE_LOCATION);
    void CompressedTexSubImage3D(
        GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid* data SOURCE_LOCATION);
    void CopyBufferSubData(GLenum readtarget, GLenum writetarget, GLintptr readoffset, GLintptr writeoffset, GLsizeiptr size SOURCE_LOCATION);
    void CopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height SOURCE_LOCATION);
    void CreateRenderbuffers(GLsizei n, GLuint* renderbuffers SOURCE_LOCATION);
    void CreateSamplers(GLsizei n, GLuint* samplers SOURCE_LOCATION);
    void CreateTransformFeedbacks(GLsizei n, GLuint* ids SOURCE_LOCATION);
    void DeleteFramebuffers(GLsizei n, GLuint* framebuffers SOURCE_LOCATION);
    void DeleteQueries(GLsizei n, const GLuint* ids SOURCE_LOCATION);
    void DeleteRenderbuffers(GLsizei n, GLuint* renderbuffers SOURCE_LOCATION);
    void DeleteSamplers(GLsizei n, const GLuint* samplers SOURCE_LOCATION);
    void DeleteSync(GLsync sync SOURCE_LOCATION);
    void DeleteTransformFeedbacks(GLsizei n, const GLuint* ids SOURCE_LOCATION);
    void DeleteVertexArrays(GLsizei n, const GLuint* arrays SOURCE_LOCATION);
    void DepthRangef(GLfloat n, GLfloat f SOURCE_LOCATION);
    void DrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei primcount SOURCE_LOCATION);
    void DrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount SOURCE_LOCATION);
    void EndQuery(GLenum target SOURCE_LOCATION);
    void EndTransformFeedback(VOID_SOURCE_LOCATION);
    void FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer SOURCE_LOCATION);
    void FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level SOURCE_LOCATION);
    void FramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer SOURCE_LOCATION);
    void GenerateMipmap(GLenum target SOURCE_LOCATION);
    void GenFramebuffers(GLsizei n, GLuint* framebuffers SOURCE_LOCATION);
    void GenQueries(GLsizei n, GLuint* ids SOURCE_LOCATION);
    void GenRenderbuffers(GLsizei n, GLuint* renderbuffers SOURCE_LOCATION);
    void GenSamplers(GLsizei n, GLuint* samplers SOURCE_LOCATION);
    void GenTransformFeedbacks(GLsizei n, GLuint* ids SOURCE_LOCATION);
    void GenVertexArrays(GLsizei n, GLuint* arrays SOURCE_LOCATION);
    void GetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params SOURCE_LOCATION);
    void GetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName SOURCE_LOCATION);
    void GetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params SOURCE_LOCATION);
    void GetBooleani_v(GLenum target, GLuint index, GLboolean* data SOURCE_LOCATION);
    void GetBufferParameteri64v(GLenum target, GLenum value, GLint64* data SOURCE_LOCATION);
    void GetBufferParameteriv(GLenum target, GLenum value, GLint* data SOURCE_LOCATION);
    void GetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid* data SOURCE_LOCATION);
    void GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params SOURCE_LOCATION);
    void GetInteger64i_v(GLenum target, GLuint index, GLint64* data SOURCE_LOCATION);
    void GetInteger64v(GLenum pname, GLint64* data SOURCE_LOCATION);
    void GetIntegeri_v(GLenum target, GLuint index, GLint* data SOURCE_LOCATION);
    void GetQueryiv(GLenum target, GLenum pname, GLint* params SOURCE_LOCATION);
    void GetQueryObjectuiv(GLuint id, GLenum pname, GLuint* params SOURCE_LOCATION);
    void GetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params SOURCE_LOCATION);
    void GetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat* params SOURCE_LOCATION);
    void GetSamplerParameteriv(GLuint sampler, GLenum pname, GLint* params SOURCE_LOCATION);
    void GetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values SOURCE_LOCATION);
    void GetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, char* name SOURCE_LOCATION);
    void GetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar** uniformNames, GLuint* uniformIndices SOURCE_LOCATION);
    void GetVertexAttribIiv(GLuint index, GLenum pname, GLint* params SOURCE_LOCATION);
    void GetVertexAttribIuiv(GLuint index, GLenum pname, GLuint* params SOURCE_LOCATION);
    void PauseTransformFeedback(VOID_SOURCE_LOCATION);
    void ReadBuffer(GLenum mode SOURCE_LOCATION);
    void RenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height SOURCE_LOCATION);
    void RenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height SOURCE_LOCATION);
    void ResumeTransformFeedback(VOID_SOURCE_LOCATION);
    void SamplerParameterf(GLuint sampler, GLenum pname, GLfloat param SOURCE_LOCATION);
    void SamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat* params SOURCE_LOCATION);
    void SamplerParameteri(GLuint sampler, GLenum pname, GLint param SOURCE_LOCATION);
    void SamplerParameteriv(GLuint sampler, GLenum pname, const GLint* params SOURCE_LOCATION);
    void TexImage3D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid* data SOURCE_LOCATION);
    void TexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth SOURCE_LOCATION);
    void TexSubImage3D(
        GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid* data SOURCE_LOCATION);
    void TransformFeedbackVaryings(GLuint program, GLsizei count, const char** varyings, GLenum bufferMode SOURCE_LOCATION);
    void UniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding SOURCE_LOCATION);
    void VertexAttribDivisor(GLuint index, GLuint divisor SOURCE_LOCATION);
    void VertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer SOURCE_LOCATION);
    void WaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout SOURCE_LOCATION);
    
    // Opengl Version 3.2
    void TexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations SOURCE_LOCATION);
    
    // Opengl ES 3.0 or Opengl Version 4.2
    void TexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height SOURCE_LOCATION);
    
    
    // Opengl 4.3
    void DebugMessageCallback(DEBUGPROC callback, const void* userParam SOURCE_LOCATION);
    void DebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled SOURCE_LOCATION);

}

#undef SOURCE_LOCATION
#undef VOID_SOURCE_LOCATION

================================================
FILE: source/OpenGL/GLTypes.hpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once
  #include <cstddef> // for ptrdiff_t
  #include <cstdint> // for fixed-width integer types

// OpenGL Type Definitions using precise fixed-width types
typedef uint32_t         GLenum;     // OpenGL enumeration values
typedef uint32_t         GLbitfield; // OpenGL bitfield values
typedef uint32_t         GLuint;     // Unsigned 32-bit integer
typedef int32_t          GLint;      // Signed 32-bit integer
typedef int32_t          GLsizei;    // Non-negative size values
typedef uint8_t          GLboolean;  // Boolean values (0 or 1)
typedef int8_t           GLbyte;     // Signed 8-bit integer
typedef int16_t          GLshort;    // Signed 16-bit integer
typedef uint8_t          GLubyte;    // Unsigned 8-bit integer
typedef uint16_t         GLushort;   // Unsigned 16-bit integer
typedef unsigned long    GLulong;    // Unsigned 64-bit integer
typedef float            GLfloat;    // 32-bit floating point
typedef float            GLclampf;   // Clamped 32-bit floating point
typedef double           GLdouble;   // 64-bit floating point
typedef double           GLclampd;   // Clamped 64-bit floating point
typedef void             GLvoid;     // Void type
typedef char             GLchar;     // Character type
typedef ptrdiff_t        GLintptr;   // Pointer-sized signed integer
typedef ptrdiff_t        GLsizeiptr; // Pointer-sized size value
typedef int64_t          GLint64;    // Signed 64-bit integer
typedef uint64_t         GLuint64;   // Unsigned 64-bit integer
typedef struct __GLsync* GLsync;     // Sync object pointer

#if not defined(APIENTRY)

# if defined(__MINGW32__) || defined(__CYGWIN__) || (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__)

# define APIENTRY __stdcall

# else

# define APIENTRY

# endif

#endif

typedef void(APIENTRY* DEBUGPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

================================================
FILE: source/OpenGL/Handle.hpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */

#pragma once
#include "GLTypes.hpp"

namespace OpenGL
{
    // OpenGL uses GLuint for handles
    using Handle = GLuint;
}

================================================
FILE: source/OpenGL/Shader.cpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "Shader.hpp"

#include "Engine/Engine.hpp"
#include "Engine/Logger.hpp"
#include "Engine/Path.hpp"
#include "GL.hpp"
#include <algorithm>

namespace
{
    void                                                 print_glsl_text(std::string_view source);
    [[nodiscard]] OpenGL::Handle                         compile_shader_source(GLenum type, std::string_view glsl_text);
    [[nodiscard]] OpenGL::Handle                         compile_shader_file(GLenum type, const std::filesystem::path& file_path);
    [[nodiscard]] OpenGL::ShaderHandle                   link_shader_program(OpenGL::Handle vertex_handle, OpenGL::Handle fragment_handle);
    [[nodiscard]] std::unordered_map<std::string, GLint> get_uniform_locations(OpenGL::ShaderHandle shader);
}

namespace OpenGL
{
    CompiledShader CreateShader(std::filesystem::path vertex_filepath, std::filesystem::path fragment_filepath)
    {
        const auto     vertex_handle   = compile_shader_file(GL_VERTEX_SHADER, vertex_filepath);
        const auto     fragment_handle = compile_shader_file(GL_FRAGMENT_SHADER, fragment_filepath);
        CompiledShader cs{};
        cs.Shader           = link_shader_program(vertex_handle, fragment_handle);
        cs.UniformLocations = get_uniform_locations(cs.Shader);
        return cs;
    }

    CompiledShader CreateShader(std::string_view vertex_source, std::string_view fragment_source)
    {
        const auto     vertex_handle   = compile_shader_source(GL_VERTEX_SHADER, vertex_source);
        const auto     fragment_handle = compile_shader_source(GL_FRAGMENT_SHADER, fragment_source);
        CompiledShader cs{};
        cs.Shader           = link_shader_program(vertex_handle, fragment_handle);
        cs.UniformLocations = get_uniform_locations(cs.Shader);
        return cs;
    }
    
    void DestroyShader(CompiledShader& shader) noexcept
    {
        GL::DeleteProgram(shader.Shader);
        shader.Shader = 0;
    
        shader.UniformLocations.clear();
    }
    
    void BindUniformBufferToShader(ShaderHandle shader_handle, GLuint binding_number, Handle uniform_bufer, std::string_view uniform_block_name)
    {
        const auto block_index = GL::GetUniformBlockIndex(shader_handle, uniform_block_name.data());
        if (block_index != GL_INVALID_INDEX)
        {
            GL::UniformBlockBinding(shader_handle, block_index, binding_number);
            GL::BindBufferBase(GL_UNIFORM_BUFFER, binding_number, uniform_bufer);
        }
        else
        {
            Engine::GetLogger().LogError("Uniform block '" + std::string(uniform_block_name) + "' not found in shader.");
        }
    }

}

namespace
{
    void print_glsl_text(std::string_view source)
    {
        using CountInt                          = decltype(std::count(source.begin(), source.end(), '\n'));
        CountInt           num_lines            = std::count(source.begin(), source.end(), '\n');
        const int          max_linenumber_width = static_cast<int>(std::to_string(num_lines).size());
        CountInt           line_number          = 1;
        std::string        line;
        std::ostringstream sout;
        std::istringstream source_stream(source.data());
        while (std::getline(source_stream, line))
        {
            sout << std::setw(max_linenumber_width) << std::right << line_number << "| " << line << '\n';
            ++line_number;
        }
        Engine::GetLogger().LogVerbose(sout.str());
    }

    OpenGL::Handle compile_shader_source(GLenum type, std::string_view glsl_text)
    {
        OpenGL::Handle shader = GL::CreateShader(type);
        GLchar const*  source[]{ glsl_text.data() };
        GL::ShaderSource(shader, 1, source, nullptr);
        GL::CompileShader(shader);
        GLint is_compiled = 0;
        GL::GetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
        if (is_compiled == GL_FALSE)
        {
            GLint log_length = 0;
            GL::GetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
            std::string error_log;
            error_log.resize(static_cast<std::string::size_type>(log_length) + 1);
            GL::GetShaderInfoLog(shader, log_length, nullptr, error_log.data());
            GL::DeleteShader(shader);
            shader = 0;
            Engine::GetLogger().LogError(error_log);
            print_glsl_text(glsl_text);
            throw std::runtime_error(error_log);
        }
        return shader;
    }
    
    OpenGL::Handle compile_shader_file(GLenum type, const std::filesystem::path& file_path)
    {
        const auto    shader_file_path = assets::locate_asset(file_path);
        std::ifstream ifs(shader_file_path, std::ios::in);
        if (!ifs)
        {
            Engine::GetLogger().LogError("Cannot open " + file_path.string());
            return 0;
        }
        std::string glsl_text;
        glsl_text.reserve(gsl::narrow<std::size_t>(std::filesystem::file_size(shader_file_path)));
        std::copy((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>(), std::back_insert_iterator(glsl_text));
        return compile_shader_source(type, std::string_view(glsl_text));
    }
    
    OpenGL::ShaderHandle link_shader_program(OpenGL::Handle vertex_handle, OpenGL::Handle fragment_handle)
    {
        OpenGL::ShaderHandle program_handle = GL::CreateProgram();
        if (program_handle == 0)
        {
            throw std::runtime_error("Unable to create program\n");
        }
    
        GL::AttachShader(program_handle, vertex_handle);
        GL::AttachShader(program_handle, fragment_handle);
    
        GL::LinkProgram(program_handle);
    
        GL::DeleteShader(vertex_handle);
        GL::DeleteShader(fragment_handle);
    
        GLint is_linked = 0;
        GL::GetProgramiv(program_handle, GL_LINK_STATUS, &is_linked);
        if (is_linked == GL_FALSE)
        {
            GLint log_length = 0;
            GL::GetProgramiv(program_handle, GL_INFO_LOG_LENGTH, &log_length);
            std::string error;
            error.resize(static_cast<unsigned>(log_length) + 1);
            GL::GetProgramInfoLog(program_handle, log_length, nullptr, error.data());
            Engine::GetLogger().LogError(error);
            throw std::runtime_error(error);
        }
        return program_handle;
    }
    
    std::unordered_map<std::string, GLint> get_uniform_locations(OpenGL::ShaderHandle shader)
    {
        std::unordered_map<std::string, GLint> uniform_locations;
        GLint                                  num_uniforms = 0;
        GL::GetProgramiv(shader, GL_ACTIVE_UNIFORMS, &num_uniforms);
        if (num_uniforms <= 0)
        {
            return uniform_locations;
        }
        GLint max_name_length = 0;
        GL::GetProgramiv(shader, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_name_length);
        uniform_locations.reserve(static_cast<std::size_t>(num_uniforms));
        std::string uniform_name;
        uniform_name.resize(static_cast<std::size_t>(max_name_length));
    
        for (GLint i = 0; i < num_uniforms; ++i)
        {
            GLsizei length = 0;
            GLint   size   = 0;
            GLenum  type   = 0;
            GL::GetActiveUniform(shader, static_cast<GLuint>(i), max_name_length, &length, &size, &type, uniform_name.data());
            uniform_name.resize(static_cast<std::size_t>(length));
            GLint location = GL::GetUniformLocation(shader, uniform_name.c_str());
            if (location != -1)
            {
                uniform_locations[uniform_name] = location;
            }
            uniform_name.resize(static_cast<std::size_t>(max_name_length));
        }
        return uniform_locations;
    }

}

================================================
FILE: source/OpenGL/Shader.hpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once

#include "Handle.hpp"
#include <filesystem>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

namespace OpenGL
{
    /**
     * \brief Descriptive alias for OpenGL shader program handles
     *
     * ShaderHandle provides a more specific and readable name for the generic
     * OpenGL handle type when referring to compiled shader programs. This improves
     * code clarity without adding compile-time type safety.
     */
    using ShaderHandle = Handle;

    /**
     * \brief Complete shader program with uniform location cache for efficient rendering
     *
     * CompiledShader represents a fully compiled and linked OpenGL shader program
     * that's ready for use in rendering operations. This struct bundles the shader
     * program handle with a pre-computed cache of uniform locations, eliminating
     * the need for expensive uniform location lookups during rendering.
     *
     * Purpose and Benefits:
     * - Encapsulates the complete shader compilation and linking process
     * - Provides efficient uniform access through cached locations
     * - Simplifies shader resource management
     * - Reduces runtime overhead by avoiding repeated OpenGL queries
     *
     * The uniform location cache is particularly important for performance, as
     * calling GL::GetUniformLocation() during rendering can be expensive. By
     * pre-computing and storing these locations, uniform updates become much
     * faster during the render loop.
     *
     * Typical shader workflow:
     * 1. Create shader from vertex and fragment sources
     * 2. Use cached uniform locations for fast parameter updates
     * 3. Bind shader program for rendering operations
     * 4. Destroy shader when no longer needed
     *
     * Resource management:
     * Both the shader program and uniform location cache should be properly
     * cleaned up when the shader is no longer needed to prevent resource leaks.
     */
    struct [[nodiscard]] CompiledShader
    {
        /** \brief Handle to the compiled and linked OpenGL shader program */
        ShaderHandle Shader;
    
        /** \brief Cache of uniform names mapped to their OpenGL locations for fast access */
        std::unordered_map<std::string, GLint> UniformLocations;
    };
    
    /**
     * \brief Create shader program from vertex and fragment shader files
     * \param vertex_filepath Path to the vertex shader source file (.vert)
     * \param fragment_filepath Path to the fragment shader source file (.frag)
     * \return Fully compiled shader program with cached uniform locations
     *
     * Loads, compiles, and links a complete shader program from separate vertex
     * and fragment shader files. This is the standard approach for shader
     * development, allowing separate editing and version control of vertex
     * and fragment shader code.
     *
     * The compilation process includes:
     * - Loading shader source code from the specified files
     * - Compiling vertex and fragment shaders separately
     * - Linking both shaders into a complete program
     * - Extracting and caching all uniform locations for fast access
     * - Cleaning up intermediate shader objects
     *
     * Error handling and debugging:
     * If compilation or linking fails, detailed error messages are logged with
     * line numbers to help identify the problematic shader code. The function
     * throws exceptions for compilation errors, making shader loading failures
     * immediately apparent.
     *
     * File organization patterns:
     * - Vertex shaders typically have .vert extension
     * - Fragment shaders typically have .frag extension
     * - Shaders are located through the asset system for proper path resolution
     *
     * This approach is ideal for production code where shaders are stored as
     * separate files and can be modified without recompiling the application.
     */
    CompiledShader CreateShader(std::filesystem::path vertex_filepath, std::filesystem::path fragment_filepath);
    
    /**
     * \brief Create shader program from vertex and fragment shader source strings
     * \param vertex_source Complete GLSL source code for the vertex shader
     * \param fragment_source Complete GLSL source code for the fragment shader
     * \return Fully compiled shader program with cached uniform locations
     *
     * Compiles and links a complete shader program directly from source code
     * strings. This approach is useful for programmatically generated shaders,
     * embedded shader code, or when shader sources are loaded through custom
     * mechanisms rather than direct file access.
     *
     * The compilation process mirrors the file-based version:
     * - Compiling vertex and fragment shaders from provided strings
     * - Linking both shaders into a complete program
     * - Extracting and caching all uniform locations
     * - Proper cleanup of intermediate resources
     *
     * Use cases:
     * - Procedurally generated shaders with variable content
     * - Embedded shaders compiled into the executable
     * - Shader templates with runtime string substitution
     * - Loading shaders from compressed archives or custom formats
     * - Shader preprocessing and macro expansion
     *
     * Error handling:
     * Like the file-based version, compilation errors result in detailed logging
     * with line numbers and exception throwing for immediate failure detection.
     *
     * This approach provides maximum flexibility for dynamic shader generation
     * while maintaining the same performance characteristics as file-based shaders.
     */
    CompiledShader CreateShader(std::string_view vertex_source, std::string_view fragment_source);
    
    /**
     * \brief Safely destroy shader program and release all associated resources
     * \param shader Compiled shader structure to destroy (will be reset to safe state)
     *
     * Properly cleans up the OpenGL shader program and clears the uniform location
     * cache, preventing resource leaks and ensuring the structure is in a safe
     * state for reuse or destruction.
     *
     * Resource cleanup includes:
     * - Deleting the OpenGL shader program object
     * - Clearing the uniform location cache
     * - Resetting the shader handle to zero for safety
     *
     * The function is designed to be safe for multiple calls on the same shader
     * structure, as it resets handles after deletion. This prevents double-deletion
     * errors and makes the function suitable for use in destructors or cleanup code.
     *
     * Usage patterns:
     * - Call when shader is no longer needed
     * - Include in application shutdown sequences
     * - Use in RAII wrapper destructors for automatic cleanup
     * - Call before reassigning shader variables
     *
     * After calling this function, the shader structure should not be used for
     * rendering operations until a new shader program is created and assigned.
     */
    void DestroyShader(CompiledShader& shader) noexcept;
    
    /**
     * \brief Bind uniform buffer to shader's uniform block for shared data access
     * \param shader_handle Handle to the shader program
     * \param binding_number Binding point index for the uniform buffer
     * \param uniform_bufer Handle to the uniform buffer object
     * \param uniform_block_name Name of the uniform block in the shader
     *
     * Establishes a connection between a uniform buffer object and a named uniform
     * block in the shader program. This enables efficient sharing of uniform data
     * across multiple shader programs and reduces the overhead of individual
     * uniform updates.
     *
     * Uniform buffer benefits:
     * - Share common data (matrices, lighting parameters) across multiple shaders
     * - Reduce driver overhead compared to individual uniform calls
     * - Enable more efficient uniform updates for large data sets
     * - Provide better organization of related uniform variables
     *
     * The binding process:
     * - Locates the named uniform block within the shader program
     * - Assigns the block to the specified binding point
     * - Binds the uniform buffer to the same binding point
     * - Logs errors if the uniform block is not found
     *
     * Common uniform block uses:
     * - Camera matrices (view, projection, view-projection)
     * - Lighting parameters (light positions, colors, attenuation)
     * - Material properties shared across multiple objects
     * - Time-based values for animations and effects
     *
     * The binding number should be consistent across all shaders that need to
     * access the same uniform buffer data, enabling true data sharing.
     */
    void BindUniformBufferToShader(ShaderHandle shader_handle, GLuint binding_number, Handle uniform_bufer, std::string_view uniform_block_name);

}

================================================
FILE: source/OpenGL/Texture.cpp
================================================
/**

* \file
* \author Rudy Castan
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "Texture.hpp"
  #include "CS200/Image.hpp"
  #include "Environment.hpp"
  #include "GL.hpp"

namespace OpenGL
{
    TextureHandle CreateTextureFromImage(const CS200::Image& image, Filtering filtering, Wrapping wrapping) noexcept
    {
        Math::ivec2 image_size = image.GetSize();
        return CreateTextureFromMemory(image_size, { image.data(), static_cast<size_t>(image_size.x * image_size.y) }, filtering, wrapping);
    }

    TextureHandle CreateTextureFromMemory(Math::ivec2 size, std::span<const CS200::RGBA> colors, Filtering filtering, Wrapping wrapping) noexcept
    {
        TextureHandle texture{};
        GL::GenTextures(1, &texture);
        GL::BindTexture(GL_TEXTURE_2D, texture);
        GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(filtering));
        GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(filtering));
    
        GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(wrapping));
        GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(wrapping));
    
        constexpr int base_mipmap_level = 0; // just bare level, we don't care
        constexpr int zero_border       = 0;
        GL::TexImage2D(GL_TEXTURE_2D, base_mipmap_level, GL_RGBA8, size.x, size.y, zero_border, GL_RGBA, GL_UNSIGNED_BYTE, colors.data());
        GL::BindTexture(GL_TEXTURE_2D, 0);
        return texture;
    }
    
    TextureHandle CreateRGBATexture(Math::ivec2 size, Filtering filtering, Wrapping wrapping) noexcept
    {
        TextureHandle texture{};
        GL::GenTextures(1, &texture);
        GL::BindTexture(GL_TEXTURE_2D, texture);
        GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(filtering));
        GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(filtering));
    
        GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(wrapping));
        GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(wrapping));
    
        constexpr int base_mipmap_level = 0; // just bare level, we don't care
        constexpr int zero_border       = 0;
         if (OpenGL::IsWebGL || OpenGL::current_version() >= OpenGL::version(4, 2))
         {
             GL::TexStorage2D(GL_TEXTURE_2D, base_mipmap_level + 1, GL_RGBA8, size.x, size.y);
         }
         else
         {
            GL::TexImage2D(GL_TEXTURE_2D, base_mipmap_level, GL_RGBA8, size.x, size.y, zero_border, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);//match channel!!!!!!!!!!!!!!
         }
    
        GL::BindTexture(GL_TEXTURE_2D, 0);
        return texture;
    }
    
    void SetFiltering(TextureHandle texture_handle, Filtering filtering) noexcept
    {
        GL::BindTexture(GL_TEXTURE_2D, texture_handle);
        GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(filtering));
        GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(filtering));
        GL::BindTexture(GL_TEXTURE_2D, 0);
    }
    
    void SetWrapping(TextureHandle texture_handle, Wrapping wrapping, TextureCoordinate coord) noexcept
    {
        GL::BindTexture(GL_TEXTURE_2D, texture_handle);
        switch (coord)
        {
            case TextureCoordinate::Both:
                GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(wrapping));
                GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(wrapping));
                break;
            case TextureCoordinate::S: GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(wrapping)); break;
            case TextureCoordinate::T: GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(wrapping)); break;
        }
    
        GL::BindTexture(GL_TEXTURE_2D, 0);
    }

}

================================================
FILE: source/OpenGL/Texture.hpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once

#include "CS200/RGBA.hpp"
#include "Engine/Vec2.hpp"
#include "GLConstants.hpp"
#include "GLTypes.hpp"
#include "Handle.hpp"
#include <filesystem>
#include <span>

namespace CS200
{
    class Image;
}

namespace OpenGL
{
    /**
     * \brief Texture filtering modes for controlling pixel sampling behavior
     *
     * Filtering determines how OpenGL samples texture pixels when the texture
     * is displayed at a different size than its native resolution. The choice
     * between nearest-pixel and linear filtering dramatically affects the
     * visual appearance of textures.
     *
     * Filtering affects both magnification (when texture appears larger than
     * its pixel resolution) and minification (when texture appears smaller).
     * The choice depends on the desired visual style and performance requirements.
     *
     * Visual characteristics:
     * - NearestPixel: Sharp, pixelated appearance with hard edges
     * - Linear: Smooth, blended appearance with soft edges
     *
     * Performance considerations:
     * - NearestPixel: Faster sampling, lower memory bandwidth
     * - Linear: More expensive sampling, higher memory bandwidth
     */
    enum class Filtering : GLint
    {
        NearestPixel = GL_NEAREST, ///< Sharp pixelated sampling, ideal for pixel art and crisp graphics
        Linear       = GL_LINEAR   ///< Smooth interpolated sampling, ideal for photographs and realistic textures
    };

    /**
     * \brief Texture wrapping modes for controlling behavior outside texture boundaries
     *
     * Wrapping determines what happens when texture coordinates fall outside
     * the [0,1] range. Different wrapping modes enable various tiling and
     * clamping behaviors essential for different rendering scenarios.
     *
     * Each mode serves specific use cases:
     * - Tiling textures (Repeat, MirroredRepeat)
     * - UI elements and single textures (ClampToEdge, ClampToBorder)
     * - Special effects and seamless patterns (MirrorClampToEdge)
     *
     * The wrapping mode is applied to both S (horizontal) and T (vertical)
     * texture coordinate axes, affecting how textures extend beyond their
     * original boundaries.
     */
    enum class Wrapping : GLint
    {
        Repeat         = GL_REPEAT,          ///< Tile texture infinitely in all directions
        ClampToEdge    = GL_CLAMP_TO_EDGE,   ///< Stretch edge pixels, preventing tiling artifacts
        MirroredRepeat = GL_MIRRORED_REPEAT, ///< Tile with alternating mirror reflections
    };
    
    /**
     * \brief Descriptive alias for OpenGL texture object handles
     *
     * TextureHandle provides a more specific and readable name for the generic
     * OpenGL handle type when referring to texture objects. This improves code
     * clarity without adding compile-time type safety.
     */
    using TextureHandle = Handle;
    
    /**
     * \brief Create OpenGL texture from loaded image data
     * \param image Image object containing loaded pixel data and dimensions
     * \param filtering Texture sampling method (default: nearest pixel for crisp graphics)
     * \param wrapping Texture coordinate wrapping behavior (default: repeat for tiling)
     * \return Handle to the created OpenGL texture object
     *
     * Creates an OpenGL texture from a pre-loaded Image object, transferring the
     * pixel data to GPU memory and configuring the texture for rendering use.
     * This is the standard approach for loading textures from image files.
     *
     * The image data is transferred in RGBA format with the specified filtering
     * and wrapping settings applied immediately. The texture is ready for use
     * in rendering operations after creation.
     *
     * Common usage patterns:
     * - Loading sprite textures from PNG/JPEG files
     * - Creating texture atlases for efficient batch rendering
     * - Loading UI element graphics and icons
     * - Importing procedurally generated images
     *
     * The function extracts size and pixel data from the Image object and
     * delegates to CreateTextureFromMemory() for the actual OpenGL setup.
     * This provides a convenient interface while maintaining implementation
     * consistency across different texture creation methods.
     */
    [[nodiscard]] TextureHandle CreateTextureFromImage(const CS200::Image& image, Filtering filtering = Filtering::NearestPixel, Wrapping wrapping = Wrapping::Repeat) noexcept;
    
    /**
     * \brief Create OpenGL texture from raw pixel data in memory
     * \param size Texture dimensions in pixels (width, height)
     * \param colors Span of RGBA pixel data in row-major order
     * \param filtering Texture sampling method (default: nearest pixel)
     * \param wrapping Texture coordinate wrapping behavior (default: repeat)
     * \return Handle to the created OpenGL texture object
     *
     * Creates an OpenGL texture directly from a span of RGBA color data,
     * providing maximum flexibility for programmatically generated textures
     * or custom pixel data sources. The pixel data is transferred to GPU
     * memory and configured for immediate rendering use.
     *
     * Pixel data requirements:
     * - Must contain exactly (width × height) RGBA values
     * - Data is interpreted in row-major order (left-to-right, top-to-bottom)
     * - Each pixel is a packed 32-bit RGBA value
     *
     * Common use cases:
     * - Procedurally generated textures (noise, patterns, gradients)
     * - Runtime texture modification and updates
     * - Converting between different color formats
     * - Creating textures from mathematical functions
     * - Importing from custom or binary file formats
     *
     * The implementation creates the OpenGL texture object, applies the
     * specified filtering and wrapping settings, and uploads the pixel
     * data using GL::TexImage2D() for immediate GPU availability.
     */
    [[nodiscard]] TextureHandle
        CreateTextureFromMemory(Math::ivec2 size, std::span<const CS200::RGBA> colors, Filtering filtering = Filtering::NearestPixel, Wrapping wrapping = Wrapping::Repeat) noexcept;
    
    /**
     * \brief Create empty RGBA texture without initial pixel data
     * \param size Texture dimensions in pixels (width, height)
     * \param filtering Texture sampling method (default: nearest pixel)
     * \param wrapping Texture coordinate wrapping behavior (default: repeat)
     * \return Handle to the created OpenGL texture object
     *
     * Creates an OpenGL texture with allocated GPU memory but no initial pixel
     * data. This is optimal for textures that will be used as render targets
     * (framebuffer attachments) or will have their data uploaded later through
     * other means.
     *
     * The texture is created with RGBA8 format, providing 8 bits per channel
     * for standard color representation. The memory is allocated but contains
     * undefined initial values until populated through rendering operations
     * or explicit data uploads.
     *
     * Primary use cases:
     * - Framebuffer color attachments for render-to-texture operations
     * - Dynamic textures that will be updated at runtime
     * - Temporary render targets for multi-pass rendering
     * - Screen capture or screenshot buffers
     * - Procedural texture generation targets
     *
     * The implementation uses different OpenGL functions depending on the
     * available OpenGL version: GL::TexStorage2D() for newer versions (more
     * efficient) or GL::TexImage2D() with null data for compatibility.
     *
     * Memory efficiency:
     * Creating empty textures avoids unnecessary data transfers and is
     * particularly efficient when the texture will be written to by
     * rendering operations rather than CPU-provided data.
     */
    [[nodiscard]] TextureHandle CreateRGBATexture(Math::ivec2 size, Filtering filtering = Filtering::NearestPixel, Wrapping wrapping = Wrapping::Repeat) noexcept;
    
    /**
     * \brief Update texture filtering mode after creation
     * \param texture_handle Handle to the texture object to modify
     * \param filtering New filtering mode to apply
     *
     * Changes the texture sampling behavior for an existing texture object.
     * This allows runtime switching between crisp pixel-perfect rendering
     * and smooth interpolated rendering based on visual requirements or
     * user preferences.
     *
     * The filtering setting affects both magnification and minification,
     * determining how the texture appears when scaled larger or smaller
     * than its native resolution.
     *
     * Common scenarios:
     * - Switching between pixel art and smooth rendering modes
     * - Adjusting texture quality based on performance requirements
     * - Creating visual effects with different sampling characteristics
     * - Implementing user-configurable graphics quality settings
     *
     * The function temporarily binds the texture, updates both MIN_FILTER
     * and MAG_FILTER parameters, then unbinds the texture. This ensures
     * the filtering change takes effect immediately for subsequent rendering.
     */
    void SetFiltering(TextureHandle texture_handle, Filtering filtering) noexcept;
    
    enum TextureCoordinate
    {
        S,
        T,
        Both
    };
    
    /**
     * \brief Update texture wrapping mode after creation
     * \param texture_handle Handle to the texture object to modify
     * \param wrapping New wrapping mode to apply
     * \param coord Texture coordinate axis to apply the wrapping mode (default: both S and T)
     *
     * Changes how the texture behaves when texture coordinates extend beyond
     * the [0,1] range. This enables runtime switching between different tiling
     * and clamping behaviors without recreating the texture.
     *
     * The wrapping mode can be applied to S (horizontal), T (vertical), or both
     * texture coordinate axes, affecting how the texture extends in all
     * directions beyond its boundaries.
     *
     * Dynamic wrapping use cases:
     * - Switching between tiled and non-tiled rendering modes
     * - Adapting texture behavior for different rendering contexts
     * - Creating visual effects with changing boundary conditions
     * - Implementing different texture addressing for UI vs. world geometry
     *
     * The function temporarily binds the texture, updates WRAP_S,
     * WRAP_T, or both parameters with the new wrapping mode, then unbinds the texture.
     * Changes take effect immediately for subsequent texture sampling operations.
     */
    void SetWrapping(TextureHandle texture_handle, Wrapping wrapping, TextureCoordinate coord = TextureCoordinate::Both) noexcept;

}

================================================
FILE: source/OpenGL/VertexArray.cpp
================================================
/**

* \file
* \author Rudy Castan
* \author Taekyung Ho
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #include "VertexArray.hpp"
  #include "GL.hpp"

namespace OpenGL
{
    /**
     * \brief Creates and configures a Vertex Array Object (VAO) with multiple vertex buffers and optional index buffer
     *
     * This function sets up a complete VAO by:
     * 1. Generating a new VAO handle
     * 2. Binding vertex buffers and configuring their attribute layouts
     * 3. Setting up vertex attribute pointers for each attribute (position, color, texture coords, etc.)
     * 4. Handling both regular floating-point and integer vertex attributes
     * 5. Configuring instanced rendering divisors if needed
     * 6. Optionally binding an index buffer for indexed drawing
     *
     * A VAO encapsulates all the vertex attribute state, so once created, you can simply bind
     * the VAO to use all the configured vertex buffers and their layouts for rendering.
     *
     * \param vertices An initializer list of VertexBuffer objects, each containing:
     *                 - buffer_handle: The OpenGL buffer handle containing vertex data
     *                 - buffer_layout: Description of how the data is organized (attributes, stride, offset)
     * \param index_buffer Optional index buffer handle for indexed rendering (0 if not used)
     *
     * \return VertexArrayHandle The OpenGL handle to the created VAO
     *
     * \note The VAO will be unbound (set to 0) before returning to avoid affecting subsequent OpenGL state
     * \note Each vertex attribute will be assigned sequential attribute indices starting from 0
     */
    VertexArrayHandle CreateVertexArrayObject([[maybe_unused]] std::initializer_list<VertexBuffer> vertices, [[maybe_unused]] BufferHandle index_buffer)
    {
        // PSEUDO CODE for CreateVertexArrayObject:
        // 1. Create a new Vertex Array Object (VAO)
        // 2. Bind the VAO to make it active
        // 3. For each vertex buffer:
        //    a. Bind the buffer as GL_ARRAY_BUFFER
        //    b. Calculate the stride (total bytes per vertex)
        //    c. For each attribute in the buffer layout:
        //       - Enable the vertex attribute array
        //       - Set up the vertex attribute pointer (regular or integer)
        //       - Set the vertex attribute divisor for instancing
        // 4. If an index buffer is provided, bind it as GL_ELEMENT_ARRAY_BUFFER
        // 5. Unbind the VAO (bind 0)
        // 6. Return the VAO handle

        // Declare a variable to hold the VAO handle
        VertexArrayHandle vao{};
    
        GL::GenVertexArrays(1, &vao);
        // Pass 1 for count and the address of vao to store the generated handle
        // Documentation: https://docs.gl/es3/glGenVertexArrays
    
        GL::BindVertexArray(vao);
        // This makes all subsequent vertex attribute calls affect this VAO
        // Documentation: https://docs.gl/es3/glBindVertexArray
    
        // Keep track of the current attribute index (starts at 0)
        [[maybe_unused]] GLuint attribute_index = 0;
    
        // Each VertexBuffer contains a buffer_handle and buffer_layout
        // Use structured binding:
        for (const auto& [buffer_handle, buffer_layout] : vertices)
        {
            // This tells OpenGL which buffer to read vertex data from
            // Documentation: https://docs.gl/es3/glBindBuffer
            GL::BindBuffer(GL_ARRAY_BUFFER, buffer_handle);
    
            // Loop through all attributes in buffer_layout.Attributes
            // Sum up each attr_type.SizeBytes to get the total stride
            [[maybe_unused]] GLsizei stride = 0;
            for (const auto& attr_type : buffer_layout.Attributes)
            {
                stride += attr_type.SizeBytes;
            }
    
            // Cast buffer_layout.BufferStartingByteOffset to GLintptr
            [[maybe_unused]] GLintptr offset = 0;
            offset                           = static_cast<GLintptr>(buffer_layout.BufferStartingByteOffset);
    
            // Use:
            for (Attribute::Type attr_type : buffer_layout.Attributes)
            {
                if (attr_type == Attribute::None)
                {
                    continue;
                }
    
                // Documentation: https://docs.gl/es3/glEnableVertexAttribArray
                GL::EnableVertexAttribArray(attribute_index);
                const GLenum    gl_type         = attr_type.GLType;
                const GLint     component_count = attr_type.ComponentCount;
                const GLboolean normalized      = attr_type.Normalize;
                const bool      is_integer      = attr_type.IntAttribute;
                const GLuint    divisor         = attr_type.Divisor;
    
                if (is_integer == true)
                {
                    // If true:
                    //   Use GL::VertexAttribIPointer for integer attributes
                    GL::VertexAttribIPointer(attribute_index, component_count, gl_type, stride, reinterpret_cast<GLvoid*>(offset));
                    //   Parameters: (attribute_index, component_count, gl_type, stride, offset as GLvoid*)
                    //   Documentation: https://docs.gl/es3/glVertexAttribPointer (contains VertexAttribIPointer)
                }
                else
                {
                    // Else:
                    //   Use GL::VertexAttribPointer for float/normalized attributes
                    GL::VertexAttribPointer(attribute_index, component_count, gl_type, normalized, stride, reinterpret_cast<GLvoid*>(offset));
                    //   Parameters: (attribute_index, component_count, gl_type, normalized, stride, offset as GLvoid*)
                    //   Documentation: https://docs.gl/es3/glVertexAttribPointer
                }
    
    
                GL::VertexAttribDivisor(attribute_index, divisor);
                // Parameters: (attribute_index, divisor)
                // Documentation: https://docs.gl/es3/glVertexAttribDivisor
    
                ++attribute_index;
    
                offset += attr_type.SizeBytes;
            }
        }
    
        if (index_buffer != 0)
        {
            // If true:
            //   Bind the index buffer as GL_ELEMENT_ARRAY_BUFFER
            GL::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
            //   Documentation: https://docs.gl/es3/glBindBuffer
        }
    
    
        GL::BindVertexArray(0);
        // This ensures we don't accidentally modify this VAO later
        // Documentation: https://docs.gl/es3/glBindVertexArray
    
        return vao;
    }
    
    VertexArrayHandle CreateVertexArrayObject(VertexBuffer vertices, BufferHandle index_buffer)
    {
        return CreateVertexArrayObject({ vertices }, index_buffer);
    }

}

================================================
FILE: source/OpenGL/VertexArray.hpp
================================================
/**

* \file
* \author Rudy Castan
* \date 2025 Fall
* \par CS200 Computer Graphics I
* \copyright DigiPen Institute of Technology
  */
  #pragma once
  #include "GLConstants.hpp"
  #include "GLTypes.hpp"
  #include "Handle.hpp"
  #include <cstdint>
  #include <initializer_list>
  #include <utility>
  #include <vector>

namespace OpenGL
{
    /**
     * \brief Descriptive alias for OpenGL buffer object handles
     *
     * BufferHandle provides a more specific and readable name for the generic
     * OpenGL handle type when referring to buffer objects. This improves code
     * clarity without adding compile-time type safety.
     */
    using BufferHandle = Handle;

    /**
     * \brief Descriptive alias for OpenGL vertex array object handles
     *
     * VertexArrayHandle provides a more specific and readable name for the generic
     * OpenGL handle type when referring to vertex array objects (VAOs). This improves
     * code clarity without adding compile-time type safety.
     */
    using VertexArrayHandle = Handle;
    
    namespace Attribute
    {
        /**
         * \brief Compact vertex attribute descriptor for efficient OpenGL vertex specification
         *
         * Type provides a space-efficient way to describe vertex attributes by packing
         * all the necessary OpenGL vertex attribute information into a single 32-bit value.
         * This includes the data type, component count, size, normalization settings,
         * and instancing divisor values.
         *
         * The bit-packed design allows for:
         * - Efficient storage of attribute specifications
         * - Fast comparison and sorting of attribute layouts
         * - Compile-time computation of attribute configurations
         * - Support for both integer and float attribute types
         * - Instanced rendering through divisor values
         *
         * Bit Layout:
         * - Bits 15-0:  OpenGL component type (GL_FLOAT, GL_UNSIGNED_BYTE, etc.)
         * - Bits 18-16: Component count (1-4 components per attribute)
         * - Bits 23-19: Attribute size in bytes (1-16 bytes)
         * - Bit 24:     Normalization flag for integer-to-float conversion
         * - Bit 25:     Integer attribute flag (glVertexAttribIPointer vs glVertexAttribPointer)
         * - Bits 31-26: Instancing divisor (0-63) for per-instance attributes
         *
         * This design enables both standard per-vertex attributes and advanced
         * instanced rendering techniques while maintaining compatibility with
         * OpenGL's vertex attribute specification requirements.
         */
        struct Type
        {
            uint16_t GLType            : 16; // Bits 15-0   (16 bits): OpenGL component type (GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, etc.)
            uint8_t     ComponentCount : 3;  // Bits 18-16   (3 bits): Component count (1, 2, 3, 4)
            uint8_t     SizeBytes        : 5;  // Bits 23-19   (5 bits): Attribute size in bytes (max size is 16 - vec4)
            bool     Normalize        : 1;  // Bit  24      (1 bit) : Normalized flag (0 = false, 1 = true)
            bool     IntAttribute    : 1;  // Bit  25      (1 bit) : Integer attribute flag (0 = use glVertexAttribPointer, 1 = use glVertexAttribIPointer)
            uint8_t     Divisor        : 6;  // Bits 26-31   (6 bits): Divisor Value to support instancing (0-63)
    
            constexpr auto operator<=>(const Type&) const noexcept = default;
    
            /**
             * \brief Set the instancing divisor for per-instance attributes
             * \param divisor_value Divisor for instanced rendering (0 = per-vertex, >0 = per-instance)
             * \return Reference to this Type for method chaining
             *
             * Configures the attribute for instanced rendering by setting how frequently
             * the attribute advances during instanced drawing calls. A divisor of 0 means
             * the attribute advances once per vertex (standard behavior), while values
             * greater than 0 cause the attribute to advance once per N instances.
             *
             * Common divisor patterns:
             * - 0: Per-vertex data (positions, normals, texture coordinates)
             * - 1: Per-instance data (transformation matrices, colors, IDs)
             * - N: Per-N-instances data (shared data across multiple instances)
             *
             * This enables efficient instanced rendering where certain attributes
             * remain constant across multiple instances of the same geometry.
             */
            //constexpr Type& WithDivisor(uint8_t divisor_value) noexcept
            //{
            //    Divisor = divisor_value & 0x3F; // only 6 bits
            //    return *this;
            //}
    
            //make copy instead so that compatible with constexpr variables
            constexpr Type WithDivisor(uint8_t divisor_value) const noexcept
            {
                Type copy     = *this;                 
                copy.Divisor = divisor_value & 0x3F; 
                return copy;                         
            }
        };
    
        static_assert(sizeof(Type) == sizeof(uint32_t));
    }
    
    /**
     * \brief Layout specification for vertex attributes within a buffer
     *
     * BufferLayout describes how vertex attributes are organized within a single
     * buffer object, including their types, order, and optional starting offset.
     * This enables flexible vertex data organization and supports interleaved
     * vertex formats, multiple attribute streams, and complex data layouts.
     *
     * The layout system supports:
     * - Interleaved vertex data (position, normal, texture coordinates in sequence)
     * - Multiple attribute streams from the same buffer
     * - Buffer sub-regions with custom starting offsets
     * - Mixed attribute types and sizes within the same buffer
     *
     * Common vertex layout patterns:
     * - Simple: {Float3, Float2} for position + texture coordinates
     * - Complete: {Float3, Float3, Float2} for position + normal + UV
     * - Packed: {UByte4ToNormalized} for compressed color attributes
     * - Instanced: Mix of per-vertex and per-instance attributes
     *
     * The starting byte offset enables using sub-regions of larger buffers
     * or skipping headers in complex buffer formats.
     */
    struct BufferLayout
    {
        /** \brief Byte offset from buffer start where attribute data begins */
        uint32_t BufferStartingByteOffset = 0;
    
        /** \brief Ordered list of attribute types in this buffer layout */
        std::vector<Attribute::Type> Attributes{};
    
        BufferLayout() = default;
    
        /**
         * \brief Create layout with attributes starting at buffer beginning
         * \param attributes Initializer list of attribute types in order
         */
        BufferLayout(std::initializer_list<Attribute::Type> attributes) : BufferStartingByteOffset{ 0 }, Attributes{ attributes }
        {
        }
    
        /**
         * \brief Create layout with custom starting offset
         * \param starting_byte_offset Byte offset from buffer start
         * \param attributes Initializer list of attribute types in order
         */
        BufferLayout(uint32_t starting_byte_offset, std::initializer_list<Attribute::Type> attributes) : BufferStartingByteOffset{ starting_byte_offset }, Attributes{ attributes }
        {
        }
    };
    
    /**
     * \brief Complete vertex buffer specification with handle and layout information
     *
     * VertexBuffer pairs an OpenGL buffer object with its corresponding layout
     * description, providing all the information needed to configure vertex
     * attributes for rendering. This combination ensures that buffer data
     * and its interpretation are kept together as a cohesive unit.
     *
     * The structure enables:
     * - Self-describing vertex buffers with embedded layout information
     * - Easy sharing of buffer configurations across rendering operations
     * - Type-safe vertex attribute setup through layout specifications
     * - Support for multiple vertex streams with different layouts
     *
     * Usage patterns:
     * - Single buffer with interleaved vertex data
     * - Multiple buffers with different attribute types
     * - Instanced rendering with per-vertex and per-instance streams
     * - Dynamic vertex buffers with consistent layouts
     *
     * The layout information is used during Vertex Array Object creation
     * to automatically configure the appropriate vertex attribute pointers
     * and enable the correct attribute locations.
     */
    struct VertexBuffer
    {
        /** \brief Handle to the OpenGL buffer object containing vertex data */
        BufferHandle Handle{ 0 };
    
        /** \brief Layout specification describing how attributes are organized */
        BufferLayout Layout{};
    };
    
    /**
     * \brief Create Vertex Array Object (VAO) from multiple vertex buffers
     * \param vertices Initializer list of vertex buffers with their layouts
     * \param index_buffer Optional element buffer for indexed rendering (default: 0)
     * \return Handle to the created and configured Vertex Array Object
     *
     * Creates a complete Vertex Array Object that encapsulates the vertex attribute
     * configuration for multiple vertex buffers. This enables complex vertex setups
     * with multiple attribute streams, different data types, and sophisticated
     * rendering techniques like instanced rendering.
     *
     * The function performs comprehensive VAO setup:
     * - Creates and binds a new Vertex Array Object
     * - Configures vertex attributes for each buffer according to its layout
     * - Calculates appropriate strides and offsets for interleaved data
     * - Sets up instancing divisors for per-instance attributes
     * - Binds optional index buffer for indexed rendering
     * - Enables all configured vertex attribute arrays
     *
     * Multi-buffer capabilities:
     * - Separate buffers for different attribute types (positions, normals, UVs)
     * - Mixed per-vertex and per-instance attribute streams
     * - Different data formats optimized for specific attribute types
     * - Independent update frequencies for dynamic vs. static data
     *
     * Attribute configuration:
     * Each buffer's layout is processed to determine the correct OpenGL vertex
     * attribute setup, including proper use of GL::VertexAttribPointer() for
     * floating-point data and GL::VertexAttribIPointer() for integer data.
     *
     * The resulting VAO can be bound once for rendering, eliminating the need
     * to reconfigure vertex attributes on every draw call.
     */
    VertexArrayHandle CreateVertexArrayObject(std::initializer_list<VertexBuffer> vertices, BufferHandle index_buffer = 0);
    
    /**
     * \brief Create Vertex Array Object (VAO) from a single vertex buffer
     * \param vertices Single vertex buffer with its layout specification
     * \param index_buffer Optional element buffer for indexed rendering (default: 0)
     * \return Handle to the created and configured Vertex Array Object
     *
     * Creates a Vertex Array Object for the common case of a single vertex buffer
     * containing all required vertex attributes. This is a convenience wrapper
     * around the multi-buffer version, ideal for simple rendering scenarios
     * with interleaved vertex data.
     *
     * Single-buffer advantages:
     * - Simplified memory management with one buffer object
     * - Better cache coherency with interleaved vertex data
     * - Reduced OpenGL state changes during attribute setup
     * - Lower memory overhead for simple vertex formats
     *
     * Common interleaved patterns:
     * - Position + Color: {Float3, Float4} or {Float2, UByte4ToNormalized}
     * - Position + UV: {Float3, Float2} for textured geometry
     * - Complete vertex: {Float3, Float3, Float2} for position + normal + UV
     * - Sprite data: {Float2, Float2} for position + texture coordinates
     *
     * The function delegates to the multi-buffer version with a single-element
     * initializer list, ensuring consistent behavior and implementation while
     * providing a cleaner API for simple use cases.
     */
    VertexArrayHandle CreateVertexArrayObject(VertexBuffer vertices, BufferHandle index_buffer = 0);
    
    namespace Attribute
    {
        namespace details
        {
            // Constants for encoding
            constexpr bool NORMALIZE    = true;
            constexpr bool NO_NORMALIZE = false;
            constexpr bool TO_INT        = true;     // Use glVertexAttribIPointer
            constexpr bool TO_FLOAT        = false; // Use glVertexAttribPointer
    
        }
    
        /**
         * \brief Predefined vertex attribute types for common data formats
         *
         * This collection provides pre-configured attribute types for all common
         * vertex data formats, eliminating the need to manually specify OpenGL
         * types, component counts, and conversion settings. Each attribute type
         * is optimized for its specific use case and shader input requirements.
         *
         * Naming Convention:
         * - Base types: Bool, Byte, Short, Int, UByte, UShort, UInt, Float
         * - Vector types: Type2, Type3, Type4 (e.g., Float2, Int3, UByte4)
         * - Conversions: TypeToFloat, TypeToNormalized (e.g., ByteToFloat, UByteToNormalized)
         *
         * Conversion Types:
         * - ToFloat: Convert integer types to float without normalization
         * - ToNormalized: Convert integer types to normalized float ranges
         *   - Signed types: [-1, 1] range (Byte, Short, Int)
         *   - Unsigned types: [0, 1] range (UByte, UShort, UInt)
         *
         * Memory Optimization:
         * - Use smaller integer types (Byte, UByte) for packed data
         * - Use normalized conversions for color and normal data
         * - Use native Float types for precise calculations
         *
         * Common Usage Patterns:
         * - Positions: Float2, Float3
         * - Colors: UByte4ToNormalized (compact), Float4 (precise)
         * - Normals: Float3, Byte3ToNormalized (compact)
         * - Texture Coordinates: Float2
         * - Indices: UShort, UInt (in index buffers)
         *
         * Instancing Support:
         * All attribute types can be modified with .WithDivisor(N) to create
         * per-instance attributes for instanced rendering techniques.
         */
    
        constexpr Type None                   = { 0, 0, 0, 0, 0, 0 };
        constexpr Type Bool                   = { GL_UNSIGNED_BYTE, 1, 1 * sizeof(uint8_t), details::NO_NORMALIZE, details::TO_INT, 0 };            // bool -> bool
        constexpr Type Bool2               = { GL_UNSIGNED_BYTE, 2, 2 * sizeof(uint8_t), details::NO_NORMALIZE, details::TO_INT, 0 };            // bool[2] -> bvec2
        constexpr Type Bool3               = { GL_UNSIGNED_BYTE, 3, 3 * sizeof(uint8_t), details::NO_NORMALIZE, details::TO_INT, 0 };            // bool[3] -> bvec3
        constexpr Type Bool4               = { GL_UNSIGNED_BYTE, 4, 4 * sizeof(uint8_t), details::NO_NORMALIZE, details::TO_INT, 0 };            // bool[4] -> bvec4
        constexpr Type Byte                   = { GL_BYTE, 1, 1 * sizeof(int8_t), details::NO_NORMALIZE, details::TO_INT, 0 };                        // int8_t -> int
        constexpr Type Byte2               = { GL_BYTE, 2, 2 * sizeof(int8_t), details::NO_NORMALIZE, details::TO_INT, 0 };                        // int8_t[2] -> ivec2
        constexpr Type Byte2ToFloat           = { GL_BYTE, 2, 2 * sizeof(int8_t), details::NO_NORMALIZE, details::TO_FLOAT, 0 };                    // int8_t[2] -> vec2
        constexpr Type Byte2ToNormalized   = { GL_BYTE, 2, 2 * sizeof(int8_t), details::NORMALIZE, details::TO_FLOAT, 0 };                        // int8_t[2] -> vec2 [-1, 1]
        constexpr Type Byte3               = { GL_BYTE, 3, 3 * sizeof(int8_t), details::NO_NORMALIZE, details::TO_INT, 0 };                        // int8_t[3] -> ivec3
        constexpr Type Byte3ToFloat           = { GL_BYTE, 3, 3 * sizeof(int8_t), details::NO_NORMALIZE, details::TO_FLOAT, 0 };                    // int8_t[3] -> vec3
        constexpr Type Byte3ToNormalized   = { GL_BYTE, 3, 3 * sizeof(int8_t), details::NORMALIZE, details::TO_FLOAT, 0 };                        // int8_t[3] -> vec3 [-1, 1]
        constexpr Type Byte4               = { GL_BYTE, 4, 4 * sizeof(int8_t), details::NO_NORMALIZE, details::TO_INT, 0 };                        // int8_t[4] -> ivec4
        constexpr Type Byte4ToFloat           = { GL_BYTE, 4, 4 * sizeof(int8_t), details::NO_NORMALIZE, details::TO_FLOAT, 0 };                    // int8_t[4] -> vec4
        constexpr Type Byte4ToNormalized   = { GL_BYTE, 4, 4 * sizeof(int8_t), details::NORMALIZE, details::TO_FLOAT, 0 };                        // int8_t[4] -> vec4 [-1, 1]
        constexpr Type ByteToFloat           = { GL_BYTE, 1, 1 * sizeof(int8_t), details::NO_NORMALIZE, details::TO_FLOAT, 0 };                    // int8_t -> float
        constexpr Type ByteToNormalized       = { GL_BYTE, 1, 1 * sizeof(int8_t), details::NORMALIZE, details::TO_FLOAT, 0 };                        // int8_t -> float [-1, 1]
        constexpr Type Float               = { GL_FLOAT, 1, 1 * sizeof(float), details::NO_NORMALIZE, details::TO_FLOAT, 0 };                    // float -> float
        constexpr Type Float2               = { GL_FLOAT, 2, 2 * sizeof(float), details::NO_NORMALIZE, details::TO_FLOAT, 0 };                    // float[2] -> vec2
        constexpr Type Float3               = { GL_FLOAT, 3, 3 * sizeof(float), details::NO_NORMALIZE, details::TO_FLOAT, 0 };                    // float[3] -> vec3
        constexpr Type Float4               = { GL_FLOAT, 4, 4 * sizeof(float), details::NO_NORMALIZE, details::TO_FLOAT, 0 };                    // float[4] -> vec4
        constexpr Type Int                   = { GL_INT, 1, 1 * sizeof(int), details::NO_NORMALIZE, details::TO_INT, 0 };                            // int -> int
        constexpr Type Int2                   = { GL_INT, 2, 2 * sizeof(int), details::NO_NORMALIZE, details::TO_INT, 0 };                            // int[2] -> ivec2
        constexpr Type Int2ToFloat           = { GL_INT, 2, 2 * sizeof(int), details::NO_NORMALIZE, details::TO_FLOAT, 0 };                        // int[2] -> vec2
        constexpr Type Int2ToNormalized       = { GL_INT, 2, 2 * sizeof(int), details::NORMALIZE, details::TO_FLOAT, 0 };                            // int[2] -> vec2 [-1, 1]
        constexpr Type Int3                   = { GL_INT, 3, 3 * sizeof(int), details::NO_NORMALIZE, details::TO_INT, 0 };                            // int[3] -> ivec3
        constexpr Type Int3ToFloat           = { GL_INT, 3, 3 * sizeof(int), details::NO_NORMALIZE, details::TO_FLOAT, 0 };                        // int[3] -> vec3
        constexpr Type Int3ToNormalized       = { GL_INT, 3, 3 * sizeof(int), details::NORMALIZE, details::TO_FLOAT, 0 };                            // int[3] -> vec3 [-1, 1]
        constexpr Type Int4                   = { GL_INT, 4, 4 * sizeof(int), details::NO_NORMALIZE, details::TO_INT, 0 };                            // int[4] -> ivec4
        constexpr Type Int4ToFloat           = { GL_INT, 4, 4 * sizeof(int), details::NO_NORMALIZE, details::TO_FLOAT, 0 };                        // int[4] -> vec4
        constexpr Type Int4ToNormalized       = { GL_INT, 4, 4 * sizeof(int), details::NORMALIZE, details::TO_FLOAT, 0 };                            // int[4] -> vec4 [-1, 1]
        constexpr Type IntToFloat           = { GL_INT, 1, 1 * sizeof(int), details::NO_NORMALIZE, details::TO_FLOAT, 0 };                        // int -> float
        constexpr Type IntToNormalized       = { GL_INT, 1, 1 * sizeof(int), details::NORMALIZE, details::TO_FLOAT, 0 };                            // int -> float [-1, 1]
        constexpr Type Short               = { GL_SHORT, 1, 1 * sizeof(short), details::NO_NORMALIZE, details::TO_INT, 0 };                        // short -> int
        constexpr Type Short2               = { GL_SHORT, 2, 2 * sizeof(short), details::NO_NORMALIZE, details::TO_INT, 0 };                        // short[2] -> ivec2
        constexpr Type Short2ToFloat       = { GL_SHORT, 2, 2 * sizeof(short), details::NO_NORMALIZE, details::TO_FLOAT, 0 };                    // short[2] -> vec2
        constexpr Type Short2ToNormalized  = { GL_SHORT, 2, 2 * sizeof(short), details::NORMALIZE, details::TO_FLOAT, 0 };                        // short[2] -> vec2 [-1, 1]
        constexpr Type Short3               = { GL_SHORT, 3, 3 * sizeof(short), details::NO_NORMALIZE, details::TO_INT, 0 };                        // short[3] -> ivec3
        constexpr Type Short3ToFloat       = { GL_SHORT, 3, 3 * sizeof(short), details::NO_NORMALIZE, details::TO_FLOAT, 0 };                    // short[3] -> vec3
        constexpr Type Short3ToNormalized  = { GL_SHORT, 3, 3 * sizeof(short), details::NORMALIZE, details::TO_FLOAT, 0 };                        // short[3] -> vec3 [-1, 1]
        constexpr Type Short4               = { GL_SHORT, 4, 4 * sizeof(short), details::NO_NORMALIZE, details::TO_INT, 0 };                        // short[4] -> ivec4
        constexpr Type Short4ToFloat       = { GL_SHORT, 4, 4 * sizeof(short), details::NO_NORMALIZE, details::TO_FLOAT, 0 };                    // short[4] -> vec4
        constexpr Type Short4ToNormalized  = { GL_SHORT, 4, 4 * sizeof(short), details::NORMALIZE, details::TO_FLOAT, 0 };                        // short[4] -> vec4 [-1, 1]
        constexpr Type ShortToFloat           = { GL_SHORT, 1, 1 * sizeof(short), details::NO_NORMALIZE, details::TO_FLOAT, 0 };                    // short -> float
        constexpr Type ShortToNormalized   = { GL_SHORT, 1, 1 * sizeof(short), details::NORMALIZE, details::TO_FLOAT, 0 };                        // short -> float [-1, 1]
        constexpr Type UByte               = { GL_UNSIGNED_BYTE, 1, 1 * sizeof(uint8_t), details::NO_NORMALIZE, details::TO_INT, 0 };            // uint8_t -> uint
        constexpr Type UByte2               = { GL_UNSIGNED_BYTE, 2, 2 * sizeof(uint8_t), details::NO_NORMALIZE, details::TO_INT, 0 };            // uint8_t[2] -> uvec2
        constexpr Type UByte2ToFloat       = { GL_UNSIGNED_BYTE, 2, 2 * sizeof(uint8_t), details::NO_NORMALIZE, details::TO_FLOAT, 0 };            // uint8_t[2] -> vec2
        constexpr Type UByte2ToNormalized  = { GL_UNSIGNED_BYTE, 2, 2 * sizeof(uint8_t), details::NORMALIZE, details::TO_FLOAT, 0 };            // uint8_t[2] -> vec2 [0, 1]
        constexpr Type UByte3               = { GL_UNSIGNED_BYTE, 3, 3 * sizeof(uint8_t), details::NO_NORMALIZE, details::TO_INT, 0 };            // uint8_t[3] -> uvec3
        constexpr Type UByte3ToFloat       = { GL_UNSIGNED_BYTE, 3, 3 * sizeof(uint8_t), details::NO_NORMALIZE, details::TO_FLOAT, 0 };            // uint8_t[3] -> vec3
        constexpr Type UByte3ToNormalized  = { GL_UNSIGNED_BYTE, 3, 3 * sizeof(uint8_t), details::NORMALIZE, details::TO_FLOAT, 0 };            // uint8_t[3] -> vec3 [0, 1]
        constexpr Type UByte4               = { GL_UNSIGNED_BYTE, 4, 4 * sizeof(uint8_t), details::NO_NORMALIZE, details::TO_INT, 0 };            // uint8_t[4] -> uvec4
        constexpr Type UByte4ToFloat       = { GL_UNSIGNED_BYTE, 4, 4 * sizeof(uint8_t), details::NO_NORMALIZE, details::TO_FLOAT, 0 };            // uint8_t[4] -> vec4
        constexpr Type UByte4ToNormalized  = { GL_UNSIGNED_BYTE, 4, 4 * sizeof(uint8_t), details::NORMALIZE, details::TO_FLOAT, 0 };            // uint8_t[4] -> vec4 [0, 1]
        constexpr Type UByteToFloat           = { GL_UNSIGNED_BYTE, 1, 1 * sizeof(uint8_t), details::NO_NORMALIZE, details::TO_FLOAT, 0 };            // uint8_t -> float
        constexpr Type UByteToNormalized   = { GL_UNSIGNED_BYTE, 1, 1 * sizeof(uint8_t), details::NORMALIZE, details::TO_FLOAT, 0 };            // uint8_t -> float [0, 1]
        constexpr Type UInt                   = { GL_UNSIGNED_INT, 1, 1 * sizeof(unsigned int), details::NO_NORMALIZE, details::TO_INT, 0 };        // uint -> uint
        constexpr Type UInt2               = { GL_UNSIGNED_INT, 2, 2 * sizeof(unsigned int), details::NO_NORMALIZE, details::TO_INT, 0 };        // uint[2] -> uvec2
        constexpr Type UInt2ToFloat           = { GL_UNSIGNED_INT, 2, 2 * sizeof(unsigned int), details::NO_NORMALIZE, details::TO_FLOAT, 0 };        // uint[2] -> vec2
        constexpr Type UInt2ToNormalized   = { GL_UNSIGNED_INT, 2, 2 * sizeof(unsigned int), details::NORMALIZE, details::TO_FLOAT, 0 };        // uint[2] -> vec2 [0, 1]
        constexpr Type UInt3               = { GL_UNSIGNED_INT, 3, 3 * sizeof(unsigned int), details::NO_NORMALIZE, details::TO_INT, 0 };        // uint[3] -> uvec3
        constexpr Type UInt3ToFloat           = { GL_UNSIGNED_INT, 3, 3 * sizeof(unsigned int), details::NO_NORMALIZE, details::TO_FLOAT, 0 };        // uint[3] -> vec3
        constexpr Type UInt3ToNormalized   = { GL_UNSIGNED_INT, 3, 3 * sizeof(unsigned int), details::NORMALIZE, details::TO_FLOAT, 0 };        // uint[3] -> vec3 [0, 1]
        constexpr Type UInt4               = { GL_UNSIGNED_INT, 4, 4 * sizeof(unsigned int), details::NO_NORMALIZE, details::TO_INT, 0 };        // uint[4] -> uvec4
        constexpr Type UInt4ToFloat           = { GL_UNSIGNED_INT, 4, 4 * sizeof(unsigned int), details::NO_NORMALIZE, details::TO_FLOAT, 0 };        // uint[4] -> vec4
        constexpr Type UInt4ToNormalized   = { GL_UNSIGNED_INT, 4, 4 * sizeof(unsigned int), details::NORMALIZE, details::TO_FLOAT, 0 };        // uint[4] -> vec4 [0, 1]
        constexpr Type UIntToFloat           = { GL_UNSIGNED_INT, 1, 1 * sizeof(unsigned int), details::NO_NORMALIZE, details::TO_FLOAT, 0 };        // uint -> float
        constexpr Type UIntToNormalized       = { GL_UNSIGNED_INT, 1, 1 * sizeof(unsigned int), details::NORMALIZE, details::TO_FLOAT, 0 };        // uint -> float [0, 1]
        constexpr Type UShort               = { GL_UNSIGNED_SHORT, 1, 1 * sizeof(unsigned short), details::NO_NORMALIZE, details::TO_INT, 0 };    // ushort -> uint
        constexpr Type UShort2               = { GL_UNSIGNED_SHORT, 2, 2 * sizeof(unsigned short), details::NO_NORMALIZE, details::TO_INT, 0 };    // ushort[2] -> uvec2
        constexpr Type UShort2ToFloat       = { GL_UNSIGNED_SHORT, 2, 2 * sizeof(unsigned short), details::NO_NORMALIZE, details::TO_FLOAT, 0 }; // ushort[2] -> vec2
        constexpr Type UShort2ToNormalized = { GL_UNSIGNED_SHORT, 2, 2 * sizeof(unsigned short), details::NORMALIZE, details::TO_FLOAT, 0 };    // ushort[2] -> vec2 [0, 1]
        constexpr Type UShort3               = { GL_UNSIGNED_SHORT, 3, 3 * sizeof(unsigned short), details::NO_NORMALIZE, details::TO_INT, 0 };    // ushort[3] -> uvec3
        constexpr Type UShort3ToFloat       = { GL_UNSIGNED_SHORT, 3, 3 * sizeof(unsigned short), details::NO_NORMALIZE, details::TO_FLOAT, 0 }; // ushort[3] -> vec3
        constexpr Type UShort3ToNormalized = { GL_UNSIGNED_SHORT, 3, 3 * sizeof(unsigned short), details::NORMALIZE, details::TO_FLOAT, 0 };    // ushort[3] -> vec3 [0, 1]
        constexpr Type UShort4               = { GL_UNSIGNED_SHORT, 4, 4 * sizeof(unsigned short), details::NO_NORMALIZE, details::TO_INT, 0 };    // ushort[4] -> uvec4
        constexpr Type UShort4ToFloat       = { GL_UNSIGNED_SHORT, 4, 4 * sizeof(unsigned short), details::NO_NORMALIZE, details::TO_FLOAT, 0 }; // ushort[4] -> vec4
        constexpr Type UShort4ToNormalized = { GL_UNSIGNED_SHORT, 4, 4 * sizeof(unsigned short), details::NORMALIZE, details::TO_FLOAT, 0 };    // ushort[4] -> vec4 [0, 1]
        constexpr Type UShortToFloat       = { GL_UNSIGNED_SHORT, 1, 1 * sizeof(unsigned short), details::NO_NORMALIZE, details::TO_FLOAT, 0 }; // ushort -> float
        constexpr Type UShortToNormalized  = { GL_UNSIGNED_SHORT, 1, 1 * sizeof(unsigned short), details::NORMALIZE, details::TO_FLOAT, 0 };    // ushort -> float [0, 1]
    };

}
