package;

#if cpp
import cpp.Lib;
#elseif neko
import neko.Lib;
#end

#if (android && openfl)
import openfl.utils.JNI;
#end


class Winutils
{
  public static function init ():Void
  {
    winutils_init();
  }
  public static function exit ():Void
  {
    winutils_exit();
  }
  public static function InsertNormalMenu(uid:Int, str:String, callback:Int->Void):Void
  {
    winutils_insertnormalmenu(uid, str, callback);
  }
  public static function InsertSeparatorMenu():Void
  {
    winutils_insertseparatormenu();
  }
  public static function SetRadio(iFirst:Int, iLast:Int, iCheck:Int):Void
  {
    winutils_setradio(iFirst, iLast, iCheck);
  }
  public static var MF_ENABLED = 0;
  public static var MF_GRAYED = 1;
  public static var MF_DISABLED = 2;
  public static function SetEnable(iPos:Int, iEnable:Int):Void
  {
    winutils_setenable(iPos, iEnable);
  }
  public static function SetCheck(iPos:Int, bCheck:Bool):Void
  {
    winutils_setcheck(iPos, bCheck);
  }
  public static function EnableRMouseDrag(bEnable:Bool):Void
  {
    winutils_enablermousedrag(bEnable);
  }
  
  
  private static var winutils_init = Lib.load ("winutils", "winutils_init", 0);
  private static var winutils_exit = Lib.load ("winutils", "winutils_exit", 0);
  private static var winutils_insertnormalmenu = Lib.load ("winutils", "winutils_insertnormalmenu", 3);
  private static var winutils_insertseparatormenu = Lib.load ("winutils", "winutils_insertseparatormenu", 0);
  private static var winutils_setradio = Lib.load ("winutils", "winutils_setradio", 3);
  private static var winutils_setenable = Lib.load ("winutils", "winutils_setenable", 2);
  private static var winutils_setcheck = Lib.load ("winutils", "winutils_setcheck", 2);
  private static var winutils_enablermousedrag = Lib.load ("winutils", "winutils_enablermousedrag", 1);
}