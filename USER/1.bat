CD ..\Obj
srec_cat.exe -Disable_Sequence_Warning T5L51.hex -Intel -o T5L51.bin -Binary 
echo.
copy "T5L51.bin" "C:\Users\DinoAutomation\Downloads\Interfaces Perilla\CPAP_HMI_VKnobV2\DWIN_SET\" /Y
