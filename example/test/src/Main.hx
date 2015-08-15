package;

import openfl.display.Sprite;
import openfl.Lib;
import flash.system.System;
import Std;
#if (neko || windows)
import Winutils;
#end

/**
 * ...
 * @author 
 */
class Main extends Sprite 
{
#if (neko || windows)
	var defaultW:Float = 200;
	var defaultH:Float = 150;
	var bFullscreen = false;
	
	var cid1x = 8380;
	var cid2x = 8381;
	var cid3x = 8382;
	var cid4x = 8383;
	var cidFullscreen = 8389;
	var cidExit = 8390;
	
	public function setWndScale(s:Float):Void
	{
		bFullscreen = false;
		stage.setFullscreen(false);
		stage.resize(Std.int(defaultW * s), Std.int(defaultH * s));
	}
	
	public function scaleWnd(cid:Int):Void
	{
		var s = cid - cid1x + 1;
		setWndScale(s);
		Winutils.SetRadio(cid1x, cidFullscreen, cid);
		//Winutils.SetEnable(cid, Winutils.MF_GRAYED);
		//Winutils.SetCheck(cid, true);
	}
	public function fullscreen(cid:Int):Void
	{
		bFullscreen = !bFullscreen;
		stage.setFullscreen(bFullscreen);
		Winutils.SetRadio(cid1x, cidFullscreen, cidFullscreen);
	}
	public function myexit(cid:Int):Void
	{
		System.exit(0);
	}
	
	public function initPopupmenu():Void
	{
		Winutils.init();
		Winutils.InsertNormalMenu(cid1x, "x1", scaleWnd);
		Winutils.InsertNormalMenu(cid2x, "x2", scaleWnd);
		Winutils.InsertNormalMenu(cid3x, "x3", scaleWnd);
		Winutils.InsertNormalMenu(cid4x, "x4", scaleWnd);
		Winutils.InsertNormalMenu(cidFullscreen, "Fullscreen", fullscreen);
		Winutils.InsertSeparatorMenu();
		Winutils.InsertNormalMenu(cidExit, "Exit", myexit);
		
		Winutils.SetRadio(cid1x, cidFullscreen, cid1x);
		//Winutils.EnableRMouseDrag(false);
	}
#end

	public function new() 
	{
		super();
		
#if (neko || windows)
#if neko //http://community.openfl.org/t/strange-uncaught-exception-on-nekovm/1815/8
    cpp.Prime.nekoInit("winutils");
#end
		initPopupmenu();
#end
	}

}
