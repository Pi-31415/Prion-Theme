#SingleInstance Force ; Ensures only one instance of the script runs, replacing the old instance automatically

/*
Shortcut List:
1. Ctrl + Alt + E: Restart Windows Explorer
2. Ctrl + Alt + C: Set Google Chrome window transparency to 230
3. Ctrl + Alt + P: Open PyCharm and set its window transparency to 230
4. Ctrl + Alt + T: Open Windows Terminal
5. Ctrl + Alt + O: Set Obsidian and Todoist window transparency to 210
6. Ctrl + Alt + L: Open this script to view the list of shortcuts
7. Ctrl + Alt + Q: Terminate Carnac application
8. Ctrl + Alt + G: Open ChatGPT in a new Chrome tab
9. Ctrl + Alt + K: Kill all aesthetic applications (Rainmeter, QuickLook, RoundedTB, System Transparency, Lively Wallpaper)
10. Ctrl + Alt + R: Restart all aesthetic applications (Rainmeter, QuickLook, RoundedTB, System Transparency, Lively Wallpaper)
11. Ctrl + Alt + A: Set transparency for the currently active window
12. Ctrl + Alt + W: Custom transparency dialog for any window

13. On Startup: Automatically set Obsidian and Todoist window transparency to 210 after 30 seconds
*/

; Check if the script is running with admin rights
if not A_IsAdmin
{
    ; Restart the script with admin rights
    Run "*RunAs " A_ScriptFullPath
    ExitApp
}

^!e:: { ; Ctrl + Alt + E
    RestartExplorer()
}

RestartExplorer() {
    ; Kill the Explorer process
    Run("taskkill /f /im explorer.exe", , "Hide")
    Sleep(500) ; Wait for a moment to ensure the process is terminated
    ; Restart Explorer
    Run("explorer.exe")
}

^!c:: { ; Ctrl + Alt + C
    SetTitleMatchMode(2) ; Set matching mode to "contains"
    SetTrans(230, "Google Chrome")
}

SetTrans(opacity, winTitle) {
    if WinExist(winTitle) {
        WinSetTransparent(opacity, winTitle) ; Set transparency only if the window exists
    }
    ; Do nothing if the window is not found
}

^!p:: { ; Ctrl + Alt + P
    Run("C:\Program Files\JetBrains\PyCharm 2024.3.1.1\bin\pycharm64.exe") ; Open PyCharm
    Sleep(5000) ; Wait 5 seconds for PyCharm to fully load (adjust if needed)
    SetTransPycharm(230, "ahk_class SunAwtFrame") ; Use ahk_class for precise matching
}

SetTransPycharm(opacity, winCriteria) {
    if WinExist(winCriteria) {
        WinSetTransparent(opacity, winCriteria) ; Set transparency only if the window exists
    }
    ; Do nothing if the window is not found
}


^!t:: { ; Ctrl + Alt + T
    Run("wt")
}


^!o:: { ; Ctrl + Alt + O
    Sleep(500) ; Allow time to activate or switch to Obsidian if needed
    SetTrans(230, "ahk_class Chrome_WidgetWin_1") ; Set Obsidian window transparency to 230 
    Sleep(500) ;
    SetTrans(230, "ahk_class ApplicationFrameWindow") ;
    Sleep(500) ; Wait 5 seconds for PyCharm to fully load (adjust if needed)
    SetTransPycharm(230, "ahk_class SunAwtFrame") ; Use ahk_class for precise matching
    Sleep(500) ; Wait for a moment to ensure the process is terminated
}


^!l:: { ; Ctrl + Alt + L
    Run("notepad C:\Users\aimlab\Documents\GitHub\Prion-Theme\shortcuts.ahk") ; Open this script in notepad
    Sleep(500) ;
    SetTransPycharm(190, "ahk_class Notepad") ; Use ahk_class for precise matching
}

^!q:: { ; Ctrl + Alt + Q
    Run("taskkill /f /im Carnac.exe", , "Hide") ; Forcefully terminate Carnac
}

^!g:: { ; Ctrl + Alt + G
    Run("C:\Program Files\BraveSoftware\Brave-Browser\Application\brave.exe --new-tab https://chatgpt.com/ --new-tab https://claude.ai/new --new-tab https://gemini.google.com/app --new-tab https://chat.deepseek.com/") ; Open ChatGPT in a new Chrome tab
    Sleep(2000) ; Wait for a moment to ensure the process is terminated
}


^!k:: { ; Ctrl + Alt + K
    KillAestheticApps()
}

KillAestheticApps() {
    apps := ["Rainmeter.exe", "QuickLook.exe", "RoundedTB.exe", "System Transparency.exe", "Lively.exe","Todoist.exe","Obsidian.exe"]
    for index, app in apps {
        try {
            Run("taskkill /f /im " app, , "Hide")
        } catch {
            continue ; Skip and move to the next application without showing a message
        }
    }
}

^!r:: { ; Ctrl + Alt + R
    RestartAestheticApps()
}

RestartAestheticApps() {
    try {
        Run("C:\\Users\\aimlab\\AppData\\Local\\Programs\\QuickLook\\QuickLook.exe")
        Sleep(1000) ; Wait 1 second
    } catch {
        ; Skip if it fails
    }
    
    try {
        Run("C:\\Program Files\\Rainmeter\\Rainmeter.exe")
        Sleep(1000) ; Wait 1 second
    } catch {
        ; Skip if it fails
    }

     try {
        Run("C:\\Program Files\\Obsidian\\Obsidian.exe")
        Sleep(1000) ; Wait 1 second
    } catch {
        ; Skip if it fails
    }

     try {
        Run(" C:\\Users\\aimlab\\AppData\\Local\\Programs\\todoist\\Todoist.exe")
        Sleep(1000) ; Wait 1 second
    } catch {
        ; Skip if it fails
    }

    
    try {
        Run("C:\\Users\\aimlab\\Documents\\GitHub\\Prion-Theme\\RoundedTB_R3.1\\RoundedTB.exe")
        Sleep(1000) ; Wait 1 second
    } catch {
        ; Skip if it fails
    }
    
    try {
        Run("C:\\Users\\aimlab\\Documents\\GitHub\\Prion-Theme\\System_Transparency_by_Prisoner7\\System Transparency.exe")
        Sleep(1000) ; Wait 1 second
    } catch {
        ; Skip if it fails
    }
    
    try {
        Run("C:\\Program Files\\WindowsApps\\12030rocksdanister.LivelyWallpaper_1.0.144.0_x64__97hta09mmv6hy\\Build\\Lively.exe")
        Sleep(1000) ; Wait 1 second
    } catch {
        ; Skip if it fails
    }
}

; Add a new shortcut to set transparency for any active window (including admin windows)
^!a:: { ; Ctrl + Alt + A
    SetTransActive(230)
}

SetTransActive(opacity) {
    try {
        WinSetTransparent(opacity, "A") ; Set transparency for the active window
    } catch {
        MsgBox("Failed to set transparency for the active window.")
    }
}

; Add a new function to set transparency for a specific admin application by its window title
^!w:: { ; Ctrl + Alt + W
    InputBox(&winTitle, "Set Window Transparency", "Enter window title (partial match is fine):")
    if (!winTitle) {
        return ; Do nothing if canceled or empty
    }
    
    InputBox(&opacityStr, "Set Window Transparency", "Enter opacity (0-255):")
    if (!opacityStr) {
        return ; Do nothing if canceled or empty
    }
    
    opacity := Integer(opacityStr)
    if (opacity < 0 || opacity > 255) {
        MsgBox("Invalid opacity value. Must be between 0 and 255.")
        return
    }
    
    SetTitleMatchMode(2) ; Set matching mode to "contains"
    SetTrans(opacity, winTitle)
}

SetObsidianAndTodoistTransparency() {
    Sleep(30000) ; Wait 30 seconds after script starts
    SetTitleMatchMode(2) ; Set matching mode to "contains"
    
    ; Check if the Obsidian or Todoist window exists
    if WinExist("ahk_class Chrome_WidgetWin_1") {
        SetTrans(210, "ahk_class Chrome_WidgetWin_1") ; Set transparency to 210
    }
    ; Do nothing if the window is not found
}

SetObsidianAndTodoistTransparency() ; Call the function immediately on script execution