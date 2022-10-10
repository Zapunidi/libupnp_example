@echo off
echo Usage: get_if_name_windows IP_address
echo Example: get_if_name_windows 192.168.10.1
setlocal
setlocal enabledelayedexpansion
set "_adapter="
set "_ip="
for /f "tokens=1* delims=:" %%g in ('ipconfig /all') do (
  set "_tmp=%%~g"
  if "!_tmp:adapter=!"=="!_tmp!" (
    if not "!_tmp:IPv4 Address=!"=="!_tmp!" (
      for %%i in (%%~h) do (
      if not "%%~i"=="" set "_ip=%%~i"
      )
    set "_ip=!_ip:(Preferred)=!"
    if "!_ip!"=="%1" (
        @echo if_name: !_adapter!
      )
    )
  ) else (
    set "_ip="
    set "_adapter=!_tmp:*adapter =!"
  )
)
endlocal