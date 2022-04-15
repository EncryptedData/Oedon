
Push-Location externals/vcpkg
Start-Process -FilePath ".\bootstrap-vcpkg.bat" -Wait -NoNewWindow
Start-Process -FilePath ".\vcpkg.exe" -ArgumentList @("install", "openmesh:x64-windows") -Wait -NoNewWindow
Start-Process -FilePath ".\vcpkg.exe" -ArgumentList @("install", "glm:x64-windows-static") -Wait -NoNewWindow
Pop-Location
