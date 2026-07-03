1. archinstall and use minimal preset
2. `sudo pacman -S --needed git base-devel linux-headers ghostty tmux pcmanfm && git clone https://aur.archlinux.org/yay.git && cd yay && makepkg -si`
3. `yay -S hyprland hypridle hyprlock hyprpaper hyprshot hyprpolkitagent hyprgraphics hyprpicker downgrade slack-desktop cloud-sql-proxy google-cloud-cli lazygit lazydocker selectdefaultapplication-fork-git brave-origin-bin neovim-git localsend-bin pandoc-bin vesktop-git tofi xorg-xhost obs-studio onlyoffice-bin qt6ct-kde`
4. `sudo pacman -S powertop github-cli yarn network-manager-applet zsh-syntax-highlighting cronie less imv mpv wlsunset nwg-look ueberzugpp pavucontrol power-profiles-daemon blueman cliphist starship gvfs glib2 gvfs-mtp gvfs-afc gvfs-gphoto2 gvfs-nfs gvfs-smb gvfs-dnssd gvfs-goa gvfs-onedrive gvfs-wsdd brightnessctl postgresql`
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
   systemctl --user enable --now gdrive-workspace.timer
   ```
7. `sudo pacman -S docker docker-compose docker-buildx && sudo systemctl enable --now docker && sudo groupadd docker && sudo usermod -aG docker $USER`
8. import any gpg keys
9. enable multilib repo in `/etc/pacman.conf` to install steam
