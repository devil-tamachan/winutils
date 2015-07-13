del /Q ndll\\Windows ndll\\Windows64
cd project
del /Q obj
haxelib run hxcpp Build.xml -DHXCPP_M32
haxelib run hxcpp Build.xml -DHXCPP_M64
pause