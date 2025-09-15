# Input Manager GTK
![print do GUI](GUIXinput.png)

Uma interface gráfica feita em **C com GTK** que permite **ativar e desativar dispositivos de entrada** (teclado, mouse, touchpad, touchscreen, etc.) no **Linux Mint**.  
O projeto utiliza **GTK** para a interface e **X11 (XInput)** para manipular os dispositivos.

---

## Funcionalidades
- Listar dispositivos de entrada disponíveis no sistema.  
- Ativar e desativar dispositivos facilmente pela interface gráfica.  

---

## Tecnologias usadas
- **C**  
- **GTK 3** (interface gráfica)  
- **X11 / XInput** (controle dos dispositivos)  

---

## 📦 Dependências
No Linux Mint, instale as bibliotecas necessárias com:

```bash
sudo apt update && sudo apt install build-essential libgtk-3-dev libxi-dev
```

## Rodar
clone o repositorio
```bash
git clone https://github.com/vinn-ic/xinput-GUi.git
```
rode o main
```bash
cd xinput-GUI/src && ./main 
```