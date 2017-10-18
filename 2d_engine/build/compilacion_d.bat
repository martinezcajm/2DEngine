@REM Compilación y Enlace con librería gráfica.
@cls


cl /nologo /Zi /GR- /EHs /W4 /MD %1 -I ..\deps\ESAT_rev196_vs2015\include ..\deps\ESAT_rev196_vs2015\bin\ESAT.lib  ..\deps\ESAT_rev196_vs2015\bin\ESAT_extra.lib opengl32.lib gdi32.lib shell32.lib
@echo  Proceso por lotes finalizado.
@echo -------------------------------