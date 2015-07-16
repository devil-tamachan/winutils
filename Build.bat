rmdir /S /Q ndll
cd project
rmdir /S /Q obj
haxelib run hxcpp Build.xml -DHXCPP_M32
haxelib run hxcpp Build.xml -DHXCPP_M64
pause