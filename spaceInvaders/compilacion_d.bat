﻿@REM Compilación y Enlace con librería gráfica.
@cls


cl /nologo /Zi /GR- /EHs /MD %1 -I .\deps\ESAT_rev196_vs2015\include .\deps\ESAT_rev196_vs2015\bin\ESAT_d.lib  .\deps\ESAT_rev196_vs2015\bin\ESAT_extra_d.lib opengl32.lib user32.lib gdi32.lib shell32.lib Ws2_32.lib
@echo  Proceso por lotes finalizado.
@echo -------------------------------