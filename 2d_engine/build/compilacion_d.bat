@REM Compilación y Enlace con librería gráfica.
@cls

cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\deps\tinyfiledialogs\tinyfiledialogs.c -I ..\deps\tinyfiledialogs
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\native_dialogs.cc -I ..\include -I ..\deps\tinyfiledialogs
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\deps\imgui\imgui.cpp -I . -I ..\deps\SFML\include
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\deps\imgui\imgui_demo.cpp -I . -I ..\deps\SFML\include
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\deps\imgui\imgui_draw.cpp -I . -I ..\deps\SFML\include
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\deps\imgui-sfml\imgui-SFML.cpp -I . -I ..\deps\SFML\include -I ..\deps\imgui
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\window.cc -I ..\include -I ..\deps\SFML\include
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\game_manager.cc -I ..\include -I ..\deps\SFML\include -I ..\deps\tinyfiledialogs
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\entity.cc -I ..\include
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\drawable_entity.cc -I ..\include  -I ..\deps\SFML\include
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\rect.cc -I ..\include  -I ..\deps\SFML\include
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\label.cc -I ..\include  -I ..\deps\SFML\include -I ..\deps\tinyfiledialogs
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\sprite.cc -I ..\include  -I ..\deps\SFML\include
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\background.cc -I ..\include -I ..\deps\SFML\include
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\ball.cc -I ..\include -I ..\deps\SFML\include -I ..\deps\tinyfiledialogs
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\brick.cc -I ..\include -I ..\deps\SFML\include -I ..\deps\tinyfiledialogs
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\wall.cc -I ..\include -I ..\deps\SFML\include
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\player.cc -I ..\include -I ..\deps\SFML\include -I ..\deps\tinyfiledialogs
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\pool.cc -I ..\include -I ..\deps\SFML\include -I ..\deps\tinyfiledialogs
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\scene.cc -I ..\include -I ..\deps\SFML\include -I ..\deps\json-develop\src\ -I ..\deps\tinyfiledialogs -I ..\deps\imgui -I ..\deps\imgui-sfml
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\user_interface.cc -I ..\deps  -I ..\deps\SFML\include -I ..\include -I ..\deps\imgui -I ..\deps\imgui-sfml -I ..\deps\tinyfiledialogs
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\game.cc -I ..\deps  -I ..\deps\SFML\include -I ..\include -I ..\deps\imgui -I ..\deps\imgui-sfml -I ..\deps\tinyfiledialogs
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\main_game.cc   -I ..\include -I ..\deps\SFML\include -I ..\deps\imgui -I ..\deps\imgui-sfml -I ..\deps\tinyfiledialogs
cl /nologo /Zi /GR- /EHs /MD /Fe:..\bin\main_engine.exe main_game.obj entity.obj drawable_entity.obj rect.obj label.obj wall.obj ball.obj brick.obj player.obj window.obj game_manager.obj game.obj scene.obj sprite.obj background.obj pool.obj user_interface.obj native_dialogs.obj tinyfiledialogs.obj imgui.obj imgui_demo.obj imgui_draw.obj imgui-SFML.obj ..\deps\SFML\lib\sfml-graphics.lib ..\deps\SFML\lib\sfml-window.lib ..\deps\SFML\lib\sfml-system.lib opengl32.lib shell32.lib user32.lib gdi32.lib Comdlg32.lib Ole32.lib
@echo  Proceso por lotes finalizado.
@echo -------------------------------