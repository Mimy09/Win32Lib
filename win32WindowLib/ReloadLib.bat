@echo Off

SET toolKit_include="WinTestingArea\ToolKit\*.h"
SET toolKit_lib="WinTestingArea\ToolKit_bin\*.lib"
SET toolKit_include_dest="Library\ToolKit\Include"
SET toolKit_lib_dest="Library\ToolKit\Libs"

:main
xcopy %toolKit_lib% %toolKit_lib_dest%
xcopy %toolKit_include% %toolKit_include_dest%
pause >nul