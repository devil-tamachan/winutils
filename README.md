# winutils
Borderless Window library for Haxe(OpenFL)

#### How to install:
  haxelib install winutils

#### Requirement:
  Windows x86/x64 (hxcpp windows / neko windows [^1])

#### Features:
  * Popup menu (Context menu) by Right Mouse button.
  * Dragging window by Left Mouse button.

#### How to use:
  example/

#### Known Error:
  SetEnable/SetCheck crash on Neko.

#### Screenshot:
  ![](http://i.imgur.com/dE8oFRG.jpg)

[^1]: Require to hide command-line. Open neko-windows (or neko-windows64) by CFF Explorer. Change subsystem to Windows GUI.


OpenFL用枠無しウィンドウライブラリ

#### インストールコマンド:
  haxelib install winutils

#### 必要環境:
  Windows x86/x64 (hxcpp windows / neko windows [^2])

#### 機能:
  * 右クリックポップアップメニュー
  * 左マウスボタンを押したまま画面ドラッグで画面移動

#### 使い方:
  example/にサンプルがあるのでそっち見て

#### 既知のバグ:
  NekoビルドでSetEnable/SetCheckを呼び出すと謎エラーで死ぬ。今のところ原因わからず。

[^2]: コマンドライン消してね。C:\HaxeToolkit\haxe\lib\lime\[2,x,x]\legacy\templates\neko\bin\neko-windows (or 64)、またはC:\HaxeToolkit\haxe\lib\lime\2,4,7\templates\neko\bin\neko-windows (or 64)を.exeに名前変更、CFF ExplorerでサブシステムをWindowsに変更して名前戻して完了