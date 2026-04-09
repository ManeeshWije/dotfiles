0. most apps (discord, proton auth, vpn) can just search and install the .deb file or run install script (brave, flux), for ghostty and yazi use custom script, gnome extensions: caffeine, clipboard indicator
1. for neovim, clone repo
    - make CMAKE_BUILD_TYPE=RelWithDebInfo
    - cd build && cpack -G DEB && sudo dpkg -i nvim-linux-x86_64.deb
2. sudo apt install rsync curl less lazygit font-manager zsh starship tmux ffmpeg 7zip jq poppler-utils fd-find ripgrep fzf zoxide imagemagick obs-studio syncthing ncdu fastfetch
3. chsh -s /bin/zsh maneesh
4. install languages and other utils
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
       curl -s https://fluxcd.io/install.sh | sudo bash
       bash <(wget -qO- https://raw.githubusercontent.com/daveprowse/scripts/refs/heads/main/dog-install.sh)
       ya pkg install --discard
     ```
5.  ```
    go install github.com/jesseduffield/lazydocker@latest
    go install github.com/derailed/k9s@latest
    ```
6. ```bash
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

8. install docker
9. install ueberzugpp for image previews in yazi
10. import any gpg keys
