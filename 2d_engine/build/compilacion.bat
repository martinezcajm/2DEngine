@REM Compilación y Enlace con librería gráfica.
@cls


cl /nologo /O2 /GR- /EHs /W4 /c /MD ..\src\entity.cc -I ..\deps -I ..\deps\ESAT_rev196_vs2015\include
cl /nologo /O2 /GR- /EHs /W4 /c /MD ..\src\rect.cc   -I ..\deps -I ..\deps\ESAT_rev196_vs2015\include
cl /nologo /O2 /GR- /EHs /W4 /c /MD ..\src\main.cc   -I ..\deps -I ..\deps\ESAT_rev196_vs2015\include
cl /nologo /O2 /GR- /EHs /W4 /MD /Fe:main_engine.exe main.obj entity.obj rect.obj ..\deps\ESAT_rev196_vs2015\bin\ESAT.lib  ..\deps\ESAT_rev196_vs2015\bin\ESAT_extra.lib opengl32.lib shell32.lib user32.lib gdi32.lib
@echo  Proceso por lotes finalizado.
@echo -------------------------------