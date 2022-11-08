param([switch]$Elevated)

function Test-Admin {
    $currentUser = New-Object Security.Principal.WindowsPrincipal $([Security.Principal.WindowsIdentity]::GetCurrent())
    $currentUser.IsInRole([Security.Principal.WindowsBuiltinRole]::Administrator)
}

if ((Test-Admin) -eq $false)  {
    if ($elevated) {
        # tried to elevate, did not work, aborting
    } else {
        Start-Process powershell.exe -Verb RunAs -ArgumentList ('-noprofile -noexit -file "{0}" -elevated' -f ($myinvocation.MyCommand.Definition))
    }
    exit
}


set-executionpolicy unrestricted

try
{
    git | Out-Null
   "Git is installed"
}
catch [System.Management.Automation.CommandNotFoundException]
{
    if(Get-ExecutionPolicy -ne "RemoteSigned")
    {
        Set-ExecutionPolicy -Scope CurrentUser -ExecutionPolicy RemoteSigned -Force
        Install-Module posh-git -Scope CurrentUser -Force
        Import-Module posh-git
        Add-PoshGitToProfile -AllHosts​​​​​​​
    }
}


$path = "C:\dev\vcpkg"
If(!(test-path -PathType container $path))
{
      New-Item -ItemType Directory -Path $path
}
Set-Location $path

try
{
    .\vcpkg\vcpkg | Out-Null
}
catch [System.Management.Automation.CommandNotFoundException]
{
    git clone https://github.com/microsoft/vcpkg
    .\vcpkg\bootstrap-vcpkg.bat
    .\vcpkg\vcpkg integrate install
}
finally{
	.\vcpkg install sdl2:x64-windows sdl2-image:x64-windows sdl2-mixer:x64-windows sdl2-ttf:x64-windows
	.\vcpkg install boost:x64windows 
	.\vcpkg install boost-asio:x64windows
	.\vcpkg install tinyxml::x64windows
}



