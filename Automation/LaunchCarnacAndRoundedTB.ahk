#SingleInstance Force ; Ensures only one instance of the script runs

/*
This script automatically launches Carnac and RoundedTB when executed.
*/

LaunchApps() {
    Run("C:\Users\aimlab\AppData\Local\carnac\Carnac.exe") ; Launch Carnac
    Sleep(1000) ; Wait for 1 second
    Run("C:\Users\aimlab\Documents\GitHub\Prion-Theme\RoundedTB_R3.1\RoundedTB.exe") ; Launch RoundedTB
}

LaunchApps() ; Call the function automatically when the script runs
