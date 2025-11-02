1. run through normal debian netinstaller
2. choose standard system utilities (we will install gnome manually to avoid too much bloat)
3. `sudo apt-get install --yes gnome-core git`
4. reboot system
5. add keyboard shortcuts (super key) for quick lauch terminal, browser, file manager, quitting windows, moving to workspaces, moving windows to workspaces, screenshots
6. disable some system and window keyboard shortcuts (focus active notif, lock screen, open quick settings, show notif list, hide window)
7. replace grub with graphical splash screen `sudo sed -i 's/GRUB_CMDLINE_LINUX_DEFAULT="quiet"/GRUB_CMDLINE_LINUX_DEFAULT="quiet splash"/' /etc/default/grub && sudo update-grub2`
8. `sudo apt-get install --show-progress --yes aptitude cups curl debian-reference deja-dup fastfetch file-roller foomatic-db-compressed-ppds gcolor3 gnome-color-manager gnome-epub-thumbnailer gnome-firmware gnome-keysign gnome-power-manager gnome-session-canberra gnome-shell-extension-launch-new-instance gnome-shell-extension-no-annoyance gnome-shell-extensions-extra gnome-software-plugin-flatpak gnome-software-plugin-snap gnome-sound-recorder gnome-tweaks gnome-video-effects-frei0r mpv-mpris nautilus-share network-manager-config-connectivity-debian network-manager-openconnect-gnome network-manager-openvpn-gnome network-manager-ssh-gnome network-manager-vpnc-gnome ooo-thumbnailer pdfarranger plymouth-themes printer-driver-cups-pdf playerctl rsync seahorse seahorse-daemon seahorse-nautilus shotwell smbclient soundconverter ssh-askpass-gnome synaptic task-laptop unattended-upgrades wireguard wl-clipboard lazygit obs-studio kdenlive libreoffice pkg-config`
9. installing languages
   - `curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh`
   - ```bash
       curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.3/install.sh | bash
       \. "$HOME/.nvm/nvm.sh"
       nvm install 24
       npm install -g prettier vscode-langservers-extracted sql-formatter
     ```
   - `wget https://go.dev/dl/go1.25.3.linux-amd64.tar.gz && sudo tar -C /usr/local -xzf go1.25.3.linux-amd64.tar.gz`
10. other packages to install either from their script or adding the apt source or by using a deb package
    - ```bash
        wget https://repo.protonvpn.com/debian/dists/stable/main/binary-all/protonvpn-stable-release_1.0.8_all.deb
        wget https://proton.me/download/authenticator/linux/ProtonAuthenticator.deb
        wget https://download.opensuse.org/repositories/home:/justkidding/Debian_13/amd64/ueberzugpp_2.9.8_amd64.deb
        wget https://vencord.dev/download/vesktop/amd64/deb
        wget https://github.com/localsend/localsend/releases/download/v1.17.0/LocalSend-1.17.0-linux-x86-64.deb
        curl -fsS https://dl.brave.com/install.sh | sh
        curl -fsSL https://opencode.ai/install | bash
        sudo dpkg -i *.deb
        sudo apt update
      ```
    ```
    - wezterm (https://wezterm.org/install/linux.html)
    - syncthing (https://apt.syncthing.net/)
    ```
11. run custom scripts to install latest neovim and yazi
12. install iosveka term font
    - `curl -OL https://github.com/ryanoasis/nerd-fonts/releases/latest/download/IosevkaTerm.tar.xz && mkdir -p IosevkaTerm && tar -xf IosevkaTerm.tar.xz -C IosevkaTerm && sudo cp -r IosevkaTerm /usr/local/share/fonts && sudo fc-cache`
    - in gnome-tweaks, edit monospace font
13. `sudo apt purge firefox-esr`
14. `ln -s $(which fdfind) ~/.local/bin/fd`
15. if this is main machine, which it probably is, setup rsync in `/etc/rsyncd.conf` and enable/start the rsync service in order for nas to pull home dir
