@REM Compilación y Enlace con librería gráfica.
@cls


cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\entity.cc -I ..\deps
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\rect.cc   -I ..\deps  -I ..\deps\SFML\include
cl /nologo /Zi /GR- /EHs /W4 /c /MD ..\src\main_sfml.cc   -I ..\deps -I ..\deps\SFML\include
cl /nologo /Zi /GR- /EHs /W4 /MD /Fe:main_engine.exe main_sfml.obj entity.obj rect.obj ..\deps\SFML\lib\sfml-graphics.lib ..\deps\SFML\lib\sfml-window.lib ..\deps\SFML\lib\sfml-system.lib opengl32.lib shell32.lib user32.lib gdi32.lib
@echo  Proceso por lotes finalizado.
@echo -------------------------------