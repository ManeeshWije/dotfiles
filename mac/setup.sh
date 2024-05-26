#!/usr/bin/env bash
# install homebrew
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
# path for homebrew
echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> ~/.profile
eval "$(/opt/homebrew/bin/brew shellenv)"

# install dev stuff
brew tap homebrew/cask-fonts
brew install ranger fzf bat tree pass pure font-iosevka-nerd-font pandoc qlmarkdown maccy gh black flake8 google-java-format stylua ninja tldr ltex-ls koekeishiya/formulae/yabai koekeishiya/formulae/skhd jdtls java lua-language-server bear postman rust-analyzer ripgrep clang-format cmake git go btop llvm lua ncdu neofetch neovim node nvm pfetch python wezterm php
brew install --cask karabiner-elements

ssh-keygen -t ed25519 -C "m.mwije1@proton.me"
eval "$(ssh-agent -s)"
ssh-add -K ~/.ssh/id_ed25519

yabai --start-service
skhd --start-service

echo "git config --global core.fsmonitor true" >> ~/.gitconfig

# optionally install other apps
# brew install --cask docker
# brew install mactex via audacity balenaetcher discord microsoft-teams slack spotify visual-studio-code mvn firefox speedtest-cli zoom
