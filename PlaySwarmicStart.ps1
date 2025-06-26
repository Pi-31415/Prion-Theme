Add-Type -AssemblyName presentationCore
$player = New-Object system.windows.media.mediaplayer
$player.open('C:\Users\paing\Documents\GitHub\Prion-Theme\SwarmicStart.mp3')
$player.Play()
Start-Sleep -Seconds 3  # Adjust this to the length of your audio