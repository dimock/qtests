del /S /F *.pro *.pch *.pdb *.obj *.sbr *.exp *.lib *.idb *.ncb *.opt *.bsc *.res *.ilk *.scc *.dll *.exe *.suo *.user *.sln *.vcproj
del /S /F /A:H *.suo
rmdir /S /Q debug
rmdir /S /Q release
rmdir /S /Q x64