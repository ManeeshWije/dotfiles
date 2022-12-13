#!/usr/bin/env bash
# install homebrew
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
# path for homebrew
echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> ~/.profile
eval "$(/opt/homebrew/bin/brew shellenv)"
# install everything
brew install gh black google-java-format stylua ninja tldr ltex-ls rectangle jdtls java lua-language-server bear via postman rust-analyzer ripgrep clang-format cmake cmatrix git go htop llvm lua mongosh ncdu neofetch neovim node nvm pfetch python speedtest-cli starship tmux tty-clock audacity balenaetcher caffeine discord microsoft-teams minecraft slack spotify visual-studio-code zoom alacritty mvn eloston-chromium betterdiscord-installer

ssh-keygen -t ed25519 -C "m.mwije1@gmail.com"
eval "$(ssh-agent -s)"
ssh-add -K ~/.ssh/id_ed25519

git config status.showuntrackedfiles no

# some lsp
npm install -g pyright bash-language-server dockerfile-language-server-nodejs vscode-langservers-extracted emmet-ls sql-language-server vim-language-server

# clone stuff
git clone https://github.com/ManeeshWije/dotfiles.git
mkdir .virtualenvs
python3 -m venv ~/.virtualenvs/debugpy
~/.virtualenvs/debugpy/bin/python -m pip install debugpy
