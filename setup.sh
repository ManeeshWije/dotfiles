#!/usr/bin/env bash
# install homebrew
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
# path for homebrew
echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> ~/.profile
eval "$(/opt/homebrew/bin/brew shellenv)"

# install dev stuff
brew tap homebrew/cask-fonts
brew install tree font-iosevka-nerd-font pandoc qlmarkdown maccy gh black flake8 google-java-format stylua ninja tldr ltex-ls koekeishiya/formulae/yabai koekeishiya/formulae/skhd jdtls java lua-language-server bear postman rust-analyzer ripgrep clang-format cmake git go htop llvm lua mongosh ncdu neofetch neovim node nvm pfetch python tmux caffeine alacritty php starship

ssh-keygen -t ed25519 -C "m.mwije1@gmail.com"
eval "$(ssh-agent -s)"
ssh-add -K ~/.ssh/id_ed25519

git config status.showuntrackedfiles no

# some lsp and tools
npm install -g pyright bash-language-server dockerfile-language-server-nodejs vscode-langservers-extracted emmet-ls sql-language-server vim-language-server typescript typescript-language-server

yabai --start-service
skhd --start-service

# optionally install other apps
# brew install mactex via audacity balenaetcher discord microsoft-teams minecraft slack spotify visual-studio-code mvn firefox lunar-client speedtest-cli zoom
