package;

import openfl.display.Sprite;
import openfl.Lib;
import flash.system.System;
import Std;
import Popupmenu;

/**
 * ...
 * @author 
 */
class Main extends Sprite 
{
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
		Popupmenu.SetRadio(cid1x, cidFullscreen, cid);
		//Popupmenu.SetEnable(cid, Popupmenu.MF_GRAYED);Uncaught exception
		//Popupmenu.SetCheck(cid, true);Uncaught exception
	}
	public function fullscreen(cid:Int):Void
	{
		bFullscreen = !bFullscreen;
		stage.setFullscreen(bFullscreen);
		Popupmenu.SetRadio(cid1x, cidFullscreen, cidFullscreen);
	}
	public function myexit(cid:Int):Void
	{
		System.exit(0);
	}
	
	public function initPopupmenu():Void
	{
		Popupmenu.init();
		Popupmenu.InsertNormalMenu(cid1x, "x1", scaleWnd);
		Popupmenu.InsertNormalMenu(cid2x, "x2", scaleWnd);
		Popupmenu.InsertNormalMenu(cid3x, "x3", scaleWnd);
		Popupmenu.InsertNormalMenu(cid4x, "x4", scaleWnd);
		Popupmenu.InsertNormalMenu(cidFullscreen, "Fullscreen", fullscreen);
		Popupmenu.InsertSeparatorMenu();
		Popupmenu.InsertNormalMenu(cidExit, "Exit", myexit);
		
		Popupmenu.SetRadio(cid1x, cidFullscreen, cid1x);
		//Winutils.EnableRMouseDrag(false);
	}

	public function new() 
	{
		super();
		
		initPopupmenu();
	}

}
