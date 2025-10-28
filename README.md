[BASÉ SUR ENDSTONE]

LCGBSS = LC Games Bedrock Server System

fichier de démarrage a modifier : /src/endstone/main.cpp
mettre le dossier qui est dans /LCG_I/ dans /src/
**avant toute release éxecuter le workflows .github/workflows/1 Build+Test.yml depuis [LIEN](https://github.com/Capitaine-steeve78/LCGBSS_based_on_endstone/actions/workflows/1%20Build+Test.yml)**

script d'update de endstone dans /LC_S/
  le script update.bat exclut tout fichier/dossier avec [#] devant

mettre dans /LCG_I/ le dossier /src/LC/ et le fichier /src/endstone/runtime/main.cpp





mkdir actions-runner && cd actions-runner <br>
curl -o actions-runner-linux-x64-2.329.0.tar.gz -L https://github.com/actions/runner/releases/download/v2.329.0/actions-runner-linux-x64-2.329.0.tar.gz <br>
echo "194f1e1e4bd02f80b7e9633fc546084d8d4e19f3928a324d512ea53430102e1d  actions-runner-linux-x64-2.329.0.tar.gz" | shasum -a 256 -c <br>
tar xzf ./actions-runner-linux-x64-2.329.0.tar.gz <br>
<br>
<br>
<br>
./config.sh --url https://github.com/Capitaine-steeve78/LCGBSS_based_on_endstone --token BY7GTZF5W7LYHY3AA5VJEQTJADI3C <br>
./run.sh
