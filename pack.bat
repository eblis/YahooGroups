for /F "tokens=5-9* delims=. " %%i in (docs\YahooGroups_readme.txt) do (call :Pack %%i %%j %%k %%l; exit)

:Pack
d:\usr\PowerArchiver\pacl\pacomp.exe -a -c2 "YahooGroups %1.%2.%3.%4.zip" @files_release.txt
d:\usr\PowerArchiver\pacl\pacomp.exe -p -a -c2 "YahooGroups %1.%2.%3.%4.zip" docs\*.* *.caca
call "pack symbols.bat" YahooGroups YahooGroups %1.%2.%3.%4
exit

error:
echo "Error packing YahooGroups"
