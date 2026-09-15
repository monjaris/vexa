# Someone experienced with powershell may contribute to this script

xmake run $args[0] *> $null || Write-Output "Example '$($args[0])' does not exist!"
