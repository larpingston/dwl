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
