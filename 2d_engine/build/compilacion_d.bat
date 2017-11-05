@REM Compilación y Enlace con librería gráfica.
@cls


cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\entity.cc -I ..\include
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\drawable_entity.cc -I ..\include  -I ..\deps\SFML\include
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\rect.cc   -I ..\include  -I ..\deps\SFML\include
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\label.cc   -I ..\include  -I ..\deps\SFML\include
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\sprite.cc   -I ..\include  -I ..\deps\SFML\include
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\deps\imgui\imgui.cpp -I . -I ..\deps\SFML\include
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\deps\imgui\imgui_demo.cpp -I . -I ..\deps\SFML\include
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\deps\imgui\imgui_draw.cpp -I . -I ..\deps\SFML\include
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\deps\imgui-sfml\imgui-SFML.cpp -I . -I ..\deps\SFML\include -I ..\deps\imgui
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\main_sfml.cc   -I ..\include -I ..\deps\SFML\include -I ..\deps\imgui -I ..\deps\imgui-sfml
cl /nologo /Zi /GR- /EHs /W4 /MD /Fe:main_engine.exe main_sfml.obj entity.obj drawable_entity.obj rect.obj label.obj sprite.obj imgui.obj imgui_demo.obj imgui_draw.obj imgui-SFML.obj ..\deps\SFML\lib\sfml-graphics.lib ..\deps\SFML\lib\sfml-window.lib ..\deps\SFML\lib\sfml-system.lib opengl32.lib shell32.lib user32.lib gdi32.lib
@echo  Proceso por lotes finalizado.
@echo -------------------------------