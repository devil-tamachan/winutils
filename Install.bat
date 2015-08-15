cd project
rmdir /S /Q obj
cd ..
set WINUTILS_VER=1,0,3
del /Q "winutils-%WINUTILS_VER%.zip"
"C:\Program Files\7-Zip\7z.exe" a winutils-%WINUTILS_VER%.zip ndll project Build.bat Install.bat haxelib.json include.xml winutils.hx example
haxelib local winutils-%WINUTILS_VER%.zip
pause