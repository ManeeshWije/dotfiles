#!/usr/bin/env bash
# install homebrew
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
# path for homebrew
echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> ~/.profile
eval "$(/opt/homebrew/bin/brew shellenv)"
# install everything
brew install jdtls lua-language-server bear via postman min rust-analyzer ripgrep clang-format cmake cmatrix git go heroku htop llvm lua mongosh ncdu neofetch neovim node nvm pfetch python speedtest-cli starship tmux tty-clock audacity balenaetcher firefox caffeine discord microsoft-teams minecraft slack spotify visual-studio-code zoom alacritty mvn

ssh-keygen -t ed25519 -C "m.mwije1@gmail.com"
eval "$(ssh-agent -s)"
ssh-add -K ~/.ssh/id_ed25519

git config status.showuntrackedfiles no

# some lsp
npm install -g pyright bash-language-server dockerfile-language-server-nodejs vscode-langservers-extracted emmet-ls sql-language-server vim-language-server

# clone projects
# mkdir ~/Documents/Projects && cd Documents/Projects
# git clone git@github.com:ManeeshWije/Personal-Website.git && git clone git@github.com:ManeeshWije/Tasker.git && git clone git@github.com:ManeeshWije/GoChat.git && git clone git@github.com:ManeeshWije/pokedex.git && git clone git@github.com:ManeeshWije/abby.git && git clone git@github.com:ManeeshWije/application-tracker.git && git clone git@github.com:ManeeshWije/Reduction.git && git clone git@github.com:ManeeshWije/GetBack2Wrk.git && git clone git@github.com:ManeeshWije/twitterLikeBot.git && git clone git@github.com:ManeeshWije/Baby-Talk.git
