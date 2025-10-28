[BASÉ SUR ENDSTONE]

LCGBSS = LC Games Bedrock Server System

fichier de démarrage a modifier : /src/endstone/main.cpp
mettre le dossier qui est dans /LCG_I/ dans /src/
**avant toute release éxecuter le workflows .github/workflows/1 Build+Test.yml depuis [LIEN](https://github.com/Capitaine-steeve78/LCGBSS_based_on_endstone/actions/workflows/1%20Build+Test.yml)**

script d'update de endstone dans /LC_S/
  le script update.bat exclut tout fichier/dossier avec [#] devant

mettre dans /LCG_I/ le dossier /src/LC/ et le fichier /src/endstone/runtime/main.cpp



mkdir actions-runner; cd actions-runner <br>
Invoke-WebRequest -Uri https://github.com/actions/runner/releases/download/v2.329.0/actions-runner-win-x64-2.329.0.zip -OutFile actions-runner-win-x64-2.329.0.zip <br>
if((Get-FileHash -Path actions-runner-win-x64-2.329.0.zip -Algorithm SHA256).Hash.ToUpper() -ne 'f60be5ddf373c52fd735388c3478536afd12bfd36d1d0777c6b855b758e70f25'.ToUpper()){ throw 'Computed checksum did not match' } <br>
Add-Type -AssemblyName System.IO.Compression.FileSystem ; [System.IO.Compression.ZipFile]::ExtractToDirectory("$PWD/actions-runner-win-x64-2.329.0.zip", "$PWD")<br>
<br>
<br>
./config.cmd --url https://github.com/Capitaine-steeve78/LCGBSS_based_on_endstone --token BY7GTZDRQY6SH7NV74C5EZ3JAC3AE <br>
./run.cmd<br>
