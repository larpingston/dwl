# my custom dwl buiild with built in slstatus like bar

<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/c18979f0-18da-431e-b274-b400f192de5e" />
<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/90c40e47-609d-43c4-ad8b-28202ab12435" />
<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/c624dbde-2385-4837-9084-b69c596a0247" />

# setup shell script (arch)
```sh
#!/bin/sh
set -e

printf "sudo or doas? > "
read -r TOOL

deps="git make gcc pkgconf wayland-protocols wlroots0.19 libinput libxkbcommon fcft tllist grim slurp wl-clipboard xorg-xwayland xcb-util-wm terminus-font ttf-terminus-nerd wmenu awww"

$TOOL pacman -S --needed --noconfirm $deps

git clone https://github.com/larpingston/dwl dwl
cd dwl && $TOOL make clean install && cd ..

git clone https://github.com/sahaj-b/wayvibes.git wayvibes
cd wayvibes && $TOOL make clean install && cd ..
```
# default keybindings

MOD = super key

## launch
- `MOD + space` : wmenu launcher
- `MOD + q` : foot terminal
- `MOD + w` : brave browser
- `MOD + e` : thunar file manager
- `printscreen` : fullscreen screenshot 
- `ctrl + printscreen` : region screenshot

## windows
- `MOD + j/k` : focus up/down
- `MOD + h/l` : resize width
- `MOD + return` : promote to master
- `MOD + c` : close
- `MOD + v` : toggle float
- `MOD + shift + return` : fullscreen

## layout
- `MOD + t` : tile
- `MOD + f` : float
- `MOD + d` : dwindle

## tags
- `MOD + 1-6` : go to tag
- `MOD + shift + 1-6` : move window to tag
- `MOD + tab` : previous tag
- `MOD + 0` : show all

## gaps
- `Alt + p` : toggle
- `Alt + i/o` : decrease/increase

## misc
- `MOD + b` : toggle bar
- `MOD + m` : quit
