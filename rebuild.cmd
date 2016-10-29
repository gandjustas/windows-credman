mkdir lib

call node-gyp rebuild --arch=x64  
xcopy /Y /F "build\Release\windows-credman.node" "lib\windows-credman-x64.node"

call node-gyp rebuild --arch=ia32
xcopy /Y /F "build\Release\windows-credman.node" "lib\windows-credman-ia32.node"
