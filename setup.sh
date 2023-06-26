#!/usr/bin/env bash
# install homebrew
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
# path for homebrew
echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> ~/.profile
eval "$(/opt/homebrew/bin/brew shellenv)"

# install everything
brew tap homebrew/cask-fonts
brew install font-iosevka-nerd-font mactex pandoc qlmarkdown maccy gh black flake8 google-java-format stylua ninja tldr ltex-ls yabai skhd jdtls java lua-language-server bear via postman rust-analyzer ripgrep clang-format cmake git go htop llvm lua mongosh ncdu neofetch neovim node nvm pfetch python speedtest-cli starship tmux audacity balenaetcher caffeine discord microsoft-teams minecraft slack spotify visual-studio-code zoom alacritty mvn firefox 
git clone --depth 1 https://github.com/wbthomason/packer.nvim\
 ~/.local/share/nvim/site/pack/packer/start/packer.nvim

ssh-keygen -t ed25519 -C "m.mwije1@gmail.com"
eval "$(ssh-agent -s)"
ssh-add -K ~/.ssh/id_ed25519

git config status.showuntrackedfiles no

# some lsp
npm install -g pyright bash-language-server dockerfile-language-server-nodejs vscode-langservers-extracted emmet-ls sql-language-server vim-language-server

yabai --start-service
skhd --start-service
