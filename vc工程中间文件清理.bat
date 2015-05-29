@echo off
echo 正在清除vc程序编译时产生的中间文件，例如obj文件、pdb文件，及一些不必需的大文件例如ncb文件，请稍等......
del /f /s /q *.aps
del /f /s /q *.bsc
del /f /s /q *.dep
del /f /s /q *.exp
del /f /s /q *.idb
del /f /s /q *.ilk
del /f /s /q *.intermediate.manifest
del /f /s /q *.ipch
del /f /s /q *.lastbuildstate
del /f /s /q *.lock
del /f /s /q *.log
del /f /s /q *.manifest
del /f /s /q *.map
del /f /s /q *.meta
del /f /s /q *.ncb
del /f /s /q *.obj
del /f /s /q *.opt
del /f /s /q *.pch
del /f /s /q *.sdf
del /f /s /q *.pdb
del /f /s /q *.pgc
del /f /s /q *.pgd
del /f /s /q *.plg
del /f /s /q *.res
del /f /s /q *.rsp
del /f /s /q *.cod
del /f /s /q *.codeanalysis
del /f /s /q *.sbr
del /f /s /q *.sdf
del /f /s /q *.suo
del /f /s /q *.tlb
del /f /s /q *.tlog
del /f /s /q *.tmp
del /f /s /q *.vcproj.*.*.user
del /f /s /q BuildLog.htm
echo 清除完成！
echo. & pause