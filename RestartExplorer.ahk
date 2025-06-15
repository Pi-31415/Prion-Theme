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
