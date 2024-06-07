#!/usr/bin/env bash
# install homebrew
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
# path for homebrew
echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> ~/.profile
eval "$(/opt/homebrew/bin/brew shellenv)"

# install dev stuff
brew tap homebrew/cask-fonts
# core utils stuff
brew install bat eza fd sd ripgrep tokei zoxide fzf jq btop ncdu
# programming
brew install git bear postman wezterm neovim pure font-iosevka-nerd-font gh
# language stuff
brew install ltex-ls jdtls java lua-language-server rust-analyzer clang-format cmake go llvm lua node nvm python php flake8 stylua ninja google-java-format black
# tools
brew install yazi mpv ffmpegthumnailer unar poppler pass pandoc qlmarkdown maccy tldr macchina syncthing
brew install --cask karabiner-elements nikitabobko/tap/aerospace

ssh-keygen -t ed25519 -C "m.mwije1@proton.me"
eval "$(ssh-agent -s)"
ssh-add -K ~/.ssh/id_ed25519

yabai --start-service
skhd --start-service

echo "git config --global core.fsmonitor true" >> ~/.gitconfig

# optionally install other apps
# brew install --cask docker
# brew install mactex via audacity balenaetcher discord microsoft-teams slack spotify visual-studio-code mvn firefox speedtest-cli zoom
