1. archinstall and use minimal preset
2. `sudo pacman -S --needed git base-devel linux-headers ghostty tmux pcmanfm && git clone https://aur.archlinux.org/yay.git && cd yay && makepkg -si`
3. `yay -S hyprland hypridle hyprlock hyprpaper hyprshot hyprpolkitagent hyprgraphics hyprpicker downgrade slack-desktop cloud-sql-proxy google-cloud-cli lazygit lazydocker selectdefaultapplication-fork-git brave-bin neovim-git localsend-bin pandoc-bin vesktop-git proton-authenticator-bin proton-vpn-gtk-app tofi xorg-xhost obs-studio onlyoffice-bin qt6ct-kde`
4. `sudo pacman -S github-cli yarn network-manager-applet zsh-syntax-highlighting cronie less imv mpv wlsunset nwg-look ueberzugpp pavucontrol syncthing power-profiles-daemon blueman cliphist starship gvfs glib2 gvfs-mtp gvfs-afc gvfs-gphoto2 gvfs-nfs gvfs-smb gvfs-dnssd gvfs-goa gvfs-onedrive gvfs-wsdd brightnessctl postgresql`
5. install languages and other utils
   - ```bash
       echo "source /usr/share/zsh/plugins/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh" >> ${ZDOTDIR:-$HOME}/.zshrc
       curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
       wget https://go.dev/dl/go1.25.3.linux-amd64.tar.gz && sudo tar -C /usr/local -xzf go1.25.3.linux-amd64.tar.gz
       curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.3/install.sh | bash
       \. "$HOME/.nvm/nvm.sh"
       nvm install 24
       nvm install 22
       nvm alias default 22
       npm install -g prettier vscode-langservers-extracted sql-formatter eslint-formatter-unix
       curl -fsSL https://opencode.ai/install | bash
     ```
6. ```bash
   systemctl enable --now --user wireplumber
   systemctl enable --now --user pipewire
   systemctl enable --now --user syncthing
   ```
7. if this is main machine, which it probably is, setup rsync in `/etc/rsyncd.conf` and enable/start the rsync service in order for nas to pull syncthing dir `sudo systemctl enable --now rsyncd`
   - ```
       uid = nobody
       gid = nobody
       use chroot = no
       max connections = 4
       syslog facility = local5
       pid file = /run/rsyncd.pid

       [ftp]
       path = /srv/ftp
       comment = ftp area

       [syncthing]
       path = /home/maneesh/syncthing
       comment = syncthing dir
       read only = yes
       hosts allow = 192.168.40.46
       hosts deny = *
       uid = maneesh
       gid = maneesh
     ```

8. `sudo pacman -S docker docker-compose docker-buildx && sudo systemctl enable --now docker && sudo groupadd docker && sudo usermod -aG docker $USER`
9. import any gpg keys
10. enable multilib repo in `/etc/pacman.conf` to install steam
