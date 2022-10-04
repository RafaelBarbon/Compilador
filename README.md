# Compilador

![GitHub Repository Size](https://img.shields.io/github/repo-size/RafaelBarbon/Compilador?label=Repository%20Size&style=for-the-badge)

![Ubuntu](https://img.shields.io/badge/Ubuntu-E95420?style=for-the-badge&logo=ubuntu&logoColor=white)
![MAC](https://img.shields.io/badge/MAC-000000?style=for-the-badge&logo=macos&logoColor=white)
![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)

![VS Code](https://img.shields.io/badge/Visual_Studio_Code-0078D4?style=for-the-badge&logo=visual%20studio%20code&logoColor=white)

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)

## Executando
### Windows
* Abra o terminal e execute o comando `.\exec.bat` para compilar o programa
* Com o programa compilado, execute `.\compilador <nome do arquivo>.txt`
Obs: é possível obter os logs de debug executando o programa com o comando `.\compilador <nome do arquivo>.txt 1`. Caso o programa fonte a ser analisado seja muito grande, utilize `.\compilador <nome do arquivo>.txt 1 > log.txt` para salvar os logs.

### Linux && MAC
* Abra o terminal e execute o comando `make` para compilar o programa
* Com o programa compilado, execute `.\compilador <nome do arquivo>.txt`
Obs: é possível obter os logs de debug executando o programa com o comando `.\compilador <nome do arquivo>.txt 1`. Caso o programa fonte a ser analisado seja muito grande, utilize `.\compilador <nome do arquivo>.txt 1 > log.txt` para salvar os logs.

## Descrição
O presente compilador realiza a tradução da linguagem de programação conforme o diagrama sintático descrito a seguir:
![Diagrama sintático](diagrama%20sintatico.png)

## Autores
[Derek Freire Quaresma](https://github.com/derekfq)

[Henrique Sartori Siqueira](https://github.com/h-ssiqueira)

[Lucas Cicconi](https://github.com/LucasCicconi)

[Rafael Silva Barbon](https://github.com/RafaelBarbon)