^!p:: { ; Ctrl + Alt + P
    Run("C:\Program Files\JetBrains\PyCharm 2024.3.1.1\bin\pycharm64.exe") ; Open PyCharm
    Sleep(5000) ; Wait 5 seconds for PyCharm to fully load (adjust if needed)
    SetTrans(230, "ahk_class SunAwtFrame") ; Use ahk_class for precise matching
}

SetTrans(opacity, winCriteria) {
    WinSetTransparent(opacity, winCriteria)
}
